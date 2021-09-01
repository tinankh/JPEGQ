/*----------------------------------------------------------------------------

  Copyright (c) 2020-2021 Rafael Grompone von Gioi <grompone@gmail.com>
  Copyright (c) 2020-2021 Tina Nikoukhah <tinanikoukhah@gmail.com>

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

#include "iio.h"

/*----------------------------------------------------------------------------*/
/* fatal error, print a message to standard-error output and exit.
 */
void error(char * msg) {
    fprintf(stderr,"error: %s\n",msg);
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
/* convert rgb image to luminance.
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
/* compute dct coefficients
 */

double * compute_dct_coefficients(double * image, int X, int Y, int * N) {
    double * c;
    int n = 0;
    int x,y;

    /* get memory */
    c = (double *) xcalloc(64 * X * Y, sizeof(double));

    for (x=0; x<X-7; x+=8) {
        for (y=0; y<Y-7; y+=8) {
            int xx, yy, i, j;

            for (i=0; i<8; i++) {
                for (j=0; j<8; j++) {
                    double dct_ij = 0.0;

                    for (xx=0; xx<8; xx++)
                        for (yy=0; yy<8; yy++)
                            dct_ij += image[x+xx + (y+yy) * X]
                                * cos((2.0*xx+1.0) * i * M_PI / 16.0)
                                * cos((2.0*yy+1.0) * j * M_PI / 16.0);
                    dct_ij *= 0.25 * (i==0 ? 1.0/sqrt(2.0) : 1.0)
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
/**
 * @brief       Computes the logarithm of NFA to base 10
 * @param       coeff DCT coefficient
 * @param       N number of bins
 * @param       c coefficient position amogng the 64 possibilities
 * @param       Q possible value from 1 to 255
 * @return      log10(NFA)
 */

double quantization_nfa(double * coeff, int N, int c, double Q) {
    double logNFA;
    double logNT = log10(64.0 * 255.0);
    double s = 0.0;
    int n = 0;
    int i;

    /* compute the sum of quantization errors */
    for (i=0; i<N; i++) {
        double v = fabs(coeff[64*i + c]);
        double q = round(v / Q);
        /* normalized error to [0,1] */
        double e = 2.0 * fabs(v/Q - q);

        if (fabs(q) >= 1.0) {
            n ++;
            s += e;
        }
    }

    /* NFA = NT * s^n / n! */
    /* log(n!) is bounded by Stirling's approximation: */
    /* n! >= sqrt(2pi) * n^(n+0.5) * exp(-n) */
    /* then, log10(NFA) <= log10(NT) + n*log10(s) - log10(latter expansion) */
    logNFA = logNT + n * log10(s)
        - 0.5 * log10(2.0 * M_PI) - (n+0.5) * log10(n) + n * log10(exp(1.0));

    return logNFA;
}

/*----------------------------------------------------------------------------*/
/* Main code */

int jpegq(double * input, double * image, double * Q, double * logNFA, int X, int Y, int C) {

    /* computed values */
    double *coeff;
    int N;
    double lnfa;
    int c;
    double q;
    /* double Q[64]; */
    /* double logNFA[64]; */
    int i,j;

    /* work on Y channel */
    rgb2luminance(input, image, X, Y, C);

    /* compute all DCT coefficients for all image blocks*/
    coeff = compute_dct_coefficients(image, X, Y, &N);

    /* estimate quantization matrix */
    /* loop on coefficients */
    for (c=0; c<64; c++) {
        Q[c] = -1.0;
        logNFA[c] = DBL_MAX;

        /* loop on quantization values */
        for (q=1.0; q<=255.0; q+=1.0) {
            lnfa = quantization_nfa(coeff,N,c,q);

            /* keep the best q value */
            if (lnfa < logNFA[c]) {
                logNFA[c] = lnfa;
                Q[c] = q;
            }
        }
    }

    /* print estimated quantization matrix */
    printf("estimated quantization matrix (-1 when not meaningful):\n");
    for (j=0; j<8; j++) {
        for (i=0; i<8; i++)
            printf("%3g ", logNFA[i+j*8] < 0.0 ? Q[i+j*8] : -1 );
        printf("\n");
    }

    /* print the associated NFA values */
    printf("\nassociated log10(NFA) values:\n");
    for (j=0; j<8; j++) {
        for(i=0; i<8; i++)
            printf("%9.1f ", logNFA[i+j*8]);
        printf("\n");
    }

    /* free memory */
    free(coeff);

    return EXIT_SUCCESS;
}
