#!/bin/sh

#  Copyright (c) 2018-2019, Carnegie Mellon University
#  See LICENSE for details

if [[ ! -f ../../targets/cx400-remote/cx_homedir.txt ]]; then
  ssh cx pwd > ../../targets/cx400-remote/cx_homedir.txt
fi

SPIRALREMOTE=_spiral-remote_
CX_HOMEDIR=$(cat ../../targets/cx400-remote/cx_homedir.txt)
DIRNAME=$(basename $PWD)
TEMPDIR=$CX_HOMEDIR/$SPIRALREMOTE/tempdirs/$DIRNAME

rsync -lprtvz -e ssh ../../ cx:$SPIRALREMOTE/

ssh cx << EOL
cd $TEMPDIR
cp -r ../../targets/cx400-remote ../../targets/cx400-remote-$DIRNAME
make -R -C ../../targets/cx400-remote-$DIRNAME GAP="$TEMPDIR/testcode.c" STUB="$TEMPDIR/testcode.h" CC="icc" CFLAGS="-O2 -Wall -fomit-frame-pointer -xCORE-AVX2 -std=c99" OUTDIR="$TEMPDIR" -s > time.txt
rm -r ../../targets/cx400-remote-$DIRNAME
EOL

scp cx:$TEMPDIR/time.txt .
ssh cx rm -rf $TEMPDIR
