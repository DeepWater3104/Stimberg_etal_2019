#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "LIFneuron.h"
#include "TMsynapse.h"

extern void timer_start( void );
extern void time_elapsed( void );

void simulate( LIFneurons_t *pop, TMsynapses_t *syn )
{
  char temp[64];
  sprintf(temp, "spike.dat");
  FILE *fp;
  fopen(fp, temp, "w");

  double time;
  for( int t=0; t<NT; t++){
    //fprintf(fp, "%f %f\n", time, pop->v[0]);
    time = t*DT;
    update_LIFneurons( pop );
    update_TMsynapses( syn, pop );
  }
  //fprintf(fp, "%f %f\n", time, pop->v[0]);
  //fclose(fp);
}

int main()
{
  TMsynapses_t *synapses = calloc( NUM_NEURONS, sizeof(TMsynapses_t) );
  LIFneurons_t *neurons = calloc( 1, sizeof(LIFneurons_t) ); 

  init_TMsynapses( synapses );
  init_LIFneurons( neurons  );

  simulate( neurons, synapses );

  free(synapses);
  free(neurons );
  return 0;
}
