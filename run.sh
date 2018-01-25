#!/bin/sh

EXEC=test-mergesort

SRC=mergesort.c

if [ -e $EXEC ]; then rm $EXEC; fi;

gcc -o $EXEC $SRC

./$EXEC
