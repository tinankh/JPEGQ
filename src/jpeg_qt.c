/*----------------------------------------------------------------------------

  Copyright (c) 2020-2022 Rafael Grompone von Gioi <grompone@gmail.com>
  Copyright (c) 2020-2022 Tina Nikoukhah <tinanikoukhah@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program. If not, see <https://www.gnu.org/licenses/>.

  ----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/* PI */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif /* !M_PI */

/*----------------------------------------------------------------------------*/
#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

/*----------------------------------------------------------------------------*/
/* fatal error, print a message to standard-error output and exit.
 */
void error(char * msg) {
    fprintf(stderr, "error: %s\n", msg);
    exit(EXIT_FAILURE);
}

/*----------------------------------------------------------------------------*/
/* memory allocation, initialization to 0, print an error and exit if fail.
 */
void * xcalloc(size_t n_items, size_t size) {
    void * p;
    if (size == 0)
        error("xcalloc: zero size");
    p = calloc(n_items, size);
    if (p == NULL)
        error("xcalloc: out of memory");
    return p;
}

/*----------------------------------------------------------------------------*/
/* convert RGB image to luminance.
 */
void rgb2luminance(double * input, double * output, int X, int Y, int C) {
    if (C >= 3) {
        for (int x=0; x<X; x++)
            for(int y=0; y<Y; y++)
                output[x+y*X] = round(0.299 * input[x + y*X + 0*X*Y]
                                    + 0.587 * input[x + y*X + 1*X*Y]
                                    + 0.114 * input[x + y*X + 2*X*Y]);
    }
    else
        memcpy(output, input, X*Y*sizeof(double));
}

/*----------------------------------------------------------------------------*/
/* compute DCT coefficients
 */
double * compute_dct_coefficients(double * image, int X, int Y, int * N) {
    double * c;
    int n = 0;

    /* get memory */
    c = (double *) xcalloc(X * Y, sizeof(double));

    for (int x=0; x<X-7; x+=8) {
        for (int y=0; y<Y-7; y+=8) {
            for (int i=0; i<8; i++) {
                for (int j=0; j<8; j++) {
                    double dct_ij = 0.0;

                    for (int xx=0; xx<8; xx++)
                        for (int yy=0; yy<8; yy++)
                            dct_ij += image[x+xx + (y+yy) * X]
                                * cos((2.0*xx+1.0) * i * M_PI / 16.0)
                                * cos((2.0*yy+1.0) * j * M_PI / 16.0);

                    dct_ij *= 0.25
                        * (i==0 ? 1.0/sqrt(2.0) : 1.0)
                        * (j==0 ? 1.0/sqrt(2.0) : 1.0);

                    c[64*n + i + j*8] = dct_ij;
                }
            }
            n++;
        }
    }

    *N = n;

    return c;
}

/*----------------------------------------------------------------------------*/
/* Upper-bound of log P(S_n<=s), where S_n is a Irwin-Hall random variable.
 */
double log_irwin_hall_pvalue(int nn, double s) {
    double n = (double) nn;
    double t = 0.5 * n - s;

    /* the sum s is larger than the mean value, so P ~ 1 */
    if(t < 0.0) return 0.0;

    /* the first term of Irwin-Hall p-value is an upper-bound */
    double pvalue_first_term = n * log10(s) - 0.5 * log10(2.0 * M_PI)
                             - (n+0.5) * log10(n) + n * log10(exp(1.0));

    /* Irwin-Hall p-value can be upper-bounded by Hoeffding's inequality */
    double pvalue_hoeffding = - 2.0 * t * t / n * log10(exp(1.0));

    /* return the smallest of the two upper-bounds */
    return MIN(pvalue_first_term, pvalue_hoeffding);
}

/*----------------------------------------------------------------------------*/
/* computes quantization NFA (in log10) for coefficient c
   and quantization value q
 */
double quantization_nfa(double * coeff, int N, int c, double q) {
    double logNT = log10(64.0 * 63.0 * 255.0);
    double logNFA;
    double s = 0.0;  /* sum of normalized quantization errors */
    int n = 0;       /* number of considered values */

    /* compute the sum of quantization errors */
    for (int i=0; i<N; i++) {     /* loop over all JPEG blocks of the image */
        double v = coeff[64*i + c];  /* DCT coefficient number c of block i */
        double V = round(v / q);     /* nearest quantized value */

        if (V != 0.0) {   /* avoid central peak */
            double e = 2.0 * fabs(v/q - V);  /* normalized error to [0,1] */
            s += e;       /* update sum of normalized quantization errors */
            n++;          /* update number of considered values */
        }
    }

    /* normal approximation of Irwin-Hall law */
    logNFA = logNT + log_irwin_hall_pvalue(n,s);

    return logNFA;
}

/*----------------------------------------------------------------------------*/
/* JPEG Q-table estimation
   Input:
     image    pointer to input data
     X        number of columns
     Y        number of rows
     C        number of channesl
   Output:
     Q        Q-table (-1 for non-detected elements)
     logNFA   associated logNFA table
 */
void jpeg_qt(double * image, int X, int Y, int C, double * Q, double * logNFA) {

    /* compute luminance channel */
    double * luminance = (double *) xcalloc(X*Y, sizeof(double));
    rgb2luminance(image, luminance, X, Y, C);

    /* compute all DCT coefficients for all image blocks*/
    int N;
    double * coeff = compute_dct_coefficients(luminance, X, Y, &N);

    /* estimate quantization matrix */
    for (int c=1; c<64; c++) {  /* loop on coefficients (DC coeff excluded) */
        Q[c] = -1.0;            /* initialize Q-table as non-detected */
        logNFA[c] = DBL_MAX;    /* initialize NFA as not meaningful */

        for (double q=1.0; q<=255.0; q+=1.0) { /* loop on quantization values */
            double lnfa = quantization_nfa(coeff, N, c, q);

            /* keep the best q value */
            if (lnfa < logNFA[c]) {
                logNFA[c] = lnfa;

                if (lnfa < 0.0)
                    Q[c] = q;
            }
        }
    }

    /* free memory */
    free(coeff);
    free(luminance);
}
/*----------------------------------------------------------------------------*/
