#include <stdlib.h>
#include "synapse.h"
#include "simulate_params.h"
#include "modifiedLiRinzel.h"
void initialize_syn( ptr_syn self )
{
  self->Y_S = 0.0;
}

void update_syn( ptr_syn self, int spike )
{
  if( spike == 1 ) self->Y_S += rho_c * Y_T;

  self->Y_S = self->Y_S - Omega_C * self->Y_S * DT;
}
