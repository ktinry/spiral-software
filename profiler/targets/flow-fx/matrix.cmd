#!/bin/sh

#  Copyright (c) 2018-2020, Carnegie Mellon University
#  See LICENSE for details

TEMPDIR=$PWD

# Use profiler target in parallel
cp -r ../../targets/flow-fx ../../targets/flow-fx-$$

make matrix -R -C ../../targets/flow-fx-$$ GAP="$TEMPDIR/testcode.c" STUB="$TEMPDIR/testcode.h" CC="fccpx" CFLAGS="-Kfast -std=gnu99" OUTDIR="$TEMPDIR" -s > matrix.txt

# Remove temporary directory
rm -rf ../../targets/flow-fx-$$
