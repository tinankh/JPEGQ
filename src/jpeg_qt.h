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

#ifndef JPEG_QT_H
#define JPEG_QT_H

void error(char * msg);

void * xcalloc(size_t n_items, size_t size);

void rgb2luminance(double * input, double * output, int X, int Y, int C);

double * compute_dct_coefficients(double * image, int X, int Y, int * N);

double quantization_nfa(double * coeff, int N, int c, double Q);

void jpeg_qt(double * image, int X, int Y, int C, double * Q, double * logNFA);

#endif
/*----------------------------------------------------------------------------*/
