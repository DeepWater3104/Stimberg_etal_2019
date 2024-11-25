#include <stdlib.h>
#include <stdio.h>
#include <SFMT.h>
#include "LIFneuron.h"


<<<<<<< HEAD
void init_LIFneurons( LIFneurons_t *pop, int32_t num_neurons )
=======
void init_LIFNeurons( LIFNeurons_t *pop, int32_t num_neurons )
>>>>>>> f9543f998181f87e86f7bbe7c02612e3f1dd5b65
{
  pop->num_neurons = num_neurons;
  pop->v         = calloc( sizeof(double ), num_neurons );
  pop->g_ex      = calloc( sizeof(double ), num_neurons );
  pop->g_in      = calloc( sizeof(double ), num_neurons );
  pop->I_stim    = calloc( sizeof(double ), num_neurons );
  pop->spike     = calloc( sizeof(int32_t), num_neurons );
  pop->refperiod = calloc( sizeof(int32_t), num_neurons );

  sfmt_t prng;
  sfmt_init_gen_rand(&prng, SEED);
  for( int i=0; i<NUM_NEURONS; i++){
    pop->v[i] = E_L + sfmt_genrand_real2( &prng )*(V_THETA - E_L);
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_ex[i] = sfmt_genrand_real2( &prng ) * G_EX;
  }
  for( int i=0; i<NUM_NEURONS; i++){
    pop->g_in[i] = sfmt_genrand_real2( &prng ) * G_IN;
  }
}


<<<<<<< HEAD
void update_LIFneurons( LIFneurons_t *pop )
=======
void update_LIFNeurons( LIFNeurons_t *pop )
>>>>>>> f9543f998181f87e86f7bbe7c02612e3f1dd5b65
{
  /* ODE */
  for( int i=0; i<pop->num_neurons; i++){
    pop->v[i] += DT*(G_L*( E_L - pop->v[i] ) + pop->g_ex[i]*( E_EX - pop->v[i] ) + pop->g_in[i]*( E_IN - pop->v[i] ) + pop->I_stim[i]) / C_M;
  }
  /* spike detection */
  for( int i=0; i<pop->num_neurons; i++){
    if( pop->v[i] > V_THETA ){
      pop->v[i]        = V_RESET;
      pop->spike[i]    = 1;
      pop->refperiod[i]= TAU_REF / DT;
    }else{
      pop->spike[i] = 0;
    }
  }
  /* refractory period */
  for( int i=0; i<pop->num_neurons; i++){
    if( pop->refperiod[i] != 0){
      pop->refperiod[i]--;
      pop->v[i] = V_RESET;
    }
  }

  for( int i=0; i<pop->num_neurons; i++){
    pop->g_ex[i] = DT*(-pop->g_ex[i]/TAU_EX);
  }
  for( int i=0; i<pop->num_neurons; i++){
    pop->g_in[i] = DT*(-pop->g_in[i]/TAU_IN);
  }

}


<<<<<<< HEAD
void simulate( LIFneurons_t *pop )
{
  //char temp[64];
  //FILE *fp;
  //sprintf(temp, "output.dat");
  //fp = fopen(temp, "w");

  double time;
  for( int t=0; t<NT; t++){
    //fprintf(fp, "%f %f\n", time, pop->v[0]);
    time = t*DT;
    update_LIFneurons( pop );
  }
  //fprintf(fp, "%f %f\n", time, pop->v[0]);
  //fclose(fp);
}

//int main()
//{
//  LIFneurons_t *single = calloc( sizeof(LIFneurons_t), NUM_NEURONS);
//  init_LIFneurons( single, NUM_NEURONS );
//
//  /* start simulation */
//  single->I_stim[0] = 200;
//  simulate( single );
//  return 0;
//}
=======
void simulate( LIFNeurons_t *pop )
{
  char temp[64];
  FILE *fp;
  sprintf(temp, "output.dat");
  fp = fopen(temp, "w");

  double time;
  for( int t=0; t<NT; t++){
    fprintf(fp, "%f %f\n", time, pop->v[0]);
    time = t*DT;
    update_LIFNeurons( pop );
  }
  fprintf(fp, "%f %f\n", time, pop->v[0]);
  fclose(fp);
}

int main()
{
  LIFNeurons_t *single = calloc( sizeof(LIFNeurons_t), NUM_NEURONS);
  init_LIFNeurons( single, NUM_NEURONS );

  /* start simulation */
  single->I_stim[0] = 200;
  simulate( single );


}
>>>>>>> f9543f998181f87e86f7bbe7c02612e3f1dd5b65
