#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "TMsynapse.h"
#include "IOput.h"

extern void timer_start( void );
extern void time_elapsed( void );

void simulate( LIFneurons_t *pop, TMsynapses_t *syns, SpikeStore_t *spk, TimeseriesData_t *tmseries )
{
  double time;
  double store_value[tmseries->num_vars];
  for( int t=0; t<NT; t++){
    time = t*DT;

    update_LIFneurons( pop );
    update_TMsynapses( syns, pop );

    StoreSpikeOnMemory(pop, spk, time);
    store_value[0] = pop->v[10];
    store_value[1] = syns[10].r_s[syns[10].post_neuron[1]];
    store_value[2] = syns[10].x_s[syns[10].post_neuron[1]];
    store_value[3] = syns[10].u_s[syns[10].post_neuron[1]];
    store_value[4] = pop->g_inh[10];
    store_value[5] = pop->g_exc[10];
    StoreTimeseriesOnMemory(tmseries, time, store_value);
  }
  outputSpikeFromMemory( spk );
}

int main( void ){
  TMsynapses_t *synapses = calloc( NUM_NEURONS, sizeof(TMsynapses_t) );
  LIFneurons_t *neurons = calloc( 1, sizeof(LIFneurons_t) ); 
  SpikeStore_t *spk = (SpikeStore_t *) malloc (sizeof(SpikeStore_t));
  TimeseriesData_t *tmseries = (TimeseriesData_t *) malloc (sizeof(TimeseriesData_t));

  init_TMsynapses( synapses );
  init_LIFneurons( neurons  );

  char temp[64];
  sprintf(temp, "spike.dat");
  spk->fp = fopen(temp, "w");
  spk->spike_time = calloc( MAX_STORE_SPIKE, sizeof(double)  );
  spk->neuron     = calloc( MAX_STORE_SPIKE, sizeof(int32_t) );
  spk->num_spikes = 0;

  sprintf(temp, "timeseries.bin");
  tmseries->fp = fopen(temp, "wb");
  tmseries->num_vars = 6;
  tmseries->time  = calloc( MAX_STORE_DAT, sizeof(double));
  tmseries->value = calloc( tmseries->num_vars, sizeof(double*));
  for( int32_t i=0; i<tmseries->num_vars; i++){
    tmseries->value[i] = calloc( MAX_STORE_DAT, sizeof(double) );
  }
  tmseries->num_tmdata = 0;

  simulate( neurons, synapses, spk, tmseries );

  free(synapses);
  free(neurons );
  return 0;
}
