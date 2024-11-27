#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "IOput.h"

//void outputTimeseriesFromMemory( TimeseriesData *data )
//{
//  int i;
//  for( i=0; i<data->n_data; i++){
//    fwrite(&data->time[i], sizeof(double), 1, data->fp);
//    fwrite(&data->value[i], sizeof(double), 1, data->fp);
//  }
//  data->n_data = 0;
//}
//
//
//void StoreTimeseriesOnMemory( TimeseriesData *data, double time, double value )
//{
//  if( data->n_data == MAX_STORE_DAT ){
//    outputTimeseriesFromMemory( data );
//  } else {
//    data->time[data->n_data] = time;
//    data->value[data->n_data] = value;
//    data->n_data ++;
//  }
//}


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
