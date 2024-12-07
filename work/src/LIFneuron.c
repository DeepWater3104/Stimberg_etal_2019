#include <stdlib.h>
#include <stdio.h>
#include <SFMT.h>
#include <omp.h>
#include "LIFneuron.h"
#include "TMsynapse.h"


void init_LIFneurons( LIFneurons_t *pop, double G_EXC, double G_INH )
{
  pop->num_neurons = NUM_NEURONS;
  pop->v         = calloc( NUM_NEURONS, sizeof(double ) );
  pop->g_exc     = calloc( NUM_NEURONS, sizeof(double ) );
  pop->g_inh     = calloc( NUM_NEURONS, sizeof(double ) );
  pop->I_stim    = calloc( NUM_NEURONS, sizeof(double ) );
  pop->spike     = calloc( NUM_NEURONS, sizeof(int32_t) );
  pop->refperiod = calloc( NUM_NEURONS, sizeof(int32_t) );

  sfmt_t prng;
  sfmt_init_gen_rand(&prng, SEED);
  for( int i=0; i<NUM_NEURONS; i++){
    pop->v[i] = E_L + sfmt_genrand_real2( &prng )*(V_THETA - E_L);
    pop->I_stim[i] = 150;
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_exc[i] = sfmt_genrand_real2( &prng ) * G_EXC;
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_inh[i] = sfmt_genrand_real2( &prng ) * G_INH;
  }
}


void update_LIFneurons( LIFneurons_t *pop )
{
  /* ODE */
  #pragma omp simd
  for( int32_t i=0; i<pop->num_neurons; i++){
    pop->v[i] += DT*(G_L*( E_L - pop->v[i] ) + pop->g_exc[i]*( E_EXC - pop->v[i] ) + pop->g_inh[i]*( E_INH - pop->v[i] ) + pop->I_stim[i]) / C_M;
  }
  #pragma omp simd
  for( int32_t i=0; i<pop->num_neurons; i++){
    pop->g_exc[i] += DT*(-pop->g_exc[i]/TAU_EXC);
  }
  #pragma omp simd
  for( int32_t i=0; i<pop->num_neurons; i++){
    pop->g_inh[i] += DT*(-pop->g_inh[i]/TAU_INH);
  }

  /* spike detection */
  #pragma omp parallel for
  for( int i=0; i<pop->num_neurons; i++){
    if( pop->v[i] > V_THETA ){
      pop->v[i]        = V_RESET;
      pop->spike[i]    = 1;
      pop->refperiod[i]= TAU_REF / DT;
    }else{
      pop->spike[i] = 0;
    }
  }

  /* refractory period */
  #pragma omp parallel for
  for( int i=0; i<pop->num_neurons; i++){
    if( pop->refperiod[i] != 0){
      pop->refperiod[i]--;
      pop->v[i] = V_RESET;
    }
  }
}
