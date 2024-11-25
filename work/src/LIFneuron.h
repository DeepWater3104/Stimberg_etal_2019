typedef struct{
  int32_t num_neurons;
  double *v;
  double *g_ex;
  double *g_in;
  double *I_stim;
  int32_t *spike;
  int32_t *refperiod;
<<<<<<< HEAD
}LIFneurons_t;
=======
}LIFNeurons_t;
>>>>>>> f9543f998181f87e86f7bbe7c02612e3f1dd5b65

#define SEED ( 100 ) //pseudo-random seed value

#define DT  ( 0.01 ) // ms
#define N   ( 1000 ) // ms
#define NT  ( N/DT ) // 

#define C_M ( 198. )     // pF
#define E_L ( -60. )     // mV
#define G_L ( 9.99 )     // nS
#define E_EX ( 0.0  )    // mV
#define E_IN ( -80. )    // mV
#define TAU_EX ( 5. )    // ms
#define TAU_IN ( 10 )    // ms
#define G_EX ( 50000 )      // nS
#define G_IN ( 1.    )      // nS
#define V_RESET ( -60. ) // mV
#define V_THETA ( -50. ) // mV
#define TAU_REF ( 5.   ) // ms

#define NUM_NEURONS ( 1 )
