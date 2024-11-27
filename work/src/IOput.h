#pragma once

#include "LIFneuron.h"

#define MAX_STORE_DAT ( 100 )
#define MAX_STORE_SPIKE ( 100 )

//typedef struct{
//  FILE *fp;
//  int n_data;
//  double *time;
//  double *value;
//}TimeseriesData_t;

typedef struct{
  FILE *fp;
  double *spike_time;
  int32_t *neuron;
  int32_t num_spikes;
}SpikeStore_t;


//void outputTimeseriesFromMemory( TimeseriesData *data );
//void StoreTimeseriesOnMemory( TimeseriesData *data, double time, double value );
void outputSpikeFromMemory ( SpikeStore_t *spk );
void StoreSpikeOnMemory( LIFneurons_t *pop, SpikeStore_t *spk, double time );
