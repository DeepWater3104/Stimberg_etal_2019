#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modifiedLiRinzel.h"
#include "simulate_params.h"
#include "gaussian.h"

/* general functions */
double Hill( const double x, const double K, const double n ){ return pow(x,n) / (pow(x, n) + pow(K, n));}
double sgn( const double x )
{
  if( x > 0 ){
    return 1;
  }else if( x < 0 ){
    return -1;
  }else{
    return 0;
  }
}

/* kinetics of gating variables */
double h_inf( const double C, const double I ){ return d2*(I+d1)/(d2*(I+d1)+(I+d3)*C); }
double tau_h( const double C, const double I ){ return (I+d3)/(O_2*d2*(I+d1)+O_2*(I+d3)*C); }
double m_inf( const double C, const double I ){ return Hill(C, d5, 1)*Hill(I, d1, 1); }

/* ODE */
double dCdt( const double C, const double h, const double I ) 
{ 
  return (Omega_C * pow(m_inf(C, I), 3) * pow(h, 3) ) * (C_T - (1+rho_A)*C) + // J_r
    Omega_L * (C_T - (1+rho_A) * C) - // J_l
    O_P * pow(C, 2) / (pow(C, 2) + pow(K_P, 2)); // J_p
}
void dhdt( const double h, const double C, const double I, const int isnoisy, double *dhdt_array, sfmt_t *prng1, sfmt_t *prng2 )
{
  double tau_h_temp = tau_h(C, I);
  double temp  = (h_inf(C, I)-h) / tau_h_temp;
  double xi = stdgaussian( prng1, prng2 ); /* gaussian white noise */
  dhdt_array[0] = temp;                        /* deterministic term */
  dhdt_array[1] = temp*isnoisy*xi*sqrt(tau_h_temp); /* stochastic    term */
  //printf("%f %f %f %f\n", dhdt_array[0], dhdt_array[1], sqrt(tau_h_temp), tau_h_temp);
}
double dIdt( const double I, const double Gamma_A, const double C )
{
  double Delta_I_bias = I - I_bias;
  return O_beta * Gamma_A + // J_beta
    O_delta * kappa_delta / (kappa_delta + I) * Hill(C, K_delta, 2) -// J_delta
    O_3K * Hill(C, K_D, 4) * Hill(I, K_3K, 1) -// J_3K
    Omega_5P * I + // J_5P
    (-1)*(F_ex/2)*(1+tanh((abs(Delta_I_bias) - I_theta)/omega_I))*sgn(Delta_I_bias); // J_ex
}

double dGamma_Adt( const double Gamma_A, const double C, const double Y_S )
{
  return O_N * Y_S * (1 - Gamma_A) - 
    Omega_N * (1 + zeta * Hill(C, K_KC, 1)) * Gamma_A;
}


void initialize_mLR( ptr_mLR self, const int isnoisy )
{
  /* initial values of state variables */
  self->C       = 0.0;
  self->I       = 0.0;
  self->Gamma_A = 0.0;
  self->h       = 0.9; // IP3Rs are initially mostly available for CICR

  /* simulation specific variables */
  self->isnoisy = isnoisy;
}

/* advance one time step */
void update_mLR( ptr_mLR self, sfmt_t *prng1, sfmt_t *prng2, const double Y_S )
{
  double dhdt_array[2];
  dhdt(self->h, self->C, self->I, self->isnoisy, dhdt_array, prng1, prng2 );

  /* euler-maruyama method */
  self->C       = self->C       + dCdt      (self->C, self->h, self->I)       * DT;
  self->I       = self->I       + dIdt      (self->I, self->Gamma_A, self->C) * DT;
  self->Gamma_A = self->Gamma_A + dGamma_Adt(self->Gamma_A, self->C, Y_S)     * DT;
  self->h       = self->h       + dhdt_array[0]                               * DT + dhdt_array[1] * sqrt(DT);
}
