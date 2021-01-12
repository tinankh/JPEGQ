/*----------------------------------------------------------------------------

  Copyright (c) 2020 Rafael Grompone von Gioi <grompone@gmail.com>
  Copyright (c) 2020 Tina Nikoukhah <tinanikoukhah@gmail.com>

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

#include "iio.h"
#include "acontrario.h"
#include "dctblocks.h"
#include "misc.h"

int main(int argc, char **argv) {

    /* read input */
    if (argc != 2) error("use: jpegq <image>");

    /* read input parameters */
    double *input = NULL;
    int X,Y,C;
    input = iio_read_image_double_split(argv[1], &X, &Y, &C);

    /* computed values */
    double *coeff;
    int N;
    double lnfa;
    int c;
    double q;
    double Q[64];
    double logNFA[64];
    int i,j;

    /* work on Y channel
     xcalloc initializes the data to zero */
    double *image = xcalloc(X*Y, sizeof(double)); // I
    rgb2y(input, image, X, Y, C);

    /* compute all DCT coefficients for all image blocks */
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
    free(input);
    free(image);
    free(coeff);

    return EXIT_SUCCESS;
}
