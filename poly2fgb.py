
import sys, re

if len(sys.argv) < 3:
    print "Usage: " + sys.argv[0] + " <polyfile> <constants>"
    sys.exit(2)

constants = re.match("p:=(?P<p>[0-9]+) N:=(?P<N>[0-9]+) n:=(?P<n>[0-9]+) m:=(?P<m>[0-9]+)", sys.argv[2])

nvars = int(constants.group("N"))
ni = int(constants.group("m"))
nj = nvars / ni

def x_ind(x):
    if len(x) != 4:
        raise Exception("Incorrect length of x: " + x)
    return (int(x[1]) - 1) * nj + int(x[3])

print """
#define LIBMODE 1
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"
#define FGb_MAXI_BASE 100000

void gb()
{
\tDpol input_basis[FGb_MAXI_BASE];
\tDpol output_basis[FGb_MAXI_BASE];
\tDpol prev;
\tdouble t0;
\tI32 m = 0;
"""

print "\tconst int nb_vars = " + str(nvars) + ";"
print "\tchar* vars[" + str(nvars) + "] = {";

for i in range(1, ni + 1):
    print "\t\t" + ", ".join(['"x' + str(i) + '_' + str(j) + '"' for j in xrange(1, nj + 1)]) + ("," if i < ni else "")

print """\t};

\tFGB(saveptr)();
\tthreads_FGb(8);
\tinit_FGb_Modp(2);
\t
\tFGB(PowerSet)(nb_vars,0,vars); // usual grevlex ordering

\t// ###### START POLYNOMIAL ######
"""

poly_count = 0

with open(sys.argv[1]) as poly:
    for line in poly:
        line = line.strip(" ,\t\r\n") # remove newlines, spaces and commas
        mons = re.split(' *\+ *', line) # line.split(" + ")
        print "\tprev = FGB(creat_poly)(" + str(len(mons)) + ");"
        print "\tinput_basis[m++]=prev;"
        for ind, mon in enumerate(mons):
            e = [0] * nvars;
            coeff = 1
            xs = mon.split("*")
            for x in xs:
                if x.startswith("x"):
                    power = 1
                    if "^" in x:
                        x, power = x.split("^")
                    e[x_ind(x) - 1] = power
                else:
                    coeff = int(x)
            print "\t// monomial " + mon
            print "\t{"
            print "\t\tI32 e[" + str(nvars) + "] = {" + ",".join([str(i) for i in e]) + "};"
            print "\t\tFGB(set_expos2)(prev, " + str(ind) + ", e, nb_vars);"
            print "\t}"
            print "\tFGB(set_coeff_I32)(prev, " + str(ind) + ", " + str(coeff) + ");"
        print "\tFGB(full_sort_poly2)(prev);"
        print ""
        poly_count += 1

print """
\t// ###### END POLYNOMIAL ######

\tint nb;"""
print "\tconst int n_input = " + str(poly_count) + ";"
print """\tSFGB_Options Opt;
\tFGB_Options options = &Opt;

\tFGb_set_default_options(options);
\toptions->_env._index = 5000000;
\toptions->_env._force_elim = 0;
\toptions->_verb = 1;

\tnb = FGB(fgb)(input_basis, n_input, output_basis, FGb_MAXI_BASE, &t0, options);

\tprintf("\\nTook %f\\n", t0);

\tprintf("===============\\nTHE RESULT\\n===============\\n\\n");

\tI32 i;
\tfor(i = 0; i < nb; i++)
\t{
\t\tconst I32 nb_mons = FGB(nb_terms)(output_basis[i]);
\t\tUI32* Mons = (UI32*)(malloc(sizeof(UI32)*nb_vars*nb_mons));
\t\tI32* Cfs = (I32*)(malloc(sizeof(I32)*nb_mons));
\t\tFGB(export_poly)(nb_vars, nb_mons, Mons, Cfs, output_basis[i]);
\t\tI32 j;

\t\tfor(j = 0; j < nb_mons; j++)
\t\t{
\t\t\tI32 k, is_one = 1;
\t\t\tUI32* ei = Mons + j * nb_vars;
\t\t\tif(j > 0) printf(" + ");
\t\t\tif(Cfs[j]) printf("%d", Cfs[j]);

\t\t\tfor(k = 0; k < nb_vars; k++)
\t\t\t{
\t\t\t\tif(ei[k] == 1) printf("*%s", vars[k]);
\t\t\t\tif(ei[k] > 1) printf("*%s^%u", vars[k], ei[k]);
\t\t\t}
\t\t}
\t\tprintf("\\n");
\t}

\tFGB(restoreptr)();
\tFGB(reset_memory)();
}

int main(int argc,char**argv)
{
\tgb();
}
"""
