/* Initialization */
#include "ReheatControllerFMU_model.h"
#include "ReheatControllerFMU_11mix.h"
#include "ReheatControllerFMU_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void ReheatControllerFMU_functionInitialEquations_0(DATA *data, threadData_t *threadData);
void ReheatControllerFMU_functionInitialEquations_1(DATA *data, threadData_t *threadData);

int ReheatControllerFMU_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  ReheatControllerFMU_functionInitialEquations_0(data, threadData);
  ReheatControllerFMU_functionInitialEquations_1(data, threadData);
  data->simulationInfo->discreteCall = 0;

  TRACE_POP
  return 0;
}
extern void ReheatControllerFMU_eqFunction_1(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_2(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_3(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_4(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_5(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_6(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_7(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_8(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_9(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_10(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_11(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_12(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_13(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_14(DATA *data, threadData_t *threadData);

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

extern void ReheatControllerFMU_eqFunction_39(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1237(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1241(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1242(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1243(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1256(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_45(DATA *data, threadData_t *threadData);

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

extern void ReheatControllerFMU_eqFunction_58(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1291(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1292(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1293(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1294(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1295(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1296(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_65(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1299(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_67(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_68(DATA *data, threadData_t *threadData);

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

extern void ReheatControllerFMU_eqFunction_113(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_114(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_115(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1181(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_117(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1356(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1357(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_120(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_121(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_122(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_123(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_124(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_125(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_126(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_127(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_128(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_129(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_130(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_131(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_132(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_133(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_134(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1336(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_136(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_137(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_138(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_139(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_140(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_141(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_142(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_143(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_144(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1322(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1323(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_147(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_148(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_149(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_150(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_151(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_152(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_153(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_154(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_155(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_156(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_157(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1377(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1378(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1379(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1380(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_162(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_163(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1283(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1367(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1368(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_167(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1370(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_169(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1384(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_171(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1382(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1373(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_174(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_175(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1391(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1392(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1393(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_179(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1396(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_181(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_182(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_183(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_184(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_185(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_186(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_187(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_188(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1265(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_190(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_191(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_192(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_193(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1416(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_195(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_196(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_197(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_198(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_199(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_200(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_201(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1260(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_203(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_204(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1258(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_206(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1245(DATA *data, threadData_t *threadData);


/*
equation index: 801
type: SIMPLE_ASSIGN
conLoo.conHea.y = conLoo.conHea.addPID.y
*/
void ReheatControllerFMU_eqFunction_801(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,801};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[70]] /* conLoo.conHea.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[62]] /* conLoo.conHea.addPID.y variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_209(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1250(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_211(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_212(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_213(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1428(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1429(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1430(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_217(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1432(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_219(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1433(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_221(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_222(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_223(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_224(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1438(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_226(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_227(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_228(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_229(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_230(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1447(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1619(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1656(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1657(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1687(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_236(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1684(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1659(DATA *data, threadData_t *threadData);


/*
equation index: 832
type: SIMPLE_ASSIGN
damVal.conVal.y = damVal.conVal.addPID.y
*/
void ReheatControllerFMU_eqFunction_832(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,832};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[116]] /* damVal.conVal.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[108]] /* damVal.conVal.addPID.y variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_240(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1662(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1663(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_243(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1665(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_245(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_246(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_247(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_248(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1672(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1682(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1683(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1685(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1686(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1655(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1636(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_256(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1654(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_258(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_259(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_260(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1648(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1649(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1650(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1651(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1620(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_266(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1635(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_268(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_269(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_270(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1632(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1633(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1634(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1652(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1653(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_276(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1450(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1451(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1251(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1252(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1254(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1255(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_283(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1229(DATA *data, threadData_t *threadData);


/*
equation index: 878
type: SIMPLE_ASSIGN
conLoo.conCoo.y = conLoo.conCoo.addPID.y
*/
void ReheatControllerFMU_eqFunction_878(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,878};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[57]] /* conLoo.conCoo.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[49]] /* conLoo.conCoo.addPID.y variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_286(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1234(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_288(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_289(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_290(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1461(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1462(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1463(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_294(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_295(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1465(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_297(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1466(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_299(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_300(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_301(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_302(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1471(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_304(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1473(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1474(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1472(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_308(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_309(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_310(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1482(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1483(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1484(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_314(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1570(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1568(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1532(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1534(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1535(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1565(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_321(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1562(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1537(DATA *data, threadData_t *threadData);


/*
equation index: 917
type: SIMPLE_ASSIGN
damVal.conDam.y = damVal.conDam.addPID.y
*/
void ReheatControllerFMU_eqFunction_917(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,917};
  (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[95]] /* damVal.conDam.y variable */) = (data->localData[0]->realVars[data->simulationInfo->realVarsIndex[87]] /* damVal.conDam.addPID.y variable */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_1539(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1540(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_327(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_328(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_329(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_330(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_331(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_332(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1548(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1560(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1561(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1563(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1564(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1533(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1513(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_340(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_341(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_342(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_343(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_344(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_345(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1512(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_347(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_348(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_349(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1521(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1522(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1523(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1524(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1485(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_355(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_356(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_357(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_358(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_359(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1509(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1510(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1511(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1525(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1526(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1235(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1236(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1238(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1239(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_369(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_370(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1679(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_372(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_373(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1681(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_375(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_376(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_377(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_378(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_379(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_380(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_381(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_382(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1574(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_384(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_385(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1559(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_387(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_388(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_389(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1586(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1588(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1587(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1556(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1589(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1590(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_396(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_397(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1209(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_399(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_400(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_401(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1600(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1601(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_404(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_405(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1204(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_407(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_408(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_409(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1611(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1612(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_412(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_413(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1700(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_415(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_416(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_417(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1699(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_419(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_420(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1713(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_422(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_423(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_424(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1712(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_426(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_427(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_428(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_429(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_430(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_431(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_432(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_433(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_434(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_435(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_436(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_437(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_438(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_439(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_440(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_441(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_442(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_443(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_444(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_445(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_446(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_447(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_448(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_449(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_450(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_451(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_452(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_453(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_454(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_455(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_456(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_457(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_458(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_459(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_460(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_461(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_462(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_463(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_464(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_465(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_466(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_467(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_468(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_469(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_470(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_471(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_472(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_473(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_474(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_475(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_476(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_477(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_478(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_479(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_480(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_481(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_482(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_483(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_484(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_485(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_486(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_487(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_488(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_489(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_490(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_491(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_492(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_493(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_494(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_495(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_496(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_497(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_498(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_499(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_500(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_501(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_502(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_503(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_504(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_505(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_506(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_507(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_508(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_509(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_510(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_511(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_512(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_513(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_514(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_515(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_516(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_517(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_518(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_519(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_520(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_521(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_522(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_523(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_524(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_525(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_526(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_527(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_528(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_529(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_530(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_531(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_532(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_533(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_534(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_535(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_536(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_537(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_538(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_539(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_540(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_541(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_542(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_543(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_544(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_545(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_546(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1617(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_548(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_549(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_550(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_551(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_552(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_553(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_554(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_555(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_556(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_557(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_558(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_559(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_560(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_561(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1183(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1182(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_564(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_565(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_566(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_567(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_568(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_569(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_570(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_571(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_572(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_573(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_574(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_575(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_576(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_577(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_578(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_579(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_580(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_581(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_582(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_583(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_584(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_585(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_586(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_587(DATA *data, threadData_t *threadData);

int ReheatControllerFMU_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
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

  ReheatControllerFMU_eqFunction_801(data, threadData);

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

  ReheatControllerFMU_eqFunction_832(data, threadData);

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

  ReheatControllerFMU_eqFunction_878(data, threadData);

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

  ReheatControllerFMU_eqFunction_917(data, threadData);

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
  data->simulationInfo->discreteCall = 0;

  TRACE_POP
  return 0;
}
int ReheatControllerFMU_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;


  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif
