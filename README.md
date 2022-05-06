JPEG_QT
=======

JPEG QUANTIZATION TABLE ESTIMATION WITH CONTROLLED FALSE DETECTIONS

by Rafael Grompone von Gioi <grompone@gmail.com>

and Tina Nikoukhah <tina.nikoukhah@gmail.com>


Introduction
------------

This program implements an a-contrario estimator of the JPEG quantization table.


Online Demo
------------

[IPOL](https://ipolcore.ipol.im/demo/clientApp/demo.html?id=399)


Requirements
------------

The following libraries are required for image input/output:

  - libpng
  - LibTIFF
  - libjpeg


Files
-----

- src/jpeg_qt.c and src/jpeg_qt.h: JPEG Q-table estimation algorithm.

- src/main.c: Main code: command line interface.

- README.md: this file.

- LICENSE: GNU AFFERO GENERAL PUBLIC LICENSE Version 3.

- Makefile: Compilation instructions.

- src/iio.c and src/iio.h: [iio](https://github.com/mnhrdt/iio) code and header.

- *.{png,jpg}: Test images.


Compiling
---------

The compiling instruction is
```bash
  make
```
from the directory where the Makefile is located.

To verify a correct compilation you can apply the algorithm on the test images
'roma.png' and 'roma95.jpg'. This can be done by executing:
```bash
  make test
```

This should print the following message:
```bash
test on roma.png
================
./jpeg_qt roma.png
estimated quantization matrix (- when not meaningful):
      -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -

associated log10(NFA) values:
                5.9       6.0       5.8       6.0       5.1       5.5       5.4
      5.9       6.0       6.0       6.0       6.0       6.0       6.0       6.0
      5.9       6.0       6.0       6.0       5.8       6.0       6.0       6.0
      5.9       6.0       5.7       6.0       6.0       6.0       6.0       6.0
      5.9       6.0       6.0       5.9       6.0       6.0       5.7       6.0
      5.7       6.0       6.0       6.0       5.7       6.0       6.0       6.0
      6.0       6.0       6.0       6.0       6.0       5.8       6.0       6.0
      6.0       5.7       6.0       5.4       6.0       5.5       6.0       6.0

test on roma95.jpg
==================
./jpeg_qt roma95.jpg
estimated quantization matrix (- when not meaningful):
      1   1   2   2   4   5   6
  1   1   1   2   3   6   6   6
  1   1   2   2   4   6   7   6
  1   2   2   3   5   9   8   6
  2   2   4   6   7  11  10   8
  2   4   6   6   8  10  11   9
  5   6   8   9  10  12  12  10
  7   9  10  10  11  10  10  10

associated log10(NFA) values:
              -15.8     -12.4    -636.0    -604.6    -845.0    -592.9    -400.0
    -13.5     -15.6     -10.8    -560.8    -793.6    -627.5    -453.6    -301.6
    -13.8     -12.1    -600.5    -536.3    -756.2    -537.6    -320.4    -270.3
    -14.9    -647.4    -574.6    -755.5    -623.2    -305.3    -212.7    -192.0
   -678.5    -595.5    -847.6    -630.5    -421.2    -174.1    -124.8     -94.4
   -600.6    -904.6    -675.5    -491.2    -274.8    -128.3     -59.8     -44.0
   -927.5    -664.1    -435.4    -227.0    -134.7     -42.1     -25.2     -22.4
   -627.5    -386.7    -241.3    -143.6     -69.2     -42.7     -14.4      -2.2
```

Running
-------

The program is executed as:
```bash
    jpeg_qt
```

(use ./jpeg_qt if the command is not included in the current path).
That should print the following usage:

```
  error: usage: jpeg_qt <image>
```

The command takes an input image as argument. Any image file format handled by
Enric Meinhardt-Llopis' IIO library can be used. This includes, for example,
PNG, JPG, TIFF, PPM, PGM.

A typical execution is as follows:
```
  ./jpeg_qt roma.png
```

Copyright and License
---------------------

Copyright (c) 2020-2022 Rafael Grompone von Gioi grompone@gmail.com

Copyright (c) 2020-2022 Tina Nikoukhah tina.nikoukhah@gmail.com

JPEGQ is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

JPEGQ is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GGNU Affero General Public
License for more details.

You should have received a copy of the GNU Affero General Public
License along with this program. If not, see
https://www.gnu.org/licenses/.

Thanks
------

We would be grateful to receive any comment, especially about errors, bugs,
or strange results.
