#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "TMsynapse.h"
#include "IOput.h"

extern void timer_start( void );
extern void time_elapsed( void );

void simulate( LIFneurons_t *pop, TMsynapses_t *syns, SpikeStore_t *spk )
{
  char temp[64];
  sprintf(temp, "temp.dat");
  FILE *fp;
  fp = fopen(temp, "w");
  double time;
  for( int t=0; t<NT; t++){
    time = t*DT;
    fprintf(fp, "%f %f %f %f %f %f %f\n", time, pop->v[10], syns[10].r_s[syns[10].post_neuron[1]], syns[10].x_s[syns[10].post_neuron[1]], syns[10].u_s[syns[10].post_neuron[1]], pop->g_inh[10], pop->g_exc[10]);
    update_LIFneurons( pop );
    update_TMsynapses( syns, pop );
    StoreSpikeOnMemory(pop, spk, time);
  }
  outputSpikeFromMemory( spk );
}

int main( void ){
  TMsynapses_t *synapses = calloc( NUM_NEURONS, sizeof(TMsynapses_t) );
  LIFneurons_t *neurons = calloc( 1, sizeof(LIFneurons_t) ); 
  SpikeStore_t *spk = (SpikeStore_t *) malloc (sizeof(SpikeStore_t));

  init_TMsynapses( synapses );
  init_LIFneurons( neurons  );

  char temp[64];
  sprintf(temp, "spike.dat");
  spk->fp = fopen(temp, "w");
  spk->spike_time = calloc( MAX_STORE_SPIKE, sizeof(double)  );
  spk->neuron     = calloc( MAX_STORE_SPIKE, sizeof(int32_t) );
  spk->num_spikes = 0;

  simulate( neurons, synapses, spk );

  free(synapses);
  free(neurons );
  return 0;
}
