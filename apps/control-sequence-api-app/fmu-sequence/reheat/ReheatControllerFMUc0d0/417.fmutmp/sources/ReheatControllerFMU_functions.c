#include "omc_simulation_settings.h"
#include "ReheatControllerFMU_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "ReheatControllerFMU_includes.h"


DLLDirection
modelica_real omc_Buildings_Utilities_Math_Functions_round(threadData_t *threadData, modelica_real _x, modelica_integer _n)
{
  modelica_real _y;
  modelica_real _fac;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_real tmp9;
  modelica_boolean tmp10;
  modelica_real tmp11;
  _tailrecursive: OMC_LABEL_UNUSED
  // _y has no default value.
  tmp1 = 10.0;
  tmp2 = ((modelica_real)_n);
  if(tmp1 < 0.0 && tmp2 != 0.0)
  {
    tmp4 = modf(tmp2, &tmp5);
    
    if(tmp4 > 0.5)
    {
      tmp4 -= 1.0;
      tmp5 += 1.0;
    }
    else if(tmp4 < -0.5)
    {
      tmp4 += 1.0;
      tmp5 -= 1.0;
    }
    
    if(fabs(tmp4) < 1e-10)
      tmp3 = pow(tmp1, tmp5);
    else
    {
      tmp7 = modf(1.0/tmp2, &tmp6);
      if(tmp7 > 0.5)
      {
        tmp7 -= 1.0;
        tmp6 += 1.0;
      }
      else if(tmp7 < -0.5)
      {
        tmp7 += 1.0;
        tmp6 -= 1.0;
      }
      if(fabs(tmp7) < 1e-10 && ((unsigned long)tmp6 & 1))
      {
        tmp3 = -pow(-tmp1, tmp4)*pow(tmp1, tmp5);
      }
      else
      {
        throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp1, tmp2);
      }
    }
  }
  else
  {
    tmp3 = pow(tmp1, tmp2);
  }
  if(isnan(tmp3) || isinf(tmp3))
  {
    throwStreamPrint(threadData, "%s:%d: Invalid root: (%g)^(%g)", __FILE__, __LINE__, tmp1, tmp2);
  }
  _fac = tmp3;
  tmp10 = (modelica_boolean)(_x > 0.0);
  if(tmp10)
  {
    tmp8 = _fac;
    if (tmp8 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "floor(x * fac + 0.5) / fac");}
    tmp11 = (floor((_x) * (_fac) + 0.5)) / tmp8;
  }
  else
  {
    tmp9 = _fac;
    if (tmp9 == 0) {throwStreamPrint(threadData, "Division by zero %s in function context", "ceil(x * fac - 0.5) / fac");}
    tmp11 = (ceil((_x) * (_fac) - 0.5)) / tmp9;
  }
  _y = tmp11;
  _return: OMC_LABEL_UNUSED
  return _y;
}
modelica_metatype boxptr_Buildings_Utilities_Math_Functions_round(threadData_t *threadData, modelica_metatype _x, modelica_metatype _n)
{
  modelica_real tmp1;
  modelica_integer tmp2;
  modelica_real _y;
  modelica_metatype out_y;
  tmp1 = mmc_unbox_real(_x);
  tmp2 = mmc_unbox_integer(_n);
  _y = omc_Buildings_Utilities_Math_Functions_round(threadData, tmp1, tmp2);
  out_y = mmc_mk_rcon(_y);
  return out_y;
}

#ifdef __cplusplus
}
#endif
