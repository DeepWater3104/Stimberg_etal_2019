#include <stdlib.h>
#include <SFMT.h>
#include <stdint.h>
#include "TMsynapse.h"
#include "LIFneuron.h"


void init_TMsynapses_statevars( TMsynapses_t *syns ){
  for( int32_t pre=0; pre<NUM_NEURONS; pre++){
    syns[pre].u_s = calloc( syns[pre].num_post_neurons, sizeof(double) );
    syns[pre].x_s = calloc( syns[pre].num_post_neurons, sizeof(double) );
    syns[pre].r_s = calloc( syns[pre].num_post_neurons, sizeof(double) );
    for( int32_t post_index=0; post_index<syns[pre].num_post_neurons; post_index++ ){
      syns[pre].x_s[post_index] = 1.;
      syns[pre].u_s[post_index] = 0.;
    }
  }
}


void make_connections( int32_t *connections, int32_t *num_post_neurons, sfmt_t *prng )
{
  double rand;
  for( int32_t pre=0; pre<NUM_NEURONS; pre++){
    for( int32_t post=0; post<NUM_NEURONS; post++){
      rand = sfmt_genrand_real2( prng );
      /* synapse from excitatory neurons */
      if( pre < NUM_EXC_NEURONS ){
        if( rand < EXC_CONNECTION_PROB ){
          connections[pre*NUM_NEURONS+post] = 1;
          num_post_neurons[pre] ++;
        }
      /* synapse from inhibitory neurons */
      }else{
        if( rand < INH_CONNECTION_PROB ){
          connections[pre*NUM_NEURONS+post] = 1;
          num_post_neurons[pre] ++;
        }
      }
    }
  }
}


void optimize_connection_matrix( TMsynapses_t *syns, int32_t *connections, int32_t *num_post_neurons )
{
  for( int32_t pre=0; pre<NUM_NEURONS; pre++){
    syns[pre].num_post_neurons = num_post_neurons[pre];
    //printf("%d\n", syns[pre].num_post_neurons);
    syns[pre].post_neuron = calloc( num_post_neurons[pre], sizeof(int32_t) );
    int32_t post_index = 0;
    for( int32_t post=0; post<NUM_NEURONS; post++){
      if( connections[pre*NUM_NEURONS+post] == 1 ){
        syns[pre].post_neuron[post_index] = post;
        post_index++;
      }
    }
  }
}

void init_TMsynapses( TMsynapses_t *syns )
{
  /* allocate memory */
  int32_t *connections = calloc( NUM_NEURONS * NUM_NEURONS, sizeof(int32_t) );
  int32_t *num_post_neurons = calloc( NUM_NEURONS, sizeof(int32_t) );

  /* pseudo-number generator */
  sfmt_t prng;
  sfmt_init_gen_rand( &prng, SEED+1 );

  /* make random network */
  make_connections( connections, num_post_neurons, &prng );
  optimize_connection_matrix( syns, connections, num_post_neurons );
  /* free allocated memory */
  free(connections);
  free(num_post_neurons);

  init_TMsynapses_statevars( syns );
}

void update_TMsynapses( TMsynapses_t *syns, LIFneurons_t *pop, double G_EXC, double G_INH )
{
  for( int32_t pre=0; pre<NUM_NEURONS; pre++){
    for( int32_t post_index=0; post_index<syns[pre].num_post_neurons; post_index++){
      syns[pre].u_s[post_index] += DT*(-OMEGA_F*syns[pre].u_s[post_index]);
      syns[pre].x_s[post_index] += DT*(OMEGA_D*(1-syns[pre].x_s[post_index]));
      if( pop->spike[pre] == 1 ){
        syns[pre].u_s[post_index] += U_0__STAR*( 1 - syns[pre].u_s[post_index]);
        syns[pre].r_s[post_index]  = syns[pre].u_s[post_index]*syns[pre].x_s[post_index];
        syns[pre].x_s[post_index] -= syns[pre].r_s[post_index];
        if( pre < NUM_EXC_NEURONS ){
          pop->g_exc[syns[pre].post_neuron[post_index]] += syns[pre].r_s[post_index] * G_EXC;
        }else{
          pop->g_inh[syns[pre].post_neuron[post_index]] += syns[pre].r_s[post_index] * G_INH;
        }
      }
    }
  }
}
