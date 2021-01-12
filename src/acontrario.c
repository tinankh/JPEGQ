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

#include "misc.h"

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
