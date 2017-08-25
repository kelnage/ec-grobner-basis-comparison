#!/bin/bash

SYSTEM=$1
OUTFILE=$2

egrep "[^][]" $SYSTEM | # remove opening and closing brackets
  sed 's/^\s*//' | # remove whitespace at the beginning of the line
  awk '{printf "%s%s", (prev~/,$/?RS:""), $0; prev=$0} END{print ""}' > $OUTFILE # join lines not ending with a comma
  
