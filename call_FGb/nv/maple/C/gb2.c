/* 
 Jean-Charles Faugere (Jean-Charles.Faugere@inria.fr)
*/
/* Example: we compute a Groebner Basis modulo a small prime number */

/* The following macro should be 1 to call FGb modulo a prime number */
#define LIBMODE 1  
#define CALL_FGB_DO_NOT_DEFINE
#include "call_fgb.h"

#define FGb_MAXI_BASE 100000


void compute_prog2(int want_display)
{
  Dpol_INT input_basis[FGb_MAXI_BASE];
  Dpol_INT output_basis[FGb_MAXI_BASE];
  Dpol_INT prev;
  double t0;
  I32 m=0;
  const int nb_vars=5;
  char* vars[5]={"x1","x2","x3","x4","x5"}; /* name of the variables (can be anything) */

  FGB(saveptr)(); /* First thing to do : GMP origmal memory allocators are saved */
  init_FGb_Modp(65521); /* init FGb for modular computations */
  /* We compute in GF(65521)[x1,x2,x3,x4,x5] */

  FGB(PowerSet)(4,1,vars);  /* Define the monomial ordering: DRL(k1,k2) where 
			       k1 is the size of the 1st block of variables 
			       k2 is the size of the 2nd block of variables 
			       and vars is the list of variables
			    */
  threads_FGb(1);

  /* ================================================== */
  /* Creat the first polynomial  */
  prev=FGB(creat_poly)(4); /* number of monomials in the polynomial (here 4) */
  input_basis[m++]=prev;  /* fill the array of input polynomials with the first polynomial */
  /* Creat the first monomial  = coef * terme */
  {
    /* Creat the first term: power product x1^e[1]*...*xn^e[n] */
    I32 e[5]={0,1,1,0,0};  /* monomial: x2*x3 */
    FGB(set_expos2)(prev,0,e,nb_vars); /* arguments:
				    0: the first monomial
				    nb_vars: the number of variables
				  */
  }
  /* Creat the first coefficient (here 2) */
  FGB(set_coeff_I32)(prev,0,2); /* arguments:
				    0: the first coefficient
				    2: value of the coefficient (modulo the prime number)
				  */

  /* Creat the second term: power product x1^e[1]*...*xn^e[n] */
  {
    I32 e[5]={0,1,0,0,1}; /* x2*x5 */
    FGB(set_expos2)(prev,1,e,nb_vars);  /* second monomial */
  }
  FGB(set_coeff_I32)(prev,1,2); /* second coefficient */
  {
    I32 e[5]={1,0,0,1,0}; /* x1*x4 */
    FGB(set_expos2)(prev,2,e,nb_vars); /* third monomial */
  }
  FGB(set_coeff_I32)(prev,2,2); /* third coefficient */
  {
    I32 e[5]={0,0,0,1,0}; /* x4 */
    FGB(set_expos2)(prev,3,e,nb_vars); /* fourth monomial */
  }
  FGB(set_coeff_I32)(prev,3,65520); /* fourth coefficient */

  FGB(full_sort_poly2)(prev); /* it is recommended to sort each polynomial */

  /* We creat the second polynomial */
  prev=FGB(creat_poly)(5);
  input_basis[m++]=prev;
  {
    I32 e[5]={0,1,1,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,2);
  {
    I32 e[5]={0,1,0,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,65520);
  {
    I32 e[5]={0,0,0,1,1};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,1,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={1,1,0,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  FGB(full_sort_poly2)(prev);


  /* We creat the third polynomial */
  prev=FGB(creat_poly)(5);
  input_basis[m++]=prev;
  {
    I32 e[5]={0,2,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,1);
  {
    I32 e[5]={1,0,1,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,2);
  {
    I32 e[5]={0,1,0,1,0};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,0,1};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,0,1,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,65520);
  FGB(full_sort_poly2)(prev);

  /* We creat the 4th polynomial */
  prev=FGB(creat_poly)(6);
  input_basis[m++]=prev;
  {
    I32 e[5]={0,0,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,65520);
  {
    I32 e[5]={0,0,0,0,1};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,2);
  {
    I32 e[5]={0,0,0,1,0};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,1,0,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,1,0,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  {
    I32 e[5]={1,0,0,0,0};
    FGB(set_expos2)(prev,5,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,5,1);
  FGB(full_sort_poly2)(prev);

  /* We creat the 5th polynomial */
  prev=FGB(creat_poly)(6);
  input_basis[m++]=prev;
  {
    I32 e[5]={0,2,0,0,0};
    FGB(set_expos2)(prev,0,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,0,2);
  {
    I32 e[5]={1,0,0,0,0};
    FGB(set_expos2)(prev,1,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,1,65520);
  {
    I32 e[5]={0,0,0,0,2};
    FGB(set_expos2)(prev,2,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,2,2);
  {
    I32 e[5]={0,0,0,2,0};
    FGB(set_expos2)(prev,3,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,3,2);
  {
    I32 e[5]={0,0,2,0,0};
    FGB(set_expos2)(prev,4,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,4,2);
  {
    I32 e[5]={2,0,0,0,0};
    FGB(set_expos2)(prev,5,e,nb_vars);
  }
  FGB(set_coeff_I32)(prev,5,1);
  FGB(full_sort_poly2)(prev); /* sort the last polynomial according the selected monomial ordering */

  {
    int nb;
    const int n_input=5; /* we have 5 polynomials on input */
    SFGB_Options options;

    /* set default options (by default we compute a GB) */
    FGb_set_default_options(&options);

    /* overide some default parameters */
    options._env._force_elim=0; /* if force_elim=1 then return only the result of the elimination 
				    (need to define a monomial ordering DRL(k1,k2) with k2>0 ) */
    options._env._index=500000; /* This is is the maximal size of the matrices generated by F4 
				    you can increase this value according to your memory */

    options._verb=1; /* display useful infos during the computation */
    
    /* Other parameters :
       t0 is the CPU time (reference to a double)
    */
    nb=FGB(fgb)(input_basis,n_input,output_basis,FGb_MAXI_BASE,&t0,&options);
    /* The value nb returned by the library is the number of polynomials */

    /* The value nb returned by the library is the number of polynomials */
    if (want_display)
      {
	int i;
	fprintf(stderr,"[\n");
	for(i=0;i<nb;i++)
	  {
	    /* Import the internal representation of each polynomial computed by FGb */
	    {
	      const I32 nb_mons=FGB(nb_terms)(output_basis[i]); /* Number of Monomials */
	      UI32* Mons=(UI32*)(malloc(sizeof(UI32)*nb_vars*nb_mons));
	      I32* Cfs=(I32*)(malloc(sizeof(I32)*nb_mons));
	      int code=FGB(export_poly)(nb_vars,nb_mons,Mons,Cfs,output_basis[i]);
	      I32 j;
	      for(j=0;j<nb_mons;j++)
		{
		  
		  I32 k,is_one=1;
		  UI32* ei=Mons+j*nb_vars;
		  
		  if (j>0) fprintf(stderr,"+");
		  fprintf(stderr,"%d",Cfs[j]);

		  for(k=0;k<nb_vars;k++)
		    if (ei[k])
		      {
			if (ei[k] == 1)
			  fprintf(stderr,"*%s",vars[k]);
			else
			  fprintf(stderr,"*%s^%u",vars[k],ei[k]);
			is_one=0;
		      }
		  if (is_one)
		    fprintf(stderr,"*1");
		}
	      free(Cfs);
	      free(Mons);
	    }


	    if (i<(nb-1))
	      fprintf(stderr,",");
	    
	  }
	fprintf(stderr,"]\n");
      } 
  }
  FGB(reset_memory)(); /* to reset Memory */
  FGB(restoreptr)(); /* restore original GMP allocators */
}
