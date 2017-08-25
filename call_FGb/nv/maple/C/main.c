/* 
 Jean-Charles Faugere (Jean-Charles.Faugere@inria.fr)
*/
#include <stdio.h>
#include <stdlib.h>
#include "call_fgb_basic.h"

static void process_memory_state()
{
#if defined(linux) && 0
  {
    char name[500];
    fprintf(stderr,"#C\tSIZE\tRES\tSHAR\tTRS\tLRS\tDRS\tDT\n");
    sprintf(name,"/proc/%d/statm",getpid());
    {
      FILE* f=fopen(name,"r");
      UI32 size0,resident,share,trs,lrs,drs,dt;
      fscanf(f, "%d %d %d %d %d %d %d",
	     &size0, &resident, &share,
	     &trs, &lrs, &drs, &dt);
      fclose(f);
      fprintf(stderr,"#C\t%u\t%u\t%u\t%u\t%u\t%u\t%u\n",size0<<2,resident<<2,share<<2,trs<<2,lrs<<2,drs<<2,dt<<2);
    }
  }
#endif /*  defined(linux) && 0 */
}

/* First GB computation: demo1 over the integers */
extern void compute_prog1(int want_display,int want_nf);
/* Second GB computation: demo2 modp computations */
extern void compute_prog2(int want_display);

int main(int argc,char**argv)
{
  int k;
  if (argc>1)
    {
      const int kmax=1;
      int want_display=((argc>1) ? atoi(argv[1]) : 0);
      
      process_memory_state();

      if (want_display)
	fprintf(stderr,"Version FGb/int %d FGb/modp:%d\n",FGb_int_internal_version(),FGb_internal_version());
      for(k=0;k<kmax;k++)
	{
	  const int dsp=((k<kmax-1) ? 0 : want_display);
	  fprintf(stderr,"--------------------------------------------------\n");
	  fprintf(stderr,"--------------------   STEP %d -------------------\n",k);
	  fprintf(stderr,"--------------------------------------------------\n");
	  /* compute over the integers a NormalForm or a GroebnerBasis : see bug_prog1.c */
	  fprintf(stderr,"****************************** Compute gbasis over Q\n");
	  fflush(stderr);
	  compute_prog1(dsp,0);

	  if (0)
	    {
	      fprintf(stderr,"****************************** Compute NF\n");
	      fflush(stderr);
	      compute_prog1(dsp,1);
	    }
	  
	  process_memory_state();
	  
	  fprintf(stderr,"****************************** Compute gbasis mod p\n");
	  /* compute modulo a small prime number  < 2^16 : see bug_prog2.c */
	  compute_prog2(dsp);
	  process_memory_state();

	}
      exit(0);
    }
  else
    {
      fprintf(stderr,"Usage: %s  [<display> (1 to display the result)] [<step> (if no idea select -1)] [<block> (if no idea select 0)]\n",argv[0]);
      exit(0);
    }
}

