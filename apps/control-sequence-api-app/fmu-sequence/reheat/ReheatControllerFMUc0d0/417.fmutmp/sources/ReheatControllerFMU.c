/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "ReheatControllerFMU_model.h"
#include "simulation/solver/events.h"



/* dummy VARINFO and FILEINFO */
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int ReheatControllerFMU_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */) = data->simulationInfo->inputVars[0];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) = data->simulationInfo->inputVars[1];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) = data->simulationInfo->inputVars[2];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* TSup variable */) = data->simulationInfo->inputVars[3];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* TSupSet variable */) = data->simulationInfo->inputVars[4];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) = data->simulationInfo->inputVars[5];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) = data->simulationInfo->inputVars[6];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[142]] /* ppmCO2 variable */) = data->simulationInfo->inputVars[7];
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */) = data->simulationInfo->inputVars[8];

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[13].attribute.start;
  data->simulationInfo->inputVars[1] = data->modelData->realVarsData[14].attribute.start;
  data->simulationInfo->inputVars[2] = data->modelData->realVarsData[15].attribute.start;
  data->simulationInfo->inputVars[3] = data->modelData->realVarsData[16].attribute.start;
  data->simulationInfo->inputVars[4] = data->modelData->realVarsData[17].attribute.start;
  data->simulationInfo->inputVars[5] = data->modelData->realVarsData[18].attribute.start;
  data->simulationInfo->inputVars[6] = data->modelData->realVarsData[21].attribute.start;
  data->simulationInfo->inputVars[7] = data->modelData->realVarsData[142].attribute.start;
  data->simulationInfo->inputVars[8] = data->modelData->realVarsData[143].attribute.start;

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[13].attribute.start = data->simulationInfo->inputVars[0];
  data->modelData->realVarsData[14].attribute.start = data->simulationInfo->inputVars[1];
  data->modelData->realVarsData[15].attribute.start = data->simulationInfo->inputVars[2];
  data->modelData->realVarsData[16].attribute.start = data->simulationInfo->inputVars[3];
  data->modelData->realVarsData[17].attribute.start = data->simulationInfo->inputVars[4];
  data->modelData->realVarsData[18].attribute.start = data->simulationInfo->inputVars[5];
  data->modelData->realVarsData[21].attribute.start = data->simulationInfo->inputVars[6];
  data->modelData->realVarsData[142].attribute.start = data->simulationInfo->inputVars[7];
  data->modelData->realVarsData[143].attribute.start = data->simulationInfo->inputVars[8];

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[13].info.name;
  names[1] = (char *) data->modelData->realVarsData[14].info.name;
  names[2] = (char *) data->modelData->realVarsData[15].info.name;
  names[3] = (char *) data->modelData->realVarsData[16].info.name;
  names[4] = (char *) data->modelData->realVarsData[17].info.name;
  names[5] = (char *) data->modelData->realVarsData[18].info.name;
  names[6] = (char *) data->modelData->realVarsData[21].info.name;
  names[7] = (char *) data->modelData->integerVarsData[20].info.name;
  names[8] = (char *) data->modelData->integerVarsData[21].info.name;
  names[9] = (char *) data->modelData->realVarsData[142].info.name;
  names[10] = (char *) data->modelData->realVarsData[143].info.name;
  names[11] = (char *) data->modelData->booleanVarsData[221].info.name;
  names[12] = (char *) data->modelData->booleanVarsData[222].info.name;
  names[13] = (char *) data->modelData->booleanVarsData[223].info.name;
  names[14] = (char *) data->modelData->booleanVarsData[224].info.name;
  names[15] = (char *) data->modelData->booleanVarsData[225].info.name;
  names[16] = (char *) data->modelData->integerVarsData[37].info.name;

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH


  TRACE_POP
  return 0;
}

int ReheatControllerFMU_dataReconciliationUnmeasuredVariables(DATA *data, char ** names)
{
  TRACE_PUSH


  TRACE_POP
  return 0;
}

int ReheatControllerFMU_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* VAdjAreBreZon_flow variable */);
  data->simulationInfo->outputVars[1] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* VAdjPopBreZon_flow variable */);
  data->simulationInfo->outputVars[2] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* VMinOA_flow variable */);
  data->simulationInfo->outputVars[3] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */);
  data->simulationInfo->outputVars[4] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */);
  data->simulationInfo->outputVars[5] = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */);

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH


  TRACE_POP
  return 0;
}

int ReheatControllerFMU_setb_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH


  TRACE_POP
  return 0;
}


/*
equation index: 1181
type: SIMPLE_ASSIGN
ala.fanIni.u = u1Fan
*/
void ReheatControllerFMU_eqFunction_1181(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1181};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[93]] /* ala.fanIni.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */);
  TRACE_POP
}
/*
equation index: 1182
type: SIMPLE_ASSIGN
conLoo.conCoo.controlError.y = TCooSet - TZon
*/
void ReheatControllerFMU_eqFunction_1182(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1182};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[53]] /* conLoo.conCoo.controlError.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */);
  TRACE_POP
}
/*
equation index: 1183
type: SIMPLE_ASSIGN
conLoo.conHea.controlError.y = THeaSet - TZon
*/
void ReheatControllerFMU_eqFunction_1183(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1183};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[66]] /* conLoo.conHea.controlError.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */);
  TRACE_POP
}
/*
equation index: 1184
type: SIMPLE_ASSIGN
actAirSet.ifOcc.y = 1 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1184(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1184};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[75]] /* actAirSet.ifOcc.y DISCRETE */) = (((modelica_integer) 1) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1185
type: SIMPLE_ASSIGN
actAirSet.occModInd.y = if actAirSet.ifOcc.y then 1.0 else actAirSet.occModInd.realFalse
*/
void ReheatControllerFMU_eqFunction_1185(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1185};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* actAirSet.occModInd.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[75]] /* actAirSet.ifOcc.y DISCRETE */)?1.0:(data->simulationInfo->realParameter[34] /* actAirSet.occModInd.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1186
type: SIMPLE_ASSIGN
actAirSet.ifCooDow.y = 2 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1186(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1186};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[74]] /* actAirSet.ifCooDow.y DISCRETE */) = (((modelica_integer) 2) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1187
type: SIMPLE_ASSIGN
actAirSet.heaMaxFlo1.y = if actAirSet.ifCooDow.y then actAirSet.heaMaxFlo1.realTrue else actAirSet.heaMaxFlo1.realFalse
*/
void ReheatControllerFMU_eqFunction_1187(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1187};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[32]] /* actAirSet.heaMaxFlo1.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[74]] /* actAirSet.ifCooDow.y DISCRETE */)?(data->simulationInfo->realParameter[27] /* actAirSet.heaMaxFlo1.realTrue PARAM */):(data->simulationInfo->realParameter[26] /* actAirSet.heaMaxFlo1.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1188
type: SIMPLE_ASSIGN
actAirSet.heaMinFlo.y = if actAirSet.ifCooDow.y then actAirSet.heaMinFlo.realTrue else actAirSet.heaMinFlo.realFalse
*/
void ReheatControllerFMU_eqFunction_1188(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1188};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[33]] /* actAirSet.heaMinFlo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[74]] /* actAirSet.ifCooDow.y DISCRETE */)?(data->simulationInfo->realParameter[31] /* actAirSet.heaMinFlo.realTrue PARAM */):(data->simulationInfo->realParameter[30] /* actAirSet.heaMinFlo.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1189
type: SIMPLE_ASSIGN
actAirSet.or3.y = actAirSet.ifOcc.y or actAirSet.ifCooDow.y
*/
void ReheatControllerFMU_eqFunction_1189(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1189};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[81]] /* actAirSet.or3.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[75]] /* actAirSet.ifOcc.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[74]] /* actAirSet.ifCooDow.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1190
type: SIMPLE_ASSIGN
actAirSet.ifSetUp.y = 3 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1190(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1190};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[77]] /* actAirSet.ifSetUp.y DISCRETE */) = (((modelica_integer) 3) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1191
type: SIMPLE_ASSIGN
actAirSet.or1.y = actAirSet.or3.y or actAirSet.ifSetUp.y
*/
void ReheatControllerFMU_eqFunction_1191(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1191};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[79]] /* actAirSet.or1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[81]] /* actAirSet.or3.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[77]] /* actAirSet.ifSetUp.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1192
type: SIMPLE_ASSIGN
actAirSet.VActCooMax_flow = if actAirSet.or1.y then actAirSet.actCooMax.realTrue else actAirSet.actCooMax.realFalse
*/
void ReheatControllerFMU_eqFunction_1192(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1192};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* actAirSet.VActCooMax_flow variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[79]] /* actAirSet.or1.y DISCRETE */)?(data->simulationInfo->realParameter[19] /* actAirSet.actCooMax.realTrue PARAM */):(data->simulationInfo->realParameter[18] /* actAirSet.actCooMax.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1193
type: SIMPLE_ASSIGN
actAirSet.ifWarUp.y = 4 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1193(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1193};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[78]] /* actAirSet.ifWarUp.y DISCRETE */) = (((modelica_integer) 4) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1194
type: SIMPLE_ASSIGN
actAirSet.ifSetBac.y = 5 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1194(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1194};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[76]] /* actAirSet.ifSetBac.y DISCRETE */) = (((modelica_integer) 5) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1195
type: SIMPLE_ASSIGN
actAirSet.or2.y = actAirSet.ifWarUp.y or actAirSet.ifSetBac.y
*/
void ReheatControllerFMU_eqFunction_1195(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1195};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[80]] /* actAirSet.or2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[78]] /* actAirSet.ifWarUp.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[76]] /* actAirSet.ifSetBac.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1196
type: SIMPLE_ASSIGN
actAirSet.cooMaxFlo.y = if actAirSet.or2.y then actAirSet.cooMaxFlo.realTrue else actAirSet.cooMaxFlo.realFalse
*/
void ReheatControllerFMU_eqFunction_1196(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1196};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* actAirSet.cooMaxFlo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[80]] /* actAirSet.or2.y DISCRETE */)?(data->simulationInfo->realParameter[21] /* actAirSet.cooMaxFlo.realTrue PARAM */):(data->simulationInfo->realParameter[20] /* actAirSet.cooMaxFlo.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1197
type: SIMPLE_ASSIGN
actAirSet.add3.y = actAirSet.cooMaxFlo.y + actAirSet.heaMaxFlo1.y
*/
void ReheatControllerFMU_eqFunction_1197(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1197};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[29]] /* actAirSet.add3.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[30]] /* actAirSet.cooMaxFlo.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[32]] /* actAirSet.heaMaxFlo1.y variable */);
  TRACE_POP
}
/*
equation index: 1198
type: SIMPLE_ASSIGN
actAirSet.heaMaxFlo.y = if actAirSet.or2.y then actAirSet.heaMaxFlo.realTrue else actAirSet.heaMaxFlo.realFalse
*/
void ReheatControllerFMU_eqFunction_1198(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1198};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* actAirSet.heaMaxFlo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[80]] /* actAirSet.or2.y DISCRETE */)?(data->simulationInfo->realParameter[25] /* actAirSet.heaMaxFlo.realTrue PARAM */):(data->simulationInfo->realParameter[24] /* actAirSet.heaMaxFlo.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1199
type: SIMPLE_ASSIGN
actAirSet.add2.y = actAirSet.heaMinFlo.y + actAirSet.heaMaxFlo.y
*/
void ReheatControllerFMU_eqFunction_1199(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1199};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* actAirSet.add2.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[33]] /* actAirSet.heaMinFlo.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[31]] /* actAirSet.heaMaxFlo.y variable */);
  TRACE_POP
}
/*
equation index: 1200
type: SIMPLE_ASSIGN
sysReq.sub2.y = TZon - TCooSet
*/
void ReheatControllerFMU_eqFunction_1200(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1200};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */);
  TRACE_POP
}
/*
equation index: 1201
type: SIMPLE_ASSIGN
sysReq.greThr1.greHys.y = not pre(sysReq.greThr1.greHys.y) and sysReq.sub2.y > sysReq.greThr1.greHys.t or pre(sysReq.greThr1.greHys.y) and sysReq.sub2.y > sysReq.greThr1.greHys.t - 0.25
*/
void ReheatControllerFMU_eqFunction_1201(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1201};
  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  tmp1 = 1.0;
  tmp2 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */));
  relationhysteresis(data, &tmp0, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */), tmp1, tmp2, 69, Greater, GreaterZC);
  tmp4 = 1.0;
  tmp5 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */)) + 0.25;
  relationhysteresis(data, &tmp3, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */) - 0.25, tmp4, tmp5, 70, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */)) && tmp0) || ((data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */) && tmp3));
  TRACE_POP
}
/*
equation index: 1202
type: SIMPLE_ASSIGN
$whenCondition70 = sysReq.greThr1.greHys.y
*/
void ReheatControllerFMU_eqFunction_1202(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1202};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[67]] /* $whenCondition70 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1203
type: SIMPLE_ASSIGN
$whenCondition69 = not sysReq.greThr1.greHys.y
*/
void ReheatControllerFMU_eqFunction_1203(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1203};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[65]] /* $whenCondition69 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1204
type: SIMPLE_ASSIGN
sysReq.tim1.u = sysReq.greThr1.greHys.y
*/
void ReheatControllerFMU_eqFunction_1204(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1204};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[195]] /* sysReq.tim1.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1205
type: SIMPLE_ASSIGN
sysReq.sub3.y = TZon - TCooSet
*/
void ReheatControllerFMU_eqFunction_1205(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1205};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */);
  TRACE_POP
}
/*
equation index: 1206
type: SIMPLE_ASSIGN
sysReq.greThr2.greHys.y = not pre(sysReq.greThr2.greHys.y) and sysReq.sub3.y > sysReq.greThr2.greHys.t or pre(sysReq.greThr2.greHys.y) and sysReq.sub3.y > sysReq.greThr2.greHys.t - 0.25
*/
void ReheatControllerFMU_eqFunction_1206(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1206};
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  tmp7 = 1.0;
  tmp8 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */));
  relationhysteresis(data, &tmp6, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */), tmp7, tmp8, 67, Greater, GreaterZC);
  tmp10 = 1.0;
  tmp11 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */)) + 0.25;
  relationhysteresis(data, &tmp9, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */) - 0.25, tmp10, tmp11, 68, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */)) && tmp6) || ((data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */) && tmp9));
  TRACE_POP
}
/*
equation index: 1207
type: SIMPLE_ASSIGN
$whenCondition67 = sysReq.greThr2.greHys.y
*/
void ReheatControllerFMU_eqFunction_1207(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1207};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[63]] /* $whenCondition67 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1208
type: SIMPLE_ASSIGN
$whenCondition66 = not sysReq.greThr2.greHys.y
*/
void ReheatControllerFMU_eqFunction_1208(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1208};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[62]] /* $whenCondition66 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1209
type: SIMPLE_ASSIGN
sysReq.tim2.u = sysReq.greThr2.greHys.y
*/
void ReheatControllerFMU_eqFunction_1209(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1209};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[197]] /* sysReq.tim2.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1210
type: SIMPLE_ASSIGN
sysReq.addPar.y = TDis + sysReq.addPar.p
*/
void ReheatControllerFMU_eqFunction_1210(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1210};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) + (data->simulationInfo->realParameter[362] /* sysReq.addPar.p PARAM */);
  TRACE_POP
}
/*
equation index: 1211
type: SIMPLE_ASSIGN
sysReq.addPar1.y = TDis + sysReq.addPar1.p
*/
void ReheatControllerFMU_eqFunction_1211(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1211};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) + (data->simulationInfo->realParameter[363] /* sysReq.addPar1.p PARAM */);
  TRACE_POP
}
/*
equation index: 1212
type: SIMPLE_ASSIGN
$whenCondition55 = sample(1, sysReq.sampler.t0, sysReq.sampler.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1212(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1212};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* $whenCondition55 DISCRETE */) = data->simulationInfo->samples[0];
  TRACE_POP
}
/*
equation index: 1213
type: WHEN

when {$whenCondition55} then
  sysReq.sampler.firstTrigger = time <= sysReq.sampler.t0 + 0.5 * sysReq.sampler.samplePeriod;
end when;
*/
void ReheatControllerFMU_eqFunction_1213(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1213};
  modelica_boolean tmp12;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* $whenCondition55 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[50] /* $whenCondition55 DISCRETE */) /* edge */))
  {
    tmp12 = LessEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[411] /* sysReq.sampler.t0 PARAM */) + (0.5) * ((data->simulationInfo->realParameter[410] /* sysReq.sampler.samplePeriod PARAM */)));
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[187]] /* sysReq.sampler.firstTrigger DISCRETE */) = tmp12;
  }
  TRACE_POP
}
/*
equation index: 1214
type: SIMPLE_ASSIGN
sysReq.sampler.sampleTrigger = $whenCondition55
*/
void ReheatControllerFMU_eqFunction_1214(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1214};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[188]] /* sysReq.sampler.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* $whenCondition55 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1215
type: SIMPLE_ASSIGN
$whenCondition54 = sample(2, sysReq.sampler1.t0, sysReq.sampler1.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1215(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1215};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[49]] /* $whenCondition54 DISCRETE */) = data->simulationInfo->samples[1];
  TRACE_POP
}
/*
equation index: 1216
type: WHEN

when {$whenCondition54} then
  sysReq.sampler1.firstTrigger = time <= sysReq.sampler1.t0 + 0.5 * sysReq.sampler1.samplePeriod;
end when;
*/
void ReheatControllerFMU_eqFunction_1216(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1216};
  modelica_boolean tmp13;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[49]] /* $whenCondition54 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[49] /* $whenCondition54 DISCRETE */) /* edge */))
  {
    tmp13 = LessEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[413] /* sysReq.sampler1.t0 PARAM */) + (0.5) * ((data->simulationInfo->realParameter[412] /* sysReq.sampler1.samplePeriod PARAM */)));
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[189]] /* sysReq.sampler1.firstTrigger DISCRETE */) = tmp13;
  }
  TRACE_POP
}
/*
equation index: 1217
type: SIMPLE_ASSIGN
sysReq.sampler1.sampleTrigger = $whenCondition54
*/
void ReheatControllerFMU_eqFunction_1217(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1217};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[190]] /* sysReq.sampler1.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[49]] /* $whenCondition54 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1218
type: SIMPLE_ASSIGN
$whenCondition53 = sample(3, sysReq.sampler2.t0, sysReq.sampler2.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1218(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1218};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[48]] /* $whenCondition53 DISCRETE */) = data->simulationInfo->samples[2];
  TRACE_POP
}
/*
equation index: 1219
type: WHEN

when {$whenCondition53} then
  sysReq.sampler2.y = VDis_flow;
end when;
*/
void ReheatControllerFMU_eqFunction_1219(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1219};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[48]] /* $whenCondition53 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[48] /* $whenCondition53 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */);
  }
  TRACE_POP
}
/*
equation index: 1220
type: WHEN

when {$whenCondition53} then
  sysReq.sampler2.firstTrigger = time <= sysReq.sampler2.t0 + 0.5 * sysReq.sampler2.samplePeriod;
end when;
*/
void ReheatControllerFMU_eqFunction_1220(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1220};
  modelica_boolean tmp14;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[48]] /* $whenCondition53 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[48] /* $whenCondition53 DISCRETE */) /* edge */))
  {
    tmp14 = LessEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[415] /* sysReq.sampler2.t0 PARAM */) + (0.5) * ((data->simulationInfo->realParameter[414] /* sysReq.sampler2.samplePeriod PARAM */)));
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[191]] /* sysReq.sampler2.firstTrigger DISCRETE */) = tmp14;
  }
  TRACE_POP
}
/*
equation index: 1221
type: SIMPLE_ASSIGN
sysReq.sampler2.sampleTrigger = $whenCondition53
*/
void ReheatControllerFMU_eqFunction_1221(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1221};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[192]] /* sysReq.sampler2.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[48]] /* $whenCondition53 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1222
type: SIMPLE_ASSIGN
$whenCondition52 = sample(4, sysReq.sampler3.t0, sysReq.sampler3.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1222(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1222};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[47]] /* $whenCondition52 DISCRETE */) = data->simulationInfo->samples[3];
  TRACE_POP
}
/*
equation index: 1223
type: WHEN

when {$whenCondition52} then
  sysReq.sampler3.firstTrigger = time <= sysReq.sampler3.t0 + 0.5 * sysReq.sampler3.samplePeriod;
end when;
*/
void ReheatControllerFMU_eqFunction_1223(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1223};
  modelica_boolean tmp15;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[47]] /* $whenCondition52 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[47] /* $whenCondition52 DISCRETE */) /* edge */))
  {
    tmp15 = LessEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[417] /* sysReq.sampler3.t0 PARAM */) + (0.5) * ((data->simulationInfo->realParameter[416] /* sysReq.sampler3.samplePeriod PARAM */)));
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[193]] /* sysReq.sampler3.firstTrigger DISCRETE */) = tmp15;
  }
  TRACE_POP
}
/*
equation index: 1224
type: SIMPLE_ASSIGN
sysReq.sampler3.sampleTrigger = $whenCondition52
*/
void ReheatControllerFMU_eqFunction_1224(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1224};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[194]] /* sysReq.sampler3.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[47]] /* $whenCondition52 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1225
type: SIMPLE_ASSIGN
conLoo.conCoo.errP.u1 = conLoo.conCoo.uS_revAct.k * TCooSet
*/
void ReheatControllerFMU_eqFunction_1225(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1225};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[55]] /* conLoo.conCoo.errP.u1 variable */) = ((data->simulationInfo->realParameter[133] /* conLoo.conCoo.uS_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */));
  TRACE_POP
}
/*
equation index: 1226
type: SIMPLE_ASSIGN
conLoo.conCoo.uMea_revAct.y = conLoo.conCoo.uMea_revAct.k * TZon
*/
void ReheatControllerFMU_eqFunction_1226(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1226};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[56]] /* conLoo.conCoo.uMea_revAct.y variable */) = ((data->simulationInfo->realParameter[132] /* conLoo.conCoo.uMea_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */));
  TRACE_POP
}
/*
equation index: 1227
type: SIMPLE_ASSIGN
conLoo.conCoo.errI1.y = conLoo.conCoo.errP.u1 - conLoo.conCoo.uMea_revAct.y
*/
void ReheatControllerFMU_eqFunction_1227(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1227};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[54]] /* conLoo.conCoo.errI1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[55]] /* conLoo.conCoo.errP.u1 variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[56]] /* conLoo.conCoo.uMea_revAct.y variable */);
  TRACE_POP
}
/*
equation index: 1228
type: SIMPLE_ASSIGN
conLoo.conCoo.addPD.y = conLoo.conCoo.P.k * conLoo.conCoo.errI1.y
*/
void ReheatControllerFMU_eqFunction_1228(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1228};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* conLoo.conCoo.addPD.y variable */) = ((data->simulationInfo->realParameter[122] /* conLoo.conCoo.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[54]] /* conLoo.conCoo.errI1.y variable */));
  TRACE_POP
}
/*
equation index: 1229
type: SIMPLE_ASSIGN
conLoo.conCoo.addPID.y = conLoo.conCoo.addPD.y + conLoo.conCoo.I.y
*/
void ReheatControllerFMU_eqFunction_1229(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1229};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* conLoo.conCoo.addPD.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* conLoo.conCoo.I.y STATE(1) */);
  TRACE_POP
}
/*
equation index: 1230
type: SIMPLE_ASSIGN
conLoo.conCoo.y = smooth(0, if noEvent(conLoo.conCoo.addPID.y > conLoo.conCoo.lim.uMax) then conLoo.conCoo.lim.uMax else if noEvent(conLoo.conCoo.addPID.y < conLoo.conCoo.lim.uMin) then conLoo.conCoo.lim.uMin else conLoo.conCoo.addPID.y)
*/
void ReheatControllerFMU_eqFunction_1230(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1230};
  modelica_boolean tmp16;
  modelica_boolean tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  tmp16 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */),(data->simulationInfo->realParameter[128] /* conLoo.conCoo.lim.uMax PARAM */));
  tmp18 = (modelica_boolean)tmp16;
  if(tmp18)
  {
    tmp19 = (data->simulationInfo->realParameter[128] /* conLoo.conCoo.lim.uMax PARAM */);
  }
  else
  {
    tmp17 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */),(data->simulationInfo->realParameter[129] /* conLoo.conCoo.lim.uMin PARAM */));
    tmp19 = (tmp17?(data->simulationInfo->realParameter[129] /* conLoo.conCoo.lim.uMin PARAM */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */) = tmp19;
  TRACE_POP
}
/*
equation index: 1231
type: SIMPLE_ASSIGN
conLoo.zerCon.lesHys.y = not pre(conLoo.zerCon.lesHys.y) and conLoo.conCoo.y < 0.01 or pre(conLoo.zerCon.lesHys.y) and conLoo.conCoo.y < 0.018000000000000002
*/
void ReheatControllerFMU_eqFunction_1231(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1231};
  modelica_boolean tmp20;
  modelica_real tmp21;
  modelica_real tmp22;
  modelica_boolean tmp23;
  modelica_real tmp24;
  modelica_real tmp25;
  tmp21 = 1.0;
  tmp22 = 0.01;
  relationhysteresis(data, &tmp20, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.01, tmp21, tmp22, 60, Less, LessZC);
  tmp24 = 1.0;
  tmp25 = 0.018000000000000002;
  relationhysteresis(data, &tmp23, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.018000000000000002, tmp24, tmp25, 61, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */)) && tmp20) || ((data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */) && tmp23));
  TRACE_POP
}
/*
equation index: 1232
type: SIMPLE_ASSIGN
$whenCondition51 = conLoo.zerCon.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1232(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1232};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[46]] /* $whenCondition51 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1233
type: SIMPLE_ASSIGN
$whenCondition50 = not conLoo.zerCon.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1233(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1233};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* $whenCondition50 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1234
type: SIMPLE_ASSIGN
conLoo.disCoo.u = conLoo.zerCon.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1234(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1234};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[127]] /* conLoo.disCoo.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1235
type: SIMPLE_ASSIGN
conLoo.conCoo.antWinErr.y = conLoo.conCoo.addPID.y - conLoo.conCoo.y
*/
void ReheatControllerFMU_eqFunction_1235(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1235};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[51]] /* conLoo.conCoo.antWinErr.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */);
  TRACE_POP
}
/*
equation index: 1236
type: SIMPLE_ASSIGN
conLoo.conCoo.antWinGai.y = conLoo.conCoo.antWinGai.k * conLoo.conCoo.antWinErr.y
*/
void ReheatControllerFMU_eqFunction_1236(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1236};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[52]] /* conLoo.conCoo.antWinGai.y variable */) = ((data->simulationInfo->realParameter[126] /* conLoo.conCoo.antWinGai.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[51]] /* conLoo.conCoo.antWinErr.y variable */));
  TRACE_POP
}
/*
equation index: 1237
type: SIMPLE_ASSIGN
conLoo.conCoo.addRes.y = conLoo.conCoo.yResSig.k - conLoo.conCoo.addPD.y
*/
void ReheatControllerFMU_eqFunction_1237(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1237};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[50]] /* conLoo.conCoo.addRes.y variable */) = (data->simulationInfo->realParameter[137] /* conLoo.conCoo.yResSig.k PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* conLoo.conCoo.addPD.y variable */);
  TRACE_POP
}
/*
equation index: 1238
type: SIMPLE_ASSIGN
conLoo.conCoo.I.u = conLoo.conCoo.errI1.y - conLoo.conCoo.antWinGai.y
*/
void ReheatControllerFMU_eqFunction_1238(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1238};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[46]] /* conLoo.conCoo.I.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[54]] /* conLoo.conCoo.errI1.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[52]] /* conLoo.conCoo.antWinGai.y variable */);
  TRACE_POP
}
/*
equation index: 1239
type: SIMPLE_ASSIGN
$DER.conLoo.conCoo.I.y = conLoo.conCoo.I.k * conLoo.conCoo.I.u
*/
void ReheatControllerFMU_eqFunction_1239(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1239};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[4]] /* der(conLoo.conCoo.I.y) STATE_DER */) = ((data->simulationInfo->realParameter[118] /* conLoo.conCoo.I.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[46]] /* conLoo.conCoo.I.u variable */));
  TRACE_POP
}
/*
equation index: 1240
type: SIMPLE_ASSIGN
conLoo.conCoo.P.u = conLoo.conCoo.errI1.y
*/
void ReheatControllerFMU_eqFunction_1240(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1240};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[47]] /* conLoo.conCoo.P.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[54]] /* conLoo.conCoo.errI1.y variable */);
  TRACE_POP
}
/*
equation index: 1241
type: SIMPLE_ASSIGN
conLoo.conHea.errP.u1 = conLoo.conHea.uS_revAct.k * THeaSet
*/
void ReheatControllerFMU_eqFunction_1241(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1241};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[68]] /* conLoo.conHea.errP.u1 variable */) = ((data->simulationInfo->realParameter[157] /* conLoo.conHea.uS_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */));
  TRACE_POP
}
/*
equation index: 1242
type: SIMPLE_ASSIGN
conLoo.conHea.uMea_revAct.y = conLoo.conHea.uMea_revAct.k * TZon
*/
void ReheatControllerFMU_eqFunction_1242(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1242};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[69]] /* conLoo.conHea.uMea_revAct.y variable */) = ((data->simulationInfo->realParameter[156] /* conLoo.conHea.uMea_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */));
  TRACE_POP
}
/*
equation index: 1243
type: SIMPLE_ASSIGN
conLoo.conHea.errI1.y = conLoo.conHea.errP.u1 - conLoo.conHea.uMea_revAct.y
*/
void ReheatControllerFMU_eqFunction_1243(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1243};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[67]] /* conLoo.conHea.errI1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[68]] /* conLoo.conHea.errP.u1 variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[69]] /* conLoo.conHea.uMea_revAct.y variable */);
  TRACE_POP
}
/*
equation index: 1244
type: SIMPLE_ASSIGN
conLoo.conHea.addPD.y = conLoo.conHea.P.k * conLoo.conHea.errI1.y
*/
void ReheatControllerFMU_eqFunction_1244(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1244};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[61]] /* conLoo.conHea.addPD.y variable */) = ((data->simulationInfo->realParameter[146] /* conLoo.conHea.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[67]] /* conLoo.conHea.errI1.y variable */));
  TRACE_POP
}
/*
equation index: 1245
type: SIMPLE_ASSIGN
conLoo.conHea.addPID.y = conLoo.conHea.addPD.y + conLoo.conHea.I.y
*/
void ReheatControllerFMU_eqFunction_1245(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1245};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[61]] /* conLoo.conHea.addPD.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* conLoo.conHea.I.y STATE(1) */);
  TRACE_POP
}
/*
equation index: 1246
type: SIMPLE_ASSIGN
conLoo.conHea.y = smooth(0, if noEvent(conLoo.conHea.addPID.y > conLoo.conHea.lim.uMax) then conLoo.conHea.lim.uMax else if noEvent(conLoo.conHea.addPID.y < conLoo.conHea.lim.uMin) then conLoo.conHea.lim.uMin else conLoo.conHea.addPID.y)
*/
void ReheatControllerFMU_eqFunction_1246(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1246};
  modelica_boolean tmp26;
  modelica_boolean tmp27;
  modelica_boolean tmp28;
  modelica_real tmp29;
  tmp26 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */),(data->simulationInfo->realParameter[152] /* conLoo.conHea.lim.uMax PARAM */));
  tmp28 = (modelica_boolean)tmp26;
  if(tmp28)
  {
    tmp29 = (data->simulationInfo->realParameter[152] /* conLoo.conHea.lim.uMax PARAM */);
  }
  else
  {
    tmp27 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */),(data->simulationInfo->realParameter[153] /* conLoo.conHea.lim.uMin PARAM */));
    tmp29 = (tmp27?(data->simulationInfo->realParameter[153] /* conLoo.conHea.lim.uMin PARAM */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */) = tmp29;
  TRACE_POP
}
/*
equation index: 1247
type: SIMPLE_ASSIGN
conLoo.zerCon1.lesHys.y = not pre(conLoo.zerCon1.lesHys.y) and conLoo.conHea.y < 0.01 or pre(conLoo.zerCon1.lesHys.y) and conLoo.conHea.y < 0.018000000000000002
*/
void ReheatControllerFMU_eqFunction_1247(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1247};
  modelica_boolean tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_boolean tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  tmp31 = 1.0;
  tmp32 = 0.01;
  relationhysteresis(data, &tmp30, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.01, tmp31, tmp32, 50, Less, LessZC);
  tmp34 = 1.0;
  tmp35 = 0.018000000000000002;
  relationhysteresis(data, &tmp33, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.018000000000000002, tmp34, tmp35, 51, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */)) && tmp30) || ((data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */) && tmp33));
  TRACE_POP
}
/*
equation index: 1248
type: SIMPLE_ASSIGN
$whenCondition48 = conLoo.zerCon1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1248(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1248};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[42]] /* $whenCondition48 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1249
type: SIMPLE_ASSIGN
$whenCondition47 = not conLoo.zerCon1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1249(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1249};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[41]] /* $whenCondition47 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1250
type: SIMPLE_ASSIGN
conLoo.disHea.u = conLoo.zerCon1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1250(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1250};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[130]] /* conLoo.disHea.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1251
type: SIMPLE_ASSIGN
conLoo.conHea.antWinErr.y = conLoo.conHea.addPID.y - conLoo.conHea.y
*/
void ReheatControllerFMU_eqFunction_1251(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1251};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[64]] /* conLoo.conHea.antWinErr.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */);
  TRACE_POP
}
/*
equation index: 1252
type: SIMPLE_ASSIGN
conLoo.conHea.antWinGai.y = conLoo.conHea.antWinGai.k * conLoo.conHea.antWinErr.y
*/
void ReheatControllerFMU_eqFunction_1252(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1252};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[65]] /* conLoo.conHea.antWinGai.y variable */) = ((data->simulationInfo->realParameter[150] /* conLoo.conHea.antWinGai.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[64]] /* conLoo.conHea.antWinErr.y variable */));
  TRACE_POP
}
/*
equation index: 1253
type: SIMPLE_ASSIGN
conLoo.conHea.addRes.y = conLoo.conHea.yResSig.k - conLoo.conHea.addPD.y
*/
void ReheatControllerFMU_eqFunction_1253(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1253};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[63]] /* conLoo.conHea.addRes.y variable */) = (data->simulationInfo->realParameter[161] /* conLoo.conHea.yResSig.k PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[61]] /* conLoo.conHea.addPD.y variable */);
  TRACE_POP
}
/*
equation index: 1254
type: SIMPLE_ASSIGN
conLoo.conHea.I.u = conLoo.conHea.errI1.y - conLoo.conHea.antWinGai.y
*/
void ReheatControllerFMU_eqFunction_1254(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1254};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[59]] /* conLoo.conHea.I.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[67]] /* conLoo.conHea.errI1.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[65]] /* conLoo.conHea.antWinGai.y variable */);
  TRACE_POP
}
/*
equation index: 1255
type: SIMPLE_ASSIGN
$DER.conLoo.conHea.I.y = conLoo.conHea.I.k * conLoo.conHea.I.u
*/
void ReheatControllerFMU_eqFunction_1255(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1255};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[5]] /* der(conLoo.conHea.I.y) STATE_DER */) = ((data->simulationInfo->realParameter[142] /* conLoo.conHea.I.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[59]] /* conLoo.conHea.I.u variable */));
  TRACE_POP
}
/*
equation index: 1256
type: SIMPLE_ASSIGN
conLoo.conHea.P.u = conLoo.conHea.errI1.y
*/
void ReheatControllerFMU_eqFunction_1256(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1256};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[60]] /* conLoo.conHea.P.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[67]] /* conLoo.conHea.errI1.y variable */);
  TRACE_POP
}
/*
equation index: 1257
type: SIMPLE_ASSIGN
conLoo.enaHeaLoo.lesHys.y = not pre(conLoo.enaHeaLoo.lesHys.y) and TZon < THeaSet or pre(conLoo.enaHeaLoo.lesHys.y) and TZon < THeaSet + 0.25
*/
void ReheatControllerFMU_eqFunction_1257(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1257};
  modelica_boolean tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_boolean tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  tmp37 = 1.0;
  tmp38 = 1.0;
  relationhysteresis(data, &tmp36, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */), tmp37, tmp38, 48, Less, LessZC);
  tmp40 = 1.0;
  tmp41 = 1.25;
  relationhysteresis(data, &tmp39, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + 0.25, tmp40, tmp41, 49, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[134]] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */)) && tmp36) || ((data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) && tmp39));
  TRACE_POP
}
/*
equation index: 1258
type: SIMPLE_ASSIGN
$whenCondition72 = conLoo.enaHeaLoo.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1258(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1258};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[69]] /* $whenCondition72 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[134]] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1259
type: SIMPLE_ASSIGN
conLoo.enaCooLoo.lesHys.y = not pre(conLoo.enaCooLoo.lesHys.y) and TCooSet < TZon or pre(conLoo.enaCooLoo.lesHys.y) and TCooSet < TZon + 0.25
*/
void ReheatControllerFMU_eqFunction_1259(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1259};
  modelica_boolean tmp42;
  modelica_real tmp43;
  modelica_real tmp44;
  modelica_boolean tmp45;
  modelica_real tmp46;
  modelica_real tmp47;
  tmp43 = 1.0;
  tmp44 = 1.0;
  relationhysteresis(data, &tmp42, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), tmp43, tmp44, 46, Less, LessZC);
  tmp46 = 1.0;
  tmp47 = 1.25;
  relationhysteresis(data, &tmp45, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) + 0.25, tmp46, tmp47, 47, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[133]] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */)) && tmp42) || ((data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) && tmp45));
  TRACE_POP
}
/*
equation index: 1260
type: SIMPLE_ASSIGN
$whenCondition71 = conLoo.enaCooLoo.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1260(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1260};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[68]] /* $whenCondition71 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[133]] /* conLoo.enaCooLoo.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1261
type: SIMPLE_ASSIGN
ala.gre1.greHys.y = not pre(ala.gre1.greHys.y) and VDis_flow > ala.gai2.y or pre(ala.gre1.greHys.y) and VDis_flow > ala.gai2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_1261(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1261};
  modelica_boolean tmp48;
  modelica_real tmp49;
  modelica_real tmp50;
  modelica_boolean tmp51;
  modelica_real tmp52;
  modelica_real tmp53;
  tmp49 = 1.0;
  tmp50 = 1.0;
  relationhysteresis(data, &tmp48, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */), tmp49, tmp50, 44, Greater, GreaterZC);
  tmp52 = 1.0;
  tmp53 = 1.005;
  relationhysteresis(data, &tmp51, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) - 0.005, tmp52, tmp53, 45, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[96]] /* ala.gre1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */)) && tmp48) || ((data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */) && tmp51));
  TRACE_POP
}
/*
equation index: 1262
type: SIMPLE_ASSIGN
$whenCondition39 = ala.gre1.greHys.y and not u1Fan
*/
void ReheatControllerFMU_eqFunction_1262(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1262};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[96]] /* ala.gre1.greHys.y DISCRETE */) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */)));
  TRACE_POP
}
/*
equation index: 1263
type: SIMPLE_ASSIGN
$whenCondition38 = not $whenCondition39
*/
void ReheatControllerFMU_eqFunction_1263(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1263};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[31]] /* $whenCondition38 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */));
  TRACE_POP
}
/*
equation index: 1264
type: SIMPLE_ASSIGN
ala.truDel2.u = $whenCondition39
*/
void ReheatControllerFMU_eqFunction_1264(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1264};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[115]] /* ala.truDel2.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1265
type: SIMPLE_ASSIGN
ala.leaDamAla.y = ala.gre1.greHys.y and u1Fan
*/
void ReheatControllerFMU_eqFunction_1265(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1265};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[102]] /* ala.leaDamAla.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[96]] /* ala.gre1.greHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */));
  TRACE_POP
}
/*
equation index: 1266
type: SIMPLE_ASSIGN
ala.addPar2.y = 3.0 + TSup
*/
void ReheatControllerFMU_eqFunction_1266(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1266};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) = 3.0 + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* TSup variable */);
  TRACE_POP
}
/*
equation index: 1267
type: SIMPLE_ASSIGN
ala.gre2.greHys.y = not pre(ala.gre2.greHys.y) and TDis > ala.addPar2.y or pre(ala.gre2.greHys.y) and TDis > ala.addPar2.y - 0.25
*/
void ReheatControllerFMU_eqFunction_1267(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1267};
  modelica_boolean tmp54;
  modelica_real tmp55;
  modelica_real tmp56;
  modelica_boolean tmp57;
  modelica_real tmp58;
  modelica_real tmp59;
  tmp55 = 1.0;
  tmp56 = 1.0;
  relationhysteresis(data, &tmp54, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */), tmp55, tmp56, 42, Greater, GreaterZC);
  tmp58 = 1.0;
  tmp59 = 1.25;
  relationhysteresis(data, &tmp57, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) - 0.25, tmp58, tmp59, 43, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[97]] /* ala.gre2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */)) && tmp54) || ((data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */) && tmp57));
  TRACE_POP
}
/*
equation index: 1268
type: SIMPLE_ASSIGN
ala.fanHotPlaOn.y = u1HotPla and u1Fan
*/
void ReheatControllerFMU_eqFunction_1268(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1268};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[92]] /* ala.fanHotPlaOn.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[222]] /* u1HotPla variable */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */));
  TRACE_POP
}
/*
equation index: 1269
type: SIMPLE_ASSIGN
ala.isOcc.y = uOpeMod == 1
*/
void ReheatControllerFMU_eqFunction_1269(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1269};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[101]] /* ala.isOcc.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1));
  TRACE_POP
}
/*
equation index: 1270
type: SIMPLE_ASSIGN
setOve.intEqu3.y = oveDamPos == 1
*/
void ReheatControllerFMU_eqFunction_1270(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1270};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[165]] /* setOve.intEqu3.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 1));
  TRACE_POP
}
/*
equation index: 1271
type: SIMPLE_ASSIGN
setOve.cloDam.y = if setOve.intEqu3.y then 0.0 else setOve.cloDam.realFalse
*/
void ReheatControllerFMU_eqFunction_1271(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1271};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[146]] /* setOve.cloDam.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[165]] /* setOve.intEqu3.y DISCRETE */)?0.0:(data->simulationInfo->realParameter[322] /* setOve.cloDam.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1272
type: SIMPLE_ASSIGN
setOve.intEqu4.y = oveDamPos == 2
*/
void ReheatControllerFMU_eqFunction_1272(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1272};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[166]] /* setOve.intEqu4.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 2));
  TRACE_POP
}
/*
equation index: 1273
type: SIMPLE_ASSIGN
setOve.opeDam.y = if setOve.intEqu4.y then 1.0 else setOve.opeDam.realFalse
*/
void ReheatControllerFMU_eqFunction_1273(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1273};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[147]] /* setOve.opeDam.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[166]] /* setOve.intEqu4.y DISCRETE */)?1.0:(data->simulationInfo->realParameter[324] /* setOve.opeDam.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1274
type: SIMPLE_ASSIGN
setOve.add3.y = setOve.cloDam.y + setOve.opeDam.y
*/
void ReheatControllerFMU_eqFunction_1274(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1274};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[144]] /* setOve.add3.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[146]] /* setOve.cloDam.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[147]] /* setOve.opeDam.y variable */);
  TRACE_POP
}
/*
equation index: 1275
type: SIMPLE_ASSIGN
setOve.or2.y = setOve.intEqu3.y or setOve.intEqu4.y
*/
void ReheatControllerFMU_eqFunction_1275(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1275};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[167]] /* setOve.or2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[165]] /* setOve.intEqu3.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[166]] /* setOve.intEqu4.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1276
type: SIMPLE_ASSIGN
setOve.booToRea.y = if uHeaOff then 0.0 else 1.0
*/
void ReheatControllerFMU_eqFunction_1276(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1276};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[145]] /* setOve.booToRea.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[225]] /* uHeaOff variable */)?0.0:1.0);
  TRACE_POP
}
/*
equation index: 1277
type: SIMPLE_ASSIGN
$whenCondition18 = sample(5, timSup.samSet.t0, timSup.samSet.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1277(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1277};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition18 DISCRETE */) = data->simulationInfo->samples[4];
  TRACE_POP
}
/*
equation index: 1278
type: WHEN

when {$whenCondition18} then
  timSup.samSet.y = TCooSet;
end when;
*/
void ReheatControllerFMU_eqFunction_1278(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1278};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition18 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[9] /* $whenCondition18 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[216]] /* timSup.samSet.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */);
  }
  TRACE_POP
}
/*
equation index: 1279
type: WHEN

when {$whenCondition18} then
  timSup.samSet.firstTrigger = time <= timSup.samSet.t0 + 0.5 * timSup.samSet.samplePeriod;
end when;
*/
void ReheatControllerFMU_eqFunction_1279(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1279};
  modelica_boolean tmp60;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition18 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[9] /* $whenCondition18 DISCRETE */) /* edge */))
  {
    tmp60 = LessEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[450] /* timSup.samSet.t0 PARAM */) + (0.5) * ((data->simulationInfo->realParameter[449] /* timSup.samSet.samplePeriod PARAM */)));
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[214]] /* timSup.samSet.firstTrigger DISCRETE */) = tmp60;
  }
  TRACE_POP
}
/*
equation index: 1280
type: SIMPLE_ASSIGN
timSup.samSet.sampleTrigger = $whenCondition18
*/
void ReheatControllerFMU_eqFunction_1280(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1280};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[215]] /* timSup.samSet.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition18 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1281
type: SIMPLE_ASSIGN
$whenCondition17 = sample(6, timSup.uniDel.t0, timSup.uniDel.samplePeriod)
*/
void ReheatControllerFMU_eqFunction_1281(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1281};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition17 DISCRETE */) = data->simulationInfo->samples[5];
  TRACE_POP
}
/*
equation index: 1282
type: WHEN

when {$whenCondition17} then
  timSup.uniDel.y = pre(timSup.uniDel.u_internal);
end when;
*/
void ReheatControllerFMU_eqFunction_1282(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1282};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition17 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[8] /* $whenCondition17 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[222]] /* timSup.uniDel.y DISCRETE */) = (data->simulationInfo->realVarsPre[221] /* timSup.uniDel.u_internal DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1283
type: SIMPLE_ASSIGN
timSup.sub1.y = timSup.samSet.y - timSup.uniDel.y
*/
void ReheatControllerFMU_eqFunction_1283(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1283};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[185]] /* timSup.sub1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[216]] /* timSup.samSet.y DISCRETE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[222]] /* timSup.uniDel.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1284
type: WHEN

when {$whenCondition17} then
  timSup.uniDel.u_internal = timSup.samSet.y;
end when;
*/
void ReheatControllerFMU_eqFunction_1284(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1284};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition17 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[8] /* $whenCondition17 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[221]] /* timSup.uniDel.u_internal DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[216]] /* timSup.samSet.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1285
type: SIMPLE_ASSIGN
timSup.uniDel.sampleTrigger = $whenCondition17
*/
void ReheatControllerFMU_eqFunction_1285(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1285};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[219]] /* timSup.uniDel.sampleTrigger DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition17 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1286
type: SIMPLE_ASSIGN
$whenCondition15 = pre(timSup.pre1.u)
*/
void ReheatControllerFMU_eqFunction_1286(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1286};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */) = (data->simulationInfo->booleanVarsPre[212] /* timSup.pre1.u DISCRETE */);
  TRACE_POP
}
/*
equation index: 1287
type: SIMPLE_ASSIGN
timSup.pre1.y = $whenCondition15
*/
void ReheatControllerFMU_eqFunction_1287(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1287};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[213]] /* timSup.pre1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1288
type: SIMPLE_ASSIGN
setPoi.addPar.y = -200.0 + ppmCO2Set
*/
void ReheatControllerFMU_eqFunction_1288(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1288};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[149]] /* setPoi.addPar.y variable */) = -200.0 + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */);
  TRACE_POP
}
/*
equation index: 1289
type: SIMPLE_ASSIGN
$cse1 = max(setPoi.addPar.y, ppmCO2)
*/
void ReheatControllerFMU_eqFunction_1289(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1289};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* $cse1 variable */) = fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[149]] /* setPoi.addPar.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[142]] /* ppmCO2 variable */));
  TRACE_POP
}
/*
equation index: 1290
type: SIMPLE_ASSIGN
setPoi.lin.xLim = min(ppmCO2Set, $cse1)
*/
void ReheatControllerFMU_eqFunction_1290(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1290};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[156]] /* setPoi.lin.xLim variable */) = fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[8]] /* $cse1 variable */));
  TRACE_POP
}
/*
equation index: 1291
type: SIMPLE_ASSIGN
setPoi.lin.b = 1.0 / (ppmCO2Set - setPoi.addPar.y)
*/
void ReheatControllerFMU_eqFunction_1291(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1291};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[155]] /* setPoi.lin.b variable */) = DIVISION_SIM(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[149]] /* setPoi.addPar.y variable */),"ppmCO2Set - setPoi.addPar.y",equationIndexes);
  TRACE_POP
}
/*
equation index: 1292
type: SIMPLE_ASSIGN
setPoi.lin.a = 1.0 - setPoi.lin.b * ppmCO2Set
*/
void ReheatControllerFMU_eqFunction_1292(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1292};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[154]] /* setPoi.lin.a variable */) = 1.0 - (((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[155]] /* setPoi.lin.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */)));
  TRACE_POP
}
/*
equation index: 1293
type: SIMPLE_ASSIGN
setPoi.lin.y = setPoi.lin.a + setPoi.lin.b * setPoi.lin.xLim
*/
void ReheatControllerFMU_eqFunction_1293(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1293};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[157]] /* setPoi.lin.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[154]] /* setPoi.lin.a variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[155]] /* setPoi.lin.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[156]] /* setPoi.lin.xLim variable */));
  TRACE_POP
}
/*
equation index: 1294
type: SIMPLE_ASSIGN
setPoi.notOccMod.y = not uOpeMod == 1
*/
void ReheatControllerFMU_eqFunction_1294(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1294};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[169]] /* setPoi.notOccMod.y DISCRETE */) = (!((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1)));
  TRACE_POP
}
/*
equation index: 1295
type: SIMPLE_ASSIGN
setPoi.booToRea.y = if not setPoi.notOccMod.y then setPoi.booToRea.realTrue else setPoi.booToRea.realFalse
*/
void ReheatControllerFMU_eqFunction_1295(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1295};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[151]] /* setPoi.booToRea.y variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[169]] /* setPoi.notOccMod.y DISCRETE */))?(data->simulationInfo->realParameter[334] /* setPoi.booToRea.realTrue PARAM */):(data->simulationInfo->realParameter[333] /* setPoi.booToRea.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1296
type: SIMPLE_ASSIGN
setPoi.co2Con.y = setPoi.booToRea.y * setPoi.lin.y
*/
void ReheatControllerFMU_eqFunction_1296(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1296};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[153]] /* setPoi.co2Con.y variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[151]] /* setPoi.booToRea.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[157]] /* setPoi.lin.y variable */));
  TRACE_POP
}
/*
equation index: 1297
type: SIMPLE_ASSIGN
$cse2 = max(0.0, setPoi.co2Con.y)
*/
void ReheatControllerFMU_eqFunction_1297(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1297};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* $cse2 variable */) = fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[153]] /* setPoi.co2Con.y variable */));
  TRACE_POP
}
/*
equation index: 1298
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.xLim = min(1.0, $cse2)
*/
void ReheatControllerFMU_eqFunction_1298(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1298};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[160]] /* setPoi.occMinAirSet.xLim variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[9]] /* $cse2 variable */));
  TRACE_POP
}
/*
equation index: 1299
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.y = setPoi.occMinAirSet.a + setPoi.occMinAirSet.b * setPoi.occMinAirSet.xLim
*/
void ReheatControllerFMU_eqFunction_1299(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1299};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[161]] /* setPoi.occMinAirSet.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[158]] /* setPoi.occMinAirSet.a variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[159]] /* setPoi.occMinAirSet.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[160]] /* setPoi.occMinAirSet.xLim variable */));
  TRACE_POP
}
/*
equation index: 1300
type: SIMPLE_ASSIGN
setPoi.unpMinZonAir.y = smooth(0, if not u1Occ then setPoi.unpMinZonFlo.y else setPoi.occMinAirSet.y)
*/
void ReheatControllerFMU_eqFunction_1300(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1300};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[169]] /* setPoi.unpMinZonAir.y variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[223]] /* u1Occ variable */))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[170]] /* setPoi.unpMinZonFlo.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[161]] /* setPoi.occMinAirSet.y variable */));
  TRACE_POP
}
/*
equation index: 1301
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.y = setPoi.desPopAir.k * setPoi.occMinAirSet.xLim
*/
void ReheatControllerFMU_eqFunction_1301(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1301};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[165]] /* setPoi.popBreOutAir.y variable */) = ((data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[160]] /* setPoi.occMinAirSet.xLim variable */));
  TRACE_POP
}
/*
equation index: 1302
type: SIMPLE_ASSIGN
setPoi.unpPopBreAir.y = smooth(0, if not u1Occ then 0.0 else setPoi.popBreOutAir.y)
*/
void ReheatControllerFMU_eqFunction_1302(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1302};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[171]] /* setPoi.unpPopBreAir.y variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[223]] /* u1Occ variable */))?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[165]] /* setPoi.popBreOutAir.y variable */));
  TRACE_POP
}
/*
equation index: 1303
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.xLim = setPoi.occMinAirSet.xLim
*/
void ReheatControllerFMU_eqFunction_1303(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1303};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[164]] /* setPoi.popBreOutAir.xLim variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[160]] /* setPoi.occMinAirSet.xLim variable */);
  TRACE_POP
}
/*
equation index: 1304
type: SIMPLE_ASSIGN
setPoi.or2.y = not u1Win or setPoi.notOccMod.y
*/
void ReheatControllerFMU_eqFunction_1304(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1304};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[170]] /* setPoi.or2.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[224]] /* u1Win variable */)) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[169]] /* setPoi.notOccMod.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1305
type: SIMPLE_ASSIGN
setPoi.VOccZonMin_flow = smooth(0, if setPoi.or2.y then 0.0 else setPoi.unpMinZonAir.y)
*/
void ReheatControllerFMU_eqFunction_1305(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1305};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[148]] /* setPoi.VOccZonMin_flow variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[170]] /* setPoi.or2.y DISCRETE */)?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[169]] /* setPoi.unpMinZonAir.y variable */));
  TRACE_POP
}
/*
equation index: 1306
type: SIMPLE_ASSIGN
actAirSet.max2.y = max(setPoi.VOccZonMin_flow, actAirSet.heaMaxAir.k)
*/
void ReheatControllerFMU_eqFunction_1306(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1306};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[35]] /* actAirSet.max2.y variable */) = fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[148]] /* setPoi.VOccZonMin_flow variable */),(data->simulationInfo->realParameter[22] /* actAirSet.heaMaxAir.k PARAM */));
  TRACE_POP
}
/*
equation index: 1307
type: SIMPLE_ASSIGN
actAirSet.pro2.y = actAirSet.occModInd.y * actAirSet.max2.y
*/
void ReheatControllerFMU_eqFunction_1307(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1307};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* actAirSet.pro2.y variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* actAirSet.occModInd.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[35]] /* actAirSet.max2.y variable */));
  TRACE_POP
}
/*
equation index: 1308
type: SIMPLE_ASSIGN
actAirSet.VActHeaMax_flow = actAirSet.pro2.y + actAirSet.add3.y
*/
void ReheatControllerFMU_eqFunction_1308(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1308};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* actAirSet.VActHeaMax_flow variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[38]] /* actAirSet.pro2.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[29]] /* actAirSet.add3.y variable */);
  TRACE_POP
}
/*
equation index: 1309
type: SIMPLE_ASSIGN
actAirSet.max1.y = max(setPoi.VOccZonMin_flow, actAirSet.heaMinAir.k)
*/
void ReheatControllerFMU_eqFunction_1309(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1309};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* actAirSet.max1.y variable */) = fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[148]] /* setPoi.VOccZonMin_flow variable */),(data->simulationInfo->realParameter[28] /* actAirSet.heaMinAir.k PARAM */));
  TRACE_POP
}
/*
equation index: 1310
type: SIMPLE_ASSIGN
actAirSet.pro1.y = actAirSet.occModInd.y * actAirSet.max1.y
*/
void ReheatControllerFMU_eqFunction_1310(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1310};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* actAirSet.pro1.y variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* actAirSet.occModInd.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[34]] /* actAirSet.max1.y variable */));
  TRACE_POP
}
/*
equation index: 1311
type: SIMPLE_ASSIGN
actAirSet.VActHeaMin_flow = actAirSet.pro1.y + actAirSet.add2.y
*/
void ReheatControllerFMU_eqFunction_1311(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1311};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[26]] /* actAirSet.VActHeaMin_flow variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[37]] /* actAirSet.pro1.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[28]] /* actAirSet.add2.y variable */);
  TRACE_POP
}
/*
equation index: 1312
type: SIMPLE_ASSIGN
damVal.lin3.b = 2.0 * (actAirSet.VActHeaMax_flow - actAirSet.VActHeaMin_flow)
*/
void ReheatControllerFMU_eqFunction_1312(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1312};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[127]] /* damVal.lin3.b variable */) = (2.0) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* actAirSet.VActHeaMax_flow variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[26]] /* actAirSet.VActHeaMin_flow variable */));
  TRACE_POP
}
/*
equation index: 1313
type: SIMPLE_ASSIGN
damVal.lin3.a = actAirSet.VActHeaMax_flow - damVal.lin3.b
*/
void ReheatControllerFMU_eqFunction_1313(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1313};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[126]] /* damVal.lin3.a variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* actAirSet.VActHeaMax_flow variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[127]] /* damVal.lin3.b variable */);
  TRACE_POP
}
/*
equation index: 1314
type: SIMPLE_ASSIGN
actAirSet.VActMin_flow = actAirSet.occModInd.y * setPoi.VOccZonMin_flow
*/
void ReheatControllerFMU_eqFunction_1314(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1314};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[36]] /* actAirSet.occModInd.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[148]] /* setPoi.VOccZonMin_flow variable */));
  TRACE_POP
}
/*
equation index: 1315
type: SIMPLE_ASSIGN
damVal.lin.b = actAirSet.VActCooMax_flow - actAirSet.VActMin_flow
*/
void ReheatControllerFMU_eqFunction_1315(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1315};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[123]] /* damVal.lin.b variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* actAirSet.VActCooMax_flow variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */);
  TRACE_POP
}
/*
equation index: 1316
type: SIMPLE_ASSIGN
damVal.lin.a = actAirSet.VActMin_flow
*/
void ReheatControllerFMU_eqFunction_1316(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1316};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[122]] /* damVal.lin.a variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */);
  TRACE_POP
}
/*
equation index: 1317
type: SIMPLE_ASSIGN
VAdjPopBreZon_flow = smooth(0, if setPoi.or2.y then 0.0 else setPoi.unpPopBreAir.y)
*/
void ReheatControllerFMU_eqFunction_1317(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1317};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* VAdjPopBreZon_flow variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[170]] /* setPoi.or2.y DISCRETE */)?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[171]] /* setPoi.unpPopBreAir.y variable */));
  TRACE_POP
}
/*
equation index: 1318
type: SIMPLE_ASSIGN
setPoi.unpAreBreAir.y = smooth(0, if not u1Occ then setPoi.unPopAreBreAir.y else setPoi.desAreAir.k)
*/
void ReheatControllerFMU_eqFunction_1318(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1318};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[168]] /* setPoi.unpAreBreAir.y variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[223]] /* u1Occ variable */))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[167]] /* setPoi.unPopAreBreAir.y variable */):(data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */));
  TRACE_POP
}
/*
equation index: 1319
type: SIMPLE_ASSIGN
VAdjAreBreZon_flow = smooth(0, if setPoi.or2.y then 0.0 else setPoi.unpAreBreAir.y)
*/
void ReheatControllerFMU_eqFunction_1319(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1319};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* VAdjAreBreZon_flow variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[170]] /* setPoi.or2.y DISCRETE */)?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[168]] /* setPoi.unpAreBreAir.y variable */));
  TRACE_POP
}
/*
equation index: 1320
type: SIMPLE_ASSIGN
setPoi.reqBreAir.y = VAdjPopBreZon_flow + VAdjAreBreZon_flow
*/
void ReheatControllerFMU_eqFunction_1320(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1320};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[166]] /* setPoi.reqBreAir.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[20]] /* VAdjPopBreZon_flow variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[19]] /* VAdjAreBreZon_flow variable */);
  TRACE_POP
}
/*
equation index: 1321
type: SIMPLE_ASSIGN
setPoi.cooSup.greHys.y = not pre(setPoi.cooSup.greHys.y) and TZon > TDis or pre(setPoi.cooSup.greHys.y) and TZon > TDis - 0.25
*/
void ReheatControllerFMU_eqFunction_1321(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1321};
  modelica_boolean tmp61;
  modelica_real tmp62;
  modelica_real tmp63;
  modelica_boolean tmp64;
  modelica_real tmp65;
  modelica_real tmp66;
  tmp62 = 1.0;
  tmp63 = 1.0;
  relationhysteresis(data, &tmp61, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), tmp62, tmp63, 33, Greater, GreaterZC);
  tmp65 = 1.0;
  tmp66 = 1.25;
  relationhysteresis(data, &tmp64, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) - 0.25, tmp65, tmp66, 34, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[168]] /* setPoi.cooSup.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */)) && tmp61) || ((data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */) && tmp64));
  TRACE_POP
}
/*
equation index: 1322
type: SIMPLE_ASSIGN
setPoi.airDisEff.y = if setPoi.cooSup.greHys.y then setPoi.airDisEff.realTrue else setPoi.airDisEff.realFalse
*/
void ReheatControllerFMU_eqFunction_1322(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1322};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[150]] /* setPoi.airDisEff.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[168]] /* setPoi.cooSup.greHys.y DISCRETE */)?(data->simulationInfo->realParameter[332] /* setPoi.airDisEff.realTrue PARAM */):(data->simulationInfo->realParameter[331] /* setPoi.airDisEff.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1323
type: SIMPLE_ASSIGN
VMinOA_flow = setPoi.reqBreAir.y / setPoi.airDisEff.y
*/
void ReheatControllerFMU_eqFunction_1323(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1323};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[22]] /* VMinOA_flow variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[166]] /* setPoi.reqBreAir.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[150]] /* setPoi.airDisEff.y variable */),"setPoi.airDisEff.y",equationIndexes);
  TRACE_POP
}
/*
equation index: 1324
type: SIMPLE_ASSIGN
damVal.conVal.uMea_revAct.y = damVal.conVal.uMea_revAct.k * TDis
*/
void ReheatControllerFMU_eqFunction_1324(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1324};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[115]] /* damVal.conVal.uMea_revAct.y variable */) = ((data->simulationInfo->realParameter[246] /* damVal.conVal.uMea_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */));
  TRACE_POP
}
/*
equation index: 1325
type: SIMPLE_ASSIGN
damVal.sub2.y = TSup - TZon
*/
void ReheatControllerFMU_eqFunction_1325(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1325};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[16]] /* TSup variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */);
  TRACE_POP
}
/*
equation index: 1326
type: SIMPLE_ASSIGN
damVal.greThr.greHys.y = not pre(damVal.greThr.greHys.y) and damVal.sub2.y > 0.25 or pre(damVal.greThr.greHys.y) and damVal.sub2.y > 0.125
*/
void ReheatControllerFMU_eqFunction_1326(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1326};
  modelica_boolean tmp67;
  modelica_real tmp68;
  modelica_real tmp69;
  modelica_boolean tmp70;
  modelica_real tmp71;
  modelica_real tmp72;
  tmp68 = 1.0;
  tmp69 = 0.25;
  relationhysteresis(data, &tmp67, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.25, tmp68, tmp69, 29, Greater, GreaterZC);
  tmp71 = 1.0;
  tmp72 = 0.125;
  relationhysteresis(data, &tmp70, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.125, tmp71, tmp72, 30, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[147]] /* damVal.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */)) && tmp67) || ((data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */) && tmp70));
  TRACE_POP
}
/*
equation index: 1327
type: SIMPLE_ASSIGN
damVal.VDis_flowNor.y = VDis_flow / damVal.max2.y
*/
void ReheatControllerFMU_eqFunction_1327(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1327};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[77]] /* damVal.VDis_flowNor.y variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[131]] /* damVal.max2.y variable */),"damVal.max2.y",equationIndexes);
  TRACE_POP
}
/*
equation index: 1328
type: SIMPLE_ASSIGN
damVal.conDam.uMea_revAct.y = damVal.conDam.uMea_revAct.k * damVal.VDis_flowNor.y
*/
void ReheatControllerFMU_eqFunction_1328(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1328};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[94]] /* damVal.conDam.uMea_revAct.y variable */) = ((data->simulationInfo->realParameter[218] /* damVal.conDam.uMea_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[77]] /* damVal.VDis_flowNor.y variable */));
  TRACE_POP
}
/*
equation index: 1329
type: SIMPLE_ASSIGN
damVal.lowMin.lesHys.y = not pre(damVal.lowMin.lesHys.y) and TDis < damVal.lowMin.lesHys.t or pre(damVal.lowMin.lesHys.y) and TDis < damVal.lowMin.lesHys.t + 0.25
*/
void ReheatControllerFMU_eqFunction_1329(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1329};
  modelica_boolean tmp73;
  modelica_real tmp74;
  modelica_real tmp75;
  modelica_boolean tmp76;
  modelica_real tmp77;
  modelica_real tmp78;
  tmp74 = 1.0;
  tmp75 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */));
  relationhysteresis(data, &tmp73, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */), tmp74, tmp75, 27, Less, LessZC);
  tmp77 = 1.0;
  tmp78 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */)) + 0.25;
  relationhysteresis(data, &tmp76, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) + 0.25, tmp77, tmp78, 28, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[152]] /* damVal.lowMin.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */)) && tmp73) || ((data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */) && tmp76));
  TRACE_POP
}
/*
equation index: 1330
type: SIMPLE_ASSIGN
damVal.addPar1.y = 3.0 + TZon
*/
void ReheatControllerFMU_eqFunction_1330(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1330};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) = 3.0 + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */);
  TRACE_POP
}
/*
equation index: 1331
type: SIMPLE_ASSIGN
damVal.gre.greHys.y = not pre(damVal.gre.greHys.y) and TDis > damVal.addPar1.y or pre(damVal.gre.greHys.y) and TDis > damVal.addPar1.y - 0.25
*/
void ReheatControllerFMU_eqFunction_1331(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1331};
  modelica_boolean tmp79;
  modelica_real tmp80;
  modelica_real tmp81;
  modelica_boolean tmp82;
  modelica_real tmp83;
  modelica_real tmp84;
  tmp80 = 1.0;
  tmp81 = 1.0;
  relationhysteresis(data, &tmp79, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */), tmp80, tmp81, 31, Greater, GreaterZC);
  tmp83 = 1.0;
  tmp84 = 1.25;
  relationhysteresis(data, &tmp82, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) - 0.25, tmp83, tmp84, 32, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[146]] /* damVal.gre.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */)) && tmp79) || ((data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */) && tmp82));
  TRACE_POP
}
/*
equation index: 1332
type: SIMPLE_ASSIGN
damVal.addPar.y = THeaSet + damVal.addPar.p
*/
void ReheatControllerFMU_eqFunction_1332(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1332};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[81]] /* damVal.addPar.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + (data->simulationInfo->realParameter[201] /* damVal.addPar.p PARAM */);
  TRACE_POP
}
/*
equation index: 1333
type: SIMPLE_ASSIGN
damVal.conTDisHeaSet.b = 2.0 * (damVal.addPar.y - TSupSet)
*/
void ReheatControllerFMU_eqFunction_1333(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1333};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[101]] /* damVal.conTDisHeaSet.b variable */) = (2.0) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[81]] /* damVal.addPar.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* TSupSet variable */));
  TRACE_POP
}
/*
equation index: 1334
type: SIMPLE_ASSIGN
damVal.conTDisHeaSet.a = damVal.addPar.y - 0.5 * damVal.conTDisHeaSet.b
*/
void ReheatControllerFMU_eqFunction_1334(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1334};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[100]] /* damVal.conTDisHeaSet.a variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[81]] /* damVal.addPar.y variable */) - ((0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[101]] /* damVal.conTDisHeaSet.b variable */)));
  TRACE_POP
}
/*
equation index: 1335
type: SIMPLE_ASSIGN
damVal.isOcc.y = 1 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1335(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1335};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[150]] /* damVal.isOcc.y DISCRETE */) = (((modelica_integer) 1) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1336
type: SIMPLE_ASSIGN
damVal.and1.y = damVal.lowMin.lesHys.y and damVal.isOcc.y
*/
void ReheatControllerFMU_eqFunction_1336(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1336};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[137]] /* damVal.and1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[152]] /* damVal.lowMin.lesHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[150]] /* damVal.isOcc.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1337
type: SIMPLE_ASSIGN
damVal.isUno.y = 7 == uOpeMod
*/
void ReheatControllerFMU_eqFunction_1337(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1337};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[151]] /* damVal.isUno.y DISCRETE */) = (((modelica_integer) 7) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
  TRACE_POP
}
/*
equation index: 1338
type: SIMPLE_ASSIGN
damVal.forZerFlo.y = oveFloSet == 1
*/
void ReheatControllerFMU_eqFunction_1338(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1338};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[145]] /* damVal.forZerFlo.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 1));
  TRACE_POP
}
/*
equation index: 1339
type: SIMPLE_ASSIGN
damVal.zerFlo.y = if damVal.forZerFlo.y then 0.0 else damVal.zerFlo.realFalse
*/
void ReheatControllerFMU_eqFunction_1339(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1339};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[141]] /* damVal.zerFlo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[145]] /* damVal.forZerFlo.y DISCRETE */)?0.0:(data->simulationInfo->realParameter[301] /* damVal.zerFlo.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1340
type: SIMPLE_ASSIGN
damVal.forCooMax.y = oveFloSet == 2
*/
void ReheatControllerFMU_eqFunction_1340(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1340};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[142]] /* damVal.forCooMax.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 2));
  TRACE_POP
}
/*
equation index: 1341
type: SIMPLE_ASSIGN
damVal.cooMax.y = if damVal.forCooMax.y then damVal.cooMax.realTrue else damVal.cooMax.realFalse
*/
void ReheatControllerFMU_eqFunction_1341(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1341};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[120]] /* damVal.cooMax.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[142]] /* damVal.forCooMax.y DISCRETE */)?(data->simulationInfo->realParameter[259] /* damVal.cooMax.realTrue PARAM */):(data->simulationInfo->realParameter[258] /* damVal.cooMax.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1342
type: SIMPLE_ASSIGN
damVal.or3.y = damVal.forZerFlo.y or damVal.forCooMax.y
*/
void ReheatControllerFMU_eqFunction_1342(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1342};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[155]] /* damVal.or3.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[145]] /* damVal.forZerFlo.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[142]] /* damVal.forCooMax.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1343
type: SIMPLE_ASSIGN
damVal.forMinFlo.y = oveFloSet == 3
*/
void ReheatControllerFMU_eqFunction_1343(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1343};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[143]] /* damVal.forMinFlo.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 3));
  TRACE_POP
}
/*
equation index: 1344
type: SIMPLE_ASSIGN
damVal.minFlo.y = if damVal.forMinFlo.y then 0.5 else damVal.minFlo.realFalse
*/
void ReheatControllerFMU_eqFunction_1344(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1344};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[132]] /* damVal.minFlo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[143]] /* damVal.forMinFlo.y DISCRETE */)?0.5:(data->simulationInfo->realParameter[295] /* damVal.minFlo.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1345
type: SIMPLE_ASSIGN
damVal.or4.y = damVal.or3.y or damVal.forMinFlo.y
*/
void ReheatControllerFMU_eqFunction_1345(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1345};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[156]] /* damVal.or4.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[155]] /* damVal.or3.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[143]] /* damVal.forMinFlo.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1346
type: SIMPLE_ASSIGN
damVal.forMinFlo1.y = oveFloSet == 4
*/
void ReheatControllerFMU_eqFunction_1346(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1346};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[144]] /* damVal.forMinFlo1.y DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 4));
  TRACE_POP
}
/*
equation index: 1347
type: SIMPLE_ASSIGN
damVal.heaMax.y = if damVal.forMinFlo1.y then damVal.heaMax.realTrue else damVal.heaMax.realFalse
*/
void ReheatControllerFMU_eqFunction_1347(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1347};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[121]] /* damVal.heaMax.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[144]] /* damVal.forMinFlo1.y DISCRETE */)?(data->simulationInfo->realParameter[279] /* damVal.heaMax.realTrue PARAM */):(data->simulationInfo->realParameter[278] /* damVal.heaMax.realFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1348
type: SIMPLE_ASSIGN
damVal.add4.y = damVal.minFlo.y + damVal.heaMax.y
*/
void ReheatControllerFMU_eqFunction_1348(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1348};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[80]] /* damVal.add4.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[132]] /* damVal.minFlo.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[121]] /* damVal.heaMax.y variable */);
  TRACE_POP
}
/*
equation index: 1349
type: SIMPLE_ASSIGN
damVal.add2.y = damVal.cooMax.y + damVal.add4.y
*/
void ReheatControllerFMU_eqFunction_1349(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1349};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[79]] /* damVal.add2.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[120]] /* damVal.cooMax.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[80]] /* damVal.add4.y variable */);
  TRACE_POP
}
/*
equation index: 1350
type: SIMPLE_ASSIGN
damVal.add1.y = damVal.zerFlo.y + damVal.add2.y
*/
void ReheatControllerFMU_eqFunction_1350(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1350};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[78]] /* damVal.add1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[141]] /* damVal.zerFlo.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[79]] /* damVal.add2.y variable */);
  TRACE_POP
}
/*
equation index: 1351
type: SIMPLE_ASSIGN
damVal.or1.y = damVal.or4.y or damVal.forMinFlo1.y
*/
void ReheatControllerFMU_eqFunction_1351(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1351};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[153]] /* damVal.or1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[156]] /* damVal.or4.y DISCRETE */) || (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[144]] /* damVal.forMinFlo1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1352
type: SIMPLE_ASSIGN
$whenCondition20 = not u1Fan
*/
void ReheatControllerFMU_eqFunction_1352(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1352};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* $whenCondition20 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */));
  TRACE_POP
}
/*
equation index: 1353
type: SIMPLE_ASSIGN
$whenCondition21 = u1Fan
*/
void ReheatControllerFMU_eqFunction_1353(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1353};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* $whenCondition21 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */);
  TRACE_POP
}
/*
equation index: 1354
type: SIMPLE_ASSIGN
$whenCondition3 = time >= pre(damVal.truFalHol1.entryTimeFalse) and time >= pre(damVal.truFalHol1.entryTimeTrue) + 600.0
*/
void ReheatControllerFMU_eqFunction_1354(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1354};
  modelica_boolean tmp85;
  modelica_real tmp86;
  modelica_real tmp87;
  modelica_boolean tmp88;
  modelica_real tmp89;
  modelica_real tmp90;
  tmp86 = 1.0;
  tmp87 = 1.0;
  relationhysteresis(data, &tmp85, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */), tmp86, tmp87, 19, GreaterEq, GreaterEqZC);
  tmp89 = 1.0;
  tmp90 = 601.0;
  relationhysteresis(data, &tmp88, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0, tmp89, tmp90, 20, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[22]] /* $whenCondition3 DISCRETE */) = (tmp85 && tmp88);
  TRACE_POP
}
/*
equation index: 1355
type: SIMPLE_ASSIGN
$whenCondition6 = time >= pre(damVal.truFalHol.entryTimeFalse) and time >= pre(damVal.truFalHol.entryTimeTrue) + 600.0
*/
void ReheatControllerFMU_eqFunction_1355(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1355};
  modelica_boolean tmp91;
  modelica_real tmp92;
  modelica_real tmp93;
  modelica_boolean tmp94;
  modelica_real tmp95;
  modelica_real tmp96;
  tmp92 = 1.0;
  tmp93 = 1.0;
  relationhysteresis(data, &tmp91, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */), tmp92, tmp93, 17, GreaterEq, GreaterEqZC);
  tmp95 = 1.0;
  tmp96 = 601.0;
  relationhysteresis(data, &tmp94, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0, tmp95, tmp96, 18, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[55]] /* $whenCondition6 DISCRETE */) = (tmp91 && tmp94);
  TRACE_POP
}
/*
equation index: 1356
type: SIMPLE_ASSIGN
$whenCondition9 = timSup.truDel.u
*/
void ReheatControllerFMU_eqFunction_1356(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1356};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[73]] /* $whenCondition9 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */);
  TRACE_POP
}
/*
equation index: 1357
type: SIMPLE_ASSIGN
$whenCondition8 = not timSup.truDel.u
*/
void ReheatControllerFMU_eqFunction_1357(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1357};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[72]] /* $whenCondition8 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */));
  TRACE_POP
}
/*
equation index: 1358
type: SIMPLE_ASSIGN
$whenCondition7 = time >= pre(timSup.truDel.t_next)
*/
void ReheatControllerFMU_eqFunction_1358(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1358};
  modelica_boolean tmp97;
  modelica_real tmp98;
  modelica_real tmp99;
  tmp98 = 1.0;
  tmp99 = 1.0;
  relationhysteresis(data, &tmp97, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */), tmp98, tmp99, 16, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[66]] /* $whenCondition7 DISCRETE */) = tmp97;
  TRACE_POP
}
/*
equation index: 1359
type: WHEN

when {} then
  timSup.truDel.t_next = time + timSup.truDel.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1359(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1359};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[220]] /* timSup.truDel.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[73]] /* $whenCondition9 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[73] /* $whenCondition9 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[220]] /* timSup.truDel.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[72]] /* $whenCondition8 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[72] /* $whenCondition8 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[220]] /* timSup.truDel.t_next DISCRETE */) = (data->simulationInfo->realParameter[457] /* timSup.truDel.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[66]] /* $whenCondition7 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[66] /* $whenCondition7 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[220]] /* timSup.truDel.t_next DISCRETE */) = (data->simulationInfo->realParameter[457] /* timSup.truDel.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1363
type: WHEN

when {} then
  timSup.truDel.y = if not timSup.truDel.delayTime > 0.0 then timSup.truDel.u else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1363(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1363};
  modelica_boolean tmp100;
  modelica_boolean tmp101;
  if(0)
  {
    tmp100 = Greater((data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */) = ((!tmp100)?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[73]] /* $whenCondition9 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[73] /* $whenCondition9 DISCRETE */) /* edge */))
  {
    tmp101 = Greater((data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */) = (!tmp101);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[72]] /* $whenCondition8 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[72] /* $whenCondition8 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[66]] /* $whenCondition7 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[66] /* $whenCondition7 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1367
type: SIMPLE_ASSIGN
timSup.swi.y = smooth(0, if timSup.truDel.y then timSup.sub1.y else 0.0)
*/
void ReheatControllerFMU_eqFunction_1367(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1367};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[187]] /* timSup.swi.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[185]] /* timSup.sub1.y variable */):0.0);
  TRACE_POP
}
/*
equation index: 1368
type: SIMPLE_ASSIGN
timSup.abs1.y = abs(timSup.swi.y)
*/
void ReheatControllerFMU_eqFunction_1368(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1368};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */) = fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[187]] /* timSup.swi.y variable */));
  TRACE_POP
}
/*
equation index: 1369
type: SIMPLE_ASSIGN
timSup.greThr.greHys.y = not pre(timSup.greThr.greHys.y) and timSup.abs1.y > 0.25 or pre(timSup.greThr.greHys.y) and timSup.abs1.y > 0.125
*/
void ReheatControllerFMU_eqFunction_1369(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1369};
  modelica_boolean tmp102;
  modelica_real tmp103;
  modelica_real tmp104;
  modelica_boolean tmp105;
  modelica_real tmp106;
  modelica_real tmp107;
  tmp103 = 1.0;
  tmp104 = 0.25;
  relationhysteresis(data, &tmp102, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.25, tmp103, tmp104, 36, Greater, GreaterZC);
  tmp106 = 1.0;
  tmp107 = 0.125;
  relationhysteresis(data, &tmp105, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.125, tmp106, tmp107, 37, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */)) && tmp102) || ((data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */) && tmp105));
  TRACE_POP
}
/*
equation index: 1370
type: SIMPLE_ASSIGN
$whenCondition16 = timSup.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_1370(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1370};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition16 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1371
type: WHEN

when {} then
  timSup.lat.y = not $whenCondition15 and timSup.greThr.greHys.y;
end when;
*/
void ReheatControllerFMU_eqFunction_1371(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1371};
  if(0)
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[7]] /* $whenCondition16 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[7] /* $whenCondition16 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[6] /* $whenCondition15 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1373
type: SIMPLE_ASSIGN
timSup.edg.u = timSup.lat.y
*/
void ReheatControllerFMU_eqFunction_1373(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1373};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[207]] /* timSup.edg.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1374
type: SIMPLE_ASSIGN
$whenCondition10 = timSup.edg.u and not pre(timSup.edg.u)
*/
void ReheatControllerFMU_eqFunction_1374(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1374};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[207]] /* timSup.edg.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[207] /* timSup.edg.u DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1375
type: WHEN

when {$whenCondition10} then
  timSup.triSam1.y = TZon;
end when;
*/
void ReheatControllerFMU_eqFunction_1375(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1375};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition10 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[219]] /* timSup.triSam1.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */);
  }
  TRACE_POP
}
/*
equation index: 1376
type: WHEN

when {$whenCondition10} then
  timSup.triSam.y = TCooSet;
end when;
*/
void ReheatControllerFMU_eqFunction_1376(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1376};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition10 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[218]] /* timSup.triSam.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */);
  }
  TRACE_POP
}
/*
equation index: 1377
type: SIMPLE_ASSIGN
timSup.temDif.y = timSup.triSam.y - timSup.triSam1.y
*/
void ReheatControllerFMU_eqFunction_1377(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1377};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[188]] /* timSup.temDif.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[218]] /* timSup.triSam.y DISCRETE */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[219]] /* timSup.triSam1.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1378
type: SIMPLE_ASSIGN
timSup.abs2.y = abs(timSup.temDif.y)
*/
void ReheatControllerFMU_eqFunction_1378(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1378};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[182]] /* timSup.abs2.y variable */) = fabs((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[188]] /* timSup.temDif.y variable */));
  TRACE_POP
}
/*
equation index: 1379
type: SIMPLE_ASSIGN
timSup.gai.y = timSup.gai.k * timSup.abs2.y
*/
void ReheatControllerFMU_eqFunction_1379(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1379};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[184]] /* timSup.gai.y variable */) = ((data->simulationInfo->realParameter[440] /* timSup.gai.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[182]] /* timSup.abs2.y variable */));
  TRACE_POP
}
/*
equation index: 1380
type: SIMPLE_ASSIGN
timSup.supTim.y = min(timSup.gai.y, timSup.maxSupTim.k)
*/
void ReheatControllerFMU_eqFunction_1380(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1380};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[186]] /* timSup.supTim.y variable */) = fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[184]] /* timSup.gai.y variable */),(data->simulationInfo->realParameter[445] /* timSup.maxSupTim.k PARAM */));
  TRACE_POP
}
/*
equation index: 1381
type: SIMPLE_ASSIGN
timSup.edg.y = $whenCondition10
*/
void ReheatControllerFMU_eqFunction_1381(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1381};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[208]] /* timSup.edg.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1382
type: SIMPLE_ASSIGN
$whenCondition13 = timSup.lat.y
*/
void ReheatControllerFMU_eqFunction_1382(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1382};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition13 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1383
type: SIMPLE_ASSIGN
$whenCondition12 = timSup.lat.y and time >= timSup.tim.t + pre(timSup.tim.entryTime)
*/
void ReheatControllerFMU_eqFunction_1383(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1383};
  modelica_boolean tmp108;
  modelica_real tmp109;
  modelica_real tmp110;
  tmp109 = 1.0;
  tmp110 = fabs((data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */)) + 1.0;
  relationhysteresis(data, &tmp108, data->localData[0]->timeValue, (data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) + (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */), tmp109, tmp110, 38, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) && tmp108);
  TRACE_POP
}
/*
equation index: 1384
type: SIMPLE_ASSIGN
$whenCondition11 = not timSup.lat.y
*/
void ReheatControllerFMU_eqFunction_1384(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1384};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1385
type: WHEN

when {$whenCondition13} then
  timSup.tim.entryTime = time;
end when;
*/
void ReheatControllerFMU_eqFunction_1385(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1385};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition13 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[4] /* $whenCondition13 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[217]] /* timSup.tim.entryTime DISCRETE */) = data->localData[0]->timeValue;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[3] /* $whenCondition12 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[217]] /* timSup.tim.entryTime DISCRETE */) = (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[2] /* $whenCondition11 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[217]] /* timSup.tim.entryTime DISCRETE */) = (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1388
type: WHEN

when {$whenCondition13} then
  timSup.tim.passed = timSup.tim.t <= 0.0;
end when;
*/
void ReheatControllerFMU_eqFunction_1388(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1388};
  modelica_boolean tmp111;
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[4]] /* $whenCondition13 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[4] /* $whenCondition13 DISCRETE */) /* edge */))
  {
    tmp111 = LessEq((data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[216]] /* timSup.tim.passed DISCRETE */) = tmp111;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[3] /* $whenCondition12 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[216]] /* timSup.tim.passed DISCRETE */) = 1 /* true */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[2]] /* $whenCondition11 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[2] /* $whenCondition11 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[216]] /* timSup.tim.passed DISCRETE */) = 0 /* false */;
  }
  TRACE_POP
}
/*
equation index: 1391
type: SIMPLE_ASSIGN
timSup.tim.y = if timSup.lat.y then time - timSup.tim.entryTime else 0.0
*/
void ReheatControllerFMU_eqFunction_1391(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1391};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[189]] /* timSup.tim.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */)?data->localData[0]->timeValue - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[217]] /* timSup.tim.entryTime DISCRETE */):0.0);
  TRACE_POP
}
/*
equation index: 1392
type: SIMPLE_ASSIGN
timSup.pre1.u = timSup.tim.y > timSup.supTim.y
*/
void ReheatControllerFMU_eqFunction_1392(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1392};
  modelica_boolean tmp112;
  modelica_real tmp113;
  modelica_real tmp114;
  tmp113 = 1.0;
  tmp114 = 1.0;
  relationhysteresis(data, &tmp112, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[189]] /* timSup.tim.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[186]] /* timSup.supTim.y variable */), tmp113, tmp114, 39, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[212]] /* timSup.pre1.u DISCRETE */) = tmp112;
  TRACE_POP
}
/*
equation index: 1393
type: SIMPLE_ASSIGN
$whenCondition14 = timSup.pre1.u
*/
void ReheatControllerFMU_eqFunction_1393(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1393};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition14 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[212]] /* timSup.pre1.u DISCRETE */);
  TRACE_POP
}
/*
equation index: 1394
type: WHEN

when {} then
  timSup.lat1.y = not $whenCondition10 and timSup.pre1.u;
end when;
*/
void ReheatControllerFMU_eqFunction_1394(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1394};
  if(0)
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[211]] /* timSup.lat1.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[212]] /* timSup.pre1.u DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[5]] /* $whenCondition14 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[5] /* $whenCondition14 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[1] /* $whenCondition10 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[211]] /* timSup.lat1.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[212]] /* timSup.pre1.u DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1396
type: SIMPLE_ASSIGN
timSup.yAftSup = if timSup.lat.y then timSup.lat1.y else true
*/
void ReheatControllerFMU_eqFunction_1396(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1396};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[220]] /* timSup.yAftSup DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */)?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[211]] /* timSup.lat1.y DISCRETE */):1 /* true */);
  TRACE_POP
}
/*
equation index: 1397
type: SIMPLE_ASSIGN
$whenCondition19 = time >= pre(ala.fanIni.t_next)
*/
void ReheatControllerFMU_eqFunction_1397(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1397};
  modelica_boolean tmp115;
  modelica_real tmp116;
  modelica_real tmp117;
  tmp116 = 1.0;
  tmp117 = 1.0;
  relationhysteresis(data, &tmp115, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */), tmp116, tmp117, 15, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition19 DISCRETE */) = tmp115;
  TRACE_POP
}
/*
equation index: 1398
type: WHEN

when {} then
  ala.fanIni.t_next = if not ala.fanIni.delayOnInit then ala.fanIni.t_past else time + ala.fanIni.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1398(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1398};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[192]] /* ala.fanIni.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[6] /* ala.fanIni.delayOnInit PARAM */))?(data->simulationInfo->realParameter[57] /* ala.fanIni.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* $whenCondition21 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[13] /* $whenCondition21 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[192]] /* ala.fanIni.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* $whenCondition20 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[12] /* $whenCondition20 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[192]] /* ala.fanIni.t_next DISCRETE */) = (data->simulationInfo->realParameter[57] /* ala.fanIni.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition19 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[10] /* $whenCondition19 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[192]] /* ala.fanIni.t_next DISCRETE */) = (data->simulationInfo->realParameter[57] /* ala.fanIni.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1402
type: WHEN

when {} then
  ala.fanIni.y = if not (ala.fanIni.delayOnInit and ala.fanIni.delayTime > 0.0) then u1Fan else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1402(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1402};
  modelica_boolean tmp118;
  modelica_boolean tmp119;
  if(0)
  {
    tmp118 = Greater((data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[6] /* ala.fanIni.delayOnInit PARAM */) && tmp118))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* $whenCondition21 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[13] /* $whenCondition21 DISCRETE */) /* edge */))
  {
    tmp119 = Greater((data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */) = (!tmp119);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* $whenCondition20 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[12] /* $whenCondition20 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition19 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[10] /* $whenCondition19 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */);
  }
  TRACE_POP
}
/*
equation index: 1406
type: SIMPLE_ASSIGN
$whenCondition22 = time >= pre(ala.truDel7.t_next)
*/
void ReheatControllerFMU_eqFunction_1406(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1406};
  modelica_boolean tmp120;
  modelica_real tmp121;
  modelica_real tmp122;
  tmp121 = 1.0;
  tmp122 = 1.0;
  relationhysteresis(data, &tmp120, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */), tmp121, tmp122, 14, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* $whenCondition22 DISCRETE */) = tmp120;
  TRACE_POP
}
/*
equation index: 1407
type: SIMPLE_ASSIGN
$whenCondition25 = time >= pre(ala.truDel6.t_next)
*/
void ReheatControllerFMU_eqFunction_1407(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1407};
  modelica_boolean tmp123;
  modelica_real tmp124;
  modelica_real tmp125;
  tmp124 = 1.0;
  tmp125 = 1.0;
  relationhysteresis(data, &tmp123, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */), tmp124, tmp125, 13, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[17]] /* $whenCondition25 DISCRETE */) = tmp123;
  TRACE_POP
}
/*
equation index: 1408
type: SIMPLE_ASSIGN
$whenCondition28 = time >= pre(ala.truDel5.t_next)
*/
void ReheatControllerFMU_eqFunction_1408(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1408};
  modelica_boolean tmp126;
  modelica_real tmp127;
  modelica_real tmp128;
  tmp127 = 1.0;
  tmp128 = 1.0;
  relationhysteresis(data, &tmp126, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */), tmp127, tmp128, 12, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[20]] /* $whenCondition28 DISCRETE */) = tmp126;
  TRACE_POP
}
/*
equation index: 1409
type: SIMPLE_ASSIGN
$whenCondition31 = time >= pre(ala.truDel4.t_next)
*/
void ReheatControllerFMU_eqFunction_1409(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1409};
  modelica_boolean tmp129;
  modelica_real tmp130;
  modelica_real tmp131;
  tmp130 = 1.0;
  tmp131 = 1.0;
  relationhysteresis(data, &tmp129, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */), tmp130, tmp131, 11, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[24]] /* $whenCondition31 DISCRETE */) = tmp129;
  TRACE_POP
}
/*
equation index: 1410
type: SIMPLE_ASSIGN
$whenCondition34 = time >= pre(ala.truDel3.t_next)
*/
void ReheatControllerFMU_eqFunction_1410(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1410};
  modelica_boolean tmp132;
  modelica_real tmp133;
  modelica_real tmp134;
  tmp133 = 1.0;
  tmp134 = 1.0;
  relationhysteresis(data, &tmp132, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */), tmp133, tmp134, 10, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[27]] /* $whenCondition34 DISCRETE */) = tmp132;
  TRACE_POP
}
/*
equation index: 1411
type: SIMPLE_ASSIGN
$whenCondition37 = time >= pre(ala.truDel2.t_next)
*/
void ReheatControllerFMU_eqFunction_1411(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1411};
  modelica_boolean tmp135;
  modelica_real tmp136;
  modelica_real tmp137;
  tmp136 = 1.0;
  tmp137 = 1.0;
  relationhysteresis(data, &tmp135, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */), tmp136, tmp137, 9, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[30]] /* $whenCondition37 DISCRETE */) = tmp135;
  TRACE_POP
}
/*
equation index: 1412
type: WHEN

when {} then
  ala.truDel2.y = if not (ala.truDel2.delayOnInit and ala.truDel2.delayTime > 0.0) then $whenCondition39 else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1412(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1412};
  modelica_boolean tmp138;
  modelica_boolean tmp139;
  if(0)
  {
    tmp138 = Greater((data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[34] /* ala.truDel2.delayOnInit PARAM */) && tmp138))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[32] /* $whenCondition39 DISCRETE */) /* edge */))
  {
    tmp139 = Greater((data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */) = (!tmp139);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[31]] /* $whenCondition38 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[31] /* $whenCondition38 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[30]] /* $whenCondition37 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[30] /* $whenCondition37 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1416
type: SIMPLE_ASSIGN
yFloSenAla = if ala.truDel2.y then 3 else ala.booToInt2.integerFalse
*/
void ReheatControllerFMU_eqFunction_1416(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1416};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[38]] /* yFloSenAla DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */)?((modelica_integer) 3):(data->simulationInfo->integerParameter[9] /* ala.booToInt2.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1417
type: WHEN

when {} then
  ala.truDel2.t_next = if not ala.truDel2.delayOnInit then ala.truDel2.t_past else time + ala.truDel2.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1417(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1417};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[195]] /* ala.truDel2.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[34] /* ala.truDel2.delayOnInit PARAM */))?(data->simulationInfo->realParameter[101] /* ala.truDel2.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[32] /* $whenCondition39 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[195]] /* ala.truDel2.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[31]] /* $whenCondition38 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[31] /* $whenCondition38 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[195]] /* ala.truDel2.t_next DISCRETE */) = (data->simulationInfo->realParameter[101] /* ala.truDel2.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[30]] /* $whenCondition37 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[30] /* $whenCondition37 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[195]] /* ala.truDel2.t_next DISCRETE */) = (data->simulationInfo->realParameter[101] /* ala.truDel2.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1421
type: SIMPLE_ASSIGN
$whenCondition40 = time >= pre(ala.truDel1.t_next)
*/
void ReheatControllerFMU_eqFunction_1421(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1421};
  modelica_boolean tmp140;
  modelica_real tmp141;
  modelica_real tmp142;
  tmp141 = 1.0;
  tmp142 = 1.0;
  relationhysteresis(data, &tmp140, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */), tmp141, tmp142, 8, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[34]] /* $whenCondition40 DISCRETE */) = tmp140;
  TRACE_POP
}
/*
equation index: 1422
type: SIMPLE_ASSIGN
$whenCondition43 = time >= pre(ala.truDel.t_next)
*/
void ReheatControllerFMU_eqFunction_1422(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1422};
  modelica_boolean tmp143;
  modelica_real tmp144;
  modelica_real tmp145;
  tmp144 = 1.0;
  tmp145 = 1.0;
  relationhysteresis(data, &tmp143, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */), tmp144, tmp145, 7, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[37]] /* $whenCondition43 DISCRETE */) = tmp143;
  TRACE_POP
}
/*
equation index: 1423
type: SIMPLE_ASSIGN
$whenCondition46 = time >= pre(conLoo.disHea.t_next)
*/
void ReheatControllerFMU_eqFunction_1423(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1423};
  modelica_boolean tmp146;
  modelica_real tmp147;
  modelica_real tmp148;
  tmp147 = 1.0;
  tmp148 = 1.0;
  relationhysteresis(data, &tmp146, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */), tmp147, tmp148, 6, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[40]] /* $whenCondition46 DISCRETE */) = tmp146;
  TRACE_POP
}
/*
equation index: 1424
type: WHEN

when {} then
  conLoo.disHea.y = if not (conLoo.disHea.delayOnInit and conLoo.disHea.delayTime > 0.0) then conLoo.zerCon1.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1424(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1424};
  modelica_boolean tmp149;
  modelica_boolean tmp150;
  if(0)
  {
    tmp149 = Greater((data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[53] /* conLoo.disHea.delayOnInit PARAM */) && tmp149))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[42]] /* $whenCondition48 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[42] /* $whenCondition48 DISCRETE */) /* edge */))
  {
    tmp150 = Greater((data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) = (!tmp150);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[41]] /* $whenCondition47 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[41] /* $whenCondition47 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[40]] /* $whenCondition46 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[40] /* $whenCondition46 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1428
type: SIMPLE_ASSIGN
conLoo.disHeaCon.y = conLoo.disHea.y and not conLoo.enaHeaLoo.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1428(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1428};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[132]] /* conLoo.disHeaCon.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[134]] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1429
type: SIMPLE_ASSIGN
conLoo.zerHea.y = if conLoo.disHeaCon.y then 0.0 else 1.0
*/
void ReheatControllerFMU_eqFunction_1429(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1429};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[74]] /* conLoo.zerHea.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[132]] /* conLoo.disHeaCon.y DISCRETE */)?0.0:1.0);
  TRACE_POP
}
/*
equation index: 1430
type: SIMPLE_ASSIGN
conLoo.yHea = conLoo.conHea.y * conLoo.zerHea.y
*/
void ReheatControllerFMU_eqFunction_1430(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1430};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[74]] /* conLoo.zerHea.y variable */));
  TRACE_POP
}
/*
equation index: 1431
type: SIMPLE_ASSIGN
damVal.greThr2.greHys.y = not pre(damVal.greThr2.greHys.y) and conLoo.yHea > 0.01 or pre(damVal.greThr2.greHys.y) and conLoo.yHea > 0.002
*/
void ReheatControllerFMU_eqFunction_1431(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1431};
  modelica_boolean tmp151;
  modelica_real tmp152;
  modelica_real tmp153;
  modelica_boolean tmp154;
  modelica_real tmp155;
  modelica_real tmp156;
  tmp152 = 1.0;
  tmp153 = 0.01;
  relationhysteresis(data, &tmp151, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.01, tmp152, tmp153, 52, Greater, GreaterZC);
  tmp155 = 1.0;
  tmp156 = 0.002;
  relationhysteresis(data, &tmp154, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.002, tmp155, tmp156, 53, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[149]] /* damVal.greThr2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */)) && tmp151) || ((data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */) && tmp154));
  TRACE_POP
}
/*
equation index: 1432
type: SIMPLE_ASSIGN
damVal.truFalHol.not_u = not damVal.greThr2.greHys.y
*/
void ReheatControllerFMU_eqFunction_1432(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1432};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[157]] /* damVal.truFalHol.not_u DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[149]] /* damVal.greThr2.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1433
type: SIMPLE_ASSIGN
damVal.truFalHol.u = not damVal.truFalHol.not_u
*/
void ReheatControllerFMU_eqFunction_1433(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1433};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[157]] /* damVal.truFalHol.not_u DISCRETE */));
  TRACE_POP
}
/*
equation index: 1434
type: SIMPLE_ASSIGN
$whenCondition4 = damVal.truFalHol.u and not pre(damVal.truFalHol.u)
*/
void ReheatControllerFMU_eqFunction_1434(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1434};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[33]] /* $whenCondition4 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[159] /* damVal.truFalHol.u DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1435
type: SIMPLE_ASSIGN
$whenCondition5 = damVal.truFalHol.not_u and not pre(damVal.truFalHol.not_u)
*/
void ReheatControllerFMU_eqFunction_1435(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1435};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[44]] /* $whenCondition5 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[157]] /* damVal.truFalHol.not_u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[157] /* damVal.truFalHol.not_u DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1436
type: WHEN

when {} then
  damVal.truFalHol.y = damVal.truFalHol.u;
end when;
*/
void ReheatControllerFMU_eqFunction_1436(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1436};
  modelica_boolean tmp157;
  modelica_boolean tmp158;
  if(0)
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[55]] /* $whenCondition6 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[55] /* $whenCondition6 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[44]] /* $whenCondition5 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[44] /* $whenCondition5 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[33]] /* $whenCondition4 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[33] /* $whenCondition4 DISCRETE */) /* edge */))
  {
    tmp157 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
    tmp158 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */) = ((tmp157 && tmp158)?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */):(data->simulationInfo->booleanVarsPre[160] /* damVal.truFalHol.y DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1438
type: SIMPLE_ASSIGN
damVal.truFalHol.not_y = not damVal.truFalHol.y
*/
void ReheatControllerFMU_eqFunction_1438(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1438};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1439
type: SIMPLE_ASSIGN
$whenCondition74 = damVal.and1.y or not damVal.truFalHol.not_y
*/
void ReheatControllerFMU_eqFunction_1439(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1439};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[71]] /* $whenCondition74 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[137]] /* damVal.and1.y DISCRETE */) || (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1440
type: SIMPLE_ASSIGN
damVal.or2.y = $whenCondition74
*/
void ReheatControllerFMU_eqFunction_1440(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1440};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[154]] /* damVal.or2.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[71]] /* $whenCondition74 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1441
type: WHEN

when {} then
  damVal.truFalHol.entryTimeTrue = if damVal.truFalHol.y then time else pre(damVal.truFalHol.entryTimeTrue);
end when;
*/
void ReheatControllerFMU_eqFunction_1441(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1441};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[204]] /* damVal.truFalHol.entryTimeTrue DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[55]] /* $whenCondition6 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[55] /* $whenCondition6 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[44]] /* $whenCondition5 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[44] /* $whenCondition5 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[33]] /* $whenCondition4 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[33] /* $whenCondition4 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[204]] /* damVal.truFalHol.entryTimeTrue DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[160] /* damVal.truFalHol.y DISCRETE */)))?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1443
type: WHEN

when {} then
  damVal.truFalHol.entryTimeFalse = if damVal.truFalHol.not_y then time else pre(damVal.truFalHol.entryTimeFalse);
end when;
*/
void ReheatControllerFMU_eqFunction_1443(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1443};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[203]] /* damVal.truFalHol.entryTimeFalse DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[55]] /* $whenCondition6 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[55] /* $whenCondition6 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[44]] /* $whenCondition5 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[44] /* $whenCondition5 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[33]] /* $whenCondition4 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[33] /* $whenCondition4 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[203]] /* damVal.truFalHol.entryTimeFalse DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[158] /* damVal.truFalHol.not_y DISCRETE */)))?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1445
type: SIMPLE_ASSIGN
$cse5 = max(0.0, conLoo.yHea)
*/
void ReheatControllerFMU_eqFunction_1445(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1445};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* $cse5 variable */) = fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */));
  TRACE_POP
}
/*
equation index: 1446
type: SIMPLE_ASSIGN
damVal.conTDisHeaSet.xLim = min(0.5, $cse5)
*/
void ReheatControllerFMU_eqFunction_1446(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1446};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[102]] /* damVal.conTDisHeaSet.xLim variable */) = fmin(0.5,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[12]] /* $cse5 variable */));
  TRACE_POP
}
/*
equation index: 1447
type: SIMPLE_ASSIGN
damVal.conTDisHeaSet.y = damVal.conTDisHeaSet.a + damVal.conTDisHeaSet.b * damVal.conTDisHeaSet.xLim
*/
void ReheatControllerFMU_eqFunction_1447(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1447};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[103]] /* damVal.conTDisHeaSet.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[100]] /* damVal.conTDisHeaSet.a variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[101]] /* damVal.conTDisHeaSet.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[102]] /* damVal.conTDisHeaSet.xLim variable */));
  TRACE_POP
}
/*
equation index: 1448
type: SIMPLE_ASSIGN
$cse4 = max(0.5, conLoo.yHea)
*/
void ReheatControllerFMU_eqFunction_1448(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1448};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* $cse4 variable */) = fmax(0.5,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */));
  TRACE_POP
}
/*
equation index: 1449
type: SIMPLE_ASSIGN
damVal.lin3.xLim = min(1.0, $cse4)
*/
void ReheatControllerFMU_eqFunction_1449(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1449};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[128]] /* damVal.lin3.xLim variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[11]] /* $cse4 variable */));
  TRACE_POP
}
/*
equation index: 1450
type: SIMPLE_ASSIGN
damVal.lin3.y = damVal.lin3.a + damVal.lin3.b * damVal.lin3.xLim
*/
void ReheatControllerFMU_eqFunction_1450(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1450};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[129]] /* damVal.lin3.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[126]] /* damVal.lin3.a variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[127]] /* damVal.lin3.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[128]] /* damVal.lin3.xLim variable */));
  TRACE_POP
}
/*
equation index: 1451
type: SIMPLE_ASSIGN
damVal.swi2.y = smooth(0, if damVal.gre.greHys.y then damVal.lin3.y else actAirSet.VActHeaMin_flow)
*/
void ReheatControllerFMU_eqFunction_1451(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1451};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[136]] /* damVal.swi2.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[146]] /* damVal.gre.greHys.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[129]] /* damVal.lin3.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[26]] /* actAirSet.VActHeaMin_flow variable */));
  TRACE_POP
}
/*
equation index: 1452
type: WHEN

when {} then
  conLoo.disHea.t_next = if not conLoo.disHea.delayOnInit then conLoo.disHea.t_past else time + conLoo.disHea.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1452(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1452};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[202]] /* conLoo.disHea.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[53] /* conLoo.disHea.delayOnInit PARAM */))?(data->simulationInfo->realParameter[169] /* conLoo.disHea.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[42]] /* $whenCondition48 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[42] /* $whenCondition48 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[202]] /* conLoo.disHea.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[41]] /* $whenCondition47 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[41] /* $whenCondition47 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[202]] /* conLoo.disHea.t_next DISCRETE */) = (data->simulationInfo->realParameter[169] /* conLoo.disHea.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[40]] /* $whenCondition46 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[40] /* $whenCondition46 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[202]] /* conLoo.disHea.t_next DISCRETE */) = (data->simulationInfo->realParameter[169] /* conLoo.disHea.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1456
type: SIMPLE_ASSIGN
$whenCondition49 = time >= pre(conLoo.disCoo.t_next)
*/
void ReheatControllerFMU_eqFunction_1456(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1456};
  modelica_boolean tmp159;
  modelica_real tmp160;
  modelica_real tmp161;
  tmp160 = 1.0;
  tmp161 = 1.0;
  relationhysteresis(data, &tmp159, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */), tmp160, tmp161, 5, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* $whenCondition49 DISCRETE */) = tmp159;
  TRACE_POP
}
/*
equation index: 1457
type: WHEN

when {} then
  conLoo.disCoo.y = if not (conLoo.disCoo.delayOnInit and conLoo.disCoo.delayTime > 0.0) then conLoo.zerCon.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1457(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1457};
  modelica_boolean tmp162;
  modelica_boolean tmp163;
  if(0)
  {
    tmp162 = Greater((data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[52] /* conLoo.disCoo.delayOnInit PARAM */) && tmp162))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[46]] /* $whenCondition51 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[46] /* $whenCondition51 DISCRETE */) /* edge */))
  {
    tmp163 = Greater((data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) = (!tmp163);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* $whenCondition50 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[45] /* $whenCondition50 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* $whenCondition49 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[43] /* $whenCondition49 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1461
type: SIMPLE_ASSIGN
conLoo.disCooCon.y = conLoo.disCoo.y and not conLoo.enaCooLoo.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1461(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1461};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[129]] /* conLoo.disCooCon.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[133]] /* conLoo.enaCooLoo.lesHys.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1462
type: SIMPLE_ASSIGN
conLoo.zerCoo.y = if conLoo.disCooCon.y then 0.0 else 1.0
*/
void ReheatControllerFMU_eqFunction_1462(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1462};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[73]] /* conLoo.zerCoo.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[129]] /* conLoo.disCooCon.y DISCRETE */)?0.0:1.0);
  TRACE_POP
}
/*
equation index: 1463
type: SIMPLE_ASSIGN
conLoo.yCoo = conLoo.conCoo.y * conLoo.zerCoo.y
*/
void ReheatControllerFMU_eqFunction_1463(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1463};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[73]] /* conLoo.zerCoo.y variable */));
  TRACE_POP
}
/*
equation index: 1464
type: SIMPLE_ASSIGN
damVal.greThr1.greHys.y = not pre(damVal.greThr1.greHys.y) and conLoo.yCoo > 0.01 or pre(damVal.greThr1.greHys.y) and conLoo.yCoo > 0.005
*/
void ReheatControllerFMU_eqFunction_1464(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1464};
  modelica_boolean tmp164;
  modelica_real tmp165;
  modelica_real tmp166;
  modelica_boolean tmp167;
  modelica_real tmp168;
  modelica_real tmp169;
  tmp165 = 1.0;
  tmp166 = 0.01;
  relationhysteresis(data, &tmp164, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.01, tmp165, tmp166, 62, Greater, GreaterZC);
  tmp168 = 1.0;
  tmp169 = 0.005;
  relationhysteresis(data, &tmp167, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.005, tmp168, tmp169, 63, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[148]] /* damVal.greThr1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */)) && tmp164) || ((data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */) && tmp167));
  TRACE_POP
}
/*
equation index: 1465
type: SIMPLE_ASSIGN
damVal.truFalHol1.not_u = not damVal.greThr1.greHys.y
*/
void ReheatControllerFMU_eqFunction_1465(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1465};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[161]] /* damVal.truFalHol1.not_u DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[148]] /* damVal.greThr1.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1466
type: SIMPLE_ASSIGN
damVal.truFalHol1.u = not damVal.truFalHol1.not_u
*/
void ReheatControllerFMU_eqFunction_1466(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1466};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[161]] /* damVal.truFalHol1.not_u DISCRETE */));
  TRACE_POP
}
/*
equation index: 1467
type: SIMPLE_ASSIGN
$whenCondition1 = damVal.truFalHol1.u and not pre(damVal.truFalHol1.u)
*/
void ReheatControllerFMU_eqFunction_1467(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1467};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[163] /* damVal.truFalHol1.u DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1468
type: SIMPLE_ASSIGN
$whenCondition2 = damVal.truFalHol1.not_u and not pre(damVal.truFalHol1.not_u)
*/
void ReheatControllerFMU_eqFunction_1468(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1468};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[161]] /* damVal.truFalHol1.not_u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[161] /* damVal.truFalHol1.not_u DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1469
type: WHEN

when {} then
  damVal.truFalHol1.y = damVal.truFalHol1.u;
end when;
*/
void ReheatControllerFMU_eqFunction_1469(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1469};
  modelica_boolean tmp170;
  modelica_boolean tmp171;
  if(0)
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[22]] /* $whenCondition3 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[22] /* $whenCondition3 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[11] /* $whenCondition2 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    tmp170 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
    tmp171 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */) = ((tmp170 && tmp171)?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */):(data->simulationInfo->booleanVarsPre[164] /* damVal.truFalHol1.y DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1471
type: SIMPLE_ASSIGN
damVal.truFalHol1.not_y = not damVal.truFalHol1.y
*/
void ReheatControllerFMU_eqFunction_1471(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1471};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1472
type: SIMPLE_ASSIGN
damVal.and4.y = not damVal.truFalHol1.not_y and damVal.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_1472(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1472};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[139]] /* damVal.and4.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[147]] /* damVal.greThr.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1473
type: SIMPLE_ASSIGN
damVal.and2.y = damVal.truFalHol1.not_y and damVal.truFalHol.not_y
*/
void ReheatControllerFMU_eqFunction_1473(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1473};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[138]] /* damVal.and2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1474
type: SIMPLE_ASSIGN
damVal.swi1.y = smooth(0, if damVal.and2.y then actAirSet.VActMin_flow else damVal.swi2.y)
*/
void ReheatControllerFMU_eqFunction_1474(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1474};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[135]] /* damVal.swi1.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[138]] /* damVal.and2.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[136]] /* damVal.swi2.y variable */));
  TRACE_POP
}
/*
equation index: 1475
type: WHEN

when {} then
  damVal.truFalHol1.entryTimeTrue = if damVal.truFalHol1.y then time else pre(damVal.truFalHol1.entryTimeTrue);
end when;
*/
void ReheatControllerFMU_eqFunction_1475(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1475};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[206]] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[22]] /* $whenCondition3 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[22] /* $whenCondition3 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[11] /* $whenCondition2 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[206]] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[164] /* damVal.truFalHol1.y DISCRETE */)))?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1477
type: WHEN

when {} then
  damVal.truFalHol1.entryTimeFalse = if damVal.truFalHol1.not_y then time else pre(damVal.truFalHol1.entryTimeFalse);
end when;
*/
void ReheatControllerFMU_eqFunction_1477(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1477};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[205]] /* damVal.truFalHol1.entryTimeFalse DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[22]] /* $whenCondition3 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[22] /* $whenCondition3 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[11] /* $whenCondition2 DISCRETE */) /* edge */) || ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[205]] /* damVal.truFalHol1.entryTimeFalse DISCRETE */) = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[162] /* damVal.truFalHol1.not_y DISCRETE */)))?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
  }
  TRACE_POP
}
/*
equation index: 1479
type: SIMPLE_ASSIGN
$cse3 = max(0.0, conLoo.yCoo)
*/
void ReheatControllerFMU_eqFunction_1479(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1479};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* $cse3 variable */) = fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */));
  TRACE_POP
}
/*
equation index: 1480
type: SIMPLE_ASSIGN
damVal.lin.xLim = min(1.0, $cse3)
*/
void ReheatControllerFMU_eqFunction_1480(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1480};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[124]] /* damVal.lin.xLim variable */) = fmin(1.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[10]] /* $cse3 variable */));
  TRACE_POP
}
/*
equation index: 1481
type: SIMPLE_ASSIGN
damVal.lin.y = actAirSet.VActMin_flow + damVal.lin.b * damVal.lin.xLim
*/
void ReheatControllerFMU_eqFunction_1481(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1481};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[125]] /* damVal.lin.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[123]] /* damVal.lin.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[124]] /* damVal.lin.xLim variable */));
  TRACE_POP
}
/*
equation index: 1482
type: SIMPLE_ASSIGN
damVal.swi5.y = smooth(0, if damVal.and4.y then actAirSet.VActMin_flow else damVal.lin.y)
*/
void ReheatControllerFMU_eqFunction_1482(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1482};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[138]] /* damVal.swi5.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[139]] /* damVal.and4.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[125]] /* damVal.lin.y variable */));
  TRACE_POP
}
/*
equation index: 1483
type: SIMPLE_ASSIGN
damVal.swi.y = smooth(0, if not damVal.truFalHol1.not_y then damVal.swi5.y else damVal.swi1.y)
*/
void ReheatControllerFMU_eqFunction_1483(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1483};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[134]] /* damVal.swi.y variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[138]] /* damVal.swi5.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[135]] /* damVal.swi1.y variable */));
  TRACE_POP
}
/*
equation index: 1484
type: SIMPLE_ASSIGN
VSet_flow = smooth(0, if damVal.or1.y then damVal.add1.y else damVal.swi.y)
*/
void ReheatControllerFMU_eqFunction_1484(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1484};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[153]] /* damVal.or1.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[78]] /* damVal.add1.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[134]] /* damVal.swi.y variable */));
  TRACE_POP
}
/*
equation index: 1485
type: SIMPLE_ASSIGN
ala.gai.y = 0.5 * VSet_flow
*/
void ReheatControllerFMU_eqFunction_1485(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1485};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) = (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */));
  TRACE_POP
}
/*
equation index: 1486
type: SIMPLE_ASSIGN
ala.les.lesHys.y = not pre(ala.les.lesHys.y) and VDis_flow < ala.gai.y or pre(ala.les.lesHys.y) and VDis_flow < ala.gai.y + 0.005
*/
void ReheatControllerFMU_eqFunction_1486(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1486};
  modelica_boolean tmp172;
  modelica_real tmp173;
  modelica_real tmp174;
  modelica_boolean tmp175;
  modelica_real tmp176;
  modelica_real tmp177;
  tmp173 = 1.0;
  tmp174 = 1.0;
  relationhysteresis(data, &tmp172, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */), tmp173, tmp174, 79, Less, LessZC);
  tmp176 = 1.0;
  tmp177 = 1.005;
  relationhysteresis(data, &tmp175, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) + 0.005, tmp176, tmp177, 80, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[104]] /* ala.les.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */)) && tmp172) || ((data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */) && tmp175));
  TRACE_POP
}
/*
equation index: 1487
type: SIMPLE_ASSIGN
$whenCondition45 = ala.les.lesHys.y and ala.fanIni.y
*/
void ReheatControllerFMU_eqFunction_1487(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1487};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[104]] /* ala.les.lesHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1488
type: SIMPLE_ASSIGN
$whenCondition44 = not $whenCondition45
*/
void ReheatControllerFMU_eqFunction_1488(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1488};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[38]] /* $whenCondition44 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */));
  TRACE_POP
}
/*
equation index: 1489
type: WHEN

when {} then
  ala.truDel.y = if not (ala.truDel.delayOnInit and ala.truDel.delayTime > 0.0) then $whenCondition45 else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1489(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1489};
  modelica_boolean tmp178;
  modelica_boolean tmp179;
  if(0)
  {
    tmp178 = Greater((data->simulationInfo->realParameter[96] /* ala.truDel.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[32] /* ala.truDel.delayOnInit PARAM */) && tmp178))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[39] /* $whenCondition45 DISCRETE */) /* edge */))
  {
    tmp179 = Greater((data->simulationInfo->realParameter[96] /* ala.truDel.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) = (!tmp179);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[38]] /* $whenCondition44 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[38] /* $whenCondition44 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[37]] /* $whenCondition43 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[37] /* $whenCondition43 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1493
type: WHEN

when {} then
  ala.truDel.t_next = if not ala.truDel.delayOnInit then ala.truDel.t_past else time + ala.truDel.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1493(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1493};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[193]] /* ala.truDel.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[32] /* ala.truDel.delayOnInit PARAM */))?(data->simulationInfo->realParameter[97] /* ala.truDel.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[96] /* ala.truDel.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[39] /* $whenCondition45 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[193]] /* ala.truDel.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[96] /* ala.truDel.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[38]] /* $whenCondition44 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[38] /* $whenCondition44 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[193]] /* ala.truDel.t_next DISCRETE */) = (data->simulationInfo->realParameter[97] /* ala.truDel.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[37]] /* $whenCondition43 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[37] /* $whenCondition43 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[193]] /* ala.truDel.t_next DISCRETE */) = (data->simulationInfo->realParameter[97] /* ala.truDel.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1497
type: SIMPLE_ASSIGN
ala.truDel.u = $whenCondition45
*/
void ReheatControllerFMU_eqFunction_1497(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1497};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[111]] /* ala.truDel.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1498
type: SIMPLE_ASSIGN
ala.greThr.greHys.y = not pre(ala.greThr.greHys.y) and VSet_flow > 0.005 or pre(ala.greThr.greHys.y) and VSet_flow > 0.0025
*/
void ReheatControllerFMU_eqFunction_1498(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1498};
  modelica_boolean tmp180;
  modelica_real tmp181;
  modelica_real tmp182;
  modelica_boolean tmp183;
  modelica_real tmp184;
  modelica_real tmp185;
  tmp181 = 1.0;
  tmp182 = 0.005;
  relationhysteresis(data, &tmp180, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.005, tmp181, tmp182, 81, Greater, GreaterZC);
  tmp184 = 1.0;
  tmp185 = 0.0025;
  relationhysteresis(data, &tmp183, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.0025, tmp184, tmp185, 82, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */)) && tmp180) || ((data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */) && tmp183));
  TRACE_POP
}
/*
equation index: 1499
type: SIMPLE_ASSIGN
$whenCondition24 = ala.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_1499(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1499};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* $whenCondition24 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1500
type: SIMPLE_ASSIGN
$whenCondition23 = not ala.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_1500(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1500};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* $whenCondition23 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1501
type: WHEN

when {} then
  ala.truDel7.t_next = if not ala.truDel7.delayOnInit then ala.truDel7.t_past else time + ala.truDel7.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1501(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1501};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[200]] /* ala.truDel7.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[39] /* ala.truDel7.delayOnInit PARAM */))?(data->simulationInfo->realParameter[111] /* ala.truDel7.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[110] /* ala.truDel7.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* $whenCondition24 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[16] /* $whenCondition24 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[200]] /* ala.truDel7.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[110] /* ala.truDel7.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* $whenCondition23 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[15] /* $whenCondition23 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[200]] /* ala.truDel7.t_next DISCRETE */) = (data->simulationInfo->realParameter[111] /* ala.truDel7.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* $whenCondition22 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[14] /* $whenCondition22 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[200]] /* ala.truDel7.t_next DISCRETE */) = (data->simulationInfo->realParameter[111] /* ala.truDel7.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1505
type: WHEN

when {} then
  ala.truDel7.y = if not (ala.truDel7.delayOnInit and ala.truDel7.delayTime > 0.0) then ala.greThr.greHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1505(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1505};
  modelica_boolean tmp186;
  modelica_boolean tmp187;
  if(0)
  {
    tmp186 = Greater((data->simulationInfo->realParameter[110] /* ala.truDel7.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[39] /* ala.truDel7.delayOnInit PARAM */) && tmp186))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* $whenCondition24 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[16] /* $whenCondition24 DISCRETE */) /* edge */))
  {
    tmp187 = Greater((data->simulationInfo->realParameter[110] /* ala.truDel7.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) = (!tmp187);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* $whenCondition23 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[15] /* $whenCondition23 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* $whenCondition22 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[14] /* $whenCondition22 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1509
type: SIMPLE_ASSIGN
ala.and2.y = ala.truDel.y and ala.truDel7.y
*/
void ReheatControllerFMU_eqFunction_1509(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1509};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[84]] /* ala.and2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1510
type: SIMPLE_ASSIGN
ala.and4.y = ala.and2.y and ala.greThr1.y
*/
void ReheatControllerFMU_eqFunction_1510(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1510};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[85]] /* ala.and4.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[84]] /* ala.and2.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[99]] /* ala.greThr1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1511
type: SIMPLE_ASSIGN
ala.not1.y = not (ala.and4.y and ala.isOcc.y)
*/
void ReheatControllerFMU_eqFunction_1511(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1511};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[107]] /* ala.not1.y DISCRETE */) = (!((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[85]] /* ala.and4.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[101]] /* ala.isOcc.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1512
type: SIMPLE_ASSIGN
ala.truDel7.u = ala.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_1512(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1512};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[125]] /* ala.truDel7.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1513
type: SIMPLE_ASSIGN
ala.gai1.y = 0.7 * VSet_flow
*/
void ReheatControllerFMU_eqFunction_1513(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1513};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */) = (0.7) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */));
  TRACE_POP
}
/*
equation index: 1514
type: SIMPLE_ASSIGN
ala.gre.greHys.y = not pre(ala.gre.greHys.y) and ala.gai1.y > VDis_flow or pre(ala.gre.greHys.y) and ala.gai1.y > VDis_flow - 0.005
*/
void ReheatControllerFMU_eqFunction_1514(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1514};
  modelica_boolean tmp188;
  modelica_real tmp189;
  modelica_real tmp190;
  modelica_boolean tmp191;
  modelica_real tmp192;
  modelica_real tmp193;
  tmp189 = 1.0;
  tmp190 = 1.0;
  relationhysteresis(data, &tmp188, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), tmp189, tmp190, 83, Greater, GreaterZC);
  tmp192 = 1.0;
  tmp193 = 1.005;
  relationhysteresis(data, &tmp191, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) - 0.005, tmp192, tmp193, 84, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[95]] /* ala.gre.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */)) && tmp188) || ((data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */) && tmp191));
  TRACE_POP
}
/*
equation index: 1515
type: SIMPLE_ASSIGN
$whenCondition42 = ala.gre.greHys.y and ala.fanIni.y
*/
void ReheatControllerFMU_eqFunction_1515(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1515};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[95]] /* ala.gre.greHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1516
type: SIMPLE_ASSIGN
$whenCondition41 = not $whenCondition42
*/
void ReheatControllerFMU_eqFunction_1516(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1516};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[35]] /* $whenCondition41 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */));
  TRACE_POP
}
/*
equation index: 1517
type: WHEN

when {} then
  ala.truDel1.y = if not (ala.truDel1.delayOnInit and ala.truDel1.delayTime > 0.0) then $whenCondition42 else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1517(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1517};
  modelica_boolean tmp194;
  modelica_boolean tmp195;
  if(0)
  {
    tmp194 = Greater((data->simulationInfo->realParameter[98] /* ala.truDel1.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[33] /* ala.truDel1.delayOnInit PARAM */) && tmp194))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[36] /* $whenCondition42 DISCRETE */) /* edge */))
  {
    tmp195 = Greater((data->simulationInfo->realParameter[98] /* ala.truDel1.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */) = (!tmp195);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[35]] /* $whenCondition41 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[35] /* $whenCondition41 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[34]] /* $whenCondition40 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[34] /* $whenCondition40 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1521
type: SIMPLE_ASSIGN
ala.and1.y = ala.truDel7.y and ala.truDel1.y
*/
void ReheatControllerFMU_eqFunction_1521(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1521};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[82]] /* ala.and1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1522
type: SIMPLE_ASSIGN
ala.and12.y = ala.and1.y and ala.greThr1.y
*/
void ReheatControllerFMU_eqFunction_1522(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1522};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[83]] /* ala.and12.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[82]] /* ala.and1.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[99]] /* ala.greThr1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1523
type: SIMPLE_ASSIGN
ala.not2.y = not (ala.and12.y and ala.isOcc.y)
*/
void ReheatControllerFMU_eqFunction_1523(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1523};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[108]] /* ala.not2.y DISCRETE */) = (!((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[83]] /* ala.and12.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[101]] /* ala.isOcc.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1524
type: SIMPLE_ASSIGN
ala.booToInt.y = if not ala.not2.y then 3 else ala.booToInt.integerFalse
*/
void ReheatControllerFMU_eqFunction_1524(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1524};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[5]] /* ala.booToInt.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[108]] /* ala.not2.y DISCRETE */))?((modelica_integer) 3):(data->simulationInfo->integerParameter[5] /* ala.booToInt.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1525
type: SIMPLE_ASSIGN
ala.lowFloAla.y = if not ala.not1.y then 2 else ala.booToInt.y
*/
void ReheatControllerFMU_eqFunction_1525(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1525};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[11]] /* ala.lowFloAla.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[107]] /* ala.not1.y DISCRETE */))?((modelica_integer) 2):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[5]] /* ala.booToInt.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1526
type: SIMPLE_ASSIGN
yLowFloAla = ala.lowFloAla.y * ala.booToInt1.y
*/
void ReheatControllerFMU_eqFunction_1526(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1526};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[43]] /* yLowFloAla DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[11]] /* ala.lowFloAla.y DISCRETE */)) * ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[6]] /* ala.booToInt1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1527
type: WHEN

when {} then
  ala.truDel1.t_next = if not ala.truDel1.delayOnInit then ala.truDel1.t_past else time + ala.truDel1.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1527(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1527};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[194]] /* ala.truDel1.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[33] /* ala.truDel1.delayOnInit PARAM */))?(data->simulationInfo->realParameter[99] /* ala.truDel1.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[98] /* ala.truDel1.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[36] /* $whenCondition42 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[194]] /* ala.truDel1.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[98] /* ala.truDel1.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[35]] /* $whenCondition41 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[35] /* $whenCondition41 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[194]] /* ala.truDel1.t_next DISCRETE */) = (data->simulationInfo->realParameter[99] /* ala.truDel1.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[34]] /* $whenCondition40 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[34] /* $whenCondition40 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[194]] /* ala.truDel1.t_next DISCRETE */) = (data->simulationInfo->realParameter[99] /* ala.truDel1.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1531
type: SIMPLE_ASSIGN
ala.truDel1.u = $whenCondition42
*/
void ReheatControllerFMU_eqFunction_1531(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1531};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[113]] /* ala.truDel1.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1532
type: SIMPLE_ASSIGN
damVal.VDisSet_flowNor.y = VSet_flow / damVal.max2.y
*/
void ReheatControllerFMU_eqFunction_1532(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1532};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[76]] /* damVal.VDisSet_flowNor.y variable */) = DIVISION_SIM((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[131]] /* damVal.max2.y variable */),"damVal.max2.y",equationIndexes);
  TRACE_POP
}
/*
equation index: 1533
type: SIMPLE_ASSIGN
damVal.conDam.controlError.y = damVal.VDisSet_flowNor.y - damVal.VDis_flowNor.y
*/
void ReheatControllerFMU_eqFunction_1533(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1533};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[91]] /* damVal.conDam.controlError.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[76]] /* damVal.VDisSet_flowNor.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[77]] /* damVal.VDis_flowNor.y variable */);
  TRACE_POP
}
/*
equation index: 1534
type: SIMPLE_ASSIGN
damVal.conDam.errP.u1 = damVal.conDam.uS_revAct.k * damVal.VDisSet_flowNor.y
*/
void ReheatControllerFMU_eqFunction_1534(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1534};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[93]] /* damVal.conDam.errP.u1 variable */) = ((data->simulationInfo->realParameter[219] /* damVal.conDam.uS_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[76]] /* damVal.VDisSet_flowNor.y variable */));
  TRACE_POP
}
/*
equation index: 1535
type: SIMPLE_ASSIGN
damVal.conDam.errI1.y = damVal.conDam.errP.u1 - damVal.conDam.uMea_revAct.y
*/
void ReheatControllerFMU_eqFunction_1535(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1535};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[92]] /* damVal.conDam.errI1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[93]] /* damVal.conDam.errP.u1 variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[94]] /* damVal.conDam.uMea_revAct.y variable */);
  TRACE_POP
}
/*
equation index: 1536
type: SIMPLE_ASSIGN
damVal.conDam.addPD.y = damVal.conDam.P.k * damVal.conDam.errI1.y
*/
void ReheatControllerFMU_eqFunction_1536(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1536};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[86]] /* damVal.conDam.addPD.y variable */) = ((data->simulationInfo->realParameter[208] /* damVal.conDam.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[92]] /* damVal.conDam.errI1.y variable */));
  TRACE_POP
}
/*
equation index: 1537
type: SIMPLE_ASSIGN
damVal.conDam.addPID.y = damVal.conDam.addPD.y + damVal.conDam.I.y
*/
void ReheatControllerFMU_eqFunction_1537(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1537};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[86]] /* damVal.conDam.addPD.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* damVal.conDam.I.y STATE(1) */);
  TRACE_POP
}
/*
equation index: 1538
type: SIMPLE_ASSIGN
damVal.conDam.y = smooth(0, if noEvent(damVal.conDam.addPID.y > 1.0) then 1.0 else if noEvent(damVal.conDam.addPID.y < 0.0) then 0.0 else damVal.conDam.addPID.y)
*/
void ReheatControllerFMU_eqFunction_1538(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1538};
  modelica_boolean tmp196;
  modelica_boolean tmp197;
  modelica_boolean tmp198;
  modelica_real tmp199;
  tmp196 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */),1.0);
  tmp198 = (modelica_boolean)tmp196;
  if(tmp198)
  {
    tmp199 = 1.0;
  }
  else
  {
    tmp197 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */),0.0);
    tmp199 = (tmp197?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[95]] /* damVal.conDam.y variable */) = tmp199;
  TRACE_POP
}
/*
equation index: 1539
type: SIMPLE_ASSIGN
damVal.yDam = smooth(0, if damVal.isUno.y then 0.0 else damVal.conDam.y)
*/
void ReheatControllerFMU_eqFunction_1539(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1539};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[139]] /* damVal.yDam variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[151]] /* damVal.isUno.y DISCRETE */)?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[95]] /* damVal.conDam.y variable */));
  TRACE_POP
}
/*
equation index: 1540
type: SIMPLE_ASSIGN
yDam = smooth(0, if setOve.or2.y then setOve.add3.y else damVal.yDam)
*/
void ReheatControllerFMU_eqFunction_1540(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1540};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[167]] /* setOve.or2.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[144]] /* setOve.add3.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[139]] /* damVal.yDam variable */));
  TRACE_POP
}
/*
equation index: 1541
type: SIMPLE_ASSIGN
ala.cloDam.lesHys.y = not pre(ala.cloDam.lesHys.y) and yDam < 0.005 or pre(ala.cloDam.lesHys.y) and yDam < 0.0075
*/
void ReheatControllerFMU_eqFunction_1541(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1541};
  modelica_boolean tmp200;
  modelica_real tmp201;
  modelica_real tmp202;
  modelica_boolean tmp203;
  modelica_real tmp204;
  modelica_real tmp205;
  tmp201 = 1.0;
  tmp202 = 0.005;
  relationhysteresis(data, &tmp200, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.005, tmp201, tmp202, 85, Less, LessZC);
  tmp204 = 1.0;
  tmp205 = 0.0075;
  relationhysteresis(data, &tmp203, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.0075, tmp204, tmp205, 86, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[90]] /* ala.cloDam.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */)) && tmp200) || ((data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */) && tmp203));
  TRACE_POP
}
/*
equation index: 1542
type: SIMPLE_ASSIGN
$whenCondition36 = ala.leaDamAla.y and ala.cloDam.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1542(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1542};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[102]] /* ala.leaDamAla.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[90]] /* ala.cloDam.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1543
type: SIMPLE_ASSIGN
$whenCondition35 = not $whenCondition36
*/
void ReheatControllerFMU_eqFunction_1543(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1543};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[28]] /* $whenCondition35 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */));
  TRACE_POP
}
/*
equation index: 1544
type: WHEN

when {} then
  ala.truDel3.y = if not (ala.truDel3.delayOnInit and ala.truDel3.delayTime > 0.0) then $whenCondition36 else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1544(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1544};
  modelica_boolean tmp206;
  modelica_boolean tmp207;
  if(0)
  {
    tmp206 = Greater((data->simulationInfo->realParameter[102] /* ala.truDel3.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[35] /* ala.truDel3.delayOnInit PARAM */) && tmp206))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[29] /* $whenCondition36 DISCRETE */) /* edge */))
  {
    tmp207 = Greater((data->simulationInfo->realParameter[102] /* ala.truDel3.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */) = (!tmp207);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[28]] /* $whenCondition35 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[28] /* $whenCondition35 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[27]] /* $whenCondition34 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[27] /* $whenCondition34 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1548
type: SIMPLE_ASSIGN
yLeaDamAla = if ala.truDel3.y then 4 else ala.booToInt3.integerFalse
*/
void ReheatControllerFMU_eqFunction_1548(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1548};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[41]] /* yLeaDamAla DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */)?((modelica_integer) 4):(data->simulationInfo->integerParameter[11] /* ala.booToInt3.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1549
type: WHEN

when {} then
  ala.truDel3.t_next = if not ala.truDel3.delayOnInit then ala.truDel3.t_past else time + ala.truDel3.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1549(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1549};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[196]] /* ala.truDel3.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[35] /* ala.truDel3.delayOnInit PARAM */))?(data->simulationInfo->realParameter[103] /* ala.truDel3.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[102] /* ala.truDel3.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[29] /* $whenCondition36 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[196]] /* ala.truDel3.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[102] /* ala.truDel3.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[28]] /* $whenCondition35 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[28] /* $whenCondition35 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[196]] /* ala.truDel3.t_next DISCRETE */) = (data->simulationInfo->realParameter[103] /* ala.truDel3.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[27]] /* $whenCondition34 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[27] /* $whenCondition34 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[196]] /* ala.truDel3.t_next DISCRETE */) = (data->simulationInfo->realParameter[103] /* ala.truDel3.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1553
type: SIMPLE_ASSIGN
ala.truDel3.u = $whenCondition36
*/
void ReheatControllerFMU_eqFunction_1553(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1553};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[117]] /* ala.truDel3.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1554
type: WHEN

when {$whenCondition54} then
  sysReq.sampler1.y = yDam;
end when;
*/
void ReheatControllerFMU_eqFunction_1554(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1554};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[49]] /* $whenCondition54 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[49] /* $whenCondition54 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */);
  }
  TRACE_POP
}
/*
equation index: 1555
type: SIMPLE_ASSIGN
sysReq.greThr3.greHys.y = not pre(sysReq.greThr3.greHys.y) and sysReq.sampler1.y > 0.95 or pre(sysReq.greThr3.greHys.y) and sysReq.sampler1.y > 0.945
*/
void ReheatControllerFMU_eqFunction_1555(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1555};
  modelica_boolean tmp208;
  modelica_boolean tmp209;
  tmp208 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */),0.95);
  tmp209 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */),0.945);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[181] /* sysReq.greThr3.greHys.y DISCRETE */)) && tmp208) || ((data->simulationInfo->booleanVarsPre[181] /* sysReq.greThr3.greHys.y DISCRETE */) && tmp209));
  TRACE_POP
}
/*
equation index: 1556
type: SIMPLE_ASSIGN
sysReq.booToInt1.y = if sysReq.greThr3.greHys.y then sysReq.booToInt1.integerTrue else sysReq.booToInt1.integerFalse
*/
void ReheatControllerFMU_eqFunction_1556(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1556};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[26]] /* sysReq.booToInt1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */)?(data->simulationInfo->integerParameter[44] /* sysReq.booToInt1.integerTrue PARAM */):(data->simulationInfo->integerParameter[43] /* sysReq.booToInt1.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1557
type: SIMPLE_ASSIGN
$whenCondition64 = sysReq.greThr3.greHys.y
*/
void ReheatControllerFMU_eqFunction_1557(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1557};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[60]] /* $whenCondition64 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1558
type: SIMPLE_ASSIGN
$whenCondition63 = not sysReq.greThr3.greHys.y
*/
void ReheatControllerFMU_eqFunction_1558(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1558};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[59]] /* $whenCondition63 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1559
type: SIMPLE_ASSIGN
sysReq.tim3.u = sysReq.greThr3.greHys.y
*/
void ReheatControllerFMU_eqFunction_1559(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1559};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[199]] /* sysReq.tim3.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1560
type: SIMPLE_ASSIGN
damVal.conDam.antWinErr.y = damVal.conDam.addPID.y - damVal.conDam.y
*/
void ReheatControllerFMU_eqFunction_1560(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1560};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[89]] /* damVal.conDam.antWinErr.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[95]] /* damVal.conDam.y variable */);
  TRACE_POP
}
/*
equation index: 1561
type: SIMPLE_ASSIGN
damVal.conDam.antWinGai.y = damVal.conDam.antWinGai.k * damVal.conDam.antWinErr.y
*/
void ReheatControllerFMU_eqFunction_1561(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1561};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[90]] /* damVal.conDam.antWinGai.y variable */) = ((data->simulationInfo->realParameter[212] /* damVal.conDam.antWinGai.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[89]] /* damVal.conDam.antWinErr.y variable */));
  TRACE_POP
}
/*
equation index: 1562
type: SIMPLE_ASSIGN
damVal.conDam.addRes.y = damVal.conDam.yResSig.k - damVal.conDam.addPD.y
*/
void ReheatControllerFMU_eqFunction_1562(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1562};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[88]] /* damVal.conDam.addRes.y variable */) = (data->simulationInfo->realParameter[223] /* damVal.conDam.yResSig.k PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[86]] /* damVal.conDam.addPD.y variable */);
  TRACE_POP
}
/*
equation index: 1563
type: SIMPLE_ASSIGN
damVal.conDam.I.u = damVal.conDam.errI1.y - damVal.conDam.antWinGai.y
*/
void ReheatControllerFMU_eqFunction_1563(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1563};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[84]] /* damVal.conDam.I.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[92]] /* damVal.conDam.errI1.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[90]] /* damVal.conDam.antWinGai.y variable */);
  TRACE_POP
}
/*
equation index: 1564
type: SIMPLE_ASSIGN
$DER.damVal.conDam.I.y = damVal.conDam.I.k * damVal.conDam.I.u
*/
void ReheatControllerFMU_eqFunction_1564(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1564};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[6]] /* der(damVal.conDam.I.y) STATE_DER */) = ((data->simulationInfo->realParameter[204] /* damVal.conDam.I.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[84]] /* damVal.conDam.I.u variable */));
  TRACE_POP
}
/*
equation index: 1565
type: SIMPLE_ASSIGN
damVal.conDam.P.u = damVal.conDam.errI1.y
*/
void ReheatControllerFMU_eqFunction_1565(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1565};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[85]] /* damVal.conDam.P.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[92]] /* damVal.conDam.errI1.y variable */);
  TRACE_POP
}
/*
equation index: 1566
type: WHEN

when {$whenCondition52} then
  sysReq.sampler3.y = VSet_flow;
end when;
*/
void ReheatControllerFMU_eqFunction_1566(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1566};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[47]] /* $whenCondition52 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[47] /* $whenCondition52 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */);
  }
  TRACE_POP
}
/*
equation index: 1567
type: SIMPLE_ASSIGN
sysReq.greThr4.greHys.y = not pre(sysReq.greThr4.greHys.y) and sysReq.sampler3.y > 0.005 or pre(sysReq.greThr4.greHys.y) and sysReq.sampler3.y > 0.0025
*/
void ReheatControllerFMU_eqFunction_1567(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1567};
  modelica_boolean tmp210;
  modelica_boolean tmp211;
  tmp210 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */),0.005);
  tmp211 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */),0.0025);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[182]] /* sysReq.greThr4.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[182] /* sysReq.greThr4.greHys.y DISCRETE */)) && tmp210) || ((data->simulationInfo->booleanVarsPre[182] /* sysReq.greThr4.greHys.y DISCRETE */) && tmp211));
  TRACE_POP
}
/*
equation index: 1568
type: SIMPLE_ASSIGN
sysReq.greEqu.u1 = 0.5 * sysReq.sampler3.y
*/
void ReheatControllerFMU_eqFunction_1568(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1568};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */) = (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1569
type: SIMPLE_ASSIGN
sysReq.greEqu.greHys.y = not pre(sysReq.greEqu.greHys.y) and sysReq.greEqu.u1 > sysReq.sampler2.y or pre(sysReq.greEqu.greHys.y) and sysReq.greEqu.u1 > sysReq.sampler2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_1569(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1569};
  modelica_boolean tmp212;
  modelica_real tmp213;
  modelica_real tmp214;
  modelica_boolean tmp215;
  modelica_real tmp216;
  modelica_real tmp217;
  tmp213 = 1.0;
  tmp214 = 1.0;
  relationhysteresis(data, &tmp212, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp213, tmp214, 87, Greater, GreaterZC);
  tmp216 = 1.0;
  tmp217 = 1.005;
  relationhysteresis(data, &tmp215, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp216, tmp217, 88, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[176]] /* sysReq.greEqu.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */)) && tmp212) || ((data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */) && tmp215));
  TRACE_POP
}
/*
equation index: 1570
type: SIMPLE_ASSIGN
sysReq.gai2.y = 0.7 * sysReq.sampler3.y
*/
void ReheatControllerFMU_eqFunction_1570(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1570};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */) = (0.7) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1571
type: SIMPLE_ASSIGN
sysReq.greEqu1.greHys.y = not pre(sysReq.greEqu1.greHys.y) and sysReq.gai2.y > sysReq.sampler2.y or pre(sysReq.greEqu1.greHys.y) and sysReq.gai2.y > sysReq.sampler2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_1571(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1571};
  modelica_boolean tmp218;
  modelica_real tmp219;
  modelica_real tmp220;
  modelica_boolean tmp221;
  modelica_real tmp222;
  modelica_real tmp223;
  tmp219 = 1.0;
  tmp220 = 1.0;
  relationhysteresis(data, &tmp218, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp219, tmp220, 89, Greater, GreaterZC);
  tmp222 = 1.0;
  tmp223 = 1.005;
  relationhysteresis(data, &tmp221, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp222, tmp223, 90, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[177]] /* sysReq.greEqu1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */)) && tmp218) || ((data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */) && tmp221));
  TRACE_POP
}
/*
equation index: 1572
type: WHEN

when {$whenCondition55} then
  sysReq.sampler.y = conLoo.yCoo;
end when;
*/
void ReheatControllerFMU_eqFunction_1572(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1572};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* $whenCondition55 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[50] /* $whenCondition55 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */);
  }
  TRACE_POP
}
/*
equation index: 1573
type: SIMPLE_ASSIGN
sysReq.greThr.greHys.y = not pre(sysReq.greThr.greHys.y) and sysReq.sampler.y > 0.95 or pre(sysReq.greThr.greHys.y) and sysReq.sampler.y > 0.94
*/
void ReheatControllerFMU_eqFunction_1573(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1573};
  modelica_boolean tmp224;
  modelica_boolean tmp225;
  tmp224 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */),0.95);
  tmp225 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */),0.94);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[178]] /* sysReq.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[178] /* sysReq.greThr.greHys.y DISCRETE */)) && tmp224) || ((data->simulationInfo->booleanVarsPre[178] /* sysReq.greThr.greHys.y DISCRETE */) && tmp225));
  TRACE_POP
}
/*
equation index: 1574
type: SIMPLE_ASSIGN
sysReq.booToInt.y = if sysReq.greThr.greHys.y then sysReq.booToInt.integerTrue else sysReq.booToInt.integerFalse
*/
void ReheatControllerFMU_eqFunction_1574(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1574};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[25]] /* sysReq.booToInt.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[178]] /* sysReq.greThr.greHys.y DISCRETE */)?(data->simulationInfo->integerParameter[42] /* sysReq.booToInt.integerTrue PARAM */):(data->simulationInfo->integerParameter[41] /* sysReq.booToInt.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1575
type: WHEN

when {} then
  conLoo.disCoo.t_next = if not conLoo.disCoo.delayOnInit then conLoo.disCoo.t_past else time + conLoo.disCoo.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1575(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1575};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[201]] /* conLoo.disCoo.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[52] /* conLoo.disCoo.delayOnInit PARAM */))?(data->simulationInfo->realParameter[167] /* conLoo.disCoo.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[46]] /* $whenCondition51 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[46] /* $whenCondition51 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[201]] /* conLoo.disCoo.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* $whenCondition50 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[45] /* $whenCondition50 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[201]] /* conLoo.disCoo.t_next DISCRETE */) = (data->simulationInfo->realParameter[167] /* conLoo.disCoo.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* $whenCondition49 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[43] /* $whenCondition49 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[201]] /* conLoo.disCoo.t_next DISCRETE */) = (data->simulationInfo->realParameter[167] /* conLoo.disCoo.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1579
type: SIMPLE_ASSIGN
$whenCondition56 = time >= pre(sysReq.tim5.t_next)
*/
void ReheatControllerFMU_eqFunction_1579(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1579};
  modelica_boolean tmp226;
  modelica_real tmp227;
  modelica_real tmp228;
  tmp227 = 1.0;
  tmp228 = 1.0;
  relationhysteresis(data, &tmp226, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */), tmp227, tmp228, 4, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[51]] /* $whenCondition56 DISCRETE */) = tmp226;
  TRACE_POP
}
/*
equation index: 1580
type: SIMPLE_ASSIGN
$whenCondition59 = time >= pre(sysReq.tim4.t_next)
*/
void ReheatControllerFMU_eqFunction_1580(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1580};
  modelica_boolean tmp229;
  modelica_real tmp230;
  modelica_real tmp231;
  tmp230 = 1.0;
  tmp231 = 1.0;
  relationhysteresis(data, &tmp229, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */), tmp230, tmp231, 3, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[54]] /* $whenCondition59 DISCRETE */) = tmp229;
  TRACE_POP
}
/*
equation index: 1581
type: SIMPLE_ASSIGN
$whenCondition62 = time >= pre(sysReq.tim3.t_next)
*/
void ReheatControllerFMU_eqFunction_1581(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1581};
  modelica_boolean tmp232;
  modelica_real tmp233;
  modelica_real tmp234;
  tmp233 = 1.0;
  tmp234 = 1.0;
  relationhysteresis(data, &tmp232, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */), tmp233, tmp234, 2, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[58]] /* $whenCondition62 DISCRETE */) = tmp232;
  TRACE_POP
}
/*
equation index: 1582
type: WHEN

when {} then
  sysReq.tim3.y = if not (sysReq.tim3.delayOnInit and sysReq.tim3.delayTime > 0.0) then sysReq.greThr3.greHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1582(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1582};
  modelica_boolean tmp235;
  modelica_boolean tmp236;
  if(0)
  {
    tmp235 = Greater((data->simulationInfo->realParameter[425] /* sysReq.tim3.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[156] /* sysReq.tim3.delayOnInit PARAM */) && tmp235))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[60]] /* $whenCondition64 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[60] /* $whenCondition64 DISCRETE */) /* edge */))
  {
    tmp236 = Greater((data->simulationInfo->realParameter[425] /* sysReq.tim3.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */) = (!tmp236);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[59]] /* $whenCondition63 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[59] /* $whenCondition63 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[58]] /* $whenCondition62 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[58] /* $whenCondition62 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1586
type: SIMPLE_ASSIGN
sysReq.and5.y = sysReq.greThr4.greHys.y and sysReq.tim3.y
*/
void ReheatControllerFMU_eqFunction_1586(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1586};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[175]] /* sysReq.and5.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[182]] /* sysReq.greThr4.greHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1587
type: SIMPLE_ASSIGN
sysReq.and3.y = sysReq.and5.y and sysReq.greEqu.greHys.y
*/
void ReheatControllerFMU_eqFunction_1587(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1587};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[173]] /* sysReq.and3.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[175]] /* sysReq.and5.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[176]] /* sysReq.greEqu.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1588
type: SIMPLE_ASSIGN
sysReq.and4.y = sysReq.and5.y and sysReq.greEqu1.greHys.y
*/
void ReheatControllerFMU_eqFunction_1588(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1588};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[174]] /* sysReq.and4.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[175]] /* sysReq.and5.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[177]] /* sysReq.greEqu1.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1589
type: SIMPLE_ASSIGN
sysReq.swi5.y = if sysReq.and4.y then 2 else sysReq.booToInt1.y
*/
void ReheatControllerFMU_eqFunction_1589(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1589};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[30]] /* sysReq.swi5.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[174]] /* sysReq.and4.y DISCRETE */)?((modelica_integer) 2):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[26]] /* sysReq.booToInt1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1590
type: SIMPLE_ASSIGN
yZonPreResReq = if sysReq.and3.y then 3 else sysReq.swi5.y
*/
void ReheatControllerFMU_eqFunction_1590(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1590};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[45]] /* yZonPreResReq DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[173]] /* sysReq.and3.y DISCRETE */)?((modelica_integer) 3):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[30]] /* sysReq.swi5.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1591
type: WHEN

when {} then
  sysReq.tim3.t_next = if not sysReq.tim3.delayOnInit then sysReq.tim3.t_past else time + sysReq.tim3.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1591(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1591};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[213]] /* sysReq.tim3.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[156] /* sysReq.tim3.delayOnInit PARAM */))?(data->simulationInfo->realParameter[426] /* sysReq.tim3.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[425] /* sysReq.tim3.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[60]] /* $whenCondition64 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[60] /* $whenCondition64 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[213]] /* sysReq.tim3.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[425] /* sysReq.tim3.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[59]] /* $whenCondition63 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[59] /* $whenCondition63 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[213]] /* sysReq.tim3.t_next DISCRETE */) = (data->simulationInfo->realParameter[426] /* sysReq.tim3.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[58]] /* $whenCondition62 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[58] /* $whenCondition62 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[213]] /* sysReq.tim3.t_next DISCRETE */) = (data->simulationInfo->realParameter[426] /* sysReq.tim3.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1595
type: SIMPLE_ASSIGN
$whenCondition65 = time >= pre(sysReq.tim2.t_next)
*/
void ReheatControllerFMU_eqFunction_1595(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1595};
  modelica_boolean tmp237;
  modelica_real tmp238;
  modelica_real tmp239;
  tmp238 = 1.0;
  tmp239 = 1.0;
  relationhysteresis(data, &tmp237, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */), tmp238, tmp239, 1, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[61]] /* $whenCondition65 DISCRETE */) = tmp237;
  TRACE_POP
}
/*
equation index: 1596
type: WHEN

when {} then
  sysReq.tim2.y = if not (sysReq.tim2.delayOnInit and sysReq.tim2.delayTime > 0.0) then sysReq.greThr2.greHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1596(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1596};
  modelica_boolean tmp240;
  modelica_boolean tmp241;
  if(0)
  {
    tmp240 = Greater((data->simulationInfo->realParameter[423] /* sysReq.tim2.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[155] /* sysReq.tim2.delayOnInit PARAM */) && tmp240))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[63]] /* $whenCondition67 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[63] /* $whenCondition67 DISCRETE */) /* edge */))
  {
    tmp241 = Greater((data->simulationInfo->realParameter[423] /* sysReq.tim2.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */) = (!tmp241);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[62]] /* $whenCondition66 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[62] /* $whenCondition66 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[61]] /* $whenCondition65 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[61] /* $whenCondition65 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1600
type: SIMPLE_ASSIGN
sysReq.and1.y = timSup.yAftSup and sysReq.tim2.y
*/
void ReheatControllerFMU_eqFunction_1600(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1600};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[171]] /* sysReq.and1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[220]] /* timSup.yAftSup DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1601
type: SIMPLE_ASSIGN
sysReq.intSwi1.y = if sysReq.and1.y then 2 else sysReq.booToInt.y
*/
void ReheatControllerFMU_eqFunction_1601(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1601};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[28]] /* sysReq.intSwi1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[171]] /* sysReq.and1.y DISCRETE */)?((modelica_integer) 2):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[25]] /* sysReq.booToInt.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1602
type: WHEN

when {} then
  sysReq.tim2.t_next = if not sysReq.tim2.delayOnInit then sysReq.tim2.t_past else time + sysReq.tim2.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1602(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1602};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[212]] /* sysReq.tim2.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[155] /* sysReq.tim2.delayOnInit PARAM */))?(data->simulationInfo->realParameter[424] /* sysReq.tim2.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[423] /* sysReq.tim2.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[63]] /* $whenCondition67 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[63] /* $whenCondition67 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[212]] /* sysReq.tim2.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[423] /* sysReq.tim2.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[62]] /* $whenCondition66 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[62] /* $whenCondition66 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[212]] /* sysReq.tim2.t_next DISCRETE */) = (data->simulationInfo->realParameter[424] /* sysReq.tim2.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[61]] /* $whenCondition65 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[61] /* $whenCondition65 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[212]] /* sysReq.tim2.t_next DISCRETE */) = (data->simulationInfo->realParameter[424] /* sysReq.tim2.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1606
type: SIMPLE_ASSIGN
$whenCondition68 = time >= pre(sysReq.tim1.t_next)
*/
void ReheatControllerFMU_eqFunction_1606(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1606};
  modelica_boolean tmp242;
  modelica_real tmp243;
  modelica_real tmp244;
  tmp243 = 1.0;
  tmp244 = 1.0;
  relationhysteresis(data, &tmp242, data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */), tmp243, tmp244, 0, GreaterEq, GreaterEqZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[64]] /* $whenCondition68 DISCRETE */) = tmp242;
  TRACE_POP
}
/*
equation index: 1607
type: WHEN

when {} then
  sysReq.tim1.y = if not (sysReq.tim1.delayOnInit and sysReq.tim1.delayTime > 0.0) then sysReq.greThr1.greHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1607(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1607};
  modelica_boolean tmp245;
  modelica_boolean tmp246;
  if(0)
  {
    tmp245 = Greater((data->simulationInfo->realParameter[421] /* sysReq.tim1.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[154] /* sysReq.tim1.delayOnInit PARAM */) && tmp245))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[67]] /* $whenCondition70 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[67] /* $whenCondition70 DISCRETE */) /* edge */))
  {
    tmp246 = Greater((data->simulationInfo->realParameter[421] /* sysReq.tim1.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */) = (!tmp246);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[65]] /* $whenCondition69 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[65] /* $whenCondition69 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[64]] /* $whenCondition68 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[64] /* $whenCondition68 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1611
type: SIMPLE_ASSIGN
sysReq.and2.y = timSup.yAftSup and sysReq.tim1.y
*/
void ReheatControllerFMU_eqFunction_1611(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1611};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[172]] /* sysReq.and2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[220]] /* timSup.yAftSup DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1612
type: SIMPLE_ASSIGN
yZonTemResReq = if sysReq.and2.y then 3 else sysReq.intSwi1.y
*/
void ReheatControllerFMU_eqFunction_1612(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1612};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[46]] /* yZonTemResReq DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[172]] /* sysReq.and2.y DISCRETE */)?((modelica_integer) 3):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[28]] /* sysReq.intSwi1.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1613
type: WHEN

when {} then
  sysReq.tim1.t_next = if not sysReq.tim1.delayOnInit then sysReq.tim1.t_past else time + sysReq.tim1.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1613(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1613};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[211]] /* sysReq.tim1.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[154] /* sysReq.tim1.delayOnInit PARAM */))?(data->simulationInfo->realParameter[422] /* sysReq.tim1.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[421] /* sysReq.tim1.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[67]] /* $whenCondition70 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[67] /* $whenCondition70 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[211]] /* sysReq.tim1.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[421] /* sysReq.tim1.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[65]] /* $whenCondition69 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[65] /* $whenCondition69 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[211]] /* sysReq.tim1.t_next DISCRETE */) = (data->simulationInfo->realParameter[422] /* sysReq.tim1.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[64]] /* $whenCondition68 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[64] /* $whenCondition68 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[211]] /* sysReq.tim1.t_next DISCRETE */) = (data->simulationInfo->realParameter[422] /* sysReq.tim1.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1617
type: SIMPLE_ASSIGN
$whenCondition73 = u1Fan
*/
void ReheatControllerFMU_eqFunction_1617(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1617};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[70]] /* $whenCondition73 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */);
  TRACE_POP
}
/*
equation index: 1618
type: SIMPLE_ASSIGN
damVal.max1.y = max(TSupSet, damVal.lowDisAirTem.k)
*/
void ReheatControllerFMU_eqFunction_1618(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1618};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[130]] /* damVal.max1.y variable */) = fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[17]] /* TSupSet variable */),(data->simulationInfo->realParameter[286] /* damVal.lowDisAirTem.k PARAM */));
  TRACE_POP
}
/*
equation index: 1619
type: SIMPLE_ASSIGN
damVal.TDisSet = smooth(0, if not damVal.truFalHol.not_y then damVal.conTDisHeaSet.y else damVal.max1.y)
*/
void ReheatControllerFMU_eqFunction_1619(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1619};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */))?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[103]] /* damVal.conTDisHeaSet.y variable */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[130]] /* damVal.max1.y variable */));
  TRACE_POP
}
/*
equation index: 1620
type: SIMPLE_ASSIGN
ala.addPar.y = -17.0 + damVal.TDisSet
*/
void ReheatControllerFMU_eqFunction_1620(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1620};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) = -17.0 + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */);
  TRACE_POP
}
/*
equation index: 1621
type: SIMPLE_ASSIGN
ala.les1.lesHys.y = not pre(ala.les1.lesHys.y) and TDis < ala.addPar.y or pre(ala.les1.lesHys.y) and TDis < ala.addPar.y + 0.25
*/
void ReheatControllerFMU_eqFunction_1621(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1621};
  modelica_boolean tmp247;
  modelica_real tmp248;
  modelica_real tmp249;
  modelica_boolean tmp250;
  modelica_real tmp251;
  modelica_real tmp252;
  tmp248 = 1.0;
  tmp249 = 1.0;
  relationhysteresis(data, &tmp247, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */), tmp248, tmp249, 54, Less, LessZC);
  tmp251 = 1.0;
  tmp252 = 1.25;
  relationhysteresis(data, &tmp250, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) + 0.25, tmp251, tmp252, 55, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */)) && tmp247) || ((data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */) && tmp250));
  TRACE_POP
}
/*
equation index: 1622
type: SIMPLE_ASSIGN
$whenCondition33 = ala.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1622(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1622};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[26]] /* $whenCondition33 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1623
type: SIMPLE_ASSIGN
$whenCondition32 = not ala.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1623(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1623};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[25]] /* $whenCondition32 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1624
type: WHEN

when {} then
  ala.truDel4.t_next = if not ala.truDel4.delayOnInit then ala.truDel4.t_past else time + ala.truDel4.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1624(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1624};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[197]] /* ala.truDel4.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[36] /* ala.truDel4.delayOnInit PARAM */))?(data->simulationInfo->realParameter[105] /* ala.truDel4.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[26]] /* $whenCondition33 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[26] /* $whenCondition33 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[197]] /* ala.truDel4.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[25]] /* $whenCondition32 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[25] /* $whenCondition32 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[197]] /* ala.truDel4.t_next DISCRETE */) = (data->simulationInfo->realParameter[105] /* ala.truDel4.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[24]] /* $whenCondition31 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[24] /* $whenCondition31 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[197]] /* ala.truDel4.t_next DISCRETE */) = (data->simulationInfo->realParameter[105] /* ala.truDel4.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1628
type: WHEN

when {} then
  ala.truDel4.y = if not (ala.truDel4.delayOnInit and ala.truDel4.delayTime > 0.0) then ala.les1.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1628(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1628};
  modelica_boolean tmp253;
  modelica_boolean tmp254;
  if(0)
  {
    tmp253 = Greater((data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[36] /* ala.truDel4.delayOnInit PARAM */) && tmp253))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[26]] /* $whenCondition33 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[26] /* $whenCondition33 DISCRETE */) /* edge */))
  {
    tmp254 = Greater((data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) = (!tmp254);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[25]] /* $whenCondition32 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[25] /* $whenCondition32 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[24]] /* $whenCondition31 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[24] /* $whenCondition31 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1632
type: SIMPLE_ASSIGN
ala.and6.y = ala.truDel4.y and ala.fanHotPlaOn.y
*/
void ReheatControllerFMU_eqFunction_1632(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1632};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[86]] /* ala.and6.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[92]] /* ala.fanHotPlaOn.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1633
type: SIMPLE_ASSIGN
ala.and7.y = ala.and6.y and ala.greThr2.y
*/
void ReheatControllerFMU_eqFunction_1633(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1633};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[87]] /* ala.and7.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[86]] /* ala.and6.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[100]] /* ala.greThr2.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1634
type: SIMPLE_ASSIGN
ala.not6.y = not (ala.and7.y and ala.isOcc.y)
*/
void ReheatControllerFMU_eqFunction_1634(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1634};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[109]] /* ala.not6.y DISCRETE */) = (!((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[87]] /* ala.and7.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[101]] /* ala.isOcc.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1635
type: SIMPLE_ASSIGN
ala.truDel4.u = ala.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1635(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1635};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[119]] /* ala.truDel4.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1636
type: SIMPLE_ASSIGN
ala.addPar1.y = -8.0 + damVal.TDisSet
*/
void ReheatControllerFMU_eqFunction_1636(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1636};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) = -8.0 + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */);
  TRACE_POP
}
/*
equation index: 1637
type: SIMPLE_ASSIGN
ala.les2.lesHys.y = not pre(ala.les2.lesHys.y) and TDis < ala.addPar1.y or pre(ala.les2.lesHys.y) and TDis < ala.addPar1.y + 0.25
*/
void ReheatControllerFMU_eqFunction_1637(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1637};
  modelica_boolean tmp255;
  modelica_real tmp256;
  modelica_real tmp257;
  modelica_boolean tmp258;
  modelica_real tmp259;
  modelica_real tmp260;
  tmp256 = 1.0;
  tmp257 = 1.0;
  relationhysteresis(data, &tmp255, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */), tmp256, tmp257, 56, Less, LessZC);
  tmp259 = 1.0;
  tmp260 = 1.25;
  relationhysteresis(data, &tmp258, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) + 0.25, tmp259, tmp260, 57, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */)) && tmp255) || ((data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */) && tmp258));
  TRACE_POP
}
/*
equation index: 1638
type: SIMPLE_ASSIGN
$whenCondition30 = ala.les2.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1638(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1638};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[23]] /* $whenCondition30 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1639
type: SIMPLE_ASSIGN
$whenCondition29 = not ala.les2.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1639(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1639};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[21]] /* $whenCondition29 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1640
type: WHEN

when {} then
  ala.truDel5.t_next = if not ala.truDel5.delayOnInit then ala.truDel5.t_past else time + ala.truDel5.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1640(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1640};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[198]] /* ala.truDel5.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[37] /* ala.truDel5.delayOnInit PARAM */))?(data->simulationInfo->realParameter[107] /* ala.truDel5.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[23]] /* $whenCondition30 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[23] /* $whenCondition30 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[198]] /* ala.truDel5.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[21]] /* $whenCondition29 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[21] /* $whenCondition29 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[198]] /* ala.truDel5.t_next DISCRETE */) = (data->simulationInfo->realParameter[107] /* ala.truDel5.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[20]] /* $whenCondition28 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[20] /* $whenCondition28 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[198]] /* ala.truDel5.t_next DISCRETE */) = (data->simulationInfo->realParameter[107] /* ala.truDel5.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1644
type: WHEN

when {} then
  ala.truDel5.y = if not (ala.truDel5.delayOnInit and ala.truDel5.delayTime > 0.0) then ala.les2.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1644(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1644};
  modelica_boolean tmp261;
  modelica_boolean tmp262;
  if(0)
  {
    tmp261 = Greater((data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[37] /* ala.truDel5.delayOnInit PARAM */) && tmp261))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[23]] /* $whenCondition30 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[23] /* $whenCondition30 DISCRETE */) /* edge */))
  {
    tmp262 = Greater((data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) = (!tmp262);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[21]] /* $whenCondition29 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[21] /* $whenCondition29 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[20]] /* $whenCondition28 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[20] /* $whenCondition28 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1648
type: SIMPLE_ASSIGN
ala.and8.y = ala.truDel5.y and ala.fanHotPlaOn.y
*/
void ReheatControllerFMU_eqFunction_1648(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1648};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[88]] /* ala.and8.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[92]] /* ala.fanHotPlaOn.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1649
type: SIMPLE_ASSIGN
ala.and9.y = ala.and8.y and ala.greThr2.y
*/
void ReheatControllerFMU_eqFunction_1649(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1649};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[89]] /* ala.and9.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[88]] /* ala.and8.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[100]] /* ala.greThr2.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1650
type: SIMPLE_ASSIGN
ala.not7.y = not (ala.and9.y and ala.isOcc.y)
*/
void ReheatControllerFMU_eqFunction_1650(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1650};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[110]] /* ala.not7.y DISCRETE */) = (!((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[89]] /* ala.and9.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[101]] /* ala.isOcc.y DISCRETE */)));
  TRACE_POP
}
/*
equation index: 1651
type: SIMPLE_ASSIGN
ala.booToInt4.y = if not ala.not7.y then 3 else ala.booToInt4.integerFalse
*/
void ReheatControllerFMU_eqFunction_1651(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1651};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[7]] /* ala.booToInt4.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[110]] /* ala.not7.y DISCRETE */))?((modelica_integer) 3):(data->simulationInfo->integerParameter[13] /* ala.booToInt4.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1652
type: SIMPLE_ASSIGN
ala.lowTemAla.y = if not ala.not6.y then 2 else ala.booToInt4.y
*/
void ReheatControllerFMU_eqFunction_1652(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1652};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[12]] /* ala.lowTemAla.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[109]] /* ala.not6.y DISCRETE */))?((modelica_integer) 2):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[7]] /* ala.booToInt4.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1653
type: SIMPLE_ASSIGN
yLowTemAla = ala.lowTemAla.y * ala.booToInt5.y
*/
void ReheatControllerFMU_eqFunction_1653(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1653};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[44]] /* yLowTemAla DISCRETE */) = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[12]] /* ala.lowTemAla.y DISCRETE */)) * ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[8]] /* ala.booToInt5.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1654
type: SIMPLE_ASSIGN
ala.truDel5.u = ala.les2.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1654(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1654};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[121]] /* ala.truDel5.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1655
type: SIMPLE_ASSIGN
damVal.conVal.controlError.y = damVal.TDisSet - TDis
*/
void ReheatControllerFMU_eqFunction_1655(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1655};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[112]] /* damVal.conVal.controlError.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */);
  TRACE_POP
}
/*
equation index: 1656
type: SIMPLE_ASSIGN
damVal.conVal.errP.u1 = damVal.conVal.uS_revAct.k * damVal.TDisSet
*/
void ReheatControllerFMU_eqFunction_1656(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1656};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[114]] /* damVal.conVal.errP.u1 variable */) = ((data->simulationInfo->realParameter[247] /* damVal.conVal.uS_revAct.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */));
  TRACE_POP
}
/*
equation index: 1657
type: SIMPLE_ASSIGN
damVal.conVal.errI1.y = damVal.conVal.errP.u1 - damVal.conVal.uMea_revAct.y
*/
void ReheatControllerFMU_eqFunction_1657(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1657};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[113]] /* damVal.conVal.errI1.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[114]] /* damVal.conVal.errP.u1 variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[115]] /* damVal.conVal.uMea_revAct.y variable */);
  TRACE_POP
}
/*
equation index: 1658
type: SIMPLE_ASSIGN
damVal.conVal.addPD.y = damVal.conVal.P.k * damVal.conVal.errI1.y
*/
void ReheatControllerFMU_eqFunction_1658(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1658};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[107]] /* damVal.conVal.addPD.y variable */) = ((data->simulationInfo->realParameter[236] /* damVal.conVal.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[113]] /* damVal.conVal.errI1.y variable */));
  TRACE_POP
}
/*
equation index: 1659
type: SIMPLE_ASSIGN
damVal.conVal.addPID.y = damVal.conVal.addPD.y + damVal.conVal.I.y
*/
void ReheatControllerFMU_eqFunction_1659(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1659};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[107]] /* damVal.conVal.addPD.y variable */) + (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* damVal.conVal.I.y STATE(1) */);
  TRACE_POP
}
/*
equation index: 1660
type: SIMPLE_ASSIGN
damVal.conVal.y = smooth(0, if noEvent(damVal.conVal.addPID.y > 1.0) then 1.0 else if noEvent(damVal.conVal.addPID.y < 0.0) then 0.0 else damVal.conVal.addPID.y)
*/
void ReheatControllerFMU_eqFunction_1660(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1660};
  modelica_boolean tmp263;
  modelica_boolean tmp264;
  modelica_boolean tmp265;
  modelica_real tmp266;
  tmp263 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */),1.0);
  tmp265 = (modelica_boolean)tmp263;
  if(tmp265)
  {
    tmp266 = 1.0;
  }
  else
  {
    tmp264 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */),0.0);
    tmp266 = (tmp264?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */) = tmp266;
  TRACE_POP
}
/*
equation index: 1661
type: SIMPLE_ASSIGN
damVal.swi4.y = smooth(0, if $whenCondition74 then damVal.conVal.y else 0.0)
*/
void ReheatControllerFMU_eqFunction_1661(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1661};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[137]] /* damVal.swi4.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[71]] /* $whenCondition74 DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */):0.0);
  TRACE_POP
}
/*
equation index: 1662
type: SIMPLE_ASSIGN
damVal.yVal = smooth(0, if damVal.isUno.y then 0.0 else damVal.swi4.y)
*/
void ReheatControllerFMU_eqFunction_1662(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1662};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[140]] /* damVal.yVal variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[151]] /* damVal.isUno.y DISCRETE */)?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[137]] /* damVal.swi4.y variable */));
  TRACE_POP
}
/*
equation index: 1663
type: SIMPLE_ASSIGN
yVal = setOve.booToRea.y * damVal.yVal
*/
void ReheatControllerFMU_eqFunction_1663(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1663};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[145]] /* setOve.booToRea.y variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[140]] /* damVal.yVal variable */));
  TRACE_POP
}
/*
equation index: 1664
type: SIMPLE_ASSIGN
ala.cloVal.lesHys.y = not pre(ala.cloVal.lesHys.y) and yVal < 0.005 or pre(ala.cloVal.lesHys.y) and yVal < 0.0075
*/
void ReheatControllerFMU_eqFunction_1664(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1664};
  modelica_boolean tmp267;
  modelica_real tmp268;
  modelica_real tmp269;
  modelica_boolean tmp270;
  modelica_real tmp271;
  modelica_real tmp272;
  tmp268 = 1.0;
  tmp269 = 0.005;
  relationhysteresis(data, &tmp267, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.005, tmp268, tmp269, 58, Less, LessZC);
  tmp271 = 1.0;
  tmp272 = 0.0075;
  relationhysteresis(data, &tmp270, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.0075, tmp271, tmp272, 59, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[91]] /* ala.cloVal.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */)) && tmp267) || ((data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */) && tmp270));
  TRACE_POP
}
/*
equation index: 1665
type: SIMPLE_ASSIGN
ala.leaValAla.y = ala.cloVal.lesHys.y and u1Fan
*/
void ReheatControllerFMU_eqFunction_1665(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1665};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[103]] /* ala.leaValAla.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[91]] /* ala.cloVal.lesHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */));
  TRACE_POP
}
/*
equation index: 1666
type: SIMPLE_ASSIGN
$whenCondition27 = ala.leaValAla.y and ala.gre2.greHys.y
*/
void ReheatControllerFMU_eqFunction_1666(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1666};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[103]] /* ala.leaValAla.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[97]] /* ala.gre2.greHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1667
type: SIMPLE_ASSIGN
$whenCondition26 = not $whenCondition27
*/
void ReheatControllerFMU_eqFunction_1667(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1667};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[18]] /* $whenCondition26 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */));
  TRACE_POP
}
/*
equation index: 1668
type: WHEN

when {} then
  ala.truDel6.y = if not (ala.truDel6.delayOnInit and ala.truDel6.delayTime > 0.0) then $whenCondition27 else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1668(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1668};
  modelica_boolean tmp273;
  modelica_boolean tmp274;
  if(0)
  {
    tmp273 = Greater((data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[38] /* ala.truDel6.delayOnInit PARAM */) && tmp273))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[19] /* $whenCondition27 DISCRETE */) /* edge */))
  {
    tmp274 = Greater((data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */) = (!tmp274);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[18]] /* $whenCondition26 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[18] /* $whenCondition26 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[17]] /* $whenCondition25 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[17] /* $whenCondition25 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1672
type: SIMPLE_ASSIGN
yLeaValAla = if ala.truDel6.y then 4 else ala.booToInt6.integerFalse
*/
void ReheatControllerFMU_eqFunction_1672(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1672};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[42]] /* yLeaValAla DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */)?((modelica_integer) 4):(data->simulationInfo->integerParameter[17] /* ala.booToInt6.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1673
type: WHEN

when {} then
  ala.truDel6.t_next = if not ala.truDel6.delayOnInit then ala.truDel6.t_past else time + ala.truDel6.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1673(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1673};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[199]] /* ala.truDel6.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[38] /* ala.truDel6.delayOnInit PARAM */))?(data->simulationInfo->realParameter[109] /* ala.truDel6.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[19] /* $whenCondition27 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[199]] /* ala.truDel6.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[18]] /* $whenCondition26 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[18] /* $whenCondition26 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[199]] /* ala.truDel6.t_next DISCRETE */) = (data->simulationInfo->realParameter[109] /* ala.truDel6.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[17]] /* $whenCondition25 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[17] /* $whenCondition25 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[199]] /* ala.truDel6.t_next DISCRETE */) = (data->simulationInfo->realParameter[109] /* ala.truDel6.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1677
type: SIMPLE_ASSIGN
ala.truDel6.u = $whenCondition27
*/
void ReheatControllerFMU_eqFunction_1677(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1677};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[123]] /* ala.truDel6.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */);
  TRACE_POP
}
/*
equation index: 1678
type: SIMPLE_ASSIGN
sysReq.greThr6.greHys.y = not pre(sysReq.greThr6.greHys.y) and yVal > 0.95 or pre(sysReq.greThr6.greHys.y) and yVal > 0.09999999999999998
*/
void ReheatControllerFMU_eqFunction_1678(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1678};
  modelica_boolean tmp275;
  modelica_real tmp276;
  modelica_real tmp277;
  modelica_boolean tmp278;
  modelica_real tmp279;
  modelica_real tmp280;
  tmp276 = 1.0;
  tmp277 = 0.95;
  relationhysteresis(data, &tmp275, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.95, tmp276, tmp277, 64, Greater, GreaterZC);
  tmp279 = 1.0;
  tmp280 = 0.09999999999999998;
  relationhysteresis(data, &tmp278, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.09999999999999998, tmp279, tmp280, 65, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[184]] /* sysReq.greThr6.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */)) && tmp275) || ((data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */) && tmp278));
  TRACE_POP
}
/*
equation index: 1679
type: SIMPLE_ASSIGN
yHotWatPlaReq = if sysReq.greThr6.greHys.y then sysReq.booToInt3.integerTrue else sysReq.booToInt3.integerFalse
*/
void ReheatControllerFMU_eqFunction_1679(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1679};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[40]] /* yHotWatPlaReq DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[184]] /* sysReq.greThr6.greHys.y DISCRETE */)?(data->simulationInfo->integerParameter[48] /* sysReq.booToInt3.integerTrue PARAM */):(data->simulationInfo->integerParameter[47] /* sysReq.booToInt3.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1680
type: SIMPLE_ASSIGN
sysReq.greThr5.greHys.y = not pre(sysReq.greThr5.greHys.y) and yVal > 0.95 or pre(sysReq.greThr5.greHys.y) and yVal > 0.945
*/
void ReheatControllerFMU_eqFunction_1680(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1680};
  modelica_boolean tmp281;
  modelica_real tmp282;
  modelica_real tmp283;
  modelica_boolean tmp284;
  modelica_real tmp285;
  modelica_real tmp286;
  tmp282 = 1.0;
  tmp283 = 0.95;
  relationhysteresis(data, &tmp281, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.95, tmp282, tmp283, 64, Greater, GreaterZC);
  tmp285 = 1.0;
  tmp286 = 0.945;
  relationhysteresis(data, &tmp284, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.945, tmp285, tmp286, 66, Greater, GreaterZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[183]] /* sysReq.greThr5.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */)) && tmp281) || ((data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */) && tmp284));
  TRACE_POP
}
/*
equation index: 1681
type: SIMPLE_ASSIGN
sysReq.booToInt2.y = if sysReq.greThr5.greHys.y then sysReq.booToInt2.integerTrue else sysReq.booToInt2.integerFalse
*/
void ReheatControllerFMU_eqFunction_1681(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1681};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[27]] /* sysReq.booToInt2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[183]] /* sysReq.greThr5.greHys.y DISCRETE */)?(data->simulationInfo->integerParameter[46] /* sysReq.booToInt2.integerTrue PARAM */):(data->simulationInfo->integerParameter[45] /* sysReq.booToInt2.integerFalse PARAM */));
  TRACE_POP
}
/*
equation index: 1682
type: SIMPLE_ASSIGN
damVal.conVal.antWinErr.y = damVal.conVal.addPID.y - damVal.conVal.y
*/
void ReheatControllerFMU_eqFunction_1682(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1682};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[110]] /* damVal.conVal.antWinErr.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */);
  TRACE_POP
}
/*
equation index: 1683
type: SIMPLE_ASSIGN
damVal.conVal.antWinGai.y = damVal.conVal.antWinGai.k * damVal.conVal.antWinErr.y
*/
void ReheatControllerFMU_eqFunction_1683(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1683};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[111]] /* damVal.conVal.antWinGai.y variable */) = ((data->simulationInfo->realParameter[240] /* damVal.conVal.antWinGai.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[110]] /* damVal.conVal.antWinErr.y variable */));
  TRACE_POP
}
/*
equation index: 1684
type: SIMPLE_ASSIGN
damVal.conVal.addRes.y = damVal.conVal.yResSig.k - damVal.conVal.addPD.y
*/
void ReheatControllerFMU_eqFunction_1684(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1684};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[109]] /* damVal.conVal.addRes.y variable */) = (data->simulationInfo->realParameter[251] /* damVal.conVal.yResSig.k PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[107]] /* damVal.conVal.addPD.y variable */);
  TRACE_POP
}
/*
equation index: 1685
type: SIMPLE_ASSIGN
damVal.conVal.I.u = damVal.conVal.errI1.y - damVal.conVal.antWinGai.y
*/
void ReheatControllerFMU_eqFunction_1685(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1685};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[105]] /* damVal.conVal.I.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[113]] /* damVal.conVal.errI1.y variable */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[111]] /* damVal.conVal.antWinGai.y variable */);
  TRACE_POP
}
/*
equation index: 1686
type: SIMPLE_ASSIGN
$DER.damVal.conVal.I.y = damVal.conVal.I.k * damVal.conVal.I.u
*/
void ReheatControllerFMU_eqFunction_1686(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1686};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[7]] /* der(damVal.conVal.I.y) STATE_DER */) = ((data->simulationInfo->realParameter[232] /* damVal.conVal.I.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[105]] /* damVal.conVal.I.u variable */));
  TRACE_POP
}
/*
equation index: 1687
type: SIMPLE_ASSIGN
damVal.conVal.P.u = damVal.conVal.errI1.y
*/
void ReheatControllerFMU_eqFunction_1687(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1687};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[106]] /* damVal.conVal.P.u variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[113]] /* damVal.conVal.errI1.y variable */);
  TRACE_POP
}
/*
equation index: 1688
type: SIMPLE_ASSIGN
sysReq.les1.lesHys.y = not pre(sysReq.les1.lesHys.y) and sysReq.addPar1.y < damVal.TDisSet or pre(sysReq.les1.lesHys.y) and sysReq.addPar1.y < damVal.TDisSet + 0.25
*/
void ReheatControllerFMU_eqFunction_1688(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1688};
  modelica_boolean tmp287;
  modelica_real tmp288;
  modelica_real tmp289;
  modelica_boolean tmp290;
  modelica_real tmp291;
  modelica_real tmp292;
  tmp288 = 1.0;
  tmp289 = 1.0;
  relationhysteresis(data, &tmp287, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp288, tmp289, 71, Less, LessZC);
  tmp291 = 1.0;
  tmp292 = 1.25;
  relationhysteresis(data, &tmp290, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp291, tmp292, 72, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */)) && tmp287) || ((data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */) && tmp290));
  TRACE_POP
}
/*
equation index: 1689
type: SIMPLE_ASSIGN
$whenCondition58 = sysReq.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1689(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1689};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[53]] /* $whenCondition58 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1690
type: SIMPLE_ASSIGN
$whenCondition57 = not sysReq.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1690(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1690};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[52]] /* $whenCondition57 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1691
type: WHEN

when {} then
  sysReq.tim5.t_next = if not sysReq.tim5.delayOnInit then sysReq.tim5.t_past else time + sysReq.tim5.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1691(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1691};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[215]] /* sysReq.tim5.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[158] /* sysReq.tim5.delayOnInit PARAM */))?(data->simulationInfo->realParameter[430] /* sysReq.tim5.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[429] /* sysReq.tim5.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[53]] /* $whenCondition58 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[53] /* $whenCondition58 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[215]] /* sysReq.tim5.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[429] /* sysReq.tim5.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[52]] /* $whenCondition57 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[52] /* $whenCondition57 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[215]] /* sysReq.tim5.t_next DISCRETE */) = (data->simulationInfo->realParameter[430] /* sysReq.tim5.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[51]] /* $whenCondition56 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[51] /* $whenCondition56 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[215]] /* sysReq.tim5.t_next DISCRETE */) = (data->simulationInfo->realParameter[430] /* sysReq.tim5.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1695
type: WHEN

when {} then
  sysReq.tim5.y = if not (sysReq.tim5.delayOnInit and sysReq.tim5.delayTime > 0.0) then sysReq.les1.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1695(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1695};
  modelica_boolean tmp293;
  modelica_boolean tmp294;
  if(0)
  {
    tmp293 = Greater((data->simulationInfo->realParameter[429] /* sysReq.tim5.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[158] /* sysReq.tim5.delayOnInit PARAM */) && tmp293))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[53]] /* $whenCondition58 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[53] /* $whenCondition58 DISCRETE */) /* edge */))
  {
    tmp294 = Greater((data->simulationInfo->realParameter[429] /* sysReq.tim5.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */) = (!tmp294);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[52]] /* $whenCondition57 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[52] /* $whenCondition57 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[51]] /* $whenCondition56 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[51] /* $whenCondition56 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1699
type: SIMPLE_ASSIGN
sysReq.intSwi3.y = if sysReq.tim5.y then 2 else sysReq.booToInt2.y
*/
void ReheatControllerFMU_eqFunction_1699(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1699};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[29]] /* sysReq.intSwi3.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */)?((modelica_integer) 2):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[27]] /* sysReq.booToInt2.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1700
type: SIMPLE_ASSIGN
sysReq.tim5.u = sysReq.les1.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1700(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1700};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[203]] /* sysReq.tim5.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1701
type: SIMPLE_ASSIGN
sysReq.les.lesHys.y = not pre(sysReq.les.lesHys.y) and sysReq.addPar.y < damVal.TDisSet or pre(sysReq.les.lesHys.y) and sysReq.addPar.y < damVal.TDisSet + 0.25
*/
void ReheatControllerFMU_eqFunction_1701(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1701};
  modelica_boolean tmp295;
  modelica_real tmp296;
  modelica_real tmp297;
  modelica_boolean tmp298;
  modelica_real tmp299;
  modelica_real tmp300;
  tmp296 = 1.0;
  tmp297 = 1.0;
  relationhysteresis(data, &tmp295, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp296, tmp297, 73, Less, LessZC);
  tmp299 = 1.0;
  tmp300 = 1.25;
  relationhysteresis(data, &tmp298, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp299, tmp300, 74, Less, LessZC);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */)) && tmp295) || ((data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */) && tmp298));
  TRACE_POP
}
/*
equation index: 1702
type: SIMPLE_ASSIGN
$whenCondition61 = sysReq.les.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1702(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1702};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[57]] /* $whenCondition61 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1703
type: SIMPLE_ASSIGN
$whenCondition60 = not sysReq.les.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1703(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1703};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[56]] /* $whenCondition60 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1704
type: WHEN

when {} then
  sysReq.tim4.t_next = if not sysReq.tim4.delayOnInit then sysReq.tim4.t_past else time + sysReq.tim4.delayTime;
end when;
*/
void ReheatControllerFMU_eqFunction_1704(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1704};
  if(0)
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[214]] /* sysReq.tim4.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[157] /* sysReq.tim4.delayOnInit PARAM */))?(data->simulationInfo->realParameter[428] /* sysReq.tim4.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[427] /* sysReq.tim4.delayTime PARAM */));
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[57]] /* $whenCondition61 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[57] /* $whenCondition61 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[214]] /* sysReq.tim4.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[427] /* sysReq.tim4.delayTime PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[56]] /* $whenCondition60 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[56] /* $whenCondition60 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[214]] /* sysReq.tim4.t_next DISCRETE */) = (data->simulationInfo->realParameter[428] /* sysReq.tim4.t_past PARAM */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[54]] /* $whenCondition59 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[54] /* $whenCondition59 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[214]] /* sysReq.tim4.t_next DISCRETE */) = (data->simulationInfo->realParameter[428] /* sysReq.tim4.t_past PARAM */);
  }
  TRACE_POP
}
/*
equation index: 1708
type: WHEN

when {} then
  sysReq.tim4.y = if not (sysReq.tim4.delayOnInit and sysReq.tim4.delayTime > 0.0) then sysReq.les.lesHys.y else false;
end when;
*/
void ReheatControllerFMU_eqFunction_1708(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1708};
  modelica_boolean tmp301;
  modelica_boolean tmp302;
  if(0)
  {
    tmp301 = Greater((data->simulationInfo->realParameter[427] /* sysReq.tim4.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[157] /* sysReq.tim4.delayOnInit PARAM */) && tmp301))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */):0 /* false */);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[57]] /* $whenCondition61 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[57] /* $whenCondition61 DISCRETE */) /* edge */))
  {
    tmp302 = Greater((data->simulationInfo->realParameter[427] /* sysReq.tim4.delayTime PARAM */),0.0);
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */) = (!tmp302);
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[56]] /* $whenCondition60 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[56] /* $whenCondition60 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */) = 0 /* false */;
  }
  else if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[54]] /* $whenCondition59 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[54] /* $whenCondition59 DISCRETE */) /* edge */))
  {
    (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 1712
type: SIMPLE_ASSIGN
yHeaValResReq = if sysReq.tim4.y then 3 else sysReq.intSwi3.y
*/
void ReheatControllerFMU_eqFunction_1712(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1712};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[39]] /* yHeaValResReq DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */)?((modelica_integer) 3):(data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[29]] /* sysReq.intSwi3.y DISCRETE */));
  TRACE_POP
}
/*
equation index: 1713
type: SIMPLE_ASSIGN
sysReq.tim4.u = sysReq.les.lesHys.y
*/
void ReheatControllerFMU_eqFunction_1713(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1713};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[201]] /* sysReq.tim4.u DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */);
  TRACE_POP
}
/*
equation index: 1727
type: ALGORITHM

  assert(conLoo.conHea.cheYMinMax.k, conLoo.conHea.assMesYMinMax.message);
*/
void ReheatControllerFMU_eqFunction_1727(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1727};
  static int tmp303 = 0;
  if(!tmp303)
  {
    if(!(data->simulationInfo->booleanParameter[47] /* conLoo.conHea.cheYMinMax.k PARAM */))
    {
      {
        const char* assert_cond = "(conLoo.conHea.cheYMinMax.k)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA((data->simulationInfo->stringParameter[8] /* conLoo.conHea.assMesYMinMax.message PARAM */)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA((data->simulationInfo->stringParameter[8] /* conLoo.conHea.assMesYMinMax.message PARAM */)));
        }
      }
      tmp303 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1726
type: ALGORITHM

  assert(conLoo.conCoo.cheYMinMax.k, conLoo.conCoo.assMesYMinMax.message);
*/
void ReheatControllerFMU_eqFunction_1726(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1726};
  static int tmp304 = 0;
  if(!tmp304)
  {
    if(!(data->simulationInfo->booleanParameter[41] /* conLoo.conCoo.cheYMinMax.k PARAM */))
    {
      {
        const char* assert_cond = "(conLoo.conCoo.cheYMinMax.k)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA((data->simulationInfo->stringParameter[7] /* conLoo.conCoo.assMesYMinMax.message PARAM */)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA((data->simulationInfo->stringParameter[7] /* conLoo.conCoo.assMesYMinMax.message PARAM */)));
        }
      }
      tmp304 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1725
type: WHEN

when {$whenCondition71} then
  reinit(conLoo.conCoo.I.y,  conLoo.conCoo.addRes.y);
end when;
*/
void ReheatControllerFMU_eqFunction_1725(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1725};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[68]] /* $whenCondition71 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[68] /* $whenCondition71 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* conLoo.conCoo.I.y STATE(1) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[50]] /* conLoo.conCoo.addRes.y variable */);
    infoStreamPrint(OMC_LOG_EVENTS, 0, "reinit conLoo.conCoo.I.y = %g", (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* conLoo.conCoo.I.y STATE(1) */));
    data->simulationInfo->needToIterate = 1;
  }
  TRACE_POP
}
/*
equation index: 1724
type: WHEN

when {$whenCondition72} then
  reinit(conLoo.conHea.I.y,  conLoo.conHea.addRes.y);
end when;
*/
void ReheatControllerFMU_eqFunction_1724(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1724};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[69]] /* $whenCondition72 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[69] /* $whenCondition72 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* conLoo.conHea.I.y STATE(1) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[63]] /* conLoo.conHea.addRes.y variable */);
    infoStreamPrint(OMC_LOG_EVENTS, 0, "reinit conLoo.conHea.I.y = %g", (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* conLoo.conHea.I.y STATE(1) */));
    data->simulationInfo->needToIterate = 1;
  }
  TRACE_POP
}
/*
equation index: 1723
type: WHEN

when {$whenCondition73} then
  reinit(damVal.conDam.I.y,  damVal.conDam.addRes.y);
end when;
*/
void ReheatControllerFMU_eqFunction_1723(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1723};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[70]] /* $whenCondition73 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[70] /* $whenCondition73 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* damVal.conDam.I.y STATE(1) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[88]] /* damVal.conDam.addRes.y variable */);
    infoStreamPrint(OMC_LOG_EVENTS, 0, "reinit damVal.conDam.I.y = %g", (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* damVal.conDam.I.y STATE(1) */));
    data->simulationInfo->needToIterate = 1;
  }
  TRACE_POP
}
/*
equation index: 1722
type: WHEN

when {$whenCondition74} then
  reinit(damVal.conVal.I.y,  damVal.conVal.addRes.y);
end when;
*/
void ReheatControllerFMU_eqFunction_1722(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1722};
  if(((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[71]] /* $whenCondition74 DISCRETE */) && !(data->simulationInfo->booleanVarsPre[71] /* $whenCondition74 DISCRETE */) /* edge */))
  {
    (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* damVal.conVal.I.y STATE(1) */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[109]] /* damVal.conVal.addRes.y variable */);
    infoStreamPrint(OMC_LOG_EVENTS, 0, "reinit damVal.conVal.I.y = %g", (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* damVal.conVal.I.y STATE(1) */));
    data->simulationInfo->needToIterate = 1;
  }
  TRACE_POP
}
/*
equation index: 1721
type: ALGORITHM

  assert(ppmCO2Set > setPoi.addPar.y, "x2 must be bigger than x1 in ReheatControllerFMU.setPoi.lin");
*/
void ReheatControllerFMU_eqFunction_1721(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1721};
  modelica_boolean tmp305;
  static const MMC_DEFSTRINGLIT(tmp306,59,"x2 must be bigger than x1 in ReheatControllerFMU.setPoi.lin");
  static int tmp307 = 0;
  if(!tmp307)
  {
    tmp305 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[149]] /* setPoi.addPar.y variable */));
    if(!tmp305)
    {
      {
        const char* assert_cond = "(ppmCO2Set > setPoi.addPar.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Line.mo",36,5,38,30,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp306)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Line.mo",36,5,38,30,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp306)));
        }
      }
      tmp307 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1720
type: ALGORITHM

  assert(not ala.truDel6.y, "Warning: the valve is leaking.");
*/
void ReheatControllerFMU_eqFunction_1720(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1720};
  static const MMC_DEFSTRINGLIT(tmp308,30,"Warning: the valve is leaking.");
  static int tmp309 = 0;
  if(!tmp309)
  {
    if(!(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */)))
    {
      {
        const char* assert_cond = "(not ala.truDel6.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp308)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp308)));
        }
      }
      tmp309 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1719
type: ALGORITHM

  assert(ala.not7.y, "Warning: discharge air temperature is 8 degC less than the setpoint.");
*/
void ReheatControllerFMU_eqFunction_1719(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1719};
  static const MMC_DEFSTRINGLIT(tmp310,68,"Warning: discharge air temperature is 8 degC less than the setpoint.");
  static int tmp311 = 0;
  if(!tmp311)
  {
    if(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[110]] /* ala.not7.y DISCRETE */))
    {
      {
        const char* assert_cond = "(ala.not7.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp310)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp310)));
        }
      }
      tmp311 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1718
type: ALGORITHM

  assert(ala.not6.y, "Warning: discharge air temperature is 17 degC less than the setpoint.");
*/
void ReheatControllerFMU_eqFunction_1718(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1718};
  static const MMC_DEFSTRINGLIT(tmp312,69,"Warning: discharge air temperature is 17 degC less than the setpoint.");
  static int tmp313 = 0;
  if(!tmp313)
  {
    if(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[109]] /* ala.not6.y DISCRETE */))
    {
      {
        const char* assert_cond = "(ala.not6.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp312)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp312)));
        }
      }
      tmp313 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1717
type: ALGORITHM

  assert(not ala.truDel3.y, "Warning: the damper is leaking.");
*/
void ReheatControllerFMU_eqFunction_1717(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1717};
  static const MMC_DEFSTRINGLIT(tmp314,31,"Warning: the damper is leaking.");
  static int tmp315 = 0;
  if(!tmp315)
  {
    if(!(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */)))
    {
      {
        const char* assert_cond = "(not ala.truDel3.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp314)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp314)));
        }
      }
      tmp315 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1716
type: ALGORITHM

  assert(not ala.truDel2.y, "Warning: airflow sensor should be calibrated.");
*/
void ReheatControllerFMU_eqFunction_1716(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1716};
  static const MMC_DEFSTRINGLIT(tmp316,45,"Warning: airflow sensor should be calibrated.");
  static int tmp317 = 0;
  if(!tmp317)
  {
    if(!(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */)))
    {
      {
        const char* assert_cond = "(not ala.truDel2.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp316)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp316)));
        }
      }
      tmp317 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1715
type: ALGORITHM

  assert(ala.not2.y, "Warning: airflow is less than 70% of the setpoint.");
*/
void ReheatControllerFMU_eqFunction_1715(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1715};
  static const MMC_DEFSTRINGLIT(tmp318,50,"Warning: airflow is less than 70% of the setpoint.");
  static int tmp319 = 0;
  if(!tmp319)
  {
    if(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[108]] /* ala.not2.y DISCRETE */))
    {
      {
        const char* assert_cond = "(ala.not2.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp318)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp318)));
        }
      }
      tmp319 = 1;
    }
  }
  TRACE_POP
}
/*
equation index: 1714
type: ALGORITHM

  assert(ala.not1.y, "Warning: airflow is less than 50% of the setpoint.");
*/
void ReheatControllerFMU_eqFunction_1714(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1714};
  static const MMC_DEFSTRINGLIT(tmp320,50,"Warning: airflow is less than 50% of the setpoint.");
  static int tmp321 = 0;
  if(!tmp321)
  {
    if(!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[107]] /* ala.not1.y DISCRETE */))
    {
      {
        const char* assert_cond = "(ala.not1.y)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp320)));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Utilities/Assert.mo",11,3,11,45,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp320)));
        }
      }
      tmp321 = 1;
    }
  }
  TRACE_POP
}

OMC_DISABLE_OPT
int ReheatControllerFMU_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  ReheatControllerFMU_functionLocalKnownVars(data, threadData);
  ReheatControllerFMU_eqFunction_1181(data, threadData);

  ReheatControllerFMU_eqFunction_1182(data, threadData);

  ReheatControllerFMU_eqFunction_1183(data, threadData);

  ReheatControllerFMU_eqFunction_1184(data, threadData);

  ReheatControllerFMU_eqFunction_1185(data, threadData);

  ReheatControllerFMU_eqFunction_1186(data, threadData);

  ReheatControllerFMU_eqFunction_1187(data, threadData);

  ReheatControllerFMU_eqFunction_1188(data, threadData);

  ReheatControllerFMU_eqFunction_1189(data, threadData);

  ReheatControllerFMU_eqFunction_1190(data, threadData);

  ReheatControllerFMU_eqFunction_1191(data, threadData);

  ReheatControllerFMU_eqFunction_1192(data, threadData);

  ReheatControllerFMU_eqFunction_1193(data, threadData);

  ReheatControllerFMU_eqFunction_1194(data, threadData);

  ReheatControllerFMU_eqFunction_1195(data, threadData);

  ReheatControllerFMU_eqFunction_1196(data, threadData);

  ReheatControllerFMU_eqFunction_1197(data, threadData);

  ReheatControllerFMU_eqFunction_1198(data, threadData);

  ReheatControllerFMU_eqFunction_1199(data, threadData);

  ReheatControllerFMU_eqFunction_1200(data, threadData);

  ReheatControllerFMU_eqFunction_1201(data, threadData);

  ReheatControllerFMU_eqFunction_1202(data, threadData);

  ReheatControllerFMU_eqFunction_1203(data, threadData);

  ReheatControllerFMU_eqFunction_1204(data, threadData);

  ReheatControllerFMU_eqFunction_1205(data, threadData);

  ReheatControllerFMU_eqFunction_1206(data, threadData);

  ReheatControllerFMU_eqFunction_1207(data, threadData);

  ReheatControllerFMU_eqFunction_1208(data, threadData);

  ReheatControllerFMU_eqFunction_1209(data, threadData);

  ReheatControllerFMU_eqFunction_1210(data, threadData);

  ReheatControllerFMU_eqFunction_1211(data, threadData);

  ReheatControllerFMU_eqFunction_1212(data, threadData);

  ReheatControllerFMU_eqFunction_1213(data, threadData);

  ReheatControllerFMU_eqFunction_1214(data, threadData);

  ReheatControllerFMU_eqFunction_1215(data, threadData);

  ReheatControllerFMU_eqFunction_1216(data, threadData);

  ReheatControllerFMU_eqFunction_1217(data, threadData);

  ReheatControllerFMU_eqFunction_1218(data, threadData);

  ReheatControllerFMU_eqFunction_1219(data, threadData);

  ReheatControllerFMU_eqFunction_1220(data, threadData);

  ReheatControllerFMU_eqFunction_1221(data, threadData);

  ReheatControllerFMU_eqFunction_1222(data, threadData);

  ReheatControllerFMU_eqFunction_1223(data, threadData);

  ReheatControllerFMU_eqFunction_1224(data, threadData);

  ReheatControllerFMU_eqFunction_1225(data, threadData);

  ReheatControllerFMU_eqFunction_1226(data, threadData);

  ReheatControllerFMU_eqFunction_1227(data, threadData);

  ReheatControllerFMU_eqFunction_1228(data, threadData);

  ReheatControllerFMU_eqFunction_1229(data, threadData);

  ReheatControllerFMU_eqFunction_1230(data, threadData);

  ReheatControllerFMU_eqFunction_1231(data, threadData);

  ReheatControllerFMU_eqFunction_1232(data, threadData);

  ReheatControllerFMU_eqFunction_1233(data, threadData);

  ReheatControllerFMU_eqFunction_1234(data, threadData);

  ReheatControllerFMU_eqFunction_1235(data, threadData);

  ReheatControllerFMU_eqFunction_1236(data, threadData);

  ReheatControllerFMU_eqFunction_1237(data, threadData);

  ReheatControllerFMU_eqFunction_1238(data, threadData);

  ReheatControllerFMU_eqFunction_1239(data, threadData);

  ReheatControllerFMU_eqFunction_1240(data, threadData);

  ReheatControllerFMU_eqFunction_1241(data, threadData);

  ReheatControllerFMU_eqFunction_1242(data, threadData);

  ReheatControllerFMU_eqFunction_1243(data, threadData);

  ReheatControllerFMU_eqFunction_1244(data, threadData);

  ReheatControllerFMU_eqFunction_1245(data, threadData);

  ReheatControllerFMU_eqFunction_1246(data, threadData);

  ReheatControllerFMU_eqFunction_1247(data, threadData);

  ReheatControllerFMU_eqFunction_1248(data, threadData);

  ReheatControllerFMU_eqFunction_1249(data, threadData);

  ReheatControllerFMU_eqFunction_1250(data, threadData);

  ReheatControllerFMU_eqFunction_1251(data, threadData);

  ReheatControllerFMU_eqFunction_1252(data, threadData);

  ReheatControllerFMU_eqFunction_1253(data, threadData);

  ReheatControllerFMU_eqFunction_1254(data, threadData);

  ReheatControllerFMU_eqFunction_1255(data, threadData);

  ReheatControllerFMU_eqFunction_1256(data, threadData);

  ReheatControllerFMU_eqFunction_1257(data, threadData);

  ReheatControllerFMU_eqFunction_1258(data, threadData);

  ReheatControllerFMU_eqFunction_1259(data, threadData);

  ReheatControllerFMU_eqFunction_1260(data, threadData);

  ReheatControllerFMU_eqFunction_1261(data, threadData);

  ReheatControllerFMU_eqFunction_1262(data, threadData);

  ReheatControllerFMU_eqFunction_1263(data, threadData);

  ReheatControllerFMU_eqFunction_1264(data, threadData);

  ReheatControllerFMU_eqFunction_1265(data, threadData);

  ReheatControllerFMU_eqFunction_1266(data, threadData);

  ReheatControllerFMU_eqFunction_1267(data, threadData);

  ReheatControllerFMU_eqFunction_1268(data, threadData);

  ReheatControllerFMU_eqFunction_1269(data, threadData);

  ReheatControllerFMU_eqFunction_1270(data, threadData);

  ReheatControllerFMU_eqFunction_1271(data, threadData);

  ReheatControllerFMU_eqFunction_1272(data, threadData);

  ReheatControllerFMU_eqFunction_1273(data, threadData);

  ReheatControllerFMU_eqFunction_1274(data, threadData);

  ReheatControllerFMU_eqFunction_1275(data, threadData);

  ReheatControllerFMU_eqFunction_1276(data, threadData);

  ReheatControllerFMU_eqFunction_1277(data, threadData);

  ReheatControllerFMU_eqFunction_1278(data, threadData);

  ReheatControllerFMU_eqFunction_1279(data, threadData);

  ReheatControllerFMU_eqFunction_1280(data, threadData);

  ReheatControllerFMU_eqFunction_1281(data, threadData);

  ReheatControllerFMU_eqFunction_1282(data, threadData);

  ReheatControllerFMU_eqFunction_1283(data, threadData);

  ReheatControllerFMU_eqFunction_1284(data, threadData);

  ReheatControllerFMU_eqFunction_1285(data, threadData);

  ReheatControllerFMU_eqFunction_1286(data, threadData);

  ReheatControllerFMU_eqFunction_1287(data, threadData);

  ReheatControllerFMU_eqFunction_1288(data, threadData);

  ReheatControllerFMU_eqFunction_1289(data, threadData);

  ReheatControllerFMU_eqFunction_1290(data, threadData);

  ReheatControllerFMU_eqFunction_1291(data, threadData);

  ReheatControllerFMU_eqFunction_1292(data, threadData);

  ReheatControllerFMU_eqFunction_1293(data, threadData);

  ReheatControllerFMU_eqFunction_1294(data, threadData);

  ReheatControllerFMU_eqFunction_1295(data, threadData);

  ReheatControllerFMU_eqFunction_1296(data, threadData);

  ReheatControllerFMU_eqFunction_1297(data, threadData);

  ReheatControllerFMU_eqFunction_1298(data, threadData);

  ReheatControllerFMU_eqFunction_1299(data, threadData);

  ReheatControllerFMU_eqFunction_1300(data, threadData);

  ReheatControllerFMU_eqFunction_1301(data, threadData);

  ReheatControllerFMU_eqFunction_1302(data, threadData);

  ReheatControllerFMU_eqFunction_1303(data, threadData);

  ReheatControllerFMU_eqFunction_1304(data, threadData);

  ReheatControllerFMU_eqFunction_1305(data, threadData);

  ReheatControllerFMU_eqFunction_1306(data, threadData);

  ReheatControllerFMU_eqFunction_1307(data, threadData);

  ReheatControllerFMU_eqFunction_1308(data, threadData);

  ReheatControllerFMU_eqFunction_1309(data, threadData);

  ReheatControllerFMU_eqFunction_1310(data, threadData);

  ReheatControllerFMU_eqFunction_1311(data, threadData);

  ReheatControllerFMU_eqFunction_1312(data, threadData);

  ReheatControllerFMU_eqFunction_1313(data, threadData);

  ReheatControllerFMU_eqFunction_1314(data, threadData);

  ReheatControllerFMU_eqFunction_1315(data, threadData);

  ReheatControllerFMU_eqFunction_1316(data, threadData);

  ReheatControllerFMU_eqFunction_1317(data, threadData);

  ReheatControllerFMU_eqFunction_1318(data, threadData);

  ReheatControllerFMU_eqFunction_1319(data, threadData);

  ReheatControllerFMU_eqFunction_1320(data, threadData);

  ReheatControllerFMU_eqFunction_1321(data, threadData);

  ReheatControllerFMU_eqFunction_1322(data, threadData);

  ReheatControllerFMU_eqFunction_1323(data, threadData);

  ReheatControllerFMU_eqFunction_1324(data, threadData);

  ReheatControllerFMU_eqFunction_1325(data, threadData);

  ReheatControllerFMU_eqFunction_1326(data, threadData);

  ReheatControllerFMU_eqFunction_1327(data, threadData);

  ReheatControllerFMU_eqFunction_1328(data, threadData);

  ReheatControllerFMU_eqFunction_1329(data, threadData);

  ReheatControllerFMU_eqFunction_1330(data, threadData);

  ReheatControllerFMU_eqFunction_1331(data, threadData);

  ReheatControllerFMU_eqFunction_1332(data, threadData);

  ReheatControllerFMU_eqFunction_1333(data, threadData);

  ReheatControllerFMU_eqFunction_1334(data, threadData);

  ReheatControllerFMU_eqFunction_1335(data, threadData);

  ReheatControllerFMU_eqFunction_1336(data, threadData);

  ReheatControllerFMU_eqFunction_1337(data, threadData);

  ReheatControllerFMU_eqFunction_1338(data, threadData);

  ReheatControllerFMU_eqFunction_1339(data, threadData);

  ReheatControllerFMU_eqFunction_1340(data, threadData);

  ReheatControllerFMU_eqFunction_1341(data, threadData);

  ReheatControllerFMU_eqFunction_1342(data, threadData);

  ReheatControllerFMU_eqFunction_1343(data, threadData);

  ReheatControllerFMU_eqFunction_1344(data, threadData);

  ReheatControllerFMU_eqFunction_1345(data, threadData);

  ReheatControllerFMU_eqFunction_1346(data, threadData);

  ReheatControllerFMU_eqFunction_1347(data, threadData);

  ReheatControllerFMU_eqFunction_1348(data, threadData);

  ReheatControllerFMU_eqFunction_1349(data, threadData);

  ReheatControllerFMU_eqFunction_1350(data, threadData);

  ReheatControllerFMU_eqFunction_1351(data, threadData);

  ReheatControllerFMU_eqFunction_1352(data, threadData);

  ReheatControllerFMU_eqFunction_1353(data, threadData);

  ReheatControllerFMU_eqFunction_1354(data, threadData);

  ReheatControllerFMU_eqFunction_1355(data, threadData);

  ReheatControllerFMU_eqFunction_1356(data, threadData);

  ReheatControllerFMU_eqFunction_1357(data, threadData);

  ReheatControllerFMU_eqFunction_1358(data, threadData);

  ReheatControllerFMU_eqFunction_1359(data, threadData);

  ReheatControllerFMU_eqFunction_1363(data, threadData);

  ReheatControllerFMU_eqFunction_1367(data, threadData);

  ReheatControllerFMU_eqFunction_1368(data, threadData);

  ReheatControllerFMU_eqFunction_1369(data, threadData);

  ReheatControllerFMU_eqFunction_1370(data, threadData);

  ReheatControllerFMU_eqFunction_1371(data, threadData);

  ReheatControllerFMU_eqFunction_1373(data, threadData);

  ReheatControllerFMU_eqFunction_1374(data, threadData);

  ReheatControllerFMU_eqFunction_1375(data, threadData);

  ReheatControllerFMU_eqFunction_1376(data, threadData);

  ReheatControllerFMU_eqFunction_1377(data, threadData);

  ReheatControllerFMU_eqFunction_1378(data, threadData);

  ReheatControllerFMU_eqFunction_1379(data, threadData);

  ReheatControllerFMU_eqFunction_1380(data, threadData);

  ReheatControllerFMU_eqFunction_1381(data, threadData);

  ReheatControllerFMU_eqFunction_1382(data, threadData);

  ReheatControllerFMU_eqFunction_1383(data, threadData);

  ReheatControllerFMU_eqFunction_1384(data, threadData);

  ReheatControllerFMU_eqFunction_1385(data, threadData);

  ReheatControllerFMU_eqFunction_1388(data, threadData);

  ReheatControllerFMU_eqFunction_1391(data, threadData);

  ReheatControllerFMU_eqFunction_1392(data, threadData);

  ReheatControllerFMU_eqFunction_1393(data, threadData);

  ReheatControllerFMU_eqFunction_1394(data, threadData);

  ReheatControllerFMU_eqFunction_1396(data, threadData);

  ReheatControllerFMU_eqFunction_1397(data, threadData);

  ReheatControllerFMU_eqFunction_1398(data, threadData);

  ReheatControllerFMU_eqFunction_1402(data, threadData);

  ReheatControllerFMU_eqFunction_1406(data, threadData);

  ReheatControllerFMU_eqFunction_1407(data, threadData);

  ReheatControllerFMU_eqFunction_1408(data, threadData);

  ReheatControllerFMU_eqFunction_1409(data, threadData);

  ReheatControllerFMU_eqFunction_1410(data, threadData);

  ReheatControllerFMU_eqFunction_1411(data, threadData);

  ReheatControllerFMU_eqFunction_1412(data, threadData);

  ReheatControllerFMU_eqFunction_1416(data, threadData);

  ReheatControllerFMU_eqFunction_1417(data, threadData);

  ReheatControllerFMU_eqFunction_1421(data, threadData);

  ReheatControllerFMU_eqFunction_1422(data, threadData);

  ReheatControllerFMU_eqFunction_1423(data, threadData);

  ReheatControllerFMU_eqFunction_1424(data, threadData);

  ReheatControllerFMU_eqFunction_1428(data, threadData);

  ReheatControllerFMU_eqFunction_1429(data, threadData);

  ReheatControllerFMU_eqFunction_1430(data, threadData);

  ReheatControllerFMU_eqFunction_1431(data, threadData);

  ReheatControllerFMU_eqFunction_1432(data, threadData);

  ReheatControllerFMU_eqFunction_1433(data, threadData);

  ReheatControllerFMU_eqFunction_1434(data, threadData);

  ReheatControllerFMU_eqFunction_1435(data, threadData);

  ReheatControllerFMU_eqFunction_1436(data, threadData);

  ReheatControllerFMU_eqFunction_1438(data, threadData);

  ReheatControllerFMU_eqFunction_1439(data, threadData);

  ReheatControllerFMU_eqFunction_1440(data, threadData);

  ReheatControllerFMU_eqFunction_1441(data, threadData);

  ReheatControllerFMU_eqFunction_1443(data, threadData);

  ReheatControllerFMU_eqFunction_1445(data, threadData);

  ReheatControllerFMU_eqFunction_1446(data, threadData);

  ReheatControllerFMU_eqFunction_1447(data, threadData);

  ReheatControllerFMU_eqFunction_1448(data, threadData);

  ReheatControllerFMU_eqFunction_1449(data, threadData);

  ReheatControllerFMU_eqFunction_1450(data, threadData);

  ReheatControllerFMU_eqFunction_1451(data, threadData);

  ReheatControllerFMU_eqFunction_1452(data, threadData);

  ReheatControllerFMU_eqFunction_1456(data, threadData);

  ReheatControllerFMU_eqFunction_1457(data, threadData);

  ReheatControllerFMU_eqFunction_1461(data, threadData);

  ReheatControllerFMU_eqFunction_1462(data, threadData);

  ReheatControllerFMU_eqFunction_1463(data, threadData);

  ReheatControllerFMU_eqFunction_1464(data, threadData);

  ReheatControllerFMU_eqFunction_1465(data, threadData);

  ReheatControllerFMU_eqFunction_1466(data, threadData);

  ReheatControllerFMU_eqFunction_1467(data, threadData);

  ReheatControllerFMU_eqFunction_1468(data, threadData);

  ReheatControllerFMU_eqFunction_1469(data, threadData);

  ReheatControllerFMU_eqFunction_1471(data, threadData);

  ReheatControllerFMU_eqFunction_1472(data, threadData);

  ReheatControllerFMU_eqFunction_1473(data, threadData);

  ReheatControllerFMU_eqFunction_1474(data, threadData);

  ReheatControllerFMU_eqFunction_1475(data, threadData);

  ReheatControllerFMU_eqFunction_1477(data, threadData);

  ReheatControllerFMU_eqFunction_1479(data, threadData);

  ReheatControllerFMU_eqFunction_1480(data, threadData);

  ReheatControllerFMU_eqFunction_1481(data, threadData);

  ReheatControllerFMU_eqFunction_1482(data, threadData);

  ReheatControllerFMU_eqFunction_1483(data, threadData);

  ReheatControllerFMU_eqFunction_1484(data, threadData);

  ReheatControllerFMU_eqFunction_1485(data, threadData);

  ReheatControllerFMU_eqFunction_1486(data, threadData);

  ReheatControllerFMU_eqFunction_1487(data, threadData);

  ReheatControllerFMU_eqFunction_1488(data, threadData);

  ReheatControllerFMU_eqFunction_1489(data, threadData);

  ReheatControllerFMU_eqFunction_1493(data, threadData);

  ReheatControllerFMU_eqFunction_1497(data, threadData);

  ReheatControllerFMU_eqFunction_1498(data, threadData);

  ReheatControllerFMU_eqFunction_1499(data, threadData);

  ReheatControllerFMU_eqFunction_1500(data, threadData);

  ReheatControllerFMU_eqFunction_1501(data, threadData);

  ReheatControllerFMU_eqFunction_1505(data, threadData);

  ReheatControllerFMU_eqFunction_1509(data, threadData);

  ReheatControllerFMU_eqFunction_1510(data, threadData);

  ReheatControllerFMU_eqFunction_1511(data, threadData);

  ReheatControllerFMU_eqFunction_1512(data, threadData);

  ReheatControllerFMU_eqFunction_1513(data, threadData);

  ReheatControllerFMU_eqFunction_1514(data, threadData);

  ReheatControllerFMU_eqFunction_1515(data, threadData);

  ReheatControllerFMU_eqFunction_1516(data, threadData);

  ReheatControllerFMU_eqFunction_1517(data, threadData);

  ReheatControllerFMU_eqFunction_1521(data, threadData);

  ReheatControllerFMU_eqFunction_1522(data, threadData);

  ReheatControllerFMU_eqFunction_1523(data, threadData);

  ReheatControllerFMU_eqFunction_1524(data, threadData);

  ReheatControllerFMU_eqFunction_1525(data, threadData);

  ReheatControllerFMU_eqFunction_1526(data, threadData);

  ReheatControllerFMU_eqFunction_1527(data, threadData);

  ReheatControllerFMU_eqFunction_1531(data, threadData);

  ReheatControllerFMU_eqFunction_1532(data, threadData);

  ReheatControllerFMU_eqFunction_1533(data, threadData);

  ReheatControllerFMU_eqFunction_1534(data, threadData);

  ReheatControllerFMU_eqFunction_1535(data, threadData);

  ReheatControllerFMU_eqFunction_1536(data, threadData);

  ReheatControllerFMU_eqFunction_1537(data, threadData);

  ReheatControllerFMU_eqFunction_1538(data, threadData);

  ReheatControllerFMU_eqFunction_1539(data, threadData);

  ReheatControllerFMU_eqFunction_1540(data, threadData);

  ReheatControllerFMU_eqFunction_1541(data, threadData);

  ReheatControllerFMU_eqFunction_1542(data, threadData);

  ReheatControllerFMU_eqFunction_1543(data, threadData);

  ReheatControllerFMU_eqFunction_1544(data, threadData);

  ReheatControllerFMU_eqFunction_1548(data, threadData);

  ReheatControllerFMU_eqFunction_1549(data, threadData);

  ReheatControllerFMU_eqFunction_1553(data, threadData);

  ReheatControllerFMU_eqFunction_1554(data, threadData);

  ReheatControllerFMU_eqFunction_1555(data, threadData);

  ReheatControllerFMU_eqFunction_1556(data, threadData);

  ReheatControllerFMU_eqFunction_1557(data, threadData);

  ReheatControllerFMU_eqFunction_1558(data, threadData);

  ReheatControllerFMU_eqFunction_1559(data, threadData);

  ReheatControllerFMU_eqFunction_1560(data, threadData);

  ReheatControllerFMU_eqFunction_1561(data, threadData);

  ReheatControllerFMU_eqFunction_1562(data, threadData);

  ReheatControllerFMU_eqFunction_1563(data, threadData);

  ReheatControllerFMU_eqFunction_1564(data, threadData);

  ReheatControllerFMU_eqFunction_1565(data, threadData);

  ReheatControllerFMU_eqFunction_1566(data, threadData);

  ReheatControllerFMU_eqFunction_1567(data, threadData);

  ReheatControllerFMU_eqFunction_1568(data, threadData);

  ReheatControllerFMU_eqFunction_1569(data, threadData);

  ReheatControllerFMU_eqFunction_1570(data, threadData);

  ReheatControllerFMU_eqFunction_1571(data, threadData);

  ReheatControllerFMU_eqFunction_1572(data, threadData);

  ReheatControllerFMU_eqFunction_1573(data, threadData);

  ReheatControllerFMU_eqFunction_1574(data, threadData);

  ReheatControllerFMU_eqFunction_1575(data, threadData);

  ReheatControllerFMU_eqFunction_1579(data, threadData);

  ReheatControllerFMU_eqFunction_1580(data, threadData);

  ReheatControllerFMU_eqFunction_1581(data, threadData);

  ReheatControllerFMU_eqFunction_1582(data, threadData);

  ReheatControllerFMU_eqFunction_1586(data, threadData);

  ReheatControllerFMU_eqFunction_1587(data, threadData);

  ReheatControllerFMU_eqFunction_1588(data, threadData);

  ReheatControllerFMU_eqFunction_1589(data, threadData);

  ReheatControllerFMU_eqFunction_1590(data, threadData);

  ReheatControllerFMU_eqFunction_1591(data, threadData);

  ReheatControllerFMU_eqFunction_1595(data, threadData);

  ReheatControllerFMU_eqFunction_1596(data, threadData);

  ReheatControllerFMU_eqFunction_1600(data, threadData);

  ReheatControllerFMU_eqFunction_1601(data, threadData);

  ReheatControllerFMU_eqFunction_1602(data, threadData);

  ReheatControllerFMU_eqFunction_1606(data, threadData);

  ReheatControllerFMU_eqFunction_1607(data, threadData);

  ReheatControllerFMU_eqFunction_1611(data, threadData);

  ReheatControllerFMU_eqFunction_1612(data, threadData);

  ReheatControllerFMU_eqFunction_1613(data, threadData);

  ReheatControllerFMU_eqFunction_1617(data, threadData);

  ReheatControllerFMU_eqFunction_1618(data, threadData);

  ReheatControllerFMU_eqFunction_1619(data, threadData);

  ReheatControllerFMU_eqFunction_1620(data, threadData);

  ReheatControllerFMU_eqFunction_1621(data, threadData);

  ReheatControllerFMU_eqFunction_1622(data, threadData);

  ReheatControllerFMU_eqFunction_1623(data, threadData);

  ReheatControllerFMU_eqFunction_1624(data, threadData);

  ReheatControllerFMU_eqFunction_1628(data, threadData);

  ReheatControllerFMU_eqFunction_1632(data, threadData);

  ReheatControllerFMU_eqFunction_1633(data, threadData);

  ReheatControllerFMU_eqFunction_1634(data, threadData);

  ReheatControllerFMU_eqFunction_1635(data, threadData);

  ReheatControllerFMU_eqFunction_1636(data, threadData);

  ReheatControllerFMU_eqFunction_1637(data, threadData);

  ReheatControllerFMU_eqFunction_1638(data, threadData);

  ReheatControllerFMU_eqFunction_1639(data, threadData);

  ReheatControllerFMU_eqFunction_1640(data, threadData);

  ReheatControllerFMU_eqFunction_1644(data, threadData);

  ReheatControllerFMU_eqFunction_1648(data, threadData);

  ReheatControllerFMU_eqFunction_1649(data, threadData);

  ReheatControllerFMU_eqFunction_1650(data, threadData);

  ReheatControllerFMU_eqFunction_1651(data, threadData);

  ReheatControllerFMU_eqFunction_1652(data, threadData);

  ReheatControllerFMU_eqFunction_1653(data, threadData);

  ReheatControllerFMU_eqFunction_1654(data, threadData);

  ReheatControllerFMU_eqFunction_1655(data, threadData);

  ReheatControllerFMU_eqFunction_1656(data, threadData);

  ReheatControllerFMU_eqFunction_1657(data, threadData);

  ReheatControllerFMU_eqFunction_1658(data, threadData);

  ReheatControllerFMU_eqFunction_1659(data, threadData);

  ReheatControllerFMU_eqFunction_1660(data, threadData);

  ReheatControllerFMU_eqFunction_1661(data, threadData);

  ReheatControllerFMU_eqFunction_1662(data, threadData);

  ReheatControllerFMU_eqFunction_1663(data, threadData);

  ReheatControllerFMU_eqFunction_1664(data, threadData);

  ReheatControllerFMU_eqFunction_1665(data, threadData);

  ReheatControllerFMU_eqFunction_1666(data, threadData);

  ReheatControllerFMU_eqFunction_1667(data, threadData);

  ReheatControllerFMU_eqFunction_1668(data, threadData);

  ReheatControllerFMU_eqFunction_1672(data, threadData);

  ReheatControllerFMU_eqFunction_1673(data, threadData);

  ReheatControllerFMU_eqFunction_1677(data, threadData);

  ReheatControllerFMU_eqFunction_1678(data, threadData);

  ReheatControllerFMU_eqFunction_1679(data, threadData);

  ReheatControllerFMU_eqFunction_1680(data, threadData);

  ReheatControllerFMU_eqFunction_1681(data, threadData);

  ReheatControllerFMU_eqFunction_1682(data, threadData);

  ReheatControllerFMU_eqFunction_1683(data, threadData);

  ReheatControllerFMU_eqFunction_1684(data, threadData);

  ReheatControllerFMU_eqFunction_1685(data, threadData);

  ReheatControllerFMU_eqFunction_1686(data, threadData);

  ReheatControllerFMU_eqFunction_1687(data, threadData);

  ReheatControllerFMU_eqFunction_1688(data, threadData);

  ReheatControllerFMU_eqFunction_1689(data, threadData);

  ReheatControllerFMU_eqFunction_1690(data, threadData);

  ReheatControllerFMU_eqFunction_1691(data, threadData);

  ReheatControllerFMU_eqFunction_1695(data, threadData);

  ReheatControllerFMU_eqFunction_1699(data, threadData);

  ReheatControllerFMU_eqFunction_1700(data, threadData);

  ReheatControllerFMU_eqFunction_1701(data, threadData);

  ReheatControllerFMU_eqFunction_1702(data, threadData);

  ReheatControllerFMU_eqFunction_1703(data, threadData);

  ReheatControllerFMU_eqFunction_1704(data, threadData);

  ReheatControllerFMU_eqFunction_1708(data, threadData);

  ReheatControllerFMU_eqFunction_1712(data, threadData);

  ReheatControllerFMU_eqFunction_1713(data, threadData);

  ReheatControllerFMU_eqFunction_1727(data, threadData);

  ReheatControllerFMU_eqFunction_1726(data, threadData);

  ReheatControllerFMU_eqFunction_1725(data, threadData);

  ReheatControllerFMU_eqFunction_1724(data, threadData);

  ReheatControllerFMU_eqFunction_1723(data, threadData);

  ReheatControllerFMU_eqFunction_1722(data, threadData);

  ReheatControllerFMU_eqFunction_1721(data, threadData);

  ReheatControllerFMU_eqFunction_1720(data, threadData);

  ReheatControllerFMU_eqFunction_1719(data, threadData);

  ReheatControllerFMU_eqFunction_1718(data, threadData);

  ReheatControllerFMU_eqFunction_1717(data, threadData);

  ReheatControllerFMU_eqFunction_1716(data, threadData);

  ReheatControllerFMU_eqFunction_1715(data, threadData);

  ReheatControllerFMU_eqFunction_1714(data, threadData);
  data->simulationInfo->discreteCall = 0;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int ReheatControllerFMU_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH


  TRACE_POP
  return 0;
}

/* forwarded equations */
extern void ReheatControllerFMU_eqFunction_1184(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1185(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1186(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1187(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1188(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1189(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1190(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1191(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1192(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1193(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1194(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1195(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1196(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1197(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1198(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1199(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1225(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1226(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1227(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1228(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1229(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1230(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1231(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1232(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1233(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1235(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1236(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1238(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1239(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1241(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1242(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1243(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1244(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1245(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1246(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1247(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1248(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1249(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1251(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1252(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1254(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1255(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1257(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1259(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1288(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1289(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1290(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1291(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1292(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1293(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1294(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1295(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1296(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1297(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1298(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1299(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1300(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1304(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1305(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1306(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1307(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1308(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1309(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1310(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1311(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1312(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1313(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1314(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1315(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1324(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1325(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1326(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1327(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1328(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1330(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1331(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1332(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1333(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1334(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1338(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1339(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1340(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1341(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1342(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1343(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1344(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1345(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1346(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1347(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1348(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1349(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1350(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1351(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1354(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1355(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1423(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1428(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1429(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1430(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1431(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1432(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1433(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1434(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1435(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1438(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1445(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1446(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1447(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1448(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1449(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1450(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1451(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1456(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1461(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1462(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1463(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1464(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1465(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1466(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1467(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1468(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1471(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1472(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1473(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1474(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1479(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1480(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1481(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1482(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1483(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1484(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1532(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1534(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1535(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1536(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1537(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1538(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1560(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1561(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1563(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1564(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1618(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1619(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1656(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1657(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1658(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1659(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1660(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1682(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1683(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1685(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1686(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
  int id;

  static void (*const eqFunctions[152])(DATA*, threadData_t*) = {
    ReheatControllerFMU_eqFunction_1184,
    ReheatControllerFMU_eqFunction_1185,
    ReheatControllerFMU_eqFunction_1186,
    ReheatControllerFMU_eqFunction_1187,
    ReheatControllerFMU_eqFunction_1188,
    ReheatControllerFMU_eqFunction_1189,
    ReheatControllerFMU_eqFunction_1190,
    ReheatControllerFMU_eqFunction_1191,
    ReheatControllerFMU_eqFunction_1192,
    ReheatControllerFMU_eqFunction_1193,
    ReheatControllerFMU_eqFunction_1194,
    ReheatControllerFMU_eqFunction_1195,
    ReheatControllerFMU_eqFunction_1196,
    ReheatControllerFMU_eqFunction_1197,
    ReheatControllerFMU_eqFunction_1198,
    ReheatControllerFMU_eqFunction_1199,
    ReheatControllerFMU_eqFunction_1225,
    ReheatControllerFMU_eqFunction_1226,
    ReheatControllerFMU_eqFunction_1227,
    ReheatControllerFMU_eqFunction_1228,
    ReheatControllerFMU_eqFunction_1229,
    ReheatControllerFMU_eqFunction_1230,
    ReheatControllerFMU_eqFunction_1231,
    ReheatControllerFMU_eqFunction_1232,
    ReheatControllerFMU_eqFunction_1233,
    ReheatControllerFMU_eqFunction_1235,
    ReheatControllerFMU_eqFunction_1236,
    ReheatControllerFMU_eqFunction_1238,
    ReheatControllerFMU_eqFunction_1239,
    ReheatControllerFMU_eqFunction_1241,
    ReheatControllerFMU_eqFunction_1242,
    ReheatControllerFMU_eqFunction_1243,
    ReheatControllerFMU_eqFunction_1244,
    ReheatControllerFMU_eqFunction_1245,
    ReheatControllerFMU_eqFunction_1246,
    ReheatControllerFMU_eqFunction_1247,
    ReheatControllerFMU_eqFunction_1248,
    ReheatControllerFMU_eqFunction_1249,
    ReheatControllerFMU_eqFunction_1251,
    ReheatControllerFMU_eqFunction_1252,
    ReheatControllerFMU_eqFunction_1254,
    ReheatControllerFMU_eqFunction_1255,
    ReheatControllerFMU_eqFunction_1257,
    ReheatControllerFMU_eqFunction_1259,
    ReheatControllerFMU_eqFunction_1288,
    ReheatControllerFMU_eqFunction_1289,
    ReheatControllerFMU_eqFunction_1290,
    ReheatControllerFMU_eqFunction_1291,
    ReheatControllerFMU_eqFunction_1292,
    ReheatControllerFMU_eqFunction_1293,
    ReheatControllerFMU_eqFunction_1294,
    ReheatControllerFMU_eqFunction_1295,
    ReheatControllerFMU_eqFunction_1296,
    ReheatControllerFMU_eqFunction_1297,
    ReheatControllerFMU_eqFunction_1298,
    ReheatControllerFMU_eqFunction_1299,
    ReheatControllerFMU_eqFunction_1300,
    ReheatControllerFMU_eqFunction_1304,
    ReheatControllerFMU_eqFunction_1305,
    ReheatControllerFMU_eqFunction_1306,
    ReheatControllerFMU_eqFunction_1307,
    ReheatControllerFMU_eqFunction_1308,
    ReheatControllerFMU_eqFunction_1309,
    ReheatControllerFMU_eqFunction_1310,
    ReheatControllerFMU_eqFunction_1311,
    ReheatControllerFMU_eqFunction_1312,
    ReheatControllerFMU_eqFunction_1313,
    ReheatControllerFMU_eqFunction_1314,
    ReheatControllerFMU_eqFunction_1315,
    ReheatControllerFMU_eqFunction_1324,
    ReheatControllerFMU_eqFunction_1325,
    ReheatControllerFMU_eqFunction_1326,
    ReheatControllerFMU_eqFunction_1327,
    ReheatControllerFMU_eqFunction_1328,
    ReheatControllerFMU_eqFunction_1330,
    ReheatControllerFMU_eqFunction_1331,
    ReheatControllerFMU_eqFunction_1332,
    ReheatControllerFMU_eqFunction_1333,
    ReheatControllerFMU_eqFunction_1334,
    ReheatControllerFMU_eqFunction_1338,
    ReheatControllerFMU_eqFunction_1339,
    ReheatControllerFMU_eqFunction_1340,
    ReheatControllerFMU_eqFunction_1341,
    ReheatControllerFMU_eqFunction_1342,
    ReheatControllerFMU_eqFunction_1343,
    ReheatControllerFMU_eqFunction_1344,
    ReheatControllerFMU_eqFunction_1345,
    ReheatControllerFMU_eqFunction_1346,
    ReheatControllerFMU_eqFunction_1347,
    ReheatControllerFMU_eqFunction_1348,
    ReheatControllerFMU_eqFunction_1349,
    ReheatControllerFMU_eqFunction_1350,
    ReheatControllerFMU_eqFunction_1351,
    ReheatControllerFMU_eqFunction_1354,
    ReheatControllerFMU_eqFunction_1355,
    ReheatControllerFMU_eqFunction_1423,
    ReheatControllerFMU_eqFunction_1428,
    ReheatControllerFMU_eqFunction_1429,
    ReheatControllerFMU_eqFunction_1430,
    ReheatControllerFMU_eqFunction_1431,
    ReheatControllerFMU_eqFunction_1432,
    ReheatControllerFMU_eqFunction_1433,
    ReheatControllerFMU_eqFunction_1434,
    ReheatControllerFMU_eqFunction_1435,
    ReheatControllerFMU_eqFunction_1438,
    ReheatControllerFMU_eqFunction_1445,
    ReheatControllerFMU_eqFunction_1446,
    ReheatControllerFMU_eqFunction_1447,
    ReheatControllerFMU_eqFunction_1448,
    ReheatControllerFMU_eqFunction_1449,
    ReheatControllerFMU_eqFunction_1450,
    ReheatControllerFMU_eqFunction_1451,
    ReheatControllerFMU_eqFunction_1456,
    ReheatControllerFMU_eqFunction_1461,
    ReheatControllerFMU_eqFunction_1462,
    ReheatControllerFMU_eqFunction_1463,
    ReheatControllerFMU_eqFunction_1464,
    ReheatControllerFMU_eqFunction_1465,
    ReheatControllerFMU_eqFunction_1466,
    ReheatControllerFMU_eqFunction_1467,
    ReheatControllerFMU_eqFunction_1468,
    ReheatControllerFMU_eqFunction_1471,
    ReheatControllerFMU_eqFunction_1472,
    ReheatControllerFMU_eqFunction_1473,
    ReheatControllerFMU_eqFunction_1474,
    ReheatControllerFMU_eqFunction_1479,
    ReheatControllerFMU_eqFunction_1480,
    ReheatControllerFMU_eqFunction_1481,
    ReheatControllerFMU_eqFunction_1482,
    ReheatControllerFMU_eqFunction_1483,
    ReheatControllerFMU_eqFunction_1484,
    ReheatControllerFMU_eqFunction_1532,
    ReheatControllerFMU_eqFunction_1534,
    ReheatControllerFMU_eqFunction_1535,
    ReheatControllerFMU_eqFunction_1536,
    ReheatControllerFMU_eqFunction_1537,
    ReheatControllerFMU_eqFunction_1538,
    ReheatControllerFMU_eqFunction_1560,
    ReheatControllerFMU_eqFunction_1561,
    ReheatControllerFMU_eqFunction_1563,
    ReheatControllerFMU_eqFunction_1564,
    ReheatControllerFMU_eqFunction_1618,
    ReheatControllerFMU_eqFunction_1619,
    ReheatControllerFMU_eqFunction_1656,
    ReheatControllerFMU_eqFunction_1657,
    ReheatControllerFMU_eqFunction_1658,
    ReheatControllerFMU_eqFunction_1659,
    ReheatControllerFMU_eqFunction_1660,
    ReheatControllerFMU_eqFunction_1682,
    ReheatControllerFMU_eqFunction_1683,
    ReheatControllerFMU_eqFunction_1685,
    ReheatControllerFMU_eqFunction_1686
  };

  static const int eqIndices[152] = {
    1184,
    1185,
    1186,
    1187,
    1188,
    1189,
    1190,
    1191,
    1192,
    1193,
    1194,
    1195,
    1196,
    1197,
    1198,
    1199,
    1225,
    1226,
    1227,
    1228,
    1229,
    1230,
    1231,
    1232,
    1233,
    1235,
    1236,
    1238,
    1239,
    1241,
    1242,
    1243,
    1244,
    1245,
    1246,
    1247,
    1248,
    1249,
    1251,
    1252,
    1254,
    1255,
    1257,
    1259,
    1288,
    1289,
    1290,
    1291,
    1292,
    1293,
    1294,
    1295,
    1296,
    1297,
    1298,
    1299,
    1300,
    1304,
    1305,
    1306,
    1307,
    1308,
    1309,
    1310,
    1311,
    1312,
    1313,
    1314,
    1315,
    1324,
    1325,
    1326,
    1327,
    1328,
    1330,
    1331,
    1332,
    1333,
    1334,
    1338,
    1339,
    1340,
    1341,
    1342,
    1343,
    1344,
    1345,
    1346,
    1347,
    1348,
    1349,
    1350,
    1351,
    1354,
    1355,
    1423,
    1428,
    1429,
    1430,
    1431,
    1432,
    1433,
    1434,
    1435,
    1438,
    1445,
    1446,
    1447,
    1448,
    1449,
    1450,
    1451,
    1456,
    1461,
    1462,
    1463,
    1464,
    1465,
    1466,
    1467,
    1468,
    1471,
    1472,
    1473,
    1474,
    1479,
    1480,
    1481,
    1482,
    1483,
    1484,
    1532,
    1534,
    1535,
    1536,
    1537,
    1538,
    1560,
    1561,
    1563,
    1564,
    1618,
    1619,
    1656,
    1657,
    1658,
    1659,
    1660,
    1682,
    1683,
    1685,
    1686
  };

  for (id = 0; id < 152; id++) {
    eqFunctions[id](data, threadData);
    threadData->lastEquationSolved = eqIndices[id];
  }
}

int ReheatControllerFMU_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif


  data->simulationInfo->callStatistics.functionODE++;

  ReheatControllerFMU_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

void ReheatControllerFMU_computeVarIndices(size_t* realIndex, size_t* integerIndex, size_t* booleanIndex, size_t* stringIndex)
{
  TRACE_PUSH

  size_t i_real = 0;
  size_t i_integer = 0;
  size_t i_boolean = 0;
  size_t i_string = 0;

  realIndex[0] = 0;
  integerIndex[0] = 0;
  booleanIndex[0] = 0;
  stringIndex[0] = 0;

  /* stateVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.I.y STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.I.y STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.I.y STATE(1) */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.I.y STATE(1) */

  /* derivativeVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(conLoo.conCoo.I.y) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(conLoo.conHea.I.y) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(damVal.conDam.I.y) STATE_DER */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* der(damVal.conVal.I.y) STATE_DER */

  /* algVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse2 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse3 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse4 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* $cse5 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* TCooSet variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* TDis variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* THeaSet variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* TSup variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* TSupSet variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* TZon variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* VAdjAreBreZon_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* VAdjPopBreZon_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* VDis_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* VMinOA_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* VSet_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.VActCooMax_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.VActHeaMax_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.VActHeaMin_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.VActMin_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.add2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.add3.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.cooMaxFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.heaMaxFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.heaMaxFlo1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.heaMinFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.max1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.max2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.occModInd.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.pro1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* actAirSet.pro2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.addPar.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.addPar1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.addPar2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.gai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.gai1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.gai2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.Dzero.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.I.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.P.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.addPD.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.addPID.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.addRes.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.antWinErr.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.antWinGai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.controlError.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.errI1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.errP.u1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.uMea_revAct.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conCoo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.Dzero.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.I.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.P.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.addPD.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.addPID.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.addRes.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.antWinErr.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.antWinGai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.controlError.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.errI1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.errP.u1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.uMea_revAct.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.conHea.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.yCoo variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.yHea variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.zerCoo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.zerHea.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.TDisSet variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.VDisSet_flowNor.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.VDis_flowNor.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.add1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.add2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.add4.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.addPar.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.addPar1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.Dzero.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.I.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.P.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.addPD.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.addPID.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.addRes.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.antWinErr.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.antWinGai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.controlError.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.errI1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.errP.u1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.uMea_revAct.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conDam.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conHal.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conHal1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conOne.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conOne2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conTDisHeaSet.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conTDisHeaSet.b variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conTDisHeaSet.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conTDisHeaSet.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.Dzero.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.I.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.P.u variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.addPD.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.addPID.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.addRes.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.antWinErr.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.antWinGai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.controlError.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.errI1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.errP.u1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.uMea_revAct.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conVal.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conZer.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conZer2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.conZer3.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.cooMax.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.heaMax.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin.b variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin3.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin3.b variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin3.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.lin3.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.max1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.max2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.minFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.sub2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.swi.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.swi1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.swi2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.swi4.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.swi5.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.yDam variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.yVal variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.zerFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ppmCO2 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ppmCO2Set variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setOve.add3.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setOve.booToRea.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setOve.cloDam.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setOve.opeDam.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.VOccZonMin_flow variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.addPar.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.airDisEff.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.booToRea.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.booToRea1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.co2Con.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.lin.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.lin.b variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.lin.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.lin.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.occMinAirSet.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.occMinAirSet.b variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.occMinAirSet.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.occMinAirSet.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.one.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.popBreOutAir.a variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.popBreOutAir.xLim variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.popBreOutAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.reqBreAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.unPopAreBreAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.unpAreBreAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.unpMinZonAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.unpMinZonFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.unpPopBreAir.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.zer.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.zer1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* setPoi.zonMinFlo.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.addPar.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.addPar1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.gai2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.greEqu.u1 variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sub2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sub3.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.abs1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.abs2.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.conZer.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.gai.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.sub1.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.supTim.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.swi.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.temDif.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.tim.y variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* yDam variable */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* yVal variable */

  /* discreteAlgVars */
  realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.fanIni.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel1.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel2.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel3.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel4.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel5.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel6.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* ala.truDel7.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.disCoo.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* conLoo.disHea.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.truFalHol.entryTimeFalse DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.truFalHol.entryTimeTrue DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.truFalHol1.entryTimeFalse DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* damVal.truFalHol1.entryTimeTrue DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sampler.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sampler1.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sampler2.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.sampler3.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.tim1.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.tim2.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.tim3.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.tim4.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* sysReq.tim5.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.samSet.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.tim.entryTime DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.triSam.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.triSam1.y DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.truDel.t_next DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.uniDel.u_internal DISCRETE */realIndex[i_real+1] = realIndex[i_real] + ((modelica_integer) 1); i_real++;  /* timSup.uniDel.y DISCRETE */

  /* realOptimizeConstraintsVars */

  /* realOptimizeFinalConstraintsVars */


  /* intAlgVars */
  integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* actAirSet.cooDowMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* actAirSet.occMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* actAirSet.setBacMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* actAirSet.setUpMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* actAirSet.warUpMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.booToInt.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.booToInt1.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.booToInt4.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.booToInt5.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.conInt.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.conInt2.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.lowFloAla.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.lowTemAla.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* ala.occMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.conInt.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.conInt1.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.conInt2.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.conInt5.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.occMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* damVal.unOcc.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* oveDamPos variable */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* oveFloSet variable */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* setOve.conInt3.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* setOve.conInt4.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* setPoi.occMod.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.booToInt.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.booToInt1.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.booToInt2.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.intSwi1.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.intSwi3.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.swi5.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.thrCooResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.thrHeaResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.thrPreResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.twoCooResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.twoHeaResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* sysReq.twoPreResReq.y DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* uOpeMod variable */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yFloSenAla DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yHeaValResReq DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yHotWatPlaReq DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yLeaDamAla DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yLeaValAla DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yLowFloAla DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yLowTemAla DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yZonPreResReq DISCRETE */integerIndex[i_integer+1] = integerIndex[i_integer] + ((modelica_integer) 1); i_integer++;  /* yZonTemResReq DISCRETE */

  /* boolAlgVars */
  booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition1 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition10 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition11 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition12 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition13 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition14 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition15 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition16 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition17 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition18 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition19 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition2 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition20 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition21 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition22 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition23 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition24 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition25 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition26 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition27 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition28 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition29 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition3 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition30 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition31 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition32 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition33 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition34 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition35 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition36 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition37 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition38 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition39 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition4 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition40 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition41 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition42 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition43 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition44 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition45 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition46 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition47 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition48 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition49 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition5 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition50 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition51 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition52 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition53 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition54 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition55 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition56 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition57 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition58 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition59 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition6 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition60 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition61 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition62 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition63 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition64 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition65 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition66 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition67 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition68 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition69 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition7 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition70 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition71 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition72 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition73 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition74 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition8 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* $whenCondition9 DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.ifCooDow.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.ifOcc.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.ifSetBac.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.ifSetUp.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.ifWarUp.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.or1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.or2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* actAirSet.or3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and12.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and6.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and7.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and8.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.and9.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.cloDam.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.cloVal.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.fanHotPlaOn.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.fanIni.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.fanIni.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.gre.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.gre1.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.gre2.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.greThr.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.greThr1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.greThr2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.isOcc.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.leaDamAla.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.leaValAla.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.les.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.les1.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.les2.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.not1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.not2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.not6.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.not7.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel1.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel2.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel3.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel4.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel5.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel5.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel6.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel6.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel7.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* ala.truDel7.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disCoo.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disCoo.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disCooCon.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disHea.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disHea.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.disHeaCon.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.enaCooLoo.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.enaHeaLoo.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.zerCon.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* conLoo.zerCon1.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.and1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.and2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.and4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.conDam.cheYMinMax.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.conVal.cheYMinMax.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.forCooMax.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.forMinFlo.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.forMinFlo1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.forZerFlo.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.gre.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.greThr.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.greThr1.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.greThr2.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.isOcc.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.isUno.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.lowMin.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.or1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.or2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.or3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.or4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol.not_u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol.not_y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol1.not_u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol1.not_y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol1.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* damVal.truFalHol1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setOve.intEqu3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setOve.intEqu4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setOve.or2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setPoi.cooSup.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setPoi.notOccMod.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* setPoi.or2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.and1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.and2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.and3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.and4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.and5.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greEqu.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greEqu1.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr1.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr2.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr3.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr4.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr5.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.greThr6.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.les.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.les1.lesHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler.firstTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler1.firstTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler1.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler2.firstTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler2.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler3.firstTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.sampler3.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim1.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim2.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim2.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim3.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim3.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim4.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim4.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim5.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* sysReq.tim5.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.con1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.con5.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.edg.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.edg.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.greThr.greHys.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.lat.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.lat1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.pre1.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.pre1.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.samSet.firstTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.samSet.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.tim.passed DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.truDel.u DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.truDel.y DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.uniDel.sampleTrigger DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* timSup.yAftSup DISCRETE */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* u1Fan variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* u1HotPla variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* u1Occ variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* u1Win variable */booleanIndex[i_boolean+1] = booleanIndex[i_boolean] + ((modelica_integer) 1); i_boolean++;  /* uHeaOff variable */

  /* stringAlgVars */

  TRACE_POP
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "ReheatControllerFMU_12jac.h"
#include "ReheatControllerFMU_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks ReheatControllerFMU_callback = {
   NULL,    /* performSimulation */
   NULL,    /* performQSSSimulation */
   NULL,    /* updateContinuousSystem */
   ReheatControllerFMU_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   ReheatControllerFMU_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   ReheatControllerFMU_initializeDAEmodeData,
   ReheatControllerFMU_computeVarIndices,
   ReheatControllerFMU_functionODE,
   ReheatControllerFMU_functionAlgebraics,
   ReheatControllerFMU_functionDAE,
   ReheatControllerFMU_functionLocalKnownVars,
   ReheatControllerFMU_input_function,
   ReheatControllerFMU_input_function_init,
   ReheatControllerFMU_input_function_updateStartValues,
   ReheatControllerFMU_data_function,
   ReheatControllerFMU_output_function,
   ReheatControllerFMU_setc_function,
   ReheatControllerFMU_setb_function,
   ReheatControllerFMU_function_storeDelayed,
   ReheatControllerFMU_function_storeSpatialDistribution,
   ReheatControllerFMU_function_initSpatialDistribution,
   ReheatControllerFMU_updateBoundVariableAttributes,
   ReheatControllerFMU_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   ReheatControllerFMU_functionInitialEquations_lambda0,
   ReheatControllerFMU_functionRemovedInitialEquations,
   ReheatControllerFMU_updateBoundParameters,
   ReheatControllerFMU_checkForAsserts,
   ReheatControllerFMU_function_ZeroCrossingsEquations,
   ReheatControllerFMU_function_ZeroCrossings,
   ReheatControllerFMU_function_updateRelations,
   ReheatControllerFMU_zeroCrossingDescription,
   ReheatControllerFMU_relationDescription,
   ReheatControllerFMU_function_initSample,
   ReheatControllerFMU_INDEX_JAC_A,
   ReheatControllerFMU_INDEX_JAC_B,
   ReheatControllerFMU_INDEX_JAC_C,
   ReheatControllerFMU_INDEX_JAC_D,
   ReheatControllerFMU_INDEX_JAC_F,
   ReheatControllerFMU_INDEX_JAC_H,
   ReheatControllerFMU_initialAnalyticJacobianA,
   ReheatControllerFMU_initialAnalyticJacobianB,
   ReheatControllerFMU_initialAnalyticJacobianC,
   ReheatControllerFMU_initialAnalyticJacobianD,
   ReheatControllerFMU_initialAnalyticJacobianF,
   ReheatControllerFMU_initialAnalyticJacobianH,
   ReheatControllerFMU_functionJacA_column,
   ReheatControllerFMU_functionJacB_column,
   ReheatControllerFMU_functionJacC_column,
   ReheatControllerFMU_functionJacD_column,
   ReheatControllerFMU_functionJacF_column,
   ReheatControllerFMU_functionJacH_column,
   ReheatControllerFMU_linear_model_frame,
   ReheatControllerFMU_linear_model_datarecovery_frame,
   ReheatControllerFMU_mayer,
   ReheatControllerFMU_lagrange,
   ReheatControllerFMU_pickUpBoundsForInputsInOptimization,
   ReheatControllerFMU_setInputData,
   ReheatControllerFMU_getTimeGrid,
   ReheatControllerFMU_symbolicInlineSystem,
   ReheatControllerFMU_function_initSynchronous,
   ReheatControllerFMU_function_updateSynchronous,
   ReheatControllerFMU_function_equationsSynchronous,
   ReheatControllerFMU_inputNames,
   ReheatControllerFMU_dataReconciliationInputNames,
   ReheatControllerFMU_dataReconciliationUnmeasuredVariables,
   ReheatControllerFMU_read_simulation_info,
   ReheatControllerFMU_read_input_fmu,
   NULL,
   NULL,
   -1,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "Buildings"
#define _OMC_LIT_RESOURCE_0_dir_data "/Users/amol/Documents/ai-projects/modelica-buildings/Buildings"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,9,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,62,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "Complex"
#define _OMC_LIT_RESOURCE_1_dir_data "/root/.openmodelica/libraries/Complex 4.1.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,7,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,52,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "Modelica"
#define _OMC_LIT_RESOURCE_2_dir_data "/root/.openmodelica/libraries/Modelica 4.1.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,8,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,53,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_3_dir_data "/root/.openmodelica/libraries/ModelicaServices 4.1.0+maint.om"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,16,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,61,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "ReheatControllerFMU"
#define _OMC_LIT_RESOURCE_4_dir_data "/Users/amol/Documents/ai-projects/bms-supervisor-controller/apps/g36-api-app/fmu-sequence/modelica"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,19,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,98,_OMC_LIT_RESOURCE_4_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,10,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir)}};
void ReheatControllerFMU_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &ReheatControllerFMU_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "ReheatControllerFMU";
  data->modelData->modelFilePrefix = "ReheatControllerFMU";
  data->modelData->modelFileName = "ReheatControllerFMU.mo";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/Users/amol/Documents/ai-projects/bms-supervisor-controller/apps/g36-api-app/fmu-sequence/modelica";
  data->modelData->modelGUID = "{acbcacfe-c67e-482b-9c6c-0cede17fb3f4}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/ReheatControllerFMU_info.json", data->modelData->resourcesDir);
  data->modelData->runTestsuite = 0;
  data->modelData->nStates = 4;
  data->modelData->nVariablesRealArray = 223;
  data->modelData->nDiscreteReal = 31;
  data->modelData->nVariablesIntegerArray = 47;
  data->modelData->nVariablesBooleanArray = 226;
  data->modelData->nVariablesStringArray = 0;
  data->modelData->nParametersReal = 466;
  data->modelData->nParametersInteger = 57;
  data->modelData->nParametersBoolean = 169;
  data->modelData->nParametersString = 11;
  data->modelData->nInputVars = 17;
  data->modelData->nOutputVars = 15;
  data->modelData->nAliasReal = 407;
  data->modelData->nAliasInteger = 83;
  data->modelData->nAliasBoolean = 236;
  data->modelData->nAliasString = 0;
  data->modelData->nZeroCrossings = 65;
  data->modelData->nSamples = 6;
  data->modelData->nRelations = 91;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 1;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 2540;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 6;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  data->modelData->nDelayExpressions = 0;
  data->modelData->nBaseClocks = 0;
  data->modelData->nSpatialDistributions = 0;
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->nSetbVars = 0;
  data->modelData->nRelatedBoundaryConditions = 0;
  data->modelData->linearizationDumpLanguage = OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}
