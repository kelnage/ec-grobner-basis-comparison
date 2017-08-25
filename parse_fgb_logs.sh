#!/bin/bash

logfile=$1
dimfile=$2
timingfile=$3

sed -n 's/[^)]*(\([0-9]\+\)x\([0-9]\+\))[^(]*/\1,\2\n/gp' $logfile | head -n -3 > $dimfile

grep -Ho "Elapsed time: \([0-9]\+.[0-9]\+\)s" $logfile | sed 's/^.*logs\/fgb_\([0-9]\+\).* \([0-9]\+.[0-9]\+\)s$/\1,\2/' >> $timingfile

