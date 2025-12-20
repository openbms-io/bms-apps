#ifndef ReheatControllerFMU__H
#define ReheatControllerFMU__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif


DLLDirection
modelica_real omc_Buildings_Utilities_Math_Functions_round(threadData_t *threadData, modelica_real _x, modelica_integer _n);
DLLDirection
modelica_metatype boxptr_Buildings_Utilities_Math_Functions_round(threadData_t *threadData, modelica_metatype _x, modelica_metatype _n);
static const MMC_DEFSTRUCTLIT(boxvar_lit_Buildings_Utilities_Math_Functions_round,2,0) {(void*) boxptr_Buildings_Utilities_Math_Functions_round,0}};
#define boxvar_Buildings_Utilities_Math_Functions_round MMC_REFSTRUCTLIT(boxvar_lit_Buildings_Utilities_Math_Functions_round)
#include "ReheatControllerFMU_model.h"


#ifdef __cplusplus
}
#endif
#endif

