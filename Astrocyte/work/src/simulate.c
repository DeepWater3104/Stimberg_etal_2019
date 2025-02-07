#include <stdio.h>
#include <stdlib.h>
#include <SFMT.h>
#include "modifiedLiRinzel.h"
#include "simulate_params.h"
#include "synapse.h"


int main()
{
  /* file for output */
  FILE *fp;
  char temp[64];
  sprintf(temp, "../data/output.dat");
  fp = fopen(temp, "w");
  if( fp == NULL ){
    printf("cannot open file\n");
  }

  modifiedLiRinzel *mLR = (modifiedLiRinzel *)calloc(2, sizeof(modifiedLiRinzel));
  Synapse *syn = (Synapse *)calloc(1, sizeof(Synapse));

  initialize_mLR( &mLR[0], 1);
  initialize_mLR( &mLR[1], 0);
  initialize_syn( &syn[0] );
  sfmt_t prng1, prng2;
  sfmt_init_gen_rand(&prng1, 1);
  sfmt_init_gen_rand(&prng2, 2);

  //for( int t=0; t<NT; t++ ){
  for( int t=0; t<NT; t++ ){
    for( int i=0; i<2; i++ ){
      update_mLR( &mLR[i], &prng1, &prng2, syn[0].Y_S );
    }
    int spike;
    if( t % 20000 == 0 ){
      spike = 1;
    }else{
      spike = 0;
    }
    update_syn( &syn[0], spike );
    fprintf(fp, " %f %f %f %f %f %f %f %f %f %f\n", t*DT, mLR[0].Gamma_A, mLR[1].Gamma_A, mLR[0].I, mLR[1].I, mLR[0].C, mLR[1].C, mLR[0].h, mLR[1].h, syn[0].Y_S);
  }

  fclose(fp);
  return 0;
}
