#pragma once

typedef struct synapse *ptr_syn;
typedef struct synapse
{
  double Y_S;
}Synapse;

#define rho_c (0.001)
#define Y_T   ( 500000 )
void initialize_syn( ptr_syn self );
void update_syn( ptr_syn self, int spike );
