JPEGQ
=====

JPEG QUANTIZATION TABLE ESTIMATION WITH CONTROLLED FALSE DETECITIONS

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
estimated quantization matrix (-1 when not meaningful):
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1
 -1  -1  -1  -1  -1  -1  -1  -1

associated log10(NFA) values:
    458.6      38.7      12.7       7.9       4.3       3.3       3.7       3.6
     87.9      16.7       7.2       5.8       4.7       4.1       4.2       4.1
     34.3       8.3       4.2       4.3       4.0       4.2       4.0       4.2
     22.8       4.5       3.9       4.1       3.9       4.2       4.0       4.2
      5.2       4.1       4.2       4.1       4.1       4.1       3.9       4.2
      3.9       4.1       4.1       4.1       3.9       4.0       4.2       4.2
      4.2       4.2       4.2       4.4       4.1       4.0       4.5       4.7
      4.1       3.9       4.1       3.6       4.2       3.7       4.2       4.2

test on roma95.jpg
================
./jpegq roma95.jpg
estimated quantization matrix (-1 when not meaningful):
  2  -1  -1   2   2   4   5   6
 -1  -1  -1   2   3   6   6   6
 -1  -1   2   2   4   6   7   6
 -1   2   2   3   5   9   8   6
  2   2   4   6   7  11  10   8
  2   4   6   6   8  10  11   9
  5   6   8   9  10  12  12  10
  7   9  10  10  11  10  10  10

associated log10(NFA) values:
   -815.8      39.2      12.9    -637.8    -606.4    -846.8    -594.7    -401.8
     88.9      16.7       7.2    -562.6    -795.4    -629.3    -455.4    -303.4
     34.4       9.1    -602.3    -538.1    -758.0    -539.4    -322.2    -272.1
     22.5    -649.2    -576.4    -757.3    -625.0    -307.1    -214.5    -193.8
   -680.3    -597.3    -849.4    -632.3    -423.0    -175.9    -126.6     -96.2
   -602.4    -906.4    -677.3    -493.0    -276.6    -130.1     -61.6     -45.8
   -929.3    -665.9    -437.2    -228.8    -136.5     -43.9     -27.0     -24.2
   -629.3    -388.5    -243.1    -145.4     -71.0     -44.5     -16.2      -4.0
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

Copyright (c) 2020 Rafael Grompone von Gioi grompone@gmail.com

Copyright (c) 2020 Tina Nikoukhah tina.nikoukhah@gmail.com

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
