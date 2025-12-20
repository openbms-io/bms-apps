#include "ReheatControllerFMU_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
extern void ReheatControllerFMU_eqFunction_1466(DATA *data, threadData_t *threadData);


/*
equation index: 299
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.y = damVal.truFalHol1.u
*/
void ReheatControllerFMU_eqFunction_299(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,299};
  (data->simulationInfo->booleanVarsPre[164] /* damVal.truFalHol1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 300
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.not_y = not damVal.truFalHol1.u
*/
void ReheatControllerFMU_eqFunction_300(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,300};
  (data->simulationInfo->booleanVarsPre[162] /* damVal.truFalHol1.not_y DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 301
type: SIMPLE_ASSIGN
$whenCondition1 = damVal.truFalHol1.u and not $PRE.damVal.truFalHol1.u
*/
void ReheatControllerFMU_eqFunction_301(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,301};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[0]] /* $whenCondition1 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[163] /* damVal.truFalHol1.u DISCRETE */)));
  TRACE_POP
}

/*
equation index: 302
type: SIMPLE_ASSIGN
damVal.truFalHol1.y = damVal.truFalHol1.u
*/
void ReheatControllerFMU_eqFunction_302(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,302};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[163]] /* damVal.truFalHol1.u DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1471(DATA *data, threadData_t *threadData);


/*
equation index: 304
type: SIMPLE_ASSIGN
damVal.truFalHol1.entryTimeFalse = if damVal.truFalHol1.not_y then time else $PRE.damVal.truFalHol1.entryTimeFalse
*/
void ReheatControllerFMU_eqFunction_304(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,304};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[205]] /* damVal.truFalHol1.entryTimeFalse DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[162]] /* damVal.truFalHol1.not_y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1473(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1474(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1472(DATA *data, threadData_t *threadData);


/*
equation index: 308
type: SIMPLE_ASSIGN
damVal.truFalHol1.entryTimeTrue = if damVal.truFalHol1.y then time else $PRE.damVal.truFalHol1.entryTimeTrue
*/
void ReheatControllerFMU_eqFunction_308(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,308};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[206]] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[164]] /* damVal.truFalHol1.y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */));
  TRACE_POP
}

/*
equation index: 309
type: SIMPLE_ASSIGN
damVal.lin.xLim = min(1.0, max(0.0, conLoo.yCoo))
*/
void ReheatControllerFMU_eqFunction_309(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,309};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[124]] /* damVal.lin.xLim variable */) = fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */)));
  TRACE_POP
}

/*
equation index: 310
type: SIMPLE_ASSIGN
damVal.lin.y = damVal.lin.a + damVal.lin.b * damVal.lin.xLim
*/
void ReheatControllerFMU_eqFunction_310(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,310};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[125]] /* damVal.lin.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[122]] /* damVal.lin.a variable */) + ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[123]] /* damVal.lin.b variable */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[124]] /* damVal.lin.xLim variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1482(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1483(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1484(DATA *data, threadData_t *threadData);


/*
equation index: 314
type: SIMPLE_ASSIGN
sysReq.sampler3.y = VSet_flow
*/
void ReheatControllerFMU_eqFunction_314(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,314};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1570(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1568(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1532(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1534(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1535(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1565(DATA *data, threadData_t *threadData);


/*
equation index: 321
type: SIMPLE_ASSIGN
damVal.conDam.addPD.y = damVal.conDam.P.k * damVal.conDam.P.u
*/
void ReheatControllerFMU_eqFunction_321(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,321};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[86]] /* damVal.conDam.addPD.y variable */) = ((data->simulationInfo->realParameter[227] /* damVal.conDam.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[85]] /* damVal.conDam.P.u variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1562(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1537(DATA *data, threadData_t *threadData);


/*
equation index: 324
type: SIMPLE_ASSIGN
damVal.conDam.y = homotopy(smooth(0, if noEvent(damVal.conDam.addPID.y > 1.0) then 1.0 else if noEvent(damVal.conDam.addPID.y < 0.0) then 0.0 else damVal.conDam.addPID.y), damVal.conDam.addPID.y)
*/
void ReheatControllerFMU_eqFunction_324(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,324};
  modelica_boolean tmp59;
  modelica_boolean tmp60;
  modelica_boolean tmp61;
  modelica_real tmp62;
  tmp59 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */),1.0);
  tmp61 = (modelica_boolean)tmp59;
  if(tmp61)
  {
    tmp62 = 1.0;
  }
  else
  {
    tmp60 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */),0.0);
    tmp62 = (tmp60?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[95]] /* damVal.conDam.y variable */) = homotopy(tmp62, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1539(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1540(DATA *data, threadData_t *threadData);


/*
equation index: 327
type: SIMPLE_ASSIGN
sysReq.sampler1.y = yDam
*/
void ReheatControllerFMU_eqFunction_327(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,327};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */);
  TRACE_POP
}

/*
equation index: 328
type: SIMPLE_ASSIGN
ala.cloDam.lesHys.y = not $PRE.ala.cloDam.lesHys.y and yDam < 0.005 or $PRE.ala.cloDam.lesHys.y and yDam < 0.0075
*/
void ReheatControllerFMU_eqFunction_328(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,328};
  modelica_boolean tmp63;
  modelica_boolean tmp64;
  tmp63 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */),0.005);
  tmp64 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */),0.0075);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[90]] /* ala.cloDam.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */)) && tmp63) || ((data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */) && tmp64));
  TRACE_POP
}

/*
equation index: 329
type: SIMPLE_ASSIGN
ala.truDel3.u = ala.leaDamAla.y and ala.cloDam.lesHys.y
*/
void ReheatControllerFMU_eqFunction_329(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,329};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[117]] /* ala.truDel3.u DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[102]] /* ala.leaDamAla.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[90]] /* ala.cloDam.lesHys.y DISCRETE */));
  TRACE_POP
}

/*
equation index: 330
type: SIMPLE_ASSIGN
$whenCondition35 = not ala.truDel3.u
*/
void ReheatControllerFMU_eqFunction_330(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,330};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[28]] /* $whenCondition35 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[117]] /* ala.truDel3.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 331
type: SIMPLE_ASSIGN
$whenCondition36 = ala.truDel3.u
*/
void ReheatControllerFMU_eqFunction_331(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,331};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[29]] /* $whenCondition36 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[117]] /* ala.truDel3.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 332
type: SIMPLE_ASSIGN
ala.truDel3.y = if not (ala.truDel3.delayOnInit and ala.truDel3.delayTime > 0.0) then ala.truDel3.u else false
*/
void ReheatControllerFMU_eqFunction_332(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,332};
  modelica_boolean tmp65;
  tmp65 = Greater((data->simulationInfo->realParameter[117] /* ala.truDel3.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[118]] /* ala.truDel3.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[35] /* ala.truDel3.delayOnInit PARAM */) && tmp65))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[117]] /* ala.truDel3.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1548(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1560(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1561(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1563(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1564(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1533(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1513(DATA *data, threadData_t *threadData);


/*
equation index: 340
type: SIMPLE_ASSIGN
ala.gre.greHys.y = not $PRE.ala.gre.greHys.y and ala.gai1.y > VDis_flow or $PRE.ala.gre.greHys.y and ala.gai1.y > VDis_flow - 0.005
*/
void ReheatControllerFMU_eqFunction_340(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,340};
  modelica_boolean tmp66;
  modelica_boolean tmp67;
  tmp66 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */));
  tmp67 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) - 0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[95]] /* ala.gre.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */)) && tmp66) || ((data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */) && tmp67));
  TRACE_POP
}

/*
equation index: 341
type: SIMPLE_ASSIGN
ala.truDel1.u = ala.gre.greHys.y and ala.fanIni.y
*/
void ReheatControllerFMU_eqFunction_341(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,341};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[113]] /* ala.truDel1.u DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[95]] /* ala.gre.greHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */));
  TRACE_POP
}

/*
equation index: 342
type: SIMPLE_ASSIGN
$whenCondition41 = not ala.truDel1.u
*/
void ReheatControllerFMU_eqFunction_342(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,342};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[35]] /* $whenCondition41 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[113]] /* ala.truDel1.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 343
type: SIMPLE_ASSIGN
$whenCondition42 = ala.truDel1.u
*/
void ReheatControllerFMU_eqFunction_343(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,343};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[36]] /* $whenCondition42 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[113]] /* ala.truDel1.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 344
type: SIMPLE_ASSIGN
ala.truDel1.y = if not (ala.truDel1.delayOnInit and ala.truDel1.delayTime > 0.0) then ala.truDel1.u else false
*/
void ReheatControllerFMU_eqFunction_344(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,344};
  modelica_boolean tmp68;
  tmp68 = Greater((data->simulationInfo->realParameter[113] /* ala.truDel1.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[114]] /* ala.truDel1.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[33] /* ala.truDel1.delayOnInit PARAM */) && tmp68))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[113]] /* ala.truDel1.u DISCRETE */):0 /* false */);
  TRACE_POP
}

/*
equation index: 345
type: SIMPLE_ASSIGN
ala.greThr.greHys.y = not $PRE.ala.greThr.greHys.y and VSet_flow > 0.005 or $PRE.ala.greThr.greHys.y and VSet_flow > 0.0025
*/
void ReheatControllerFMU_eqFunction_345(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,345};
  modelica_boolean tmp69;
  modelica_boolean tmp70;
  tmp69 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */),0.005);
  tmp70 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */),0.0025);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[98]] /* ala.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */)) && tmp69) || ((data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */) && tmp70));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1512(DATA *data, threadData_t *threadData);


/*
equation index: 347
type: SIMPLE_ASSIGN
$whenCondition23 = not ala.truDel7.u
*/
void ReheatControllerFMU_eqFunction_347(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,347};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[15]] /* $whenCondition23 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[125]] /* ala.truDel7.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 348
type: SIMPLE_ASSIGN
$whenCondition24 = ala.truDel7.u
*/
void ReheatControllerFMU_eqFunction_348(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,348};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[16]] /* $whenCondition24 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[125]] /* ala.truDel7.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 349
type: SIMPLE_ASSIGN
ala.truDel7.y = if not (ala.truDel7.delayOnInit and ala.truDel7.delayTime > 0.0) then ala.truDel7.u else false
*/
void ReheatControllerFMU_eqFunction_349(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,349};
  modelica_boolean tmp71;
  tmp71 = Greater((data->simulationInfo->realParameter[125] /* ala.truDel7.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[126]] /* ala.truDel7.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[39] /* ala.truDel7.delayOnInit PARAM */) && tmp71))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[125]] /* ala.truDel7.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1521(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1522(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1523(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1524(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1485(DATA *data, threadData_t *threadData);


/*
equation index: 355
type: SIMPLE_ASSIGN
ala.les.lesHys.y = not $PRE.ala.les.lesHys.y and VDis_flow < ala.gai.y or $PRE.ala.les.lesHys.y and VDis_flow < ala.gai.y + 0.005
*/
void ReheatControllerFMU_eqFunction_355(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,355};
  modelica_boolean tmp72;
  modelica_boolean tmp73;
  tmp72 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */));
  tmp73 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) + 0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[104]] /* ala.les.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */)) && tmp72) || ((data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */) && tmp73));
  TRACE_POP
}

/*
equation index: 356
type: SIMPLE_ASSIGN
ala.truDel.u = ala.les.lesHys.y and ala.fanIni.y
*/
void ReheatControllerFMU_eqFunction_356(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,356};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[111]] /* ala.truDel.u DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[104]] /* ala.les.lesHys.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */));
  TRACE_POP
}

/*
equation index: 357
type: SIMPLE_ASSIGN
$whenCondition44 = not ala.truDel.u
*/
void ReheatControllerFMU_eqFunction_357(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,357};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[38]] /* $whenCondition44 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[111]] /* ala.truDel.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 358
type: SIMPLE_ASSIGN
$whenCondition45 = ala.truDel.u
*/
void ReheatControllerFMU_eqFunction_358(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,358};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[39]] /* $whenCondition45 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[111]] /* ala.truDel.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 359
type: SIMPLE_ASSIGN
ala.truDel.y = if not (ala.truDel.delayOnInit and ala.truDel.delayTime > 0.0) then ala.truDel.u else false
*/
void ReheatControllerFMU_eqFunction_359(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,359};
  modelica_boolean tmp74;
  tmp74 = Greater((data->simulationInfo->realParameter[111] /* ala.truDel.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[112]] /* ala.truDel.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[32] /* ala.truDel.delayOnInit PARAM */) && tmp74))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[111]] /* ala.truDel.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1509(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1510(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1511(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1525(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1526(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1235(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1236(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1238(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1239(DATA *data, threadData_t *threadData);


/*
equation index: 369
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr6.greHys.y = sysReq.greThr6.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_369(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,369};
  (data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[150] /* sysReq.greThr6.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 370
type: SIMPLE_ASSIGN
sysReq.greThr6.greHys.y = not $PRE.sysReq.greThr6.greHys.y and yVal > 0.95 or $PRE.sysReq.greThr6.greHys.y and yVal > 0.09999999999999998
*/
void ReheatControllerFMU_eqFunction_370(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,370};
  modelica_boolean tmp75;
  modelica_boolean tmp76;
  tmp75 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.95);
  tmp76 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.09999999999999998);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[184]] /* sysReq.greThr6.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */)) && tmp75) || ((data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */) && tmp76));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1679(DATA *data, threadData_t *threadData);


/*
equation index: 372
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr5.greHys.y = sysReq.greThr5.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_372(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,372};
  (data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[147] /* sysReq.greThr5.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 373
type: SIMPLE_ASSIGN
sysReq.greThr5.greHys.y = not $PRE.sysReq.greThr5.greHys.y and yVal > 0.95 or $PRE.sysReq.greThr5.greHys.y and yVal > 0.945
*/
void ReheatControllerFMU_eqFunction_373(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,373};
  modelica_boolean tmp77;
  modelica_boolean tmp78;
  tmp77 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.95);
  tmp78 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.945);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[183]] /* sysReq.greThr5.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */)) && tmp77) || ((data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */) && tmp78));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1681(DATA *data, threadData_t *threadData);


/*
equation index: 375
type: SIMPLE_ASSIGN
$PRE.sysReq.greEqu1.greHys.y = sysReq.greEqu1.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_375(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,375};
  (data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[129] /* sysReq.greEqu1.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 376
type: SIMPLE_ASSIGN
sysReq.greEqu1.greHys.y = not $PRE.sysReq.greEqu1.greHys.y and sysReq.gai2.y > sysReq.sampler2.y or $PRE.sysReq.greEqu1.greHys.y and sysReq.gai2.y > sysReq.sampler2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_376(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,376};
  modelica_boolean tmp79;
  modelica_boolean tmp80;
  tmp79 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */));
  tmp80 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[177]] /* sysReq.greEqu1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */)) && tmp79) || ((data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */) && tmp80));
  TRACE_POP
}

/*
equation index: 377
type: SIMPLE_ASSIGN
$PRE.sysReq.greEqu.greHys.y = sysReq.greEqu.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_377(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,377};
  (data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[126] /* sysReq.greEqu.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 378
type: SIMPLE_ASSIGN
sysReq.greEqu.greHys.y = not $PRE.sysReq.greEqu.greHys.y and sysReq.greEqu.u1 > sysReq.sampler2.y or $PRE.sysReq.greEqu.greHys.y and sysReq.greEqu.u1 > sysReq.sampler2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_378(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,378};
  modelica_boolean tmp81;
  modelica_boolean tmp82;
  tmp81 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */));
  tmp82 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[176]] /* sysReq.greEqu.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */)) && tmp81) || ((data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */) && tmp82));
  TRACE_POP
}

/*
equation index: 379
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr4.greHys.y = sysReq.greThr4.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_379(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,379};
  (data->simulationInfo->booleanVarsPre[182] /* sysReq.greThr4.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[144] /* sysReq.greThr4.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 380
type: SIMPLE_ASSIGN
sysReq.greThr4.greHys.y = not $PRE.sysReq.greThr4.greHys.y and sysReq.sampler3.y > 0.005 or $PRE.sysReq.greThr4.greHys.y and sysReq.sampler3.y > 0.0025
*/
void ReheatControllerFMU_eqFunction_380(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,380};
  modelica_boolean tmp83;
  modelica_boolean tmp84;
  tmp83 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */),0.005);
  tmp84 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[210]] /* sysReq.sampler3.y DISCRETE */),0.0025);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[182]] /* sysReq.greThr4.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[182] /* sysReq.greThr4.greHys.y DISCRETE */)) && tmp83) || ((data->simulationInfo->booleanVarsPre[182] /* sysReq.greThr4.greHys.y DISCRETE */) && tmp84));
  TRACE_POP
}

/*
equation index: 381
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr.greHys.y = sysReq.greThr.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_381(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,381};
  (data->simulationInfo->booleanVarsPre[178] /* sysReq.greThr.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[132] /* sysReq.greThr.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 382
type: SIMPLE_ASSIGN
sysReq.greThr.greHys.y = not $PRE.sysReq.greThr.greHys.y and sysReq.sampler.y > 0.95 or $PRE.sysReq.greThr.greHys.y and sysReq.sampler.y > 0.94
*/
void ReheatControllerFMU_eqFunction_382(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,382};
  modelica_boolean tmp85;
  modelica_boolean tmp86;
  tmp85 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */),0.95);
  tmp86 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */),0.94);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[178]] /* sysReq.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[178] /* sysReq.greThr.greHys.y DISCRETE */)) && tmp85) || ((data->simulationInfo->booleanVarsPre[178] /* sysReq.greThr.greHys.y DISCRETE */) && tmp86));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1574(DATA *data, threadData_t *threadData);


/*
equation index: 384
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr3.greHys.y = sysReq.greThr3.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_384(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,384};
  (data->simulationInfo->booleanVarsPre[181] /* sysReq.greThr3.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[141] /* sysReq.greThr3.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 385
type: SIMPLE_ASSIGN
sysReq.greThr3.greHys.y = not $PRE.sysReq.greThr3.greHys.y and sysReq.sampler1.y > 0.95 or $PRE.sysReq.greThr3.greHys.y and sysReq.sampler1.y > 0.945
*/
void ReheatControllerFMU_eqFunction_385(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,385};
  modelica_boolean tmp87;
  modelica_boolean tmp88;
  tmp87 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */),0.95);
  tmp88 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[208]] /* sysReq.sampler1.y DISCRETE */),0.945);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[181]] /* sysReq.greThr3.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[181] /* sysReq.greThr3.greHys.y DISCRETE */)) && tmp87) || ((data->simulationInfo->booleanVarsPre[181] /* sysReq.greThr3.greHys.y DISCRETE */) && tmp88));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1559(DATA *data, threadData_t *threadData);


/*
equation index: 387
type: SIMPLE_ASSIGN
$whenCondition63 = not sysReq.tim3.u
*/
void ReheatControllerFMU_eqFunction_387(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,387};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[59]] /* $whenCondition63 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[199]] /* sysReq.tim3.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 388
type: SIMPLE_ASSIGN
$whenCondition64 = sysReq.tim3.u
*/
void ReheatControllerFMU_eqFunction_388(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,388};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[60]] /* $whenCondition64 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[199]] /* sysReq.tim3.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 389
type: SIMPLE_ASSIGN
sysReq.tim3.y = if not (sysReq.tim3.delayOnInit and sysReq.tim3.delayTime > 0.0) then sysReq.tim3.u else false
*/
void ReheatControllerFMU_eqFunction_389(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,389};
  modelica_boolean tmp89;
  tmp89 = Greater((data->simulationInfo->realParameter[463] /* sysReq.tim3.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[200]] /* sysReq.tim3.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[161] /* sysReq.tim3.delayOnInit PARAM */) && tmp89))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[199]] /* sysReq.tim3.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1586(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1588(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1587(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1556(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1589(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1590(DATA *data, threadData_t *threadData);


/*
equation index: 396
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr2.greHys.y = sysReq.greThr2.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_396(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,396};
  (data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[138] /* sysReq.greThr2.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 397
type: SIMPLE_ASSIGN
sysReq.greThr2.greHys.y = not $PRE.sysReq.greThr2.greHys.y and sysReq.sub3.y > sysReq.greThr2.greHys.t or $PRE.sysReq.greThr2.greHys.y and sysReq.sub3.y > sysReq.greThr2.greHys.t - 0.25
*/
void ReheatControllerFMU_eqFunction_397(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,397};
  modelica_boolean tmp90;
  modelica_boolean tmp91;
  tmp90 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */),(data->simulationInfo->realParameter[423] /* sysReq.greThr2.greHys.t PARAM */));
  tmp91 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */),(data->simulationInfo->realParameter[423] /* sysReq.greThr2.greHys.t PARAM */) - 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[180]] /* sysReq.greThr2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */)) && tmp90) || ((data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */) && tmp91));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1209(DATA *data, threadData_t *threadData);


/*
equation index: 399
type: SIMPLE_ASSIGN
$whenCondition66 = not sysReq.tim2.u
*/
void ReheatControllerFMU_eqFunction_399(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,399};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[62]] /* $whenCondition66 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[197]] /* sysReq.tim2.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 400
type: SIMPLE_ASSIGN
$whenCondition67 = sysReq.tim2.u
*/
void ReheatControllerFMU_eqFunction_400(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,400};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[63]] /* $whenCondition67 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[197]] /* sysReq.tim2.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 401
type: SIMPLE_ASSIGN
sysReq.tim2.y = if not (sysReq.tim2.delayOnInit and sysReq.tim2.delayTime > 0.0) then sysReq.tim2.u else false
*/
void ReheatControllerFMU_eqFunction_401(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,401};
  modelica_boolean tmp92;
  tmp92 = Greater((data->simulationInfo->realParameter[461] /* sysReq.tim2.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[198]] /* sysReq.tim2.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[160] /* sysReq.tim2.delayOnInit PARAM */) && tmp92))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[197]] /* sysReq.tim2.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1600(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1601(DATA *data, threadData_t *threadData);


/*
equation index: 404
type: SIMPLE_ASSIGN
$PRE.sysReq.greThr1.greHys.y = sysReq.greThr1.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_404(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,404};
  (data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[135] /* sysReq.greThr1.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 405
type: SIMPLE_ASSIGN
sysReq.greThr1.greHys.y = not $PRE.sysReq.greThr1.greHys.y and sysReq.sub2.y > sysReq.greThr1.greHys.t or $PRE.sysReq.greThr1.greHys.y and sysReq.sub2.y > sysReq.greThr1.greHys.t - 0.25
*/
void ReheatControllerFMU_eqFunction_405(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,405};
  modelica_boolean tmp93;
  modelica_boolean tmp94;
  tmp93 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */),(data->simulationInfo->realParameter[419] /* sysReq.greThr1.greHys.t PARAM */));
  tmp94 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */),(data->simulationInfo->realParameter[419] /* sysReq.greThr1.greHys.t PARAM */) - 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[179]] /* sysReq.greThr1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */)) && tmp93) || ((data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */) && tmp94));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1204(DATA *data, threadData_t *threadData);


/*
equation index: 407
type: SIMPLE_ASSIGN
$whenCondition69 = not sysReq.tim1.u
*/
void ReheatControllerFMU_eqFunction_407(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,407};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[65]] /* $whenCondition69 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[195]] /* sysReq.tim1.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 408
type: SIMPLE_ASSIGN
$whenCondition70 = sysReq.tim1.u
*/
void ReheatControllerFMU_eqFunction_408(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,408};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[67]] /* $whenCondition70 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[195]] /* sysReq.tim1.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 409
type: SIMPLE_ASSIGN
sysReq.tim1.y = if not (sysReq.tim1.delayOnInit and sysReq.tim1.delayTime > 0.0) then sysReq.tim1.u else false
*/
void ReheatControllerFMU_eqFunction_409(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,409};
  modelica_boolean tmp95;
  tmp95 = Greater((data->simulationInfo->realParameter[459] /* sysReq.tim1.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[196]] /* sysReq.tim1.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[159] /* sysReq.tim1.delayOnInit PARAM */) && tmp95))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[195]] /* sysReq.tim1.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1611(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1612(DATA *data, threadData_t *threadData);


/*
equation index: 412
type: SIMPLE_ASSIGN
$PRE.sysReq.les1.lesHys.y = sysReq.les1.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_412(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,412};
  (data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[157] /* sysReq.les1.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 413
type: SIMPLE_ASSIGN
sysReq.les1.lesHys.y = not $PRE.sysReq.les1.lesHys.y and sysReq.addPar1.y < damVal.TDisSet or $PRE.sysReq.les1.lesHys.y and sysReq.addPar1.y < damVal.TDisSet + 0.25
*/
void ReheatControllerFMU_eqFunction_413(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,413};
  modelica_boolean tmp96;
  modelica_boolean tmp97;
  tmp96 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */));
  tmp97 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[186]] /* sysReq.les1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */)) && tmp96) || ((data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */) && tmp97));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1700(DATA *data, threadData_t *threadData);


/*
equation index: 415
type: SIMPLE_ASSIGN
$whenCondition57 = not sysReq.tim5.u
*/
void ReheatControllerFMU_eqFunction_415(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,415};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[52]] /* $whenCondition57 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[203]] /* sysReq.tim5.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 416
type: SIMPLE_ASSIGN
$whenCondition58 = sysReq.tim5.u
*/
void ReheatControllerFMU_eqFunction_416(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,416};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[53]] /* $whenCondition58 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[203]] /* sysReq.tim5.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 417
type: SIMPLE_ASSIGN
sysReq.tim5.y = if not (sysReq.tim5.delayOnInit and sysReq.tim5.delayTime > 0.0) then sysReq.tim5.u else false
*/
void ReheatControllerFMU_eqFunction_417(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,417};
  modelica_boolean tmp98;
  tmp98 = Greater((data->simulationInfo->realParameter[467] /* sysReq.tim5.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[204]] /* sysReq.tim5.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[163] /* sysReq.tim5.delayOnInit PARAM */) && tmp98))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[203]] /* sysReq.tim5.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1699(DATA *data, threadData_t *threadData);


/*
equation index: 419
type: SIMPLE_ASSIGN
$PRE.sysReq.les.lesHys.y = sysReq.les.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_419(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,419};
  (data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[154] /* sysReq.les.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 420
type: SIMPLE_ASSIGN
sysReq.les.lesHys.y = not $PRE.sysReq.les.lesHys.y and sysReq.addPar.y < damVal.TDisSet or $PRE.sysReq.les.lesHys.y and sysReq.addPar.y < damVal.TDisSet + 0.25
*/
void ReheatControllerFMU_eqFunction_420(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,420};
  modelica_boolean tmp99;
  modelica_boolean tmp100;
  tmp99 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */));
  tmp100 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[185]] /* sysReq.les.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */)) && tmp99) || ((data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */) && tmp100));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1713(DATA *data, threadData_t *threadData);


/*
equation index: 422
type: SIMPLE_ASSIGN
$whenCondition60 = not sysReq.tim4.u
*/
void ReheatControllerFMU_eqFunction_422(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,422};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[56]] /* $whenCondition60 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[201]] /* sysReq.tim4.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 423
type: SIMPLE_ASSIGN
$whenCondition61 = sysReq.tim4.u
*/
void ReheatControllerFMU_eqFunction_423(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,423};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[57]] /* $whenCondition61 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[201]] /* sysReq.tim4.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 424
type: SIMPLE_ASSIGN
sysReq.tim4.y = if not (sysReq.tim4.delayOnInit and sysReq.tim4.delayTime > 0.0) then sysReq.tim4.u else false
*/
void ReheatControllerFMU_eqFunction_424(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,424};
  modelica_boolean tmp101;
  tmp101 = Greater((data->simulationInfo->realParameter[465] /* sysReq.tim4.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[202]] /* sysReq.tim4.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[162] /* sysReq.tim4.delayOnInit PARAM */) && tmp101))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[201]] /* sysReq.tim4.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1712(DATA *data, threadData_t *threadData);


/*
equation index: 426
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.a = 0.0
*/
void ReheatControllerFMU_eqFunction_426(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,426};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[163]] /* setPoi.popBreOutAir.a variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 427
type: SIMPLE_ASSIGN
actAirSet.occMod.y = 1
*/
void ReheatControllerFMU_eqFunction_427(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,427};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[1]] /* actAirSet.occMod.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 428
type: SIMPLE_ASSIGN
actAirSet.cooDowMod.y = 2
*/
void ReheatControllerFMU_eqFunction_428(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,428};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[0]] /* actAirSet.cooDowMod.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 429
type: SIMPLE_ASSIGN
actAirSet.setUpMod.y = 3
*/
void ReheatControllerFMU_eqFunction_429(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,429};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[3]] /* actAirSet.setUpMod.y DISCRETE */) = ((modelica_integer) 3);
  TRACE_POP
}

/*
equation index: 430
type: SIMPLE_ASSIGN
actAirSet.setBacMod.y = 5
*/
void ReheatControllerFMU_eqFunction_430(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,430};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[2]] /* actAirSet.setBacMod.y DISCRETE */) = ((modelica_integer) 5);
  TRACE_POP
}

/*
equation index: 431
type: SIMPLE_ASSIGN
actAirSet.warUpMod.y = 4
*/
void ReheatControllerFMU_eqFunction_431(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,431};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[4]] /* actAirSet.warUpMod.y DISCRETE */) = ((modelica_integer) 4);
  TRACE_POP
}

/*
equation index: 432
type: SIMPLE_ASSIGN
sysReq.thrCooResReq.y = 3
*/
void ReheatControllerFMU_eqFunction_432(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,432};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[31]] /* sysReq.thrCooResReq.y DISCRETE */) = ((modelica_integer) 3);
  TRACE_POP
}

/*
equation index: 433
type: SIMPLE_ASSIGN
sysReq.twoCooResReq.y = 2
*/
void ReheatControllerFMU_eqFunction_433(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,433};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[34]] /* sysReq.twoCooResReq.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 434
type: SIMPLE_ASSIGN
sysReq.thrPreResReq.y = 3
*/
void ReheatControllerFMU_eqFunction_434(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,434};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[33]] /* sysReq.thrPreResReq.y DISCRETE */) = ((modelica_integer) 3);
  TRACE_POP
}

/*
equation index: 435
type: SIMPLE_ASSIGN
sysReq.twoPreResReq.y = 2
*/
void ReheatControllerFMU_eqFunction_435(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,435};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[36]] /* sysReq.twoPreResReq.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 436
type: SIMPLE_ASSIGN
sysReq.thrHeaResReq.y = 3
*/
void ReheatControllerFMU_eqFunction_436(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,436};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[32]] /* sysReq.thrHeaResReq.y DISCRETE */) = ((modelica_integer) 3);
  TRACE_POP
}

/*
equation index: 437
type: SIMPLE_ASSIGN
sysReq.twoHeaResReq.y = 2
*/
void ReheatControllerFMU_eqFunction_437(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,437};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[35]] /* sysReq.twoHeaResReq.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 438
type: SIMPLE_ASSIGN
conLoo.conCoo.Dzero.y = 0.0
*/
void ReheatControllerFMU_eqFunction_438(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,438};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[45]] /* conLoo.conCoo.Dzero.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 439
type: SIMPLE_ASSIGN
conLoo.conHea.Dzero.y = 0.0
*/
void ReheatControllerFMU_eqFunction_439(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,439};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[58]] /* conLoo.conHea.Dzero.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 440
type: SIMPLE_ASSIGN
ala.conInt.y = 2
*/
void ReheatControllerFMU_eqFunction_440(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,440};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[9]] /* ala.conInt.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 441
type: SIMPLE_ASSIGN
ala.conInt2.y = 2
*/
void ReheatControllerFMU_eqFunction_441(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,441};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[10]] /* ala.conInt2.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 442
type: SIMPLE_ASSIGN
ala.occMod.y = 1
*/
void ReheatControllerFMU_eqFunction_442(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,442};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[13]] /* ala.occMod.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 443
type: SIMPLE_ASSIGN
setOve.conInt3.y = 1
*/
void ReheatControllerFMU_eqFunction_443(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,443};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[22]] /* setOve.conInt3.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 444
type: SIMPLE_ASSIGN
setOve.conInt4.y = 2
*/
void ReheatControllerFMU_eqFunction_444(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,444};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[23]] /* setOve.conInt4.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 445
type: SIMPLE_ASSIGN
timSup.conZer.y = 0.0
*/
void ReheatControllerFMU_eqFunction_445(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,445};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[183]] /* timSup.conZer.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 446
type: SIMPLE_ASSIGN
timSup.con5.y = true
*/
void ReheatControllerFMU_eqFunction_446(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,446};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[206]] /* timSup.con5.y DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 447
type: SIMPLE_ASSIGN
timSup.con1.y = true
*/
void ReheatControllerFMU_eqFunction_447(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,447};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[205]] /* timSup.con1.y DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 448
type: SIMPLE_ASSIGN
setPoi.zer.y = 0.0
*/
void ReheatControllerFMU_eqFunction_448(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,448};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[172]] /* setPoi.zer.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 449
type: SIMPLE_ASSIGN
setPoi.one.y = 1.0
*/
void ReheatControllerFMU_eqFunction_449(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,449};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[162]] /* setPoi.one.y variable */) = 1.0;
  TRACE_POP
}

/*
equation index: 450
type: SIMPLE_ASSIGN
setPoi.zonMinFlo.y = 0.5
*/
void ReheatControllerFMU_eqFunction_450(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,450};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[174]] /* setPoi.zonMinFlo.y variable */) = 0.5;
  TRACE_POP
}

/*
equation index: 451
type: SIMPLE_ASSIGN
setPoi.zer1.y = 0.0
*/
void ReheatControllerFMU_eqFunction_451(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,451};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[173]] /* setPoi.zer1.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 452
type: SIMPLE_ASSIGN
setPoi.occMod.y = 1
*/
void ReheatControllerFMU_eqFunction_452(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,452};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[24]] /* setPoi.occMod.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 453
type: SIMPLE_ASSIGN
damVal.conDam.Dzero.y = 0.0
*/
void ReheatControllerFMU_eqFunction_453(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,453};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[83]] /* damVal.conDam.Dzero.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 454
type: SIMPLE_ASSIGN
damVal.conVal.Dzero.y = 0.0
*/
void ReheatControllerFMU_eqFunction_454(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,454};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[104]] /* damVal.conVal.Dzero.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 455
type: SIMPLE_ASSIGN
damVal.conZer.y = 0.0
*/
void ReheatControllerFMU_eqFunction_455(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,455};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[117]] /* damVal.conZer.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 456
type: SIMPLE_ASSIGN
damVal.conOne.y = 1.0
*/
void ReheatControllerFMU_eqFunction_456(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,456};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[98]] /* damVal.conOne.y variable */) = 1.0;
  TRACE_POP
}

/*
equation index: 457
type: SIMPLE_ASSIGN
damVal.conZer2.y = 0.0
*/
void ReheatControllerFMU_eqFunction_457(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,457};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[118]] /* damVal.conZer2.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 458
type: SIMPLE_ASSIGN
damVal.conHal1.y = 0.5
*/
void ReheatControllerFMU_eqFunction_458(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,458};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[97]] /* damVal.conHal1.y variable */) = 0.5;
  TRACE_POP
}

/*
equation index: 459
type: SIMPLE_ASSIGN
damVal.conOne2.y = 1.0
*/
void ReheatControllerFMU_eqFunction_459(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,459};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[99]] /* damVal.conOne2.y variable */) = 1.0;
  TRACE_POP
}

/*
equation index: 460
type: SIMPLE_ASSIGN
damVal.conHal.y = 0.5
*/
void ReheatControllerFMU_eqFunction_460(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,460};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[96]] /* damVal.conHal.y variable */) = 0.5;
  TRACE_POP
}

/*
equation index: 461
type: SIMPLE_ASSIGN
damVal.conZer3.y = 0.0
*/
void ReheatControllerFMU_eqFunction_461(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,461};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[119]] /* damVal.conZer3.y variable */) = 0.0;
  TRACE_POP
}

/*
equation index: 462
type: SIMPLE_ASSIGN
damVal.occMod.y = 1
*/
void ReheatControllerFMU_eqFunction_462(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,462};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[18]] /* damVal.occMod.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 463
type: SIMPLE_ASSIGN
damVal.unOcc.y = 7
*/
void ReheatControllerFMU_eqFunction_463(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,463};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[19]] /* damVal.unOcc.y DISCRETE */) = ((modelica_integer) 7);
  TRACE_POP
}

/*
equation index: 464
type: SIMPLE_ASSIGN
damVal.conInt.y = 1
*/
void ReheatControllerFMU_eqFunction_464(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,464};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[14]] /* damVal.conInt.y DISCRETE */) = ((modelica_integer) 1);
  TRACE_POP
}

/*
equation index: 465
type: SIMPLE_ASSIGN
damVal.conInt1.y = 2
*/
void ReheatControllerFMU_eqFunction_465(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,465};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[15]] /* damVal.conInt1.y DISCRETE */) = ((modelica_integer) 2);
  TRACE_POP
}

/*
equation index: 466
type: SIMPLE_ASSIGN
damVal.conInt2.y = 3
*/
void ReheatControllerFMU_eqFunction_466(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,466};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[16]] /* damVal.conInt2.y DISCRETE */) = ((modelica_integer) 3);
  TRACE_POP
}

/*
equation index: 467
type: SIMPLE_ASSIGN
damVal.conInt5.y = 4
*/
void ReheatControllerFMU_eqFunction_467(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,467};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[17]] /* damVal.conInt5.y DISCRETE */) = ((modelica_integer) 4);
  TRACE_POP
}

/*
equation index: 468
type: SIMPLE_ASSIGN
sysReq.sampler.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_468(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,468};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[188]] /* sysReq.sampler.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 469
type: SIMPLE_ASSIGN
$whenCondition55 = sysReq.sampler.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_469(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,469};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[50]] /* $whenCondition55 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[188]] /* sysReq.sampler.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 470
type: SIMPLE_ASSIGN
sysReq.sampler1.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_470(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,470};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[190]] /* sysReq.sampler1.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 471
type: SIMPLE_ASSIGN
$whenCondition54 = sysReq.sampler1.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_471(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,471};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[49]] /* $whenCondition54 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[190]] /* sysReq.sampler1.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 472
type: SIMPLE_ASSIGN
sysReq.sampler2.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_472(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,472};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[192]] /* sysReq.sampler2.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 473
type: SIMPLE_ASSIGN
$whenCondition53 = sysReq.sampler2.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_473(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,473};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[48]] /* $whenCondition53 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[192]] /* sysReq.sampler2.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 474
type: SIMPLE_ASSIGN
sysReq.sampler3.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_474(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,474};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[194]] /* sysReq.sampler3.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 475
type: SIMPLE_ASSIGN
$whenCondition52 = sysReq.sampler3.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_475(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,475};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[47]] /* $whenCondition52 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[194]] /* sysReq.sampler3.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 476
type: SIMPLE_ASSIGN
timSup.samSet.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_476(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,476};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[215]] /* timSup.samSet.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 477
type: SIMPLE_ASSIGN
$whenCondition18 = timSup.samSet.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_477(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,477};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[9]] /* $whenCondition18 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[215]] /* timSup.samSet.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 478
type: SIMPLE_ASSIGN
timSup.uniDel.sampleTrigger = false
*/
void ReheatControllerFMU_eqFunction_478(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,478};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[219]] /* timSup.uniDel.sampleTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 479
type: SIMPLE_ASSIGN
$whenCondition17 = timSup.uniDel.sampleTrigger
*/
void ReheatControllerFMU_eqFunction_479(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,479};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[8]] /* $whenCondition17 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[219]] /* timSup.uniDel.sampleTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 480
type: SIMPLE_ASSIGN
timSup.truDel.t_next = time + timSup.truDel.delayTime
*/
void ReheatControllerFMU_eqFunction_480(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,480};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[220]] /* timSup.truDel.t_next DISCRETE */) = data->localData[0]->timeValue + (data->simulationInfo->realParameter[498] /* timSup.truDel.delayTime PARAM */);
  TRACE_POP
}

/*
equation index: 481
type: SIMPLE_ASSIGN
ala.fanIni.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_481(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,481};
  (data->simulationInfo->realParameter[72] /* ala.fanIni.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 482
type: SIMPLE_ASSIGN
ala.fanIni.t_next = if not ala.fanIni.delayOnInit then ala.fanIni.t_past else time + ala.fanIni.delayTime
*/
void ReheatControllerFMU_eqFunction_482(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,482};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[192]] /* ala.fanIni.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[6] /* ala.fanIni.delayOnInit PARAM */))?(data->simulationInfo->realParameter[72] /* ala.fanIni.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[71] /* ala.fanIni.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 483
type: SIMPLE_ASSIGN
ala.truDel7.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_483(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,483};
  (data->simulationInfo->realParameter[126] /* ala.truDel7.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 484
type: SIMPLE_ASSIGN
ala.truDel7.t_next = if not ala.truDel7.delayOnInit then ala.truDel7.t_past else time + ala.truDel7.delayTime
*/
void ReheatControllerFMU_eqFunction_484(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,484};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[200]] /* ala.truDel7.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[39] /* ala.truDel7.delayOnInit PARAM */))?(data->simulationInfo->realParameter[126] /* ala.truDel7.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[125] /* ala.truDel7.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 485
type: SIMPLE_ASSIGN
ala.truDel6.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_485(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,485};
  (data->simulationInfo->realParameter[124] /* ala.truDel6.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 486
type: SIMPLE_ASSIGN
ala.truDel6.t_next = if not ala.truDel6.delayOnInit then ala.truDel6.t_past else time + ala.truDel6.delayTime
*/
void ReheatControllerFMU_eqFunction_486(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,486};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[199]] /* ala.truDel6.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[38] /* ala.truDel6.delayOnInit PARAM */))?(data->simulationInfo->realParameter[124] /* ala.truDel6.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[123] /* ala.truDel6.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 487
type: SIMPLE_ASSIGN
ala.truDel5.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_487(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,487};
  (data->simulationInfo->realParameter[122] /* ala.truDel5.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 488
type: SIMPLE_ASSIGN
ala.truDel5.t_next = if not ala.truDel5.delayOnInit then ala.truDel5.t_past else time + ala.truDel5.delayTime
*/
void ReheatControllerFMU_eqFunction_488(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,488};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[198]] /* ala.truDel5.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[37] /* ala.truDel5.delayOnInit PARAM */))?(data->simulationInfo->realParameter[122] /* ala.truDel5.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[121] /* ala.truDel5.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 489
type: SIMPLE_ASSIGN
ala.truDel4.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_489(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,489};
  (data->simulationInfo->realParameter[120] /* ala.truDel4.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 490
type: SIMPLE_ASSIGN
ala.truDel4.t_next = if not ala.truDel4.delayOnInit then ala.truDel4.t_past else time + ala.truDel4.delayTime
*/
void ReheatControllerFMU_eqFunction_490(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,490};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[197]] /* ala.truDel4.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[36] /* ala.truDel4.delayOnInit PARAM */))?(data->simulationInfo->realParameter[120] /* ala.truDel4.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[119] /* ala.truDel4.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 491
type: SIMPLE_ASSIGN
ala.truDel3.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_491(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,491};
  (data->simulationInfo->realParameter[118] /* ala.truDel3.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 492
type: SIMPLE_ASSIGN
ala.truDel3.t_next = if not ala.truDel3.delayOnInit then ala.truDel3.t_past else time + ala.truDel3.delayTime
*/
void ReheatControllerFMU_eqFunction_492(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,492};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[196]] /* ala.truDel3.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[35] /* ala.truDel3.delayOnInit PARAM */))?(data->simulationInfo->realParameter[118] /* ala.truDel3.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[117] /* ala.truDel3.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 493
type: SIMPLE_ASSIGN
ala.truDel2.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_493(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,493};
  (data->simulationInfo->realParameter[116] /* ala.truDel2.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 494
type: SIMPLE_ASSIGN
ala.truDel2.t_next = if not ala.truDel2.delayOnInit then ala.truDel2.t_past else time + ala.truDel2.delayTime
*/
void ReheatControllerFMU_eqFunction_494(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,494};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[195]] /* ala.truDel2.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[34] /* ala.truDel2.delayOnInit PARAM */))?(data->simulationInfo->realParameter[116] /* ala.truDel2.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[115] /* ala.truDel2.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 495
type: SIMPLE_ASSIGN
ala.truDel1.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_495(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,495};
  (data->simulationInfo->realParameter[114] /* ala.truDel1.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 496
type: SIMPLE_ASSIGN
ala.truDel1.t_next = if not ala.truDel1.delayOnInit then ala.truDel1.t_past else time + ala.truDel1.delayTime
*/
void ReheatControllerFMU_eqFunction_496(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,496};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[194]] /* ala.truDel1.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[33] /* ala.truDel1.delayOnInit PARAM */))?(data->simulationInfo->realParameter[114] /* ala.truDel1.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[113] /* ala.truDel1.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 497
type: SIMPLE_ASSIGN
ala.truDel.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_497(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,497};
  (data->simulationInfo->realParameter[112] /* ala.truDel.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 498
type: SIMPLE_ASSIGN
ala.truDel.t_next = if not ala.truDel.delayOnInit then ala.truDel.t_past else time + ala.truDel.delayTime
*/
void ReheatControllerFMU_eqFunction_498(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,498};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[193]] /* ala.truDel.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[32] /* ala.truDel.delayOnInit PARAM */))?(data->simulationInfo->realParameter[112] /* ala.truDel.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[111] /* ala.truDel.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 499
type: SIMPLE_ASSIGN
conLoo.disHea.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_499(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,499};
  (data->simulationInfo->realParameter[185] /* conLoo.disHea.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 500
type: SIMPLE_ASSIGN
conLoo.disHea.t_next = if not conLoo.disHea.delayOnInit then conLoo.disHea.t_past else time + conLoo.disHea.delayTime
*/
void ReheatControllerFMU_eqFunction_500(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,500};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[202]] /* conLoo.disHea.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[53] /* conLoo.disHea.delayOnInit PARAM */))?(data->simulationInfo->realParameter[185] /* conLoo.disHea.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[184] /* conLoo.disHea.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 501
type: SIMPLE_ASSIGN
conLoo.disCoo.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_501(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,501};
  (data->simulationInfo->realParameter[183] /* conLoo.disCoo.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 502
type: SIMPLE_ASSIGN
conLoo.disCoo.t_next = if not conLoo.disCoo.delayOnInit then conLoo.disCoo.t_past else time + conLoo.disCoo.delayTime
*/
void ReheatControllerFMU_eqFunction_502(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,502};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[201]] /* conLoo.disCoo.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[52] /* conLoo.disCoo.delayOnInit PARAM */))?(data->simulationInfo->realParameter[183] /* conLoo.disCoo.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[182] /* conLoo.disCoo.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 503
type: SIMPLE_ASSIGN
sysReq.tim5.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_503(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,503};
  (data->simulationInfo->realParameter[468] /* sysReq.tim5.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 504
type: SIMPLE_ASSIGN
sysReq.tim5.t_next = if not sysReq.tim5.delayOnInit then sysReq.tim5.t_past else time + sysReq.tim5.delayTime
*/
void ReheatControllerFMU_eqFunction_504(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,504};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[215]] /* sysReq.tim5.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[163] /* sysReq.tim5.delayOnInit PARAM */))?(data->simulationInfo->realParameter[468] /* sysReq.tim5.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[467] /* sysReq.tim5.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 505
type: SIMPLE_ASSIGN
sysReq.tim4.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_505(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,505};
  (data->simulationInfo->realParameter[466] /* sysReq.tim4.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 506
type: SIMPLE_ASSIGN
sysReq.tim4.t_next = if not sysReq.tim4.delayOnInit then sysReq.tim4.t_past else time + sysReq.tim4.delayTime
*/
void ReheatControllerFMU_eqFunction_506(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,506};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[214]] /* sysReq.tim4.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[162] /* sysReq.tim4.delayOnInit PARAM */))?(data->simulationInfo->realParameter[466] /* sysReq.tim4.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[465] /* sysReq.tim4.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 507
type: SIMPLE_ASSIGN
sysReq.tim3.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_507(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,507};
  (data->simulationInfo->realParameter[464] /* sysReq.tim3.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 508
type: SIMPLE_ASSIGN
sysReq.tim3.t_next = if not sysReq.tim3.delayOnInit then sysReq.tim3.t_past else time + sysReq.tim3.delayTime
*/
void ReheatControllerFMU_eqFunction_508(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,508};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[213]] /* sysReq.tim3.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[161] /* sysReq.tim3.delayOnInit PARAM */))?(data->simulationInfo->realParameter[464] /* sysReq.tim3.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[463] /* sysReq.tim3.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 509
type: SIMPLE_ASSIGN
sysReq.tim2.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_509(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,509};
  (data->simulationInfo->realParameter[462] /* sysReq.tim2.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 510
type: SIMPLE_ASSIGN
sysReq.tim2.t_next = if not sysReq.tim2.delayOnInit then sysReq.tim2.t_past else time + sysReq.tim2.delayTime
*/
void ReheatControllerFMU_eqFunction_510(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,510};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[212]] /* sysReq.tim2.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[160] /* sysReq.tim2.delayOnInit PARAM */))?(data->simulationInfo->realParameter[462] /* sysReq.tim2.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[461] /* sysReq.tim2.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 511
type: SIMPLE_ASSIGN
sysReq.tim1.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_511(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,511};
  (data->simulationInfo->realParameter[460] /* sysReq.tim1.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 512
type: SIMPLE_ASSIGN
sysReq.tim1.t_next = if not sysReq.tim1.delayOnInit then sysReq.tim1.t_past else time + sysReq.tim1.delayTime
*/
void ReheatControllerFMU_eqFunction_512(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,512};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[211]] /* sysReq.tim1.t_next DISCRETE */) = ((!(data->simulationInfo->booleanParameter[159] /* sysReq.tim1.delayOnInit PARAM */))?(data->simulationInfo->realParameter[460] /* sysReq.tim1.t_past PARAM */):data->localData[0]->timeValue + (data->simulationInfo->realParameter[459] /* sysReq.tim1.delayTime PARAM */));
  TRACE_POP
}

/*
equation index: 513
type: SIMPLE_ASSIGN
$PRE.timSup.truDel.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_513(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,513};
  (data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 514
type: SIMPLE_ASSIGN
$whenCondition7 = time >= $PRE.timSup.truDel.t_next
*/
void ReheatControllerFMU_eqFunction_514(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,514};
  modelica_boolean tmp102;
  tmp102 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[66]] /* $whenCondition7 DISCRETE */) = tmp102;
  TRACE_POP
}

/*
equation index: 515
type: SIMPLE_ASSIGN
$PRE.ala.fanIni.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_515(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,515};
  (data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 516
type: SIMPLE_ASSIGN
$whenCondition19 = time >= $PRE.ala.fanIni.t_next
*/
void ReheatControllerFMU_eqFunction_516(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,516};
  modelica_boolean tmp103;
  tmp103 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[10]] /* $whenCondition19 DISCRETE */) = tmp103;
  TRACE_POP
}

/*
equation index: 517
type: SIMPLE_ASSIGN
$PRE.ala.truDel7.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_517(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,517};
  (data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 518
type: SIMPLE_ASSIGN
$whenCondition22 = time >= $PRE.ala.truDel7.t_next
*/
void ReheatControllerFMU_eqFunction_518(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,518};
  modelica_boolean tmp104;
  tmp104 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[14]] /* $whenCondition22 DISCRETE */) = tmp104;
  TRACE_POP
}

/*
equation index: 519
type: SIMPLE_ASSIGN
$PRE.ala.truDel6.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_519(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,519};
  (data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 520
type: SIMPLE_ASSIGN
$whenCondition25 = time >= $PRE.ala.truDel6.t_next
*/
void ReheatControllerFMU_eqFunction_520(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,520};
  modelica_boolean tmp105;
  tmp105 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[17]] /* $whenCondition25 DISCRETE */) = tmp105;
  TRACE_POP
}

/*
equation index: 521
type: SIMPLE_ASSIGN
$PRE.ala.truDel5.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_521(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,521};
  (data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 522
type: SIMPLE_ASSIGN
$whenCondition28 = time >= $PRE.ala.truDel5.t_next
*/
void ReheatControllerFMU_eqFunction_522(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,522};
  modelica_boolean tmp106;
  tmp106 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[20]] /* $whenCondition28 DISCRETE */) = tmp106;
  TRACE_POP
}

/*
equation index: 523
type: SIMPLE_ASSIGN
$PRE.ala.truDel4.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_523(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,523};
  (data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 524
type: SIMPLE_ASSIGN
$whenCondition31 = time >= $PRE.ala.truDel4.t_next
*/
void ReheatControllerFMU_eqFunction_524(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,524};
  modelica_boolean tmp107;
  tmp107 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[24]] /* $whenCondition31 DISCRETE */) = tmp107;
  TRACE_POP
}

/*
equation index: 525
type: SIMPLE_ASSIGN
$PRE.ala.truDel3.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_525(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,525};
  (data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 526
type: SIMPLE_ASSIGN
$whenCondition34 = time >= $PRE.ala.truDel3.t_next
*/
void ReheatControllerFMU_eqFunction_526(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,526};
  modelica_boolean tmp108;
  tmp108 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[27]] /* $whenCondition34 DISCRETE */) = tmp108;
  TRACE_POP
}

/*
equation index: 527
type: SIMPLE_ASSIGN
$PRE.ala.truDel2.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_527(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,527};
  (data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 528
type: SIMPLE_ASSIGN
$whenCondition37 = time >= $PRE.ala.truDel2.t_next
*/
void ReheatControllerFMU_eqFunction_528(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,528};
  modelica_boolean tmp109;
  tmp109 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[30]] /* $whenCondition37 DISCRETE */) = tmp109;
  TRACE_POP
}

/*
equation index: 529
type: SIMPLE_ASSIGN
$PRE.ala.truDel1.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_529(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,529};
  (data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 530
type: SIMPLE_ASSIGN
$whenCondition40 = time >= $PRE.ala.truDel1.t_next
*/
void ReheatControllerFMU_eqFunction_530(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,530};
  modelica_boolean tmp110;
  tmp110 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[34]] /* $whenCondition40 DISCRETE */) = tmp110;
  TRACE_POP
}

/*
equation index: 531
type: SIMPLE_ASSIGN
$PRE.ala.truDel.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_531(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,531};
  (data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 532
type: SIMPLE_ASSIGN
$whenCondition43 = time >= $PRE.ala.truDel.t_next
*/
void ReheatControllerFMU_eqFunction_532(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,532};
  modelica_boolean tmp111;
  tmp111 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[37]] /* $whenCondition43 DISCRETE */) = tmp111;
  TRACE_POP
}

/*
equation index: 533
type: SIMPLE_ASSIGN
$PRE.conLoo.disHea.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_533(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,533};
  (data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 534
type: SIMPLE_ASSIGN
$whenCondition46 = time >= $PRE.conLoo.disHea.t_next
*/
void ReheatControllerFMU_eqFunction_534(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,534};
  modelica_boolean tmp112;
  tmp112 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[40]] /* $whenCondition46 DISCRETE */) = tmp112;
  TRACE_POP
}

/*
equation index: 535
type: SIMPLE_ASSIGN
$PRE.conLoo.disCoo.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_535(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,535};
  (data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 536
type: SIMPLE_ASSIGN
$whenCondition49 = time >= $PRE.conLoo.disCoo.t_next
*/
void ReheatControllerFMU_eqFunction_536(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,536};
  modelica_boolean tmp113;
  tmp113 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[43]] /* $whenCondition49 DISCRETE */) = tmp113;
  TRACE_POP
}

/*
equation index: 537
type: SIMPLE_ASSIGN
$PRE.sysReq.tim5.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_537(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,537};
  (data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 538
type: SIMPLE_ASSIGN
$whenCondition56 = time >= $PRE.sysReq.tim5.t_next
*/
void ReheatControllerFMU_eqFunction_538(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,538};
  modelica_boolean tmp114;
  tmp114 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[51]] /* $whenCondition56 DISCRETE */) = tmp114;
  TRACE_POP
}

/*
equation index: 539
type: SIMPLE_ASSIGN
$PRE.sysReq.tim4.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_539(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,539};
  (data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 540
type: SIMPLE_ASSIGN
$whenCondition59 = time >= $PRE.sysReq.tim4.t_next
*/
void ReheatControllerFMU_eqFunction_540(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,540};
  modelica_boolean tmp115;
  tmp115 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[54]] /* $whenCondition59 DISCRETE */) = tmp115;
  TRACE_POP
}

/*
equation index: 541
type: SIMPLE_ASSIGN
$PRE.sysReq.tim3.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_541(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,541};
  (data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 542
type: SIMPLE_ASSIGN
$whenCondition62 = time >= $PRE.sysReq.tim3.t_next
*/
void ReheatControllerFMU_eqFunction_542(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,542};
  modelica_boolean tmp116;
  tmp116 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[58]] /* $whenCondition62 DISCRETE */) = tmp116;
  TRACE_POP
}

/*
equation index: 543
type: SIMPLE_ASSIGN
$PRE.sysReq.tim2.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_543(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,543};
  (data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 544
type: SIMPLE_ASSIGN
$whenCondition65 = time >= $PRE.sysReq.tim2.t_next
*/
void ReheatControllerFMU_eqFunction_544(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,544};
  modelica_boolean tmp117;
  tmp117 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[61]] /* $whenCondition65 DISCRETE */) = tmp117;
  TRACE_POP
}

/*
equation index: 545
type: SIMPLE_ASSIGN
$PRE.sysReq.tim1.t_next = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_545(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,545};
  (data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 546
type: SIMPLE_ASSIGN
$whenCondition68 = time >= $PRE.sysReq.tim1.t_next
*/
void ReheatControllerFMU_eqFunction_546(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,546};
  modelica_boolean tmp118;
  tmp118 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[64]] /* $whenCondition68 DISCRETE */) = tmp118;
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1617(DATA *data, threadData_t *threadData);


/*
equation index: 548
type: SIMPLE_ASSIGN
$PRE.timSup.tim.passed = timSup.tim.t <= 0.0
*/
void ReheatControllerFMU_eqFunction_548(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,548};
  modelica_boolean tmp119;
  tmp119 = LessEq((data->simulationInfo->realParameter[495] /* timSup.tim.t PARAM */),0.0);
  (data->simulationInfo->booleanVarsPre[216] /* timSup.tim.passed DISCRETE */) = tmp119;
  TRACE_POP
}

/*
equation index: 549
type: SIMPLE_ASSIGN
timSup.tim.passed = $PRE.timSup.tim.passed
*/
void ReheatControllerFMU_eqFunction_549(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,549};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[216]] /* timSup.tim.passed DISCRETE */) = (data->simulationInfo->booleanVarsPre[216] /* timSup.tim.passed DISCRETE */);
  TRACE_POP
}

/*
equation index: 550
type: SIMPLE_ASSIGN
timSup.uniDel.u_internal = timSup.uniDel.y_start
*/
void ReheatControllerFMU_eqFunction_550(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,550};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[221]] /* timSup.uniDel.u_internal DISCRETE */) = (data->simulationInfo->realParameter[502] /* timSup.uniDel.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 551
type: SIMPLE_ASSIGN
$PRE.timSup.uniDel.u_internal = timSup.uniDel.u_internal
*/
void ReheatControllerFMU_eqFunction_551(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,551};
  (data->simulationInfo->realVarsPre[221] /* timSup.uniDel.u_internal DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[221]] /* timSup.uniDel.u_internal DISCRETE */);
  TRACE_POP
}

/*
equation index: 552
type: SIMPLE_ASSIGN
$PRE.timSup.samSet.firstTrigger = false
*/
void ReheatControllerFMU_eqFunction_552(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,552};
  (data->simulationInfo->booleanVarsPre[214] /* timSup.samSet.firstTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 553
type: SIMPLE_ASSIGN
timSup.samSet.firstTrigger = $PRE.timSup.samSet.firstTrigger
*/
void ReheatControllerFMU_eqFunction_553(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,553};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[214]] /* timSup.samSet.firstTrigger DISCRETE */) = (data->simulationInfo->booleanVarsPre[214] /* timSup.samSet.firstTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 554
type: SIMPLE_ASSIGN
$PRE.sysReq.sampler3.firstTrigger = false
*/
void ReheatControllerFMU_eqFunction_554(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,554};
  (data->simulationInfo->booleanVarsPre[193] /* sysReq.sampler3.firstTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 555
type: SIMPLE_ASSIGN
sysReq.sampler3.firstTrigger = $PRE.sysReq.sampler3.firstTrigger
*/
void ReheatControllerFMU_eqFunction_555(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,555};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[193]] /* sysReq.sampler3.firstTrigger DISCRETE */) = (data->simulationInfo->booleanVarsPre[193] /* sysReq.sampler3.firstTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 556
type: SIMPLE_ASSIGN
$PRE.sysReq.sampler2.firstTrigger = false
*/
void ReheatControllerFMU_eqFunction_556(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,556};
  (data->simulationInfo->booleanVarsPre[191] /* sysReq.sampler2.firstTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 557
type: SIMPLE_ASSIGN
sysReq.sampler2.firstTrigger = $PRE.sysReq.sampler2.firstTrigger
*/
void ReheatControllerFMU_eqFunction_557(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,557};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[191]] /* sysReq.sampler2.firstTrigger DISCRETE */) = (data->simulationInfo->booleanVarsPre[191] /* sysReq.sampler2.firstTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 558
type: SIMPLE_ASSIGN
$PRE.sysReq.sampler1.firstTrigger = false
*/
void ReheatControllerFMU_eqFunction_558(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,558};
  (data->simulationInfo->booleanVarsPre[189] /* sysReq.sampler1.firstTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 559
type: SIMPLE_ASSIGN
sysReq.sampler1.firstTrigger = $PRE.sysReq.sampler1.firstTrigger
*/
void ReheatControllerFMU_eqFunction_559(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,559};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[189]] /* sysReq.sampler1.firstTrigger DISCRETE */) = (data->simulationInfo->booleanVarsPre[189] /* sysReq.sampler1.firstTrigger DISCRETE */);
  TRACE_POP
}

/*
equation index: 560
type: SIMPLE_ASSIGN
$PRE.sysReq.sampler.firstTrigger = false
*/
void ReheatControllerFMU_eqFunction_560(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,560};
  (data->simulationInfo->booleanVarsPre[187] /* sysReq.sampler.firstTrigger DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 561
type: SIMPLE_ASSIGN
sysReq.sampler.firstTrigger = $PRE.sysReq.sampler.firstTrigger
*/
void ReheatControllerFMU_eqFunction_561(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,561};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[187]] /* sysReq.sampler.firstTrigger DISCRETE */) = (data->simulationInfo->booleanVarsPre[187] /* sysReq.sampler.firstTrigger DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1183(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1182(DATA *data, threadData_t *threadData);


/*
equation index: 564
type: SIMPLE_ASSIGN
$PRE.timSup.truDel.u = false
*/
void ReheatControllerFMU_eqFunction_564(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,564};
  (data->simulationInfo->booleanVarsPre[217] /* timSup.truDel.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 565
type: SIMPLE_ASSIGN
timSup.truDel.t_past = -1000.0 + time
*/
void ReheatControllerFMU_eqFunction_565(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,565};
  (data->simulationInfo->realParameter[499] /* timSup.truDel.t_past PARAM */) = -1000.0 + data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 566
type: SIMPLE_ASSIGN
timSup.uniDel.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / timSup.uniDel.samplePeriod)) * timSup.uniDel.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_566(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,566};
  (data->simulationInfo->realParameter[501] /* timSup.uniDel.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[500] /* timSup.uniDel.samplePeriod PARAM */),"timSup.uniDel.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[500] /* timSup.uniDel.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 567
type: SIMPLE_ASSIGN
timSup.samSet.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / timSup.samSet.samplePeriod)) * timSup.samSet.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_567(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,567};
  (data->simulationInfo->realParameter[492] /* timSup.samSet.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[491] /* timSup.samSet.samplePeriod PARAM */),"timSup.samSet.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[491] /* timSup.samSet.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 568
type: SIMPLE_ASSIGN
$PRE.ala.fanIni.u = false
*/
void ReheatControllerFMU_eqFunction_568(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,568};
  (data->simulationInfo->booleanVarsPre[93] /* ala.fanIni.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 569
type: SIMPLE_ASSIGN
$PRE.ala.truDel7.u = false
*/
void ReheatControllerFMU_eqFunction_569(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,569};
  (data->simulationInfo->booleanVarsPre[125] /* ala.truDel7.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 570
type: SIMPLE_ASSIGN
$PRE.ala.truDel6.u = false
*/
void ReheatControllerFMU_eqFunction_570(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,570};
  (data->simulationInfo->booleanVarsPre[123] /* ala.truDel6.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 571
type: SIMPLE_ASSIGN
$PRE.ala.truDel5.u = false
*/
void ReheatControllerFMU_eqFunction_571(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,571};
  (data->simulationInfo->booleanVarsPre[121] /* ala.truDel5.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 572
type: SIMPLE_ASSIGN
$PRE.ala.truDel4.u = false
*/
void ReheatControllerFMU_eqFunction_572(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,572};
  (data->simulationInfo->booleanVarsPre[119] /* ala.truDel4.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 573
type: SIMPLE_ASSIGN
$PRE.ala.truDel3.u = false
*/
void ReheatControllerFMU_eqFunction_573(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,573};
  (data->simulationInfo->booleanVarsPre[117] /* ala.truDel3.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 574
type: SIMPLE_ASSIGN
$PRE.ala.truDel2.u = false
*/
void ReheatControllerFMU_eqFunction_574(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,574};
  (data->simulationInfo->booleanVarsPre[115] /* ala.truDel2.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 575
type: SIMPLE_ASSIGN
$PRE.ala.truDel1.u = false
*/
void ReheatControllerFMU_eqFunction_575(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,575};
  (data->simulationInfo->booleanVarsPre[113] /* ala.truDel1.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 576
type: SIMPLE_ASSIGN
$PRE.ala.truDel.u = false
*/
void ReheatControllerFMU_eqFunction_576(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,576};
  (data->simulationInfo->booleanVarsPre[111] /* ala.truDel.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 577
type: SIMPLE_ASSIGN
$PRE.conLoo.disHea.u = false
*/
void ReheatControllerFMU_eqFunction_577(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,577};
  (data->simulationInfo->booleanVarsPre[130] /* conLoo.disHea.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 578
type: SIMPLE_ASSIGN
$PRE.conLoo.disCoo.u = false
*/
void ReheatControllerFMU_eqFunction_578(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,578};
  (data->simulationInfo->booleanVarsPre[127] /* conLoo.disCoo.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 579
type: SIMPLE_ASSIGN
sysReq.sampler3.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / sysReq.sampler3.samplePeriod)) * sysReq.sampler3.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_579(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,579};
  (data->simulationInfo->realParameter[455] /* sysReq.sampler3.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[454] /* sysReq.sampler3.samplePeriod PARAM */),"sysReq.sampler3.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[454] /* sysReq.sampler3.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 580
type: SIMPLE_ASSIGN
sysReq.sampler2.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / sysReq.sampler2.samplePeriod)) * sysReq.sampler2.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_580(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,580};
  (data->simulationInfo->realParameter[453] /* sysReq.sampler2.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[452] /* sysReq.sampler2.samplePeriod PARAM */),"sysReq.sampler2.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[452] /* sysReq.sampler2.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 581
type: SIMPLE_ASSIGN
sysReq.sampler1.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / sysReq.sampler1.samplePeriod)) * sysReq.sampler1.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_581(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,581};
  (data->simulationInfo->realParameter[451] /* sysReq.sampler1.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[450] /* sysReq.sampler1.samplePeriod PARAM */),"sysReq.sampler1.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[450] /* sysReq.sampler1.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 582
type: SIMPLE_ASSIGN
sysReq.sampler.t0 = Buildings.Utilities.Math.Functions.round((*Real*)(integer(time / sysReq.sampler.samplePeriod)) * sysReq.sampler.samplePeriod, 6)
*/
void ReheatControllerFMU_eqFunction_582(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,582};
  (data->simulationInfo->realParameter[449] /* sysReq.sampler.t0 PARAM */) = omc_Buildings_Utilities_Math_Functions_round(threadData, (((modelica_real)((modelica_integer)floor(DIVISION_SIM(data->localData[0]->timeValue,(data->simulationInfo->realParameter[448] /* sysReq.sampler.samplePeriod PARAM */),"sysReq.sampler.samplePeriod",equationIndexes))))) * ((data->simulationInfo->realParameter[448] /* sysReq.sampler.samplePeriod PARAM */)), ((modelica_integer) 6));
  TRACE_POP
}

/*
equation index: 583
type: SIMPLE_ASSIGN
$PRE.sysReq.tim5.u = false
*/
void ReheatControllerFMU_eqFunction_583(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,583};
  (data->simulationInfo->booleanVarsPre[203] /* sysReq.tim5.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 584
type: SIMPLE_ASSIGN
$PRE.sysReq.tim4.u = false
*/
void ReheatControllerFMU_eqFunction_584(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,584};
  (data->simulationInfo->booleanVarsPre[201] /* sysReq.tim4.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 585
type: SIMPLE_ASSIGN
$PRE.sysReq.tim3.u = false
*/
void ReheatControllerFMU_eqFunction_585(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,585};
  (data->simulationInfo->booleanVarsPre[199] /* sysReq.tim3.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 586
type: SIMPLE_ASSIGN
$PRE.sysReq.tim2.u = false
*/
void ReheatControllerFMU_eqFunction_586(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,586};
  (data->simulationInfo->booleanVarsPre[197] /* sysReq.tim2.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 587
type: SIMPLE_ASSIGN
$PRE.sysReq.tim1.u = false
*/
void ReheatControllerFMU_eqFunction_587(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,587};
  (data->simulationInfo->booleanVarsPre[195] /* sysReq.tim1.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 593
type: ALGORITHM

  assert(conLoo.conCoo.lim.uMin < conLoo.conCoo.lim.uMax, "uMin must be smaller than uMax. Check parameters.");
*/
void ReheatControllerFMU_eqFunction_593(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,593};
  modelica_boolean tmp120;
  static const MMC_DEFSTRINGLIT(tmp121,49,"uMin must be smaller than uMax. Check parameters.");
  static int tmp122 = 0;
  {
    tmp120 = Less((data->simulationInfo->realParameter[145] /* conLoo.conCoo.lim.uMin PARAM */),(data->simulationInfo->realParameter[144] /* conLoo.conCoo.lim.uMax PARAM */));
    if(!tmp120)
    {
      {
        const char* assert_cond = "(conLoo.conCoo.lim.uMin < conLoo.conCoo.lim.uMax)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp121)));
          data->simulationInfo->needToReThrow = 1;
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          omc_assert_withEquationIndexes(threadData, info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp121)));
        }
      }
    }
  }
  TRACE_POP
}

/*
equation index: 592
type: ALGORITHM

  assert(conLoo.conHea.lim.uMin < conLoo.conHea.lim.uMax, "uMin must be smaller than uMax. Check parameters.");
*/
void ReheatControllerFMU_eqFunction_592(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,592};
  modelica_boolean tmp123;
  static const MMC_DEFSTRINGLIT(tmp124,49,"uMin must be smaller than uMax. Check parameters.");
  static int tmp125 = 0;
  {
    tmp123 = Less((data->simulationInfo->realParameter[169] /* conLoo.conHea.lim.uMin PARAM */),(data->simulationInfo->realParameter[168] /* conLoo.conHea.lim.uMax PARAM */));
    if(!tmp123)
    {
      {
        const char* assert_cond = "(conLoo.conHea.lim.uMin < conLoo.conHea.lim.uMax)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp124)));
          data->simulationInfo->needToReThrow = 1;
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          omc_assert_withEquationIndexes(threadData, info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp124)));
        }
      }
    }
  }
  TRACE_POP
}

/*
equation index: 591
type: ALGORITHM

  assert(true, "uMin must be smaller than uMax. Check parameters.");
*/
void ReheatControllerFMU_eqFunction_591(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,591};
  static const MMC_DEFSTRINGLIT(tmp126,49,"uMin must be smaller than uMax. Check parameters.");
  static int tmp127 = 0;
  {
    if(!1 /* true */)
    {
      {
        const char* assert_cond = "(true)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp126)));
          data->simulationInfo->needToReThrow = 1;
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          omc_assert_withEquationIndexes(threadData, info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp126)));
        }
      }
    }
  }
  TRACE_POP
}

/*
equation index: 590
type: ALGORITHM

  assert(true, "uMin must be smaller than uMax. Check parameters.");
*/
void ReheatControllerFMU_eqFunction_590(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,590};
  static const MMC_DEFSTRINGLIT(tmp128,49,"uMin must be smaller than uMax. Check parameters.");
  static int tmp129 = 0;
  {
    if(!1 /* true */)
    {
      {
        const char* assert_cond = "(true)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp128)));
          data->simulationInfo->needToReThrow = 1;
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Limiter.mo",16,3,17,57,0};
          omc_assert_withEquationIndexes(threadData, info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(MMC_REFSTRINGLIT(tmp128)));
        }
      }
    }
  }
  TRACE_POP
}

/*
equation index: 589
type: ALGORITHM

  assert(conLoo.conCoo.cheYMinMax.k, conLoo.conCoo.assMesYMinMax.message);
*/
void ReheatControllerFMU_eqFunction_589(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,589};
  static int tmp130 = 0;
  if(!tmp130)
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
      tmp130 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 588
type: ALGORITHM

  assert(conLoo.conHea.cheYMinMax.k, conLoo.conHea.assMesYMinMax.message);
*/
void ReheatControllerFMU_eqFunction_588(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,588};
  static int tmp131 = 0;
  if(!tmp131)
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
      tmp131 = 1;
    }
  }
  TRACE_POP
}
OMC_DISABLE_OPT
void ReheatControllerFMU_functionInitialEquations_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ReheatControllerFMU_eqFunction_1466(data, threadData);
  ReheatControllerFMU_eqFunction_299(data, threadData);
  ReheatControllerFMU_eqFunction_300(data, threadData);
  ReheatControllerFMU_eqFunction_301(data, threadData);
  ReheatControllerFMU_eqFunction_302(data, threadData);
  ReheatControllerFMU_eqFunction_1471(data, threadData);
  ReheatControllerFMU_eqFunction_304(data, threadData);
  ReheatControllerFMU_eqFunction_1473(data, threadData);
  ReheatControllerFMU_eqFunction_1474(data, threadData);
  ReheatControllerFMU_eqFunction_1472(data, threadData);
  ReheatControllerFMU_eqFunction_308(data, threadData);
  ReheatControllerFMU_eqFunction_309(data, threadData);
  ReheatControllerFMU_eqFunction_310(data, threadData);
  ReheatControllerFMU_eqFunction_1482(data, threadData);
  ReheatControllerFMU_eqFunction_1483(data, threadData);
  ReheatControllerFMU_eqFunction_1484(data, threadData);
  ReheatControllerFMU_eqFunction_314(data, threadData);
  ReheatControllerFMU_eqFunction_1570(data, threadData);
  ReheatControllerFMU_eqFunction_1568(data, threadData);
  ReheatControllerFMU_eqFunction_1532(data, threadData);
  ReheatControllerFMU_eqFunction_1534(data, threadData);
  ReheatControllerFMU_eqFunction_1535(data, threadData);
  ReheatControllerFMU_eqFunction_1565(data, threadData);
  ReheatControllerFMU_eqFunction_321(data, threadData);
  ReheatControllerFMU_eqFunction_1562(data, threadData);
  ReheatControllerFMU_eqFunction_1537(data, threadData);
  ReheatControllerFMU_eqFunction_324(data, threadData);
  ReheatControllerFMU_eqFunction_1539(data, threadData);
  ReheatControllerFMU_eqFunction_1540(data, threadData);
  ReheatControllerFMU_eqFunction_327(data, threadData);
  ReheatControllerFMU_eqFunction_328(data, threadData);
  ReheatControllerFMU_eqFunction_329(data, threadData);
  ReheatControllerFMU_eqFunction_330(data, threadData);
  ReheatControllerFMU_eqFunction_331(data, threadData);
  ReheatControllerFMU_eqFunction_332(data, threadData);
  ReheatControllerFMU_eqFunction_1548(data, threadData);
  ReheatControllerFMU_eqFunction_1560(data, threadData);
  ReheatControllerFMU_eqFunction_1561(data, threadData);
  ReheatControllerFMU_eqFunction_1563(data, threadData);
  ReheatControllerFMU_eqFunction_1564(data, threadData);
  ReheatControllerFMU_eqFunction_1533(data, threadData);
  ReheatControllerFMU_eqFunction_1513(data, threadData);
  ReheatControllerFMU_eqFunction_340(data, threadData);
  ReheatControllerFMU_eqFunction_341(data, threadData);
  ReheatControllerFMU_eqFunction_342(data, threadData);
  ReheatControllerFMU_eqFunction_343(data, threadData);
  ReheatControllerFMU_eqFunction_344(data, threadData);
  ReheatControllerFMU_eqFunction_345(data, threadData);
  ReheatControllerFMU_eqFunction_1512(data, threadData);
  ReheatControllerFMU_eqFunction_347(data, threadData);
  ReheatControllerFMU_eqFunction_348(data, threadData);
  ReheatControllerFMU_eqFunction_349(data, threadData);
  ReheatControllerFMU_eqFunction_1521(data, threadData);
  ReheatControllerFMU_eqFunction_1522(data, threadData);
  ReheatControllerFMU_eqFunction_1523(data, threadData);
  ReheatControllerFMU_eqFunction_1524(data, threadData);
  ReheatControllerFMU_eqFunction_1485(data, threadData);
  ReheatControllerFMU_eqFunction_355(data, threadData);
  ReheatControllerFMU_eqFunction_356(data, threadData);
  ReheatControllerFMU_eqFunction_357(data, threadData);
  ReheatControllerFMU_eqFunction_358(data, threadData);
  ReheatControllerFMU_eqFunction_359(data, threadData);
  ReheatControllerFMU_eqFunction_1509(data, threadData);
  ReheatControllerFMU_eqFunction_1510(data, threadData);
  ReheatControllerFMU_eqFunction_1511(data, threadData);
  ReheatControllerFMU_eqFunction_1525(data, threadData);
  ReheatControllerFMU_eqFunction_1526(data, threadData);
  ReheatControllerFMU_eqFunction_1235(data, threadData);
  ReheatControllerFMU_eqFunction_1236(data, threadData);
  ReheatControllerFMU_eqFunction_1238(data, threadData);
  ReheatControllerFMU_eqFunction_1239(data, threadData);
  ReheatControllerFMU_eqFunction_369(data, threadData);
  ReheatControllerFMU_eqFunction_370(data, threadData);
  ReheatControllerFMU_eqFunction_1679(data, threadData);
  ReheatControllerFMU_eqFunction_372(data, threadData);
  ReheatControllerFMU_eqFunction_373(data, threadData);
  ReheatControllerFMU_eqFunction_1681(data, threadData);
  ReheatControllerFMU_eqFunction_375(data, threadData);
  ReheatControllerFMU_eqFunction_376(data, threadData);
  ReheatControllerFMU_eqFunction_377(data, threadData);
  ReheatControllerFMU_eqFunction_378(data, threadData);
  ReheatControllerFMU_eqFunction_379(data, threadData);
  ReheatControllerFMU_eqFunction_380(data, threadData);
  ReheatControllerFMU_eqFunction_381(data, threadData);
  ReheatControllerFMU_eqFunction_382(data, threadData);
  ReheatControllerFMU_eqFunction_1574(data, threadData);
  ReheatControllerFMU_eqFunction_384(data, threadData);
  ReheatControllerFMU_eqFunction_385(data, threadData);
  ReheatControllerFMU_eqFunction_1559(data, threadData);
  ReheatControllerFMU_eqFunction_387(data, threadData);
  ReheatControllerFMU_eqFunction_388(data, threadData);
  ReheatControllerFMU_eqFunction_389(data, threadData);
  ReheatControllerFMU_eqFunction_1586(data, threadData);
  ReheatControllerFMU_eqFunction_1588(data, threadData);
  ReheatControllerFMU_eqFunction_1587(data, threadData);
  ReheatControllerFMU_eqFunction_1556(data, threadData);
  ReheatControllerFMU_eqFunction_1589(data, threadData);
  ReheatControllerFMU_eqFunction_1590(data, threadData);
  ReheatControllerFMU_eqFunction_396(data, threadData);
  ReheatControllerFMU_eqFunction_397(data, threadData);
  ReheatControllerFMU_eqFunction_1209(data, threadData);
  ReheatControllerFMU_eqFunction_399(data, threadData);
  ReheatControllerFMU_eqFunction_400(data, threadData);
  ReheatControllerFMU_eqFunction_401(data, threadData);
  ReheatControllerFMU_eqFunction_1600(data, threadData);
  ReheatControllerFMU_eqFunction_1601(data, threadData);
  ReheatControllerFMU_eqFunction_404(data, threadData);
  ReheatControllerFMU_eqFunction_405(data, threadData);
  ReheatControllerFMU_eqFunction_1204(data, threadData);
  ReheatControllerFMU_eqFunction_407(data, threadData);
  ReheatControllerFMU_eqFunction_408(data, threadData);
  ReheatControllerFMU_eqFunction_409(data, threadData);
  ReheatControllerFMU_eqFunction_1611(data, threadData);
  ReheatControllerFMU_eqFunction_1612(data, threadData);
  ReheatControllerFMU_eqFunction_412(data, threadData);
  ReheatControllerFMU_eqFunction_413(data, threadData);
  ReheatControllerFMU_eqFunction_1700(data, threadData);
  ReheatControllerFMU_eqFunction_415(data, threadData);
  ReheatControllerFMU_eqFunction_416(data, threadData);
  ReheatControllerFMU_eqFunction_417(data, threadData);
  ReheatControllerFMU_eqFunction_1699(data, threadData);
  ReheatControllerFMU_eqFunction_419(data, threadData);
  ReheatControllerFMU_eqFunction_420(data, threadData);
  ReheatControllerFMU_eqFunction_1713(data, threadData);
  ReheatControllerFMU_eqFunction_422(data, threadData);
  ReheatControllerFMU_eqFunction_423(data, threadData);
  ReheatControllerFMU_eqFunction_424(data, threadData);
  ReheatControllerFMU_eqFunction_1712(data, threadData);
  ReheatControllerFMU_eqFunction_426(data, threadData);
  ReheatControllerFMU_eqFunction_427(data, threadData);
  ReheatControllerFMU_eqFunction_428(data, threadData);
  ReheatControllerFMU_eqFunction_429(data, threadData);
  ReheatControllerFMU_eqFunction_430(data, threadData);
  ReheatControllerFMU_eqFunction_431(data, threadData);
  ReheatControllerFMU_eqFunction_432(data, threadData);
  ReheatControllerFMU_eqFunction_433(data, threadData);
  ReheatControllerFMU_eqFunction_434(data, threadData);
  ReheatControllerFMU_eqFunction_435(data, threadData);
  ReheatControllerFMU_eqFunction_436(data, threadData);
  ReheatControllerFMU_eqFunction_437(data, threadData);
  ReheatControllerFMU_eqFunction_438(data, threadData);
  ReheatControllerFMU_eqFunction_439(data, threadData);
  ReheatControllerFMU_eqFunction_440(data, threadData);
  ReheatControllerFMU_eqFunction_441(data, threadData);
  ReheatControllerFMU_eqFunction_442(data, threadData);
  ReheatControllerFMU_eqFunction_443(data, threadData);
  ReheatControllerFMU_eqFunction_444(data, threadData);
  ReheatControllerFMU_eqFunction_445(data, threadData);
  ReheatControllerFMU_eqFunction_446(data, threadData);
  ReheatControllerFMU_eqFunction_447(data, threadData);
  ReheatControllerFMU_eqFunction_448(data, threadData);
  ReheatControllerFMU_eqFunction_449(data, threadData);
  ReheatControllerFMU_eqFunction_450(data, threadData);
  ReheatControllerFMU_eqFunction_451(data, threadData);
  ReheatControllerFMU_eqFunction_452(data, threadData);
  ReheatControllerFMU_eqFunction_453(data, threadData);
  ReheatControllerFMU_eqFunction_454(data, threadData);
  ReheatControllerFMU_eqFunction_455(data, threadData);
  ReheatControllerFMU_eqFunction_456(data, threadData);
  ReheatControllerFMU_eqFunction_457(data, threadData);
  ReheatControllerFMU_eqFunction_458(data, threadData);
  ReheatControllerFMU_eqFunction_459(data, threadData);
  ReheatControllerFMU_eqFunction_460(data, threadData);
  ReheatControllerFMU_eqFunction_461(data, threadData);
  ReheatControllerFMU_eqFunction_462(data, threadData);
  ReheatControllerFMU_eqFunction_463(data, threadData);
  ReheatControllerFMU_eqFunction_464(data, threadData);
  ReheatControllerFMU_eqFunction_465(data, threadData);
  ReheatControllerFMU_eqFunction_466(data, threadData);
  ReheatControllerFMU_eqFunction_467(data, threadData);
  ReheatControllerFMU_eqFunction_468(data, threadData);
  ReheatControllerFMU_eqFunction_469(data, threadData);
  ReheatControllerFMU_eqFunction_470(data, threadData);
  ReheatControllerFMU_eqFunction_471(data, threadData);
  ReheatControllerFMU_eqFunction_472(data, threadData);
  ReheatControllerFMU_eqFunction_473(data, threadData);
  ReheatControllerFMU_eqFunction_474(data, threadData);
  ReheatControllerFMU_eqFunction_475(data, threadData);
  ReheatControllerFMU_eqFunction_476(data, threadData);
  ReheatControllerFMU_eqFunction_477(data, threadData);
  ReheatControllerFMU_eqFunction_478(data, threadData);
  ReheatControllerFMU_eqFunction_479(data, threadData);
  ReheatControllerFMU_eqFunction_480(data, threadData);
  ReheatControllerFMU_eqFunction_481(data, threadData);
  ReheatControllerFMU_eqFunction_482(data, threadData);
  ReheatControllerFMU_eqFunction_483(data, threadData);
  ReheatControllerFMU_eqFunction_484(data, threadData);
  ReheatControllerFMU_eqFunction_485(data, threadData);
  ReheatControllerFMU_eqFunction_486(data, threadData);
  ReheatControllerFMU_eqFunction_487(data, threadData);
  ReheatControllerFMU_eqFunction_488(data, threadData);
  ReheatControllerFMU_eqFunction_489(data, threadData);
  ReheatControllerFMU_eqFunction_490(data, threadData);
  ReheatControllerFMU_eqFunction_491(data, threadData);
  ReheatControllerFMU_eqFunction_492(data, threadData);
  ReheatControllerFMU_eqFunction_493(data, threadData);
  ReheatControllerFMU_eqFunction_494(data, threadData);
  ReheatControllerFMU_eqFunction_495(data, threadData);
  ReheatControllerFMU_eqFunction_496(data, threadData);
  ReheatControllerFMU_eqFunction_497(data, threadData);
  ReheatControllerFMU_eqFunction_498(data, threadData);
  ReheatControllerFMU_eqFunction_499(data, threadData);
  ReheatControllerFMU_eqFunction_500(data, threadData);
  ReheatControllerFMU_eqFunction_501(data, threadData);
  ReheatControllerFMU_eqFunction_502(data, threadData);
  ReheatControllerFMU_eqFunction_503(data, threadData);
  ReheatControllerFMU_eqFunction_504(data, threadData);
  ReheatControllerFMU_eqFunction_505(data, threadData);
  ReheatControllerFMU_eqFunction_506(data, threadData);
  ReheatControllerFMU_eqFunction_507(data, threadData);
  ReheatControllerFMU_eqFunction_508(data, threadData);
  ReheatControllerFMU_eqFunction_509(data, threadData);
  ReheatControllerFMU_eqFunction_510(data, threadData);
  ReheatControllerFMU_eqFunction_511(data, threadData);
  ReheatControllerFMU_eqFunction_512(data, threadData);
  ReheatControllerFMU_eqFunction_513(data, threadData);
  ReheatControllerFMU_eqFunction_514(data, threadData);
  ReheatControllerFMU_eqFunction_515(data, threadData);
  ReheatControllerFMU_eqFunction_516(data, threadData);
  ReheatControllerFMU_eqFunction_517(data, threadData);
  ReheatControllerFMU_eqFunction_518(data, threadData);
  ReheatControllerFMU_eqFunction_519(data, threadData);
  ReheatControllerFMU_eqFunction_520(data, threadData);
  ReheatControllerFMU_eqFunction_521(data, threadData);
  ReheatControllerFMU_eqFunction_522(data, threadData);
  ReheatControllerFMU_eqFunction_523(data, threadData);
  ReheatControllerFMU_eqFunction_524(data, threadData);
  ReheatControllerFMU_eqFunction_525(data, threadData);
  ReheatControllerFMU_eqFunction_526(data, threadData);
  ReheatControllerFMU_eqFunction_527(data, threadData);
  ReheatControllerFMU_eqFunction_528(data, threadData);
  ReheatControllerFMU_eqFunction_529(data, threadData);
  ReheatControllerFMU_eqFunction_530(data, threadData);
  ReheatControllerFMU_eqFunction_531(data, threadData);
  ReheatControllerFMU_eqFunction_532(data, threadData);
  ReheatControllerFMU_eqFunction_533(data, threadData);
  ReheatControllerFMU_eqFunction_534(data, threadData);
  ReheatControllerFMU_eqFunction_535(data, threadData);
  ReheatControllerFMU_eqFunction_536(data, threadData);
  ReheatControllerFMU_eqFunction_537(data, threadData);
  ReheatControllerFMU_eqFunction_538(data, threadData);
  ReheatControllerFMU_eqFunction_539(data, threadData);
  ReheatControllerFMU_eqFunction_540(data, threadData);
  ReheatControllerFMU_eqFunction_541(data, threadData);
  ReheatControllerFMU_eqFunction_542(data, threadData);
  ReheatControllerFMU_eqFunction_543(data, threadData);
  ReheatControllerFMU_eqFunction_544(data, threadData);
  ReheatControllerFMU_eqFunction_545(data, threadData);
  ReheatControllerFMU_eqFunction_546(data, threadData);
  ReheatControllerFMU_eqFunction_1617(data, threadData);
  ReheatControllerFMU_eqFunction_548(data, threadData);
  ReheatControllerFMU_eqFunction_549(data, threadData);
  ReheatControllerFMU_eqFunction_550(data, threadData);
  ReheatControllerFMU_eqFunction_551(data, threadData);
  ReheatControllerFMU_eqFunction_552(data, threadData);
  ReheatControllerFMU_eqFunction_553(data, threadData);
  ReheatControllerFMU_eqFunction_554(data, threadData);
  ReheatControllerFMU_eqFunction_555(data, threadData);
  ReheatControllerFMU_eqFunction_556(data, threadData);
  ReheatControllerFMU_eqFunction_557(data, threadData);
  ReheatControllerFMU_eqFunction_558(data, threadData);
  ReheatControllerFMU_eqFunction_559(data, threadData);
  ReheatControllerFMU_eqFunction_560(data, threadData);
  ReheatControllerFMU_eqFunction_561(data, threadData);
  ReheatControllerFMU_eqFunction_1183(data, threadData);
  ReheatControllerFMU_eqFunction_1182(data, threadData);
  ReheatControllerFMU_eqFunction_564(data, threadData);
  ReheatControllerFMU_eqFunction_565(data, threadData);
  ReheatControllerFMU_eqFunction_566(data, threadData);
  ReheatControllerFMU_eqFunction_567(data, threadData);
  ReheatControllerFMU_eqFunction_568(data, threadData);
  ReheatControllerFMU_eqFunction_569(data, threadData);
  ReheatControllerFMU_eqFunction_570(data, threadData);
  ReheatControllerFMU_eqFunction_571(data, threadData);
  ReheatControllerFMU_eqFunction_572(data, threadData);
  ReheatControllerFMU_eqFunction_573(data, threadData);
  ReheatControllerFMU_eqFunction_574(data, threadData);
  ReheatControllerFMU_eqFunction_575(data, threadData);
  ReheatControllerFMU_eqFunction_576(data, threadData);
  ReheatControllerFMU_eqFunction_577(data, threadData);
  ReheatControllerFMU_eqFunction_578(data, threadData);
  ReheatControllerFMU_eqFunction_579(data, threadData);
  ReheatControllerFMU_eqFunction_580(data, threadData);
  ReheatControllerFMU_eqFunction_581(data, threadData);
  ReheatControllerFMU_eqFunction_582(data, threadData);
  ReheatControllerFMU_eqFunction_583(data, threadData);
  ReheatControllerFMU_eqFunction_584(data, threadData);
  ReheatControllerFMU_eqFunction_585(data, threadData);
  ReheatControllerFMU_eqFunction_586(data, threadData);
  ReheatControllerFMU_eqFunction_587(data, threadData);
  ReheatControllerFMU_eqFunction_593(data, threadData);
  ReheatControllerFMU_eqFunction_592(data, threadData);
  ReheatControllerFMU_eqFunction_591(data, threadData);
  ReheatControllerFMU_eqFunction_590(data, threadData);
  ReheatControllerFMU_eqFunction_589(data, threadData);
  ReheatControllerFMU_eqFunction_588(data, threadData);
  TRACE_POP
}
#if defined(__cplusplus)
}
#endif