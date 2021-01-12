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
#include <string.h>
#include <math.h>

#include "misc.h"

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
