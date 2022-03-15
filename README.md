JPEGQ
=====

JPEG QUANTIZATION TABLE ESTIMATION WITH CONTROLLED FALSE DETECTIONS

by Rafael Grompone von Gioi <grompone@gmail.com>

and Tina Nikoukhah <tina.nikoukhah@gmail.com>


Introduction
------------

This program implements an a-contrario estimator of the JPEG quantization table.


Online Demo
------------

[IPOL](https://ipolcore.ipol.im/demo/clientApp/demo.html?id=77777000052)


Requirements
------------

The following libraries are required for image input/output:

  - libpng
  - LibTIFF
  - libjpeg


Files
-----

- src/jpegq.c: Main code.

- src/acontrario.c and src/acontrario.h: A contrario computation.

- src/dctblocks.c and src/dctblocks.h: DCT computation.

- src/misc.c and src/misc.h: Useful functions.

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
from the directory where the source codes and the Makefile are located.

To verify a correct compilation you can apply the algorithm to the test images
'pelican.png' and 'roma.png'. This can be done by executing:
```bash
  make test
```

This should print the following message:
```bash
test on roma.png
===================
./jpegq roma.png
estimated quantization matrix (- when not meaningful):
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -
  -   -   -   -   -   -   -   -

associated log10(NFA) values:
      -        40.5      14.5       9.7       6.1       5.1       5.5       5.4
     89.7      18.5       9.0       7.6       6.5       5.9       6.0       5.9
     36.1      10.1       6.0       6.1       5.8       6.0       5.8       6.0
     24.6       6.3       5.7       5.9       5.7       6.0       5.8       6.0
      7.0       5.9       6.0       5.9       5.9       5.9       5.7       6.0
      5.7       5.9       5.9       5.9       5.7       5.8       6.0       6.0
      6.0       6.0       6.0       6.2       5.9       5.8       6.3       6.5
      5.9       5.7       5.9       5.4       6.0       5.5       6.0       6.0

test on roma95.jpg
================
./jpegq roma95.jpg
estimated quantization matrix (- when not meaningful):
  -   -   -   2   2   4   5   6
  -   -   -   2   3   6   6   6
  -   -   2   2   4   6   7   6
  -   2   2   3   5   9   8   6
  2   2   4   6   7  11  10   8
  2   4   6   6   8  10  11   9
  5   6   8   9  10  12  12  10
  7   9  10  10  11  10  10  10

associated log10(NFA) values:
      -        41.0      14.7    -636.0    -604.6    -845.0    -592.9    -400.0
     90.7      18.5       9.0    -560.8    -793.6    -627.5    -453.6    -301.6
     36.2      10.9    -600.5    -536.3    -756.2    -537.6    -320.4    -270.3
     24.3    -647.4    -574.6    -755.5    -623.2    -305.3    -212.7    -192.0
   -678.5    -595.5    -847.6    -630.5    -421.2    -174.1    -124.8     -94.4
   -600.6    -904.6    -675.5    -491.2    -274.8    -128.3     -59.8     -44.0
   -927.5    -664.1    -435.4    -227.0    -134.7     -42.1     -25.2     -22.4
   -627.5    -386.7    -241.3    -143.6     -69.2     -42.7     -14.4      -2.2
```

Running
-------

The program is executed as:
```bash
    jpegq
```

(use ./god if the command is not included in the current path).
That should print the following usage:

```
  Error: use: jpegq <image>
```

The command takes an input image as argument. Any image file format handled by
Enric Meinhardt-Llopis' IIO library can be used. This includes, for example,
PNG, JPG, TIFF, PPM, PGM.

A typical execution is as follows:
```
  ./jpegq pelican.png
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
