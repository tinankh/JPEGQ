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
#include <string.h>

#include "iio.h"
#include "jpegq.h"

int main(int argc, char ** argv) {
    double * image;
    double Qtable[64];
    double logNFA[64];
    int X, Y, C;

    if (argc != 2) error("usage: jpegq <image>");

    image = iio_read_image_double_split(argv[1], &X, &Y, &C);

    /* run algorithm */
    jpegq(image, X, Y, C, Qtable, logNFA);

    /* print estimated quantization matrix */
    printf("estimated quantization matrix (- when not meaningful):\n");
    for (int j=0; j<8; j++) {
        for (int i=0; i<8; i++)
            if (i == 0 && j == 0) /* DC coefficient, not estimated */
                printf("  - ");
            else
                if (logNFA[i+j*8] < 0.0)
                    printf("%3g ", Qtable[i+j*8] );
                else
                    printf("  - ");
        printf("\n");
    }

    /* print the associated NFA values */
    printf("\nassociated log10(NFA) values:\n");
    for (int j=0; j<8; j++) {
        for(int i=0; i<8; i++)
            if (i == 0 && j == 0) /* DC coefficient, not estimated */
                printf("      -   ");
            else
                printf("%9.1f ", logNFA[i+j*8]);
        printf("\n");
    }

    /* free memory */
    free(image);

    return EXIT_SUCCESS;
}
/*----------------------------------------------------------------------------*/
