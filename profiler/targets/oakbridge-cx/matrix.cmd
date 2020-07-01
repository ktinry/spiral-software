#!/bin/sh

#  Copyright (c) 2018-2020, Carnegie Mellon University
#  See LICENSE for details

TEMPDIR=$PWD

# to use a profiler target in parallel
cp -r ../../targets/oakbridge-cx ../../targets/oakbridge-cx-$$

make matrix -R -C ../../targets/oakbridge-cx-$$ GAP="$TEMPDIR/testcode.c" STUB="$TEMPDIR/testcode.h" CC="icc" CFLAGS="-O2 -Wall -fomit-frame-pointer -xCORE-AVX512 -std=c99" OUTDIR="$TEMPDIR" -s > matrix.txt

# remove temporary directory
rm -rf ../../targets/oakbridge-cx-$$
