#include <stdlib.h>
#include <stdio.h>
#include <SFMT.h>
#include "LIFneuron.h"
#include "TMsynapse.h"


void init_LIFneurons( LIFneurons_t *pop )
{
  pop->num_neurons = NUM_NEURONS;
  pop->v         = calloc( NUM_NEURONS, sizeof(double ) );
  pop->g_ex      = calloc( NUM_NEURONS, sizeof(double ) );
  pop->g_in      = calloc( NUM_NEURONS, sizeof(double ) );
  pop->I_stim    = calloc( NUM_NEURONS, sizeof(double ) );
  pop->spike     = calloc( NUM_NEURONS, sizeof(int32_t) );
  pop->refperiod = calloc( NUM_NEURONS, sizeof(int32_t) );

  sfmt_t prng;
  sfmt_init_gen_rand(&prng, SEED);
  for( int i=0; i<NUM_NEURONS; i++){
    pop->v[i] = E_L + sfmt_genrand_real2( &prng )*(V_THETA - E_L);
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_ex[i] = sfmt_genrand_real2( &prng ) * G_EX;
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_in[i] = sfmt_genrand_real2( &prng ) * G_IN;
  }
}


void update_LIFneurons( LIFneurons_t *pop )
{
  /* ODE */
  for( int i=0; i<pop->num_neurons; i++){
    pop->v[i] += DT*(G_L*( E_L - pop->v[i] ) + pop->g_ex[i]*( E_EX - pop->v[i] ) + pop->g_in[i]*( E_IN - pop->v[i] ) + pop->I_stim[i]) / C_M;
  }
  /* spike detection */
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
  for( int i=0; i<pop->num_neurons; i++){
    if( pop->refperiod[i] != 0){
      pop->refperiod[i]--;
      pop->v[i] = V_RESET;
    }
  }

  for( int i=0; i<pop->num_neurons; i++){
    pop->g_ex[i] = DT*(-pop->g_ex[i]/TAU_EX);
  }
  for( int i=0; i<pop->num_neurons; i++){
    pop->g_in[i] = DT*(-pop->g_in[i]/TAU_IN);
  }

}
