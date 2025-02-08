#pragma once

#include <SFMT.h>

typedef struct modified_li_rinzel *ptr_mLR;
typedef struct modified_li_rinzel
{
  /* state variables */
  double Gamma_A;
  double I;
  double C;
  double h;

  /* stimulation */
  double I_bias;
  int isnoisy;
}modifiedLiRinzel;

/* Parameters */
/* Calcium-induced Ca^2+ release */
#define C_T     ( 2.0   ) // microM
#define rho_A   ( 0.18  ) // 
#define d1      ( 0.13  ) // microM
#define d2      ( 1.05  ) // microM
#define d3      ( 0.9434) // microM
#define d5      ( 0.08  ) // microM
#define O_2     ( 0.2   ) // microMs-1
#define Omega_C ( 6.0   ) // s-1
#define Omega_L ( 0.1   ) // s-1
#define O_P     ( 0.9   ) // microMs-1
#define K_P     ( 0.05  ) // microM

/* IP3 signaling */
#define O_beta      ( 5.0    ) // microMs-1
//#define O_delta     ( 0.6    ) // microMs-1
#define O_delta     ( 0.2    ) // microMs-1 // only for Fig. 18.2
#define kappa_delta ( 1.5    ) // microM
//#define K_delta     ( 0.1    ) // microM
#define K_delta     ( 0.3    ) // microM // only for Fig.18.2
#define O_3K        ( 4.5    ) // microMs-1
#define K_3K        ( 1.0    ) // microM
//#define K_D         ( 0.7    ) // microM
#define K_D         ( 0.5    ) // microM // only for Fig. 18.2
//#define Omega_5P    ( 0.05   ) // s-1
#define Omega_5P    ( 0.1   ) // s-1 // only for Fig. 18.2

/* metabotropic receptor kinetics */
#define O_N     ( 0.3 ) // microMs-1
#define Omega_N ( 0.5 ) // s-1
#define K_KC    ( 0.5 ) // microM
#define zeta    ( 10  ) // 

/* IP3 stimulation and diffusion */
//#define F_ex    ( 2.0    ) // microMs-1
#define F_ex    ( 0.09    ) // microMs-1 // only for Fig. 18.2
#define I_bias  ( 0.0    ) // microM
#define F       ( 0.09   ) // microMs-1
#define I_theta ( 0.3    ) // microM
#define omega_I ( 0.05   ) // microM

/* Gliotransmission */
#define C_theta ( 0.5     ) // microM
#define G_T     ( 200.0   ) // mM
#define Omega_A ( 0.6     ) // s-1
#define U_A     ( 0.6     ) // 
#define rho_e   ( 0.00065 ) // 
#define Omega_e ( 60.0    ) // s-1
#define alpha   ( 0.0     ) // 



void initialize_mLR( ptr_mLR self, const int isnoisy );
void update_mLR( ptr_mLR self, sfmt_t *prng1, sfmt_t *prng2, const double Y_s );
