#!/bin/bash

input=$1
iter=$2
RESULTS=$3

last_run=$(mktemp)

tail -n +$(grep -n 'Weil Descent attempt' $input | tail -1 | grep -o '^[0-9]\+') $input > $last_run

sed -n "s/Matrix size: \([0-9]\+\) by \([0-9]\+\)/\1,\2/p" $last_run > $RESULTS/magma_matrix_dims_$2.csv

grep -o "Total GroebnerBasis time: [0-9]\+.[0-9]\+" $last_run | grep -o "[0-9]\+.[0-9]\+$" | sed "s/\(.*\)/$iter,\1/" >> $RESULTS/magma_timing.csv

rm "$last_run"
