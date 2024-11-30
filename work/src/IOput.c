#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "IOput.h"

void outputTimeseriesFromMemory( TimeseriesData_t *data )
{
  for( int32_t t=0; t<data->num_tmdata; t++){
    fwrite(&data->time[t], sizeof(double), 1, data->fp);
    for( int32_t i=0; i<data->num_vars; i++){
      fwrite(&data->value[i][t], sizeof(double), 1, data->fp);
    }
  }
  data->num_tmdata = 0;
}


void StoreTimeseriesOnMemory( TimeseriesData_t *data, double time, double *value )
{
  if( data->num_tmdata == MAX_STORE_DAT ){
    outputTimeseriesFromMemory( data );
  } else {
    data->time[data->num_tmdata] = time;
    for( int32_t i=0; i<data->num_vars; i++){
      data->value[i][data->num_tmdata] = value[i];
    }
    data->num_tmdata ++;
  }
}


void outputSpikeFromMemory ( SpikeStore_t *spk )
{
  int i;
  for ( i = 0; i < spk -> num_spikes; i++){
    fprintf ( spk->fp, "%f %d\n", spk->spike_time[i], spk->neuron[i]);
  }
  spk->num_spikes = 0;
}


void StoreSpikeOnMemory( LIFneurons_t *pop, SpikeStore_t *spk, double time )
{
  for ( int32_t i = 0; i < pop->num_neurons; i++ ){
    if (pop->spike[i] != 0){
      if(spk->num_spikes == MAX_STORE_SPIKE){
        outputSpikeFromMemory( spk );
      }
      spk -> neuron[spk->num_spikes] = i;
      spk -> spike_time[spk->num_spikes] = time;
      spk -> num_spikes++;
    }
  }
}
