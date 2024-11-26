#pragma once
#include "LIFneuron.h"
typedef struct{
  int32_t num_post_neurons;
  int32_t *post_neuron;
  double *u_s;
  double *x_s;
  double *r_s;
}TMsynapses_t;

#define EXC_CONNECTION_PROB ( 0.05 )
#define INH_CONNECTION_PROB ( 0.2  )

#define OMEGA_D   ( 2.   )  //
#define OMEGA_F   ( 3.33 )  //
#define U_0__STAR ( 0.6  )  //
#define Y_T       ( 500  )  //
#define RHO_C     ( 0.005)  //
#define OMEGA_C   ( 40   )  //

void init_TMsynapses( TMsynapses_t *synapses );
void update_TMsynapses( TMsynapses_t *syns, LIFneurons_t *pop );
