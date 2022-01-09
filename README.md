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


## Update from BusyBox

This code was originally based on busybox commit [8f48fc0](https://git.busybox.net/busybox/commit/?h=1_29_stable&id=8f48fc01e9e43d16bf5860fa37252b43c76cb395) without keeping history.
A backup tag [unlzma_tiny-2021.01](https://github.com/j-d-r/unlzma_tiny/commit/3e911f553feac1c6b337cdfc685eee6472741ed2) to previous history was kept.

Further changes are merged from a filtered branch obtained with this script:

```bash
#!/bin/sh

set -e

REF=1_29_0

export FILTER_BRANCH_SQUELCH_WARNING=1

git fetch busybox -t -f
git checkout $REF -b busybox-filtered
git filter-branch -f --subdirectory-filter archival/ --prune-empty -- --all
git filter-branch -f --prune-empty --index-filter "git ls-files | grep -v 'decompress_unlzma.c' | xargs git rm --cached --ignore-unmatch"
git filter-branch -f --prune-empty --tree-filter "git ls-files | xargs -I '{}' git mv '{}' ./"
git fetch busybox -t -f
```

## Credits

- BusyBox (https://busybox.net) (2006  Aurelien Jacobs)
- LZMA SDK 4.22 (http://www.7-zip.org/) (1999-2005  Igor Pavlov)
