# Tiny unlzma for embedded systems

Adaptation of BusyBox lzma decompressor for embedded, inflate directly from buffer to buffer.

Main goal is binary size.

## Modifications from busybox version

 - read and write directly into buffers, removed all file handling
 - handle files without compressed size, using a end marker. Can now inflate lzma1 files made with lzma from xz-utils
  - prefer stack variable for rc\_t

## Binary Size

- Observed binary sizes (without main and libs):
  - x86\_64: 1.982 bytes
  - armv7: 1.652 bytes
  - armv7 thumb: 1.132 bytes
  - mips: 2.176 bytes
  - mips16 1.296 bytes

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
