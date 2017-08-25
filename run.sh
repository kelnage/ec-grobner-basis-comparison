#!/bin/bash

# This script will execute a Magma script with a number of parameters, which will produce a system of polynomials and a
# Groebner basis for that system. Those systems will be fed into both FGb and Sage, where the same Groebner basis 
# should be computed. The output will be a series of measurements, detailing execution time and the sizes of matrices 
# used.

# Define the necessary file path constants
INPUT_CONSTANTS="constants.magma" # a file containing a series of system constants in the form "p:=W N:=X n:=Y m:=Z" newline separated
MAGMA_SCRIPT="WeilDescent.magma" # the Magma script that generates the polynomial system and Groebner basis

TIMESTAMP=$(date +%Y%m%d_%H%M%S)
RUNDIR="runs/run_$TIMESTAMP"
LOGS="$RUNDIR/logs"
SYSTEMS="$RUNDIR/systems"
CODE="$RUNDIR/code"
RESULTS="$RUNDIR/results"
mkdir -p $RUNDIR $CODE $LOGS $SYSTEMS $RESULTS 

if [ -L last_run ]; then
    rm last_run
fi
ln -sf $RUNDIR last_run

reps=3
iter=1

echo "Writing log to $RUNDIR/run.log"
while IFS='' read -r constants || [[ -n $constants ]]; do
    for i in $(seq $reps); do
        echo "Starting iteration $iter with constants $constants"
        echo "Running Magma"
        magma -b iter:=$iter $constants system_file:=$SYSTEMS/system_$iter.magma $MAGMA_SCRIPT &> $LOGS/magma_$iter.log
        if [ $? -ne 0 ]; then
            echo "Running magma with $constants failed - please check the error log in $LOGS/magma_$iter.log"
            exit 1
        fi
        echo "Magma finished"
        ./parse_magma_logs.sh $LOGS/magma_$iter.log $iter $RESULTS 
        # Convert Magma output into generic input for FGb and Sage
        ./magma2poly.sh $SYSTEMS/system_$iter.magma $SYSTEMS/system_$iter.poly
        # Run FGb over the same system
        python poly2fgb.py $SYSTEMS/system_$iter.poly "$constants" > $CODE/fgb_$iter.c
        gcc -m64 -I call_FGb/nv/maple/C -I call_FGb/nv/protocol -I call_FGb/nv/int -c $CODE/fgb_$iter.c -o $CODE/fgb_$iter.o
        g++ -m64 -L call_FGb/nv/maple/C/x64 -o $CODE/fgb_$iter $CODE/fgb_$iter.o call_FGb/nv/maple/C/gb1.o -lfgb -lfgbexp -lgb -lgbexp -lminpoly -lminpolyvgf -lgmp -lm -fopenmp
        echo "Running FGb"
        ./$CODE/fgb_$iter &> $LOGS/fgb_$iter.log
        if [ $? -ne 0 ]; then
            echo "Running FGb with $constants failed - please check the error log in $LOGS/fgb_$iter.log"
            exit 1
        fi
        echo "FGb finished"
        # Parse FGb logfiles
        ./parse_fgb_logs.sh $LOGS/fgb_$iter.log $RESULTS/fgb_matrix_dims_$iter.csv $RESULTS/fgb_timing.csv
        # Not currently working
        # Run Sage/Singular over the same system
        # ./poly2sage.sh system_$iter.poly > sage_$iter.sage
        # echo "Running Sage"
        # sage sage_$iter.sage > logs/sage_$iter.log
        # echo "Sage finished"
        let iter+=1
    done
done < $INPUT_CONSTANTS &> $RUNDIR/run.log

