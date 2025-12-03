/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "ReheatControllerFMU_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void ReheatControllerFMU_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
  /* sample 1 */
  data->modelData->samplesInfo[i].index = 1;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[411] /* sysReq.sampler.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[410] /* sysReq.sampler.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
  /* sample 2 */
  data->modelData->samplesInfo[i].index = 2;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[413] /* sysReq.sampler1.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[412] /* sysReq.sampler1.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
  /* sample 3 */
  data->modelData->samplesInfo[i].index = 3;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[415] /* sysReq.sampler2.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[414] /* sysReq.sampler2.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
  /* sample 4 */
  data->modelData->samplesInfo[i].index = 4;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[417] /* sysReq.sampler3.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[416] /* sysReq.sampler3.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
  /* sample 5 */
  data->modelData->samplesInfo[i].index = 5;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[450] /* timSup.samSet.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[449] /* timSup.samSet.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
  /* sample 6 */
  data->modelData->samplesInfo[i].index = 6;
  data->modelData->samplesInfo[i].start = (data->simulationInfo->realParameter[459] /* timSup.uniDel.t0 PARAM */);
  data->modelData->samplesInfo[i].interval = (data->simulationInfo->realParameter[458] /* timSup.uniDel.samplePeriod PARAM */) /* (max real for single time events) */;
  i++;
}

const char *ReheatControllerFMU_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"time >= pre(sysReq.tim1.t_next)",
  "time >= pre(sysReq.tim2.t_next)",
  "time >= pre(sysReq.tim3.t_next)",
  "time >= pre(sysReq.tim4.t_next)",
  "time >= pre(sysReq.tim5.t_next)",
  "time >= pre(conLoo.disCoo.t_next)",
  "time >= pre(conLoo.disHea.t_next)",
  "time >= pre(ala.truDel.t_next)",
  "time >= pre(ala.truDel1.t_next)",
  "time >= pre(ala.truDel2.t_next)",
  "time >= pre(ala.truDel3.t_next)",
  "time >= pre(ala.truDel4.t_next)",
  "time >= pre(ala.truDel5.t_next)",
  "time >= pre(ala.truDel6.t_next)",
  "time >= pre(ala.truDel7.t_next)",
  "time >= pre(ala.fanIni.t_next)",
  "time >= pre(timSup.truDel.t_next)",
  "time >= pre(damVal.truFalHol.entryTimeFalse) and time >= pre(damVal.truFalHol.entryTimeTrue) + 600.0",
  "time >= pre(damVal.truFalHol1.entryTimeFalse) and time >= pre(damVal.truFalHol1.entryTimeTrue) + 600.0",
  "not u1Fan",
  "oveFloSet == 4",
  "oveFloSet == 3",
  "oveFloSet == 2",
  "oveFloSet == 1",
  "7 == uOpeMod",
  "1 == uOpeMod",
  "not pre(damVal.lowMin.lesHys.y) and TDis < damVal.lowMin.lesHys.t or pre(damVal.lowMin.lesHys.y) and TDis < damVal.lowMin.lesHys.t + 0.25",
  "not pre(damVal.greThr.greHys.y) and damVal.sub2.y > 0.25 or pre(damVal.greThr.greHys.y) and damVal.sub2.y > 0.125",
  "not pre(damVal.gre.greHys.y) and TDis > damVal.addPar1.y or pre(damVal.gre.greHys.y) and TDis > damVal.addPar1.y - 0.25",
  "not pre(setPoi.cooSup.greHys.y) and TZon > TDis or pre(setPoi.cooSup.greHys.y) and TZon > TDis - 0.25",
  "uOpeMod == 1",
  "not uOpeMod == 1",
  "not u1Win",
  "not pre(timSup.greThr.greHys.y) and timSup.abs1.y > 0.25 or pre(timSup.greThr.greHys.y) and timSup.abs1.y > 0.125",
  "timSup.lat.y and time >= timSup.tim.t + pre(timSup.tim.entryTime)",
  "timSup.tim.y > timSup.supTim.y",
  "oveDamPos == 2",
  "oveDamPos == 1",
  "not pre(ala.gre2.greHys.y) and TDis > ala.addPar2.y or pre(ala.gre2.greHys.y) and TDis > ala.addPar2.y - 0.25",
  "not pre(ala.gre1.greHys.y) and VDis_flow > ala.gai2.y or pre(ala.gre1.greHys.y) and VDis_flow > ala.gai2.y - 0.005",
  "not pre(conLoo.enaCooLoo.lesHys.y) and TCooSet < TZon or pre(conLoo.enaCooLoo.lesHys.y) and TCooSet < TZon + 0.25",
  "not pre(conLoo.enaHeaLoo.lesHys.y) and TZon < THeaSet or pre(conLoo.enaHeaLoo.lesHys.y) and TZon < THeaSet + 0.25",
  "not pre(conLoo.zerCon1.lesHys.y) and conLoo.conHea.y < 0.01 or pre(conLoo.zerCon1.lesHys.y) and conLoo.conHea.y < 0.018000000000000002",
  "not pre(damVal.greThr2.greHys.y) and conLoo.yHea > 0.01 or pre(damVal.greThr2.greHys.y) and conLoo.yHea > 0.002",
  "not pre(ala.les1.lesHys.y) and TDis < ala.addPar.y or pre(ala.les1.lesHys.y) and TDis < ala.addPar.y + 0.25",
  "not pre(ala.les2.lesHys.y) and TDis < ala.addPar1.y or pre(ala.les2.lesHys.y) and TDis < ala.addPar1.y + 0.25",
  "not pre(ala.cloVal.lesHys.y) and yVal < 0.005 or pre(ala.cloVal.lesHys.y) and yVal < 0.0075",
  "not pre(conLoo.zerCon.lesHys.y) and conLoo.conCoo.y < 0.01 or pre(conLoo.zerCon.lesHys.y) and conLoo.conCoo.y < 0.018000000000000002",
  "not pre(damVal.greThr1.greHys.y) and conLoo.yCoo > 0.01 or pre(damVal.greThr1.greHys.y) and conLoo.yCoo > 0.005",
  "not pre(sysReq.greThr6.greHys.y) and yVal > 0.95 or pre(sysReq.greThr6.greHys.y) and yVal > 0.09999999999999998",
  "not pre(sysReq.greThr5.greHys.y) and yVal > 0.95 or pre(sysReq.greThr5.greHys.y) and yVal > 0.945",
  "not pre(sysReq.greThr2.greHys.y) and sysReq.sub3.y > sysReq.greThr2.greHys.t or pre(sysReq.greThr2.greHys.y) and sysReq.sub3.y > sysReq.greThr2.greHys.t - 0.25",
  "not pre(sysReq.greThr1.greHys.y) and sysReq.sub2.y > sysReq.greThr1.greHys.t or pre(sysReq.greThr1.greHys.y) and sysReq.sub2.y > sysReq.greThr1.greHys.t - 0.25",
  "not pre(sysReq.les1.lesHys.y) and sysReq.addPar1.y < damVal.TDisSet or pre(sysReq.les1.lesHys.y) and sysReq.addPar1.y < damVal.TDisSet + 0.25",
  "not pre(sysReq.les.lesHys.y) and sysReq.addPar.y < damVal.TDisSet or pre(sysReq.les.lesHys.y) and sysReq.addPar.y < damVal.TDisSet + 0.25",
  "5 == uOpeMod",
  "4 == uOpeMod",
  "3 == uOpeMod",
  "2 == uOpeMod",
  "not pre(ala.les.lesHys.y) and VDis_flow < ala.gai.y or pre(ala.les.lesHys.y) and VDis_flow < ala.gai.y + 0.005",
  "not pre(ala.greThr.greHys.y) and VSet_flow > 0.005 or pre(ala.greThr.greHys.y) and VSet_flow > 0.0025",
  "not pre(ala.gre.greHys.y) and ala.gai1.y > VDis_flow or pre(ala.gre.greHys.y) and ala.gai1.y > VDis_flow - 0.005",
  "not pre(ala.cloDam.lesHys.y) and yDam < 0.005 or pre(ala.cloDam.lesHys.y) and yDam < 0.0075",
  "not pre(sysReq.greEqu.greHys.y) and sysReq.greEqu.u1 > sysReq.sampler2.y or pre(sysReq.greEqu.greHys.y) and sysReq.greEqu.u1 > sysReq.sampler2.y - 0.005",
  "not pre(sysReq.greEqu1.greHys.y) and sysReq.gai2.y > sysReq.sampler2.y or pre(sysReq.greEqu1.greHys.y) and sysReq.gai2.y > sysReq.sampler2.y - 0.005"};
  static const int occurEqs0[] = {1,1606};
  static const int occurEqs1[] = {1,1595};
  static const int occurEqs2[] = {1,1581};
  static const int occurEqs3[] = {1,1580};
  static const int occurEqs4[] = {1,1579};
  static const int occurEqs5[] = {1,1456};
  static const int occurEqs6[] = {1,1423};
  static const int occurEqs7[] = {1,1422};
  static const int occurEqs8[] = {1,1421};
  static const int occurEqs9[] = {1,1411};
  static const int occurEqs10[] = {1,1410};
  static const int occurEqs11[] = {1,1409};
  static const int occurEqs12[] = {1,1408};
  static const int occurEqs13[] = {1,1407};
  static const int occurEqs14[] = {1,1406};
  static const int occurEqs15[] = {1,1397};
  static const int occurEqs16[] = {1,1358};
  static const int occurEqs17[] = {1,1355};
  static const int occurEqs18[] = {1,1354};
  static const int occurEqs19[] = {1,1352};
  static const int occurEqs20[] = {1,1346};
  static const int occurEqs21[] = {1,1343};
  static const int occurEqs22[] = {1,1340};
  static const int occurEqs23[] = {1,1338};
  static const int occurEqs24[] = {1,1337};
  static const int occurEqs25[] = {1,1335};
  static const int occurEqs26[] = {1,1329};
  static const int occurEqs27[] = {1,1326};
  static const int occurEqs28[] = {1,1331};
  static const int occurEqs29[] = {1,1321};
  static const int occurEqs30[] = {1,1294};
  static const int occurEqs31[] = {1,1294};
  static const int occurEqs32[] = {1,1304};
  static const int occurEqs33[] = {1,1369};
  static const int occurEqs34[] = {1,1383};
  static const int occurEqs35[] = {1,1392};
  static const int occurEqs36[] = {1,1272};
  static const int occurEqs37[] = {1,1270};
  static const int occurEqs38[] = {1,1267};
  static const int occurEqs39[] = {1,1261};
  static const int occurEqs40[] = {1,1259};
  static const int occurEqs41[] = {1,1257};
  static const int occurEqs42[] = {1,1247};
  static const int occurEqs43[] = {1,1431};
  static const int occurEqs44[] = {1,1621};
  static const int occurEqs45[] = {1,1637};
  static const int occurEqs46[] = {1,1664};
  static const int occurEqs47[] = {1,1231};
  static const int occurEqs48[] = {1,1464};
  static const int occurEqs49[] = {1,1678};
  static const int occurEqs50[] = {1,1680};
  static const int occurEqs51[] = {1,1206};
  static const int occurEqs52[] = {1,1201};
  static const int occurEqs53[] = {1,1688};
  static const int occurEqs54[] = {1,1701};
  static const int occurEqs55[] = {1,1194};
  static const int occurEqs56[] = {1,1193};
  static const int occurEqs57[] = {1,1190};
  static const int occurEqs58[] = {1,1186};
  static const int occurEqs59[] = {1,1486};
  static const int occurEqs60[] = {1,1498};
  static const int occurEqs61[] = {1,1514};
  static const int occurEqs62[] = {1,1541};
  static const int occurEqs63[] = {1,1569};
  static const int occurEqs64[] = {1,1571};
  static const int *occurEqs[] = {occurEqs0,occurEqs1,occurEqs2,occurEqs3,occurEqs4,occurEqs5,occurEqs6,occurEqs7,occurEqs8,occurEqs9,occurEqs10,occurEqs11,occurEqs12,occurEqs13,occurEqs14,occurEqs15,occurEqs16,occurEqs17,occurEqs18,occurEqs19,occurEqs20,occurEqs21,occurEqs22,occurEqs23,occurEqs24,occurEqs25,occurEqs26,occurEqs27,occurEqs28,occurEqs29,occurEqs30,occurEqs31,occurEqs32,occurEqs33,occurEqs34,occurEqs35,occurEqs36,occurEqs37,occurEqs38,occurEqs39,occurEqs40,occurEqs41,occurEqs42,occurEqs43,occurEqs44,occurEqs45,occurEqs46,occurEqs47,occurEqs48,occurEqs49,occurEqs50,occurEqs51,occurEqs52,occurEqs53,occurEqs54,occurEqs55,occurEqs56,occurEqs57,occurEqs58,occurEqs59,occurEqs60,occurEqs61,occurEqs62,occurEqs63,occurEqs64};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
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
extern void ReheatControllerFMU_eqFunction_1200(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1205(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1210(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1211(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1218(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1222(DATA* data, threadData_t *threadData);
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
extern void ReheatControllerFMU_eqFunction_1266(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1270(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1271(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1272(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1273(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1274(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1275(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1276(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1277(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1281(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1283(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1286(DATA* data, threadData_t *threadData);
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
extern void ReheatControllerFMU_eqFunction_1329(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1330(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1331(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1332(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1333(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1334(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1335(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1336(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1337(DATA* data, threadData_t *threadData);
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
extern void ReheatControllerFMU_eqFunction_1356(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1357(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1358(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1367(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1368(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1369(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1370(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1373(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1374(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1377(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1378(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1379(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1380(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1382(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1383(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1384(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1391(DATA* data, threadData_t *threadData);
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
extern void ReheatControllerFMU_eqFunction_1439(DATA* data, threadData_t *threadData);
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
extern void ReheatControllerFMU_eqFunction_1485(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1513(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1532(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1534(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1535(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1536(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1537(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1538(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1539(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1540(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1560(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1561(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1563(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1564(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1568(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1570(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1618(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1619(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1620(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1636(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1656(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1657(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1658(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1659(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1660(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1661(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1662(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1663(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1682(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1683(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1685(DATA* data, threadData_t *threadData);
extern void ReheatControllerFMU_eqFunction_1686(DATA* data, threadData_t *threadData);

int ReheatControllerFMU_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

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

  ReheatControllerFMU_eqFunction_1205(data, threadData);

  ReheatControllerFMU_eqFunction_1210(data, threadData);

  ReheatControllerFMU_eqFunction_1211(data, threadData);

  ReheatControllerFMU_eqFunction_1218(data, threadData);

  ReheatControllerFMU_eqFunction_1222(data, threadData);

  ReheatControllerFMU_eqFunction_1225(data, threadData);

  ReheatControllerFMU_eqFunction_1226(data, threadData);

  ReheatControllerFMU_eqFunction_1227(data, threadData);

  ReheatControllerFMU_eqFunction_1228(data, threadData);

  ReheatControllerFMU_eqFunction_1229(data, threadData);

  ReheatControllerFMU_eqFunction_1230(data, threadData);

  ReheatControllerFMU_eqFunction_1231(data, threadData);

  ReheatControllerFMU_eqFunction_1232(data, threadData);

  ReheatControllerFMU_eqFunction_1233(data, threadData);

  ReheatControllerFMU_eqFunction_1235(data, threadData);

  ReheatControllerFMU_eqFunction_1236(data, threadData);

  ReheatControllerFMU_eqFunction_1238(data, threadData);

  ReheatControllerFMU_eqFunction_1239(data, threadData);

  ReheatControllerFMU_eqFunction_1241(data, threadData);

  ReheatControllerFMU_eqFunction_1242(data, threadData);

  ReheatControllerFMU_eqFunction_1243(data, threadData);

  ReheatControllerFMU_eqFunction_1244(data, threadData);

  ReheatControllerFMU_eqFunction_1245(data, threadData);

  ReheatControllerFMU_eqFunction_1246(data, threadData);

  ReheatControllerFMU_eqFunction_1247(data, threadData);

  ReheatControllerFMU_eqFunction_1248(data, threadData);

  ReheatControllerFMU_eqFunction_1249(data, threadData);

  ReheatControllerFMU_eqFunction_1251(data, threadData);

  ReheatControllerFMU_eqFunction_1252(data, threadData);

  ReheatControllerFMU_eqFunction_1254(data, threadData);

  ReheatControllerFMU_eqFunction_1255(data, threadData);

  ReheatControllerFMU_eqFunction_1257(data, threadData);

  ReheatControllerFMU_eqFunction_1259(data, threadData);

  ReheatControllerFMU_eqFunction_1266(data, threadData);

  ReheatControllerFMU_eqFunction_1270(data, threadData);

  ReheatControllerFMU_eqFunction_1271(data, threadData);

  ReheatControllerFMU_eqFunction_1272(data, threadData);

  ReheatControllerFMU_eqFunction_1273(data, threadData);

  ReheatControllerFMU_eqFunction_1274(data, threadData);

  ReheatControllerFMU_eqFunction_1275(data, threadData);

  ReheatControllerFMU_eqFunction_1276(data, threadData);

  ReheatControllerFMU_eqFunction_1277(data, threadData);

  ReheatControllerFMU_eqFunction_1281(data, threadData);

  ReheatControllerFMU_eqFunction_1283(data, threadData);

  ReheatControllerFMU_eqFunction_1286(data, threadData);

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

  ReheatControllerFMU_eqFunction_1354(data, threadData);

  ReheatControllerFMU_eqFunction_1355(data, threadData);

  ReheatControllerFMU_eqFunction_1356(data, threadData);

  ReheatControllerFMU_eqFunction_1357(data, threadData);

  ReheatControllerFMU_eqFunction_1358(data, threadData);

  ReheatControllerFMU_eqFunction_1367(data, threadData);

  ReheatControllerFMU_eqFunction_1368(data, threadData);

  ReheatControllerFMU_eqFunction_1369(data, threadData);

  ReheatControllerFMU_eqFunction_1370(data, threadData);

  ReheatControllerFMU_eqFunction_1373(data, threadData);

  ReheatControllerFMU_eqFunction_1374(data, threadData);

  ReheatControllerFMU_eqFunction_1377(data, threadData);

  ReheatControllerFMU_eqFunction_1378(data, threadData);

  ReheatControllerFMU_eqFunction_1379(data, threadData);

  ReheatControllerFMU_eqFunction_1380(data, threadData);

  ReheatControllerFMU_eqFunction_1382(data, threadData);

  ReheatControllerFMU_eqFunction_1383(data, threadData);

  ReheatControllerFMU_eqFunction_1384(data, threadData);

  ReheatControllerFMU_eqFunction_1391(data, threadData);

  ReheatControllerFMU_eqFunction_1423(data, threadData);

  ReheatControllerFMU_eqFunction_1428(data, threadData);

  ReheatControllerFMU_eqFunction_1429(data, threadData);

  ReheatControllerFMU_eqFunction_1430(data, threadData);

  ReheatControllerFMU_eqFunction_1431(data, threadData);

  ReheatControllerFMU_eqFunction_1432(data, threadData);

  ReheatControllerFMU_eqFunction_1433(data, threadData);

  ReheatControllerFMU_eqFunction_1434(data, threadData);

  ReheatControllerFMU_eqFunction_1435(data, threadData);

  ReheatControllerFMU_eqFunction_1438(data, threadData);

  ReheatControllerFMU_eqFunction_1439(data, threadData);

  ReheatControllerFMU_eqFunction_1445(data, threadData);

  ReheatControllerFMU_eqFunction_1446(data, threadData);

  ReheatControllerFMU_eqFunction_1447(data, threadData);

  ReheatControllerFMU_eqFunction_1448(data, threadData);

  ReheatControllerFMU_eqFunction_1449(data, threadData);

  ReheatControllerFMU_eqFunction_1450(data, threadData);

  ReheatControllerFMU_eqFunction_1451(data, threadData);

  ReheatControllerFMU_eqFunction_1456(data, threadData);

  ReheatControllerFMU_eqFunction_1461(data, threadData);

  ReheatControllerFMU_eqFunction_1462(data, threadData);

  ReheatControllerFMU_eqFunction_1463(data, threadData);

  ReheatControllerFMU_eqFunction_1464(data, threadData);

  ReheatControllerFMU_eqFunction_1465(data, threadData);

  ReheatControllerFMU_eqFunction_1466(data, threadData);

  ReheatControllerFMU_eqFunction_1467(data, threadData);

  ReheatControllerFMU_eqFunction_1468(data, threadData);

  ReheatControllerFMU_eqFunction_1471(data, threadData);

  ReheatControllerFMU_eqFunction_1472(data, threadData);

  ReheatControllerFMU_eqFunction_1473(data, threadData);

  ReheatControllerFMU_eqFunction_1474(data, threadData);

  ReheatControllerFMU_eqFunction_1479(data, threadData);

  ReheatControllerFMU_eqFunction_1480(data, threadData);

  ReheatControllerFMU_eqFunction_1481(data, threadData);

  ReheatControllerFMU_eqFunction_1482(data, threadData);

  ReheatControllerFMU_eqFunction_1483(data, threadData);

  ReheatControllerFMU_eqFunction_1484(data, threadData);

  ReheatControllerFMU_eqFunction_1485(data, threadData);

  ReheatControllerFMU_eqFunction_1513(data, threadData);

  ReheatControllerFMU_eqFunction_1532(data, threadData);

  ReheatControllerFMU_eqFunction_1534(data, threadData);

  ReheatControllerFMU_eqFunction_1535(data, threadData);

  ReheatControllerFMU_eqFunction_1536(data, threadData);

  ReheatControllerFMU_eqFunction_1537(data, threadData);

  ReheatControllerFMU_eqFunction_1538(data, threadData);

  ReheatControllerFMU_eqFunction_1539(data, threadData);

  ReheatControllerFMU_eqFunction_1540(data, threadData);

  ReheatControllerFMU_eqFunction_1560(data, threadData);

  ReheatControllerFMU_eqFunction_1561(data, threadData);

  ReheatControllerFMU_eqFunction_1563(data, threadData);

  ReheatControllerFMU_eqFunction_1564(data, threadData);

  ReheatControllerFMU_eqFunction_1568(data, threadData);

  ReheatControllerFMU_eqFunction_1570(data, threadData);

  ReheatControllerFMU_eqFunction_1618(data, threadData);

  ReheatControllerFMU_eqFunction_1619(data, threadData);

  ReheatControllerFMU_eqFunction_1620(data, threadData);

  ReheatControllerFMU_eqFunction_1636(data, threadData);

  ReheatControllerFMU_eqFunction_1656(data, threadData);

  ReheatControllerFMU_eqFunction_1657(data, threadData);

  ReheatControllerFMU_eqFunction_1658(data, threadData);

  ReheatControllerFMU_eqFunction_1659(data, threadData);

  ReheatControllerFMU_eqFunction_1660(data, threadData);

  ReheatControllerFMU_eqFunction_1661(data, threadData);

  ReheatControllerFMU_eqFunction_1662(data, threadData);

  ReheatControllerFMU_eqFunction_1663(data, threadData);

  ReheatControllerFMU_eqFunction_1682(data, threadData);

  ReheatControllerFMU_eqFunction_1683(data, threadData);

  ReheatControllerFMU_eqFunction_1685(data, threadData);

  ReheatControllerFMU_eqFunction_1686(data, threadData);

  TRACE_POP
  return 0;
}

int ReheatControllerFMU_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp0;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_boolean tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_boolean tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_boolean tmp9;
  modelica_real tmp10;
  modelica_real tmp11;
  modelica_boolean tmp12;
  modelica_real tmp13;
  modelica_real tmp14;
  modelica_boolean tmp15;
  modelica_real tmp16;
  modelica_real tmp17;
  modelica_boolean tmp18;
  modelica_real tmp19;
  modelica_real tmp20;
  modelica_boolean tmp21;
  modelica_real tmp22;
  modelica_real tmp23;
  modelica_boolean tmp24;
  modelica_real tmp25;
  modelica_real tmp26;
  modelica_boolean tmp27;
  modelica_real tmp28;
  modelica_real tmp29;
  modelica_boolean tmp30;
  modelica_real tmp31;
  modelica_real tmp32;
  modelica_boolean tmp33;
  modelica_real tmp34;
  modelica_real tmp35;
  modelica_boolean tmp36;
  modelica_real tmp37;
  modelica_real tmp38;
  modelica_boolean tmp39;
  modelica_real tmp40;
  modelica_real tmp41;
  modelica_boolean tmp42;
  modelica_real tmp43;
  modelica_real tmp44;
  modelica_boolean tmp45;
  modelica_real tmp46;
  modelica_real tmp47;
  modelica_boolean tmp48;
  modelica_real tmp49;
  modelica_real tmp50;
  modelica_boolean tmp51;
  modelica_real tmp52;
  modelica_real tmp53;
  modelica_boolean tmp54;
  modelica_real tmp55;
  modelica_real tmp56;
  modelica_boolean tmp57;
  modelica_real tmp58;
  modelica_real tmp59;
  modelica_boolean tmp60;
  modelica_real tmp61;
  modelica_real tmp62;
  modelica_boolean tmp63;
  modelica_real tmp64;
  modelica_real tmp65;
  modelica_boolean tmp66;
  modelica_real tmp67;
  modelica_real tmp68;
  modelica_boolean tmp69;
  modelica_real tmp70;
  modelica_real tmp71;
  modelica_boolean tmp72;
  modelica_real tmp73;
  modelica_real tmp74;
  modelica_boolean tmp75;
  modelica_real tmp76;
  modelica_real tmp77;
  modelica_boolean tmp78;
  modelica_real tmp79;
  modelica_real tmp80;
  modelica_boolean tmp81;
  modelica_real tmp82;
  modelica_real tmp83;
  modelica_boolean tmp84;
  modelica_real tmp85;
  modelica_real tmp86;
  modelica_boolean tmp87;
  modelica_real tmp88;
  modelica_real tmp89;
  modelica_boolean tmp90;
  modelica_real tmp91;
  modelica_real tmp92;
  modelica_boolean tmp93;
  modelica_real tmp94;
  modelica_real tmp95;
  modelica_boolean tmp96;
  modelica_real tmp97;
  modelica_real tmp98;
  modelica_boolean tmp99;
  modelica_real tmp100;
  modelica_real tmp101;
  modelica_boolean tmp102;
  modelica_real tmp103;
  modelica_real tmp104;
  modelica_boolean tmp105;
  modelica_real tmp106;
  modelica_real tmp107;
  modelica_boolean tmp108;
  modelica_real tmp109;
  modelica_real tmp110;
  modelica_boolean tmp111;
  modelica_real tmp112;
  modelica_real tmp113;
  modelica_boolean tmp114;
  modelica_real tmp115;
  modelica_real tmp116;
  modelica_boolean tmp117;
  modelica_real tmp118;
  modelica_real tmp119;
  modelica_boolean tmp120;
  modelica_real tmp121;
  modelica_real tmp122;
  modelica_boolean tmp123;
  modelica_real tmp124;
  modelica_real tmp125;
  modelica_boolean tmp126;
  modelica_real tmp127;
  modelica_real tmp128;
  modelica_boolean tmp129;
  modelica_real tmp130;
  modelica_real tmp131;
  modelica_boolean tmp132;
  modelica_real tmp133;
  modelica_real tmp134;
  modelica_boolean tmp135;
  modelica_real tmp136;
  modelica_real tmp137;
  modelica_boolean tmp138;
  modelica_real tmp139;
  modelica_real tmp140;
  modelica_boolean tmp141;
  modelica_real tmp142;
  modelica_real tmp143;
  modelica_boolean tmp144;
  modelica_real tmp145;
  modelica_real tmp146;
  modelica_boolean tmp147;
  modelica_real tmp148;
  modelica_real tmp149;
  modelica_boolean tmp150;
  modelica_real tmp151;
  modelica_real tmp152;
  modelica_boolean tmp153;
  modelica_real tmp154;
  modelica_real tmp155;
  modelica_boolean tmp156;
  modelica_real tmp157;
  modelica_real tmp158;
  modelica_boolean tmp159;
  modelica_real tmp160;
  modelica_real tmp161;
  modelica_boolean tmp162;
  modelica_real tmp163;
  modelica_real tmp164;
  modelica_boolean tmp165;
  modelica_real tmp166;
  modelica_real tmp167;
  modelica_boolean tmp168;
  modelica_real tmp169;
  modelica_real tmp170;
  modelica_boolean tmp171;
  modelica_real tmp172;
  modelica_real tmp173;
  modelica_boolean tmp174;
  modelica_real tmp175;
  modelica_real tmp176;
  modelica_boolean tmp177;
  modelica_real tmp178;
  modelica_real tmp179;
  modelica_boolean tmp180;
  modelica_real tmp181;
  modelica_real tmp182;
  modelica_boolean tmp183;
  modelica_real tmp184;
  modelica_real tmp185;
  modelica_boolean tmp186;
  modelica_real tmp187;
  modelica_real tmp188;
  modelica_boolean tmp189;
  modelica_real tmp190;
  modelica_real tmp191;
  modelica_boolean tmp192;
  modelica_real tmp193;
  modelica_real tmp194;
  modelica_boolean tmp195;
  modelica_real tmp196;
  modelica_real tmp197;
  modelica_boolean tmp198;
  modelica_real tmp199;
  modelica_real tmp200;
  modelica_boolean tmp201;
  modelica_real tmp202;
  modelica_real tmp203;
  modelica_boolean tmp204;
  modelica_real tmp205;
  modelica_real tmp206;
  modelica_boolean tmp207;
  modelica_real tmp208;
  modelica_real tmp209;
  modelica_boolean tmp210;
  modelica_real tmp211;
  modelica_real tmp212;
  modelica_boolean tmp213;
  modelica_real tmp214;
  modelica_real tmp215;
  modelica_boolean tmp216;
  modelica_real tmp217;
  modelica_real tmp218;
  modelica_boolean tmp219;
  modelica_real tmp220;
  modelica_real tmp221;
  modelica_boolean tmp222;
  modelica_real tmp223;
  modelica_real tmp224;
  modelica_boolean tmp225;
  modelica_real tmp226;
  modelica_real tmp227;
  modelica_boolean tmp228;
  modelica_real tmp229;
  modelica_real tmp230;
  modelica_boolean tmp231;
  modelica_real tmp232;
  modelica_real tmp233;
  modelica_boolean tmp234;
  modelica_real tmp235;
  modelica_real tmp236;
  modelica_integer current_index = 0;
  modelica_integer start_index;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  start_index = current_index;
  tmp1 = 1.0;
  tmp2 = 1.0;
  tmp0 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */), tmp1, tmp2, data->simulationInfo->storedRelations[0]);
  gout[start_index] = (tmp0) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp4 = 1.0;
  tmp5 = 1.0;
  tmp3 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */), tmp4, tmp5, data->simulationInfo->storedRelations[1]);
  gout[start_index] = (tmp3) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp7 = 1.0;
  tmp8 = 1.0;
  tmp6 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */), tmp7, tmp8, data->simulationInfo->storedRelations[2]);
  gout[start_index] = (tmp6) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp10 = 1.0;
  tmp11 = 1.0;
  tmp9 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */), tmp10, tmp11, data->simulationInfo->storedRelations[3]);
  gout[start_index] = (tmp9) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp13 = 1.0;
  tmp14 = 1.0;
  tmp12 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */), tmp13, tmp14, data->simulationInfo->storedRelations[4]);
  gout[start_index] = (tmp12) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp16 = 1.0;
  tmp17 = 1.0;
  tmp15 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */), tmp16, tmp17, data->simulationInfo->storedRelations[5]);
  gout[start_index] = (tmp15) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp19 = 1.0;
  tmp20 = 1.0;
  tmp18 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */), tmp19, tmp20, data->simulationInfo->storedRelations[6]);
  gout[start_index] = (tmp18) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp22 = 1.0;
  tmp23 = 1.0;
  tmp21 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */), tmp22, tmp23, data->simulationInfo->storedRelations[7]);
  gout[start_index] = (tmp21) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp25 = 1.0;
  tmp26 = 1.0;
  tmp24 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */), tmp25, tmp26, data->simulationInfo->storedRelations[8]);
  gout[start_index] = (tmp24) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp28 = 1.0;
  tmp29 = 1.0;
  tmp27 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */), tmp28, tmp29, data->simulationInfo->storedRelations[9]);
  gout[start_index] = (tmp27) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp31 = 1.0;
  tmp32 = 1.0;
  tmp30 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */), tmp31, tmp32, data->simulationInfo->storedRelations[10]);
  gout[start_index] = (tmp30) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp34 = 1.0;
  tmp35 = 1.0;
  tmp33 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */), tmp34, tmp35, data->simulationInfo->storedRelations[11]);
  gout[start_index] = (tmp33) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp37 = 1.0;
  tmp38 = 1.0;
  tmp36 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */), tmp37, tmp38, data->simulationInfo->storedRelations[12]);
  gout[start_index] = (tmp36) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp40 = 1.0;
  tmp41 = 1.0;
  tmp39 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */), tmp40, tmp41, data->simulationInfo->storedRelations[13]);
  gout[start_index] = (tmp39) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp43 = 1.0;
  tmp44 = 1.0;
  tmp42 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */), tmp43, tmp44, data->simulationInfo->storedRelations[14]);
  gout[start_index] = (tmp42) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp46 = 1.0;
  tmp47 = 1.0;
  tmp45 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */), tmp46, tmp47, data->simulationInfo->storedRelations[15]);
  gout[start_index] = (tmp45) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp49 = 1.0;
  tmp50 = 1.0;
  tmp48 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */), tmp49, tmp50, data->simulationInfo->storedRelations[16]);
  gout[start_index] = (tmp48) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp52 = 1.0;
  tmp53 = 1.0;
  tmp51 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */), tmp52, tmp53, data->simulationInfo->storedRelations[17]);
  tmp55 = 1.0;
  tmp56 = 601.0;
  tmp54 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0, tmp55, tmp56, data->simulationInfo->storedRelations[18]);
  gout[start_index] = ((tmp51 && tmp54)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp58 = 1.0;
  tmp59 = 1.0;
  tmp57 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */), tmp58, tmp59, data->simulationInfo->storedRelations[19]);
  tmp61 = 1.0;
  tmp62 = 601.0;
  tmp60 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0, tmp61, tmp62, data->simulationInfo->storedRelations[20]);
  gout[start_index] = ((tmp57 && tmp60)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[221]] /* u1Fan variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 4))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 3))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 2))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 1))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 7) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 1) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp64 = 1.0;
  tmp65 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */));
  tmp63 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */), tmp64, tmp65, data->simulationInfo->storedRelations[27]);
  tmp67 = 1.0;
  tmp68 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */)) + 0.25;
  tmp66 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) + 0.25, tmp67, tmp68, data->simulationInfo->storedRelations[28]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */)) && tmp63) || ((data->simulationInfo->booleanVarsPre[152] /* damVal.lowMin.lesHys.y DISCRETE */) && tmp66))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp70 = 1.0;
  tmp71 = 0.25;
  tmp69 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.25, tmp70, tmp71, data->simulationInfo->storedRelations[29]);
  tmp73 = 1.0;
  tmp74 = 0.125;
  tmp72 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.125, tmp73, tmp74, data->simulationInfo->storedRelations[30]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */)) && tmp69) || ((data->simulationInfo->booleanVarsPre[147] /* damVal.greThr.greHys.y DISCRETE */) && tmp72))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp76 = 1.0;
  tmp77 = 1.0;
  tmp75 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */), tmp76, tmp77, data->simulationInfo->storedRelations[31]);
  tmp79 = 1.0;
  tmp80 = 1.25;
  tmp78 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) - 0.25, tmp79, tmp80, data->simulationInfo->storedRelations[32]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */)) && tmp75) || ((data->simulationInfo->booleanVarsPre[146] /* damVal.gre.greHys.y DISCRETE */) && tmp78))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp82 = 1.0;
  tmp83 = 1.0;
  tmp81 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), tmp82, tmp83, data->simulationInfo->storedRelations[33]);
  tmp85 = 1.0;
  tmp86 = 1.25;
  tmp84 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) - 0.25, tmp85, tmp86, data->simulationInfo->storedRelations[34]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */)) && tmp81) || ((data->simulationInfo->booleanVarsPre[168] /* setPoi.cooSup.greHys.y DISCRETE */) && tmp84))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((!((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1)))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((!(data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[224]] /* u1Win variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp88 = 1.0;
  tmp89 = 0.25;
  tmp87 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.25, tmp88, tmp89, data->simulationInfo->storedRelations[36]);
  tmp91 = 1.0;
  tmp92 = 0.125;
  tmp90 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.125, tmp91, tmp92, data->simulationInfo->storedRelations[37]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */)) && tmp87) || ((data->simulationInfo->booleanVarsPre[209] /* timSup.greThr.greHys.y DISCRETE */) && tmp90))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp94 = 1.0;
  tmp95 = fabs((data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */)) + 1.0;
  tmp93 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) + (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */), tmp94, tmp95, data->simulationInfo->storedRelations[38]);
  gout[start_index] = (((data->localData[0]->booleanVars[data->simulationInfo->booleanVarsIndex[210]] /* timSup.lat.y DISCRETE */) && tmp93)) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp97 = 1.0;
  tmp98 = 1.0;
  tmp96 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[189]] /* timSup.tim.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[186]] /* timSup.supTim.y variable */), tmp97, tmp98, data->simulationInfo->storedRelations[39]);
  gout[start_index] = (tmp96) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 2))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = (((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 1))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp100 = 1.0;
  tmp101 = 1.0;
  tmp99 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */), tmp100, tmp101, data->simulationInfo->storedRelations[42]);
  tmp103 = 1.0;
  tmp104 = 1.25;
  tmp102 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) - 0.25, tmp103, tmp104, data->simulationInfo->storedRelations[43]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */)) && tmp99) || ((data->simulationInfo->booleanVarsPre[97] /* ala.gre2.greHys.y DISCRETE */) && tmp102))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp106 = 1.0;
  tmp107 = 1.0;
  tmp105 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */), tmp106, tmp107, data->simulationInfo->storedRelations[44]);
  tmp109 = 1.0;
  tmp110 = 1.005;
  tmp108 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) - 0.005, tmp109, tmp110, data->simulationInfo->storedRelations[45]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */)) && tmp105) || ((data->simulationInfo->booleanVarsPre[96] /* ala.gre1.greHys.y DISCRETE */) && tmp108))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp112 = 1.0;
  tmp113 = 1.0;
  tmp111 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), tmp112, tmp113, data->simulationInfo->storedRelations[46]);
  tmp115 = 1.0;
  tmp116 = 1.25;
  tmp114 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) + 0.25, tmp115, tmp116, data->simulationInfo->storedRelations[47]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */)) && tmp111) || ((data->simulationInfo->booleanVarsPre[133] /* conLoo.enaCooLoo.lesHys.y DISCRETE */) && tmp114))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp118 = 1.0;
  tmp119 = 1.0;
  tmp117 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */), tmp118, tmp119, data->simulationInfo->storedRelations[48]);
  tmp121 = 1.0;
  tmp122 = 1.25;
  tmp120 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + 0.25, tmp121, tmp122, data->simulationInfo->storedRelations[49]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */)) && tmp117) || ((data->simulationInfo->booleanVarsPre[134] /* conLoo.enaHeaLoo.lesHys.y DISCRETE */) && tmp120))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp124 = 1.0;
  tmp125 = 0.01;
  tmp123 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.01, tmp124, tmp125, data->simulationInfo->storedRelations[50]);
  tmp127 = 1.0;
  tmp128 = 0.018000000000000002;
  tmp126 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.018000000000000002, tmp127, tmp128, data->simulationInfo->storedRelations[51]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */)) && tmp123) || ((data->simulationInfo->booleanVarsPre[136] /* conLoo.zerCon1.lesHys.y DISCRETE */) && tmp126))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp130 = 1.0;
  tmp131 = 0.01;
  tmp129 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.01, tmp130, tmp131, data->simulationInfo->storedRelations[52]);
  tmp133 = 1.0;
  tmp134 = 0.002;
  tmp132 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.002, tmp133, tmp134, data->simulationInfo->storedRelations[53]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */)) && tmp129) || ((data->simulationInfo->booleanVarsPre[149] /* damVal.greThr2.greHys.y DISCRETE */) && tmp132))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp136 = 1.0;
  tmp137 = 1.0;
  tmp135 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */), tmp136, tmp137, data->simulationInfo->storedRelations[54]);
  tmp139 = 1.0;
  tmp140 = 1.25;
  tmp138 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) + 0.25, tmp139, tmp140, data->simulationInfo->storedRelations[55]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */)) && tmp135) || ((data->simulationInfo->booleanVarsPre[105] /* ala.les1.lesHys.y DISCRETE */) && tmp138))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp142 = 1.0;
  tmp143 = 1.0;
  tmp141 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */), tmp142, tmp143, data->simulationInfo->storedRelations[56]);
  tmp145 = 1.0;
  tmp146 = 1.25;
  tmp144 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) + 0.25, tmp145, tmp146, data->simulationInfo->storedRelations[57]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */)) && tmp141) || ((data->simulationInfo->booleanVarsPre[106] /* ala.les2.lesHys.y DISCRETE */) && tmp144))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp148 = 1.0;
  tmp149 = 0.005;
  tmp147 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.005, tmp148, tmp149, data->simulationInfo->storedRelations[58]);
  tmp151 = 1.0;
  tmp152 = 0.0075;
  tmp150 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.0075, tmp151, tmp152, data->simulationInfo->storedRelations[59]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */)) && tmp147) || ((data->simulationInfo->booleanVarsPre[91] /* ala.cloVal.lesHys.y DISCRETE */) && tmp150))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp154 = 1.0;
  tmp155 = 0.01;
  tmp153 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.01, tmp154, tmp155, data->simulationInfo->storedRelations[60]);
  tmp157 = 1.0;
  tmp158 = 0.018000000000000002;
  tmp156 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.018000000000000002, tmp157, tmp158, data->simulationInfo->storedRelations[61]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */)) && tmp153) || ((data->simulationInfo->booleanVarsPre[135] /* conLoo.zerCon.lesHys.y DISCRETE */) && tmp156))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp160 = 1.0;
  tmp161 = 0.01;
  tmp159 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.01, tmp160, tmp161, data->simulationInfo->storedRelations[62]);
  tmp163 = 1.0;
  tmp164 = 0.005;
  tmp162 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.005, tmp163, tmp164, data->simulationInfo->storedRelations[63]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */)) && tmp159) || ((data->simulationInfo->booleanVarsPre[148] /* damVal.greThr1.greHys.y DISCRETE */) && tmp162))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp166 = 1.0;
  tmp167 = 0.95;
  tmp165 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.95, tmp166, tmp167, data->simulationInfo->storedRelations[64]);
  tmp169 = 1.0;
  tmp170 = 0.09999999999999998;
  tmp168 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.09999999999999998, tmp169, tmp170, data->simulationInfo->storedRelations[65]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */)) && tmp165) || ((data->simulationInfo->booleanVarsPre[184] /* sysReq.greThr6.greHys.y DISCRETE */) && tmp168))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp172 = 1.0;
  tmp173 = 0.95;
  tmp171 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.95, tmp172, tmp173, data->simulationInfo->storedRelations[64]);
  tmp175 = 1.0;
  tmp176 = 0.945;
  tmp174 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.945, tmp175, tmp176, data->simulationInfo->storedRelations[66]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */)) && tmp171) || ((data->simulationInfo->booleanVarsPre[183] /* sysReq.greThr5.greHys.y DISCRETE */) && tmp174))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp178 = 1.0;
  tmp179 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */));
  tmp177 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */), tmp178, tmp179, data->simulationInfo->storedRelations[67]);
  tmp181 = 1.0;
  tmp182 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */)) + 0.25;
  tmp180 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */) - 0.25, tmp181, tmp182, data->simulationInfo->storedRelations[68]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */)) && tmp177) || ((data->simulationInfo->booleanVarsPre[180] /* sysReq.greThr2.greHys.y DISCRETE */) && tmp180))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp184 = 1.0;
  tmp185 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */));
  tmp183 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */), tmp184, tmp185, data->simulationInfo->storedRelations[69]);
  tmp187 = 1.0;
  tmp188 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */)) + 0.25;
  tmp186 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */) - 0.25, tmp187, tmp188, data->simulationInfo->storedRelations[70]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */)) && tmp183) || ((data->simulationInfo->booleanVarsPre[179] /* sysReq.greThr1.greHys.y DISCRETE */) && tmp186))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp190 = 1.0;
  tmp191 = 1.0;
  tmp189 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp190, tmp191, data->simulationInfo->storedRelations[71]);
  tmp193 = 1.0;
  tmp194 = 1.25;
  tmp192 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp193, tmp194, data->simulationInfo->storedRelations[72]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */)) && tmp189) || ((data->simulationInfo->booleanVarsPre[186] /* sysReq.les1.lesHys.y DISCRETE */) && tmp192))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp196 = 1.0;
  tmp197 = 1.0;
  tmp195 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp196, tmp197, data->simulationInfo->storedRelations[73]);
  tmp199 = 1.0;
  tmp200 = 1.25;
  tmp198 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp199, tmp200, data->simulationInfo->storedRelations[74]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */)) && tmp195) || ((data->simulationInfo->booleanVarsPre[185] /* sysReq.les.lesHys.y DISCRETE */) && tmp198))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 5) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 4) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 3) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  gout[start_index] = ((((modelica_integer) 2) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp202 = 1.0;
  tmp203 = 1.0;
  tmp201 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */), tmp202, tmp203, data->simulationInfo->storedRelations[79]);
  tmp205 = 1.0;
  tmp206 = 1.005;
  tmp204 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) + 0.005, tmp205, tmp206, data->simulationInfo->storedRelations[80]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */)) && tmp201) || ((data->simulationInfo->booleanVarsPre[104] /* ala.les.lesHys.y DISCRETE */) && tmp204))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp208 = 1.0;
  tmp209 = 0.005;
  tmp207 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.005, tmp208, tmp209, data->simulationInfo->storedRelations[81]);
  tmp211 = 1.0;
  tmp212 = 0.0025;
  tmp210 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.0025, tmp211, tmp212, data->simulationInfo->storedRelations[82]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */)) && tmp207) || ((data->simulationInfo->booleanVarsPre[98] /* ala.greThr.greHys.y DISCRETE */) && tmp210))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp214 = 1.0;
  tmp215 = 1.0;
  tmp213 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), tmp214, tmp215, data->simulationInfo->storedRelations[83]);
  tmp217 = 1.0;
  tmp218 = 1.005;
  tmp216 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) - 0.005, tmp217, tmp218, data->simulationInfo->storedRelations[84]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */)) && tmp213) || ((data->simulationInfo->booleanVarsPre[95] /* ala.gre.greHys.y DISCRETE */) && tmp216))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp220 = 1.0;
  tmp221 = 0.005;
  tmp219 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.005, tmp220, tmp221, data->simulationInfo->storedRelations[85]);
  tmp223 = 1.0;
  tmp224 = 0.0075;
  tmp222 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.0075, tmp223, tmp224, data->simulationInfo->storedRelations[86]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */)) && tmp219) || ((data->simulationInfo->booleanVarsPre[90] /* ala.cloDam.lesHys.y DISCRETE */) && tmp222))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp226 = 1.0;
  tmp227 = 1.0;
  tmp225 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp226, tmp227, data->simulationInfo->storedRelations[87]);
  tmp229 = 1.0;
  tmp230 = 1.005;
  tmp228 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp229, tmp230, data->simulationInfo->storedRelations[88]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */)) && tmp225) || ((data->simulationInfo->booleanVarsPre[176] /* sysReq.greEqu.greHys.y DISCRETE */) && tmp228))) ? 1 : -1;
  current_index++;

  start_index = current_index;
  tmp232 = 1.0;
  tmp233 = 1.0;
  tmp231 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp232, tmp233, data->simulationInfo->storedRelations[89]);
  tmp235 = 1.0;
  tmp236 = 1.005;
  tmp234 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp235, tmp236, data->simulationInfo->storedRelations[90]);
  gout[start_index] = ((((!(data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */)) && tmp231) || ((data->simulationInfo->booleanVarsPre[177] /* sysReq.greEqu1.greHys.y DISCRETE */) && tmp234))) ? 1 : -1;
  current_index++;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *ReheatControllerFMU_relationDescription(int i)
{
  const char *res[] = {"time >= pre(sysReq.tim1.t_next)",
  "time >= pre(sysReq.tim2.t_next)",
  "time >= pre(sysReq.tim3.t_next)",
  "time >= pre(sysReq.tim4.t_next)",
  "time >= pre(sysReq.tim5.t_next)",
  "time >= pre(conLoo.disCoo.t_next)",
  "time >= pre(conLoo.disHea.t_next)",
  "time >= pre(ala.truDel.t_next)",
  "time >= pre(ala.truDel1.t_next)",
  "time >= pre(ala.truDel2.t_next)",
  "time >= pre(ala.truDel3.t_next)",
  "time >= pre(ala.truDel4.t_next)",
  "time >= pre(ala.truDel5.t_next)",
  "time >= pre(ala.truDel6.t_next)",
  "time >= pre(ala.truDel7.t_next)",
  "time >= pre(ala.fanIni.t_next)",
  "time >= pre(timSup.truDel.t_next)",
  "time >= pre(damVal.truFalHol.entryTimeFalse)",
  "time >= pre(damVal.truFalHol.entryTimeTrue) + 600.0",
  "time >= pre(damVal.truFalHol1.entryTimeFalse)",
  "time >= pre(damVal.truFalHol1.entryTimeTrue) + 600.0",
  "oveFloSet == 4",
  "oveFloSet == 3",
  "oveFloSet == 2",
  "oveFloSet == 1",
  "7 == uOpeMod",
  "1 == uOpeMod",
  "TDis < damVal.lowMin.lesHys.t",
  "TDis < damVal.lowMin.lesHys.t + 0.25",
  "damVal.sub2.y > 0.25",
  "damVal.sub2.y > 0.125",
  "TDis > damVal.addPar1.y",
  "TDis > damVal.addPar1.y - 0.25",
  "TZon > TDis",
  "TZon > TDis - 0.25",
  "uOpeMod == 1",
  "timSup.abs1.y > 0.25",
  "timSup.abs1.y > 0.125",
  "time >= timSup.tim.t + pre(timSup.tim.entryTime)",
  "timSup.tim.y > timSup.supTim.y",
  "oveDamPos == 2",
  "oveDamPos == 1",
  "TDis > ala.addPar2.y",
  "TDis > ala.addPar2.y - 0.25",
  "VDis_flow > ala.gai2.y",
  "VDis_flow > ala.gai2.y - 0.005",
  "TCooSet < TZon",
  "TCooSet < TZon + 0.25",
  "TZon < THeaSet",
  "TZon < THeaSet + 0.25",
  "conLoo.conHea.y < 0.01",
  "conLoo.conHea.y < 0.018000000000000002",
  "conLoo.yHea > 0.01",
  "conLoo.yHea > 0.002",
  "TDis < ala.addPar.y",
  "TDis < ala.addPar.y + 0.25",
  "TDis < ala.addPar1.y",
  "TDis < ala.addPar1.y + 0.25",
  "yVal < 0.005",
  "yVal < 0.0075",
  "conLoo.conCoo.y < 0.01",
  "conLoo.conCoo.y < 0.018000000000000002",
  "conLoo.yCoo > 0.01",
  "conLoo.yCoo > 0.005",
  "yVal > 0.95",
  "yVal > 0.09999999999999998",
  "yVal > 0.945",
  "sysReq.sub3.y > sysReq.greThr2.greHys.t",
  "sysReq.sub3.y > sysReq.greThr2.greHys.t - 0.25",
  "sysReq.sub2.y > sysReq.greThr1.greHys.t",
  "sysReq.sub2.y > sysReq.greThr1.greHys.t - 0.25",
  "sysReq.addPar1.y < damVal.TDisSet",
  "sysReq.addPar1.y < damVal.TDisSet + 0.25",
  "sysReq.addPar.y < damVal.TDisSet",
  "sysReq.addPar.y < damVal.TDisSet + 0.25",
  "5 == uOpeMod",
  "4 == uOpeMod",
  "3 == uOpeMod",
  "2 == uOpeMod",
  "VDis_flow < ala.gai.y",
  "VDis_flow < ala.gai.y + 0.005",
  "VSet_flow > 0.005",
  "VSet_flow > 0.0025",
  "ala.gai1.y > VDis_flow",
  "ala.gai1.y > VDis_flow - 0.005",
  "yDam < 0.005",
  "yDam < 0.0075",
  "sysReq.greEqu.u1 > sysReq.sampler2.y",
  "sysReq.greEqu.u1 > sysReq.sampler2.y - 0.005",
  "sysReq.gai2.y > sysReq.sampler2.y",
  "sysReq.gai2.y > sysReq.sampler2.y - 0.005"};
  return res[i];
}

int ReheatControllerFMU_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;

  modelica_boolean tmp237;
  modelica_real tmp238;
  modelica_real tmp239;
  modelica_boolean tmp240;
  modelica_real tmp241;
  modelica_real tmp242;
  modelica_boolean tmp243;
  modelica_real tmp244;
  modelica_real tmp245;
  modelica_boolean tmp246;
  modelica_real tmp247;
  modelica_real tmp248;
  modelica_boolean tmp249;
  modelica_real tmp250;
  modelica_real tmp251;
  modelica_boolean tmp252;
  modelica_real tmp253;
  modelica_real tmp254;
  modelica_boolean tmp255;
  modelica_real tmp256;
  modelica_real tmp257;
  modelica_boolean tmp258;
  modelica_real tmp259;
  modelica_real tmp260;
  modelica_boolean tmp261;
  modelica_real tmp262;
  modelica_real tmp263;
  modelica_boolean tmp264;
  modelica_real tmp265;
  modelica_real tmp266;
  modelica_boolean tmp267;
  modelica_real tmp268;
  modelica_real tmp269;
  modelica_boolean tmp270;
  modelica_real tmp271;
  modelica_real tmp272;
  modelica_boolean tmp273;
  modelica_real tmp274;
  modelica_real tmp275;
  modelica_boolean tmp276;
  modelica_real tmp277;
  modelica_real tmp278;
  modelica_boolean tmp279;
  modelica_real tmp280;
  modelica_real tmp281;
  modelica_boolean tmp282;
  modelica_real tmp283;
  modelica_real tmp284;
  modelica_boolean tmp285;
  modelica_real tmp286;
  modelica_real tmp287;
  modelica_boolean tmp288;
  modelica_real tmp289;
  modelica_real tmp290;
  modelica_boolean tmp291;
  modelica_real tmp292;
  modelica_real tmp293;
  modelica_boolean tmp294;
  modelica_real tmp295;
  modelica_real tmp296;
  modelica_boolean tmp297;
  modelica_real tmp298;
  modelica_real tmp299;
  modelica_boolean tmp300;
  modelica_real tmp301;
  modelica_real tmp302;
  modelica_boolean tmp303;
  modelica_real tmp304;
  modelica_real tmp305;
  modelica_boolean tmp306;
  modelica_real tmp307;
  modelica_real tmp308;
  modelica_boolean tmp309;
  modelica_real tmp310;
  modelica_real tmp311;
  modelica_boolean tmp312;
  modelica_real tmp313;
  modelica_real tmp314;
  modelica_boolean tmp315;
  modelica_real tmp316;
  modelica_real tmp317;
  modelica_boolean tmp318;
  modelica_real tmp319;
  modelica_real tmp320;
  modelica_boolean tmp321;
  modelica_real tmp322;
  modelica_real tmp323;
  modelica_boolean tmp324;
  modelica_real tmp325;
  modelica_real tmp326;
  modelica_boolean tmp327;
  modelica_real tmp328;
  modelica_real tmp329;
  modelica_boolean tmp330;
  modelica_real tmp331;
  modelica_real tmp332;
  modelica_boolean tmp333;
  modelica_real tmp334;
  modelica_real tmp335;
  modelica_boolean tmp336;
  modelica_real tmp337;
  modelica_real tmp338;
  modelica_boolean tmp339;
  modelica_real tmp340;
  modelica_real tmp341;
  modelica_boolean tmp342;
  modelica_real tmp343;
  modelica_real tmp344;
  modelica_boolean tmp345;
  modelica_real tmp346;
  modelica_real tmp347;
  modelica_boolean tmp348;
  modelica_real tmp349;
  modelica_real tmp350;
  modelica_boolean tmp351;
  modelica_real tmp352;
  modelica_real tmp353;
  modelica_boolean tmp354;
  modelica_real tmp355;
  modelica_real tmp356;
  modelica_boolean tmp357;
  modelica_real tmp358;
  modelica_real tmp359;
  modelica_boolean tmp360;
  modelica_real tmp361;
  modelica_real tmp362;
  modelica_boolean tmp363;
  modelica_real tmp364;
  modelica_real tmp365;
  modelica_boolean tmp366;
  modelica_real tmp367;
  modelica_real tmp368;
  modelica_boolean tmp369;
  modelica_real tmp370;
  modelica_real tmp371;
  modelica_boolean tmp372;
  modelica_real tmp373;
  modelica_real tmp374;
  modelica_boolean tmp375;
  modelica_real tmp376;
  modelica_real tmp377;
  modelica_boolean tmp378;
  modelica_real tmp379;
  modelica_real tmp380;
  modelica_boolean tmp381;
  modelica_real tmp382;
  modelica_real tmp383;
  modelica_boolean tmp384;
  modelica_real tmp385;
  modelica_real tmp386;
  modelica_boolean tmp387;
  modelica_real tmp388;
  modelica_real tmp389;
  modelica_boolean tmp390;
  modelica_real tmp391;
  modelica_real tmp392;
  modelica_boolean tmp393;
  modelica_real tmp394;
  modelica_real tmp395;
  modelica_boolean tmp396;
  modelica_real tmp397;
  modelica_real tmp398;
  modelica_boolean tmp399;
  modelica_real tmp400;
  modelica_real tmp401;
  modelica_boolean tmp402;
  modelica_real tmp403;
  modelica_real tmp404;
  modelica_boolean tmp405;
  modelica_real tmp406;
  modelica_real tmp407;
  modelica_boolean tmp408;
  modelica_real tmp409;
  modelica_real tmp410;
  modelica_boolean tmp411;
  modelica_real tmp412;
  modelica_real tmp413;
  modelica_boolean tmp414;
  modelica_real tmp415;
  modelica_real tmp416;
  modelica_boolean tmp417;
  modelica_real tmp418;
  modelica_real tmp419;
  modelica_boolean tmp420;
  modelica_real tmp421;
  modelica_real tmp422;
  modelica_boolean tmp423;
  modelica_real tmp424;
  modelica_real tmp425;
  modelica_boolean tmp426;
  modelica_real tmp427;
  modelica_real tmp428;
  modelica_boolean tmp429;
  modelica_real tmp430;
  modelica_real tmp431;
  modelica_boolean tmp432;
  modelica_real tmp433;
  modelica_real tmp434;
  modelica_boolean tmp435;
  modelica_real tmp436;
  modelica_real tmp437;
  modelica_boolean tmp438;
  modelica_real tmp439;
  modelica_real tmp440;
  modelica_boolean tmp441;
  modelica_real tmp442;
  modelica_real tmp443;
  modelica_boolean tmp444;
  modelica_real tmp445;
  modelica_real tmp446;
  modelica_boolean tmp447;
  modelica_real tmp448;
  modelica_real tmp449;
  modelica_boolean tmp450;
  modelica_real tmp451;
  modelica_real tmp452;
  modelica_boolean tmp453;
  modelica_real tmp454;
  modelica_real tmp455;
  modelica_boolean tmp456;
  modelica_real tmp457;
  modelica_real tmp458;
  modelica_boolean tmp459;
  modelica_real tmp460;
  modelica_real tmp461;
  modelica_boolean tmp462;
  modelica_real tmp463;
  modelica_real tmp464;
  modelica_boolean tmp465;
  modelica_real tmp466;
  modelica_real tmp467;
  modelica_boolean tmp468;
  modelica_real tmp469;
  modelica_real tmp470;
  modelica_integer current_index = 0;
  modelica_integer start_index;

  if(evalforZeroCross) {
    start_index = current_index;
    tmp238 = 1.0;
    tmp239 = 1.0;
    tmp237 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */), tmp238, tmp239, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[start_index] = tmp237;
    current_index++;

    start_index = current_index;
    tmp241 = 1.0;
    tmp242 = 1.0;
    tmp240 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */), tmp241, tmp242, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[start_index] = tmp240;
    current_index++;

    start_index = current_index;
    tmp244 = 1.0;
    tmp245 = 1.0;
    tmp243 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */), tmp244, tmp245, data->simulationInfo->storedRelations[2]);
    data->simulationInfo->relations[start_index] = tmp243;
    current_index++;

    start_index = current_index;
    tmp247 = 1.0;
    tmp248 = 1.0;
    tmp246 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */), tmp247, tmp248, data->simulationInfo->storedRelations[3]);
    data->simulationInfo->relations[start_index] = tmp246;
    current_index++;

    start_index = current_index;
    tmp250 = 1.0;
    tmp251 = 1.0;
    tmp249 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */), tmp250, tmp251, data->simulationInfo->storedRelations[4]);
    data->simulationInfo->relations[start_index] = tmp249;
    current_index++;

    start_index = current_index;
    tmp253 = 1.0;
    tmp254 = 1.0;
    tmp252 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */), tmp253, tmp254, data->simulationInfo->storedRelations[5]);
    data->simulationInfo->relations[start_index] = tmp252;
    current_index++;

    start_index = current_index;
    tmp256 = 1.0;
    tmp257 = 1.0;
    tmp255 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */), tmp256, tmp257, data->simulationInfo->storedRelations[6]);
    data->simulationInfo->relations[start_index] = tmp255;
    current_index++;

    start_index = current_index;
    tmp259 = 1.0;
    tmp260 = 1.0;
    tmp258 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */), tmp259, tmp260, data->simulationInfo->storedRelations[7]);
    data->simulationInfo->relations[start_index] = tmp258;
    current_index++;

    start_index = current_index;
    tmp262 = 1.0;
    tmp263 = 1.0;
    tmp261 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */), tmp262, tmp263, data->simulationInfo->storedRelations[8]);
    data->simulationInfo->relations[start_index] = tmp261;
    current_index++;

    start_index = current_index;
    tmp265 = 1.0;
    tmp266 = 1.0;
    tmp264 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */), tmp265, tmp266, data->simulationInfo->storedRelations[9]);
    data->simulationInfo->relations[start_index] = tmp264;
    current_index++;

    start_index = current_index;
    tmp268 = 1.0;
    tmp269 = 1.0;
    tmp267 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */), tmp268, tmp269, data->simulationInfo->storedRelations[10]);
    data->simulationInfo->relations[start_index] = tmp267;
    current_index++;

    start_index = current_index;
    tmp271 = 1.0;
    tmp272 = 1.0;
    tmp270 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */), tmp271, tmp272, data->simulationInfo->storedRelations[11]);
    data->simulationInfo->relations[start_index] = tmp270;
    current_index++;

    start_index = current_index;
    tmp274 = 1.0;
    tmp275 = 1.0;
    tmp273 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */), tmp274, tmp275, data->simulationInfo->storedRelations[12]);
    data->simulationInfo->relations[start_index] = tmp273;
    current_index++;

    start_index = current_index;
    tmp277 = 1.0;
    tmp278 = 1.0;
    tmp276 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */), tmp277, tmp278, data->simulationInfo->storedRelations[13]);
    data->simulationInfo->relations[start_index] = tmp276;
    current_index++;

    start_index = current_index;
    tmp280 = 1.0;
    tmp281 = 1.0;
    tmp279 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */), tmp280, tmp281, data->simulationInfo->storedRelations[14]);
    data->simulationInfo->relations[start_index] = tmp279;
    current_index++;

    start_index = current_index;
    tmp283 = 1.0;
    tmp284 = 1.0;
    tmp282 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */), tmp283, tmp284, data->simulationInfo->storedRelations[15]);
    data->simulationInfo->relations[start_index] = tmp282;
    current_index++;

    start_index = current_index;
    tmp286 = 1.0;
    tmp287 = 1.0;
    tmp285 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */), tmp286, tmp287, data->simulationInfo->storedRelations[16]);
    data->simulationInfo->relations[start_index] = tmp285;
    current_index++;

    start_index = current_index;
    tmp289 = 1.0;
    tmp290 = 1.0;
    tmp288 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */), tmp289, tmp290, data->simulationInfo->storedRelations[17]);
    data->simulationInfo->relations[start_index] = tmp288;
    current_index++;

    start_index = current_index;
    tmp292 = 1.0;
    tmp293 = 601.0;
    tmp291 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0, tmp292, tmp293, data->simulationInfo->storedRelations[18]);
    data->simulationInfo->relations[start_index] = tmp291;
    current_index++;

    start_index = current_index;
    tmp295 = 1.0;
    tmp296 = 1.0;
    tmp294 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */), tmp295, tmp296, data->simulationInfo->storedRelations[19]);
    data->simulationInfo->relations[start_index] = tmp294;
    current_index++;

    start_index = current_index;
    tmp298 = 1.0;
    tmp299 = 601.0;
    tmp297 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0, tmp298, tmp299, data->simulationInfo->storedRelations[20]);
    data->simulationInfo->relations[start_index] = tmp297;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 4));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 3));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 7) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 1) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    tmp301 = 1.0;
    tmp302 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */));
    tmp300 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */), tmp301, tmp302, data->simulationInfo->storedRelations[27]);
    data->simulationInfo->relations[start_index] = tmp300;
    current_index++;

    start_index = current_index;
    tmp304 = 1.0;
    tmp305 = fabs((data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */)) + 0.25;
    tmp303 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) + 0.25, tmp304, tmp305, data->simulationInfo->storedRelations[28]);
    data->simulationInfo->relations[start_index] = tmp303;
    current_index++;

    start_index = current_index;
    tmp307 = 1.0;
    tmp308 = 0.25;
    tmp306 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.25, tmp307, tmp308, data->simulationInfo->storedRelations[29]);
    data->simulationInfo->relations[start_index] = tmp306;
    current_index++;

    start_index = current_index;
    tmp310 = 1.0;
    tmp311 = 0.125;
    tmp309 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */), 0.125, tmp310, tmp311, data->simulationInfo->storedRelations[30]);
    data->simulationInfo->relations[start_index] = tmp309;
    current_index++;

    start_index = current_index;
    tmp313 = 1.0;
    tmp314 = 1.0;
    tmp312 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */), tmp313, tmp314, data->simulationInfo->storedRelations[31]);
    data->simulationInfo->relations[start_index] = tmp312;
    current_index++;

    start_index = current_index;
    tmp316 = 1.0;
    tmp317 = 1.25;
    tmp315 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) - 0.25, tmp316, tmp317, data->simulationInfo->storedRelations[32]);
    data->simulationInfo->relations[start_index] = tmp315;
    current_index++;

    start_index = current_index;
    tmp319 = 1.0;
    tmp320 = 1.0;
    tmp318 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), tmp319, tmp320, data->simulationInfo->storedRelations[33]);
    data->simulationInfo->relations[start_index] = tmp318;
    current_index++;

    start_index = current_index;
    tmp322 = 1.0;
    tmp323 = 1.25;
    tmp321 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) - 0.25, tmp322, tmp323, data->simulationInfo->storedRelations[34]);
    data->simulationInfo->relations[start_index] = tmp321;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    tmp325 = 1.0;
    tmp326 = 0.25;
    tmp324 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.25, tmp325, tmp326, data->simulationInfo->storedRelations[36]);
    data->simulationInfo->relations[start_index] = tmp324;
    current_index++;

    start_index = current_index;
    tmp328 = 1.0;
    tmp329 = 0.125;
    tmp327 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */), 0.125, tmp328, tmp329, data->simulationInfo->storedRelations[37]);
    data->simulationInfo->relations[start_index] = tmp327;
    current_index++;

    start_index = current_index;
    tmp331 = 1.0;
    tmp332 = fabs((data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */)) + 1.0;
    tmp330 = GreaterEqZC(data->localData[0]->timeValue, (data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) + (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */), tmp331, tmp332, data->simulationInfo->storedRelations[38]);
    data->simulationInfo->relations[start_index] = tmp330;
    current_index++;

    start_index = current_index;
    tmp334 = 1.0;
    tmp335 = 1.0;
    tmp333 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[189]] /* timSup.tim.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[186]] /* timSup.supTim.y variable */), tmp334, tmp335, data->simulationInfo->storedRelations[39]);
    data->simulationInfo->relations[start_index] = tmp333;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    tmp337 = 1.0;
    tmp338 = 1.0;
    tmp336 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */), tmp337, tmp338, data->simulationInfo->storedRelations[42]);
    data->simulationInfo->relations[start_index] = tmp336;
    current_index++;

    start_index = current_index;
    tmp340 = 1.0;
    tmp341 = 1.25;
    tmp339 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) - 0.25, tmp340, tmp341, data->simulationInfo->storedRelations[43]);
    data->simulationInfo->relations[start_index] = tmp339;
    current_index++;

    start_index = current_index;
    tmp343 = 1.0;
    tmp344 = 1.0;
    tmp342 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */), tmp343, tmp344, data->simulationInfo->storedRelations[44]);
    data->simulationInfo->relations[start_index] = tmp342;
    current_index++;

    start_index = current_index;
    tmp346 = 1.0;
    tmp347 = 1.005;
    tmp345 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) - 0.005, tmp346, tmp347, data->simulationInfo->storedRelations[45]);
    data->simulationInfo->relations[start_index] = tmp345;
    current_index++;

    start_index = current_index;
    tmp349 = 1.0;
    tmp350 = 1.0;
    tmp348 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), tmp349, tmp350, data->simulationInfo->storedRelations[46]);
    data->simulationInfo->relations[start_index] = tmp348;
    current_index++;

    start_index = current_index;
    tmp352 = 1.0;
    tmp353 = 1.25;
    tmp351 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) + 0.25, tmp352, tmp353, data->simulationInfo->storedRelations[47]);
    data->simulationInfo->relations[start_index] = tmp351;
    current_index++;

    start_index = current_index;
    tmp355 = 1.0;
    tmp356 = 1.0;
    tmp354 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */), tmp355, tmp356, data->simulationInfo->storedRelations[48]);
    data->simulationInfo->relations[start_index] = tmp354;
    current_index++;

    start_index = current_index;
    tmp358 = 1.0;
    tmp359 = 1.25;
    tmp357 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + 0.25, tmp358, tmp359, data->simulationInfo->storedRelations[49]);
    data->simulationInfo->relations[start_index] = tmp357;
    current_index++;

    start_index = current_index;
    tmp361 = 1.0;
    tmp362 = 0.01;
    tmp360 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.01, tmp361, tmp362, data->simulationInfo->storedRelations[50]);
    data->simulationInfo->relations[start_index] = tmp360;
    current_index++;

    start_index = current_index;
    tmp364 = 1.0;
    tmp365 = 0.018000000000000002;
    tmp363 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */), 0.018000000000000002, tmp364, tmp365, data->simulationInfo->storedRelations[51]);
    data->simulationInfo->relations[start_index] = tmp363;
    current_index++;

    start_index = current_index;
    tmp367 = 1.0;
    tmp368 = 0.01;
    tmp366 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.01, tmp367, tmp368, data->simulationInfo->storedRelations[52]);
    data->simulationInfo->relations[start_index] = tmp366;
    current_index++;

    start_index = current_index;
    tmp370 = 1.0;
    tmp371 = 0.002;
    tmp369 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), 0.002, tmp370, tmp371, data->simulationInfo->storedRelations[53]);
    data->simulationInfo->relations[start_index] = tmp369;
    current_index++;

    start_index = current_index;
    tmp373 = 1.0;
    tmp374 = 1.0;
    tmp372 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */), tmp373, tmp374, data->simulationInfo->storedRelations[54]);
    data->simulationInfo->relations[start_index] = tmp372;
    current_index++;

    start_index = current_index;
    tmp376 = 1.0;
    tmp377 = 1.25;
    tmp375 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) + 0.25, tmp376, tmp377, data->simulationInfo->storedRelations[55]);
    data->simulationInfo->relations[start_index] = tmp375;
    current_index++;

    start_index = current_index;
    tmp379 = 1.0;
    tmp380 = 1.0;
    tmp378 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */), tmp379, tmp380, data->simulationInfo->storedRelations[56]);
    data->simulationInfo->relations[start_index] = tmp378;
    current_index++;

    start_index = current_index;
    tmp382 = 1.0;
    tmp383 = 1.25;
    tmp381 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) + 0.25, tmp382, tmp383, data->simulationInfo->storedRelations[57]);
    data->simulationInfo->relations[start_index] = tmp381;
    current_index++;

    start_index = current_index;
    tmp385 = 1.0;
    tmp386 = 0.005;
    tmp384 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.005, tmp385, tmp386, data->simulationInfo->storedRelations[58]);
    data->simulationInfo->relations[start_index] = tmp384;
    current_index++;

    start_index = current_index;
    tmp388 = 1.0;
    tmp389 = 0.0075;
    tmp387 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.0075, tmp388, tmp389, data->simulationInfo->storedRelations[59]);
    data->simulationInfo->relations[start_index] = tmp387;
    current_index++;

    start_index = current_index;
    tmp391 = 1.0;
    tmp392 = 0.01;
    tmp390 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.01, tmp391, tmp392, data->simulationInfo->storedRelations[60]);
    data->simulationInfo->relations[start_index] = tmp390;
    current_index++;

    start_index = current_index;
    tmp394 = 1.0;
    tmp395 = 0.018000000000000002;
    tmp393 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */), 0.018000000000000002, tmp394, tmp395, data->simulationInfo->storedRelations[61]);
    data->simulationInfo->relations[start_index] = tmp393;
    current_index++;

    start_index = current_index;
    tmp397 = 1.0;
    tmp398 = 0.01;
    tmp396 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.01, tmp397, tmp398, data->simulationInfo->storedRelations[62]);
    data->simulationInfo->relations[start_index] = tmp396;
    current_index++;

    start_index = current_index;
    tmp400 = 1.0;
    tmp401 = 0.005;
    tmp399 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), 0.005, tmp400, tmp401, data->simulationInfo->storedRelations[63]);
    data->simulationInfo->relations[start_index] = tmp399;
    current_index++;

    start_index = current_index;
    tmp403 = 1.0;
    tmp404 = 0.95;
    tmp402 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.95, tmp403, tmp404, data->simulationInfo->storedRelations[64]);
    data->simulationInfo->relations[start_index] = tmp402;
    current_index++;

    start_index = current_index;
    tmp406 = 1.0;
    tmp407 = 0.09999999999999998;
    tmp405 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.09999999999999998, tmp406, tmp407, data->simulationInfo->storedRelations[65]);
    data->simulationInfo->relations[start_index] = tmp405;
    current_index++;

    start_index = current_index;
    tmp409 = 1.0;
    tmp410 = 0.945;
    tmp408 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), 0.945, tmp409, tmp410, data->simulationInfo->storedRelations[66]);
    data->simulationInfo->relations[start_index] = tmp408;
    current_index++;

    start_index = current_index;
    tmp412 = 1.0;
    tmp413 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */));
    tmp411 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */), tmp412, tmp413, data->simulationInfo->storedRelations[67]);
    data->simulationInfo->relations[start_index] = tmp411;
    current_index++;

    start_index = current_index;
    tmp415 = 1.0;
    tmp416 = fabs((data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */)) + 0.25;
    tmp414 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */), (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */) - 0.25, tmp415, tmp416, data->simulationInfo->storedRelations[68]);
    data->simulationInfo->relations[start_index] = tmp414;
    current_index++;

    start_index = current_index;
    tmp418 = 1.0;
    tmp419 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */));
    tmp417 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */), tmp418, tmp419, data->simulationInfo->storedRelations[69]);
    data->simulationInfo->relations[start_index] = tmp417;
    current_index++;

    start_index = current_index;
    tmp421 = 1.0;
    tmp422 = fabs((data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */)) + 0.25;
    tmp420 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */), (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */) - 0.25, tmp421, tmp422, data->simulationInfo->storedRelations[70]);
    data->simulationInfo->relations[start_index] = tmp420;
    current_index++;

    start_index = current_index;
    tmp424 = 1.0;
    tmp425 = 1.0;
    tmp423 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp424, tmp425, data->simulationInfo->storedRelations[71]);
    data->simulationInfo->relations[start_index] = tmp423;
    current_index++;

    start_index = current_index;
    tmp427 = 1.0;
    tmp428 = 1.25;
    tmp426 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp427, tmp428, data->simulationInfo->storedRelations[72]);
    data->simulationInfo->relations[start_index] = tmp426;
    current_index++;

    start_index = current_index;
    tmp430 = 1.0;
    tmp431 = 1.0;
    tmp429 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */), tmp430, tmp431, data->simulationInfo->storedRelations[73]);
    data->simulationInfo->relations[start_index] = tmp429;
    current_index++;

    start_index = current_index;
    tmp433 = 1.0;
    tmp434 = 1.25;
    tmp432 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25, tmp433, tmp434, data->simulationInfo->storedRelations[74]);
    data->simulationInfo->relations[start_index] = tmp432;
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 5) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 4) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 3) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 2) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    tmp436 = 1.0;
    tmp437 = 1.0;
    tmp435 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */), tmp436, tmp437, data->simulationInfo->storedRelations[79]);
    data->simulationInfo->relations[start_index] = tmp435;
    current_index++;

    start_index = current_index;
    tmp439 = 1.0;
    tmp440 = 1.005;
    tmp438 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) + 0.005, tmp439, tmp440, data->simulationInfo->storedRelations[80]);
    data->simulationInfo->relations[start_index] = tmp438;
    current_index++;

    start_index = current_index;
    tmp442 = 1.0;
    tmp443 = 0.005;
    tmp441 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.005, tmp442, tmp443, data->simulationInfo->storedRelations[81]);
    data->simulationInfo->relations[start_index] = tmp441;
    current_index++;

    start_index = current_index;
    tmp445 = 1.0;
    tmp446 = 0.0025;
    tmp444 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), 0.0025, tmp445, tmp446, data->simulationInfo->storedRelations[82]);
    data->simulationInfo->relations[start_index] = tmp444;
    current_index++;

    start_index = current_index;
    tmp448 = 1.0;
    tmp449 = 1.0;
    tmp447 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */), tmp448, tmp449, data->simulationInfo->storedRelations[83]);
    data->simulationInfo->relations[start_index] = tmp447;
    current_index++;

    start_index = current_index;
    tmp451 = 1.0;
    tmp452 = 1.005;
    tmp450 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) - 0.005, tmp451, tmp452, data->simulationInfo->storedRelations[84]);
    data->simulationInfo->relations[start_index] = tmp450;
    current_index++;

    start_index = current_index;
    tmp454 = 1.0;
    tmp455 = 0.005;
    tmp453 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.005, tmp454, tmp455, data->simulationInfo->storedRelations[85]);
    data->simulationInfo->relations[start_index] = tmp453;
    current_index++;

    start_index = current_index;
    tmp457 = 1.0;
    tmp458 = 0.0075;
    tmp456 = LessZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), 0.0075, tmp457, tmp458, data->simulationInfo->storedRelations[86]);
    data->simulationInfo->relations[start_index] = tmp456;
    current_index++;

    start_index = current_index;
    tmp460 = 1.0;
    tmp461 = 1.0;
    tmp459 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp460, tmp461, data->simulationInfo->storedRelations[87]);
    data->simulationInfo->relations[start_index] = tmp459;
    current_index++;

    start_index = current_index;
    tmp463 = 1.0;
    tmp464 = 1.005;
    tmp462 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp463, tmp464, data->simulationInfo->storedRelations[88]);
    data->simulationInfo->relations[start_index] = tmp462;
    current_index++;

    start_index = current_index;
    tmp466 = 1.0;
    tmp467 = 1.0;
    tmp465 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */), tmp466, tmp467, data->simulationInfo->storedRelations[89]);
    data->simulationInfo->relations[start_index] = tmp465;
    current_index++;

    start_index = current_index;
    tmp469 = 1.0;
    tmp470 = 1.005;
    tmp468 = GreaterZC((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */), (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005, tmp469, tmp470, data->simulationInfo->storedRelations[90]);
    data->simulationInfo->relations[start_index] = tmp468;
    current_index++;
  } else {
    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[211] /* sysReq.tim1.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[212] /* sysReq.tim2.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[213] /* sysReq.tim3.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[214] /* sysReq.tim4.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[215] /* sysReq.tim5.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[201] /* conLoo.disCoo.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[202] /* conLoo.disHea.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[193] /* ala.truDel.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[194] /* ala.truDel1.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[195] /* ala.truDel2.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[196] /* ala.truDel3.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[197] /* ala.truDel4.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[198] /* ala.truDel5.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[199] /* ala.truDel6.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[200] /* ala.truDel7.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[192] /* ala.fanIni.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[220] /* timSup.truDel.t_next DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[203] /* damVal.truFalHol.entryTimeFalse DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[204] /* damVal.truFalHol.entryTimeTrue DISCRETE */) + 600.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[205] /* damVal.truFalHol1.entryTimeFalse DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realVarsPre[206] /* damVal.truFalHol1.entryTimeTrue DISCRETE */) + 600.0);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 4));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 3));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[21]] /* oveFloSet variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 7) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 1) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */) > 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[133]] /* damVal.sub2.y variable */) > 0.125);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[82]] /* damVal.addPar1.y variable */) - 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) - 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */) > 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[181]] /* timSup.abs1.y variable */) > 0.125);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (data->localData[0]->timeValue >= (data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) + (data->simulationInfo->realVarsPre[217] /* timSup.tim.entryTime DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[189]] /* timSup.tim.y variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[186]] /* timSup.supTim.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 2));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[20]] /* oveDamPos variable */) == ((modelica_integer) 1));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[41]] /* ala.addPar2.y variable */) - 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[44]] /* ala.gai2.y variable */) - 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[13]] /* TCooSet variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[18]] /* TZon variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[15]] /* THeaSet variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */) < 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */) < 0.018000000000000002);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */) > 0.002);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[39]] /* ala.addPar.y variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[14]] /* TDis variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[40]] /* ala.addPar1.y variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) < 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) < 0.0075);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */) < 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */) < 0.018000000000000002);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */) > 0.01);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */) > 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) > 0.95);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) > 0.09999999999999998);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */) > 0.945);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */) > (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[180]] /* sysReq.sub3.y variable */) > (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */) - 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */) > (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[179]] /* sysReq.sub2.y variable */) > (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */) - 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[176]] /* sysReq.addPar1.y variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[175]] /* sysReq.addPar.y variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[75]] /* damVal.TDisSet variable */) + 0.25);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 5) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 4) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 3) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = (((modelica_integer) 2) == (data->localData[0]->integerVars[data->simulationInfo->integerVarsIndex[37]] /* uOpeMod variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) < (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[42]] /* ala.gai.y variable */) + 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */) > 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */) > 0.0025);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[43]] /* ala.gai1.y variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[21]] /* VDis_flow variable */) - 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */) < 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */) < 0.0075);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[178]] /* sysReq.greEqu.u1 variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005);
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */));
    current_index++;

    start_index = current_index;
    data->simulationInfo->relations[start_index] = ((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[177]] /* sysReq.gai2.y variable */) > (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[209]] /* sysReq.sampler2.y DISCRETE */) - 0.005);
    current_index++;
  }

  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif
