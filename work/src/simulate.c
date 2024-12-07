#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <omp.h>
#include "LIFneuron.h"
#include "TMsynapse.h"
#include "IOput.h"
#include "condition.h"

extern void timer_start( void );
extern double timer_elapsed( void );

void simulate( LIFneurons_t *pop, TMsynapses_t *syns, SpikeStore_t *spk, TimeseriesData_t *tmseries, double G_EXC, double G_INH )
{
  double time;
  double store_value[tmseries->num_vars];
  timer_start ();
  for( int t=0; t<NT; t++){
    time = t*DT;

    update_LIFneurons( pop );
    update_TMsynapses( syns, pop, G_EXC, G_INH );

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
  outputTimeseriesFromMemory( tmseries );
  double time_elapsed = timer_elapsed();
  printf("Time elapsed:%f sec ", time_elapsed);
}

int main( int argc, char *argv[] ){
  printf("debug:start1\n");
  omp_set_num_threads ( 12 );
  TMsynapses_t *synapses = calloc( NUM_NEURONS, sizeof(TMsynapses_t) );
  LIFneurons_t *neurons = calloc( 1, sizeof(LIFneurons_t) ); 
  SpikeStore_t *spk = (SpikeStore_t *) malloc (sizeof(SpikeStore_t));
  TimeseriesData_t *tmseries = (TimeseriesData_t *) malloc (sizeof(TimeseriesData_t));

  int32_t G_EXC_index = atoi(argv[1]);
  int32_t G_INH_index = atoi(argv[2]);
  double G_EXC = ( max_G_EXC / (num_G_EXC - 1 ) ) * G_EXC_index;
  double G_INH = ( max_G_INH / (num_G_INH - 1 ) ) * G_INH_index;

  init_TMsynapses( synapses );
  init_LIFneurons( neurons, G_EXC, G_INH );

  printf("debug:initialized2\n");

  char temp[64];
  sprintf(temp, "../data/%02d_%02d_spike.dat", G_EXC_index, G_INH_index);
  spk->fp = fopen(temp, "w");
  if( spk->fp == NULL ) printf("cannot open FIle\n");
  spk->spike_time = calloc( MAX_STORE_SPIKE, sizeof(double)  );
  spk->neuron     = calloc( MAX_STORE_SPIKE, sizeof(int32_t) );
  spk->num_spikes = 0;

  sprintf(temp, "../data/%02d_%02d_timeseries.bin", G_EXC_index, G_INH_index);
  tmseries->fp = fopen(temp, "wb");
  if( tmseries->fp == NULL ) printf("cannot open FIle\n");
  tmseries->num_vars = 6;
  tmseries->time  = calloc( MAX_STORE_DAT, sizeof(double));
  tmseries->value = calloc( tmseries->num_vars, sizeof(double*));
  for( int32_t i=0; i<tmseries->num_vars; i++){
    tmseries->value[i] = calloc( MAX_STORE_DAT, sizeof(double) );
  }
  tmseries->num_tmdata = 0;

  printf("debug:allocatedmemory for IOput\n");

  simulate( neurons, synapses, spk, tmseries, G_EXC, G_INH );

  free(synapses);
  free(neurons );
  printf("simulation ended(G_EXC:%f, G_INH:%f)\n", G_EXC, G_INH);
  return 0;
}
