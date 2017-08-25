----------------------------------------------------------------------
                   How to call FGb from C Code ?
----------------------------------------------------------------------

cd <...>/call_FGb/nv/maple/C 

# Preliminary step:
# a)  gmp.h must be part of the compilation paths
# if not you must copy it:
cp <....>/gmp.h ../../nv/int 
# (for instance: cp ~/nv/int/gmp/i686/gmp/gmp.h ../../nv/int)
#
# b) The gmp library must be available for the last step (link)
# edit the file Makefile and modify the line: GMP_STATIC_DIR:=/home2/jcf/nv/gmp/i686/gmp/.libs

# in the file Makefile adjust the variable

LIBDIR := macosx

or 

LIBDIR := x64

# Compilation
# You can can compile the demo program: several Groebner bases computations over a prime field or over the integers.
# edit the files  main.c gb1.c and gb2.c : some coments can be uselful.
#
make 

 # Run the program to compute a Groebner basis
 % ./main 1
 --------------------------------------------------
 --------------------   STEP 0 -------------------
 --------------------------------------------------
 ****************************** Compute gbasis

 INCREASE HEAP 1440096
 Set offset primes to 0/20000
 INCREASE HEAP 28941504
 Lin Bk ignored [NEW lib]/S:0 -> 13/[2](2x4)COMPACT_NEW_LINES=1 BACKWARD=1
 100%/[3](21x46)100%/[4](85x121)100%/[2](5x9)100%/[3](73x66)100%/[2](29x20)58.3%/100%/
 #C Dimension: -1, Degree: -1
 restore Z1 Copy 100.00 for 1/1 exposants
  {done}
 SWAP Z1/2 Memory usage (estimate):  0.000
 1 polys in gbasis
 [
 1]

 # Run the program to compute NormalForms:
 #  ./main 1 8 0 1

 --------------------------------------------------
 --------------------   STEP 0 -------------------
 --------------------------------------------------
 ****************************** Compute NF

 INCREASE HEAP 1440096
 Set offset primes to 0/20000
 INCREASE HEAP 28941504
 Lin Bk ignored [NEW lib]/S:0 -> 13/#C Second step time 0.01 sec
 restore Z1 Copy 100.00 for 10/10 exposants
  {done}
 SWAP Z1/2 Memory usage (estimate):  0.000
 4 polys in gbasis
 [
 1,x3*x4*x5 -x2*x4*x6,1,18*x4*x5-9*x5^2-18*x4*x6+9*x6^2-10*x2+10*x3]



----------------------------------------------------------------------
----------------------------------------------------------------------
----------------------------------------------------------------------
                        FAQ
----------------------------------------------------------------------
----------------------------------------------------------------------
----------------------------------------------------------------------
1) Linux only: it is also possible to compile in static mode (can be easier wrt the gmp lib):

make main.static

2) You can run the tests and compile the program by:

make test

----------------------------------------------------------------------
----------------------------------------------------------------------
----------------------------------------------------------------------

Changle Log:

2010-06-15: Initial Version
2010-09-15: Add comments
2010-09-17: Add function to access to internal representation of a multivariate polynomial
2010-09-19: Add example to remove verbose display.
2010-09-21: Link against one library: libcallfgbuni.a
2012-19-12: New Version (compatible with MacOS X, Lion)
2015-07-19: New version (compatible with MacOS X, Yosemite) + new simplifed interface
