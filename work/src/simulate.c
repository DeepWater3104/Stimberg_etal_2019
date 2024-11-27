#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "TMsynapse.h"
#include "IOput.h"

extern void timer_start( void );
extern void time_elapsed( void );

void simulate( LIFneurons_t *pop, TMsynapses_t *syn, SpikeStore_t *spk )
{
  double time;
  for( int t=0; t<NT; t++){
    time = t*DT;
    update_LIFneurons( pop );
    update_TMsynapses( syn, pop );
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
