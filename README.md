# Compare various implementations of Grobner basis computations

This repo is for comparing multiple different implementations of the Grobner basis calcuation, offered by various
packages such as FGb, magma, and Sage (not currently working).

## Usage

* Check magma is installed, along with a C compiler for FGb and it's dependencies (see call_FGb/README.txt)
* Edit constants.magma to control the size of the elliptic curve and the parameters
* Execute a run with the following command:

  ./run

* This will put all the results in a subfolder of runs/ with the timestamp it started in the folder name
* It will also create a symbolic link called last_run to the last run folder
