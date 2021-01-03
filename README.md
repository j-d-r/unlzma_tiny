# Tiny unlzma for embedded systems

Adaptation of BusyBox lzma decompressor for embedded, inflate directly from buffer to buffer.

Main goal is binary size.

## Modifications from busybox version

 - read and write directly into buffers, removed all file handling
 - handle files without compressed size, using a end marker. Can now inflate lzma1 files made with lzma from xz-utils
 - prefer stack variable for rc\_t
 - reuse buffer\_end to handle truncated input

## Binary Size

- Observed binary sizes with GCC 10:
  - i686: 1.445 bytes
  - x86\_64: 1.545 bytes
  - armv7-a thumb: 1.128 bytes
  - armv7-a: 1.652 bytes
  - aarch64: 1.756 bytes
  - mips: 2.016 bytes
  - mips16 1.456 bytes

## Build

    mkdir obj
    cd obj
    make -f ../Makefile

## Contents

 - unlzma\_tiny.c: uncompressor base on busybox/archival/libarchive/decompress\_unlzma.c
 - unlzma\_tiny\_config.h: wrapper for base functions
 - unlzma.c: test program for debugging


## Credits

- BusyBox (https://busybox.net) (2006  Aurelien Jacobs)
- LZMA SDK 4.22 (http://www.7-zip.org/) (1999-2005  Igor Pavlov)
