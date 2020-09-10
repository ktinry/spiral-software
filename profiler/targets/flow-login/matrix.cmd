#!/bin/sh

#  Copyright (c) 2018-2020, Carnegie Mellon University
#  See LICENSE for details

TEMPDIR=$PWD

# Use profiler target in parallel
cp -r ../../targets/flow-login ../../targets/flow-login-$$

make matrix -R -C ../../targets/flow-login-$$ GAP="$TEMPDIR/testcode.c" STUB="$TEMPDIR/testcode.h" CC="gcc" CFLAGS="-O2 -Wall -fomit-frame-pointer -march=native -std=c99" OUTDIR="$TEMPDIR" -s > matrix.txt

# Remove temporary directory
rm -rf ../../targets/flow-login-$$
