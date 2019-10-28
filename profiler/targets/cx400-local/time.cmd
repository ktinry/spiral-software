#!/bin/sh

#  Copyright (c) 2018-2019, Carnegie Mellon University
#  See LICENSE for details

TEMPDIR=$PWD

make -R -C ../../targets/cx400-local GAP="$TEMPDIR/testcode.c" STUB="$TEMPDIR/testcode.h" CC="icc" CFLAGS="-O2 -Wall -fomit-frame-pointer -xCORE-AVX2 -std=c99" OUTDIR="$TEMPDIR" -s > time.txt
