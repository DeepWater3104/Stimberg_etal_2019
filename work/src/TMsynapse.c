#include <stdlib.h>
#include <SFMT.h>
#include <stdint.h>
#include "TMsynapse.h"
#include "LIFneuron.h"


void init_TMsynapses_statevars( TMsynapses_t *syns ){
  syns->u_s = calloc( syns->num_post_neurons, sizeof(double) );
  syns->x_s = calloc( syns->num_post_neurons, sizeof(double) );
  syns->r_s = calloc( syns->num_post_neurons, sizeof(double) );
  for( int32_t post_index=0; post_index<syns->num_post_neurons; post_index++ ){
    syns->x_s[post_index] = 1.;
    syns->u_s[post_index] = 0.;
  }
}


void make_connections( int32_t pre_neuron, int32_t *connections, TMsynapses_t *syns, sfmt_t *prng )
{
  double rand;
  for( int32_t post_neuron=0; post_neuron<NUM_NEURONS; post_neuron++){
    rand = sfmt_genrand_real2( prng );
    /* synapse from excitatory neurons */
    if( pre_neuron < NUM_EXC_NEURONS ){
      if( rand < EXC_CONNECTION_PROB ){
        connections[syns->num_post_neurons] = post_neuron;
        syns->num_post_neurons ++;
      }
    /* synapse from inhibitory neurons */
    }else{
      if( rand < INH_CONNECTION_PROB ){
        connections[syns->num_post_neurons] = post_neuron;
        syns->num_post_neurons ++;
      }
    }
  }
}


void optimize_connection_matrix( TMsynapses_t *syns, int32_t *connections )
{
  //printf("%d\n", syns[pre].num_post_neurons);
  syns->post_neuron = calloc( syns->num_post_neurons, sizeof(int32_t) );
  for( int32_t post_index=0; post_index<syns->num_post_neurons; post_index++){
    syns->post_neuron[post_index] = connections[post_index];
    post_index++;
  }
}

void init_TMsynapses( TMsynapses_t *syns )
{
  /* pseudo-number generator */
  sfmt_t prng;
  sfmt_init_gen_rand( &prng, SEED+1 );

  /* make random network */
  for( int32_t pre_neuron=0; pre_neuron<NUM_NEURONS; pre_neuron++){
    int32_t *connections = calloc( NUM_NEURONS, sizeof(int32_t) );
    make_connections( pre_neuron, connections, &syns[pre_neuron], &prng );
    optimize_connection_matrix( &syns[pre_neuron], connections );
    free(connections);
    init_TMsynapses_statevars( &syns[pre_neuron] );
  }
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
