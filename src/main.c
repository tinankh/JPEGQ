/*----------------------------------------------------------------------------

  Copyright (c) 2018-2021 Rafael Grompone von Gioi <grompone@gmail.com>
  Copyright (c) 2018-2021 Jérémy Anger <anger@cmla.ens-cachan.fr>
  Copyright (c) 2018-2021 Tina Nikoukhah <tinanikoukhah@gmail.com>

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
    double * input;
    double * image;
    double Q[64];
    double logNFA[64];
    int X, Y, C;

    if (argc != 2) error("use: jpegq <image>");

    input = iio_read_image_double_split(argv[1], &X, &Y, &C);

    /* luminance image */
    image = (double *) xcalloc(X*Y, sizeof(double));

    /* run algorithm */
    jpegq(input, image, Q, logNFA, X, Y, C);

    /* store vote map and forgery detection outputs */
    iio_write_image_double("luminance.png", image, X, Y);

    /* free memory */
    free((void *) input);
    free((void *) image);

    return EXIT_SUCCESS;
}
/* ---------------------------------------------------------------------------- */
