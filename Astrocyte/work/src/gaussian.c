#include <math.h>
#include <SFMT.h>
#include <math.h>

void box_muller( double *u ){
  u[0] = sqrt(-2 * log(u[0])) * cos(2 * M_PI * u[1]);
  u[1] = sqrt(-2 * log(u[0])) * sin(2 * M_PI * u[1]);
}

double stdgaussian( sfmt_t* prng1, sfmt_t* prng2 ){
  double u1 = sfmt_genrand_real2( prng1 );
  double u2 = sfmt_genrand_real2( prng2 );
  double array[2] = {u1, u2};

  box_muller( array );
  double var = array[0];
  return var;
}
