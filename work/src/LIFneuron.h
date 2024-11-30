#pragma once

typedef struct{
  int32_t num_neurons;
  double *v;
  double *g_exc;
  double *g_inh;
  double *I_stim;
  int32_t *spike;
  int32_t *refperiod;
}LIFneurons_t;

#define SEED ( 100 ) //pseudo-random seed value

#define DT  ( 0.01 ) // ms
#define N   ( 1000 ) // ms
#define NT  ( N/DT ) // 

#define NUM_NEURONS     ( NUM_EXC_NEURONS + NUM_INH_NEURONS )
//#define NUM_EXC_NEURONS ( 800 )
//#define NUM_INH_NEURONS ( 200 )
#define NUM_EXC_NEURONS ( 3200 )
#define NUM_INH_NEURONS ( 800 )

#define C_M  ( 198. )     // pF
#define E_L  ( -60. )     // mV
#define G_L  ( 9.99 )     // nS
#define E_EXC ( 0.0  )    // mV
#define E_INH ( -80. )    // mV
#define TAU_EXC ( 5. )    // ms
#define TAU_INH ( 10. )    // ms
//#define G_EXC ( 0.050 )      // nS
//#define G_INH ( 1.    )      // nS
#define V_RESET ( -60. ) // mV
#define V_THETA ( -50. ) // mV
#define TAU_REF ( 5.   ) // ms

void init_LIFneurons( LIFneurons_t *pop, double G_EXC, double G_INH );
void update_LIFneurons( LIFneurons_t *pop );
