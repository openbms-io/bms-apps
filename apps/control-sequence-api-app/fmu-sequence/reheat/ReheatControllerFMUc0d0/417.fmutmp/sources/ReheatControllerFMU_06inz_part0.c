#include "ReheatControllerFMU_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/*
equation index: 1
type: SIMPLE_ASSIGN
damVal.conDam.cheYMinMax.y = true
*/
void ReheatControllerFMU_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[140]] /* damVal.conDam.cheYMinMax.y DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
damVal.conVal.cheYMinMax.y = true
*/
void ReheatControllerFMU_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[141]] /* damVal.conVal.cheYMinMax.y DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
timSup.truDel.u = true
*/
void ReheatControllerFMU_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 4
type: SIMPLE_ASSIGN
damVal.max2.y = max(damVal.cooMax1.k, damVal.heaMax1.k)
*/
void ReheatControllerFMU_eqFunction_4(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,4};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[131]] /* damVal.max2.y variable */) = fmax((data->simulationInfo->realParameter[260] /* damVal.cooMax1.k PARAM */),(data->simulationInfo->realParameter[280] /* damVal.heaMax1.k PARAM */));
  TRACE_POP
}

/*
equation index: 5
type: SIMPLE_ASSIGN
setPoi.booToRea1.y = if setPoi.perOccSta.k then 0.0 else 1.0
*/
void ReheatControllerFMU_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[152]] /* setPoi.booToRea1.y variable */) = ((data->simulationInfo->booleanParameter[116] /* setPoi.perOccSta.k PARAM */)?0.0:1.0);
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
setPoi.unpMinZonFlo.y = 0.5 * setPoi.booToRea1.y
*/
void ReheatControllerFMU_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[170]] /* setPoi.unpMinZonFlo.y variable */) = (0.5) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[152]] /* setPoi.booToRea1.y variable */));
  TRACE_POP
}

/*
equation index: 7
type: SIMPLE_ASSIGN
setPoi.unPopAreBreAir.y = setPoi.desAreAir.k * setPoi.booToRea1.y
*/
void ReheatControllerFMU_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[167]] /* setPoi.unPopAreBreAir.y variable */) = ((data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[152]] /* setPoi.booToRea1.y variable */));
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.b = -0.5 + setPoi.zonCooMaxFlo.k
*/
void ReheatControllerFMU_eqFunction_8(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,8};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[159]] /* setPoi.occMinAirSet.b variable */) = -0.5 + (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 9
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.a = setPoi.zonCooMaxFlo.k - setPoi.occMinAirSet.b
*/
void ReheatControllerFMU_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[158]] /* setPoi.occMinAirSet.a variable */) = (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */) - (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[159]] /* setPoi.occMinAirSet.b variable */);
  TRACE_POP
}

/*
equation index: 10
type: SIMPLE_ASSIGN
ala.greThr2.y = ala.conInt3.k > ala.greThr2.greNoHys.t
*/
void ReheatControllerFMU_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  modelica_boolean tmp0;
  tmp0 = Greater((data->simulationInfo->realParameter[50] /* ala.conInt3.k PARAM */),(data->simulationInfo->realParameter[79] /* ala.greThr2.greNoHys.t PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[100]] /* ala.greThr2.y DISCRETE */) = tmp0;
  TRACE_POP
}

/*
equation index: 11
type: SIMPLE_ASSIGN
ala.booToInt5.y = if ala.greThr2.y then ala.booToInt5.integerTrue else ala.booToInt5.integerFalse
*/
void ReheatControllerFMU_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[8]] /* ala.booToInt5.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[100]] /* ala.greThr2.y DISCRETE */)?(data->simulationInfo->integerParameter[16] /* ala.booToInt5.integerTrue PARAM */):(data->simulationInfo->integerParameter[15] /* ala.booToInt5.integerFalse PARAM */));
  TRACE_POP
}

/*
equation index: 12
type: SIMPLE_ASSIGN
ala.gai2.y = 0.1 * ala.cooMaxFlo.k
*/
void ReheatControllerFMU_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) = (0.1) * ((data->simulationInfo->realParameter[52] /* ala.cooMaxFlo.k PARAM */));
  TRACE_POP
}

/*
equation index: 13
type: SIMPLE_ASSIGN
ala.greThr1.y = ala.conInt1.k > ala.greThr1.greNoHys.t
*/
void ReheatControllerFMU_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  modelica_boolean tmp1;
  tmp1 = Greater((data->simulationInfo->realParameter[48] /* ala.conInt1.k PARAM */),(data->simulationInfo->realParameter[74] /* ala.greThr1.greNoHys.t PARAM */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[99]] /* ala.greThr1.y DISCRETE */) = tmp1;
  TRACE_POP
}

/*
equation index: 14
type: SIMPLE_ASSIGN
ala.booToInt1.y = if ala.greThr1.y then ala.booToInt1.integerTrue else ala.booToInt1.integerFalse
*/
void ReheatControllerFMU_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[6]] /* ala.booToInt1.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[99]] /* ala.greThr1.y DISCRETE */)?(data->simulationInfo->integerParameter[8] /* ala.booToInt1.integerTrue PARAM */):(data->simulationInfo->integerParameter[7] /* ala.booToInt1.integerFalse PARAM */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1184(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1185(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1186(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1187(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1188(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1189(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1190(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1193(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1194(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1195(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1196(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1197(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1198(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1199(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1191(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1192(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1200(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1205(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1210(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1211(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1225(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1226(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1227(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1240(DATA *data, threadData_t *threadData);


/*
equation index: 39
type: SIMPLE_ASSIGN
conLoo.conCoo.addPD.y = conLoo.conCoo.P.k * conLoo.conCoo.P.u
*/
void ReheatControllerFMU_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[48]] /* conLoo.conCoo.addPD.y variable */) = ((data->simulationInfo->realParameter[122] /* conLoo.conCoo.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[47]] /* conLoo.conCoo.P.u variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1237(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1241(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1242(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1243(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1256(DATA *data, threadData_t *threadData);


/*
equation index: 45
type: SIMPLE_ASSIGN
conLoo.conHea.addPD.y = conLoo.conHea.P.k * conLoo.conHea.P.u
*/
void ReheatControllerFMU_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[61]] /* conLoo.conHea.addPD.y variable */) = ((data->simulationInfo->realParameter[146] /* conLoo.conHea.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[60]] /* conLoo.conHea.P.u variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1253(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1266(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1268(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1269(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1270(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1272(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1271(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1273(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1274(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1275(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1276(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1288(DATA *data, threadData_t *threadData);


/*
equation index: 58
type: SIMPLE_ASSIGN
setPoi.lin.xLim = min(ppmCO2Set, max(setPoi.addPar.y, ppmCO2))
*/
void ReheatControllerFMU_eqFunction_58(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,58};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[156]] /* setPoi.lin.xLim variable */) = fmin((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[143]] /* ppmCO2Set variable */),fmax((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[149]] /* setPoi.addPar.y variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[142]] /* ppmCO2 variable */)));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1291(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1292(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1293(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1294(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1295(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1296(DATA *data, threadData_t *threadData);


/*
equation index: 65
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.xLim = min(1.0, max(0.0, setPoi.co2Con.y))
*/
void ReheatControllerFMU_eqFunction_65(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,65};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[160]] /* setPoi.occMinAirSet.xLim variable */) = fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[153]] /* setPoi.co2Con.y variable */)));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1299(DATA *data, threadData_t *threadData);


/*
equation index: 67
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.xLim = min(1.0, max(0.0, setPoi.co2Con.y))
*/
void ReheatControllerFMU_eqFunction_67(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,67};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[164]] /* setPoi.popBreOutAir.xLim variable */) = fmin(1.0,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[153]] /* setPoi.co2Con.y variable */)));
  TRACE_POP
}

/*
equation index: 68
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.y = setPoi.desPopAir.k * setPoi.popBreOutAir.xLim
*/
void ReheatControllerFMU_eqFunction_68(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,68};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[165]] /* setPoi.popBreOutAir.y variable */) = ((data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[164]] /* setPoi.popBreOutAir.xLim variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1304(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1302(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1317(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1318(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1319(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1300(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1305(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1306(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1307(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1308(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1309(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1310(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1311(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1314(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1320(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1315(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1316(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1312(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1313(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1324(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1325(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1327(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1328(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1330(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1332(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1333(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1334(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1335(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1337(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1618(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1338(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1340(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1343(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1339(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1341(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1344(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1342(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1346(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1347(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1348(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1349(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1350(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1345(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1351(DATA *data, threadData_t *threadData);


/*
equation index: 113
type: SIMPLE_ASSIGN
timSup.truDel.y = if not timSup.truDel.delayTime > 0.0 then timSup.truDel.u else false
*/
void ReheatControllerFMU_eqFunction_113(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,113};
  modelica_boolean tmp2;
  tmp2 = Greater((data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[218]] /* timSup.truDel.y DISCRETE */) = ((!tmp2)?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[217]] /* timSup.truDel.u DISCRETE */):0 /* false */);
  TRACE_POP
}

/*
equation index: 114
type: SIMPLE_ASSIGN
timSup.samSet.y = TCooSet
*/
void ReheatControllerFMU_eqFunction_114(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,114};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[216]] /* timSup.samSet.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */);
  TRACE_POP
}

/*
equation index: 115
type: SIMPLE_ASSIGN
sysReq.sampler2.y = VDis_flow
*/
void ReheatControllerFMU_eqFunction_115(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,115};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1181(DATA *data, threadData_t *threadData);


/*
equation index: 117
type: SIMPLE_ASSIGN
ala.fanIni.y = if not (ala.fanIni.delayOnInit and ala.fanIni.delayTime > 0.0) then ala.fanIni.u else false
*/
void ReheatControllerFMU_eqFunction_117(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,117};
  modelica_boolean tmp3;
  tmp3 = Greater((data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[94]] /* ala.fanIni.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[6] /* ala.fanIni.delayOnInit PARAM */) && tmp3))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[93]] /* ala.fanIni.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1356(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1357(DATA *data, threadData_t *threadData);


/*
equation index: 120
type: SIMPLE_ASSIGN
$whenCondition21 = ala.fanIni.u
*/
void ReheatControllerFMU_eqFunction_120(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,120};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[13]] /* $whenCondition21 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[93]] /* ala.fanIni.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 121
type: SIMPLE_ASSIGN
$whenCondition20 = not ala.fanIni.u
*/
void ReheatControllerFMU_eqFunction_121(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,121};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[12]] /* $whenCondition20 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[93]] /* ala.fanIni.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 122
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.not_u = true
*/
void ReheatControllerFMU_eqFunction_122(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,122};
  (data->simulationInfo->booleanVarsPre[161] /* damVal.truFalHol1.not_u DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 123
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.u = false
*/
void ReheatControllerFMU_eqFunction_123(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,123};
  (data->simulationInfo->booleanVarsPre[163] /* damVal.truFalHol1.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 124
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.entryTimeFalse = -1e60
*/
void ReheatControllerFMU_eqFunction_124(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,124};
  (data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */) = -1e60;
  TRACE_POP
}

/*
equation index: 125
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol1.entryTimeTrue = -1e60
*/
void ReheatControllerFMU_eqFunction_125(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,125};
  (data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) = -1e60;
  TRACE_POP
}

/*
equation index: 126
type: SIMPLE_ASSIGN
$whenCondition3 = time >= $PRE.damVal.truFalHol1.entryTimeFalse and time >= $PRE.damVal.truFalHol1.entryTimeTrue + 600.0
*/
void ReheatControllerFMU_eqFunction_126(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,126};
  modelica_boolean tmp4;
  modelica_boolean tmp5;
  tmp4 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
  tmp5 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[22]] /* $whenCondition3 DISCRETE */) = (tmp4 && tmp5);
  TRACE_POP
}

/*
equation index: 127
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.not_u = true
*/
void ReheatControllerFMU_eqFunction_127(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,127};
  (data->simulationInfo->booleanVarsPre[157] /* damVal.truFalHol.not_u DISCRETE */) = 1 /* true */;
  TRACE_POP
}

/*
equation index: 128
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.u = false
*/
void ReheatControllerFMU_eqFunction_128(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,128};
  (data->simulationInfo->booleanVarsPre[159] /* damVal.truFalHol.u DISCRETE */) = 0 /* false */;
  TRACE_POP
}

/*
equation index: 129
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.entryTimeFalse = -1e60
*/
void ReheatControllerFMU_eqFunction_129(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,129};
  (data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */) = -1e60;
  TRACE_POP
}

/*
equation index: 130
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.entryTimeTrue = -1e60
*/
void ReheatControllerFMU_eqFunction_130(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,130};
  (data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) = -1e60;
  TRACE_POP
}

/*
equation index: 131
type: SIMPLE_ASSIGN
$whenCondition6 = time >= $PRE.damVal.truFalHol.entryTimeFalse and time >= $PRE.damVal.truFalHol.entryTimeTrue + 600.0
*/
void ReheatControllerFMU_eqFunction_131(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,131};
  modelica_boolean tmp6;
  modelica_boolean tmp7;
  tmp6 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
  tmp7 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[55]] /* $whenCondition6 DISCRETE */) = (tmp6 && tmp7);
  TRACE_POP
}

/*
equation index: 132
type: SIMPLE_ASSIGN
$PRE.damVal.greThr2.greHys.y = damVal.greThr2.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_132(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,132};
  (data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[85] /* damVal.greThr2.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 133
type: SIMPLE_ASSIGN
$PRE.damVal.lowMin.lesHys.y = damVal.lowMin.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_133(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,133};
  (data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[93] /* damVal.lowMin.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 134
type: SIMPLE_ASSIGN
damVal.lowMin.lesHys.y = not $PRE.damVal.lowMin.lesHys.y and TDis < damVal.lowMin.lesHys.t or $PRE.damVal.lowMin.lesHys.y and TDis < damVal.lowMin.lesHys.t + 0.25
*/
void ReheatControllerFMU_eqFunction_134(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,134};
  modelica_boolean tmp8;
  modelica_boolean tmp9;
  tmp8 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */));
  tmp9 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[152]] /* damVal.lowMin.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */)) && tmp8) || ((data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */) && tmp9));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1336(DATA *data, threadData_t *threadData);


/*
equation index: 136
type: SIMPLE_ASSIGN
$PRE.damVal.greThr.greHys.y = damVal.greThr.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_136(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,136};
  (data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[79] /* damVal.greThr.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 137
type: SIMPLE_ASSIGN
damVal.greThr.greHys.y = not $PRE.damVal.greThr.greHys.y and damVal.sub2.y > 0.25 or $PRE.damVal.greThr.greHys.y and damVal.sub2.y > 0.125
*/
void ReheatControllerFMU_eqFunction_137(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,137};
  modelica_boolean tmp10;
  modelica_boolean tmp11;
  tmp10 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */),0.25);
  tmp11 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */),0.125);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[147]] /* damVal.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */)) && tmp10) || ((data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */) && tmp11));
  TRACE_POP
}

/*
equation index: 138
type: SIMPLE_ASSIGN
$PRE.damVal.greThr1.greHys.y = damVal.greThr1.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_138(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,138};
  (data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[82] /* damVal.greThr1.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 139
type: SIMPLE_ASSIGN
damVal.conVal.I.y = damVal.conVal.I.y_start
*/
void ReheatControllerFMU_eqFunction_139(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,139};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[3]] /* damVal.conVal.I.y STATE(1) */) = (data->simulationInfo->realParameter[233] /* damVal.conVal.I.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 140
type: SIMPLE_ASSIGN
$PRE.damVal.gre.greHys.y = damVal.gre.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_140(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,140};
  (data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[76] /* damVal.gre.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 141
type: SIMPLE_ASSIGN
damVal.gre.greHys.y = not $PRE.damVal.gre.greHys.y and TDis > damVal.addPar1.y or $PRE.damVal.gre.greHys.y and TDis > damVal.addPar1.y - 0.25
*/
void ReheatControllerFMU_eqFunction_141(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,141};
  modelica_boolean tmp12;
  modelica_boolean tmp13;
  tmp12 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */));
  tmp13 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) - 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[146]] /* damVal.gre.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */)) && tmp12) || ((data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */) && tmp13));
  TRACE_POP
}

/*
equation index: 142
type: SIMPLE_ASSIGN
damVal.conDam.I.y = damVal.conDam.I.y_start
*/
void ReheatControllerFMU_eqFunction_142(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,142};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[2]] /* damVal.conDam.I.y STATE(1) */) = (data->simulationInfo->realParameter[205] /* damVal.conDam.I.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 143
type: SIMPLE_ASSIGN
$PRE.setPoi.cooSup.greHys.y = setPoi.cooSup.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_143(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,143};
  (data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[103] /* setPoi.cooSup.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 144
type: SIMPLE_ASSIGN
setPoi.cooSup.greHys.y = not $PRE.setPoi.cooSup.greHys.y and TZon > TDis or $PRE.setPoi.cooSup.greHys.y and TZon > TDis - 0.25
*/
void ReheatControllerFMU_eqFunction_144(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,144};
  modelica_boolean tmp14;
  modelica_boolean tmp15;
  tmp14 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */));
  tmp15 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) - 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[168]] /* setPoi.cooSup.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */)) && tmp14) || ((data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */) && tmp15));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1322(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1323(DATA *data, threadData_t *threadData);


/*
equation index: 147
type: SIMPLE_ASSIGN
timSup.triSam1.y = timSup.triSam1.y_start
*/
void ReheatControllerFMU_eqFunction_147(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,147};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[219]] /* timSup.triSam1.y DISCRETE */) = (data->simulationInfo->realParameter[455] /* timSup.triSam1.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 148
type: SIMPLE_ASSIGN
$PRE.timSup.triSam1.y = timSup.triSam1.y
*/
void ReheatControllerFMU_eqFunction_148(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,148};
  (data->simulationInfo->realVarsPre[219] /* timSup.triSam1.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[219]] /* timSup.triSam1.y DISCRETE */);
  TRACE_POP
}

/*
equation index: 149
type: SIMPLE_ASSIGN
$PRE.timSup.pre1.u = timSup.pre1.pre_u_start
*/
void ReheatControllerFMU_eqFunction_149(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,149};
  (data->simulationInfo->booleanVarsPre[212] /* timSup.pre1.u DISCRETE */) = (data->simulationInfo->booleanParameter[167] /* timSup.pre1.pre_u_start PARAM */);
  TRACE_POP
}

/*
equation index: 150
type: SIMPLE_ASSIGN
timSup.pre1.y = $PRE.timSup.pre1.u
*/
void ReheatControllerFMU_eqFunction_150(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,150};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[213]] /* timSup.pre1.y DISCRETE */) = (data->simulationInfo->booleanVarsPre[212] /* timSup.pre1.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 151
type: SIMPLE_ASSIGN
$whenCondition15 = timSup.pre1.y
*/
void ReheatControllerFMU_eqFunction_151(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,151};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[6]] /* $whenCondition15 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[213]] /* timSup.pre1.y DISCRETE */);
  TRACE_POP
}

/*
equation index: 152
type: SIMPLE_ASSIGN
$PRE.timSup.greThr.greHys.y = timSup.greThr.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_152(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,152};
  (data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[162] /* timSup.greThr.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 153
type: SIMPLE_ASSIGN
$PRE.timSup.tim.entryTime = time
*/
void ReheatControllerFMU_eqFunction_153(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,153};
  (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */) = data->localData[0]->timeValue;
  TRACE_POP
}

/*
equation index: 154
type: SIMPLE_ASSIGN
timSup.tim.entryTime = $PRE.timSup.tim.entryTime
*/
void ReheatControllerFMU_eqFunction_154(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,154};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[217]] /* timSup.tim.entryTime DISCRETE */) = (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */);
  TRACE_POP
}

/*
equation index: 155
type: SIMPLE_ASSIGN
$PRE.timSup.edg.u = timSup.edg.pre_u_start
*/
void ReheatControllerFMU_eqFunction_155(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,155};
  (data->simulationInfo->booleanVarsPre[207] /* timSup.edg.u DISCRETE */) = (data->simulationInfo->booleanParameter[161] /* timSup.edg.pre_u_start PARAM */);
  TRACE_POP
}

/*
equation index: 156
type: SIMPLE_ASSIGN
timSup.triSam.y = timSup.triSam.y_start
*/
void ReheatControllerFMU_eqFunction_156(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,156};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[218]] /* timSup.triSam.y DISCRETE */) = (data->simulationInfo->realParameter[454] /* timSup.triSam.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 157
type: SIMPLE_ASSIGN
$PRE.timSup.triSam.y = timSup.triSam.y
*/
void ReheatControllerFMU_eqFunction_157(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,157};
  (data->simulationInfo->realVarsPre[218] /* timSup.triSam.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[218]] /* timSup.triSam.y DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1377(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1378(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1379(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1380(DATA *data, threadData_t *threadData);


/*
equation index: 162
type: SIMPLE_ASSIGN
timSup.uniDel.y = timSup.uniDel.y_start
*/
void ReheatControllerFMU_eqFunction_162(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,162};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[222]] /* timSup.uniDel.y DISCRETE */) = (data->simulationInfo->realParameter[460] /* timSup.uniDel.y_start PARAM */);
  TRACE_POP
}

/*
equation index: 163
type: SIMPLE_ASSIGN
$PRE.timSup.uniDel.y = timSup.uniDel.y
*/
void ReheatControllerFMU_eqFunction_163(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,163};
  (data->simulationInfo->realVarsPre[222] /* timSup.uniDel.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[222]] /* timSup.uniDel.y DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1283(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1367(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1368(DATA *data, threadData_t *threadData);


/*
equation index: 167
type: SIMPLE_ASSIGN
timSup.greThr.greHys.y = not $PRE.timSup.greThr.greHys.y and timSup.abs1.y > 0.25 or $PRE.timSup.greThr.greHys.y and timSup.abs1.y > 0.125
*/
void ReheatControllerFMU_eqFunction_167(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,167};
  modelica_boolean tmp16;
  modelica_boolean tmp17;
  tmp16 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */),0.25);
  tmp17 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */),0.125);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */)) && tmp16) || ((data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */) && tmp17));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1370(DATA *data, threadData_t *threadData);


/*
equation index: 169
type: SIMPLE_ASSIGN
timSup.lat.y = not timSup.pre1.y and timSup.greThr.greHys.y
*/
void ReheatControllerFMU_eqFunction_169(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,169};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[213]] /* timSup.pre1.y DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[209]] /* timSup.greThr.greHys.y DISCRETE */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1384(DATA *data, threadData_t *threadData);


/*
equation index: 171
type: SIMPLE_ASSIGN
$whenCondition12 = timSup.lat.y and time >= timSup.tim.t + $PRE.timSup.tim.entryTime
*/
void ReheatControllerFMU_eqFunction_171(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,171};
  modelica_boolean tmp18;
  tmp18 = GreaterEq(data->localData[0]->timeValue,(data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) + (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */));
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[3]] /* $whenCondition12 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) && tmp18);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1382(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1373(DATA *data, threadData_t *threadData);


/*
equation index: 174
type: SIMPLE_ASSIGN
timSup.edg.y = timSup.edg.u and not $PRE.timSup.edg.u
*/
void ReheatControllerFMU_eqFunction_174(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,174};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[208]] /* timSup.edg.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[207]] /* timSup.edg.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[207] /* timSup.edg.u DISCRETE */)));
  TRACE_POP
}

/*
equation index: 175
type: SIMPLE_ASSIGN
$whenCondition10 = timSup.edg.y
*/
void ReheatControllerFMU_eqFunction_175(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,175};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[1]] /* $whenCondition10 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[208]] /* timSup.edg.y DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1391(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1392(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1393(DATA *data, threadData_t *threadData);


/*
equation index: 179
type: SIMPLE_ASSIGN
timSup.lat1.y = not timSup.edg.y and timSup.pre1.u
*/
void ReheatControllerFMU_eqFunction_179(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,179};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[211]] /* timSup.lat1.y DISCRETE */) = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[208]] /* timSup.edg.y DISCRETE */)) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[212]] /* timSup.pre1.u DISCRETE */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1396(DATA *data, threadData_t *threadData);


/*
equation index: 181
type: SIMPLE_ASSIGN
$PRE.ala.gre2.greHys.y = ala.gre2.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_181(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,181};
  (data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[13] /* ala.gre2.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 182
type: SIMPLE_ASSIGN
ala.gre2.greHys.y = not $PRE.ala.gre2.greHys.y and TDis > ala.addPar2.y or $PRE.ala.gre2.greHys.y and TDis > ala.addPar2.y - 0.25
*/
void ReheatControllerFMU_eqFunction_182(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,182};
  modelica_boolean tmp19;
  modelica_boolean tmp20;
  tmp19 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */));
  tmp20 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) - 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[97]] /* ala.gre2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */)) && tmp19) || ((data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */) && tmp20));
  TRACE_POP
}

/*
equation index: 183
type: SIMPLE_ASSIGN
$PRE.ala.cloVal.lesHys.y = ala.cloVal.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_183(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,183};
  (data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[4] /* ala.cloVal.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 184
type: SIMPLE_ASSIGN
$PRE.ala.les2.lesHys.y = ala.les2.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_184(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,184};
  (data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[30] /* ala.les2.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 185
type: SIMPLE_ASSIGN
$PRE.ala.les1.lesHys.y = ala.les1.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_185(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,185};
  (data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[27] /* ala.les1.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 186
type: SIMPLE_ASSIGN
$PRE.ala.cloDam.lesHys.y = ala.cloDam.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_186(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,186};
  (data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[1] /* ala.cloDam.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 187
type: SIMPLE_ASSIGN
$PRE.ala.gre1.greHys.y = ala.gre1.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_187(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,187};
  (data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[10] /* ala.gre1.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 188
type: SIMPLE_ASSIGN
ala.gre1.greHys.y = not $PRE.ala.gre1.greHys.y and VDis_flow > ala.gai2.y or $PRE.ala.gre1.greHys.y and VDis_flow > ala.gai2.y - 0.005
*/
void ReheatControllerFMU_eqFunction_188(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,188};
  modelica_boolean tmp21;
  modelica_boolean tmp22;
  tmp21 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */));
  tmp22 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) - 0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[96]] /* ala.gre1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */)) && tmp21) || ((data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */) && tmp22));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1265(DATA *data, threadData_t *threadData);


/*
equation index: 190
type: SIMPLE_ASSIGN
ala.truDel2.u = ala.gre1.greHys.y and not u1Fan
*/
void ReheatControllerFMU_eqFunction_190(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,190};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[115]] /* ala.truDel2.u DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[96]] /* ala.gre1.greHys.y DISCRETE */) && (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */)));
  TRACE_POP
}

/*
equation index: 191
type: SIMPLE_ASSIGN
$whenCondition38 = not ala.truDel2.u
*/
void ReheatControllerFMU_eqFunction_191(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,191};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[31]] /* $whenCondition38 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[115]] /* ala.truDel2.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 192
type: SIMPLE_ASSIGN
$whenCondition39 = ala.truDel2.u
*/
void ReheatControllerFMU_eqFunction_192(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,192};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[32]] /* $whenCondition39 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[115]] /* ala.truDel2.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 193
type: SIMPLE_ASSIGN
ala.truDel2.y = if not (ala.truDel2.delayOnInit and ala.truDel2.delayTime > 0.0) then ala.truDel2.u else false
*/
void ReheatControllerFMU_eqFunction_193(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,193};
  modelica_boolean tmp23;
  tmp23 = Greater((data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[116]] /* ala.truDel2.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[34] /* ala.truDel2.delayOnInit PARAM */) && tmp23))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[115]] /* ala.truDel2.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1416(DATA *data, threadData_t *threadData);


/*
equation index: 195
type: SIMPLE_ASSIGN
$PRE.ala.gre.greHys.y = ala.gre.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_195(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,195};
  (data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[7] /* ala.gre.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 196
type: SIMPLE_ASSIGN
$PRE.ala.greThr.greHys.y = ala.greThr.greHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_196(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,196};
  (data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[16] /* ala.greThr.greHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 197
type: SIMPLE_ASSIGN
$PRE.ala.les.lesHys.y = ala.les.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_197(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,197};
  (data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[24] /* ala.les.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 198
type: SIMPLE_ASSIGN
$PRE.conLoo.zerCon1.lesHys.y = conLoo.zerCon1.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_198(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,198};
  (data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[64] /* conLoo.zerCon1.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 199
type: SIMPLE_ASSIGN
$PRE.conLoo.zerCon.lesHys.y = conLoo.zerCon.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_199(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,199};
  (data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[61] /* conLoo.zerCon.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 200
type: SIMPLE_ASSIGN
$PRE.conLoo.enaCooLoo.lesHys.y = conLoo.enaCooLoo.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_200(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,200};
  (data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[55] /* conLoo.enaCooLoo.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 201
type: SIMPLE_ASSIGN
conLoo.enaCooLoo.lesHys.y = not $PRE.conLoo.enaCooLoo.lesHys.y and TCooSet < TZon or $PRE.conLoo.enaCooLoo.lesHys.y and TCooSet < TZon + 0.25
*/
void ReheatControllerFMU_eqFunction_201(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,201};
  modelica_boolean tmp24;
  modelica_boolean tmp25;
  tmp24 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */));
  tmp25 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[133]] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */)) && tmp24) || ((data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) && tmp25));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1260(DATA *data, threadData_t *threadData);


/*
equation index: 203
type: SIMPLE_ASSIGN
$PRE.conLoo.enaHeaLoo.lesHys.y = conLoo.enaHeaLoo.lesHys.pre_y_start
*/
void ReheatControllerFMU_eqFunction_203(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,203};
  (data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) = (data->simulationInfo->booleanParameter[58] /* conLoo.enaHeaLoo.lesHys.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 204
type: SIMPLE_ASSIGN
conLoo.enaHeaLoo.lesHys.y = not $PRE.conLoo.enaHeaLoo.lesHys.y and TZon < THeaSet or $PRE.conLoo.enaHeaLoo.lesHys.y and TZon < THeaSet + 0.25
*/
void ReheatControllerFMU_eqFunction_204(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,204};
  modelica_boolean tmp26;
  modelica_boolean tmp27;
  tmp26 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */));
  tmp27 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[134]] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */)) && tmp26) || ((data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) && tmp27));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1258(DATA *data, threadData_t *threadData);


/*
equation index: 206
type: SIMPLE_ASSIGN
conLoo.conHea.I.y = conLoo.conHea.I.y_start
*/
void ReheatControllerFMU_eqFunction_206(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,206};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[1]] /* conLoo.conHea.I.y STATE(1) */) = (data->simulationInfo->realParameter[143] /* conLoo.conHea.I.y_start PARAM */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1245(DATA *data, threadData_t *threadData);


/*
equation index: 208
type: SIMPLE_ASSIGN
conLoo.conHea.y = homotopy(smooth(0, if noEvent(conLoo.conHea.addPID.y > conLoo.conHea.lim.uMax) then conLoo.conHea.lim.uMax else if noEvent(conLoo.conHea.addPID.y < conLoo.conHea.lim.uMin) then conLoo.conHea.lim.uMin else conLoo.conHea.addPID.y), conLoo.conHea.addPID.y)
*/
void ReheatControllerFMU_eqFunction_208(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,208};
  modelica_boolean tmp28;
  modelica_boolean tmp29;
  modelica_boolean tmp30;
  modelica_real tmp31;
  tmp28 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */),(data->simulationInfo->realParameter[152] /* conLoo.conHea.lim.uMax PARAM */));
  tmp30 = (modelica_boolean)tmp28;
  if(tmp30)
  {
    tmp31 = (data->simulationInfo->realParameter[152] /* conLoo.conHea.lim.uMax PARAM */);
  }
  else
  {
    tmp29 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */),(data->simulationInfo->realParameter[153] /* conLoo.conHea.lim.uMin PARAM */));
    tmp31 = (tmp29?(data->simulationInfo->realParameter[153] /* conLoo.conHea.lim.uMin PARAM */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */) = homotopy(tmp31, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */));
  TRACE_POP
}

/*
equation index: 209
type: SIMPLE_ASSIGN
conLoo.zerCon1.lesHys.y = not $PRE.conLoo.zerCon1.lesHys.y and conLoo.conHea.y < 0.01 or $PRE.conLoo.zerCon1.lesHys.y and conLoo.conHea.y < 0.018000000000000002
*/
void ReheatControllerFMU_eqFunction_209(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,209};
  modelica_boolean tmp32;
  modelica_boolean tmp33;
  tmp32 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */),0.01);
  tmp33 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */),0.018000000000000002);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[136]] /* conLoo.zerCon1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */)) && tmp32) || ((data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */) && tmp33));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1250(DATA *data, threadData_t *threadData);


/*
equation index: 211
type: SIMPLE_ASSIGN
$whenCondition47 = not conLoo.disHea.u
*/
void ReheatControllerFMU_eqFunction_211(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,211};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[41]] /* $whenCondition47 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[130]] /* conLoo.disHea.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 212
type: SIMPLE_ASSIGN
$whenCondition48 = conLoo.disHea.u
*/
void ReheatControllerFMU_eqFunction_212(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,212};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[42]] /* $whenCondition48 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[130]] /* conLoo.disHea.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 213
type: SIMPLE_ASSIGN
conLoo.disHea.y = if not (conLoo.disHea.delayOnInit and conLoo.disHea.delayTime > 0.0) then conLoo.disHea.u else false
*/
void ReheatControllerFMU_eqFunction_213(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,213};
  modelica_boolean tmp34;
  tmp34 = Greater((data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[131]] /* conLoo.disHea.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[53] /* conLoo.disHea.delayOnInit PARAM */) && tmp34))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[130]] /* conLoo.disHea.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1428(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1429(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1430(DATA *data, threadData_t *threadData);


/*
equation index: 217
type: SIMPLE_ASSIGN
damVal.greThr2.greHys.y = not $PRE.damVal.greThr2.greHys.y and conLoo.yHea > 0.01 or $PRE.damVal.greThr2.greHys.y and conLoo.yHea > 0.002
*/
void ReheatControllerFMU_eqFunction_217(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,217};
  modelica_boolean tmp35;
  modelica_boolean tmp36;
  tmp35 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */),0.01);
  tmp36 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */),0.002);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[149]] /* damVal.greThr2.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */)) && tmp35) || ((data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */) && tmp36));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1432(DATA *data, threadData_t *threadData);


/*
equation index: 219
type: SIMPLE_ASSIGN
$whenCondition5 = damVal.truFalHol.not_u and not $PRE.damVal.truFalHol.not_u
*/
void ReheatControllerFMU_eqFunction_219(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,219};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[44]] /* $whenCondition5 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[157]] /* damVal.truFalHol.not_u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[157] /* damVal.truFalHol.not_u DISCRETE */)));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1433(DATA *data, threadData_t *threadData);


/*
equation index: 221
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.y = damVal.truFalHol.u
*/
void ReheatControllerFMU_eqFunction_221(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,221};
  (data->simulationInfo->booleanVarsPre[160] /* damVal.truFalHol.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 222
type: SIMPLE_ASSIGN
$PRE.damVal.truFalHol.not_y = not damVal.truFalHol.u
*/
void ReheatControllerFMU_eqFunction_222(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,222};
  (data->simulationInfo->booleanVarsPre[158] /* damVal.truFalHol.not_y DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 223
type: SIMPLE_ASSIGN
$whenCondition4 = damVal.truFalHol.u and not $PRE.damVal.truFalHol.u
*/
void ReheatControllerFMU_eqFunction_223(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,223};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[33]] /* $whenCondition4 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[159] /* damVal.truFalHol.u DISCRETE */)));
  TRACE_POP
}

/*
equation index: 224
type: SIMPLE_ASSIGN
damVal.truFalHol.y = damVal.truFalHol.u
*/
void ReheatControllerFMU_eqFunction_224(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,224};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[159]] /* damVal.truFalHol.u DISCRETE */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1438(DATA *data, threadData_t *threadData);


/*
equation index: 226
type: SIMPLE_ASSIGN
damVal.truFalHol.entryTimeFalse = if damVal.truFalHol.not_y then time else $PRE.damVal.truFalHol.entryTimeFalse
*/
void ReheatControllerFMU_eqFunction_226(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,226};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[203]] /* damVal.truFalHol.entryTimeFalse DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
  TRACE_POP
}

/*
equation index: 227
type: SIMPLE_ASSIGN
damVal.or2.y = damVal.and1.y or not damVal.truFalHol.not_y
*/
void ReheatControllerFMU_eqFunction_227(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,227};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[154]] /* damVal.or2.y DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[137]] /* damVal.and1.y DISCRETE */) || (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[158]] /* damVal.truFalHol.not_y DISCRETE */)));
  TRACE_POP
}

/*
equation index: 228
type: SIMPLE_ASSIGN
$whenCondition74 = damVal.or2.y
*/
void ReheatControllerFMU_eqFunction_228(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,228};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[71]] /* $whenCondition74 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[154]] /* damVal.or2.y DISCRETE */);
  TRACE_POP
}

/*
equation index: 229
type: SIMPLE_ASSIGN
damVal.truFalHol.entryTimeTrue = if damVal.truFalHol.y then time else $PRE.damVal.truFalHol.entryTimeTrue
*/
void ReheatControllerFMU_eqFunction_229(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,229};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[204]] /* damVal.truFalHol.entryTimeTrue DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[160]] /* damVal.truFalHol.y DISCRETE */)?data->localData[0]->timeValue:(data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */));
  TRACE_POP
}

/*
equation index: 230
type: SIMPLE_ASSIGN
damVal.conTDisHeaSet.xLim = min(0.5, max(0.0, conLoo.yHea))
*/
void ReheatControllerFMU_eqFunction_230(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,230};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[102]] /* damVal.conTDisHeaSet.xLim variable */) = fmin(0.5,fmax(0.0,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */)));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1447(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1619(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1656(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1657(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1687(DATA *data, threadData_t *threadData);


/*
equation index: 236
type: SIMPLE_ASSIGN
damVal.conVal.addPD.y = damVal.conVal.P.k * damVal.conVal.P.u
*/
void ReheatControllerFMU_eqFunction_236(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,236};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[107]] /* damVal.conVal.addPD.y variable */) = ((data->simulationInfo->realParameter[236] /* damVal.conVal.P.k PARAM */)) * ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[106]] /* damVal.conVal.P.u variable */));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1684(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1659(DATA *data, threadData_t *threadData);


/*
equation index: 239
type: SIMPLE_ASSIGN
damVal.conVal.y = homotopy(smooth(0, if noEvent(damVal.conVal.addPID.y > 1.0) then 1.0 else if noEvent(damVal.conVal.addPID.y < 0.0) then 0.0 else damVal.conVal.addPID.y), damVal.conVal.addPID.y)
*/
void ReheatControllerFMU_eqFunction_239(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,239};
  modelica_boolean tmp37;
  modelica_boolean tmp38;
  modelica_boolean tmp39;
  modelica_real tmp40;
  tmp37 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */),1.0);
  tmp39 = (modelica_boolean)tmp37;
  if(tmp39)
  {
    tmp40 = 1.0;
  }
  else
  {
    tmp38 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */),0.0);
    tmp40 = (tmp38?0.0:(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */) = homotopy(tmp40, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */));
  TRACE_POP
}

/*
equation index: 240
type: SIMPLE_ASSIGN
damVal.swi4.y = smooth(0, if damVal.or2.y then damVal.conVal.y else 0.0)
*/
void ReheatControllerFMU_eqFunction_240(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,240};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[137]] /* damVal.swi4.y variable */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[154]] /* damVal.or2.y DISCRETE */)?(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */):0.0);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1662(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1663(DATA *data, threadData_t *threadData);


/*
equation index: 243
type: SIMPLE_ASSIGN
ala.cloVal.lesHys.y = not $PRE.ala.cloVal.lesHys.y and yVal < 0.005 or $PRE.ala.cloVal.lesHys.y and yVal < 0.0075
*/
void ReheatControllerFMU_eqFunction_243(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,243};
  modelica_boolean tmp41;
  modelica_boolean tmp42;
  tmp41 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.005);
  tmp42 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.0075);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[91]] /* ala.cloVal.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */)) && tmp41) || ((data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */) && tmp42));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1665(DATA *data, threadData_t *threadData);


/*
equation index: 245
type: SIMPLE_ASSIGN
ala.truDel6.u = ala.leaValAla.y and ala.gre2.greHys.y
*/
void ReheatControllerFMU_eqFunction_245(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,245};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[123]] /* ala.truDel6.u DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[103]] /* ala.leaValAla.y DISCRETE */) && (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[97]] /* ala.gre2.greHys.y DISCRETE */));
  TRACE_POP
}

/*
equation index: 246
type: SIMPLE_ASSIGN
$whenCondition26 = not ala.truDel6.u
*/
void ReheatControllerFMU_eqFunction_246(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,246};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[18]] /* $whenCondition26 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[123]] /* ala.truDel6.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 247
type: SIMPLE_ASSIGN
$whenCondition27 = ala.truDel6.u
*/
void ReheatControllerFMU_eqFunction_247(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,247};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[19]] /* $whenCondition27 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[123]] /* ala.truDel6.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 248
type: SIMPLE_ASSIGN
ala.truDel6.y = if not (ala.truDel6.delayOnInit and ala.truDel6.delayTime > 0.0) then ala.truDel6.u else false
*/
void ReheatControllerFMU_eqFunction_248(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,248};
  modelica_boolean tmp43;
  tmp43 = Greater((data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[124]] /* ala.truDel6.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[38] /* ala.truDel6.delayOnInit PARAM */) && tmp43))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[123]] /* ala.truDel6.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1672(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1682(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1683(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1685(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1686(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1655(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1636(DATA *data, threadData_t *threadData);


/*
equation index: 256
type: SIMPLE_ASSIGN
ala.les2.lesHys.y = not $PRE.ala.les2.lesHys.y and TDis < ala.addPar1.y or $PRE.ala.les2.lesHys.y and TDis < ala.addPar1.y + 0.25
*/
void ReheatControllerFMU_eqFunction_256(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,256};
  modelica_boolean tmp44;
  modelica_boolean tmp45;
  tmp44 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */));
  tmp45 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[106]] /* ala.les2.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */)) && tmp44) || ((data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */) && tmp45));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1654(DATA *data, threadData_t *threadData);


/*
equation index: 258
type: SIMPLE_ASSIGN
$whenCondition29 = not ala.truDel5.u
*/
void ReheatControllerFMU_eqFunction_258(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,258};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[21]] /* $whenCondition29 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[121]] /* ala.truDel5.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 259
type: SIMPLE_ASSIGN
$whenCondition30 = ala.truDel5.u
*/
void ReheatControllerFMU_eqFunction_259(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,259};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[23]] /* $whenCondition30 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[121]] /* ala.truDel5.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 260
type: SIMPLE_ASSIGN
ala.truDel5.y = if not (ala.truDel5.delayOnInit and ala.truDel5.delayTime > 0.0) then ala.truDel5.u else false
*/
void ReheatControllerFMU_eqFunction_260(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,260};
  modelica_boolean tmp46;
  tmp46 = Greater((data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[122]] /* ala.truDel5.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[37] /* ala.truDel5.delayOnInit PARAM */) && tmp46))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[121]] /* ala.truDel5.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1648(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1649(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1650(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1651(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1620(DATA *data, threadData_t *threadData);


/*
equation index: 266
type: SIMPLE_ASSIGN
ala.les1.lesHys.y = not $PRE.ala.les1.lesHys.y and TDis < ala.addPar.y or $PRE.ala.les1.lesHys.y and TDis < ala.addPar.y + 0.25
*/
void ReheatControllerFMU_eqFunction_266(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,266};
  modelica_boolean tmp47;
  modelica_boolean tmp48;
  tmp47 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */));
  tmp48 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */),(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) + 0.25);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[105]] /* ala.les1.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */)) && tmp47) || ((data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */) && tmp48));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1635(DATA *data, threadData_t *threadData);


/*
equation index: 268
type: SIMPLE_ASSIGN
$whenCondition32 = not ala.truDel4.u
*/
void ReheatControllerFMU_eqFunction_268(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,268};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[25]] /* $whenCondition32 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[119]] /* ala.truDel4.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 269
type: SIMPLE_ASSIGN
$whenCondition33 = ala.truDel4.u
*/
void ReheatControllerFMU_eqFunction_269(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,269};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[26]] /* $whenCondition33 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[119]] /* ala.truDel4.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 270
type: SIMPLE_ASSIGN
ala.truDel4.y = if not (ala.truDel4.delayOnInit and ala.truDel4.delayTime > 0.0) then ala.truDel4.u else false
*/
void ReheatControllerFMU_eqFunction_270(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,270};
  modelica_boolean tmp49;
  tmp49 = Greater((data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[120]] /* ala.truDel4.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[36] /* ala.truDel4.delayOnInit PARAM */) && tmp49))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[119]] /* ala.truDel4.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1632(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1633(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1634(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1652(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1653(DATA *data, threadData_t *threadData);


/*
equation index: 276
type: SIMPLE_ASSIGN
damVal.lin3.xLim = min(1.0, max(0.5, conLoo.yHea))
*/
void ReheatControllerFMU_eqFunction_276(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,276};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[128]] /* damVal.lin3.xLim variable */) = fmin(1.0,fmax(0.5,(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */)));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1450(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1451(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1251(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1252(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1254(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1255(DATA *data, threadData_t *threadData);


/*
equation index: 283
type: SIMPLE_ASSIGN
conLoo.conCoo.I.y = conLoo.conCoo.I.y_start
*/
void ReheatControllerFMU_eqFunction_283(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,283};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[0]] /* conLoo.conCoo.I.y STATE(1) */) = (data->simulationInfo->realParameter[119] /* conLoo.conCoo.I.y_start PARAM */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1229(DATA *data, threadData_t *threadData);


/*
equation index: 285
type: SIMPLE_ASSIGN
conLoo.conCoo.y = homotopy(smooth(0, if noEvent(conLoo.conCoo.addPID.y > conLoo.conCoo.lim.uMax) then conLoo.conCoo.lim.uMax else if noEvent(conLoo.conCoo.addPID.y < conLoo.conCoo.lim.uMin) then conLoo.conCoo.lim.uMin else conLoo.conCoo.addPID.y), conLoo.conCoo.addPID.y)
*/
void ReheatControllerFMU_eqFunction_285(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,285};
  modelica_boolean tmp50;
  modelica_boolean tmp51;
  modelica_boolean tmp52;
  modelica_real tmp53;
  tmp50 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */),(data->simulationInfo->realParameter[128] /* conLoo.conCoo.lim.uMax PARAM */));
  tmp52 = (modelica_boolean)tmp50;
  if(tmp52)
  {
    tmp53 = (data->simulationInfo->realParameter[128] /* conLoo.conCoo.lim.uMax PARAM */);
  }
  else
  {
    tmp51 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */),(data->simulationInfo->realParameter[129] /* conLoo.conCoo.lim.uMin PARAM */));
    tmp53 = (tmp51?(data->simulationInfo->realParameter[129] /* conLoo.conCoo.lim.uMin PARAM */):(data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */));
  }
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */) = homotopy(tmp53, (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */));
  TRACE_POP
}

/*
equation index: 286
type: SIMPLE_ASSIGN
conLoo.zerCon.lesHys.y = not $PRE.conLoo.zerCon.lesHys.y and conLoo.conCoo.y < 0.01 or $PRE.conLoo.zerCon.lesHys.y and conLoo.conCoo.y < 0.018000000000000002
*/
void ReheatControllerFMU_eqFunction_286(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,286};
  modelica_boolean tmp54;
  modelica_boolean tmp55;
  tmp54 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */),0.01);
  tmp55 = Less((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */),0.018000000000000002);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[135]] /* conLoo.zerCon.lesHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */)) && tmp54) || ((data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */) && tmp55));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1234(DATA *data, threadData_t *threadData);


/*
equation index: 288
type: SIMPLE_ASSIGN
$whenCondition50 = not conLoo.disCoo.u
*/
void ReheatControllerFMU_eqFunction_288(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,288};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[45]] /* $whenCondition50 DISCRETE */) = (!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[127]] /* conLoo.disCoo.u DISCRETE */));
  TRACE_POP
}

/*
equation index: 289
type: SIMPLE_ASSIGN
$whenCondition51 = conLoo.disCoo.u
*/
void ReheatControllerFMU_eqFunction_289(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,289};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[46]] /* $whenCondition51 DISCRETE */) = (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[127]] /* conLoo.disCoo.u DISCRETE */);
  TRACE_POP
}

/*
equation index: 290
type: SIMPLE_ASSIGN
conLoo.disCoo.y = if not (conLoo.disCoo.delayOnInit and conLoo.disCoo.delayTime > 0.0) then conLoo.disCoo.u else false
*/
void ReheatControllerFMU_eqFunction_290(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,290};
  modelica_boolean tmp56;
  tmp56 = Greater((data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */),0.0);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[128]] /* conLoo.disCoo.y DISCRETE */) = ((!((data->simulationInfo->booleanParameter[52] /* conLoo.disCoo.delayOnInit PARAM */) && tmp56))?(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[127]] /* conLoo.disCoo.u DISCRETE */):0 /* false */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1461(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1462(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1463(DATA *data, threadData_t *threadData);


/*
equation index: 294
type: SIMPLE_ASSIGN
sysReq.sampler.y = conLoo.yCoo
*/
void ReheatControllerFMU_eqFunction_294(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,294};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[207]] /* sysReq.sampler.y DISCRETE */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */);
  TRACE_POP
}

/*
equation index: 295
type: SIMPLE_ASSIGN
damVal.greThr1.greHys.y = not $PRE.damVal.greThr1.greHys.y and conLoo.yCoo > 0.01 or $PRE.damVal.greThr1.greHys.y and conLoo.yCoo > 0.005
*/
void ReheatControllerFMU_eqFunction_295(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,295};
  modelica_boolean tmp57;
  modelica_boolean tmp58;
  tmp57 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */),0.01);
  tmp58 = Greater((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */),0.005);
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[148]] /* damVal.greThr1.greHys.y DISCRETE */) = (((!(data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */)) && tmp57) || ((data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */) && tmp58));
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1465(DATA *data, threadData_t *threadData);


/*
equation index: 297
type: SIMPLE_ASSIGN
$whenCondition2 = damVal.truFalHol1.not_u and not $PRE.damVal.truFalHol1.not_u
*/
void ReheatControllerFMU_eqFunction_297(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,297};
  (data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[11]] /* $whenCondition2 DISCRETE */) = ((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[161]] /* damVal.truFalHol1.not_u DISCRETE */) && (!(data->simulationInfo->booleanVarsPre[161] /* damVal.truFalHol1.not_u DISCRETE */)));
  TRACE_POP
}
OMC_DISABLE_OPT
void ReheatControllerFMU_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ReheatControllerFMU_eqFunction_1(data, threadData);
  ReheatControllerFMU_eqFunction_2(data, threadData);
  ReheatControllerFMU_eqFunction_3(data, threadData);
  ReheatControllerFMU_eqFunction_4(data, threadData);
  ReheatControllerFMU_eqFunction_5(data, threadData);
  ReheatControllerFMU_eqFunction_6(data, threadData);
  ReheatControllerFMU_eqFunction_7(data, threadData);
  ReheatControllerFMU_eqFunction_8(data, threadData);
  ReheatControllerFMU_eqFunction_9(data, threadData);
  ReheatControllerFMU_eqFunction_10(data, threadData);
  ReheatControllerFMU_eqFunction_11(data, threadData);
  ReheatControllerFMU_eqFunction_12(data, threadData);
  ReheatControllerFMU_eqFunction_13(data, threadData);
  ReheatControllerFMU_eqFunction_14(data, threadData);
  ReheatControllerFMU_eqFunction_1184(data, threadData);
  ReheatControllerFMU_eqFunction_1185(data, threadData);
  ReheatControllerFMU_eqFunction_1186(data, threadData);
  ReheatControllerFMU_eqFunction_1187(data, threadData);
  ReheatControllerFMU_eqFunction_1188(data, threadData);
  ReheatControllerFMU_eqFunction_1189(data, threadData);
  ReheatControllerFMU_eqFunction_1190(data, threadData);
  ReheatControllerFMU_eqFunction_1193(data, threadData);
  ReheatControllerFMU_eqFunction_1194(data, threadData);
  ReheatControllerFMU_eqFunction_1195(data, threadData);
  ReheatControllerFMU_eqFunction_1196(data, threadData);
  ReheatControllerFMU_eqFunction_1197(data, threadData);
  ReheatControllerFMU_eqFunction_1198(data, threadData);
  ReheatControllerFMU_eqFunction_1199(data, threadData);
  ReheatControllerFMU_eqFunction_1191(data, threadData);
  ReheatControllerFMU_eqFunction_1192(data, threadData);
  ReheatControllerFMU_eqFunction_1200(data, threadData);
  ReheatControllerFMU_eqFunction_1205(data, threadData);
  ReheatControllerFMU_eqFunction_1210(data, threadData);
  ReheatControllerFMU_eqFunction_1211(data, threadData);
  ReheatControllerFMU_eqFunction_1225(data, threadData);
  ReheatControllerFMU_eqFunction_1226(data, threadData);
  ReheatControllerFMU_eqFunction_1227(data, threadData);
  ReheatControllerFMU_eqFunction_1240(data, threadData);
  ReheatControllerFMU_eqFunction_39(data, threadData);
  ReheatControllerFMU_eqFunction_1237(data, threadData);
  ReheatControllerFMU_eqFunction_1241(data, threadData);
  ReheatControllerFMU_eqFunction_1242(data, threadData);
  ReheatControllerFMU_eqFunction_1243(data, threadData);
  ReheatControllerFMU_eqFunction_1256(data, threadData);
  ReheatControllerFMU_eqFunction_45(data, threadData);
  ReheatControllerFMU_eqFunction_1253(data, threadData);
  ReheatControllerFMU_eqFunction_1266(data, threadData);
  ReheatControllerFMU_eqFunction_1268(data, threadData);
  ReheatControllerFMU_eqFunction_1269(data, threadData);
  ReheatControllerFMU_eqFunction_1270(data, threadData);
  ReheatControllerFMU_eqFunction_1272(data, threadData);
  ReheatControllerFMU_eqFunction_1271(data, threadData);
  ReheatControllerFMU_eqFunction_1273(data, threadData);
  ReheatControllerFMU_eqFunction_1274(data, threadData);
  ReheatControllerFMU_eqFunction_1275(data, threadData);
  ReheatControllerFMU_eqFunction_1276(data, threadData);
  ReheatControllerFMU_eqFunction_1288(data, threadData);
  ReheatControllerFMU_eqFunction_58(data, threadData);
  ReheatControllerFMU_eqFunction_1291(data, threadData);
  ReheatControllerFMU_eqFunction_1292(data, threadData);
  ReheatControllerFMU_eqFunction_1293(data, threadData);
  ReheatControllerFMU_eqFunction_1294(data, threadData);
  ReheatControllerFMU_eqFunction_1295(data, threadData);
  ReheatControllerFMU_eqFunction_1296(data, threadData);
  ReheatControllerFMU_eqFunction_65(data, threadData);
  ReheatControllerFMU_eqFunction_1299(data, threadData);
  ReheatControllerFMU_eqFunction_67(data, threadData);
  ReheatControllerFMU_eqFunction_68(data, threadData);
  ReheatControllerFMU_eqFunction_1304(data, threadData);
  ReheatControllerFMU_eqFunction_1302(data, threadData);
  ReheatControllerFMU_eqFunction_1317(data, threadData);
  ReheatControllerFMU_eqFunction_1318(data, threadData);
  ReheatControllerFMU_eqFunction_1319(data, threadData);
  ReheatControllerFMU_eqFunction_1300(data, threadData);
  ReheatControllerFMU_eqFunction_1305(data, threadData);
  ReheatControllerFMU_eqFunction_1306(data, threadData);
  ReheatControllerFMU_eqFunction_1307(data, threadData);
  ReheatControllerFMU_eqFunction_1308(data, threadData);
  ReheatControllerFMU_eqFunction_1309(data, threadData);
  ReheatControllerFMU_eqFunction_1310(data, threadData);
  ReheatControllerFMU_eqFunction_1311(data, threadData);
  ReheatControllerFMU_eqFunction_1314(data, threadData);
  ReheatControllerFMU_eqFunction_1320(data, threadData);
  ReheatControllerFMU_eqFunction_1315(data, threadData);
  ReheatControllerFMU_eqFunction_1316(data, threadData);
  ReheatControllerFMU_eqFunction_1312(data, threadData);
  ReheatControllerFMU_eqFunction_1313(data, threadData);
  ReheatControllerFMU_eqFunction_1324(data, threadData);
  ReheatControllerFMU_eqFunction_1325(data, threadData);
  ReheatControllerFMU_eqFunction_1327(data, threadData);
  ReheatControllerFMU_eqFunction_1328(data, threadData);
  ReheatControllerFMU_eqFunction_1330(data, threadData);
  ReheatControllerFMU_eqFunction_1332(data, threadData);
  ReheatControllerFMU_eqFunction_1333(data, threadData);
  ReheatControllerFMU_eqFunction_1334(data, threadData);
  ReheatControllerFMU_eqFunction_1335(data, threadData);
  ReheatControllerFMU_eqFunction_1337(data, threadData);
  ReheatControllerFMU_eqFunction_1618(data, threadData);
  ReheatControllerFMU_eqFunction_1338(data, threadData);
  ReheatControllerFMU_eqFunction_1340(data, threadData);
  ReheatControllerFMU_eqFunction_1343(data, threadData);
  ReheatControllerFMU_eqFunction_1339(data, threadData);
  ReheatControllerFMU_eqFunction_1341(data, threadData);
  ReheatControllerFMU_eqFunction_1344(data, threadData);
  ReheatControllerFMU_eqFunction_1342(data, threadData);
  ReheatControllerFMU_eqFunction_1346(data, threadData);
  ReheatControllerFMU_eqFunction_1347(data, threadData);
  ReheatControllerFMU_eqFunction_1348(data, threadData);
  ReheatControllerFMU_eqFunction_1349(data, threadData);
  ReheatControllerFMU_eqFunction_1350(data, threadData);
  ReheatControllerFMU_eqFunction_1345(data, threadData);
  ReheatControllerFMU_eqFunction_1351(data, threadData);
  ReheatControllerFMU_eqFunction_113(data, threadData);
  ReheatControllerFMU_eqFunction_114(data, threadData);
  ReheatControllerFMU_eqFunction_115(data, threadData);
  ReheatControllerFMU_eqFunction_1181(data, threadData);
  ReheatControllerFMU_eqFunction_117(data, threadData);
  ReheatControllerFMU_eqFunction_1356(data, threadData);
  ReheatControllerFMU_eqFunction_1357(data, threadData);
  ReheatControllerFMU_eqFunction_120(data, threadData);
  ReheatControllerFMU_eqFunction_121(data, threadData);
  ReheatControllerFMU_eqFunction_122(data, threadData);
  ReheatControllerFMU_eqFunction_123(data, threadData);
  ReheatControllerFMU_eqFunction_124(data, threadData);
  ReheatControllerFMU_eqFunction_125(data, threadData);
  ReheatControllerFMU_eqFunction_126(data, threadData);
  ReheatControllerFMU_eqFunction_127(data, threadData);
  ReheatControllerFMU_eqFunction_128(data, threadData);
  ReheatControllerFMU_eqFunction_129(data, threadData);
  ReheatControllerFMU_eqFunction_130(data, threadData);
  ReheatControllerFMU_eqFunction_131(data, threadData);
  ReheatControllerFMU_eqFunction_132(data, threadData);
  ReheatControllerFMU_eqFunction_133(data, threadData);
  ReheatControllerFMU_eqFunction_134(data, threadData);
  ReheatControllerFMU_eqFunction_1336(data, threadData);
  ReheatControllerFMU_eqFunction_136(data, threadData);
  ReheatControllerFMU_eqFunction_137(data, threadData);
  ReheatControllerFMU_eqFunction_138(data, threadData);
  ReheatControllerFMU_eqFunction_139(data, threadData);
  ReheatControllerFMU_eqFunction_140(data, threadData);
  ReheatControllerFMU_eqFunction_141(data, threadData);
  ReheatControllerFMU_eqFunction_142(data, threadData);
  ReheatControllerFMU_eqFunction_143(data, threadData);
  ReheatControllerFMU_eqFunction_144(data, threadData);
  ReheatControllerFMU_eqFunction_1322(data, threadData);
  ReheatControllerFMU_eqFunction_1323(data, threadData);
  ReheatControllerFMU_eqFunction_147(data, threadData);
  ReheatControllerFMU_eqFunction_148(data, threadData);
  ReheatControllerFMU_eqFunction_149(data, threadData);
  ReheatControllerFMU_eqFunction_150(data, threadData);
  ReheatControllerFMU_eqFunction_151(data, threadData);
  ReheatControllerFMU_eqFunction_152(data, threadData);
  ReheatControllerFMU_eqFunction_153(data, threadData);
  ReheatControllerFMU_eqFunction_154(data, threadData);
  ReheatControllerFMU_eqFunction_155(data, threadData);
  ReheatControllerFMU_eqFunction_156(data, threadData);
  ReheatControllerFMU_eqFunction_157(data, threadData);
  ReheatControllerFMU_eqFunction_1377(data, threadData);
  ReheatControllerFMU_eqFunction_1378(data, threadData);
  ReheatControllerFMU_eqFunction_1379(data, threadData);
  ReheatControllerFMU_eqFunction_1380(data, threadData);
  ReheatControllerFMU_eqFunction_162(data, threadData);
  ReheatControllerFMU_eqFunction_163(data, threadData);
  ReheatControllerFMU_eqFunction_1283(data, threadData);
  ReheatControllerFMU_eqFunction_1367(data, threadData);
  ReheatControllerFMU_eqFunction_1368(data, threadData);
  ReheatControllerFMU_eqFunction_167(data, threadData);
  ReheatControllerFMU_eqFunction_1370(data, threadData);
  ReheatControllerFMU_eqFunction_169(data, threadData);
  ReheatControllerFMU_eqFunction_1384(data, threadData);
  ReheatControllerFMU_eqFunction_171(data, threadData);
  ReheatControllerFMU_eqFunction_1382(data, threadData);
  ReheatControllerFMU_eqFunction_1373(data, threadData);
  ReheatControllerFMU_eqFunction_174(data, threadData);
  ReheatControllerFMU_eqFunction_175(data, threadData);
  ReheatControllerFMU_eqFunction_1391(data, threadData);
  ReheatControllerFMU_eqFunction_1392(data, threadData);
  ReheatControllerFMU_eqFunction_1393(data, threadData);
  ReheatControllerFMU_eqFunction_179(data, threadData);
  ReheatControllerFMU_eqFunction_1396(data, threadData);
  ReheatControllerFMU_eqFunction_181(data, threadData);
  ReheatControllerFMU_eqFunction_182(data, threadData);
  ReheatControllerFMU_eqFunction_183(data, threadData);
  ReheatControllerFMU_eqFunction_184(data, threadData);
  ReheatControllerFMU_eqFunction_185(data, threadData);
  ReheatControllerFMU_eqFunction_186(data, threadData);
  ReheatControllerFMU_eqFunction_187(data, threadData);
  ReheatControllerFMU_eqFunction_188(data, threadData);
  ReheatControllerFMU_eqFunction_1265(data, threadData);
  ReheatControllerFMU_eqFunction_190(data, threadData);
  ReheatControllerFMU_eqFunction_191(data, threadData);
  ReheatControllerFMU_eqFunction_192(data, threadData);
  ReheatControllerFMU_eqFunction_193(data, threadData);
  ReheatControllerFMU_eqFunction_1416(data, threadData);
  ReheatControllerFMU_eqFunction_195(data, threadData);
  ReheatControllerFMU_eqFunction_196(data, threadData);
  ReheatControllerFMU_eqFunction_197(data, threadData);
  ReheatControllerFMU_eqFunction_198(data, threadData);
  ReheatControllerFMU_eqFunction_199(data, threadData);
  ReheatControllerFMU_eqFunction_200(data, threadData);
  ReheatControllerFMU_eqFunction_201(data, threadData);
  ReheatControllerFMU_eqFunction_1260(data, threadData);
  ReheatControllerFMU_eqFunction_203(data, threadData);
  ReheatControllerFMU_eqFunction_204(data, threadData);
  ReheatControllerFMU_eqFunction_1258(data, threadData);
  ReheatControllerFMU_eqFunction_206(data, threadData);
  ReheatControllerFMU_eqFunction_1245(data, threadData);
  ReheatControllerFMU_eqFunction_208(data, threadData);
  ReheatControllerFMU_eqFunction_209(data, threadData);
  ReheatControllerFMU_eqFunction_1250(data, threadData);
  ReheatControllerFMU_eqFunction_211(data, threadData);
  ReheatControllerFMU_eqFunction_212(data, threadData);
  ReheatControllerFMU_eqFunction_213(data, threadData);
  ReheatControllerFMU_eqFunction_1428(data, threadData);
  ReheatControllerFMU_eqFunction_1429(data, threadData);
  ReheatControllerFMU_eqFunction_1430(data, threadData);
  ReheatControllerFMU_eqFunction_217(data, threadData);
  ReheatControllerFMU_eqFunction_1432(data, threadData);
  ReheatControllerFMU_eqFunction_219(data, threadData);
  ReheatControllerFMU_eqFunction_1433(data, threadData);
  ReheatControllerFMU_eqFunction_221(data, threadData);
  ReheatControllerFMU_eqFunction_222(data, threadData);
  ReheatControllerFMU_eqFunction_223(data, threadData);
  ReheatControllerFMU_eqFunction_224(data, threadData);
  ReheatControllerFMU_eqFunction_1438(data, threadData);
  ReheatControllerFMU_eqFunction_226(data, threadData);
  ReheatControllerFMU_eqFunction_227(data, threadData);
  ReheatControllerFMU_eqFunction_228(data, threadData);
  ReheatControllerFMU_eqFunction_229(data, threadData);
  ReheatControllerFMU_eqFunction_230(data, threadData);
  ReheatControllerFMU_eqFunction_1447(data, threadData);
  ReheatControllerFMU_eqFunction_1619(data, threadData);
  ReheatControllerFMU_eqFunction_1656(data, threadData);
  ReheatControllerFMU_eqFunction_1657(data, threadData);
  ReheatControllerFMU_eqFunction_1687(data, threadData);
  ReheatControllerFMU_eqFunction_236(data, threadData);
  ReheatControllerFMU_eqFunction_1684(data, threadData);
  ReheatControllerFMU_eqFunction_1659(data, threadData);
  ReheatControllerFMU_eqFunction_239(data, threadData);
  ReheatControllerFMU_eqFunction_240(data, threadData);
  ReheatControllerFMU_eqFunction_1662(data, threadData);
  ReheatControllerFMU_eqFunction_1663(data, threadData);
  ReheatControllerFMU_eqFunction_243(data, threadData);
  ReheatControllerFMU_eqFunction_1665(data, threadData);
  ReheatControllerFMU_eqFunction_245(data, threadData);
  ReheatControllerFMU_eqFunction_246(data, threadData);
  ReheatControllerFMU_eqFunction_247(data, threadData);
  ReheatControllerFMU_eqFunction_248(data, threadData);
  ReheatControllerFMU_eqFunction_1672(data, threadData);
  ReheatControllerFMU_eqFunction_1682(data, threadData);
  ReheatControllerFMU_eqFunction_1683(data, threadData);
  ReheatControllerFMU_eqFunction_1685(data, threadData);
  ReheatControllerFMU_eqFunction_1686(data, threadData);
  ReheatControllerFMU_eqFunction_1655(data, threadData);
  ReheatControllerFMU_eqFunction_1636(data, threadData);
  ReheatControllerFMU_eqFunction_256(data, threadData);
  ReheatControllerFMU_eqFunction_1654(data, threadData);
  ReheatControllerFMU_eqFunction_258(data, threadData);
  ReheatControllerFMU_eqFunction_259(data, threadData);
  ReheatControllerFMU_eqFunction_260(data, threadData);
  ReheatControllerFMU_eqFunction_1648(data, threadData);
  ReheatControllerFMU_eqFunction_1649(data, threadData);
  ReheatControllerFMU_eqFunction_1650(data, threadData);
  ReheatControllerFMU_eqFunction_1651(data, threadData);
  ReheatControllerFMU_eqFunction_1620(data, threadData);
  ReheatControllerFMU_eqFunction_266(data, threadData);
  ReheatControllerFMU_eqFunction_1635(data, threadData);
  ReheatControllerFMU_eqFunction_268(data, threadData);
  ReheatControllerFMU_eqFunction_269(data, threadData);
  ReheatControllerFMU_eqFunction_270(data, threadData);
  ReheatControllerFMU_eqFunction_1632(data, threadData);
  ReheatControllerFMU_eqFunction_1633(data, threadData);
  ReheatControllerFMU_eqFunction_1634(data, threadData);
  ReheatControllerFMU_eqFunction_1652(data, threadData);
  ReheatControllerFMU_eqFunction_1653(data, threadData);
  ReheatControllerFMU_eqFunction_276(data, threadData);
  ReheatControllerFMU_eqFunction_1450(data, threadData);
  ReheatControllerFMU_eqFunction_1451(data, threadData);
  ReheatControllerFMU_eqFunction_1251(data, threadData);
  ReheatControllerFMU_eqFunction_1252(data, threadData);
  ReheatControllerFMU_eqFunction_1254(data, threadData);
  ReheatControllerFMU_eqFunction_1255(data, threadData);
  ReheatControllerFMU_eqFunction_283(data, threadData);
  ReheatControllerFMU_eqFunction_1229(data, threadData);
  ReheatControllerFMU_eqFunction_285(data, threadData);
  ReheatControllerFMU_eqFunction_286(data, threadData);
  ReheatControllerFMU_eqFunction_1234(data, threadData);
  ReheatControllerFMU_eqFunction_288(data, threadData);
  ReheatControllerFMU_eqFunction_289(data, threadData);
  ReheatControllerFMU_eqFunction_290(data, threadData);
  ReheatControllerFMU_eqFunction_1461(data, threadData);
  ReheatControllerFMU_eqFunction_1462(data, threadData);
  ReheatControllerFMU_eqFunction_1463(data, threadData);
  ReheatControllerFMU_eqFunction_294(data, threadData);
  ReheatControllerFMU_eqFunction_295(data, threadData);
  ReheatControllerFMU_eqFunction_1465(data, threadData);
  ReheatControllerFMU_eqFunction_297(data, threadData);
  TRACE_POP
}
#if defined(__cplusplus)
}
#endif
