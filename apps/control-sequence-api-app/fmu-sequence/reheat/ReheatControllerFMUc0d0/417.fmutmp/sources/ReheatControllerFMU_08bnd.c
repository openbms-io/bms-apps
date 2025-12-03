/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "ReheatControllerFMU_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

OMC_DISABLE_OPT
int ReheatControllerFMU_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating min-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);

  /* max ******************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating max-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);

  /* nominal **************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating nominal-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);

  /* start ****************************************************** */
  infoStreamPrint(OMC_LOG_INIT, 1, "updating primary start-values");
  if (OMC_ACTIVE_STREAM(OMC_LOG_INIT)) messageClose(OMC_LOG_INIT);

  TRACE_POP
  return 0;
}

void ReheatControllerFMU_updateBoundParameters_0(DATA *data, threadData_t *threadData);

/*
equation index: 1730
type: SIMPLE_ASSIGN
conLoo.conCoo.cheYMinMax.k = conLoo.conCoo.yMin < conLoo.conCoo.yMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1730(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1730};
  modelica_boolean tmp0;
  tmp0 = Less((data->simulationInfo->realParameter[136] /* conLoo.conCoo.yMin PARAM */),(data->simulationInfo->realParameter[135] /* conLoo.conCoo.yMax PARAM */));
  (data->simulationInfo->booleanParameter[41] /* conLoo.conCoo.cheYMinMax.k PARAM */) = tmp0;
  TRACE_POP
}

/*
equation index: 1731
type: SIMPLE_ASSIGN
conLoo.conCoo.assMesYMinMax.u = conLoo.conCoo.cheYMinMax.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1731(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1731};
  (data->simulationInfo->booleanParameter[40] /* conLoo.conCoo.assMesYMinMax.u PARAM */) = (data->simulationInfo->booleanParameter[41] /* conLoo.conCoo.cheYMinMax.k PARAM */);
  TRACE_POP
}

/*
equation index: 1732
type: SIMPLE_ASSIGN
conLoo.conCoo.cheYMinMax.y = conLoo.conCoo.cheYMinMax.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1732(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1732};
  (data->simulationInfo->booleanParameter[42] /* conLoo.conCoo.cheYMinMax.y PARAM */) = (data->simulationInfo->booleanParameter[41] /* conLoo.conCoo.cheYMinMax.k PARAM */);
  TRACE_POP
}

/*
equation index: 1735
type: SIMPLE_ASSIGN
conLoo.conHea.cheYMinMax.k = conLoo.conHea.yMin < conLoo.conHea.yMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1735(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1735};
  modelica_boolean tmp1;
  tmp1 = Less((data->simulationInfo->realParameter[160] /* conLoo.conHea.yMin PARAM */),(data->simulationInfo->realParameter[159] /* conLoo.conHea.yMax PARAM */));
  (data->simulationInfo->booleanParameter[47] /* conLoo.conHea.cheYMinMax.k PARAM */) = tmp1;
  TRACE_POP
}

/*
equation index: 1736
type: SIMPLE_ASSIGN
conLoo.conHea.assMesYMinMax.u = conLoo.conHea.cheYMinMax.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1736(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1736};
  (data->simulationInfo->booleanParameter[46] /* conLoo.conHea.assMesYMinMax.u PARAM */) = (data->simulationInfo->booleanParameter[47] /* conLoo.conHea.cheYMinMax.k PARAM */);
  TRACE_POP
}

/*
equation index: 1737
type: SIMPLE_ASSIGN
conLoo.conHea.cheYMinMax.y = conLoo.conHea.cheYMinMax.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1737(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1737};
  (data->simulationInfo->booleanParameter[48] /* conLoo.conHea.cheYMinMax.y PARAM */) = (data->simulationInfo->booleanParameter[47] /* conLoo.conHea.cheYMinMax.k PARAM */);
  TRACE_POP
}

/*
equation index: 1738
type: SIMPLE_ASSIGN
setPoi.VPopBreZon_flow = VPopBreZon_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1738(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1738};
  (data->simulationInfo->realParameter[329] /* setPoi.VPopBreZon_flow PARAM */) = (data->simulationInfo->realParameter[14] /* VPopBreZon_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1739
type: SIMPLE_ASSIGN
setPoi.desPopAir.k = setPoi.VPopBreZon_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1739(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1739};
  (data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */) = (data->simulationInfo->realParameter[329] /* setPoi.VPopBreZon_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1740
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.b = setPoi.desPopAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1740(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1740};
  (data->simulationInfo->realParameter[349] /* setPoi.popBreOutAir.b PARAM */) = (data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1741
type: SIMPLE_ASSIGN
actAirSet.VHeaMax_flow = VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1741(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1741};
  (data->simulationInfo->realParameter[16] /* actAirSet.VHeaMax_flow PARAM */) = (data->simulationInfo->realParameter[10] /* VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1742
type: SIMPLE_ASSIGN
actAirSet.heaMaxAir.k = actAirSet.VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1742(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1742};
  (data->simulationInfo->realParameter[22] /* actAirSet.heaMaxAir.k PARAM */) = (data->simulationInfo->realParameter[16] /* actAirSet.VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1743
type: SIMPLE_ASSIGN
actAirSet.max2.u2 = actAirSet.heaMaxAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1743(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1743};
  (data->simulationInfo->realParameter[33] /* actAirSet.max2.u2 PARAM */) = (data->simulationInfo->realParameter[22] /* actAirSet.heaMaxAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1744
type: SIMPLE_ASSIGN
actAirSet.heaMaxAir.y = actAirSet.heaMaxAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1744(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1744};
  (data->simulationInfo->realParameter[23] /* actAirSet.heaMaxAir.y PARAM */) = (data->simulationInfo->realParameter[22] /* actAirSet.heaMaxAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1745
type: SIMPLE_ASSIGN
actAirSet.VHeaMin_flow = VHeaMin_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1745(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1745};
  (data->simulationInfo->realParameter[17] /* actAirSet.VHeaMin_flow PARAM */) = (data->simulationInfo->realParameter[11] /* VHeaMin_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1746
type: SIMPLE_ASSIGN
actAirSet.heaMinAir.k = actAirSet.VHeaMin_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1746(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1746};
  (data->simulationInfo->realParameter[28] /* actAirSet.heaMinAir.k PARAM */) = (data->simulationInfo->realParameter[17] /* actAirSet.VHeaMin_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1747
type: SIMPLE_ASSIGN
actAirSet.max1.u2 = actAirSet.heaMinAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1747(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1747};
  (data->simulationInfo->realParameter[32] /* actAirSet.max1.u2 PARAM */) = (data->simulationInfo->realParameter[28] /* actAirSet.heaMinAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1748
type: SIMPLE_ASSIGN
actAirSet.heaMinAir.y = actAirSet.heaMinAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1748(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1748};
  (data->simulationInfo->realParameter[29] /* actAirSet.heaMinAir.y PARAM */) = (data->simulationInfo->realParameter[28] /* actAirSet.heaMinAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1750
type: SIMPLE_ASSIGN
conLoo.conCoo.y_reset = conLoo.conCoo.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1750(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1750};
  (data->simulationInfo->realParameter[139] /* conLoo.conCoo.y_reset PARAM */) = (data->simulationInfo->realParameter[134] /* conLoo.conCoo.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 1751
type: SIMPLE_ASSIGN
conLoo.conCoo.yResSig.k = conLoo.conCoo.y_reset
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1751(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1751};
  (data->simulationInfo->realParameter[137] /* conLoo.conCoo.yResSig.k PARAM */) = (data->simulationInfo->realParameter[139] /* conLoo.conCoo.y_reset PARAM */);
  TRACE_POP
}

/*
equation index: 1752
type: SIMPLE_ASSIGN
conLoo.conCoo.addRes.u1 = conLoo.conCoo.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1752(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1752};
  (data->simulationInfo->realParameter[125] /* conLoo.conCoo.addRes.u1 PARAM */) = (data->simulationInfo->realParameter[137] /* conLoo.conCoo.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1753
type: SIMPLE_ASSIGN
conLoo.conCoo.yResSig.y = conLoo.conCoo.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1753(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1753};
  (data->simulationInfo->realParameter[138] /* conLoo.conCoo.yResSig.y PARAM */) = (data->simulationInfo->realParameter[137] /* conLoo.conCoo.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1755
type: SIMPLE_ASSIGN
conLoo.conHea.y_reset = conLoo.conHea.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1755(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1755};
  (data->simulationInfo->realParameter[163] /* conLoo.conHea.y_reset PARAM */) = (data->simulationInfo->realParameter[158] /* conLoo.conHea.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 1756
type: SIMPLE_ASSIGN
conLoo.conHea.yResSig.k = conLoo.conHea.y_reset
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1756(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1756};
  (data->simulationInfo->realParameter[161] /* conLoo.conHea.yResSig.k PARAM */) = (data->simulationInfo->realParameter[163] /* conLoo.conHea.y_reset PARAM */);
  TRACE_POP
}

/*
equation index: 1757
type: SIMPLE_ASSIGN
conLoo.conHea.addRes.u1 = conLoo.conHea.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1757(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1757};
  (data->simulationInfo->realParameter[149] /* conLoo.conHea.addRes.u1 PARAM */) = (data->simulationInfo->realParameter[161] /* conLoo.conHea.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1758
type: SIMPLE_ASSIGN
conLoo.conHea.yResSig.y = conLoo.conHea.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1758(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1758};
  (data->simulationInfo->realParameter[162] /* conLoo.conHea.yResSig.y PARAM */) = (data->simulationInfo->realParameter[161] /* conLoo.conHea.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1759
type: SIMPLE_ASSIGN
ala.staPreMul = staPreMul
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1759(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1759};
  (data->simulationInfo->realParameter[94] /* ala.staPreMul PARAM */) = (data->simulationInfo->realParameter[360] /* staPreMul PARAM */);
  TRACE_POP
}

/*
equation index: 1760
type: SIMPLE_ASSIGN
ala.conInt1.k = ala.staPreMul
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1760(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1760};
  (data->simulationInfo->realParameter[48] /* ala.conInt1.k PARAM */) = (data->simulationInfo->realParameter[94] /* ala.staPreMul PARAM */);
  TRACE_POP
}

/*
equation index: 1761
type: SIMPLE_ASSIGN
ala.greThr1.greNoHys.u = ala.conInt1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1761(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1761};
  (data->simulationInfo->realParameter[75] /* ala.greThr1.greNoHys.u PARAM */) = (data->simulationInfo->realParameter[48] /* ala.conInt1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1762
type: SIMPLE_ASSIGN
ala.greThr1.u = ala.conInt1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1762(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1762};
  (data->simulationInfo->realParameter[78] /* ala.greThr1.u PARAM */) = (data->simulationInfo->realParameter[48] /* ala.conInt1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1763
type: SIMPLE_ASSIGN
ala.conInt1.y = ala.conInt1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1763(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1763};
  (data->simulationInfo->realParameter[49] /* ala.conInt1.y PARAM */) = (data->simulationInfo->realParameter[48] /* ala.conInt1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1764
type: SIMPLE_ASSIGN
ala.VCooMax_flow = VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1764(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1764};
  (data->simulationInfo->realParameter[36] /* ala.VCooMax_flow PARAM */) = (data->simulationInfo->realParameter[9] /* VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1765
type: SIMPLE_ASSIGN
ala.cooMaxFlo.k = ala.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1765(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1765};
  (data->simulationInfo->realParameter[52] /* ala.cooMaxFlo.k PARAM */) = (data->simulationInfo->realParameter[36] /* ala.VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1766
type: SIMPLE_ASSIGN
ala.gai2.u = ala.cooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1766(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1766};
  (data->simulationInfo->realParameter[63] /* ala.gai2.u PARAM */) = (data->simulationInfo->realParameter[52] /* ala.cooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1767
type: SIMPLE_ASSIGN
ala.cooMaxFlo.y = ala.cooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1767(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1767};
  (data->simulationInfo->realParameter[53] /* ala.cooMaxFlo.y PARAM */) = (data->simulationInfo->realParameter[52] /* ala.cooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1768
type: SIMPLE_ASSIGN
ala.hotWatRes = hotWatRes
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1768(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1768};
  (data->simulationInfo->realParameter[84] /* ala.hotWatRes PARAM */) = (data->simulationInfo->realParameter[308] /* hotWatRes PARAM */);
  TRACE_POP
}

/*
equation index: 1769
type: SIMPLE_ASSIGN
ala.conInt3.k = ala.hotWatRes
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1769(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1769};
  (data->simulationInfo->realParameter[50] /* ala.conInt3.k PARAM */) = (data->simulationInfo->realParameter[84] /* ala.hotWatRes PARAM */);
  TRACE_POP
}

/*
equation index: 1770
type: SIMPLE_ASSIGN
ala.greThr2.greNoHys.u = ala.conInt3.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1770(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1770};
  (data->simulationInfo->realParameter[80] /* ala.greThr2.greNoHys.u PARAM */) = (data->simulationInfo->realParameter[50] /* ala.conInt3.k PARAM */);
  TRACE_POP
}

/*
equation index: 1771
type: SIMPLE_ASSIGN
ala.greThr2.u = ala.conInt3.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1771(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1771};
  (data->simulationInfo->realParameter[83] /* ala.greThr2.u PARAM */) = (data->simulationInfo->realParameter[50] /* ala.conInt3.k PARAM */);
  TRACE_POP
}

/*
equation index: 1772
type: SIMPLE_ASSIGN
ala.conInt3.y = ala.conInt3.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1772(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1772};
  (data->simulationInfo->realParameter[51] /* ala.conInt3.y PARAM */) = (data->simulationInfo->realParameter[50] /* ala.conInt3.k PARAM */);
  TRACE_POP
}

/*
equation index: 1773
type: SIMPLE_ASSIGN
timSup.maxTim = maxSupTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1773(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1773};
  (data->simulationInfo->realParameter[447] /* timSup.maxTim PARAM */) = (data->simulationInfo->realParameter[318] /* maxSupTim PARAM */);
  TRACE_POP
}

/*
equation index: 1774
type: SIMPLE_ASSIGN
timSup.maxSupTim.k = timSup.maxTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1774(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1774};
  (data->simulationInfo->realParameter[445] /* timSup.maxSupTim.k PARAM */) = (data->simulationInfo->realParameter[447] /* timSup.maxTim PARAM */);
  TRACE_POP
}

/*
equation index: 1775
type: SIMPLE_ASSIGN
timSup.supTim.u2 = timSup.maxSupTim.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1775(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1775};
  (data->simulationInfo->realParameter[452] /* timSup.supTim.u2 PARAM */) = (data->simulationInfo->realParameter[445] /* timSup.maxSupTim.k PARAM */);
  TRACE_POP
}

/*
equation index: 1776
type: SIMPLE_ASSIGN
timSup.maxSupTim.y = timSup.maxSupTim.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1776(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1776};
  (data->simulationInfo->realParameter[446] /* timSup.maxSupTim.y PARAM */) = (data->simulationInfo->realParameter[445] /* timSup.maxSupTim.k PARAM */);
  TRACE_POP
}

/*
equation index: 1777
type: SIMPLE_ASSIGN
setPoi.permit_occStandby = permit_occStandby
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1777(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1777};
  (data->simulationInfo->booleanParameter[118] /* setPoi.permit_occStandby PARAM */) = (data->simulationInfo->booleanParameter[101] /* permit_occStandby PARAM */);
  TRACE_POP
}

/*
equation index: 1778
type: SIMPLE_ASSIGN
setPoi.perOccSta.k = setPoi.permit_occStandby
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1778(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1778};
  (data->simulationInfo->booleanParameter[116] /* setPoi.perOccSta.k PARAM */) = (data->simulationInfo->booleanParameter[118] /* setPoi.permit_occStandby PARAM */);
  TRACE_POP
}

/*
equation index: 1779
type: SIMPLE_ASSIGN
setPoi.booToRea1.u = setPoi.perOccSta.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1779(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1779};
  (data->simulationInfo->booleanParameter[102] /* setPoi.booToRea1.u PARAM */) = (data->simulationInfo->booleanParameter[116] /* setPoi.perOccSta.k PARAM */);
  TRACE_POP
}

/*
equation index: 1780
type: SIMPLE_ASSIGN
setPoi.perOccSta.y = setPoi.perOccSta.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1780(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1780};
  (data->simulationInfo->booleanParameter[117] /* setPoi.perOccSta.y PARAM */) = (data->simulationInfo->booleanParameter[116] /* setPoi.perOccSta.k PARAM */);
  TRACE_POP
}

/*
equation index: 1781
type: SIMPLE_ASSIGN
setPoi.VCooMax_flow = VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1781(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1781};
  (data->simulationInfo->realParameter[327] /* setPoi.VCooMax_flow PARAM */) = (data->simulationInfo->realParameter[9] /* VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1782
type: SIMPLE_ASSIGN
setPoi.zonCooMaxFlo.k = setPoi.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1782(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1782};
  (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */) = (data->simulationInfo->realParameter[327] /* setPoi.VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1783
type: SIMPLE_ASSIGN
setPoi.occMinAirSet.f2 = setPoi.zonCooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1783(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1783};
  (data->simulationInfo->realParameter[347] /* setPoi.occMinAirSet.f2 PARAM */) = (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1784
type: SIMPLE_ASSIGN
setPoi.gai2.y = setPoi.zonCooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1784(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1784};
  (data->simulationInfo->realParameter[346] /* setPoi.gai2.y PARAM */) = (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1785
type: SIMPLE_ASSIGN
setPoi.gai2.u = setPoi.zonCooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1785(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1785};
  (data->simulationInfo->realParameter[345] /* setPoi.gai2.u PARAM */) = (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1786
type: SIMPLE_ASSIGN
setPoi.zonCooMaxFlo.y = setPoi.zonCooMaxFlo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1786(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1786};
  (data->simulationInfo->realParameter[356] /* setPoi.zonCooMaxFlo.y PARAM */) = (data->simulationInfo->realParameter[355] /* setPoi.zonCooMaxFlo.k PARAM */);
  TRACE_POP
}

/*
equation index: 1787
type: SIMPLE_ASSIGN
setPoi.VAreBreZon_flow = VAreBreZon_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1787(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1787};
  (data->simulationInfo->realParameter[326] /* setPoi.VAreBreZon_flow PARAM */) = (data->simulationInfo->realParameter[7] /* VAreBreZon_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1788
type: SIMPLE_ASSIGN
setPoi.desAreAir.k = setPoi.VAreBreZon_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1788(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1788};
  (data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */) = (data->simulationInfo->realParameter[326] /* setPoi.VAreBreZon_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1789
type: SIMPLE_ASSIGN
setPoi.unPopAreBreAir.u1 = setPoi.desAreAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1789(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1789};
  (data->simulationInfo->realParameter[351] /* setPoi.unPopAreBreAir.u1 PARAM */) = (data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1790
type: SIMPLE_ASSIGN
setPoi.unpAreBreAir.u3 = setPoi.desAreAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1790(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1790};
  (data->simulationInfo->realParameter[352] /* setPoi.unpAreBreAir.u3 PARAM */) = (data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1791
type: SIMPLE_ASSIGN
setPoi.desAreAir.y = setPoi.desAreAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1791(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1791};
  (data->simulationInfo->realParameter[341] /* setPoi.desAreAir.y PARAM */) = (data->simulationInfo->realParameter[340] /* setPoi.desAreAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1792
type: SIMPLE_ASSIGN
setPoi.popBreOutAir.f2 = setPoi.desPopAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1792(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1792};
  (data->simulationInfo->realParameter[350] /* setPoi.popBreOutAir.f2 PARAM */) = (data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1793
type: SIMPLE_ASSIGN
setPoi.desPopAir.y = setPoi.desPopAir.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1793(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1793};
  (data->simulationInfo->realParameter[343] /* setPoi.desPopAir.y PARAM */) = (data->simulationInfo->realParameter[342] /* setPoi.desPopAir.k PARAM */);
  TRACE_POP
}

/*
equation index: 1795
type: SIMPLE_ASSIGN
damVal.conDam.y_reset = damVal.iniDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1795(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1795};
  (data->simulationInfo->realParameter[225] /* damVal.conDam.y_reset PARAM */) = (data->simulationInfo->realParameter[282] /* damVal.iniDam PARAM */);
  TRACE_POP
}

/*
equation index: 1796
type: SIMPLE_ASSIGN
damVal.conDam.yResSig.k = damVal.conDam.y_reset
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1796(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1796};
  (data->simulationInfo->realParameter[223] /* damVal.conDam.yResSig.k PARAM */) = (data->simulationInfo->realParameter[225] /* damVal.conDam.y_reset PARAM */);
  TRACE_POP
}

/*
equation index: 1797
type: SIMPLE_ASSIGN
damVal.conDam.addRes.u1 = damVal.conDam.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1797(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1797};
  (data->simulationInfo->realParameter[211] /* damVal.conDam.addRes.u1 PARAM */) = (data->simulationInfo->realParameter[223] /* damVal.conDam.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1798
type: SIMPLE_ASSIGN
damVal.conDam.yResSig.y = damVal.conDam.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1798(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1798};
  (data->simulationInfo->realParameter[224] /* damVal.conDam.yResSig.y PARAM */) = (data->simulationInfo->realParameter[223] /* damVal.conDam.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1800
type: SIMPLE_ASSIGN
damVal.conVal.y_reset = damVal.conVal.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1800(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1800};
  (data->simulationInfo->realParameter[253] /* damVal.conVal.y_reset PARAM */) = (data->simulationInfo->realParameter[248] /* damVal.conVal.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 1801
type: SIMPLE_ASSIGN
damVal.conVal.yResSig.k = damVal.conVal.y_reset
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1801(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1801};
  (data->simulationInfo->realParameter[251] /* damVal.conVal.yResSig.k PARAM */) = (data->simulationInfo->realParameter[253] /* damVal.conVal.y_reset PARAM */);
  TRACE_POP
}

/*
equation index: 1802
type: SIMPLE_ASSIGN
damVal.conVal.addRes.u1 = damVal.conVal.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1802(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1802};
  (data->simulationInfo->realParameter[239] /* damVal.conVal.addRes.u1 PARAM */) = (data->simulationInfo->realParameter[251] /* damVal.conVal.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1803
type: SIMPLE_ASSIGN
damVal.conVal.yResSig.y = damVal.conVal.yResSig.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1803(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1803};
  (data->simulationInfo->realParameter[252] /* damVal.conVal.yResSig.y PARAM */) = (data->simulationInfo->realParameter[251] /* damVal.conVal.yResSig.k PARAM */);
  TRACE_POP
}

/*
equation index: 1804
type: SIMPLE_ASSIGN
damVal.TDisMin = TDisMin
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1804(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1804};
  (data->simulationInfo->realParameter[193] /* damVal.TDisMin PARAM */) = (data->simulationInfo->realParameter[0] /* TDisMin PARAM */);
  TRACE_POP
}

/*
equation index: 1805
type: SIMPLE_ASSIGN
damVal.lowDisAirTem.k = damVal.TDisMin
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1805(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1805};
  (data->simulationInfo->realParameter[286] /* damVal.lowDisAirTem.k PARAM */) = (data->simulationInfo->realParameter[193] /* damVal.TDisMin PARAM */);
  TRACE_POP
}

/*
equation index: 1806
type: SIMPLE_ASSIGN
damVal.max1.u2 = damVal.lowDisAirTem.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1806(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1806};
  (data->simulationInfo->realParameter[292] /* damVal.max1.u2 PARAM */) = (data->simulationInfo->realParameter[286] /* damVal.lowDisAirTem.k PARAM */);
  TRACE_POP
}

/*
equation index: 1807
type: SIMPLE_ASSIGN
damVal.lowDisAirTem.y = damVal.lowDisAirTem.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1807(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1807};
  (data->simulationInfo->realParameter[287] /* damVal.lowDisAirTem.y PARAM */) = (data->simulationInfo->realParameter[286] /* damVal.lowDisAirTem.k PARAM */);
  TRACE_POP
}

/*
equation index: 1808
type: SIMPLE_ASSIGN
damVal.VCooMax_flow = VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1808(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1808};
  (data->simulationInfo->realParameter[198] /* damVal.VCooMax_flow PARAM */) = (data->simulationInfo->realParameter[9] /* VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1809
type: SIMPLE_ASSIGN
damVal.cooMax1.k = damVal.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1809(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1809};
  (data->simulationInfo->realParameter[260] /* damVal.cooMax1.k PARAM */) = (data->simulationInfo->realParameter[198] /* damVal.VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1810
type: SIMPLE_ASSIGN
damVal.max2.u1 = damVal.cooMax1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1810(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1810};
  (data->simulationInfo->realParameter[293] /* damVal.max2.u1 PARAM */) = (data->simulationInfo->realParameter[260] /* damVal.cooMax1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1811
type: SIMPLE_ASSIGN
damVal.cooMax1.y = damVal.cooMax1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1811(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1811};
  (data->simulationInfo->realParameter[261] /* damVal.cooMax1.y PARAM */) = (data->simulationInfo->realParameter[260] /* damVal.cooMax1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1812
type: SIMPLE_ASSIGN
damVal.VHeaMax_flow = VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1812(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1812};
  (data->simulationInfo->realParameter[199] /* damVal.VHeaMax_flow PARAM */) = (data->simulationInfo->realParameter[10] /* VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1813
type: SIMPLE_ASSIGN
damVal.heaMax1.k = damVal.VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1813(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1813};
  (data->simulationInfo->realParameter[280] /* damVal.heaMax1.k PARAM */) = (data->simulationInfo->realParameter[199] /* damVal.VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1814
type: SIMPLE_ASSIGN
damVal.max2.u2 = damVal.heaMax1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1814(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1814};
  (data->simulationInfo->realParameter[294] /* damVal.max2.u2 PARAM */) = (data->simulationInfo->realParameter[280] /* damVal.heaMax1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1815
type: SIMPLE_ASSIGN
damVal.heaMax1.y = damVal.heaMax1.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1815(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1815};
  (data->simulationInfo->realParameter[281] /* damVal.heaMax1.y PARAM */) = (data->simulationInfo->realParameter[280] /* damVal.heaMax1.k PARAM */);
  TRACE_POP
}

/*
equation index: 1823
type: SIMPLE_ASSIGN
damVal.heaMax.realTrue = damVal.VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1823(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1823};
  (data->simulationInfo->realParameter[279] /* damVal.heaMax.realTrue PARAM */) = (data->simulationInfo->realParameter[199] /* damVal.VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1828
type: SIMPLE_ASSIGN
damVal.cooMax.realTrue = damVal.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1828(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1828};
  (data->simulationInfo->realParameter[259] /* damVal.cooMax.realTrue PARAM */) = (data->simulationInfo->realParameter[198] /* damVal.VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 1836
type: SIMPLE_ASSIGN
damVal.dTDisZonSetMax = dTDisZonSetMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1836(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1836};
  (data->simulationInfo->realParameter[262] /* damVal.dTDisZonSetMax PARAM */) = (data->simulationInfo->realParameter[190] /* dTDisZonSetMax PARAM */);
  TRACE_POP
}

/*
equation index: 1837
type: SIMPLE_ASSIGN
damVal.addPar.p = damVal.dTDisZonSetMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1837(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1837};
  (data->simulationInfo->realParameter[201] /* damVal.addPar.p PARAM */) = (data->simulationInfo->realParameter[262] /* damVal.dTDisZonSetMax PARAM */);
  TRACE_POP
}

/*
equation index: 1844
type: SIMPLE_ASSIGN
damVal.greThr2.greHys.pre_y_start = damVal.greThr2.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1844(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1844};
  (data->simulationInfo->booleanParameter[85] /* damVal.greThr2.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[87] /* damVal.greThr2.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1852
type: SIMPLE_ASSIGN
damVal.lowMin.lesHys.pre_y_start = damVal.lowMin.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1852(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1852};
  (data->simulationInfo->booleanParameter[93] /* damVal.lowMin.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[94] /* damVal.lowMin.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1854
type: SIMPLE_ASSIGN
damVal.lowMin.t = damVal.TDisMin
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1854(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1854};
  (data->simulationInfo->realParameter[291] /* damVal.lowMin.t PARAM */) = (data->simulationInfo->realParameter[193] /* damVal.TDisMin PARAM */);
  TRACE_POP
}

/*
equation index: 1855
type: SIMPLE_ASSIGN
damVal.lowMin.lesHys.t = damVal.lowMin.t
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1855(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1855};
  (data->simulationInfo->realParameter[290] /* damVal.lowMin.lesHys.t PARAM */) = (data->simulationInfo->realParameter[291] /* damVal.lowMin.t PARAM */);
  TRACE_POP
}

/*
equation index: 1859
type: SIMPLE_ASSIGN
damVal.greThr.greHys.pre_y_start = damVal.greThr.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1859(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1859};
  (data->simulationInfo->booleanParameter[79] /* damVal.greThr.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[81] /* damVal.greThr.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1866
type: SIMPLE_ASSIGN
damVal.greThr1.greHys.pre_y_start = damVal.greThr1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1866(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1866};
  (data->simulationInfo->booleanParameter[82] /* damVal.greThr1.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[84] /* damVal.greThr1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1874
type: SIMPLE_ASSIGN
damVal.conVal.assMesYMinMax.message = "LimPID: Limits must be yMin < yMax"
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1874(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1874};
  (data->simulationInfo->stringParameter[10] /* damVal.conVal.assMesYMinMax.message PARAM */) = _OMC_LIT0;
  TRACE_POP
}

/*
equation index: 1876
type: SIMPLE_ASSIGN
damVal.kVal = kVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1876(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1876};
  (data->simulationInfo->realParameter[284] /* damVal.kVal PARAM */) = (data->simulationInfo->realParameter[313] /* kVal PARAM */);
  TRACE_POP
}

/*
equation index: 1877
type: SIMPLE_ASSIGN
damVal.conVal.k = damVal.kVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1877(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1877};
  (data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */) = (data->simulationInfo->realParameter[284] /* damVal.kVal PARAM */);
  TRACE_POP
}

/*
equation index: 1879
type: SIMPLE_ASSIGN
damVal.conVal.antWinGai.k = 1.0 / (damVal.conVal.Ni * damVal.conVal.k)
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1879(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1879};
  (data->simulationInfo->realParameter[240] /* damVal.conVal.antWinGai.k PARAM */) = DIVISION_SIM(1.0,((data->simulationInfo->realParameter[235] /* damVal.conVal.Ni PARAM */)) * ((data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */)),"damVal.conVal.Ni * damVal.conVal.k",equationIndexes);
  TRACE_POP
}

/*
equation index: 1882
type: SIMPLE_ASSIGN
damVal.conVal.revAct = if damVal.conVal.reverseActing then 1.0 else -1.0
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1882(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1882};
  (data->simulationInfo->realParameter[245] /* damVal.conVal.revAct PARAM */) = ((data->simulationInfo->booleanParameter[73] /* damVal.conVal.reverseActing PARAM */)?1.0:-1.0);
  TRACE_POP
}

/*
equation index: 1883
type: SIMPLE_ASSIGN
damVal.conVal.uMea_revAct.k = damVal.conVal.revAct / damVal.conVal.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1883(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1883};
  (data->simulationInfo->realParameter[246] /* damVal.conVal.uMea_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[245] /* damVal.conVal.revAct PARAM */),(data->simulationInfo->realParameter[244] /* damVal.conVal.r PARAM */),"damVal.conVal.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 1884
type: SIMPLE_ASSIGN
damVal.conVal.uS_revAct.k = damVal.conVal.revAct / damVal.conVal.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1884(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1884};
  (data->simulationInfo->realParameter[247] /* damVal.conVal.uS_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[245] /* damVal.conVal.revAct PARAM */),(data->simulationInfo->realParameter[244] /* damVal.conVal.r PARAM */),"damVal.conVal.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 1890
type: SIMPLE_ASSIGN
damVal.conVal.I.y_start = damVal.conVal.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1890(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1890};
  (data->simulationInfo->realParameter[233] /* damVal.conVal.I.y_start PARAM */) = (data->simulationInfo->realParameter[248] /* damVal.conVal.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 1891
type: SIMPLE_ASSIGN
damVal.TiVal = TiVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1891(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1891};
  (data->simulationInfo->realParameter[197] /* damVal.TiVal PARAM */) = (data->simulationInfo->realParameter[6] /* TiVal PARAM */);
  TRACE_POP
}

/*
equation index: 1892
type: SIMPLE_ASSIGN
damVal.conVal.Ti = damVal.TiVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1892(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1892};
  (data->simulationInfo->realParameter[238] /* damVal.conVal.Ti PARAM */) = (data->simulationInfo->realParameter[197] /* damVal.TiVal PARAM */);
  TRACE_POP
}

/*
equation index: 1893
type: SIMPLE_ASSIGN
damVal.conVal.I.k = damVal.conVal.k / damVal.conVal.Ti
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1893(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1893};
  (data->simulationInfo->realParameter[232] /* damVal.conVal.I.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */),(data->simulationInfo->realParameter[238] /* damVal.conVal.Ti PARAM */),"damVal.conVal.Ti",equationIndexes);
  TRACE_POP
}

/*
equation index: 1894
type: SIMPLE_ASSIGN
damVal.conVal.P.k = damVal.conVal.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1894(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1894};
  (data->simulationInfo->realParameter[236] /* damVal.conVal.P.k PARAM */) = (data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */);
  TRACE_POP
}

/*
equation index: 1899
type: SIMPLE_ASSIGN
damVal.TdVal = TdVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1899(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1899};
  (data->simulationInfo->realParameter[195] /* damVal.TdVal PARAM */) = (data->simulationInfo->realParameter[2] /* TdVal PARAM */);
  TRACE_POP
}

/*
equation index: 1900
type: SIMPLE_ASSIGN
damVal.conVal.Td = damVal.TdVal
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1900(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1900};
  (data->simulationInfo->realParameter[237] /* damVal.conVal.Td PARAM */) = (data->simulationInfo->realParameter[195] /* damVal.TdVal PARAM */);
  TRACE_POP
}

/*
equation index: 1905
type: SIMPLE_ASSIGN
damVal.gre.greHys.pre_y_start = damVal.gre.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1905(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1905};
  (data->simulationInfo->booleanParameter[76] /* damVal.gre.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[78] /* damVal.gre.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1911
type: SIMPLE_ASSIGN
damVal.conDam.assMesYMinMax.message = "LimPID: Limits must be yMin < yMax"
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1911(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1911};
  (data->simulationInfo->stringParameter[9] /* damVal.conDam.assMesYMinMax.message PARAM */) = _OMC_LIT0;
  TRACE_POP
}

/*
equation index: 1913
type: SIMPLE_ASSIGN
damVal.kDam = kDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1913(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1913};
  (data->simulationInfo->realParameter[283] /* damVal.kDam PARAM */) = (data->simulationInfo->realParameter[311] /* kDam PARAM */);
  TRACE_POP
}

/*
equation index: 1914
type: SIMPLE_ASSIGN
damVal.conDam.k = damVal.kDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1914(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1914};
  (data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */) = (data->simulationInfo->realParameter[283] /* damVal.kDam PARAM */);
  TRACE_POP
}

/*
equation index: 1916
type: SIMPLE_ASSIGN
damVal.conDam.antWinGai.k = 1.0 / (damVal.conDam.Ni * damVal.conDam.k)
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1916(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1916};
  (data->simulationInfo->realParameter[212] /* damVal.conDam.antWinGai.k PARAM */) = DIVISION_SIM(1.0,((data->simulationInfo->realParameter[207] /* damVal.conDam.Ni PARAM */)) * ((data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */)),"damVal.conDam.Ni * damVal.conDam.k",equationIndexes);
  TRACE_POP
}

/*
equation index: 1919
type: SIMPLE_ASSIGN
damVal.conDam.revAct = if damVal.conDam.reverseActing then 1.0 else -1.0
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1919(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1919};
  (data->simulationInfo->realParameter[217] /* damVal.conDam.revAct PARAM */) = ((data->simulationInfo->booleanParameter[67] /* damVal.conDam.reverseActing PARAM */)?1.0:-1.0);
  TRACE_POP
}

/*
equation index: 1920
type: SIMPLE_ASSIGN
damVal.conDam.uMea_revAct.k = damVal.conDam.revAct / damVal.conDam.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1920(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1920};
  (data->simulationInfo->realParameter[218] /* damVal.conDam.uMea_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[217] /* damVal.conDam.revAct PARAM */),(data->simulationInfo->realParameter[216] /* damVal.conDam.r PARAM */),"damVal.conDam.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 1921
type: SIMPLE_ASSIGN
damVal.conDam.uS_revAct.k = damVal.conDam.revAct / damVal.conDam.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1921(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1921};
  (data->simulationInfo->realParameter[219] /* damVal.conDam.uS_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[217] /* damVal.conDam.revAct PARAM */),(data->simulationInfo->realParameter[216] /* damVal.conDam.r PARAM */),"damVal.conDam.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 1928
type: SIMPLE_ASSIGN
damVal.conDam.I.y_start = damVal.conDam.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1928(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1928};
  (data->simulationInfo->realParameter[205] /* damVal.conDam.I.y_start PARAM */) = (data->simulationInfo->realParameter[220] /* damVal.conDam.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 1929
type: SIMPLE_ASSIGN
damVal.TiDam = TiDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1929(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1929};
  (data->simulationInfo->realParameter[196] /* damVal.TiDam PARAM */) = (data->simulationInfo->realParameter[4] /* TiDam PARAM */);
  TRACE_POP
}

/*
equation index: 1930
type: SIMPLE_ASSIGN
damVal.conDam.Ti = damVal.TiDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1930(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1930};
  (data->simulationInfo->realParameter[210] /* damVal.conDam.Ti PARAM */) = (data->simulationInfo->realParameter[196] /* damVal.TiDam PARAM */);
  TRACE_POP
}

/*
equation index: 1931
type: SIMPLE_ASSIGN
damVal.conDam.I.k = damVal.conDam.k / damVal.conDam.Ti
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1931(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1931};
  (data->simulationInfo->realParameter[204] /* damVal.conDam.I.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */),(data->simulationInfo->realParameter[210] /* damVal.conDam.Ti PARAM */),"damVal.conDam.Ti",equationIndexes);
  TRACE_POP
}

/*
equation index: 1932
type: SIMPLE_ASSIGN
damVal.conDam.P.k = damVal.conDam.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1932(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1932};
  (data->simulationInfo->realParameter[208] /* damVal.conDam.P.k PARAM */) = (data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */);
  TRACE_POP
}

/*
equation index: 1937
type: SIMPLE_ASSIGN
damVal.TdDam = TdDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1937(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1937};
  (data->simulationInfo->realParameter[194] /* damVal.TdDam PARAM */) = (data->simulationInfo->realParameter[1] /* TdDam PARAM */);
  TRACE_POP
}

/*
equation index: 1938
type: SIMPLE_ASSIGN
damVal.conDam.Td = damVal.TdDam
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1938(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1938};
  (data->simulationInfo->realParameter[209] /* damVal.conDam.Td PARAM */) = (data->simulationInfo->realParameter[194] /* damVal.TdDam PARAM */);
  TRACE_POP
}

/*
equation index: 1949
type: SIMPLE_ASSIGN
setPoi.cooSup.greHys.pre_y_start = setPoi.cooSup.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1949(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1949};
  (data->simulationInfo->booleanParameter[103] /* setPoi.cooSup.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[105] /* setPoi.cooSup.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 1969
type: SIMPLE_ASSIGN
setPoi.zonDisEff_heat = zonDisEff_heat
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1969(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1969};
  (data->simulationInfo->realParameter[358] /* setPoi.zonDisEff_heat PARAM */) = (data->simulationInfo->realParameter[465] /* zonDisEff_heat PARAM */);
  TRACE_POP
}

/*
equation index: 1970
type: SIMPLE_ASSIGN
setPoi.airDisEff.realFalse = setPoi.zonDisEff_heat
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1970(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1970};
  (data->simulationInfo->realParameter[331] /* setPoi.airDisEff.realFalse PARAM */) = (data->simulationInfo->realParameter[358] /* setPoi.zonDisEff_heat PARAM */);
  TRACE_POP
}

/*
equation index: 1971
type: SIMPLE_ASSIGN
setPoi.zonDisEff_cool = zonDisEff_cool
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1971(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1971};
  (data->simulationInfo->realParameter[357] /* setPoi.zonDisEff_cool PARAM */) = (data->simulationInfo->realParameter[464] /* zonDisEff_cool PARAM */);
  TRACE_POP
}

/*
equation index: 1972
type: SIMPLE_ASSIGN
setPoi.airDisEff.realTrue = setPoi.zonDisEff_cool
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1972(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1972};
  (data->simulationInfo->realParameter[332] /* setPoi.airDisEff.realTrue PARAM */) = (data->simulationInfo->realParameter[357] /* setPoi.zonDisEff_cool PARAM */);
  TRACE_POP
}

/*
equation index: 1983
type: SIMPLE_ASSIGN
timSup.samplePeriod = samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1983(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1983};
  (data->simulationInfo->realParameter[451] /* timSup.samplePeriod PARAM */) = (data->simulationInfo->realParameter[319] /* samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 1984
type: SIMPLE_ASSIGN
timSup.truDel.delayTime = timSup.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1984(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1984};
  (data->simulationInfo->realParameter[456] /* timSup.truDel.delayTime PARAM */) = (data->simulationInfo->realParameter[451] /* timSup.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 1992
type: SIMPLE_ASSIGN
timSup.chaRat = chaRat
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1992(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1992};
  (data->simulationInfo->realParameter[437] /* timSup.chaRat PARAM */) = (data->simulationInfo->realParameter[114] /* chaRat PARAM */);
  TRACE_POP
}

/*
equation index: 1993
type: SIMPLE_ASSIGN
timSup.gai.k = timSup.chaRat
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1993(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1993};
  (data->simulationInfo->realParameter[440] /* timSup.gai.k PARAM */) = (data->simulationInfo->realParameter[437] /* timSup.chaRat PARAM */);
  TRACE_POP
}

/*
equation index: 1995
type: SIMPLE_ASSIGN
timSup.greThr.greHys.pre_y_start = timSup.greThr.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_1995(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1995};
  (data->simulationInfo->booleanParameter[162] /* timSup.greThr.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[164] /* timSup.greThr.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2005
type: SIMPLE_ASSIGN
timSup.uniDel.samplePeriod = timSup.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2005(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2005};
  (data->simulationInfo->realParameter[458] /* timSup.uniDel.samplePeriod PARAM */) = (data->simulationInfo->realParameter[451] /* timSup.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2006
type: SIMPLE_ASSIGN
timSup.samSet.samplePeriod = timSup.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2006(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2006};
  (data->simulationInfo->realParameter[449] /* timSup.samSet.samplePeriod PARAM */) = (data->simulationInfo->realParameter[451] /* timSup.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2018
type: SIMPLE_ASSIGN
ala.staTim = staTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2018(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2018};
  (data->simulationInfo->realParameter[95] /* ala.staTim PARAM */) = (data->simulationInfo->realParameter[361] /* staTim PARAM */);
  TRACE_POP
}

/*
equation index: 2019
type: SIMPLE_ASSIGN
ala.fanIni.delayTime = ala.staTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2019(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2019};
  (data->simulationInfo->realParameter[56] /* ala.fanIni.delayTime PARAM */) = (data->simulationInfo->realParameter[95] /* ala.staTim PARAM */);
  TRACE_POP
}

/*
equation index: 2021
type: SIMPLE_ASSIGN
ala.lowFloTim = lowFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2021(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2021};
  (data->simulationInfo->realParameter[92] /* ala.lowFloTim PARAM */) = (data->simulationInfo->realParameter[316] /* lowFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2022
type: SIMPLE_ASSIGN
ala.truDel7.delayTime = ala.lowFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2022(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2022};
  (data->simulationInfo->realParameter[110] /* ala.truDel7.delayTime PARAM */) = (data->simulationInfo->realParameter[92] /* ala.lowFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2023
type: SIMPLE_ASSIGN
ala.assMes6.message = "Warning: the valve is leaking."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2023(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2023};
  (data->simulationInfo->stringParameter[6] /* ala.assMes6.message PARAM */) = _OMC_LIT1;
  TRACE_POP
}

/*
equation index: 2027
type: SIMPLE_ASSIGN
ala.gre2.greHys.pre_y_start = ala.gre2.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2027(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2027};
  (data->simulationInfo->booleanParameter[13] /* ala.gre2.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[15] /* ala.gre2.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2033
type: SIMPLE_ASSIGN
ala.cloVal.lesHys.pre_y_start = ala.cloVal.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2033(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2033};
  (data->simulationInfo->booleanParameter[4] /* ala.cloVal.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[5] /* ala.cloVal.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2040
type: SIMPLE_ASSIGN
ala.valCloTim = valCloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2040(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2040};
  (data->simulationInfo->realParameter[112] /* ala.valCloTim PARAM */) = (data->simulationInfo->realParameter[462] /* valCloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2041
type: SIMPLE_ASSIGN
ala.truDel6.delayTime = ala.valCloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2041(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2041};
  (data->simulationInfo->realParameter[108] /* ala.truDel6.delayTime PARAM */) = (data->simulationInfo->realParameter[112] /* ala.valCloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2045
type: SIMPLE_ASSIGN
ala.greThr2.greNoHys.t = ala.greThr2.t
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2045(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2045};
  (data->simulationInfo->realParameter[79] /* ala.greThr2.greNoHys.t PARAM */) = (data->simulationInfo->realParameter[82] /* ala.greThr2.t PARAM */);
  TRACE_POP
}

/*
equation index: 2049
type: SIMPLE_ASSIGN
ala.assMes5.message = "Warning: discharge air temperature is 8 degC less than the setpoint."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2049(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2049};
  (data->simulationInfo->stringParameter[5] /* ala.assMes5.message PARAM */) = _OMC_LIT2;
  TRACE_POP
}

/*
equation index: 2053
type: SIMPLE_ASSIGN
ala.assMes4.message = "Warning: discharge air temperature is 17 degC less than the setpoint."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2053(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2053};
  (data->simulationInfo->stringParameter[4] /* ala.assMes4.message PARAM */) = _OMC_LIT3;
  TRACE_POP
}

/*
equation index: 2055
type: SIMPLE_ASSIGN
ala.lowTemTim = lowTemTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2055(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2055};
  (data->simulationInfo->realParameter[93] /* ala.lowTemTim PARAM */) = (data->simulationInfo->realParameter[317] /* lowTemTim PARAM */);
  TRACE_POP
}

/*
equation index: 2056
type: SIMPLE_ASSIGN
ala.truDel5.delayTime = ala.lowTemTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2056(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2056};
  (data->simulationInfo->realParameter[106] /* ala.truDel5.delayTime PARAM */) = (data->simulationInfo->realParameter[93] /* ala.lowTemTim PARAM */);
  TRACE_POP
}

/*
equation index: 2058
type: SIMPLE_ASSIGN
ala.truDel4.delayTime = ala.lowTemTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2058(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2058};
  (data->simulationInfo->realParameter[104] /* ala.truDel4.delayTime PARAM */) = (data->simulationInfo->realParameter[93] /* ala.lowTemTim PARAM */);
  TRACE_POP
}

/*
equation index: 2061
type: SIMPLE_ASSIGN
ala.les2.lesHys.pre_y_start = ala.les2.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2061(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2061};
  (data->simulationInfo->booleanParameter[30] /* ala.les2.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[31] /* ala.les2.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2067
type: SIMPLE_ASSIGN
ala.les1.lesHys.pre_y_start = ala.les1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2067(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2067};
  (data->simulationInfo->booleanParameter[27] /* ala.les1.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[28] /* ala.les1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2073
type: SIMPLE_ASSIGN
ala.assMes3.message = "Warning: the damper is leaking."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2073(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2073};
  (data->simulationInfo->stringParameter[3] /* ala.assMes3.message PARAM */) = _OMC_LIT4;
  TRACE_POP
}

/*
equation index: 2075
type: SIMPLE_ASSIGN
ala.cloDam.lesHys.pre_y_start = ala.cloDam.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2075(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2075};
  (data->simulationInfo->booleanParameter[1] /* ala.cloDam.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[2] /* ala.cloDam.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2082
type: SIMPLE_ASSIGN
ala.leaFloTim = leaFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2082(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2082};
  (data->simulationInfo->realParameter[85] /* ala.leaFloTim PARAM */) = (data->simulationInfo->realParameter[314] /* leaFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2083
type: SIMPLE_ASSIGN
ala.truDel3.delayTime = ala.leaFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2083(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2083};
  (data->simulationInfo->realParameter[102] /* ala.truDel3.delayTime PARAM */) = (data->simulationInfo->realParameter[85] /* ala.leaFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2086
type: SIMPLE_ASSIGN
ala.assMes2.message = "Warning: airflow sensor should be calibrated."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2086(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2086};
  (data->simulationInfo->stringParameter[2] /* ala.assMes2.message PARAM */) = _OMC_LIT5;
  TRACE_POP
}

/*
equation index: 2088
type: SIMPLE_ASSIGN
ala.gre1.greHys.pre_y_start = ala.gre1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2088(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2088};
  (data->simulationInfo->booleanParameter[10] /* ala.gre1.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[12] /* ala.gre1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2093
type: SIMPLE_ASSIGN
ala.fanOffTim = fanOffTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2093(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2093};
  (data->simulationInfo->realParameter[58] /* ala.fanOffTim PARAM */) = (data->simulationInfo->realParameter[306] /* fanOffTim PARAM */);
  TRACE_POP
}

/*
equation index: 2094
type: SIMPLE_ASSIGN
ala.truDel2.delayTime = ala.fanOffTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2094(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2094};
  (data->simulationInfo->realParameter[100] /* ala.truDel2.delayTime PARAM */) = (data->simulationInfo->realParameter[58] /* ala.fanOffTim PARAM */);
  TRACE_POP
}

/*
equation index: 2096
type: SIMPLE_ASSIGN
ala.assMes1.message = "Warning: airflow is less than 70% of the setpoint."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2096(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2096};
  (data->simulationInfo->stringParameter[1] /* ala.assMes1.message PARAM */) = _OMC_LIT6;
  TRACE_POP
}

/*
equation index: 2097
type: SIMPLE_ASSIGN
ala.assMes.message = "Warning: airflow is less than 50% of the setpoint."
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2097(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2097};
  (data->simulationInfo->stringParameter[0] /* ala.assMes.message PARAM */) = _OMC_LIT7;
  TRACE_POP
}

/*
equation index: 2101
type: SIMPLE_ASSIGN
ala.greThr1.greNoHys.t = ala.greThr1.t
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2101(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2101};
  (data->simulationInfo->realParameter[74] /* ala.greThr1.greNoHys.t PARAM */) = (data->simulationInfo->realParameter[77] /* ala.greThr1.t PARAM */);
  TRACE_POP
}

/*
equation index: 2109
type: SIMPLE_ASSIGN
ala.truDel1.delayTime = ala.lowFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2109(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2109};
  (data->simulationInfo->realParameter[98] /* ala.truDel1.delayTime PARAM */) = (data->simulationInfo->realParameter[92] /* ala.lowFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2112
type: SIMPLE_ASSIGN
ala.gre.greHys.pre_y_start = ala.gre.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2112(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2112};
  (data->simulationInfo->booleanParameter[7] /* ala.gre.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[9] /* ala.gre.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2117
type: SIMPLE_ASSIGN
ala.greThr.greHys.pre_y_start = ala.greThr.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2117(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2117};
  (data->simulationInfo->booleanParameter[16] /* ala.greThr.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[18] /* ala.greThr.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2124
type: SIMPLE_ASSIGN
ala.truDel.delayTime = ala.lowFloTim
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2124(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2124};
  (data->simulationInfo->realParameter[96] /* ala.truDel.delayTime PARAM */) = (data->simulationInfo->realParameter[92] /* ala.lowFloTim PARAM */);
  TRACE_POP
}

/*
equation index: 2126
type: SIMPLE_ASSIGN
ala.les.lesHys.pre_y_start = ala.les.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2126(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2126};
  (data->simulationInfo->booleanParameter[24] /* ala.les.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[25] /* ala.les.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2137
type: SIMPLE_ASSIGN
conLoo.zerCon1.lesHys.pre_y_start = conLoo.zerCon1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2137(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2137};
  (data->simulationInfo->booleanParameter[64] /* conLoo.zerCon1.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[65] /* conLoo.zerCon1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2144
type: SIMPLE_ASSIGN
conLoo.zerCon.lesHys.pre_y_start = conLoo.zerCon.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2144(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2144};
  (data->simulationInfo->booleanParameter[61] /* conLoo.zerCon.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[62] /* conLoo.zerCon.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2153
type: SIMPLE_ASSIGN
conLoo.timChe = timChe
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2153(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2153};
  (data->simulationInfo->realParameter[177] /* conLoo.timChe PARAM */) = (data->simulationInfo->realParameter[436] /* timChe PARAM */);
  TRACE_POP
}

/*
equation index: 2154
type: SIMPLE_ASSIGN
conLoo.disHea.delayTime = conLoo.timChe
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2154(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2154};
  (data->simulationInfo->realParameter[168] /* conLoo.disHea.delayTime PARAM */) = (data->simulationInfo->realParameter[177] /* conLoo.timChe PARAM */);
  TRACE_POP
}

/*
equation index: 2158
type: SIMPLE_ASSIGN
conLoo.disCoo.delayTime = conLoo.timChe
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2158(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2158};
  (data->simulationInfo->realParameter[166] /* conLoo.disCoo.delayTime PARAM */) = (data->simulationInfo->realParameter[177] /* conLoo.timChe PARAM */);
  TRACE_POP
}

/*
equation index: 2160
type: SIMPLE_ASSIGN
conLoo.enaCooLoo.lesHys.pre_y_start = conLoo.enaCooLoo.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2160(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2160};
  (data->simulationInfo->booleanParameter[55] /* conLoo.enaCooLoo.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[56] /* conLoo.enaCooLoo.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2165
type: SIMPLE_ASSIGN
conLoo.enaHeaLoo.lesHys.pre_y_start = conLoo.enaHeaLoo.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2165(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2165};
  (data->simulationInfo->booleanParameter[58] /* conLoo.enaHeaLoo.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[59] /* conLoo.enaHeaLoo.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2169
type: SIMPLE_ASSIGN
conLoo.conHea.assMesYMinMax.message = "LimPID: Limits must be yMin < yMax"
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2169(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2169};
  (data->simulationInfo->stringParameter[8] /* conLoo.conHea.assMesYMinMax.message PARAM */) = _OMC_LIT0;
  TRACE_POP
}

/*
equation index: 2170
type: SIMPLE_ASSIGN
conLoo.kHeaCon = kHeaCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2170(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2170};
  (data->simulationInfo->realParameter[175] /* conLoo.kHeaCon PARAM */) = (data->simulationInfo->realParameter[312] /* kHeaCon PARAM */);
  TRACE_POP
}

/*
equation index: 2171
type: SIMPLE_ASSIGN
conLoo.conHea.k = conLoo.kHeaCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2171(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2171};
  (data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */) = (data->simulationInfo->realParameter[175] /* conLoo.kHeaCon PARAM */);
  TRACE_POP
}

/*
equation index: 2173
type: SIMPLE_ASSIGN
conLoo.conHea.antWinGai.k = 1.0 / (conLoo.conHea.Ni * conLoo.conHea.k)
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2173(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2173};
  (data->simulationInfo->realParameter[150] /* conLoo.conHea.antWinGai.k PARAM */) = DIVISION_SIM(1.0,((data->simulationInfo->realParameter[145] /* conLoo.conHea.Ni PARAM */)) * ((data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */)),"conLoo.conHea.Ni * conLoo.conHea.k",equationIndexes);
  TRACE_POP
}

/*
equation index: 2176
type: SIMPLE_ASSIGN
conLoo.conHea.revAct = if conLoo.conHea.reverseActing then 1.0 else -1.0
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2176(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2176};
  (data->simulationInfo->realParameter[155] /* conLoo.conHea.revAct PARAM */) = ((data->simulationInfo->booleanParameter[49] /* conLoo.conHea.reverseActing PARAM */)?1.0:-1.0);
  TRACE_POP
}

/*
equation index: 2177
type: SIMPLE_ASSIGN
conLoo.conHea.uMea_revAct.k = conLoo.conHea.revAct / conLoo.conHea.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2177(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2177};
  (data->simulationInfo->realParameter[156] /* conLoo.conHea.uMea_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[155] /* conLoo.conHea.revAct PARAM */),(data->simulationInfo->realParameter[154] /* conLoo.conHea.r PARAM */),"conLoo.conHea.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 2178
type: SIMPLE_ASSIGN
conLoo.conHea.uS_revAct.k = conLoo.conHea.revAct / conLoo.conHea.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2178(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2178};
  (data->simulationInfo->realParameter[157] /* conLoo.conHea.uS_revAct.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[155] /* conLoo.conHea.revAct PARAM */),(data->simulationInfo->realParameter[154] /* conLoo.conHea.r PARAM */),"conLoo.conHea.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 2182
type: SIMPLE_ASSIGN
conLoo.conHea.lim.uMin = conLoo.conHea.yMin
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2182(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2182};
  (data->simulationInfo->realParameter[153] /* conLoo.conHea.lim.uMin PARAM */) = (data->simulationInfo->realParameter[160] /* conLoo.conHea.yMin PARAM */);
  TRACE_POP
}

/*
equation index: 2183
type: SIMPLE_ASSIGN
conLoo.conHea.lim.uMax = conLoo.conHea.yMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2183(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2183};
  (data->simulationInfo->realParameter[152] /* conLoo.conHea.lim.uMax PARAM */) = (data->simulationInfo->realParameter[159] /* conLoo.conHea.yMax PARAM */);
  TRACE_POP
}

/*
equation index: 2184
type: SIMPLE_ASSIGN
conLoo.conHea.I.y_start = conLoo.conHea.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2184(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2184};
  (data->simulationInfo->realParameter[143] /* conLoo.conHea.I.y_start PARAM */) = (data->simulationInfo->realParameter[158] /* conLoo.conHea.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 2185
type: SIMPLE_ASSIGN
conLoo.TiHeaCon = TiHeaCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2185(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2185};
  (data->simulationInfo->realParameter[116] /* conLoo.TiHeaCon PARAM */) = (data->simulationInfo->realParameter[5] /* TiHeaCon PARAM */);
  TRACE_POP
}

/*
equation index: 2186
type: SIMPLE_ASSIGN
conLoo.conHea.Ti = conLoo.TiHeaCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2186(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2186};
  (data->simulationInfo->realParameter[148] /* conLoo.conHea.Ti PARAM */) = (data->simulationInfo->realParameter[116] /* conLoo.TiHeaCon PARAM */);
  TRACE_POP
}

/*
equation index: 2187
type: SIMPLE_ASSIGN
conLoo.conHea.I.k = conLoo.conHea.k / conLoo.conHea.Ti
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2187(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2187};
  (data->simulationInfo->realParameter[142] /* conLoo.conHea.I.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */),(data->simulationInfo->realParameter[148] /* conLoo.conHea.Ti PARAM */),"conLoo.conHea.Ti",equationIndexes);
  TRACE_POP
}

/*
equation index: 2188
type: SIMPLE_ASSIGN
conLoo.conHea.P.k = conLoo.conHea.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2188(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2188};
  (data->simulationInfo->realParameter[146] /* conLoo.conHea.P.k PARAM */) = (data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */);
  TRACE_POP
}

/*
equation index: 2193
type: SIMPLE_ASSIGN
conLoo.conCoo.assMesYMinMax.message = "LimPID: Limits must be yMin < yMax"
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2193(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2193};
  (data->simulationInfo->stringParameter[7] /* conLoo.conCoo.assMesYMinMax.message PARAM */) = _OMC_LIT0;
  TRACE_POP
}

/*
equation index: 2194
type: SIMPLE_ASSIGN
conLoo.kCooCon = kCooCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2194(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2194};
  (data->simulationInfo->realParameter[174] /* conLoo.kCooCon PARAM */) = (data->simulationInfo->realParameter[310] /* kCooCon PARAM */);
  TRACE_POP
}

/*
equation index: 2195
type: SIMPLE_ASSIGN
conLoo.conCoo.k = conLoo.kCooCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2195(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2195};
  (data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */) = (data->simulationInfo->realParameter[174] /* conLoo.kCooCon PARAM */);
  TRACE_POP
}

/*
equation index: 2197
type: SIMPLE_ASSIGN
conLoo.conCoo.antWinGai.k = 1.0 / (conLoo.conCoo.Ni * conLoo.conCoo.k)
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2197(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2197};
  (data->simulationInfo->realParameter[126] /* conLoo.conCoo.antWinGai.k PARAM */) = DIVISION_SIM(1.0,((data->simulationInfo->realParameter[121] /* conLoo.conCoo.Ni PARAM */)) * ((data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */)),"conLoo.conCoo.Ni * conLoo.conCoo.k",equationIndexes);
  TRACE_POP
}

/*
equation index: 2199
type: SIMPLE_ASSIGN
conLoo.conCoo.uMea_revAct.k = (-1.0) / conLoo.conCoo.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2199(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2199};
  (data->simulationInfo->realParameter[132] /* conLoo.conCoo.uMea_revAct.k PARAM */) = DIVISION_SIM(-1.0,(data->simulationInfo->realParameter[130] /* conLoo.conCoo.r PARAM */),"conLoo.conCoo.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 2200
type: SIMPLE_ASSIGN
conLoo.conCoo.uS_revAct.k = (-1.0) / conLoo.conCoo.r
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2200(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2200};
  (data->simulationInfo->realParameter[133] /* conLoo.conCoo.uS_revAct.k PARAM */) = DIVISION_SIM(-1.0,(data->simulationInfo->realParameter[130] /* conLoo.conCoo.r PARAM */),"conLoo.conCoo.r",equationIndexes);
  TRACE_POP
}

/*
equation index: 2205
type: SIMPLE_ASSIGN
conLoo.conCoo.lim.uMin = conLoo.conCoo.yMin
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2205(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2205};
  (data->simulationInfo->realParameter[129] /* conLoo.conCoo.lim.uMin PARAM */) = (data->simulationInfo->realParameter[136] /* conLoo.conCoo.yMin PARAM */);
  TRACE_POP
}

/*
equation index: 2206
type: SIMPLE_ASSIGN
conLoo.conCoo.lim.uMax = conLoo.conCoo.yMax
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2206(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2206};
  (data->simulationInfo->realParameter[128] /* conLoo.conCoo.lim.uMax PARAM */) = (data->simulationInfo->realParameter[135] /* conLoo.conCoo.yMax PARAM */);
  TRACE_POP
}

/*
equation index: 2207
type: SIMPLE_ASSIGN
conLoo.conCoo.I.y_start = conLoo.conCoo.xi_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2207(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2207};
  (data->simulationInfo->realParameter[119] /* conLoo.conCoo.I.y_start PARAM */) = (data->simulationInfo->realParameter[134] /* conLoo.conCoo.xi_start PARAM */);
  TRACE_POP
}

/*
equation index: 2208
type: SIMPLE_ASSIGN
conLoo.TiCooCon = TiCooCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2208(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2208};
  (data->simulationInfo->realParameter[115] /* conLoo.TiCooCon PARAM */) = (data->simulationInfo->realParameter[3] /* TiCooCon PARAM */);
  TRACE_POP
}

/*
equation index: 2209
type: SIMPLE_ASSIGN
conLoo.conCoo.Ti = conLoo.TiCooCon
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2209(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2209};
  (data->simulationInfo->realParameter[124] /* conLoo.conCoo.Ti PARAM */) = (data->simulationInfo->realParameter[115] /* conLoo.TiCooCon PARAM */);
  TRACE_POP
}

/*
equation index: 2210
type: SIMPLE_ASSIGN
conLoo.conCoo.I.k = conLoo.conCoo.k / conLoo.conCoo.Ti
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2210(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2210};
  (data->simulationInfo->realParameter[118] /* conLoo.conCoo.I.k PARAM */) = DIVISION_SIM((data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */),(data->simulationInfo->realParameter[124] /* conLoo.conCoo.Ti PARAM */),"conLoo.conCoo.Ti",equationIndexes);
  TRACE_POP
}

/*
equation index: 2211
type: SIMPLE_ASSIGN
conLoo.conCoo.P.k = conLoo.conCoo.k
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2211(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2211};
  (data->simulationInfo->realParameter[122] /* conLoo.conCoo.P.k PARAM */) = (data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */);
  TRACE_POP
}

/*
equation index: 2219
type: SIMPLE_ASSIGN
sysReq.samplePeriod = samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2219(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2219};
  (data->simulationInfo->realParameter[409] /* sysReq.samplePeriod PARAM */) = (data->simulationInfo->realParameter[319] /* samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2220
type: SIMPLE_ASSIGN
sysReq.sampler3.samplePeriod = sysReq.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2220(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2220};
  (data->simulationInfo->realParameter[416] /* sysReq.sampler3.samplePeriod PARAM */) = (data->simulationInfo->realParameter[409] /* sysReq.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2221
type: SIMPLE_ASSIGN
sysReq.sampler2.samplePeriod = sysReq.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2221(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2221};
  (data->simulationInfo->realParameter[414] /* sysReq.sampler2.samplePeriod PARAM */) = (data->simulationInfo->realParameter[409] /* sysReq.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2222
type: SIMPLE_ASSIGN
sysReq.sampler1.samplePeriod = sysReq.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2222(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2222};
  (data->simulationInfo->realParameter[412] /* sysReq.sampler1.samplePeriod PARAM */) = (data->simulationInfo->realParameter[409] /* sysReq.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2223
type: SIMPLE_ASSIGN
sysReq.sampler.samplePeriod = sysReq.samplePeriod
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2223(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2223};
  (data->simulationInfo->realParameter[410] /* sysReq.sampler.samplePeriod PARAM */) = (data->simulationInfo->realParameter[409] /* sysReq.samplePeriod PARAM */);
  TRACE_POP
}

/*
equation index: 2227
type: SIMPLE_ASSIGN
sysReq.greThr6.greHys.pre_y_start = sysReq.greThr6.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2227(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2227};
  (data->simulationInfo->booleanParameter[145] /* sysReq.greThr6.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[147] /* sysReq.greThr6.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2236
type: SIMPLE_ASSIGN
sysReq.greThr5.greHys.pre_y_start = sysReq.greThr5.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2236(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2236};
  (data->simulationInfo->booleanParameter[142] /* sysReq.greThr5.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[144] /* sysReq.greThr5.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2243
type: SIMPLE_ASSIGN
sysReq.durTimDisAir = durTimDisAir
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2243(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2243};
  (data->simulationInfo->realParameter[366] /* sysReq.durTimDisAir PARAM */) = (data->simulationInfo->realParameter[303] /* durTimDisAir PARAM */);
  TRACE_POP
}

/*
equation index: 2244
type: SIMPLE_ASSIGN
sysReq.tim5.delayTime = sysReq.durTimDisAir
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2244(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2244};
  (data->simulationInfo->realParameter[429] /* sysReq.tim5.delayTime PARAM */) = (data->simulationInfo->realParameter[366] /* sysReq.durTimDisAir PARAM */);
  TRACE_POP
}

/*
equation index: 2246
type: SIMPLE_ASSIGN
sysReq.tim4.delayTime = sysReq.durTimDisAir
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2246(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2246};
  (data->simulationInfo->realParameter[427] /* sysReq.tim4.delayTime PARAM */) = (data->simulationInfo->realParameter[366] /* sysReq.durTimDisAir PARAM */);
  TRACE_POP
}

/*
equation index: 2249
type: SIMPLE_ASSIGN
sysReq.thrTDis_2 = thrTDis_2
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2249(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2249};
  (data->simulationInfo->realParameter[419] /* sysReq.thrTDis_2 PARAM */) = (data->simulationInfo->realParameter[434] /* thrTDis_2 PARAM */);
  TRACE_POP
}

/*
equation index: 2250
type: SIMPLE_ASSIGN
sysReq.addPar1.p = sysReq.thrTDis_2
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2250(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2250};
  (data->simulationInfo->realParameter[363] /* sysReq.addPar1.p PARAM */) = (data->simulationInfo->realParameter[419] /* sysReq.thrTDis_2 PARAM */);
  TRACE_POP
}

/*
equation index: 2251
type: SIMPLE_ASSIGN
sysReq.thrTDis_1 = thrTDis_1
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2251(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2251};
  (data->simulationInfo->realParameter[418] /* sysReq.thrTDis_1 PARAM */) = (data->simulationInfo->realParameter[433] /* thrTDis_1 PARAM */);
  TRACE_POP
}

/*
equation index: 2252
type: SIMPLE_ASSIGN
sysReq.addPar.p = sysReq.thrTDis_1
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2252(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2252};
  (data->simulationInfo->realParameter[362] /* sysReq.addPar.p PARAM */) = (data->simulationInfo->realParameter[418] /* sysReq.thrTDis_1 PARAM */);
  TRACE_POP
}

/*
equation index: 2254
type: SIMPLE_ASSIGN
sysReq.greEqu1.greHys.pre_y_start = sysReq.greEqu1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2254(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2254};
  (data->simulationInfo->booleanParameter[124] /* sysReq.greEqu1.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[126] /* sysReq.greEqu1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2259
type: SIMPLE_ASSIGN
sysReq.greEqu.greHys.pre_y_start = sysReq.greEqu.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2259(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2259};
  (data->simulationInfo->booleanParameter[121] /* sysReq.greEqu.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[123] /* sysReq.greEqu.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2264
type: SIMPLE_ASSIGN
sysReq.durTimFlo = durTimFlo
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2264(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2264};
  (data->simulationInfo->realParameter[367] /* sysReq.durTimFlo PARAM */) = (data->simulationInfo->realParameter[304] /* durTimFlo PARAM */);
  TRACE_POP
}

/*
equation index: 2265
type: SIMPLE_ASSIGN
sysReq.tim3.delayTime = sysReq.durTimFlo
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2265(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2265};
  (data->simulationInfo->realParameter[425] /* sysReq.tim3.delayTime PARAM */) = (data->simulationInfo->realParameter[367] /* sysReq.durTimFlo PARAM */);
  TRACE_POP
}

/*
equation index: 2267
type: SIMPLE_ASSIGN
sysReq.durTimTem = durTimTem
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2267(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2267};
  (data->simulationInfo->realParameter[368] /* sysReq.durTimTem PARAM */) = (data->simulationInfo->realParameter[305] /* durTimTem PARAM */);
  TRACE_POP
}

/*
equation index: 2268
type: SIMPLE_ASSIGN
sysReq.tim2.delayTime = sysReq.durTimTem
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2268(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2268};
  (data->simulationInfo->realParameter[423] /* sysReq.tim2.delayTime PARAM */) = (data->simulationInfo->realParameter[368] /* sysReq.durTimTem PARAM */);
  TRACE_POP
}

/*
equation index: 2270
type: SIMPLE_ASSIGN
sysReq.tim1.delayTime = sysReq.durTimTem
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2270(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2270};
  (data->simulationInfo->realParameter[421] /* sysReq.tim1.delayTime PARAM */) = (data->simulationInfo->realParameter[368] /* sysReq.durTimTem PARAM */);
  TRACE_POP
}

/*
equation index: 2282
type: SIMPLE_ASSIGN
sysReq.greThr4.greHys.pre_y_start = sysReq.greThr4.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2282(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2282};
  (data->simulationInfo->booleanParameter[139] /* sysReq.greThr4.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[141] /* sysReq.greThr4.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2289
type: SIMPLE_ASSIGN
sysReq.greThr.greHys.pre_y_start = sysReq.greThr.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2289(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2289};
  (data->simulationInfo->booleanParameter[127] /* sysReq.greThr.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[129] /* sysReq.greThr.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2296
type: SIMPLE_ASSIGN
sysReq.greThr3.greHys.pre_y_start = sysReq.greThr3.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2296(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2296};
  (data->simulationInfo->booleanParameter[136] /* sysReq.greThr3.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[138] /* sysReq.greThr3.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2303
type: SIMPLE_ASSIGN
sysReq.greThr2.greHys.pre_y_start = sysReq.greThr2.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2303(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2303};
  (data->simulationInfo->booleanParameter[133] /* sysReq.greThr2.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[135] /* sysReq.greThr2.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2305
type: SIMPLE_ASSIGN
sysReq.twoTemDif = twoTemDif
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2305(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2305};
  (data->simulationInfo->realParameter[431] /* sysReq.twoTemDif PARAM */) = (data->simulationInfo->realParameter[461] /* twoTemDif PARAM */);
  TRACE_POP
}

/*
equation index: 2306
type: SIMPLE_ASSIGN
sysReq.greThr2.t = sysReq.twoTemDif
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2306(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2306};
  (data->simulationInfo->realParameter[387] /* sysReq.greThr2.t PARAM */) = (data->simulationInfo->realParameter[431] /* sysReq.twoTemDif PARAM */);
  TRACE_POP
}

/*
equation index: 2307
type: SIMPLE_ASSIGN
sysReq.greThr2.greHys.t = sysReq.greThr2.t
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2307(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2307};
  (data->simulationInfo->realParameter[385] /* sysReq.greThr2.greHys.t PARAM */) = (data->simulationInfo->realParameter[387] /* sysReq.greThr2.t PARAM */);
  TRACE_POP
}

/*
equation index: 2311
type: SIMPLE_ASSIGN
sysReq.greThr1.greHys.pre_y_start = sysReq.greThr1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2311(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2311};
  (data->simulationInfo->booleanParameter[130] /* sysReq.greThr1.greHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[132] /* sysReq.greThr1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2313
type: SIMPLE_ASSIGN
sysReq.thrTemDif = thrTemDif
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2313(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2313};
  (data->simulationInfo->realParameter[420] /* sysReq.thrTemDif PARAM */) = (data->simulationInfo->realParameter[435] /* thrTemDif PARAM */);
  TRACE_POP
}

/*
equation index: 2314
type: SIMPLE_ASSIGN
sysReq.greThr1.t = sysReq.thrTemDif
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2314(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2314};
  (data->simulationInfo->realParameter[383] /* sysReq.greThr1.t PARAM */) = (data->simulationInfo->realParameter[420] /* sysReq.thrTemDif PARAM */);
  TRACE_POP
}

/*
equation index: 2315
type: SIMPLE_ASSIGN
sysReq.greThr1.greHys.t = sysReq.greThr1.t
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2315(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2315};
  (data->simulationInfo->realParameter[381] /* sysReq.greThr1.greHys.t PARAM */) = (data->simulationInfo->realParameter[383] /* sysReq.greThr1.t PARAM */);
  TRACE_POP
}

/*
equation index: 2319
type: SIMPLE_ASSIGN
sysReq.les1.lesHys.pre_y_start = sysReq.les1.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2319(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2319};
  (data->simulationInfo->booleanParameter[152] /* sysReq.les1.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[153] /* sysReq.les1.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2324
type: SIMPLE_ASSIGN
sysReq.les.lesHys.pre_y_start = sysReq.les.pre_y_start
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2324(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2324};
  (data->simulationInfo->booleanParameter[149] /* sysReq.les.lesHys.pre_y_start PARAM */) = (data->simulationInfo->booleanParameter[150] /* sysReq.les.pre_y_start PARAM */);
  TRACE_POP
}

/*
equation index: 2337
type: SIMPLE_ASSIGN
actAirSet.heaMaxFlo1.realTrue = actAirSet.VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2337(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2337};
  (data->simulationInfo->realParameter[27] /* actAirSet.heaMaxFlo1.realTrue PARAM */) = (data->simulationInfo->realParameter[16] /* actAirSet.VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 2339
type: SIMPLE_ASSIGN
actAirSet.VCooMax_flow = VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2339(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2339};
  (data->simulationInfo->realParameter[15] /* actAirSet.VCooMax_flow PARAM */) = (data->simulationInfo->realParameter[9] /* VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 2340
type: SIMPLE_ASSIGN
actAirSet.cooMaxFlo.realTrue = actAirSet.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2340(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2340};
  (data->simulationInfo->realParameter[21] /* actAirSet.cooMaxFlo.realTrue PARAM */) = (data->simulationInfo->realParameter[15] /* actAirSet.VCooMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 2342
type: SIMPLE_ASSIGN
actAirSet.heaMaxFlo.realTrue = actAirSet.VHeaMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2342(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2342};
  (data->simulationInfo->realParameter[25] /* actAirSet.heaMaxFlo.realTrue PARAM */) = (data->simulationInfo->realParameter[16] /* actAirSet.VHeaMax_flow PARAM */);
  TRACE_POP
}

/*
equation index: 2344
type: SIMPLE_ASSIGN
actAirSet.heaMinFlo.realTrue = actAirSet.VHeaMin_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2344(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2344};
  (data->simulationInfo->realParameter[31] /* actAirSet.heaMinFlo.realTrue PARAM */) = (data->simulationInfo->realParameter[17] /* actAirSet.VHeaMin_flow PARAM */);
  TRACE_POP
}

/*
equation index: 2348
type: SIMPLE_ASSIGN
actAirSet.actCooMax.realTrue = actAirSet.VCooMax_flow
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2348(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2348};
  (data->simulationInfo->realParameter[19] /* actAirSet.actCooMax.realTrue PARAM */) = (data->simulationInfo->realParameter[15] /* actAirSet.VCooMax_flow PARAM */);
  TRACE_POP
}
extern void ReheatControllerFMU_eqFunction_467(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_466(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_465(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_464(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_463(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_462(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_461(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_460(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_459(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_458(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_457(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_456(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_455(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_454(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_453(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_452(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_451(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_450(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_449(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_448(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_447(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_446(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_445(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_444(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_443(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_442(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_441(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_440(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_439(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_438(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_437(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_436(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_435(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_434(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_433(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_432(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_431(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_430(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_429(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_428(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_427(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_13(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_12(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_10(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_8(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_5(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_4(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_3(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_6(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_7(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_426(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_9(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_11(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_14(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_2(DATA *data, threadData_t *threadData);

extern void ReheatControllerFMU_eqFunction_1(DATA *data, threadData_t *threadData);


/*
equation index: 2422
type: ALGORITHM

  assert(damVal.greThr2.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr2.greHys.h, has value: " + String(damVal.greThr2.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2422(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2422};
  modelica_boolean tmp2;
  static const MMC_DEFSTRINGLIT(tmp3,78,"Variable violating min constraint: 0.0 <= damVal.greThr2.greHys.h, has value: ");
  modelica_string tmp4;
  modelica_metatype tmpMeta5;
  static int tmp6 = 0;
  if(!tmp6)
  {
    tmp2 = GreaterEq((data->simulationInfo->realParameter[274] /* damVal.greThr2.greHys.h PARAM */),0.0);
    if(!tmp2)
    {
      tmp4 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[274] /* damVal.greThr2.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta5 = stringAppend(MMC_REFSTRINGLIT(tmp3),tmp4);
      {
        const char* assert_cond = "(damVal.greThr2.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta5));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta5));
        }
      }
      tmp6 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2423
type: ALGORITHM

  assert(damVal.greThr2.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr2.h, has value: " + String(damVal.greThr2.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2423(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2423};
  modelica_boolean tmp7;
  static const MMC_DEFSTRINGLIT(tmp8,71,"Variable violating min constraint: 0.0 <= damVal.greThr2.h, has value: ");
  modelica_string tmp9;
  modelica_metatype tmpMeta10;
  static int tmp11 = 0;
  if(!tmp11)
  {
    tmp7 = GreaterEq((data->simulationInfo->realParameter[276] /* damVal.greThr2.h PARAM */),0.0);
    if(!tmp7)
    {
      tmp9 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[276] /* damVal.greThr2.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta10 = stringAppend(MMC_REFSTRINGLIT(tmp8),tmp9);
      {
        const char* assert_cond = "(damVal.greThr2.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta10));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta10));
        }
      }
      tmp11 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2424
type: ALGORITHM

  assert(damVal.lowMin.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.lowMin.lesHys.h, has value: " + String(damVal.lowMin.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2424(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2424};
  modelica_boolean tmp12;
  static const MMC_DEFSTRINGLIT(tmp13,77,"Variable violating min constraint: 0.0 <= damVal.lowMin.lesHys.h, has value: ");
  modelica_string tmp14;
  modelica_metatype tmpMeta15;
  static int tmp16 = 0;
  if(!tmp16)
  {
    tmp12 = GreaterEq((data->simulationInfo->realParameter[289] /* damVal.lowMin.lesHys.h PARAM */),0.0);
    if(!tmp12)
    {
      tmp14 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[289] /* damVal.lowMin.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta15 = stringAppend(MMC_REFSTRINGLIT(tmp13),tmp14);
      {
        const char* assert_cond = "(damVal.lowMin.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta15));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta15));
        }
      }
      tmp16 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2425
type: ALGORITHM

  assert(damVal.lowMin.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.lowMin.h, has value: " + String(damVal.lowMin.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2425(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2425};
  modelica_boolean tmp17;
  static const MMC_DEFSTRINGLIT(tmp18,70,"Variable violating min constraint: 0.0 <= damVal.lowMin.h, has value: ");
  modelica_string tmp19;
  modelica_metatype tmpMeta20;
  static int tmp21 = 0;
  if(!tmp21)
  {
    tmp17 = GreaterEq((data->simulationInfo->realParameter[288] /* damVal.lowMin.h PARAM */),0.0);
    if(!tmp17)
    {
      tmp19 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[288] /* damVal.lowMin.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta20 = stringAppend(MMC_REFSTRINGLIT(tmp18),tmp19);
      {
        const char* assert_cond = "(damVal.lowMin.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta20));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta20));
        }
      }
      tmp21 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2426
type: ALGORITHM

  assert(damVal.greThr.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr.greHys.h, has value: " + String(damVal.greThr.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2426(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2426};
  modelica_boolean tmp22;
  static const MMC_DEFSTRINGLIT(tmp23,77,"Variable violating min constraint: 0.0 <= damVal.greThr.greHys.h, has value: ");
  modelica_string tmp24;
  modelica_metatype tmpMeta25;
  static int tmp26 = 0;
  if(!tmp26)
  {
    tmp22 = GreaterEq((data->simulationInfo->realParameter[266] /* damVal.greThr.greHys.h PARAM */),0.0);
    if(!tmp22)
    {
      tmp24 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[266] /* damVal.greThr.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta25 = stringAppend(MMC_REFSTRINGLIT(tmp23),tmp24);
      {
        const char* assert_cond = "(damVal.greThr.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta25));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta25));
        }
      }
      tmp26 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2427
type: ALGORITHM

  assert(damVal.greThr.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr.h, has value: " + String(damVal.greThr.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2427(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2427};
  modelica_boolean tmp27;
  static const MMC_DEFSTRINGLIT(tmp28,70,"Variable violating min constraint: 0.0 <= damVal.greThr.h, has value: ");
  modelica_string tmp29;
  modelica_metatype tmpMeta30;
  static int tmp31 = 0;
  if(!tmp31)
  {
    tmp27 = GreaterEq((data->simulationInfo->realParameter[268] /* damVal.greThr.h PARAM */),0.0);
    if(!tmp27)
    {
      tmp29 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[268] /* damVal.greThr.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta30 = stringAppend(MMC_REFSTRINGLIT(tmp28),tmp29);
      {
        const char* assert_cond = "(damVal.greThr.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta30));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta30));
        }
      }
      tmp31 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2428
type: ALGORITHM

  assert(damVal.greThr1.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr1.greHys.h, has value: " + String(damVal.greThr1.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2428(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2428};
  modelica_boolean tmp32;
  static const MMC_DEFSTRINGLIT(tmp33,78,"Variable violating min constraint: 0.0 <= damVal.greThr1.greHys.h, has value: ");
  modelica_string tmp34;
  modelica_metatype tmpMeta35;
  static int tmp36 = 0;
  if(!tmp36)
  {
    tmp32 = GreaterEq((data->simulationInfo->realParameter[270] /* damVal.greThr1.greHys.h PARAM */),0.0);
    if(!tmp32)
    {
      tmp34 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[270] /* damVal.greThr1.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta35 = stringAppend(MMC_REFSTRINGLIT(tmp33),tmp34);
      {
        const char* assert_cond = "(damVal.greThr1.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta35));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta35));
        }
      }
      tmp36 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2429
type: ALGORITHM

  assert(damVal.greThr1.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.greThr1.h, has value: " + String(damVal.greThr1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2429(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2429};
  modelica_boolean tmp37;
  static const MMC_DEFSTRINGLIT(tmp38,71,"Variable violating min constraint: 0.0 <= damVal.greThr1.h, has value: ");
  modelica_string tmp39;
  modelica_metatype tmpMeta40;
  static int tmp41 = 0;
  if(!tmp41)
  {
    tmp37 = GreaterEq((data->simulationInfo->realParameter[272] /* damVal.greThr1.h PARAM */),0.0);
    if(!tmp37)
    {
      tmp39 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[272] /* damVal.greThr1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta40 = stringAppend(MMC_REFSTRINGLIT(tmp38),tmp39);
      {
        const char* assert_cond = "(damVal.greThr1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta40));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta40));
        }
      }
      tmp41 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2430
type: ALGORITHM

  assert(damVal.conVal.k >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.k, has value: " + String(damVal.conVal.k, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2430(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2430};
  modelica_boolean tmp42;
  static const MMC_DEFSTRINGLIT(tmp43,72,"Variable violating min constraint: 1e-13 <= damVal.conVal.k, has value: ");
  modelica_string tmp44;
  modelica_metatype tmpMeta45;
  static int tmp46 = 0;
  if(!tmp46)
  {
    tmp42 = GreaterEq((data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */),1e-13);
    if(!tmp42)
    {
      tmp44 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[241] /* damVal.conVal.k PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta45 = stringAppend(MMC_REFSTRINGLIT(tmp43),tmp44);
      {
        const char* assert_cond = "(damVal.conVal.k >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta45));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta45));
        }
      }
      tmp46 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2431
type: ALGORITHM

  assert(damVal.conVal.Ni >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.Ni, has value: " + String(damVal.conVal.Ni, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2431(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2431};
  modelica_boolean tmp47;
  static const MMC_DEFSTRINGLIT(tmp48,73,"Variable violating min constraint: 1e-13 <= damVal.conVal.Ni, has value: ");
  modelica_string tmp49;
  modelica_metatype tmpMeta50;
  static int tmp51 = 0;
  if(!tmp51)
  {
    tmp47 = GreaterEq((data->simulationInfo->realParameter[235] /* damVal.conVal.Ni PARAM */),1e-13);
    if(!tmp47)
    {
      tmp49 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[235] /* damVal.conVal.Ni PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta50 = stringAppend(MMC_REFSTRINGLIT(tmp48),tmp49);
      {
        const char* assert_cond = "(damVal.conVal.Ni >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta50));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta50));
        }
      }
      tmp51 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2432
type: ALGORITHM

  assert(damVal.conVal.r >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.r, has value: " + String(damVal.conVal.r, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2432(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2432};
  modelica_boolean tmp52;
  static const MMC_DEFSTRINGLIT(tmp53,72,"Variable violating min constraint: 1e-13 <= damVal.conVal.r, has value: ");
  modelica_string tmp54;
  modelica_metatype tmpMeta55;
  static int tmp56 = 0;
  if(!tmp56)
  {
    tmp52 = GreaterEq((data->simulationInfo->realParameter[244] /* damVal.conVal.r PARAM */),1e-13);
    if(!tmp52)
    {
      tmp54 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[244] /* damVal.conVal.r PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta55 = stringAppend(MMC_REFSTRINGLIT(tmp53),tmp54);
      {
        const char* assert_cond = "(damVal.conVal.r >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta55));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta55));
        }
      }
      tmp56 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2433
type: ALGORITHM

  assert(damVal.conVal.Ti >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.Ti, has value: " + String(damVal.conVal.Ti, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2433(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2433};
  modelica_boolean tmp57;
  static const MMC_DEFSTRINGLIT(tmp58,73,"Variable violating min constraint: 1e-13 <= damVal.conVal.Ti, has value: ");
  modelica_string tmp59;
  modelica_metatype tmpMeta60;
  static int tmp61 = 0;
  if(!tmp61)
  {
    tmp57 = GreaterEq((data->simulationInfo->realParameter[238] /* damVal.conVal.Ti PARAM */),1e-13);
    if(!tmp57)
    {
      tmp59 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[238] /* damVal.conVal.Ti PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta60 = stringAppend(MMC_REFSTRINGLIT(tmp58),tmp59);
      {
        const char* assert_cond = "(damVal.conVal.Ti >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta60));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta60));
        }
      }
      tmp61 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2434
type: ALGORITHM

  assert(damVal.conVal.Nd >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.Nd, has value: " + String(damVal.conVal.Nd, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2434(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2434};
  modelica_boolean tmp62;
  static const MMC_DEFSTRINGLIT(tmp63,73,"Variable violating min constraint: 1e-13 <= damVal.conVal.Nd, has value: ");
  modelica_string tmp64;
  modelica_metatype tmpMeta65;
  static int tmp66 = 0;
  if(!tmp66)
  {
    tmp62 = GreaterEq((data->simulationInfo->realParameter[234] /* damVal.conVal.Nd PARAM */),1e-13);
    if(!tmp62)
    {
      tmp64 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[234] /* damVal.conVal.Nd PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta65 = stringAppend(MMC_REFSTRINGLIT(tmp63),tmp64);
      {
        const char* assert_cond = "(damVal.conVal.Nd >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta65));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta65));
        }
      }
      tmp66 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2435
type: ALGORITHM

  assert(damVal.conVal.Td >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conVal.Td, has value: " + String(damVal.conVal.Td, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2435(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2435};
  modelica_boolean tmp67;
  static const MMC_DEFSTRINGLIT(tmp68,73,"Variable violating min constraint: 1e-13 <= damVal.conVal.Td, has value: ");
  modelica_string tmp69;
  modelica_metatype tmpMeta70;
  static int tmp71 = 0;
  if(!tmp71)
  {
    tmp67 = GreaterEq((data->simulationInfo->realParameter[237] /* damVal.conVal.Td PARAM */),1e-13);
    if(!tmp67)
    {
      tmp69 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[237] /* damVal.conVal.Td PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta70 = stringAppend(MMC_REFSTRINGLIT(tmp68),tmp69);
      {
        const char* assert_cond = "(damVal.conVal.Td >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta70));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta70));
        }
      }
      tmp71 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2436
type: ALGORITHM

  assert(damVal.conVal.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.conVal.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.conVal.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(damVal.conVal.controllerType, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2436(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2436};
  modelica_boolean tmp72;
  modelica_boolean tmp73;
  static const MMC_DEFSTRINGLIT(tmp74,192,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.conVal.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp75;
  modelica_metatype tmpMeta76;
  static int tmp77 = 0;
  if(!tmp77)
  {
    tmp72 = GreaterEq((data->simulationInfo->integerParameter[32] /* damVal.conVal.controllerType PARAM */),1);
    tmp73 = LessEq((data->simulationInfo->integerParameter[32] /* damVal.conVal.controllerType PARAM */),4);
    if(!(tmp72 && tmp73))
    {
      tmp75 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[32] /* damVal.conVal.controllerType PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta76 = stringAppend(MMC_REFSTRINGLIT(tmp74),tmp75);
      {
        const char* assert_cond = "(damVal.conVal.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.conVal.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta76));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta76));
        }
      }
      tmp77 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2437
type: ALGORITHM

  assert(damVal.gre.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.gre.greHys.h, has value: " + String(damVal.gre.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2437(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2437};
  modelica_boolean tmp78;
  static const MMC_DEFSTRINGLIT(tmp79,74,"Variable violating min constraint: 0.0 <= damVal.gre.greHys.h, has value: ");
  modelica_string tmp80;
  modelica_metatype tmpMeta81;
  static int tmp82 = 0;
  if(!tmp82)
  {
    tmp78 = GreaterEq((data->simulationInfo->realParameter[264] /* damVal.gre.greHys.h PARAM */),0.0);
    if(!tmp78)
    {
      tmp80 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[264] /* damVal.gre.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta81 = stringAppend(MMC_REFSTRINGLIT(tmp79),tmp80);
      {
        const char* assert_cond = "(damVal.gre.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta81));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta81));
        }
      }
      tmp82 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2438
type: ALGORITHM

  assert(damVal.gre.h >= 0.0, "Variable violating min constraint: 0.0 <= damVal.gre.h, has value: " + String(damVal.gre.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2438(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2438};
  modelica_boolean tmp83;
  static const MMC_DEFSTRINGLIT(tmp84,67,"Variable violating min constraint: 0.0 <= damVal.gre.h, has value: ");
  modelica_string tmp85;
  modelica_metatype tmpMeta86;
  static int tmp87 = 0;
  if(!tmp87)
  {
    tmp83 = GreaterEq((data->simulationInfo->realParameter[265] /* damVal.gre.h PARAM */),0.0);
    if(!tmp83)
    {
      tmp85 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[265] /* damVal.gre.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta86 = stringAppend(MMC_REFSTRINGLIT(tmp84),tmp85);
      {
        const char* assert_cond = "(damVal.gre.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta86));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta86));
        }
      }
      tmp87 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2439
type: ALGORITHM

  assert(damVal.conDam.k >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.k, has value: " + String(damVal.conDam.k, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2439(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2439};
  modelica_boolean tmp88;
  static const MMC_DEFSTRINGLIT(tmp89,72,"Variable violating min constraint: 1e-13 <= damVal.conDam.k, has value: ");
  modelica_string tmp90;
  modelica_metatype tmpMeta91;
  static int tmp92 = 0;
  if(!tmp92)
  {
    tmp88 = GreaterEq((data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */),1e-13);
    if(!tmp88)
    {
      tmp90 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[213] /* damVal.conDam.k PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta91 = stringAppend(MMC_REFSTRINGLIT(tmp89),tmp90);
      {
        const char* assert_cond = "(damVal.conDam.k >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta91));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta91));
        }
      }
      tmp92 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2440
type: ALGORITHM

  assert(damVal.conDam.Ni >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.Ni, has value: " + String(damVal.conDam.Ni, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2440(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2440};
  modelica_boolean tmp93;
  static const MMC_DEFSTRINGLIT(tmp94,73,"Variable violating min constraint: 1e-13 <= damVal.conDam.Ni, has value: ");
  modelica_string tmp95;
  modelica_metatype tmpMeta96;
  static int tmp97 = 0;
  if(!tmp97)
  {
    tmp93 = GreaterEq((data->simulationInfo->realParameter[207] /* damVal.conDam.Ni PARAM */),1e-13);
    if(!tmp93)
    {
      tmp95 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[207] /* damVal.conDam.Ni PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta96 = stringAppend(MMC_REFSTRINGLIT(tmp94),tmp95);
      {
        const char* assert_cond = "(damVal.conDam.Ni >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta96));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta96));
        }
      }
      tmp97 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2441
type: ALGORITHM

  assert(damVal.conDam.r >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.r, has value: " + String(damVal.conDam.r, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2441(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2441};
  modelica_boolean tmp98;
  static const MMC_DEFSTRINGLIT(tmp99,72,"Variable violating min constraint: 1e-13 <= damVal.conDam.r, has value: ");
  modelica_string tmp100;
  modelica_metatype tmpMeta101;
  static int tmp102 = 0;
  if(!tmp102)
  {
    tmp98 = GreaterEq((data->simulationInfo->realParameter[216] /* damVal.conDam.r PARAM */),1e-13);
    if(!tmp98)
    {
      tmp100 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[216] /* damVal.conDam.r PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta101 = stringAppend(MMC_REFSTRINGLIT(tmp99),tmp100);
      {
        const char* assert_cond = "(damVal.conDam.r >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta101));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta101));
        }
      }
      tmp102 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2442
type: ALGORITHM

  assert(damVal.conDam.Ti >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.Ti, has value: " + String(damVal.conDam.Ti, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2442(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2442};
  modelica_boolean tmp103;
  static const MMC_DEFSTRINGLIT(tmp104,73,"Variable violating min constraint: 1e-13 <= damVal.conDam.Ti, has value: ");
  modelica_string tmp105;
  modelica_metatype tmpMeta106;
  static int tmp107 = 0;
  if(!tmp107)
  {
    tmp103 = GreaterEq((data->simulationInfo->realParameter[210] /* damVal.conDam.Ti PARAM */),1e-13);
    if(!tmp103)
    {
      tmp105 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[210] /* damVal.conDam.Ti PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta106 = stringAppend(MMC_REFSTRINGLIT(tmp104),tmp105);
      {
        const char* assert_cond = "(damVal.conDam.Ti >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta106));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta106));
        }
      }
      tmp107 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2443
type: ALGORITHM

  assert(damVal.conDam.Nd >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.Nd, has value: " + String(damVal.conDam.Nd, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2443(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2443};
  modelica_boolean tmp108;
  static const MMC_DEFSTRINGLIT(tmp109,73,"Variable violating min constraint: 1e-13 <= damVal.conDam.Nd, has value: ");
  modelica_string tmp110;
  modelica_metatype tmpMeta111;
  static int tmp112 = 0;
  if(!tmp112)
  {
    tmp108 = GreaterEq((data->simulationInfo->realParameter[206] /* damVal.conDam.Nd PARAM */),1e-13);
    if(!tmp108)
    {
      tmp110 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[206] /* damVal.conDam.Nd PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta111 = stringAppend(MMC_REFSTRINGLIT(tmp109),tmp110);
      {
        const char* assert_cond = "(damVal.conDam.Nd >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta111));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta111));
        }
      }
      tmp112 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2444
type: ALGORITHM

  assert(damVal.conDam.Td >= 1e-13, "Variable violating min constraint: 1e-13 <= damVal.conDam.Td, has value: " + String(damVal.conDam.Td, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2444(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2444};
  modelica_boolean tmp113;
  static const MMC_DEFSTRINGLIT(tmp114,73,"Variable violating min constraint: 1e-13 <= damVal.conDam.Td, has value: ");
  modelica_string tmp115;
  modelica_metatype tmpMeta116;
  static int tmp117 = 0;
  if(!tmp117)
  {
    tmp113 = GreaterEq((data->simulationInfo->realParameter[209] /* damVal.conDam.Td PARAM */),1e-13);
    if(!tmp113)
    {
      tmp115 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[209] /* damVal.conDam.Td PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta116 = stringAppend(MMC_REFSTRINGLIT(tmp114),tmp115);
      {
        const char* assert_cond = "(damVal.conDam.Td >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta116));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta116));
        }
      }
      tmp117 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2445
type: ALGORITHM

  assert(damVal.conDam.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.conDam.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.conDam.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(damVal.conDam.controllerType, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2445(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2445};
  modelica_boolean tmp118;
  modelica_boolean tmp119;
  static const MMC_DEFSTRINGLIT(tmp120,192,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.conDam.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp121;
  modelica_metatype tmpMeta122;
  static int tmp123 = 0;
  if(!tmp123)
  {
    tmp118 = GreaterEq((data->simulationInfo->integerParameter[27] /* damVal.conDam.controllerType PARAM */),1);
    tmp119 = LessEq((data->simulationInfo->integerParameter[27] /* damVal.conDam.controllerType PARAM */),4);
    if(!(tmp118 && tmp119))
    {
      tmp121 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[27] /* damVal.conDam.controllerType PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta122 = stringAppend(MMC_REFSTRINGLIT(tmp120),tmp121);
      {
        const char* assert_cond = "(damVal.conDam.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.conDam.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta122));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta122));
        }
      }
      tmp123 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2446
type: ALGORITHM

  assert(damVal.controllerTypeDam >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(damVal.controllerTypeDam, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2446(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2446};
  modelica_boolean tmp124;
  modelica_boolean tmp125;
  static const MMC_DEFSTRINGLIT(tmp126,188,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp127;
  modelica_metatype tmpMeta128;
  static int tmp129 = 0;
  if(!tmp129)
  {
    tmp124 = GreaterEq((data->simulationInfo->integerParameter[33] /* damVal.controllerTypeDam PARAM */),1);
    tmp125 = LessEq((data->simulationInfo->integerParameter[33] /* damVal.controllerTypeDam PARAM */),4);
    if(!(tmp124 && tmp125))
    {
      tmp127 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[33] /* damVal.controllerTypeDam PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta128 = stringAppend(MMC_REFSTRINGLIT(tmp126),tmp127);
      {
        const char* assert_cond = "(damVal.controllerTypeDam >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",38,3,41,71,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta128));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",38,3,41,71,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta128));
        }
      }
      tmp129 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2447
type: ALGORITHM

  assert(damVal.controllerTypeVal >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(damVal.controllerTypeVal, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2447(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2447};
  modelica_boolean tmp130;
  modelica_boolean tmp131;
  static const MMC_DEFSTRINGLIT(tmp132,188,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= damVal.controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp133;
  modelica_metatype tmpMeta134;
  static int tmp135 = 0;
  if(!tmp135)
  {
    tmp130 = GreaterEq((data->simulationInfo->integerParameter[34] /* damVal.controllerTypeVal PARAM */),1);
    tmp131 = LessEq((data->simulationInfo->integerParameter[34] /* damVal.controllerTypeVal PARAM */),4);
    if(!(tmp130 && tmp131))
    {
      tmp133 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[34] /* damVal.controllerTypeVal PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta134 = stringAppend(MMC_REFSTRINGLIT(tmp132),tmp133);
      {
        const char* assert_cond = "(damVal.controllerTypeVal >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and damVal.controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",19,3,22,70,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta134));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",19,3,22,70,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta134));
        }
      }
      tmp135 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2448
type: ALGORITHM

  assert(setPoi.cooSup.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= setPoi.cooSup.greHys.h, has value: " + String(setPoi.cooSup.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2448(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2448};
  modelica_boolean tmp136;
  static const MMC_DEFSTRINGLIT(tmp137,77,"Variable violating min constraint: 0.0 <= setPoi.cooSup.greHys.h, has value: ");
  modelica_string tmp138;
  modelica_metatype tmpMeta139;
  static int tmp140 = 0;
  if(!tmp140)
  {
    tmp136 = GreaterEq((data->simulationInfo->realParameter[337] /* setPoi.cooSup.greHys.h PARAM */),0.0);
    if(!tmp136)
    {
      tmp138 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[337] /* setPoi.cooSup.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta139 = stringAppend(MMC_REFSTRINGLIT(tmp137),tmp138);
      {
        const char* assert_cond = "(setPoi.cooSup.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta139));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta139));
        }
      }
      tmp140 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2449
type: ALGORITHM

  assert(setPoi.cooSup.h >= 0.0, "Variable violating min constraint: 0.0 <= setPoi.cooSup.h, has value: " + String(setPoi.cooSup.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2449(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2449};
  modelica_boolean tmp141;
  static const MMC_DEFSTRINGLIT(tmp142,70,"Variable violating min constraint: 0.0 <= setPoi.cooSup.h, has value: ");
  modelica_string tmp143;
  modelica_metatype tmpMeta144;
  static int tmp145 = 0;
  if(!tmp145)
  {
    tmp141 = GreaterEq((data->simulationInfo->realParameter[338] /* setPoi.cooSup.h PARAM */),0.0);
    if(!tmp141)
    {
      tmp143 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[338] /* setPoi.cooSup.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta144 = stringAppend(MMC_REFSTRINGLIT(tmp142),tmp143);
      {
        const char* assert_cond = "(setPoi.cooSup.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta144));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta144));
        }
      }
      tmp145 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2450
type: ALGORITHM

  assert(timSup.pasSup.h >= 0.0, "Variable violating min constraint: 0.0 <= timSup.pasSup.h, has value: " + String(timSup.pasSup.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2450(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2450};
  modelica_boolean tmp146;
  static const MMC_DEFSTRINGLIT(tmp147,70,"Variable violating min constraint: 0.0 <= timSup.pasSup.h, has value: ");
  modelica_string tmp148;
  modelica_metatype tmpMeta149;
  static int tmp150 = 0;
  if(!tmp150)
  {
    tmp146 = GreaterEq((data->simulationInfo->realParameter[448] /* timSup.pasSup.h PARAM */),0.0);
    if(!tmp146)
    {
      tmp148 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[448] /* timSup.pasSup.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta149 = stringAppend(MMC_REFSTRINGLIT(tmp147),tmp148);
      {
        const char* assert_cond = "(timSup.pasSup.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta149));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta149));
        }
      }
      tmp150 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2451
type: ALGORITHM

  assert(timSup.greThr.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= timSup.greThr.greHys.h, has value: " + String(timSup.greThr.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2451(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2451};
  modelica_boolean tmp151;
  static const MMC_DEFSTRINGLIT(tmp152,77,"Variable violating min constraint: 0.0 <= timSup.greThr.greHys.h, has value: ");
  modelica_string tmp153;
  modelica_metatype tmpMeta154;
  static int tmp155 = 0;
  if(!tmp155)
  {
    tmp151 = GreaterEq((data->simulationInfo->realParameter[441] /* timSup.greThr.greHys.h PARAM */),0.0);
    if(!tmp151)
    {
      tmp153 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[441] /* timSup.greThr.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta154 = stringAppend(MMC_REFSTRINGLIT(tmp152),tmp153);
      {
        const char* assert_cond = "(timSup.greThr.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta154));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta154));
        }
      }
      tmp155 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2452
type: ALGORITHM

  assert(timSup.greThr.h >= 0.0, "Variable violating min constraint: 0.0 <= timSup.greThr.h, has value: " + String(timSup.greThr.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2452(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2452};
  modelica_boolean tmp156;
  static const MMC_DEFSTRINGLIT(tmp157,70,"Variable violating min constraint: 0.0 <= timSup.greThr.h, has value: ");
  modelica_string tmp158;
  modelica_metatype tmpMeta159;
  static int tmp160 = 0;
  if(!tmp160)
  {
    tmp156 = GreaterEq((data->simulationInfo->realParameter[443] /* timSup.greThr.h PARAM */),0.0);
    if(!tmp156)
    {
      tmp158 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[443] /* timSup.greThr.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta159 = stringAppend(MMC_REFSTRINGLIT(tmp157),tmp158);
      {
        const char* assert_cond = "(timSup.greThr.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta159));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta159));
        }
      }
      tmp160 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2453
type: ALGORITHM

  assert(timSup.uniDel.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= timSup.uniDel.samplePeriod, has value: " + String(timSup.uniDel.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2453(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2453};
  modelica_boolean tmp161;
  static const MMC_DEFSTRINGLIT(tmp162,83,"Variable violating min constraint: 0.001 <= timSup.uniDel.samplePeriod, has value: ");
  modelica_string tmp163;
  modelica_metatype tmpMeta164;
  static int tmp165 = 0;
  if(!tmp165)
  {
    tmp161 = GreaterEq((data->simulationInfo->realParameter[458] /* timSup.uniDel.samplePeriod PARAM */),0.001);
    if(!tmp161)
    {
      tmp163 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[458] /* timSup.uniDel.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta164 = stringAppend(MMC_REFSTRINGLIT(tmp162),tmp163);
      {
        const char* assert_cond = "(timSup.uniDel.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/UnitDelay.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta164));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/UnitDelay.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta164));
        }
      }
      tmp165 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2454
type: ALGORITHM

  assert(timSup.samSet.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= timSup.samSet.samplePeriod, has value: " + String(timSup.samSet.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2454(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2454};
  modelica_boolean tmp166;
  static const MMC_DEFSTRINGLIT(tmp167,83,"Variable violating min constraint: 0.001 <= timSup.samSet.samplePeriod, has value: ");
  modelica_string tmp168;
  modelica_metatype tmpMeta169;
  static int tmp170 = 0;
  if(!tmp170)
  {
    tmp166 = GreaterEq((data->simulationInfo->realParameter[449] /* timSup.samSet.samplePeriod PARAM */),0.001);
    if(!tmp166)
    {
      tmp168 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[449] /* timSup.samSet.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta169 = stringAppend(MMC_REFSTRINGLIT(tmp167),tmp168);
      {
        const char* assert_cond = "(timSup.samSet.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta169));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta169));
        }
      }
      tmp170 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2455
type: ALGORITHM

  assert(ala.gre2.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre2.greHys.h, has value: " + String(ala.gre2.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2455(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2455};
  modelica_boolean tmp171;
  static const MMC_DEFSTRINGLIT(tmp172,72,"Variable violating min constraint: 0.0 <= ala.gre2.greHys.h, has value: ");
  modelica_string tmp173;
  modelica_metatype tmpMeta174;
  static int tmp175 = 0;
  if(!tmp175)
  {
    tmp171 = GreaterEq((data->simulationInfo->realParameter[68] /* ala.gre2.greHys.h PARAM */),0.0);
    if(!tmp171)
    {
      tmp173 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[68] /* ala.gre2.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta174 = stringAppend(MMC_REFSTRINGLIT(tmp172),tmp173);
      {
        const char* assert_cond = "(ala.gre2.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta174));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta174));
        }
      }
      tmp175 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2456
type: ALGORITHM

  assert(ala.gre2.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre2.h, has value: " + String(ala.gre2.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2456(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2456};
  modelica_boolean tmp176;
  static const MMC_DEFSTRINGLIT(tmp177,65,"Variable violating min constraint: 0.0 <= ala.gre2.h, has value: ");
  modelica_string tmp178;
  modelica_metatype tmpMeta179;
  static int tmp180 = 0;
  if(!tmp180)
  {
    tmp176 = GreaterEq((data->simulationInfo->realParameter[69] /* ala.gre2.h PARAM */),0.0);
    if(!tmp176)
    {
      tmp178 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[69] /* ala.gre2.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta179 = stringAppend(MMC_REFSTRINGLIT(tmp177),tmp178);
      {
        const char* assert_cond = "(ala.gre2.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta179));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta179));
        }
      }
      tmp180 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2457
type: ALGORITHM

  assert(ala.cloVal.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.cloVal.lesHys.h, has value: " + String(ala.cloVal.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2457(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2457};
  modelica_boolean tmp181;
  static const MMC_DEFSTRINGLIT(tmp182,74,"Variable violating min constraint: 0.0 <= ala.cloVal.lesHys.h, has value: ");
  modelica_string tmp183;
  modelica_metatype tmpMeta184;
  static int tmp185 = 0;
  if(!tmp185)
  {
    tmp181 = GreaterEq((data->simulationInfo->realParameter[45] /* ala.cloVal.lesHys.h PARAM */),0.0);
    if(!tmp181)
    {
      tmp183 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[45] /* ala.cloVal.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta184 = stringAppend(MMC_REFSTRINGLIT(tmp182),tmp183);
      {
        const char* assert_cond = "(ala.cloVal.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta184));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta184));
        }
      }
      tmp185 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2458
type: ALGORITHM

  assert(ala.cloVal.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.cloVal.h, has value: " + String(ala.cloVal.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2458(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2458};
  modelica_boolean tmp186;
  static const MMC_DEFSTRINGLIT(tmp187,67,"Variable violating min constraint: 0.0 <= ala.cloVal.h, has value: ");
  modelica_string tmp188;
  modelica_metatype tmpMeta189;
  static int tmp190 = 0;
  if(!tmp190)
  {
    tmp186 = GreaterEq((data->simulationInfo->realParameter[44] /* ala.cloVal.h PARAM */),0.0);
    if(!tmp186)
    {
      tmp188 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[44] /* ala.cloVal.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta189 = stringAppend(MMC_REFSTRINGLIT(tmp187),tmp188);
      {
        const char* assert_cond = "(ala.cloVal.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta189));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta189));
        }
      }
      tmp190 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2459
type: ALGORITHM

  assert(ala.greThr2.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.greThr2.h, has value: " + String(ala.greThr2.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2459(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2459};
  modelica_boolean tmp191;
  static const MMC_DEFSTRINGLIT(tmp192,68,"Variable violating min constraint: 0.0 <= ala.greThr2.h, has value: ");
  modelica_string tmp193;
  modelica_metatype tmpMeta194;
  static int tmp195 = 0;
  if(!tmp195)
  {
    tmp191 = GreaterEq((data->simulationInfo->realParameter[81] /* ala.greThr2.h PARAM */),0.0);
    if(!tmp191)
    {
      tmp193 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[81] /* ala.greThr2.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta194 = stringAppend(MMC_REFSTRINGLIT(tmp192),tmp193);
      {
        const char* assert_cond = "(ala.greThr2.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta194));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta194));
        }
      }
      tmp195 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2460
type: ALGORITHM

  assert(ala.les2.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les2.lesHys.h, has value: " + String(ala.les2.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2460(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2460};
  modelica_boolean tmp196;
  static const MMC_DEFSTRINGLIT(tmp197,72,"Variable violating min constraint: 0.0 <= ala.les2.lesHys.h, has value: ");
  modelica_string tmp198;
  modelica_metatype tmpMeta199;
  static int tmp200 = 0;
  if(!tmp200)
  {
    tmp196 = GreaterEq((data->simulationInfo->realParameter[91] /* ala.les2.lesHys.h PARAM */),0.0);
    if(!tmp196)
    {
      tmp198 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[91] /* ala.les2.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta199 = stringAppend(MMC_REFSTRINGLIT(tmp197),tmp198);
      {
        const char* assert_cond = "(ala.les2.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta199));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta199));
        }
      }
      tmp200 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2461
type: ALGORITHM

  assert(ala.les2.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les2.h, has value: " + String(ala.les2.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2461(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2461};
  modelica_boolean tmp201;
  static const MMC_DEFSTRINGLIT(tmp202,65,"Variable violating min constraint: 0.0 <= ala.les2.h, has value: ");
  modelica_string tmp203;
  modelica_metatype tmpMeta204;
  static int tmp205 = 0;
  if(!tmp205)
  {
    tmp201 = GreaterEq((data->simulationInfo->realParameter[90] /* ala.les2.h PARAM */),0.0);
    if(!tmp201)
    {
      tmp203 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[90] /* ala.les2.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta204 = stringAppend(MMC_REFSTRINGLIT(tmp202),tmp203);
      {
        const char* assert_cond = "(ala.les2.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta204));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta204));
        }
      }
      tmp205 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2462
type: ALGORITHM

  assert(ala.les1.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les1.lesHys.h, has value: " + String(ala.les1.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2462(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2462};
  modelica_boolean tmp206;
  static const MMC_DEFSTRINGLIT(tmp207,72,"Variable violating min constraint: 0.0 <= ala.les1.lesHys.h, has value: ");
  modelica_string tmp208;
  modelica_metatype tmpMeta209;
  static int tmp210 = 0;
  if(!tmp210)
  {
    tmp206 = GreaterEq((data->simulationInfo->realParameter[89] /* ala.les1.lesHys.h PARAM */),0.0);
    if(!tmp206)
    {
      tmp208 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[89] /* ala.les1.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta209 = stringAppend(MMC_REFSTRINGLIT(tmp207),tmp208);
      {
        const char* assert_cond = "(ala.les1.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta209));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta209));
        }
      }
      tmp210 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2463
type: ALGORITHM

  assert(ala.les1.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les1.h, has value: " + String(ala.les1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2463(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2463};
  modelica_boolean tmp211;
  static const MMC_DEFSTRINGLIT(tmp212,65,"Variable violating min constraint: 0.0 <= ala.les1.h, has value: ");
  modelica_string tmp213;
  modelica_metatype tmpMeta214;
  static int tmp215 = 0;
  if(!tmp215)
  {
    tmp211 = GreaterEq((data->simulationInfo->realParameter[88] /* ala.les1.h PARAM */),0.0);
    if(!tmp211)
    {
      tmp213 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[88] /* ala.les1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta214 = stringAppend(MMC_REFSTRINGLIT(tmp212),tmp213);
      {
        const char* assert_cond = "(ala.les1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta214));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta214));
        }
      }
      tmp215 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2464
type: ALGORITHM

  assert(ala.cloDam.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.cloDam.lesHys.h, has value: " + String(ala.cloDam.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2464(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2464};
  modelica_boolean tmp216;
  static const MMC_DEFSTRINGLIT(tmp217,74,"Variable violating min constraint: 0.0 <= ala.cloDam.lesHys.h, has value: ");
  modelica_string tmp218;
  modelica_metatype tmpMeta219;
  static int tmp220 = 0;
  if(!tmp220)
  {
    tmp216 = GreaterEq((data->simulationInfo->realParameter[41] /* ala.cloDam.lesHys.h PARAM */),0.0);
    if(!tmp216)
    {
      tmp218 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[41] /* ala.cloDam.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta219 = stringAppend(MMC_REFSTRINGLIT(tmp217),tmp218);
      {
        const char* assert_cond = "(ala.cloDam.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta219));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta219));
        }
      }
      tmp220 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2465
type: ALGORITHM

  assert(ala.cloDam.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.cloDam.h, has value: " + String(ala.cloDam.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2465(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2465};
  modelica_boolean tmp221;
  static const MMC_DEFSTRINGLIT(tmp222,67,"Variable violating min constraint: 0.0 <= ala.cloDam.h, has value: ");
  modelica_string tmp223;
  modelica_metatype tmpMeta224;
  static int tmp225 = 0;
  if(!tmp225)
  {
    tmp221 = GreaterEq((data->simulationInfo->realParameter[40] /* ala.cloDam.h PARAM */),0.0);
    if(!tmp221)
    {
      tmp223 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[40] /* ala.cloDam.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta224 = stringAppend(MMC_REFSTRINGLIT(tmp222),tmp223);
      {
        const char* assert_cond = "(ala.cloDam.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta224));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta224));
        }
      }
      tmp225 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2466
type: ALGORITHM

  assert(ala.gre1.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre1.greHys.h, has value: " + String(ala.gre1.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2466(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2466};
  modelica_boolean tmp226;
  static const MMC_DEFSTRINGLIT(tmp227,72,"Variable violating min constraint: 0.0 <= ala.gre1.greHys.h, has value: ");
  modelica_string tmp228;
  modelica_metatype tmpMeta229;
  static int tmp230 = 0;
  if(!tmp230)
  {
    tmp226 = GreaterEq((data->simulationInfo->realParameter[66] /* ala.gre1.greHys.h PARAM */),0.0);
    if(!tmp226)
    {
      tmp228 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[66] /* ala.gre1.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta229 = stringAppend(MMC_REFSTRINGLIT(tmp227),tmp228);
      {
        const char* assert_cond = "(ala.gre1.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta229));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta229));
        }
      }
      tmp230 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2467
type: ALGORITHM

  assert(ala.gre1.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre1.h, has value: " + String(ala.gre1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2467(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2467};
  modelica_boolean tmp231;
  static const MMC_DEFSTRINGLIT(tmp232,65,"Variable violating min constraint: 0.0 <= ala.gre1.h, has value: ");
  modelica_string tmp233;
  modelica_metatype tmpMeta234;
  static int tmp235 = 0;
  if(!tmp235)
  {
    tmp231 = GreaterEq((data->simulationInfo->realParameter[67] /* ala.gre1.h PARAM */),0.0);
    if(!tmp231)
    {
      tmp233 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[67] /* ala.gre1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta234 = stringAppend(MMC_REFSTRINGLIT(tmp232),tmp233);
      {
        const char* assert_cond = "(ala.gre1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta234));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta234));
        }
      }
      tmp235 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2468
type: ALGORITHM

  assert(ala.greThr1.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.greThr1.h, has value: " + String(ala.greThr1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2468(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2468};
  modelica_boolean tmp236;
  static const MMC_DEFSTRINGLIT(tmp237,68,"Variable violating min constraint: 0.0 <= ala.greThr1.h, has value: ");
  modelica_string tmp238;
  modelica_metatype tmpMeta239;
  static int tmp240 = 0;
  if(!tmp240)
  {
    tmp236 = GreaterEq((data->simulationInfo->realParameter[76] /* ala.greThr1.h PARAM */),0.0);
    if(!tmp236)
    {
      tmp238 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[76] /* ala.greThr1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta239 = stringAppend(MMC_REFSTRINGLIT(tmp237),tmp238);
      {
        const char* assert_cond = "(ala.greThr1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta239));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta239));
        }
      }
      tmp240 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2469
type: ALGORITHM

  assert(ala.gre.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre.greHys.h, has value: " + String(ala.gre.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2469(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2469};
  modelica_boolean tmp241;
  static const MMC_DEFSTRINGLIT(tmp242,71,"Variable violating min constraint: 0.0 <= ala.gre.greHys.h, has value: ");
  modelica_string tmp243;
  modelica_metatype tmpMeta244;
  static int tmp245 = 0;
  if(!tmp245)
  {
    tmp241 = GreaterEq((data->simulationInfo->realParameter[64] /* ala.gre.greHys.h PARAM */),0.0);
    if(!tmp241)
    {
      tmp243 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[64] /* ala.gre.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta244 = stringAppend(MMC_REFSTRINGLIT(tmp242),tmp243);
      {
        const char* assert_cond = "(ala.gre.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta244));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta244));
        }
      }
      tmp245 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2470
type: ALGORITHM

  assert(ala.gre.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.gre.h, has value: " + String(ala.gre.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2470(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2470};
  modelica_boolean tmp246;
  static const MMC_DEFSTRINGLIT(tmp247,64,"Variable violating min constraint: 0.0 <= ala.gre.h, has value: ");
  modelica_string tmp248;
  modelica_metatype tmpMeta249;
  static int tmp250 = 0;
  if(!tmp250)
  {
    tmp246 = GreaterEq((data->simulationInfo->realParameter[65] /* ala.gre.h PARAM */),0.0);
    if(!tmp246)
    {
      tmp248 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[65] /* ala.gre.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta249 = stringAppend(MMC_REFSTRINGLIT(tmp247),tmp248);
      {
        const char* assert_cond = "(ala.gre.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta249));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta249));
        }
      }
      tmp250 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2471
type: ALGORITHM

  assert(ala.greThr.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.greThr.greHys.h, has value: " + String(ala.greThr.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2471(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2471};
  modelica_boolean tmp251;
  static const MMC_DEFSTRINGLIT(tmp252,74,"Variable violating min constraint: 0.0 <= ala.greThr.greHys.h, has value: ");
  modelica_string tmp253;
  modelica_metatype tmpMeta254;
  static int tmp255 = 0;
  if(!tmp255)
  {
    tmp251 = GreaterEq((data->simulationInfo->realParameter[70] /* ala.greThr.greHys.h PARAM */),0.0);
    if(!tmp251)
    {
      tmp253 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[70] /* ala.greThr.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta254 = stringAppend(MMC_REFSTRINGLIT(tmp252),tmp253);
      {
        const char* assert_cond = "(ala.greThr.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta254));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta254));
        }
      }
      tmp255 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2472
type: ALGORITHM

  assert(ala.greThr.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.greThr.h, has value: " + String(ala.greThr.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2472(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2472};
  modelica_boolean tmp256;
  static const MMC_DEFSTRINGLIT(tmp257,67,"Variable violating min constraint: 0.0 <= ala.greThr.h, has value: ");
  modelica_string tmp258;
  modelica_metatype tmpMeta259;
  static int tmp260 = 0;
  if(!tmp260)
  {
    tmp256 = GreaterEq((data->simulationInfo->realParameter[72] /* ala.greThr.h PARAM */),0.0);
    if(!tmp256)
    {
      tmp258 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[72] /* ala.greThr.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta259 = stringAppend(MMC_REFSTRINGLIT(tmp257),tmp258);
      {
        const char* assert_cond = "(ala.greThr.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta259));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta259));
        }
      }
      tmp260 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2473
type: ALGORITHM

  assert(ala.les.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les.lesHys.h, has value: " + String(ala.les.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2473(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2473};
  modelica_boolean tmp261;
  static const MMC_DEFSTRINGLIT(tmp262,71,"Variable violating min constraint: 0.0 <= ala.les.lesHys.h, has value: ");
  modelica_string tmp263;
  modelica_metatype tmpMeta264;
  static int tmp265 = 0;
  if(!tmp265)
  {
    tmp261 = GreaterEq((data->simulationInfo->realParameter[87] /* ala.les.lesHys.h PARAM */),0.0);
    if(!tmp261)
    {
      tmp263 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[87] /* ala.les.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta264 = stringAppend(MMC_REFSTRINGLIT(tmp262),tmp263);
      {
        const char* assert_cond = "(ala.les.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta264));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta264));
        }
      }
      tmp265 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2474
type: ALGORITHM

  assert(ala.les.h >= 0.0, "Variable violating min constraint: 0.0 <= ala.les.h, has value: " + String(ala.les.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2474(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2474};
  modelica_boolean tmp266;
  static const MMC_DEFSTRINGLIT(tmp267,64,"Variable violating min constraint: 0.0 <= ala.les.h, has value: ");
  modelica_string tmp268;
  modelica_metatype tmpMeta269;
  static int tmp270 = 0;
  if(!tmp270)
  {
    tmp266 = GreaterEq((data->simulationInfo->realParameter[86] /* ala.les.h PARAM */),0.0);
    if(!tmp266)
    {
      tmp268 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[86] /* ala.les.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta269 = stringAppend(MMC_REFSTRINGLIT(tmp267),tmp268);
      {
        const char* assert_cond = "(ala.les.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta269));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta269));
        }
      }
      tmp270 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2475
type: ALGORITHM

  assert(ala.heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and ala.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, "Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= ala.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: " + String(ala.heaCoi, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2475(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2475};
  modelica_boolean tmp271;
  modelica_boolean tmp272;
  static const MMC_DEFSTRINGLIT(tmp273,186,"Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= ala.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: ");
  modelica_string tmp274;
  modelica_metatype tmpMeta275;
  static int tmp276 = 0;
  if(!tmp276)
  {
    tmp271 = GreaterEq((data->simulationInfo->integerParameter[21] /* ala.heaCoi PARAM */),1);
    tmp272 = LessEq((data->simulationInfo->integerParameter[21] /* ala.heaCoi PARAM */),3);
    if(!(tmp271 && tmp272))
    {
      tmp274 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[21] /* ala.heaCoi PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta275 = stringAppend(MMC_REFSTRINGLIT(tmp273),tmp274);
      {
        const char* assert_cond = "(ala.heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and ala.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/Alarms.mo",4,3,6,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta275));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/Alarms.mo",4,3,6,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta275));
        }
      }
      tmp276 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2476
type: ALGORITHM

  assert(conLoo.zerCon1.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.zerCon1.lesHys.h, has value: " + String(conLoo.zerCon1.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2476(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2476};
  modelica_boolean tmp277;
  static const MMC_DEFSTRINGLIT(tmp278,78,"Variable violating min constraint: 0.0 <= conLoo.zerCon1.lesHys.h, has value: ");
  modelica_string tmp279;
  modelica_metatype tmpMeta280;
  static int tmp281 = 0;
  if(!tmp281)
  {
    tmp277 = GreaterEq((data->simulationInfo->realParameter[183] /* conLoo.zerCon1.lesHys.h PARAM */),0.0);
    if(!tmp277)
    {
      tmp279 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[183] /* conLoo.zerCon1.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta280 = stringAppend(MMC_REFSTRINGLIT(tmp278),tmp279);
      {
        const char* assert_cond = "(conLoo.zerCon1.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta280));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta280));
        }
      }
      tmp281 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2477
type: ALGORITHM

  assert(conLoo.zerCon1.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.zerCon1.h, has value: " + String(conLoo.zerCon1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2477(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2477};
  modelica_boolean tmp282;
  static const MMC_DEFSTRINGLIT(tmp283,71,"Variable violating min constraint: 0.0 <= conLoo.zerCon1.h, has value: ");
  modelica_string tmp284;
  modelica_metatype tmpMeta285;
  static int tmp286 = 0;
  if(!tmp286)
  {
    tmp282 = GreaterEq((data->simulationInfo->realParameter[182] /* conLoo.zerCon1.h PARAM */),0.0);
    if(!tmp282)
    {
      tmp284 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[182] /* conLoo.zerCon1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta285 = stringAppend(MMC_REFSTRINGLIT(tmp283),tmp284);
      {
        const char* assert_cond = "(conLoo.zerCon1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta285));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta285));
        }
      }
      tmp286 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2478
type: ALGORITHM

  assert(conLoo.zerCon.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.zerCon.lesHys.h, has value: " + String(conLoo.zerCon.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2478(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2478};
  modelica_boolean tmp287;
  static const MMC_DEFSTRINGLIT(tmp288,77,"Variable violating min constraint: 0.0 <= conLoo.zerCon.lesHys.h, has value: ");
  modelica_string tmp289;
  modelica_metatype tmpMeta290;
  static int tmp291 = 0;
  if(!tmp291)
  {
    tmp287 = GreaterEq((data->simulationInfo->realParameter[179] /* conLoo.zerCon.lesHys.h PARAM */),0.0);
    if(!tmp287)
    {
      tmp289 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[179] /* conLoo.zerCon.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta290 = stringAppend(MMC_REFSTRINGLIT(tmp288),tmp289);
      {
        const char* assert_cond = "(conLoo.zerCon.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta290));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",65,5,68,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta290));
        }
      }
      tmp291 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2479
type: ALGORITHM

  assert(conLoo.zerCon.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.zerCon.h, has value: " + String(conLoo.zerCon.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2479(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2479};
  modelica_boolean tmp292;
  static const MMC_DEFSTRINGLIT(tmp293,70,"Variable violating min constraint: 0.0 <= conLoo.zerCon.h, has value: ");
  modelica_string tmp294;
  modelica_metatype tmpMeta295;
  static int tmp296 = 0;
  if(!tmp296)
  {
    tmp292 = GreaterEq((data->simulationInfo->realParameter[178] /* conLoo.zerCon.h PARAM */),0.0);
    if(!tmp292)
    {
      tmp294 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[178] /* conLoo.zerCon.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta295 = stringAppend(MMC_REFSTRINGLIT(tmp293),tmp294);
      {
        const char* assert_cond = "(conLoo.zerCon.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta295));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/LessThreshold.mo",6,3,8,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta295));
        }
      }
      tmp296 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2480
type: ALGORITHM

  assert(conLoo.enaCooLoo.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.enaCooLoo.lesHys.h, has value: " + String(conLoo.enaCooLoo.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2480(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2480};
  modelica_boolean tmp297;
  static const MMC_DEFSTRINGLIT(tmp298,80,"Variable violating min constraint: 0.0 <= conLoo.enaCooLoo.lesHys.h, has value: ");
  modelica_string tmp299;
  modelica_metatype tmpMeta300;
  static int tmp301 = 0;
  if(!tmp301)
  {
    tmp297 = GreaterEq((data->simulationInfo->realParameter[171] /* conLoo.enaCooLoo.lesHys.h PARAM */),0.0);
    if(!tmp297)
    {
      tmp299 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[171] /* conLoo.enaCooLoo.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta300 = stringAppend(MMC_REFSTRINGLIT(tmp298),tmp299);
      {
        const char* assert_cond = "(conLoo.enaCooLoo.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta300));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta300));
        }
      }
      tmp301 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2481
type: ALGORITHM

  assert(conLoo.enaCooLoo.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.enaCooLoo.h, has value: " + String(conLoo.enaCooLoo.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2481(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2481};
  modelica_boolean tmp302;
  static const MMC_DEFSTRINGLIT(tmp303,73,"Variable violating min constraint: 0.0 <= conLoo.enaCooLoo.h, has value: ");
  modelica_string tmp304;
  modelica_metatype tmpMeta305;
  static int tmp306 = 0;
  if(!tmp306)
  {
    tmp302 = GreaterEq((data->simulationInfo->realParameter[170] /* conLoo.enaCooLoo.h PARAM */),0.0);
    if(!tmp302)
    {
      tmp304 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[170] /* conLoo.enaCooLoo.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta305 = stringAppend(MMC_REFSTRINGLIT(tmp303),tmp304);
      {
        const char* assert_cond = "(conLoo.enaCooLoo.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta305));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta305));
        }
      }
      tmp306 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2482
type: ALGORITHM

  assert(conLoo.enaHeaLoo.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.enaHeaLoo.lesHys.h, has value: " + String(conLoo.enaHeaLoo.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2482(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2482};
  modelica_boolean tmp307;
  static const MMC_DEFSTRINGLIT(tmp308,80,"Variable violating min constraint: 0.0 <= conLoo.enaHeaLoo.lesHys.h, has value: ");
  modelica_string tmp309;
  modelica_metatype tmpMeta310;
  static int tmp311 = 0;
  if(!tmp311)
  {
    tmp307 = GreaterEq((data->simulationInfo->realParameter[173] /* conLoo.enaHeaLoo.lesHys.h PARAM */),0.0);
    if(!tmp307)
    {
      tmp309 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[173] /* conLoo.enaHeaLoo.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta310 = stringAppend(MMC_REFSTRINGLIT(tmp308),tmp309);
      {
        const char* assert_cond = "(conLoo.enaHeaLoo.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta310));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta310));
        }
      }
      tmp311 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2483
type: ALGORITHM

  assert(conLoo.enaHeaLoo.h >= 0.0, "Variable violating min constraint: 0.0 <= conLoo.enaHeaLoo.h, has value: " + String(conLoo.enaHeaLoo.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2483(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2483};
  modelica_boolean tmp312;
  static const MMC_DEFSTRINGLIT(tmp313,73,"Variable violating min constraint: 0.0 <= conLoo.enaHeaLoo.h, has value: ");
  modelica_string tmp314;
  modelica_metatype tmpMeta315;
  static int tmp316 = 0;
  if(!tmp316)
  {
    tmp312 = GreaterEq((data->simulationInfo->realParameter[172] /* conLoo.enaHeaLoo.h PARAM */),0.0);
    if(!tmp312)
    {
      tmp314 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[172] /* conLoo.enaHeaLoo.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta315 = stringAppend(MMC_REFSTRINGLIT(tmp313),tmp314);
      {
        const char* assert_cond = "(conLoo.enaHeaLoo.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta315));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta315));
        }
      }
      tmp316 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2484
type: ALGORITHM

  assert(conLoo.conHea.k >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.k, has value: " + String(conLoo.conHea.k, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2484(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2484};
  modelica_boolean tmp317;
  static const MMC_DEFSTRINGLIT(tmp318,72,"Variable violating min constraint: 1e-13 <= conLoo.conHea.k, has value: ");
  modelica_string tmp319;
  modelica_metatype tmpMeta320;
  static int tmp321 = 0;
  if(!tmp321)
  {
    tmp317 = GreaterEq((data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */),1e-13);
    if(!tmp317)
    {
      tmp319 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[151] /* conLoo.conHea.k PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta320 = stringAppend(MMC_REFSTRINGLIT(tmp318),tmp319);
      {
        const char* assert_cond = "(conLoo.conHea.k >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta320));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta320));
        }
      }
      tmp321 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2485
type: ALGORITHM

  assert(conLoo.conHea.Ni >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.Ni, has value: " + String(conLoo.conHea.Ni, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2485(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2485};
  modelica_boolean tmp322;
  static const MMC_DEFSTRINGLIT(tmp323,73,"Variable violating min constraint: 1e-13 <= conLoo.conHea.Ni, has value: ");
  modelica_string tmp324;
  modelica_metatype tmpMeta325;
  static int tmp326 = 0;
  if(!tmp326)
  {
    tmp322 = GreaterEq((data->simulationInfo->realParameter[145] /* conLoo.conHea.Ni PARAM */),1e-13);
    if(!tmp322)
    {
      tmp324 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[145] /* conLoo.conHea.Ni PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta325 = stringAppend(MMC_REFSTRINGLIT(tmp323),tmp324);
      {
        const char* assert_cond = "(conLoo.conHea.Ni >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta325));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta325));
        }
      }
      tmp326 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2486
type: ALGORITHM

  assert(conLoo.conHea.r >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.r, has value: " + String(conLoo.conHea.r, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2486(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2486};
  modelica_boolean tmp327;
  static const MMC_DEFSTRINGLIT(tmp328,72,"Variable violating min constraint: 1e-13 <= conLoo.conHea.r, has value: ");
  modelica_string tmp329;
  modelica_metatype tmpMeta330;
  static int tmp331 = 0;
  if(!tmp331)
  {
    tmp327 = GreaterEq((data->simulationInfo->realParameter[154] /* conLoo.conHea.r PARAM */),1e-13);
    if(!tmp327)
    {
      tmp329 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[154] /* conLoo.conHea.r PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta330 = stringAppend(MMC_REFSTRINGLIT(tmp328),tmp329);
      {
        const char* assert_cond = "(conLoo.conHea.r >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta330));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta330));
        }
      }
      tmp331 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2487
type: ALGORITHM

  assert(conLoo.conHea.Ti >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.Ti, has value: " + String(conLoo.conHea.Ti, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2487(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2487};
  modelica_boolean tmp332;
  static const MMC_DEFSTRINGLIT(tmp333,73,"Variable violating min constraint: 1e-13 <= conLoo.conHea.Ti, has value: ");
  modelica_string tmp334;
  modelica_metatype tmpMeta335;
  static int tmp336 = 0;
  if(!tmp336)
  {
    tmp332 = GreaterEq((data->simulationInfo->realParameter[148] /* conLoo.conHea.Ti PARAM */),1e-13);
    if(!tmp332)
    {
      tmp334 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[148] /* conLoo.conHea.Ti PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta335 = stringAppend(MMC_REFSTRINGLIT(tmp333),tmp334);
      {
        const char* assert_cond = "(conLoo.conHea.Ti >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta335));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta335));
        }
      }
      tmp336 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2488
type: ALGORITHM

  assert(conLoo.conHea.Nd >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.Nd, has value: " + String(conLoo.conHea.Nd, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2488(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2488};
  modelica_boolean tmp337;
  static const MMC_DEFSTRINGLIT(tmp338,73,"Variable violating min constraint: 1e-13 <= conLoo.conHea.Nd, has value: ");
  modelica_string tmp339;
  modelica_metatype tmpMeta340;
  static int tmp341 = 0;
  if(!tmp341)
  {
    tmp337 = GreaterEq((data->simulationInfo->realParameter[144] /* conLoo.conHea.Nd PARAM */),1e-13);
    if(!tmp337)
    {
      tmp339 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[144] /* conLoo.conHea.Nd PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta340 = stringAppend(MMC_REFSTRINGLIT(tmp338),tmp339);
      {
        const char* assert_cond = "(conLoo.conHea.Nd >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta340));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta340));
        }
      }
      tmp341 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2489
type: ALGORITHM

  assert(conLoo.conHea.Td >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conHea.Td, has value: " + String(conLoo.conHea.Td, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2489(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2489};
  modelica_boolean tmp342;
  static const MMC_DEFSTRINGLIT(tmp343,73,"Variable violating min constraint: 1e-13 <= conLoo.conHea.Td, has value: ");
  modelica_string tmp344;
  modelica_metatype tmpMeta345;
  static int tmp346 = 0;
  if(!tmp346)
  {
    tmp342 = GreaterEq((data->simulationInfo->realParameter[147] /* conLoo.conHea.Td PARAM */),1e-13);
    if(!tmp342)
    {
      tmp344 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[147] /* conLoo.conHea.Td PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta345 = stringAppend(MMC_REFSTRINGLIT(tmp343),tmp344);
      {
        const char* assert_cond = "(conLoo.conHea.Td >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta345));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta345));
        }
      }
      tmp346 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2490
type: ALGORITHM

  assert(conLoo.conHea.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and conLoo.conHea.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= conLoo.conHea.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(conLoo.conHea.controllerType, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2490(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2490};
  modelica_boolean tmp347;
  modelica_boolean tmp348;
  static const MMC_DEFSTRINGLIT(tmp349,192,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= conLoo.conHea.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp350;
  modelica_metatype tmpMeta351;
  static int tmp352 = 0;
  if(!tmp352)
  {
    tmp347 = GreaterEq((data->simulationInfo->integerParameter[24] /* conLoo.conHea.controllerType PARAM */),1);
    tmp348 = LessEq((data->simulationInfo->integerParameter[24] /* conLoo.conHea.controllerType PARAM */),4);
    if(!(tmp347 && tmp348))
    {
      tmp350 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[24] /* conLoo.conHea.controllerType PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta351 = stringAppend(MMC_REFSTRINGLIT(tmp349),tmp350);
      {
        const char* assert_cond = "(conLoo.conHea.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and conLoo.conHea.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta351));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta351));
        }
      }
      tmp352 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2491
type: ALGORITHM

  assert(conLoo.conCoo.k >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.k, has value: " + String(conLoo.conCoo.k, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2491(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2491};
  modelica_boolean tmp353;
  static const MMC_DEFSTRINGLIT(tmp354,72,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.k, has value: ");
  modelica_string tmp355;
  modelica_metatype tmpMeta356;
  static int tmp357 = 0;
  if(!tmp357)
  {
    tmp353 = GreaterEq((data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */),1e-13);
    if(!tmp353)
    {
      tmp355 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[127] /* conLoo.conCoo.k PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta356 = stringAppend(MMC_REFSTRINGLIT(tmp354),tmp355);
      {
        const char* assert_cond = "(conLoo.conCoo.k >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta356));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",7,3,9,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta356));
        }
      }
      tmp357 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2492
type: ALGORITHM

  assert(conLoo.conCoo.Ni >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.Ni, has value: " + String(conLoo.conCoo.Ni, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2492(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2492};
  modelica_boolean tmp358;
  static const MMC_DEFSTRINGLIT(tmp359,73,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.Ni, has value: ");
  modelica_string tmp360;
  modelica_metatype tmpMeta361;
  static int tmp362 = 0;
  if(!tmp362)
  {
    tmp358 = GreaterEq((data->simulationInfo->realParameter[121] /* conLoo.conCoo.Ni PARAM */),1e-13);
    if(!tmp358)
    {
      tmp360 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[121] /* conLoo.conCoo.Ni PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta361 = stringAppend(MMC_REFSTRINGLIT(tmp359),tmp360);
      {
        const char* assert_cond = "(conLoo.conCoo.Ni >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta361));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",30,3,33,178,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta361));
        }
      }
      tmp362 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2493
type: ALGORITHM

  assert(conLoo.conCoo.r >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.r, has value: " + String(conLoo.conCoo.r, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2493(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2493};
  modelica_boolean tmp363;
  static const MMC_DEFSTRINGLIT(tmp364,72,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.r, has value: ");
  modelica_string tmp365;
  modelica_metatype tmpMeta366;
  static int tmp367 = 0;
  if(!tmp367)
  {
    tmp363 = GreaterEq((data->simulationInfo->realParameter[130] /* conLoo.conCoo.r PARAM */),1e-13);
    if(!tmp363)
    {
      tmp365 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[130] /* conLoo.conCoo.r PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta366 = stringAppend(MMC_REFSTRINGLIT(tmp364),tmp365);
      {
        const char* assert_cond = "(conLoo.conCoo.r >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta366));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",22,3,23,73,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta366));
        }
      }
      tmp367 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2494
type: ALGORITHM

  assert(conLoo.conCoo.Ti >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.Ti, has value: " + String(conLoo.conCoo.Ti, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2494(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2494};
  modelica_boolean tmp368;
  static const MMC_DEFSTRINGLIT(tmp369,73,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.Ti, has value: ");
  modelica_string tmp370;
  modelica_metatype tmpMeta371;
  static int tmp372 = 0;
  if(!tmp372)
  {
    tmp368 = GreaterEq((data->simulationInfo->realParameter[124] /* conLoo.conCoo.Ti PARAM */),1e-13);
    if(!tmp368)
    {
      tmp370 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[124] /* conLoo.conCoo.Ti PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta371 = stringAppend(MMC_REFSTRINGLIT(tmp369),tmp370);
      {
        const char* assert_cond = "(conLoo.conCoo.Ti >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta371));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",10,3,15,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta371));
        }
      }
      tmp372 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2495
type: ALGORITHM

  assert(conLoo.conCoo.Nd >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.Nd, has value: " + String(conLoo.conCoo.Nd, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2495(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2495};
  modelica_boolean tmp373;
  static const MMC_DEFSTRINGLIT(tmp374,73,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.Nd, has value: ");
  modelica_string tmp375;
  modelica_metatype tmpMeta376;
  static int tmp377 = 0;
  if(!tmp377)
  {
    tmp373 = GreaterEq((data->simulationInfo->realParameter[120] /* conLoo.conCoo.Nd PARAM */),1e-13);
    if(!tmp373)
    {
      tmp375 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[120] /* conLoo.conCoo.Nd PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta376 = stringAppend(MMC_REFSTRINGLIT(tmp374),tmp375);
      {
        const char* assert_cond = "(conLoo.conCoo.Nd >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta376));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",34,3,37,172,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta376));
        }
      }
      tmp377 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2496
type: ALGORITHM

  assert(conLoo.conCoo.Td >= 1e-13, "Variable violating min constraint: 1e-13 <= conLoo.conCoo.Td, has value: " + String(conLoo.conCoo.Td, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2496(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2496};
  modelica_boolean tmp378;
  static const MMC_DEFSTRINGLIT(tmp379,73,"Variable violating min constraint: 1e-13 <= conLoo.conCoo.Td, has value: ");
  modelica_string tmp380;
  modelica_metatype tmpMeta381;
  static int tmp382 = 0;
  if(!tmp382)
  {
    tmp378 = GreaterEq((data->simulationInfo->realParameter[123] /* conLoo.conCoo.Td PARAM */),1e-13);
    if(!tmp378)
    {
      tmp380 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[123] /* conLoo.conCoo.Td PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta381 = stringAppend(MMC_REFSTRINGLIT(tmp379),tmp380);
      {
        const char* assert_cond = "(conLoo.conCoo.Td >= 1e-13)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta381));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",16,3,21,154,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta381));
        }
      }
      tmp382 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2497
type: ALGORITHM

  assert(conLoo.conCoo.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and conLoo.conCoo.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= conLoo.conCoo.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(conLoo.conCoo.controllerType, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2497(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2497};
  modelica_boolean tmp383;
  modelica_boolean tmp384;
  static const MMC_DEFSTRINGLIT(tmp385,192,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= conLoo.conCoo.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp386;
  modelica_metatype tmpMeta387;
  static int tmp388 = 0;
  if(!tmp388)
  {
    tmp383 = GreaterEq((data->simulationInfo->integerParameter[23] /* conLoo.conCoo.controllerType PARAM */),1);
    tmp384 = LessEq((data->simulationInfo->integerParameter[23] /* conLoo.conCoo.controllerType PARAM */),4);
    if(!(tmp383 && tmp384))
    {
      tmp386 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[23] /* conLoo.conCoo.controllerType PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta387 = stringAppend(MMC_REFSTRINGLIT(tmp385),tmp386);
      {
        const char* assert_cond = "(conLoo.conCoo.controllerType >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and conLoo.conCoo.controllerType <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta387));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/PIDWithReset.mo",4,3,6,25,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta387));
        }
      }
      tmp388 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2498
type: ALGORITHM

  assert(sysReq.sampler3.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= sysReq.sampler3.samplePeriod, has value: " + String(sysReq.sampler3.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2498(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2498};
  modelica_boolean tmp389;
  static const MMC_DEFSTRINGLIT(tmp390,85,"Variable violating min constraint: 0.001 <= sysReq.sampler3.samplePeriod, has value: ");
  modelica_string tmp391;
  modelica_metatype tmpMeta392;
  static int tmp393 = 0;
  if(!tmp393)
  {
    tmp389 = GreaterEq((data->simulationInfo->realParameter[416] /* sysReq.sampler3.samplePeriod PARAM */),0.001);
    if(!tmp389)
    {
      tmp391 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[416] /* sysReq.sampler3.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta392 = stringAppend(MMC_REFSTRINGLIT(tmp390),tmp391);
      {
        const char* assert_cond = "(sysReq.sampler3.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta392));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta392));
        }
      }
      tmp393 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2499
type: ALGORITHM

  assert(sysReq.sampler2.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= sysReq.sampler2.samplePeriod, has value: " + String(sysReq.sampler2.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2499(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2499};
  modelica_boolean tmp394;
  static const MMC_DEFSTRINGLIT(tmp395,85,"Variable violating min constraint: 0.001 <= sysReq.sampler2.samplePeriod, has value: ");
  modelica_string tmp396;
  modelica_metatype tmpMeta397;
  static int tmp398 = 0;
  if(!tmp398)
  {
    tmp394 = GreaterEq((data->simulationInfo->realParameter[414] /* sysReq.sampler2.samplePeriod PARAM */),0.001);
    if(!tmp394)
    {
      tmp396 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[414] /* sysReq.sampler2.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta397 = stringAppend(MMC_REFSTRINGLIT(tmp395),tmp396);
      {
        const char* assert_cond = "(sysReq.sampler2.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta397));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta397));
        }
      }
      tmp398 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2500
type: ALGORITHM

  assert(sysReq.sampler1.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= sysReq.sampler1.samplePeriod, has value: " + String(sysReq.sampler1.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2500(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2500};
  modelica_boolean tmp399;
  static const MMC_DEFSTRINGLIT(tmp400,85,"Variable violating min constraint: 0.001 <= sysReq.sampler1.samplePeriod, has value: ");
  modelica_string tmp401;
  modelica_metatype tmpMeta402;
  static int tmp403 = 0;
  if(!tmp403)
  {
    tmp399 = GreaterEq((data->simulationInfo->realParameter[412] /* sysReq.sampler1.samplePeriod PARAM */),0.001);
    if(!tmp399)
    {
      tmp401 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[412] /* sysReq.sampler1.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta402 = stringAppend(MMC_REFSTRINGLIT(tmp400),tmp401);
      {
        const char* assert_cond = "(sysReq.sampler1.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta402));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta402));
        }
      }
      tmp403 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2501
type: ALGORITHM

  assert(sysReq.sampler.samplePeriod >= 0.001, "Variable violating min constraint: 0.001 <= sysReq.sampler.samplePeriod, has value: " + String(sysReq.sampler.samplePeriod, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2501(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2501};
  modelica_boolean tmp404;
  static const MMC_DEFSTRINGLIT(tmp405,84,"Variable violating min constraint: 0.001 <= sysReq.sampler.samplePeriod, has value: ");
  modelica_string tmp406;
  modelica_metatype tmpMeta407;
  static int tmp408 = 0;
  if(!tmp408)
  {
    tmp404 = GreaterEq((data->simulationInfo->realParameter[410] /* sysReq.sampler.samplePeriod PARAM */),0.001);
    if(!tmp404)
    {
      tmp406 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[410] /* sysReq.sampler.samplePeriod PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta407 = stringAppend(MMC_REFSTRINGLIT(tmp405),tmp406);
      {
        const char* assert_cond = "(sysReq.sampler.samplePeriod >= 0.001)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta407));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Discrete/Sampler.mo",4,3,8,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta407));
        }
      }
      tmp408 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2502
type: ALGORITHM

  assert(sysReq.greThr6.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr6.greHys.h, has value: " + String(sysReq.greThr6.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2502(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2502};
  modelica_boolean tmp409;
  static const MMC_DEFSTRINGLIT(tmp410,78,"Variable violating min constraint: 0.0 <= sysReq.greThr6.greHys.h, has value: ");
  modelica_string tmp411;
  modelica_metatype tmpMeta412;
  static int tmp413 = 0;
  if(!tmp413)
  {
    tmp409 = GreaterEq((data->simulationInfo->realParameter[400] /* sysReq.greThr6.greHys.h PARAM */),0.0);
    if(!tmp409)
    {
      tmp411 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[400] /* sysReq.greThr6.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta412 = stringAppend(MMC_REFSTRINGLIT(tmp410),tmp411);
      {
        const char* assert_cond = "(sysReq.greThr6.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta412));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta412));
        }
      }
      tmp413 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2503
type: ALGORITHM

  assert(sysReq.greThr6.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr6.h, has value: " + String(sysReq.greThr6.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2503(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2503};
  modelica_boolean tmp414;
  static const MMC_DEFSTRINGLIT(tmp415,71,"Variable violating min constraint: 0.0 <= sysReq.greThr6.h, has value: ");
  modelica_string tmp416;
  modelica_metatype tmpMeta417;
  static int tmp418 = 0;
  if(!tmp418)
  {
    tmp414 = GreaterEq((data->simulationInfo->realParameter[402] /* sysReq.greThr6.h PARAM */),0.0);
    if(!tmp414)
    {
      tmp416 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[402] /* sysReq.greThr6.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta417 = stringAppend(MMC_REFSTRINGLIT(tmp415),tmp416);
      {
        const char* assert_cond = "(sysReq.greThr6.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta417));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta417));
        }
      }
      tmp418 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2504
type: ALGORITHM

  assert(sysReq.greThr5.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr5.greHys.h, has value: " + String(sysReq.greThr5.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2504(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2504};
  modelica_boolean tmp419;
  static const MMC_DEFSTRINGLIT(tmp420,78,"Variable violating min constraint: 0.0 <= sysReq.greThr5.greHys.h, has value: ");
  modelica_string tmp421;
  modelica_metatype tmpMeta422;
  static int tmp423 = 0;
  if(!tmp423)
  {
    tmp419 = GreaterEq((data->simulationInfo->realParameter[396] /* sysReq.greThr5.greHys.h PARAM */),0.0);
    if(!tmp419)
    {
      tmp421 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[396] /* sysReq.greThr5.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta422 = stringAppend(MMC_REFSTRINGLIT(tmp420),tmp421);
      {
        const char* assert_cond = "(sysReq.greThr5.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta422));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta422));
        }
      }
      tmp423 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2505
type: ALGORITHM

  assert(sysReq.greThr5.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr5.h, has value: " + String(sysReq.greThr5.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2505(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2505};
  modelica_boolean tmp424;
  static const MMC_DEFSTRINGLIT(tmp425,71,"Variable violating min constraint: 0.0 <= sysReq.greThr5.h, has value: ");
  modelica_string tmp426;
  modelica_metatype tmpMeta427;
  static int tmp428 = 0;
  if(!tmp428)
  {
    tmp424 = GreaterEq((data->simulationInfo->realParameter[398] /* sysReq.greThr5.h PARAM */),0.0);
    if(!tmp424)
    {
      tmp426 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[398] /* sysReq.greThr5.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta427 = stringAppend(MMC_REFSTRINGLIT(tmp425),tmp426);
      {
        const char* assert_cond = "(sysReq.greThr5.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta427));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta427));
        }
      }
      tmp428 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2506
type: ALGORITHM

  assert(sysReq.greEqu1.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greEqu1.greHys.h, has value: " + String(sysReq.greEqu1.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2506(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2506};
  modelica_boolean tmp429;
  static const MMC_DEFSTRINGLIT(tmp430,78,"Variable violating min constraint: 0.0 <= sysReq.greEqu1.greHys.h, has value: ");
  modelica_string tmp431;
  modelica_metatype tmpMeta432;
  static int tmp433 = 0;
  if(!tmp433)
  {
    tmp429 = GreaterEq((data->simulationInfo->realParameter[374] /* sysReq.greEqu1.greHys.h PARAM */),0.0);
    if(!tmp429)
    {
      tmp431 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[374] /* sysReq.greEqu1.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta432 = stringAppend(MMC_REFSTRINGLIT(tmp430),tmp431);
      {
        const char* assert_cond = "(sysReq.greEqu1.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta432));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta432));
        }
      }
      tmp433 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2507
type: ALGORITHM

  assert(sysReq.greEqu1.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greEqu1.h, has value: " + String(sysReq.greEqu1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2507(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2507};
  modelica_boolean tmp434;
  static const MMC_DEFSTRINGLIT(tmp435,71,"Variable violating min constraint: 0.0 <= sysReq.greEqu1.h, has value: ");
  modelica_string tmp436;
  modelica_metatype tmpMeta437;
  static int tmp438 = 0;
  if(!tmp438)
  {
    tmp434 = GreaterEq((data->simulationInfo->realParameter[375] /* sysReq.greEqu1.h PARAM */),0.0);
    if(!tmp434)
    {
      tmp436 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[375] /* sysReq.greEqu1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta437 = stringAppend(MMC_REFSTRINGLIT(tmp435),tmp436);
      {
        const char* assert_cond = "(sysReq.greEqu1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta437));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta437));
        }
      }
      tmp438 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2508
type: ALGORITHM

  assert(sysReq.greEqu.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greEqu.greHys.h, has value: " + String(sysReq.greEqu.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2508(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2508};
  modelica_boolean tmp439;
  static const MMC_DEFSTRINGLIT(tmp440,77,"Variable violating min constraint: 0.0 <= sysReq.greEqu.greHys.h, has value: ");
  modelica_string tmp441;
  modelica_metatype tmpMeta442;
  static int tmp443 = 0;
  if(!tmp443)
  {
    tmp439 = GreaterEq((data->simulationInfo->realParameter[372] /* sysReq.greEqu.greHys.h PARAM */),0.0);
    if(!tmp439)
    {
      tmp441 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[372] /* sysReq.greEqu.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta442 = stringAppend(MMC_REFSTRINGLIT(tmp440),tmp441);
      {
        const char* assert_cond = "(sysReq.greEqu.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta442));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",64,5,67,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta442));
        }
      }
      tmp443 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2509
type: ALGORITHM

  assert(sysReq.greEqu.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greEqu.h, has value: " + String(sysReq.greEqu.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2509(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2509};
  modelica_boolean tmp444;
  static const MMC_DEFSTRINGLIT(tmp445,70,"Variable violating min constraint: 0.0 <= sysReq.greEqu.h, has value: ");
  modelica_string tmp446;
  modelica_metatype tmpMeta447;
  static int tmp448 = 0;
  if(!tmp448)
  {
    tmp444 = GreaterEq((data->simulationInfo->realParameter[373] /* sysReq.greEqu.h PARAM */),0.0);
    if(!tmp444)
    {
      tmp446 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[373] /* sysReq.greEqu.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta447 = stringAppend(MMC_REFSTRINGLIT(tmp445),tmp446);
      {
        const char* assert_cond = "(sysReq.greEqu.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta447));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Greater.mo",4,3,7,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta447));
        }
      }
      tmp448 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2510
type: ALGORITHM

  assert(sysReq.greThr4.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr4.greHys.h, has value: " + String(sysReq.greThr4.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2510(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2510};
  modelica_boolean tmp449;
  static const MMC_DEFSTRINGLIT(tmp450,78,"Variable violating min constraint: 0.0 <= sysReq.greThr4.greHys.h, has value: ");
  modelica_string tmp451;
  modelica_metatype tmpMeta452;
  static int tmp453 = 0;
  if(!tmp453)
  {
    tmp449 = GreaterEq((data->simulationInfo->realParameter[392] /* sysReq.greThr4.greHys.h PARAM */),0.0);
    if(!tmp449)
    {
      tmp451 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[392] /* sysReq.greThr4.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta452 = stringAppend(MMC_REFSTRINGLIT(tmp450),tmp451);
      {
        const char* assert_cond = "(sysReq.greThr4.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta452));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta452));
        }
      }
      tmp453 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2511
type: ALGORITHM

  assert(sysReq.greThr4.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr4.h, has value: " + String(sysReq.greThr4.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2511(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2511};
  modelica_boolean tmp454;
  static const MMC_DEFSTRINGLIT(tmp455,71,"Variable violating min constraint: 0.0 <= sysReq.greThr4.h, has value: ");
  modelica_string tmp456;
  modelica_metatype tmpMeta457;
  static int tmp458 = 0;
  if(!tmp458)
  {
    tmp454 = GreaterEq((data->simulationInfo->realParameter[394] /* sysReq.greThr4.h PARAM */),0.0);
    if(!tmp454)
    {
      tmp456 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[394] /* sysReq.greThr4.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta457 = stringAppend(MMC_REFSTRINGLIT(tmp455),tmp456);
      {
        const char* assert_cond = "(sysReq.greThr4.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta457));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta457));
        }
      }
      tmp458 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2512
type: ALGORITHM

  assert(sysReq.greThr.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr.greHys.h, has value: " + String(sysReq.greThr.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2512(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2512};
  modelica_boolean tmp459;
  static const MMC_DEFSTRINGLIT(tmp460,77,"Variable violating min constraint: 0.0 <= sysReq.greThr.greHys.h, has value: ");
  modelica_string tmp461;
  modelica_metatype tmpMeta462;
  static int tmp463 = 0;
  if(!tmp463)
  {
    tmp459 = GreaterEq((data->simulationInfo->realParameter[376] /* sysReq.greThr.greHys.h PARAM */),0.0);
    if(!tmp459)
    {
      tmp461 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[376] /* sysReq.greThr.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta462 = stringAppend(MMC_REFSTRINGLIT(tmp460),tmp461);
      {
        const char* assert_cond = "(sysReq.greThr.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta462));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta462));
        }
      }
      tmp463 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2513
type: ALGORITHM

  assert(sysReq.greThr.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr.h, has value: " + String(sysReq.greThr.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2513(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2513};
  modelica_boolean tmp464;
  static const MMC_DEFSTRINGLIT(tmp465,70,"Variable violating min constraint: 0.0 <= sysReq.greThr.h, has value: ");
  modelica_string tmp466;
  modelica_metatype tmpMeta467;
  static int tmp468 = 0;
  if(!tmp468)
  {
    tmp464 = GreaterEq((data->simulationInfo->realParameter[378] /* sysReq.greThr.h PARAM */),0.0);
    if(!tmp464)
    {
      tmp466 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[378] /* sysReq.greThr.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta467 = stringAppend(MMC_REFSTRINGLIT(tmp465),tmp466);
      {
        const char* assert_cond = "(sysReq.greThr.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta467));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta467));
        }
      }
      tmp468 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2514
type: ALGORITHM

  assert(sysReq.greThr3.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr3.greHys.h, has value: " + String(sysReq.greThr3.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2514(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2514};
  modelica_boolean tmp469;
  static const MMC_DEFSTRINGLIT(tmp470,78,"Variable violating min constraint: 0.0 <= sysReq.greThr3.greHys.h, has value: ");
  modelica_string tmp471;
  modelica_metatype tmpMeta472;
  static int tmp473 = 0;
  if(!tmp473)
  {
    tmp469 = GreaterEq((data->simulationInfo->realParameter[388] /* sysReq.greThr3.greHys.h PARAM */),0.0);
    if(!tmp469)
    {
      tmp471 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[388] /* sysReq.greThr3.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta472 = stringAppend(MMC_REFSTRINGLIT(tmp470),tmp471);
      {
        const char* assert_cond = "(sysReq.greThr3.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta472));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta472));
        }
      }
      tmp473 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2515
type: ALGORITHM

  assert(sysReq.greThr3.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr3.h, has value: " + String(sysReq.greThr3.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2515(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2515};
  modelica_boolean tmp474;
  static const MMC_DEFSTRINGLIT(tmp475,71,"Variable violating min constraint: 0.0 <= sysReq.greThr3.h, has value: ");
  modelica_string tmp476;
  modelica_metatype tmpMeta477;
  static int tmp478 = 0;
  if(!tmp478)
  {
    tmp474 = GreaterEq((data->simulationInfo->realParameter[390] /* sysReq.greThr3.h PARAM */),0.0);
    if(!tmp474)
    {
      tmp476 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[390] /* sysReq.greThr3.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta477 = stringAppend(MMC_REFSTRINGLIT(tmp475),tmp476);
      {
        const char* assert_cond = "(sysReq.greThr3.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta477));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta477));
        }
      }
      tmp478 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2516
type: ALGORITHM

  assert(sysReq.greThr2.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr2.greHys.h, has value: " + String(sysReq.greThr2.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2516(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2516};
  modelica_boolean tmp479;
  static const MMC_DEFSTRINGLIT(tmp480,78,"Variable violating min constraint: 0.0 <= sysReq.greThr2.greHys.h, has value: ");
  modelica_string tmp481;
  modelica_metatype tmpMeta482;
  static int tmp483 = 0;
  if(!tmp483)
  {
    tmp479 = GreaterEq((data->simulationInfo->realParameter[384] /* sysReq.greThr2.greHys.h PARAM */),0.0);
    if(!tmp479)
    {
      tmp481 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[384] /* sysReq.greThr2.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta482 = stringAppend(MMC_REFSTRINGLIT(tmp480),tmp481);
      {
        const char* assert_cond = "(sysReq.greThr2.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta482));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta482));
        }
      }
      tmp483 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2517
type: ALGORITHM

  assert(sysReq.greThr2.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr2.h, has value: " + String(sysReq.greThr2.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2517(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2517};
  modelica_boolean tmp484;
  static const MMC_DEFSTRINGLIT(tmp485,71,"Variable violating min constraint: 0.0 <= sysReq.greThr2.h, has value: ");
  modelica_string tmp486;
  modelica_metatype tmpMeta487;
  static int tmp488 = 0;
  if(!tmp488)
  {
    tmp484 = GreaterEq((data->simulationInfo->realParameter[386] /* sysReq.greThr2.h PARAM */),0.0);
    if(!tmp484)
    {
      tmp486 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[386] /* sysReq.greThr2.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta487 = stringAppend(MMC_REFSTRINGLIT(tmp485),tmp486);
      {
        const char* assert_cond = "(sysReq.greThr2.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta487));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta487));
        }
      }
      tmp488 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2518
type: ALGORITHM

  assert(sysReq.greThr1.greHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr1.greHys.h, has value: " + String(sysReq.greThr1.greHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2518(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2518};
  modelica_boolean tmp489;
  static const MMC_DEFSTRINGLIT(tmp490,78,"Variable violating min constraint: 0.0 <= sysReq.greThr1.greHys.h, has value: ");
  modelica_string tmp491;
  modelica_metatype tmpMeta492;
  static int tmp493 = 0;
  if(!tmp493)
  {
    tmp489 = GreaterEq((data->simulationInfo->realParameter[380] /* sysReq.greThr1.greHys.h PARAM */),0.0);
    if(!tmp489)
    {
      tmp491 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[380] /* sysReq.greThr1.greHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta492 = stringAppend(MMC_REFSTRINGLIT(tmp490),tmp491);
      {
        const char* assert_cond = "(sysReq.greThr1.greHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta492));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",66,5,69,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta492));
        }
      }
      tmp493 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2519
type: ALGORITHM

  assert(sysReq.greThr1.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.greThr1.h, has value: " + String(sysReq.greThr1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2519(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2519};
  modelica_boolean tmp494;
  static const MMC_DEFSTRINGLIT(tmp495,71,"Variable violating min constraint: 0.0 <= sysReq.greThr1.h, has value: ");
  modelica_string tmp496;
  modelica_metatype tmpMeta497;
  static int tmp498 = 0;
  if(!tmp498)
  {
    tmp494 = GreaterEq((data->simulationInfo->realParameter[382] /* sysReq.greThr1.h PARAM */),0.0);
    if(!tmp494)
    {
      tmp496 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[382] /* sysReq.greThr1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta497 = stringAppend(MMC_REFSTRINGLIT(tmp495),tmp496);
      {
        const char* assert_cond = "(sysReq.greThr1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta497));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/GreaterThreshold.mo",6,3,9,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta497));
        }
      }
      tmp498 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2520
type: ALGORITHM

  assert(sysReq.les1.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.les1.lesHys.h, has value: " + String(sysReq.les1.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2520(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2520};
  modelica_boolean tmp499;
  static const MMC_DEFSTRINGLIT(tmp500,75,"Variable violating min constraint: 0.0 <= sysReq.les1.lesHys.h, has value: ");
  modelica_string tmp501;
  modelica_metatype tmpMeta502;
  static int tmp503 = 0;
  if(!tmp503)
  {
    tmp499 = GreaterEq((data->simulationInfo->realParameter[407] /* sysReq.les1.lesHys.h PARAM */),0.0);
    if(!tmp499)
    {
      tmp501 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[407] /* sysReq.les1.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta502 = stringAppend(MMC_REFSTRINGLIT(tmp500),tmp501);
      {
        const char* assert_cond = "(sysReq.les1.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta502));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta502));
        }
      }
      tmp503 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2521
type: ALGORITHM

  assert(sysReq.les1.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.les1.h, has value: " + String(sysReq.les1.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2521(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2521};
  modelica_boolean tmp504;
  static const MMC_DEFSTRINGLIT(tmp505,68,"Variable violating min constraint: 0.0 <= sysReq.les1.h, has value: ");
  modelica_string tmp506;
  modelica_metatype tmpMeta507;
  static int tmp508 = 0;
  if(!tmp508)
  {
    tmp504 = GreaterEq((data->simulationInfo->realParameter[406] /* sysReq.les1.h PARAM */),0.0);
    if(!tmp504)
    {
      tmp506 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[406] /* sysReq.les1.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta507 = stringAppend(MMC_REFSTRINGLIT(tmp505),tmp506);
      {
        const char* assert_cond = "(sysReq.les1.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta507));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta507));
        }
      }
      tmp508 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2522
type: ALGORITHM

  assert(sysReq.les.lesHys.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.les.lesHys.h, has value: " + String(sysReq.les.lesHys.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2522(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2522};
  modelica_boolean tmp509;
  static const MMC_DEFSTRINGLIT(tmp510,74,"Variable violating min constraint: 0.0 <= sysReq.les.lesHys.h, has value: ");
  modelica_string tmp511;
  modelica_metatype tmpMeta512;
  static int tmp513 = 0;
  if(!tmp513)
  {
    tmp509 = GreaterEq((data->simulationInfo->realParameter[405] /* sysReq.les.lesHys.h PARAM */),0.0);
    if(!tmp509)
    {
      tmp511 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[405] /* sysReq.les.lesHys.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta512 = stringAppend(MMC_REFSTRINGLIT(tmp510),tmp511);
      {
        const char* assert_cond = "(sysReq.les.lesHys.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta512));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",63,5,65,33,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta512));
        }
      }
      tmp513 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2523
type: ALGORITHM

  assert(sysReq.les.h >= 0.0, "Variable violating min constraint: 0.0 <= sysReq.les.h, has value: " + String(sysReq.les.h, "g"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2523(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2523};
  modelica_boolean tmp514;
  static const MMC_DEFSTRINGLIT(tmp515,67,"Variable violating min constraint: 0.0 <= sysReq.les.h, has value: ");
  modelica_string tmp516;
  modelica_metatype tmpMeta517;
  static int tmp518 = 0;
  if(!tmp518)
  {
    tmp514 = GreaterEq((data->simulationInfo->realParameter[404] /* sysReq.les.h PARAM */),0.0);
    if(!tmp514)
    {
      tmp516 = modelica_real_to_modelica_string_format((data->simulationInfo->realParameter[404] /* sysReq.les.h PARAM */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta517 = stringAppend(MMC_REFSTRINGLIT(tmp515),tmp516);
      {
        const char* assert_cond = "(sysReq.les.h >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta517));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/CDL/Reals/Less.mo",4,3,6,31,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta517));
        }
      }
      tmp518 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2524
type: ALGORITHM

  assert(sysReq.heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and sysReq.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, "Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= sysReq.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: " + String(sysReq.heaCoi, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2524(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2524};
  modelica_boolean tmp519;
  modelica_boolean tmp520;
  static const MMC_DEFSTRINGLIT(tmp521,189,"Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= sysReq.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: ");
  modelica_string tmp522;
  modelica_metatype tmpMeta523;
  static int tmp524 = 0;
  if(!tmp524)
  {
    tmp519 = GreaterEq((data->simulationInfo->integerParameter[49] /* sysReq.heaCoi PARAM */),1);
    tmp520 = LessEq((data->simulationInfo->integerParameter[49] /* sysReq.heaCoi PARAM */),3);
    if(!(tmp519 && tmp520))
    {
      tmp522 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[49] /* sysReq.heaCoi PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta523 = stringAppend(MMC_REFSTRINGLIT(tmp521),tmp522);
      {
        const char* assert_cond = "(sysReq.heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and sysReq.heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/SystemRequests.mo",4,3,6,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta523));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/SystemRequests.mo",4,3,6,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta523));
        }
      }
      tmp524 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2525
type: ALGORITHM

  assert(heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, "Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: " + String(heaCoi, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2525(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2525};
  modelica_boolean tmp525;
  modelica_boolean tmp526;
  static const MMC_DEFSTRINGLIT(tmp527,182,"Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None <= heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric, has value: ");
  modelica_string tmp528;
  modelica_metatype tmpMeta529;
  static int tmp530 = 0;
  if(!tmp530)
  {
    tmp525 = GreaterEq((data->simulationInfo->integerParameter[37] /* heaCoi PARAM */),1);
    tmp526 = LessEq((data->simulationInfo->integerParameter[37] /* heaCoi PARAM */),3);
    if(!(tmp525 && tmp526))
    {
      tmp528 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[37] /* heaCoi PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta529 = stringAppend(MMC_REFSTRINGLIT(tmp527),tmp528);
      {
        const char* assert_cond = "(heaCoi >= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.None and heaCoi <= Buildings.Controls.OBC.ASHRAE.G36.Types.HeatingCoil.Electric)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",398,3,402,47,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta529));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",398,3,402,47,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta529));
        }
      }
      tmp530 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2526
type: ALGORITHM

  assert(controllerTypeDam >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(controllerTypeDam, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2526(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2526};
  modelica_boolean tmp531;
  modelica_boolean tmp532;
  static const MMC_DEFSTRINGLIT(tmp533,181,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp534;
  modelica_metatype tmpMeta535;
  static int tmp536 = 0;
  if(!tmp536)
  {
    tmp531 = GreaterEq((data->simulationInfo->integerParameter[25] /* controllerTypeDam PARAM */),1);
    tmp532 = LessEq((data->simulationInfo->integerParameter[25] /* controllerTypeDam PARAM */),4);
    if(!(tmp531 && tmp532))
    {
      tmp534 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[25] /* controllerTypeDam PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta535 = stringAppend(MMC_REFSTRINGLIT(tmp533),tmp534);
      {
        const char* assert_cond = "(controllerTypeDam >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and controllerTypeDam <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",98,3,101,72,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta535));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",98,3,101,72,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta535));
        }
      }
      tmp536 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2527
type: ALGORITHM

  assert(controllerTypeVal >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, "Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: " + String(controllerTypeVal, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2527(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2527};
  modelica_boolean tmp537;
  modelica_boolean tmp538;
  static const MMC_DEFSTRINGLIT(tmp539,181,"Variable violating min/max constraint: Buildings.Controls.OBC.CDL.Types.SimpleController.P <= controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID, has value: ");
  modelica_string tmp540;
  modelica_metatype tmpMeta541;
  static int tmp542 = 0;
  if(!tmp542)
  {
    tmp537 = GreaterEq((data->simulationInfo->integerParameter[26] /* controllerTypeVal PARAM */),1);
    tmp538 = LessEq((data->simulationInfo->integerParameter[26] /* controllerTypeVal PARAM */),4);
    if(!(tmp537 && tmp538))
    {
      tmp540 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[26] /* controllerTypeVal PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta541 = stringAppend(MMC_REFSTRINGLIT(tmp539),tmp540);
      {
        const char* assert_cond = "(controllerTypeVal >= Buildings.Controls.OBC.CDL.Types.SimpleController.P and controllerTypeVal <= Buildings.Controls.OBC.CDL.Types.SimpleController.PID)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",78,3,81,71,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta541));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",78,3,81,71,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta541));
        }
      }
      tmp542 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2528
type: ALGORITHM

  assert(venStd >= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1 and venStd <= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.California_Title_24, "Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1 <= venStd <= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.California_Title_24, has value: " + String(venStd, "d"));
*/
OMC_DISABLE_OPT
static void ReheatControllerFMU_eqFunction_2528(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2528};
  modelica_boolean tmp543;
  modelica_boolean tmp544;
  static const MMC_DEFSTRINGLIT(tmp545,215,"Variable violating min/max constraint: Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1 <= venStd <= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.California_Title_24, has value: ");
  modelica_string tmp546;
  modelica_metatype tmpMeta547;
  static int tmp548 = 0;
  if(!tmp548)
  {
    tmp543 = GreaterEq((data->simulationInfo->integerParameter[56] /* venStd PARAM */),1);
    tmp544 = LessEq((data->simulationInfo->integerParameter[56] /* venStd PARAM */),2);
    if(!(tmp543 && tmp544))
    {
      tmp546 = modelica_integer_to_modelica_string_format((data->simulationInfo->integerParameter[56] /* venStd PARAM */), (modelica_string) mmc_strings_len1[100]);
      tmpMeta547 = stringAppend(MMC_REFSTRINGLIT(tmp545),tmp546);
      {
        const char* assert_cond = "(venStd >= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1 and venStd <= Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.California_Title_24)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",4,3,5,52,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta547));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",4,3,5,52,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta547));
        }
      }
      tmp548 = 1;
    }
  }
  TRACE_POP
}
OMC_DISABLE_OPT
void ReheatControllerFMU_updateBoundParameters_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  ReheatControllerFMU_eqFunction_1730(data, threadData);
  ReheatControllerFMU_eqFunction_1731(data, threadData);
  ReheatControllerFMU_eqFunction_1732(data, threadData);
  ReheatControllerFMU_eqFunction_1735(data, threadData);
  ReheatControllerFMU_eqFunction_1736(data, threadData);
  ReheatControllerFMU_eqFunction_1737(data, threadData);
  ReheatControllerFMU_eqFunction_1738(data, threadData);
  ReheatControllerFMU_eqFunction_1739(data, threadData);
  ReheatControllerFMU_eqFunction_1740(data, threadData);
  ReheatControllerFMU_eqFunction_1741(data, threadData);
  ReheatControllerFMU_eqFunction_1742(data, threadData);
  ReheatControllerFMU_eqFunction_1743(data, threadData);
  ReheatControllerFMU_eqFunction_1744(data, threadData);
  ReheatControllerFMU_eqFunction_1745(data, threadData);
  ReheatControllerFMU_eqFunction_1746(data, threadData);
  ReheatControllerFMU_eqFunction_1747(data, threadData);
  ReheatControllerFMU_eqFunction_1748(data, threadData);
  ReheatControllerFMU_eqFunction_1750(data, threadData);
  ReheatControllerFMU_eqFunction_1751(data, threadData);
  ReheatControllerFMU_eqFunction_1752(data, threadData);
  ReheatControllerFMU_eqFunction_1753(data, threadData);
  ReheatControllerFMU_eqFunction_1755(data, threadData);
  ReheatControllerFMU_eqFunction_1756(data, threadData);
  ReheatControllerFMU_eqFunction_1757(data, threadData);
  ReheatControllerFMU_eqFunction_1758(data, threadData);
  ReheatControllerFMU_eqFunction_1759(data, threadData);
  ReheatControllerFMU_eqFunction_1760(data, threadData);
  ReheatControllerFMU_eqFunction_1761(data, threadData);
  ReheatControllerFMU_eqFunction_1762(data, threadData);
  ReheatControllerFMU_eqFunction_1763(data, threadData);
  ReheatControllerFMU_eqFunction_1764(data, threadData);
  ReheatControllerFMU_eqFunction_1765(data, threadData);
  ReheatControllerFMU_eqFunction_1766(data, threadData);
  ReheatControllerFMU_eqFunction_1767(data, threadData);
  ReheatControllerFMU_eqFunction_1768(data, threadData);
  ReheatControllerFMU_eqFunction_1769(data, threadData);
  ReheatControllerFMU_eqFunction_1770(data, threadData);
  ReheatControllerFMU_eqFunction_1771(data, threadData);
  ReheatControllerFMU_eqFunction_1772(data, threadData);
  ReheatControllerFMU_eqFunction_1773(data, threadData);
  ReheatControllerFMU_eqFunction_1774(data, threadData);
  ReheatControllerFMU_eqFunction_1775(data, threadData);
  ReheatControllerFMU_eqFunction_1776(data, threadData);
  ReheatControllerFMU_eqFunction_1777(data, threadData);
  ReheatControllerFMU_eqFunction_1778(data, threadData);
  ReheatControllerFMU_eqFunction_1779(data, threadData);
  ReheatControllerFMU_eqFunction_1780(data, threadData);
  ReheatControllerFMU_eqFunction_1781(data, threadData);
  ReheatControllerFMU_eqFunction_1782(data, threadData);
  ReheatControllerFMU_eqFunction_1783(data, threadData);
  ReheatControllerFMU_eqFunction_1784(data, threadData);
  ReheatControllerFMU_eqFunction_1785(data, threadData);
  ReheatControllerFMU_eqFunction_1786(data, threadData);
  ReheatControllerFMU_eqFunction_1787(data, threadData);
  ReheatControllerFMU_eqFunction_1788(data, threadData);
  ReheatControllerFMU_eqFunction_1789(data, threadData);
  ReheatControllerFMU_eqFunction_1790(data, threadData);
  ReheatControllerFMU_eqFunction_1791(data, threadData);
  ReheatControllerFMU_eqFunction_1792(data, threadData);
  ReheatControllerFMU_eqFunction_1793(data, threadData);
  ReheatControllerFMU_eqFunction_1795(data, threadData);
  ReheatControllerFMU_eqFunction_1796(data, threadData);
  ReheatControllerFMU_eqFunction_1797(data, threadData);
  ReheatControllerFMU_eqFunction_1798(data, threadData);
  ReheatControllerFMU_eqFunction_1800(data, threadData);
  ReheatControllerFMU_eqFunction_1801(data, threadData);
  ReheatControllerFMU_eqFunction_1802(data, threadData);
  ReheatControllerFMU_eqFunction_1803(data, threadData);
  ReheatControllerFMU_eqFunction_1804(data, threadData);
  ReheatControllerFMU_eqFunction_1805(data, threadData);
  ReheatControllerFMU_eqFunction_1806(data, threadData);
  ReheatControllerFMU_eqFunction_1807(data, threadData);
  ReheatControllerFMU_eqFunction_1808(data, threadData);
  ReheatControllerFMU_eqFunction_1809(data, threadData);
  ReheatControllerFMU_eqFunction_1810(data, threadData);
  ReheatControllerFMU_eqFunction_1811(data, threadData);
  ReheatControllerFMU_eqFunction_1812(data, threadData);
  ReheatControllerFMU_eqFunction_1813(data, threadData);
  ReheatControllerFMU_eqFunction_1814(data, threadData);
  ReheatControllerFMU_eqFunction_1815(data, threadData);
  ReheatControllerFMU_eqFunction_1823(data, threadData);
  ReheatControllerFMU_eqFunction_1828(data, threadData);
  ReheatControllerFMU_eqFunction_1836(data, threadData);
  ReheatControllerFMU_eqFunction_1837(data, threadData);
  ReheatControllerFMU_eqFunction_1844(data, threadData);
  ReheatControllerFMU_eqFunction_1852(data, threadData);
  ReheatControllerFMU_eqFunction_1854(data, threadData);
  ReheatControllerFMU_eqFunction_1855(data, threadData);
  ReheatControllerFMU_eqFunction_1859(data, threadData);
  ReheatControllerFMU_eqFunction_1866(data, threadData);
  ReheatControllerFMU_eqFunction_1874(data, threadData);
  ReheatControllerFMU_eqFunction_1876(data, threadData);
  ReheatControllerFMU_eqFunction_1877(data, threadData);
  ReheatControllerFMU_eqFunction_1879(data, threadData);
  ReheatControllerFMU_eqFunction_1882(data, threadData);
  ReheatControllerFMU_eqFunction_1883(data, threadData);
  ReheatControllerFMU_eqFunction_1884(data, threadData);
  ReheatControllerFMU_eqFunction_1890(data, threadData);
  ReheatControllerFMU_eqFunction_1891(data, threadData);
  ReheatControllerFMU_eqFunction_1892(data, threadData);
  ReheatControllerFMU_eqFunction_1893(data, threadData);
  ReheatControllerFMU_eqFunction_1894(data, threadData);
  ReheatControllerFMU_eqFunction_1899(data, threadData);
  ReheatControllerFMU_eqFunction_1900(data, threadData);
  ReheatControllerFMU_eqFunction_1905(data, threadData);
  ReheatControllerFMU_eqFunction_1911(data, threadData);
  ReheatControllerFMU_eqFunction_1913(data, threadData);
  ReheatControllerFMU_eqFunction_1914(data, threadData);
  ReheatControllerFMU_eqFunction_1916(data, threadData);
  ReheatControllerFMU_eqFunction_1919(data, threadData);
  ReheatControllerFMU_eqFunction_1920(data, threadData);
  ReheatControllerFMU_eqFunction_1921(data, threadData);
  ReheatControllerFMU_eqFunction_1928(data, threadData);
  ReheatControllerFMU_eqFunction_1929(data, threadData);
  ReheatControllerFMU_eqFunction_1930(data, threadData);
  ReheatControllerFMU_eqFunction_1931(data, threadData);
  ReheatControllerFMU_eqFunction_1932(data, threadData);
  ReheatControllerFMU_eqFunction_1937(data, threadData);
  ReheatControllerFMU_eqFunction_1938(data, threadData);
  ReheatControllerFMU_eqFunction_1949(data, threadData);
  ReheatControllerFMU_eqFunction_1969(data, threadData);
  ReheatControllerFMU_eqFunction_1970(data, threadData);
  ReheatControllerFMU_eqFunction_1971(data, threadData);
  ReheatControllerFMU_eqFunction_1972(data, threadData);
  ReheatControllerFMU_eqFunction_1983(data, threadData);
  ReheatControllerFMU_eqFunction_1984(data, threadData);
  ReheatControllerFMU_eqFunction_1992(data, threadData);
  ReheatControllerFMU_eqFunction_1993(data, threadData);
  ReheatControllerFMU_eqFunction_1995(data, threadData);
  ReheatControllerFMU_eqFunction_2005(data, threadData);
  ReheatControllerFMU_eqFunction_2006(data, threadData);
  ReheatControllerFMU_eqFunction_2018(data, threadData);
  ReheatControllerFMU_eqFunction_2019(data, threadData);
  ReheatControllerFMU_eqFunction_2021(data, threadData);
  ReheatControllerFMU_eqFunction_2022(data, threadData);
  ReheatControllerFMU_eqFunction_2023(data, threadData);
  ReheatControllerFMU_eqFunction_2027(data, threadData);
  ReheatControllerFMU_eqFunction_2033(data, threadData);
  ReheatControllerFMU_eqFunction_2040(data, threadData);
  ReheatControllerFMU_eqFunction_2041(data, threadData);
  ReheatControllerFMU_eqFunction_2045(data, threadData);
  ReheatControllerFMU_eqFunction_2049(data, threadData);
  ReheatControllerFMU_eqFunction_2053(data, threadData);
  ReheatControllerFMU_eqFunction_2055(data, threadData);
  ReheatControllerFMU_eqFunction_2056(data, threadData);
  ReheatControllerFMU_eqFunction_2058(data, threadData);
  ReheatControllerFMU_eqFunction_2061(data, threadData);
  ReheatControllerFMU_eqFunction_2067(data, threadData);
  ReheatControllerFMU_eqFunction_2073(data, threadData);
  ReheatControllerFMU_eqFunction_2075(data, threadData);
  ReheatControllerFMU_eqFunction_2082(data, threadData);
  ReheatControllerFMU_eqFunction_2083(data, threadData);
  ReheatControllerFMU_eqFunction_2086(data, threadData);
  ReheatControllerFMU_eqFunction_2088(data, threadData);
  ReheatControllerFMU_eqFunction_2093(data, threadData);
  ReheatControllerFMU_eqFunction_2094(data, threadData);
  ReheatControllerFMU_eqFunction_2096(data, threadData);
  ReheatControllerFMU_eqFunction_2097(data, threadData);
  ReheatControllerFMU_eqFunction_2101(data, threadData);
  ReheatControllerFMU_eqFunction_2109(data, threadData);
  ReheatControllerFMU_eqFunction_2112(data, threadData);
  ReheatControllerFMU_eqFunction_2117(data, threadData);
  ReheatControllerFMU_eqFunction_2124(data, threadData);
  ReheatControllerFMU_eqFunction_2126(data, threadData);
  ReheatControllerFMU_eqFunction_2137(data, threadData);
  ReheatControllerFMU_eqFunction_2144(data, threadData);
  ReheatControllerFMU_eqFunction_2153(data, threadData);
  ReheatControllerFMU_eqFunction_2154(data, threadData);
  ReheatControllerFMU_eqFunction_2158(data, threadData);
  ReheatControllerFMU_eqFunction_2160(data, threadData);
  ReheatControllerFMU_eqFunction_2165(data, threadData);
  ReheatControllerFMU_eqFunction_2169(data, threadData);
  ReheatControllerFMU_eqFunction_2170(data, threadData);
  ReheatControllerFMU_eqFunction_2171(data, threadData);
  ReheatControllerFMU_eqFunction_2173(data, threadData);
  ReheatControllerFMU_eqFunction_2176(data, threadData);
  ReheatControllerFMU_eqFunction_2177(data, threadData);
  ReheatControllerFMU_eqFunction_2178(data, threadData);
  ReheatControllerFMU_eqFunction_2182(data, threadData);
  ReheatControllerFMU_eqFunction_2183(data, threadData);
  ReheatControllerFMU_eqFunction_2184(data, threadData);
  ReheatControllerFMU_eqFunction_2185(data, threadData);
  ReheatControllerFMU_eqFunction_2186(data, threadData);
  ReheatControllerFMU_eqFunction_2187(data, threadData);
  ReheatControllerFMU_eqFunction_2188(data, threadData);
  ReheatControllerFMU_eqFunction_2193(data, threadData);
  ReheatControllerFMU_eqFunction_2194(data, threadData);
  ReheatControllerFMU_eqFunction_2195(data, threadData);
  ReheatControllerFMU_eqFunction_2197(data, threadData);
  ReheatControllerFMU_eqFunction_2199(data, threadData);
  ReheatControllerFMU_eqFunction_2200(data, threadData);
  ReheatControllerFMU_eqFunction_2205(data, threadData);
  ReheatControllerFMU_eqFunction_2206(data, threadData);
  ReheatControllerFMU_eqFunction_2207(data, threadData);
  ReheatControllerFMU_eqFunction_2208(data, threadData);
  ReheatControllerFMU_eqFunction_2209(data, threadData);
  ReheatControllerFMU_eqFunction_2210(data, threadData);
  ReheatControllerFMU_eqFunction_2211(data, threadData);
  ReheatControllerFMU_eqFunction_2219(data, threadData);
  ReheatControllerFMU_eqFunction_2220(data, threadData);
  ReheatControllerFMU_eqFunction_2221(data, threadData);
  ReheatControllerFMU_eqFunction_2222(data, threadData);
  ReheatControllerFMU_eqFunction_2223(data, threadData);
  ReheatControllerFMU_eqFunction_2227(data, threadData);
  ReheatControllerFMU_eqFunction_2236(data, threadData);
  ReheatControllerFMU_eqFunction_2243(data, threadData);
  ReheatControllerFMU_eqFunction_2244(data, threadData);
  ReheatControllerFMU_eqFunction_2246(data, threadData);
  ReheatControllerFMU_eqFunction_2249(data, threadData);
  ReheatControllerFMU_eqFunction_2250(data, threadData);
  ReheatControllerFMU_eqFunction_2251(data, threadData);
  ReheatControllerFMU_eqFunction_2252(data, threadData);
  ReheatControllerFMU_eqFunction_2254(data, threadData);
  ReheatControllerFMU_eqFunction_2259(data, threadData);
  ReheatControllerFMU_eqFunction_2264(data, threadData);
  ReheatControllerFMU_eqFunction_2265(data, threadData);
  ReheatControllerFMU_eqFunction_2267(data, threadData);
  ReheatControllerFMU_eqFunction_2268(data, threadData);
  ReheatControllerFMU_eqFunction_2270(data, threadData);
  ReheatControllerFMU_eqFunction_2282(data, threadData);
  ReheatControllerFMU_eqFunction_2289(data, threadData);
  ReheatControllerFMU_eqFunction_2296(data, threadData);
  ReheatControllerFMU_eqFunction_2303(data, threadData);
  ReheatControllerFMU_eqFunction_2305(data, threadData);
  ReheatControllerFMU_eqFunction_2306(data, threadData);
  ReheatControllerFMU_eqFunction_2307(data, threadData);
  ReheatControllerFMU_eqFunction_2311(data, threadData);
  ReheatControllerFMU_eqFunction_2313(data, threadData);
  ReheatControllerFMU_eqFunction_2314(data, threadData);
  ReheatControllerFMU_eqFunction_2315(data, threadData);
  ReheatControllerFMU_eqFunction_2319(data, threadData);
  ReheatControllerFMU_eqFunction_2324(data, threadData);
  ReheatControllerFMU_eqFunction_2337(data, threadData);
  ReheatControllerFMU_eqFunction_2339(data, threadData);
  ReheatControllerFMU_eqFunction_2340(data, threadData);
  ReheatControllerFMU_eqFunction_2342(data, threadData);
  ReheatControllerFMU_eqFunction_2344(data, threadData);
  ReheatControllerFMU_eqFunction_2348(data, threadData);
  ReheatControllerFMU_eqFunction_467(data, threadData);
  ReheatControllerFMU_eqFunction_466(data, threadData);
  ReheatControllerFMU_eqFunction_465(data, threadData);
  ReheatControllerFMU_eqFunction_464(data, threadData);
  ReheatControllerFMU_eqFunction_463(data, threadData);
  ReheatControllerFMU_eqFunction_462(data, threadData);
  ReheatControllerFMU_eqFunction_461(data, threadData);
  ReheatControllerFMU_eqFunction_460(data, threadData);
  ReheatControllerFMU_eqFunction_459(data, threadData);
  ReheatControllerFMU_eqFunction_458(data, threadData);
  ReheatControllerFMU_eqFunction_457(data, threadData);
  ReheatControllerFMU_eqFunction_456(data, threadData);
  ReheatControllerFMU_eqFunction_455(data, threadData);
  ReheatControllerFMU_eqFunction_454(data, threadData);
  ReheatControllerFMU_eqFunction_453(data, threadData);
  ReheatControllerFMU_eqFunction_452(data, threadData);
  ReheatControllerFMU_eqFunction_451(data, threadData);
  ReheatControllerFMU_eqFunction_450(data, threadData);
  ReheatControllerFMU_eqFunction_449(data, threadData);
  ReheatControllerFMU_eqFunction_448(data, threadData);
  ReheatControllerFMU_eqFunction_447(data, threadData);
  ReheatControllerFMU_eqFunction_446(data, threadData);
  ReheatControllerFMU_eqFunction_445(data, threadData);
  ReheatControllerFMU_eqFunction_444(data, threadData);
  ReheatControllerFMU_eqFunction_443(data, threadData);
  ReheatControllerFMU_eqFunction_442(data, threadData);
  ReheatControllerFMU_eqFunction_441(data, threadData);
  ReheatControllerFMU_eqFunction_440(data, threadData);
  ReheatControllerFMU_eqFunction_439(data, threadData);
  ReheatControllerFMU_eqFunction_438(data, threadData);
  ReheatControllerFMU_eqFunction_437(data, threadData);
  ReheatControllerFMU_eqFunction_436(data, threadData);
  ReheatControllerFMU_eqFunction_435(data, threadData);
  ReheatControllerFMU_eqFunction_434(data, threadData);
  ReheatControllerFMU_eqFunction_433(data, threadData);
  ReheatControllerFMU_eqFunction_432(data, threadData);
  ReheatControllerFMU_eqFunction_431(data, threadData);
  ReheatControllerFMU_eqFunction_430(data, threadData);
  ReheatControllerFMU_eqFunction_429(data, threadData);
  ReheatControllerFMU_eqFunction_428(data, threadData);
  ReheatControllerFMU_eqFunction_427(data, threadData);
  ReheatControllerFMU_eqFunction_13(data, threadData);
  ReheatControllerFMU_eqFunction_12(data, threadData);
  ReheatControllerFMU_eqFunction_10(data, threadData);
  ReheatControllerFMU_eqFunction_8(data, threadData);
  ReheatControllerFMU_eqFunction_5(data, threadData);
  ReheatControllerFMU_eqFunction_4(data, threadData);
  ReheatControllerFMU_eqFunction_3(data, threadData);
  ReheatControllerFMU_eqFunction_6(data, threadData);
  ReheatControllerFMU_eqFunction_7(data, threadData);
  ReheatControllerFMU_eqFunction_426(data, threadData);
  ReheatControllerFMU_eqFunction_9(data, threadData);
  ReheatControllerFMU_eqFunction_11(data, threadData);
  ReheatControllerFMU_eqFunction_14(data, threadData);
  ReheatControllerFMU_eqFunction_2(data, threadData);
  ReheatControllerFMU_eqFunction_1(data, threadData);
  ReheatControllerFMU_eqFunction_2422(data, threadData);
  ReheatControllerFMU_eqFunction_2423(data, threadData);
  ReheatControllerFMU_eqFunction_2424(data, threadData);
  ReheatControllerFMU_eqFunction_2425(data, threadData);
  ReheatControllerFMU_eqFunction_2426(data, threadData);
  ReheatControllerFMU_eqFunction_2427(data, threadData);
  ReheatControllerFMU_eqFunction_2428(data, threadData);
  ReheatControllerFMU_eqFunction_2429(data, threadData);
  ReheatControllerFMU_eqFunction_2430(data, threadData);
  ReheatControllerFMU_eqFunction_2431(data, threadData);
  ReheatControllerFMU_eqFunction_2432(data, threadData);
  ReheatControllerFMU_eqFunction_2433(data, threadData);
  ReheatControllerFMU_eqFunction_2434(data, threadData);
  ReheatControllerFMU_eqFunction_2435(data, threadData);
  ReheatControllerFMU_eqFunction_2436(data, threadData);
  ReheatControllerFMU_eqFunction_2437(data, threadData);
  ReheatControllerFMU_eqFunction_2438(data, threadData);
  ReheatControllerFMU_eqFunction_2439(data, threadData);
  ReheatControllerFMU_eqFunction_2440(data, threadData);
  ReheatControllerFMU_eqFunction_2441(data, threadData);
  ReheatControllerFMU_eqFunction_2442(data, threadData);
  ReheatControllerFMU_eqFunction_2443(data, threadData);
  ReheatControllerFMU_eqFunction_2444(data, threadData);
  ReheatControllerFMU_eqFunction_2445(data, threadData);
  ReheatControllerFMU_eqFunction_2446(data, threadData);
  ReheatControllerFMU_eqFunction_2447(data, threadData);
  ReheatControllerFMU_eqFunction_2448(data, threadData);
  ReheatControllerFMU_eqFunction_2449(data, threadData);
  ReheatControllerFMU_eqFunction_2450(data, threadData);
  ReheatControllerFMU_eqFunction_2451(data, threadData);
  ReheatControllerFMU_eqFunction_2452(data, threadData);
  ReheatControllerFMU_eqFunction_2453(data, threadData);
  ReheatControllerFMU_eqFunction_2454(data, threadData);
  ReheatControllerFMU_eqFunction_2455(data, threadData);
  ReheatControllerFMU_eqFunction_2456(data, threadData);
  ReheatControllerFMU_eqFunction_2457(data, threadData);
  ReheatControllerFMU_eqFunction_2458(data, threadData);
  ReheatControllerFMU_eqFunction_2459(data, threadData);
  ReheatControllerFMU_eqFunction_2460(data, threadData);
  ReheatControllerFMU_eqFunction_2461(data, threadData);
  ReheatControllerFMU_eqFunction_2462(data, threadData);
  ReheatControllerFMU_eqFunction_2463(data, threadData);
  ReheatControllerFMU_eqFunction_2464(data, threadData);
  ReheatControllerFMU_eqFunction_2465(data, threadData);
  ReheatControllerFMU_eqFunction_2466(data, threadData);
  ReheatControllerFMU_eqFunction_2467(data, threadData);
  ReheatControllerFMU_eqFunction_2468(data, threadData);
  ReheatControllerFMU_eqFunction_2469(data, threadData);
  ReheatControllerFMU_eqFunction_2470(data, threadData);
  ReheatControllerFMU_eqFunction_2471(data, threadData);
  ReheatControllerFMU_eqFunction_2472(data, threadData);
  ReheatControllerFMU_eqFunction_2473(data, threadData);
  ReheatControllerFMU_eqFunction_2474(data, threadData);
  ReheatControllerFMU_eqFunction_2475(data, threadData);
  ReheatControllerFMU_eqFunction_2476(data, threadData);
  ReheatControllerFMU_eqFunction_2477(data, threadData);
  ReheatControllerFMU_eqFunction_2478(data, threadData);
  ReheatControllerFMU_eqFunction_2479(data, threadData);
  ReheatControllerFMU_eqFunction_2480(data, threadData);
  ReheatControllerFMU_eqFunction_2481(data, threadData);
  ReheatControllerFMU_eqFunction_2482(data, threadData);
  ReheatControllerFMU_eqFunction_2483(data, threadData);
  ReheatControllerFMU_eqFunction_2484(data, threadData);
  ReheatControllerFMU_eqFunction_2485(data, threadData);
  ReheatControllerFMU_eqFunction_2486(data, threadData);
  ReheatControllerFMU_eqFunction_2487(data, threadData);
  ReheatControllerFMU_eqFunction_2488(data, threadData);
  ReheatControllerFMU_eqFunction_2489(data, threadData);
  ReheatControllerFMU_eqFunction_2490(data, threadData);
  ReheatControllerFMU_eqFunction_2491(data, threadData);
  ReheatControllerFMU_eqFunction_2492(data, threadData);
  ReheatControllerFMU_eqFunction_2493(data, threadData);
  ReheatControllerFMU_eqFunction_2494(data, threadData);
  ReheatControllerFMU_eqFunction_2495(data, threadData);
  ReheatControllerFMU_eqFunction_2496(data, threadData);
  ReheatControllerFMU_eqFunction_2497(data, threadData);
  ReheatControllerFMU_eqFunction_2498(data, threadData);
  ReheatControllerFMU_eqFunction_2499(data, threadData);
  ReheatControllerFMU_eqFunction_2500(data, threadData);
  ReheatControllerFMU_eqFunction_2501(data, threadData);
  ReheatControllerFMU_eqFunction_2502(data, threadData);
  ReheatControllerFMU_eqFunction_2503(data, threadData);
  ReheatControllerFMU_eqFunction_2504(data, threadData);
  ReheatControllerFMU_eqFunction_2505(data, threadData);
  ReheatControllerFMU_eqFunction_2506(data, threadData);
  ReheatControllerFMU_eqFunction_2507(data, threadData);
  ReheatControllerFMU_eqFunction_2508(data, threadData);
  ReheatControllerFMU_eqFunction_2509(data, threadData);
  ReheatControllerFMU_eqFunction_2510(data, threadData);
  ReheatControllerFMU_eqFunction_2511(data, threadData);
  ReheatControllerFMU_eqFunction_2512(data, threadData);
  ReheatControllerFMU_eqFunction_2513(data, threadData);
  ReheatControllerFMU_eqFunction_2514(data, threadData);
  ReheatControllerFMU_eqFunction_2515(data, threadData);
  ReheatControllerFMU_eqFunction_2516(data, threadData);
  ReheatControllerFMU_eqFunction_2517(data, threadData);
  ReheatControllerFMU_eqFunction_2518(data, threadData);
  ReheatControllerFMU_eqFunction_2519(data, threadData);
  ReheatControllerFMU_eqFunction_2520(data, threadData);
  ReheatControllerFMU_eqFunction_2521(data, threadData);
  ReheatControllerFMU_eqFunction_2522(data, threadData);
  ReheatControllerFMU_eqFunction_2523(data, threadData);
  ReheatControllerFMU_eqFunction_2524(data, threadData);
  ReheatControllerFMU_eqFunction_2525(data, threadData);
  ReheatControllerFMU_eqFunction_2526(data, threadData);
  ReheatControllerFMU_eqFunction_2527(data, threadData);
  ReheatControllerFMU_eqFunction_2528(data, threadData);
  TRACE_POP
}
OMC_DISABLE_OPT
int ReheatControllerFMU_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  (data->simulationInfo->integerParameter[0] /* actAirSet.cooDowMod.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[0].time_unvarying = 1;
  (data->simulationInfo->integerParameter[1] /* actAirSet.occMod.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[1].time_unvarying = 1;
  (data->simulationInfo->integerParameter[2] /* actAirSet.setBacMod.k PARAM */) = ((modelica_integer) 5);
  data->modelData->integerParameterData[2].time_unvarying = 1;
  (data->simulationInfo->integerParameter[3] /* actAirSet.setUpMod.k PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[3].time_unvarying = 1;
  (data->simulationInfo->integerParameter[4] /* actAirSet.warUpMod.k PARAM */) = ((modelica_integer) 4);
  data->modelData->integerParameterData[4].time_unvarying = 1;
  (data->simulationInfo->integerParameter[5] /* ala.booToInt.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[5].time_unvarying = 1;
  (data->simulationInfo->integerParameter[6] /* ala.booToInt.integerTrue PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[6].time_unvarying = 1;
  (data->simulationInfo->integerParameter[7] /* ala.booToInt1.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[7].time_unvarying = 1;
  (data->simulationInfo->integerParameter[8] /* ala.booToInt1.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[8].time_unvarying = 1;
  (data->simulationInfo->integerParameter[9] /* ala.booToInt2.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[9].time_unvarying = 1;
  (data->simulationInfo->integerParameter[10] /* ala.booToInt2.integerTrue PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[10].time_unvarying = 1;
  (data->simulationInfo->integerParameter[11] /* ala.booToInt3.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[11].time_unvarying = 1;
  (data->simulationInfo->integerParameter[12] /* ala.booToInt3.integerTrue PARAM */) = ((modelica_integer) 4);
  data->modelData->integerParameterData[12].time_unvarying = 1;
  (data->simulationInfo->integerParameter[13] /* ala.booToInt4.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[13].time_unvarying = 1;
  (data->simulationInfo->integerParameter[14] /* ala.booToInt4.integerTrue PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[14].time_unvarying = 1;
  (data->simulationInfo->integerParameter[15] /* ala.booToInt5.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[15].time_unvarying = 1;
  (data->simulationInfo->integerParameter[16] /* ala.booToInt5.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[16].time_unvarying = 1;
  (data->simulationInfo->integerParameter[17] /* ala.booToInt6.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[17].time_unvarying = 1;
  (data->simulationInfo->integerParameter[18] /* ala.booToInt6.integerTrue PARAM */) = ((modelica_integer) 4);
  data->modelData->integerParameterData[18].time_unvarying = 1;
  (data->simulationInfo->integerParameter[19] /* ala.conInt.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[19].time_unvarying = 1;
  (data->simulationInfo->integerParameter[20] /* ala.conInt2.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[20].time_unvarying = 1;
  (data->simulationInfo->integerParameter[22] /* ala.occMod.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[22].time_unvarying = 1;
  (data->simulationInfo->integerParameter[28] /* damVal.conInt.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[28].time_unvarying = 1;
  (data->simulationInfo->integerParameter[29] /* damVal.conInt1.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[29].time_unvarying = 1;
  (data->simulationInfo->integerParameter[30] /* damVal.conInt2.k PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[30].time_unvarying = 1;
  (data->simulationInfo->integerParameter[31] /* damVal.conInt5.k PARAM */) = ((modelica_integer) 4);
  data->modelData->integerParameterData[31].time_unvarying = 1;
  (data->simulationInfo->integerParameter[35] /* damVal.occMod.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[35].time_unvarying = 1;
  (data->simulationInfo->integerParameter[36] /* damVal.unOcc.k PARAM */) = ((modelica_integer) 7);
  data->modelData->integerParameterData[36].time_unvarying = 1;
  (data->simulationInfo->integerParameter[38] /* setOve.conInt3.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[38].time_unvarying = 1;
  (data->simulationInfo->integerParameter[39] /* setOve.conInt4.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[39].time_unvarying = 1;
  (data->simulationInfo->integerParameter[40] /* setPoi.occMod.k PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[40].time_unvarying = 1;
  (data->simulationInfo->integerParameter[41] /* sysReq.booToInt.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[41].time_unvarying = 1;
  (data->simulationInfo->integerParameter[42] /* sysReq.booToInt.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[42].time_unvarying = 1;
  (data->simulationInfo->integerParameter[43] /* sysReq.booToInt1.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[43].time_unvarying = 1;
  (data->simulationInfo->integerParameter[44] /* sysReq.booToInt1.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[44].time_unvarying = 1;
  (data->simulationInfo->integerParameter[45] /* sysReq.booToInt2.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[45].time_unvarying = 1;
  (data->simulationInfo->integerParameter[46] /* sysReq.booToInt2.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[46].time_unvarying = 1;
  (data->simulationInfo->integerParameter[47] /* sysReq.booToInt3.integerFalse PARAM */) = ((modelica_integer) 0);
  data->modelData->integerParameterData[47].time_unvarying = 1;
  (data->simulationInfo->integerParameter[48] /* sysReq.booToInt3.integerTrue PARAM */) = ((modelica_integer) 1);
  data->modelData->integerParameterData[48].time_unvarying = 1;
  (data->simulationInfo->integerParameter[50] /* sysReq.thrCooResReq.k PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[50].time_unvarying = 1;
  (data->simulationInfo->integerParameter[51] /* sysReq.thrHeaResReq.k PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[51].time_unvarying = 1;
  (data->simulationInfo->integerParameter[52] /* sysReq.thrPreResReq.k PARAM */) = ((modelica_integer) 3);
  data->modelData->integerParameterData[52].time_unvarying = 1;
  (data->simulationInfo->integerParameter[53] /* sysReq.twoCooResReq.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[53].time_unvarying = 1;
  (data->simulationInfo->integerParameter[54] /* sysReq.twoHeaResReq.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[54].time_unvarying = 1;
  (data->simulationInfo->integerParameter[55] /* sysReq.twoPreResReq.k PARAM */) = ((modelica_integer) 2);
  data->modelData->integerParameterData[55].time_unvarying = 1;
  (data->simulationInfo->realParameter[12] /* VMin_flow PARAM */) = 0.5;
  data->modelData->realParameterData[12].time_unvarying = 1;
  (data->simulationInfo->realParameter[18] /* actAirSet.actCooMax.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[18].time_unvarying = 1;
  (data->simulationInfo->realParameter[20] /* actAirSet.cooMaxFlo.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[20].time_unvarying = 1;
  (data->simulationInfo->realParameter[24] /* actAirSet.heaMaxFlo.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[24].time_unvarying = 1;
  (data->simulationInfo->realParameter[26] /* actAirSet.heaMaxFlo1.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[26].time_unvarying = 1;
  (data->simulationInfo->realParameter[30] /* actAirSet.heaMinFlo.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[30].time_unvarying = 1;
  (data->simulationInfo->realParameter[34] /* actAirSet.occModInd.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[34].time_unvarying = 1;
  (data->simulationInfo->realParameter[35] /* actAirSet.occModInd.realTrue PARAM */) = 1.0;
  data->modelData->realParameterData[35].time_unvarying = 1;
  (data->simulationInfo->realParameter[37] /* ala.addPar.p PARAM */) = -17.0;
  data->modelData->realParameterData[37].time_unvarying = 1;
  (data->simulationInfo->realParameter[38] /* ala.addPar1.p PARAM */) = -8.0;
  data->modelData->realParameterData[38].time_unvarying = 1;
  (data->simulationInfo->realParameter[39] /* ala.addPar2.p PARAM */) = 3.0;
  data->modelData->realParameterData[39].time_unvarying = 1;
  (data->simulationInfo->realParameter[40] /* ala.cloDam.h PARAM */) = 0.0025;
  data->modelData->realParameterData[40].time_unvarying = 1;
  (data->simulationInfo->realParameter[41] /* ala.cloDam.lesHys.h PARAM */) = 0.0025;
  data->modelData->realParameterData[41].time_unvarying = 1;
  (data->simulationInfo->realParameter[42] /* ala.cloDam.lesHys.t PARAM */) = 0.005;
  data->modelData->realParameterData[42].time_unvarying = 1;
  (data->simulationInfo->realParameter[43] /* ala.cloDam.t PARAM */) = 0.005;
  data->modelData->realParameterData[43].time_unvarying = 1;
  (data->simulationInfo->realParameter[44] /* ala.cloVal.h PARAM */) = 0.0025;
  data->modelData->realParameterData[44].time_unvarying = 1;
  (data->simulationInfo->realParameter[45] /* ala.cloVal.lesHys.h PARAM */) = 0.0025;
  data->modelData->realParameterData[45].time_unvarying = 1;
  (data->simulationInfo->realParameter[46] /* ala.cloVal.lesHys.t PARAM */) = 0.005;
  data->modelData->realParameterData[46].time_unvarying = 1;
  (data->simulationInfo->realParameter[47] /* ala.cloVal.t PARAM */) = 0.005;
  data->modelData->realParameterData[47].time_unvarying = 1;
  (data->simulationInfo->realParameter[54] /* ala.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[54].time_unvarying = 1;
  (data->simulationInfo->realParameter[55] /* ala.damPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[55].time_unvarying = 1;
  (data->simulationInfo->realParameter[59] /* ala.floHys PARAM */) = 0.005;
  data->modelData->realParameterData[59].time_unvarying = 1;
  (data->simulationInfo->realParameter[60] /* ala.gai.k PARAM */) = 0.5;
  data->modelData->realParameterData[60].time_unvarying = 1;
  (data->simulationInfo->realParameter[61] /* ala.gai1.k PARAM */) = 0.7;
  data->modelData->realParameterData[61].time_unvarying = 1;
  (data->simulationInfo->realParameter[62] /* ala.gai2.k PARAM */) = 0.1;
  data->modelData->realParameterData[62].time_unvarying = 1;
  (data->simulationInfo->realParameter[64] /* ala.gre.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[64].time_unvarying = 1;
  (data->simulationInfo->realParameter[65] /* ala.gre.h PARAM */) = 0.005;
  data->modelData->realParameterData[65].time_unvarying = 1;
  (data->simulationInfo->realParameter[66] /* ala.gre1.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[66].time_unvarying = 1;
  (data->simulationInfo->realParameter[67] /* ala.gre1.h PARAM */) = 0.005;
  data->modelData->realParameterData[67].time_unvarying = 1;
  (data->simulationInfo->realParameter[68] /* ala.gre2.greHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[68].time_unvarying = 1;
  (data->simulationInfo->realParameter[69] /* ala.gre2.h PARAM */) = 0.25;
  data->modelData->realParameterData[69].time_unvarying = 1;
  (data->simulationInfo->realParameter[70] /* ala.greThr.greHys.h PARAM */) = 0.0025;
  data->modelData->realParameterData[70].time_unvarying = 1;
  (data->simulationInfo->realParameter[71] /* ala.greThr.greHys.t PARAM */) = 0.005;
  data->modelData->realParameterData[71].time_unvarying = 1;
  (data->simulationInfo->realParameter[72] /* ala.greThr.h PARAM */) = 0.0025;
  data->modelData->realParameterData[72].time_unvarying = 1;
  (data->simulationInfo->realParameter[73] /* ala.greThr.t PARAM */) = 0.005;
  data->modelData->realParameterData[73].time_unvarying = 1;
  (data->simulationInfo->realParameter[76] /* ala.greThr1.h PARAM */) = 0.0;
  data->modelData->realParameterData[76].time_unvarying = 1;
  (data->simulationInfo->realParameter[77] /* ala.greThr1.t PARAM */) = 0.0;
  data->modelData->realParameterData[77].time_unvarying = 1;
  (data->simulationInfo->realParameter[81] /* ala.greThr2.h PARAM */) = 0.0;
  data->modelData->realParameterData[81].time_unvarying = 1;
  (data->simulationInfo->realParameter[82] /* ala.greThr2.t PARAM */) = 0.0;
  data->modelData->realParameterData[82].time_unvarying = 1;
  (data->simulationInfo->realParameter[86] /* ala.les.h PARAM */) = 0.005;
  data->modelData->realParameterData[86].time_unvarying = 1;
  (data->simulationInfo->realParameter[87] /* ala.les.lesHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[87].time_unvarying = 1;
  (data->simulationInfo->realParameter[88] /* ala.les1.h PARAM */) = 0.25;
  data->modelData->realParameterData[88].time_unvarying = 1;
  (data->simulationInfo->realParameter[89] /* ala.les1.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[89].time_unvarying = 1;
  (data->simulationInfo->realParameter[90] /* ala.les2.h PARAM */) = 0.25;
  data->modelData->realParameterData[90].time_unvarying = 1;
  (data->simulationInfo->realParameter[91] /* ala.les2.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[91].time_unvarying = 1;
  (data->simulationInfo->realParameter[113] /* ala.valPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[113].time_unvarying = 1;
  (data->simulationInfo->realParameter[117] /* conLoo.conCoo.Dzero.k PARAM */) = 0.0;
  data->modelData->realParameterData[117].time_unvarying = 1;
  (data->simulationInfo->realParameter[120] /* conLoo.conCoo.Nd PARAM */) = 10.0;
  data->modelData->realParameterData[120].time_unvarying = 1;
  (data->simulationInfo->realParameter[121] /* conLoo.conCoo.Ni PARAM */) = 0.9;
  data->modelData->realParameterData[121].time_unvarying = 1;
  (data->simulationInfo->realParameter[123] /* conLoo.conCoo.Td PARAM */) = 0.1;
  data->modelData->realParameterData[123].time_unvarying = 1;
  (data->simulationInfo->realParameter[130] /* conLoo.conCoo.r PARAM */) = 1.0;
  data->modelData->realParameterData[130].time_unvarying = 1;
  (data->simulationInfo->realParameter[131] /* conLoo.conCoo.revAct PARAM */) = -1.0;
  data->modelData->realParameterData[131].time_unvarying = 1;
  (data->simulationInfo->realParameter[134] /* conLoo.conCoo.xi_start PARAM */) = 0.0;
  data->modelData->realParameterData[134].time_unvarying = 1;
  (data->simulationInfo->realParameter[135] /* conLoo.conCoo.yMax PARAM */) = 1.0;
  data->modelData->realParameterData[135].time_unvarying = 1;
  (data->simulationInfo->realParameter[136] /* conLoo.conCoo.yMin PARAM */) = 0.0;
  data->modelData->realParameterData[136].time_unvarying = 1;
  (data->simulationInfo->realParameter[140] /* conLoo.conCoo.yd_start PARAM */) = 0.0;
  data->modelData->realParameterData[140].time_unvarying = 1;
  (data->simulationInfo->realParameter[141] /* conLoo.conHea.Dzero.k PARAM */) = 0.0;
  data->modelData->realParameterData[141].time_unvarying = 1;
  (data->simulationInfo->realParameter[144] /* conLoo.conHea.Nd PARAM */) = 10.0;
  data->modelData->realParameterData[144].time_unvarying = 1;
  (data->simulationInfo->realParameter[145] /* conLoo.conHea.Ni PARAM */) = 0.9;
  data->modelData->realParameterData[145].time_unvarying = 1;
  (data->simulationInfo->realParameter[147] /* conLoo.conHea.Td PARAM */) = 0.1;
  data->modelData->realParameterData[147].time_unvarying = 1;
  (data->simulationInfo->realParameter[154] /* conLoo.conHea.r PARAM */) = 1.0;
  data->modelData->realParameterData[154].time_unvarying = 1;
  (data->simulationInfo->realParameter[158] /* conLoo.conHea.xi_start PARAM */) = 0.0;
  data->modelData->realParameterData[158].time_unvarying = 1;
  (data->simulationInfo->realParameter[159] /* conLoo.conHea.yMax PARAM */) = 1.0;
  data->modelData->realParameterData[159].time_unvarying = 1;
  (data->simulationInfo->realParameter[160] /* conLoo.conHea.yMin PARAM */) = 0.0;
  data->modelData->realParameterData[160].time_unvarying = 1;
  (data->simulationInfo->realParameter[164] /* conLoo.conHea.yd_start PARAM */) = 0.0;
  data->modelData->realParameterData[164].time_unvarying = 1;
  (data->simulationInfo->realParameter[165] /* conLoo.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[165].time_unvarying = 1;
  (data->simulationInfo->realParameter[170] /* conLoo.enaCooLoo.h PARAM */) = 0.25;
  data->modelData->realParameterData[170].time_unvarying = 1;
  (data->simulationInfo->realParameter[171] /* conLoo.enaCooLoo.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[171].time_unvarying = 1;
  (data->simulationInfo->realParameter[172] /* conLoo.enaHeaLoo.h PARAM */) = 0.25;
  data->modelData->realParameterData[172].time_unvarying = 1;
  (data->simulationInfo->realParameter[173] /* conLoo.enaHeaLoo.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[173].time_unvarying = 1;
  (data->simulationInfo->realParameter[176] /* conLoo.looHys PARAM */) = 0.01;
  data->modelData->realParameterData[176].time_unvarying = 1;
  (data->simulationInfo->realParameter[178] /* conLoo.zerCon.h PARAM */) = 0.008;
  data->modelData->realParameterData[178].time_unvarying = 1;
  (data->simulationInfo->realParameter[179] /* conLoo.zerCon.lesHys.h PARAM */) = 0.008;
  data->modelData->realParameterData[179].time_unvarying = 1;
  (data->simulationInfo->realParameter[180] /* conLoo.zerCon.lesHys.t PARAM */) = 0.01;
  data->modelData->realParameterData[180].time_unvarying = 1;
  (data->simulationInfo->realParameter[181] /* conLoo.zerCon.t PARAM */) = 0.01;
  data->modelData->realParameterData[181].time_unvarying = 1;
  (data->simulationInfo->realParameter[182] /* conLoo.zerCon1.h PARAM */) = 0.008;
  data->modelData->realParameterData[182].time_unvarying = 1;
  (data->simulationInfo->realParameter[183] /* conLoo.zerCon1.lesHys.h PARAM */) = 0.008;
  data->modelData->realParameterData[183].time_unvarying = 1;
  (data->simulationInfo->realParameter[184] /* conLoo.zerCon1.lesHys.t PARAM */) = 0.01;
  data->modelData->realParameterData[184].time_unvarying = 1;
  (data->simulationInfo->realParameter[185] /* conLoo.zerCon1.t PARAM */) = 0.01;
  data->modelData->realParameterData[185].time_unvarying = 1;
  (data->simulationInfo->realParameter[186] /* conLoo.zerCoo.realFalse PARAM */) = 1.0;
  data->modelData->realParameterData[186].time_unvarying = 1;
  (data->simulationInfo->realParameter[187] /* conLoo.zerCoo.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[187].time_unvarying = 1;
  (data->simulationInfo->realParameter[188] /* conLoo.zerHea.realFalse PARAM */) = 1.0;
  data->modelData->realParameterData[188].time_unvarying = 1;
  (data->simulationInfo->realParameter[189] /* conLoo.zerHea.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[189].time_unvarying = 1;
  (data->simulationInfo->realParameter[191] /* dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[191].time_unvarying = 1;
  (data->simulationInfo->realParameter[192] /* damPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[192].time_unvarying = 1;
  (data->simulationInfo->realParameter[200] /* damVal.VMin_flow PARAM */) = 0.5;
  data->modelData->realParameterData[200].time_unvarying = 1;
  (data->simulationInfo->realParameter[202] /* damVal.addPar1.p PARAM */) = 3.0;
  data->modelData->realParameterData[202].time_unvarying = 1;
  (data->simulationInfo->realParameter[203] /* damVal.conDam.Dzero.k PARAM */) = 0.0;
  data->modelData->realParameterData[203].time_unvarying = 1;
  (data->simulationInfo->realParameter[206] /* damVal.conDam.Nd PARAM */) = 10.0;
  data->modelData->realParameterData[206].time_unvarying = 1;
  (data->simulationInfo->realParameter[207] /* damVal.conDam.Ni PARAM */) = 0.9;
  data->modelData->realParameterData[207].time_unvarying = 1;
  (data->simulationInfo->realParameter[214] /* damVal.conDam.lim.uMax PARAM */) = 1.0;
  data->modelData->realParameterData[214].time_unvarying = 1;
  (data->simulationInfo->realParameter[215] /* damVal.conDam.lim.uMin PARAM */) = 0.0;
  data->modelData->realParameterData[215].time_unvarying = 1;
  (data->simulationInfo->realParameter[216] /* damVal.conDam.r PARAM */) = 1.0;
  data->modelData->realParameterData[216].time_unvarying = 1;
  (data->simulationInfo->realParameter[220] /* damVal.conDam.xi_start PARAM */) = 0.0;
  data->modelData->realParameterData[220].time_unvarying = 1;
  (data->simulationInfo->realParameter[221] /* damVal.conDam.yMax PARAM */) = 1.0;
  data->modelData->realParameterData[221].time_unvarying = 1;
  (data->simulationInfo->realParameter[222] /* damVal.conDam.yMin PARAM */) = 0.0;
  data->modelData->realParameterData[222].time_unvarying = 1;
  (data->simulationInfo->realParameter[226] /* damVal.conDam.yd_start PARAM */) = 0.0;
  data->modelData->realParameterData[226].time_unvarying = 1;
  (data->simulationInfo->realParameter[227] /* damVal.conHal.k PARAM */) = 0.5;
  data->modelData->realParameterData[227].time_unvarying = 1;
  (data->simulationInfo->realParameter[228] /* damVal.conHal1.k PARAM */) = 0.5;
  data->modelData->realParameterData[228].time_unvarying = 1;
  (data->simulationInfo->realParameter[229] /* damVal.conOne.k PARAM */) = 1.0;
  data->modelData->realParameterData[229].time_unvarying = 1;
  (data->simulationInfo->realParameter[230] /* damVal.conOne2.k PARAM */) = 1.0;
  data->modelData->realParameterData[230].time_unvarying = 1;
  (data->simulationInfo->realParameter[231] /* damVal.conVal.Dzero.k PARAM */) = 0.0;
  data->modelData->realParameterData[231].time_unvarying = 1;
  (data->simulationInfo->realParameter[234] /* damVal.conVal.Nd PARAM */) = 10.0;
  data->modelData->realParameterData[234].time_unvarying = 1;
  (data->simulationInfo->realParameter[235] /* damVal.conVal.Ni PARAM */) = 0.9;
  data->modelData->realParameterData[235].time_unvarying = 1;
  (data->simulationInfo->realParameter[242] /* damVal.conVal.lim.uMax PARAM */) = 1.0;
  data->modelData->realParameterData[242].time_unvarying = 1;
  (data->simulationInfo->realParameter[243] /* damVal.conVal.lim.uMin PARAM */) = 0.0;
  data->modelData->realParameterData[243].time_unvarying = 1;
  (data->simulationInfo->realParameter[244] /* damVal.conVal.r PARAM */) = 1.0;
  data->modelData->realParameterData[244].time_unvarying = 1;
  (data->simulationInfo->realParameter[248] /* damVal.conVal.xi_start PARAM */) = 0.0;
  data->modelData->realParameterData[248].time_unvarying = 1;
  (data->simulationInfo->realParameter[249] /* damVal.conVal.yMax PARAM */) = 1.0;
  data->modelData->realParameterData[249].time_unvarying = 1;
  (data->simulationInfo->realParameter[250] /* damVal.conVal.yMin PARAM */) = 0.0;
  data->modelData->realParameterData[250].time_unvarying = 1;
  (data->simulationInfo->realParameter[254] /* damVal.conVal.yd_start PARAM */) = 0.0;
  data->modelData->realParameterData[254].time_unvarying = 1;
  (data->simulationInfo->realParameter[255] /* damVal.conZer.k PARAM */) = 0.0;
  data->modelData->realParameterData[255].time_unvarying = 1;
  (data->simulationInfo->realParameter[256] /* damVal.conZer2.k PARAM */) = 0.0;
  data->modelData->realParameterData[256].time_unvarying = 1;
  (data->simulationInfo->realParameter[257] /* damVal.conZer3.k PARAM */) = 0.0;
  data->modelData->realParameterData[257].time_unvarying = 1;
  (data->simulationInfo->realParameter[258] /* damVal.cooMax.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[258].time_unvarying = 1;
  (data->simulationInfo->realParameter[263] /* damVal.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[263].time_unvarying = 1;
  (data->simulationInfo->realParameter[264] /* damVal.gre.greHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[264].time_unvarying = 1;
  (data->simulationInfo->realParameter[265] /* damVal.gre.h PARAM */) = 0.25;
  data->modelData->realParameterData[265].time_unvarying = 1;
  (data->simulationInfo->realParameter[266] /* damVal.greThr.greHys.h PARAM */) = 0.125;
  data->modelData->realParameterData[266].time_unvarying = 1;
  (data->simulationInfo->realParameter[267] /* damVal.greThr.greHys.t PARAM */) = 0.25;
  data->modelData->realParameterData[267].time_unvarying = 1;
  (data->simulationInfo->realParameter[268] /* damVal.greThr.h PARAM */) = 0.125;
  data->modelData->realParameterData[268].time_unvarying = 1;
  (data->simulationInfo->realParameter[269] /* damVal.greThr.t PARAM */) = 0.25;
  data->modelData->realParameterData[269].time_unvarying = 1;
  (data->simulationInfo->realParameter[270] /* damVal.greThr1.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[270].time_unvarying = 1;
  (data->simulationInfo->realParameter[271] /* damVal.greThr1.greHys.t PARAM */) = 0.01;
  data->modelData->realParameterData[271].time_unvarying = 1;
  (data->simulationInfo->realParameter[272] /* damVal.greThr1.h PARAM */) = 0.005;
  data->modelData->realParameterData[272].time_unvarying = 1;
  (data->simulationInfo->realParameter[273] /* damVal.greThr1.t PARAM */) = 0.01;
  data->modelData->realParameterData[273].time_unvarying = 1;
  (data->simulationInfo->realParameter[274] /* damVal.greThr2.greHys.h PARAM */) = 0.008;
  data->modelData->realParameterData[274].time_unvarying = 1;
  (data->simulationInfo->realParameter[275] /* damVal.greThr2.greHys.t PARAM */) = 0.01;
  data->modelData->realParameterData[275].time_unvarying = 1;
  (data->simulationInfo->realParameter[276] /* damVal.greThr2.h PARAM */) = 0.008;
  data->modelData->realParameterData[276].time_unvarying = 1;
  (data->simulationInfo->realParameter[277] /* damVal.greThr2.t PARAM */) = 0.01;
  data->modelData->realParameterData[277].time_unvarying = 1;
  (data->simulationInfo->realParameter[278] /* damVal.heaMax.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[278].time_unvarying = 1;
  (data->simulationInfo->realParameter[282] /* damVal.iniDam PARAM */) = 0.01;
  data->modelData->realParameterData[282].time_unvarying = 1;
  (data->simulationInfo->realParameter[285] /* damVal.looHys PARAM */) = 0.01;
  data->modelData->realParameterData[285].time_unvarying = 1;
  (data->simulationInfo->realParameter[288] /* damVal.lowMin.h PARAM */) = 0.25;
  data->modelData->realParameterData[288].time_unvarying = 1;
  (data->simulationInfo->realParameter[289] /* damVal.lowMin.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[289].time_unvarying = 1;
  (data->simulationInfo->realParameter[295] /* damVal.minFlo.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[295].time_unvarying = 1;
  (data->simulationInfo->realParameter[296] /* damVal.minFlo.realTrue PARAM */) = 0.5;
  data->modelData->realParameterData[296].time_unvarying = 1;
  (data->simulationInfo->realParameter[297] /* damVal.truFalHol.falseHoldDuration PARAM */) = 0.0;
  data->modelData->realParameterData[297].time_unvarying = 1;
  (data->simulationInfo->realParameter[298] /* damVal.truFalHol.trueHoldDuration PARAM */) = 600.0;
  data->modelData->realParameterData[298].time_unvarying = 1;
  (data->simulationInfo->realParameter[299] /* damVal.truFalHol1.falseHoldDuration PARAM */) = 0.0;
  data->modelData->realParameterData[299].time_unvarying = 1;
  (data->simulationInfo->realParameter[300] /* damVal.truFalHol1.trueHoldDuration PARAM */) = 600.0;
  data->modelData->realParameterData[300].time_unvarying = 1;
  (data->simulationInfo->realParameter[301] /* damVal.zerFlo.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[301].time_unvarying = 1;
  (data->simulationInfo->realParameter[302] /* damVal.zerFlo.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[302].time_unvarying = 1;
  (data->simulationInfo->realParameter[307] /* floHys PARAM */) = 0.005;
  data->modelData->realParameterData[307].time_unvarying = 1;
  (data->simulationInfo->realParameter[315] /* looHys PARAM */) = 0.01;
  data->modelData->realParameterData[315].time_unvarying = 1;
  (data->simulationInfo->realParameter[320] /* setOve.booToRea.realFalse PARAM */) = 1.0;
  data->modelData->realParameterData[320].time_unvarying = 1;
  (data->simulationInfo->realParameter[321] /* setOve.booToRea.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[321].time_unvarying = 1;
  (data->simulationInfo->realParameter[322] /* setOve.cloDam.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[322].time_unvarying = 1;
  (data->simulationInfo->realParameter[323] /* setOve.cloDam.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[323].time_unvarying = 1;
  (data->simulationInfo->realParameter[324] /* setOve.opeDam.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[324].time_unvarying = 1;
  (data->simulationInfo->realParameter[325] /* setOve.opeDam.realTrue PARAM */) = 1.0;
  data->modelData->realParameterData[325].time_unvarying = 1;
  (data->simulationInfo->realParameter[328] /* setPoi.VMin_flow PARAM */) = 0.5;
  data->modelData->realParameterData[328].time_unvarying = 1;
  (data->simulationInfo->realParameter[330] /* setPoi.addPar.p PARAM */) = -200.0;
  data->modelData->realParameterData[330].time_unvarying = 1;
  (data->simulationInfo->realParameter[333] /* setPoi.booToRea.realFalse PARAM */) = 0.0;
  data->modelData->realParameterData[333].time_unvarying = 1;
  (data->simulationInfo->realParameter[334] /* setPoi.booToRea.realTrue PARAM */) = 1.0;
  data->modelData->realParameterData[334].time_unvarying = 1;
  (data->simulationInfo->realParameter[335] /* setPoi.booToRea1.realFalse PARAM */) = 1.0;
  data->modelData->realParameterData[335].time_unvarying = 1;
  (data->simulationInfo->realParameter[336] /* setPoi.booToRea1.realTrue PARAM */) = 0.0;
  data->modelData->realParameterData[336].time_unvarying = 1;
  (data->simulationInfo->realParameter[337] /* setPoi.cooSup.greHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[337].time_unvarying = 1;
  (data->simulationInfo->realParameter[338] /* setPoi.cooSup.h PARAM */) = 0.25;
  data->modelData->realParameterData[338].time_unvarying = 1;
  (data->simulationInfo->realParameter[339] /* setPoi.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[339].time_unvarying = 1;
  (data->simulationInfo->realParameter[344] /* setPoi.gai2.k PARAM */) = 1.0;
  data->modelData->realParameterData[344].time_unvarying = 1;
  (data->simulationInfo->realParameter[348] /* setPoi.one.k PARAM */) = 1.0;
  data->modelData->realParameterData[348].time_unvarying = 1;
  (data->simulationInfo->realParameter[353] /* setPoi.zer.k PARAM */) = 0.0;
  data->modelData->realParameterData[353].time_unvarying = 1;
  (data->simulationInfo->realParameter[354] /* setPoi.zer1.k PARAM */) = 0.0;
  data->modelData->realParameterData[354].time_unvarying = 1;
  (data->simulationInfo->realParameter[359] /* setPoi.zonMinFlo.k PARAM */) = 0.5;
  data->modelData->realParameterData[359].time_unvarying = 1;
  (data->simulationInfo->realParameter[364] /* sysReq.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[364].time_unvarying = 1;
  (data->simulationInfo->realParameter[365] /* sysReq.damPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[365].time_unvarying = 1;
  (data->simulationInfo->realParameter[369] /* sysReq.floHys PARAM */) = 0.005;
  data->modelData->realParameterData[369].time_unvarying = 1;
  (data->simulationInfo->realParameter[370] /* sysReq.gai1.k PARAM */) = 0.5;
  data->modelData->realParameterData[370].time_unvarying = 1;
  (data->simulationInfo->realParameter[371] /* sysReq.gai2.k PARAM */) = 0.7;
  data->modelData->realParameterData[371].time_unvarying = 1;
  (data->simulationInfo->realParameter[372] /* sysReq.greEqu.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[372].time_unvarying = 1;
  (data->simulationInfo->realParameter[373] /* sysReq.greEqu.h PARAM */) = 0.005;
  data->modelData->realParameterData[373].time_unvarying = 1;
  (data->simulationInfo->realParameter[374] /* sysReq.greEqu1.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[374].time_unvarying = 1;
  (data->simulationInfo->realParameter[375] /* sysReq.greEqu1.h PARAM */) = 0.005;
  data->modelData->realParameterData[375].time_unvarying = 1;
  (data->simulationInfo->realParameter[376] /* sysReq.greThr.greHys.h PARAM */) = 0.01;
  data->modelData->realParameterData[376].time_unvarying = 1;
  (data->simulationInfo->realParameter[377] /* sysReq.greThr.greHys.t PARAM */) = 0.95;
  data->modelData->realParameterData[377].time_unvarying = 1;
  (data->simulationInfo->realParameter[378] /* sysReq.greThr.h PARAM */) = 0.01;
  data->modelData->realParameterData[378].time_unvarying = 1;
  (data->simulationInfo->realParameter[379] /* sysReq.greThr.t PARAM */) = 0.95;
  data->modelData->realParameterData[379].time_unvarying = 1;
  (data->simulationInfo->realParameter[380] /* sysReq.greThr1.greHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[380].time_unvarying = 1;
  (data->simulationInfo->realParameter[382] /* sysReq.greThr1.h PARAM */) = 0.25;
  data->modelData->realParameterData[382].time_unvarying = 1;
  (data->simulationInfo->realParameter[384] /* sysReq.greThr2.greHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[384].time_unvarying = 1;
  (data->simulationInfo->realParameter[386] /* sysReq.greThr2.h PARAM */) = 0.25;
  data->modelData->realParameterData[386].time_unvarying = 1;
  (data->simulationInfo->realParameter[388] /* sysReq.greThr3.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[388].time_unvarying = 1;
  (data->simulationInfo->realParameter[389] /* sysReq.greThr3.greHys.t PARAM */) = 0.95;
  data->modelData->realParameterData[389].time_unvarying = 1;
  (data->simulationInfo->realParameter[390] /* sysReq.greThr3.h PARAM */) = 0.005;
  data->modelData->realParameterData[390].time_unvarying = 1;
  (data->simulationInfo->realParameter[391] /* sysReq.greThr3.t PARAM */) = 0.95;
  data->modelData->realParameterData[391].time_unvarying = 1;
  (data->simulationInfo->realParameter[392] /* sysReq.greThr4.greHys.h PARAM */) = 0.0025;
  data->modelData->realParameterData[392].time_unvarying = 1;
  (data->simulationInfo->realParameter[393] /* sysReq.greThr4.greHys.t PARAM */) = 0.005;
  data->modelData->realParameterData[393].time_unvarying = 1;
  (data->simulationInfo->realParameter[394] /* sysReq.greThr4.h PARAM */) = 0.0025;
  data->modelData->realParameterData[394].time_unvarying = 1;
  (data->simulationInfo->realParameter[395] /* sysReq.greThr4.t PARAM */) = 0.005;
  data->modelData->realParameterData[395].time_unvarying = 1;
  (data->simulationInfo->realParameter[396] /* sysReq.greThr5.greHys.h PARAM */) = 0.005;
  data->modelData->realParameterData[396].time_unvarying = 1;
  (data->simulationInfo->realParameter[397] /* sysReq.greThr5.greHys.t PARAM */) = 0.95;
  data->modelData->realParameterData[397].time_unvarying = 1;
  (data->simulationInfo->realParameter[398] /* sysReq.greThr5.h PARAM */) = 0.005;
  data->modelData->realParameterData[398].time_unvarying = 1;
  (data->simulationInfo->realParameter[399] /* sysReq.greThr5.t PARAM */) = 0.95;
  data->modelData->realParameterData[399].time_unvarying = 1;
  (data->simulationInfo->realParameter[400] /* sysReq.greThr6.greHys.h PARAM */) = 0.85;
  data->modelData->realParameterData[400].time_unvarying = 1;
  (data->simulationInfo->realParameter[401] /* sysReq.greThr6.greHys.t PARAM */) = 0.95;
  data->modelData->realParameterData[401].time_unvarying = 1;
  (data->simulationInfo->realParameter[402] /* sysReq.greThr6.h PARAM */) = 0.85;
  data->modelData->realParameterData[402].time_unvarying = 1;
  (data->simulationInfo->realParameter[403] /* sysReq.greThr6.t PARAM */) = 0.95;
  data->modelData->realParameterData[403].time_unvarying = 1;
  (data->simulationInfo->realParameter[404] /* sysReq.les.h PARAM */) = 0.25;
  data->modelData->realParameterData[404].time_unvarying = 1;
  (data->simulationInfo->realParameter[405] /* sysReq.les.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[405].time_unvarying = 1;
  (data->simulationInfo->realParameter[406] /* sysReq.les1.h PARAM */) = 0.25;
  data->modelData->realParameterData[406].time_unvarying = 1;
  (data->simulationInfo->realParameter[407] /* sysReq.les1.lesHys.h PARAM */) = 0.25;
  data->modelData->realParameterData[407].time_unvarying = 1;
  (data->simulationInfo->realParameter[408] /* sysReq.looHys PARAM */) = 0.01;
  data->modelData->realParameterData[408].time_unvarying = 1;
  (data->simulationInfo->realParameter[432] /* sysReq.valPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[432].time_unvarying = 1;
  (data->simulationInfo->realParameter[438] /* timSup.conZer.k PARAM */) = 0.0;
  data->modelData->realParameterData[438].time_unvarying = 1;
  (data->simulationInfo->realParameter[439] /* timSup.dTHys PARAM */) = 0.25;
  data->modelData->realParameterData[439].time_unvarying = 1;
  (data->simulationInfo->realParameter[441] /* timSup.greThr.greHys.h PARAM */) = 0.125;
  data->modelData->realParameterData[441].time_unvarying = 1;
  (data->simulationInfo->realParameter[442] /* timSup.greThr.greHys.t PARAM */) = 0.25;
  data->modelData->realParameterData[442].time_unvarying = 1;
  (data->simulationInfo->realParameter[443] /* timSup.greThr.h PARAM */) = 0.125;
  data->modelData->realParameterData[443].time_unvarying = 1;
  (data->simulationInfo->realParameter[444] /* timSup.greThr.t PARAM */) = 0.25;
  data->modelData->realParameterData[444].time_unvarying = 1;
  (data->simulationInfo->realParameter[448] /* timSup.pasSup.h PARAM */) = 0.0;
  data->modelData->realParameterData[448].time_unvarying = 1;
  (data->simulationInfo->realParameter[453] /* timSup.tim.t PARAM */) = 0.0;
  data->modelData->realParameterData[453].time_unvarying = 1;
  (data->simulationInfo->realParameter[454] /* timSup.triSam.y_start PARAM */) = 0.0;
  data->modelData->realParameterData[454].time_unvarying = 1;
  (data->simulationInfo->realParameter[455] /* timSup.triSam1.y_start PARAM */) = 0.0;
  data->modelData->realParameterData[455].time_unvarying = 1;
  (data->simulationInfo->realParameter[460] /* timSup.uniDel.y_start PARAM */) = 0.0;
  data->modelData->realParameterData[460].time_unvarying = 1;
  (data->simulationInfo->realParameter[463] /* valPosHys PARAM */) = 0.005;
  data->modelData->realParameterData[463].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[0] /* ala.cloDam.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[0].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[2] /* ala.cloDam.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[2].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[3] /* ala.cloVal.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[3].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[5] /* ala.cloVal.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[5].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[6] /* ala.fanIni.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[6].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[8] /* ala.gre.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[8].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[9] /* ala.gre.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[9].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[11] /* ala.gre1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[11].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[12] /* ala.gre1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[12].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[14] /* ala.gre2.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[14].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[15] /* ala.gre2.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[15].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[17] /* ala.greThr.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[17].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[18] /* ala.greThr.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[18].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[19] /* ala.greThr1.have_hysteresis PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[19].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[20] /* ala.greThr1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[20].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[21] /* ala.greThr2.have_hysteresis PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[21].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[22] /* ala.greThr2.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[22].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[23] /* ala.les.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[23].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[25] /* ala.les.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[25].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[26] /* ala.les1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[26].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[28] /* ala.les1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[28].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[29] /* ala.les2.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[29].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[31] /* ala.les2.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[31].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[32] /* ala.truDel.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[32].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[33] /* ala.truDel1.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[33].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[34] /* ala.truDel2.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[34].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[35] /* ala.truDel3.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[35].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[36] /* ala.truDel4.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[36].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[37] /* ala.truDel5.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[37].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[38] /* ala.truDel6.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[38].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[39] /* ala.truDel7.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[39].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[43] /* conLoo.conCoo.reverseActing PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[43].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[44] /* conLoo.conCoo.with_D PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[44].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[45] /* conLoo.conCoo.with_I PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[45].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[49] /* conLoo.conHea.reverseActing PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[49].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[50] /* conLoo.conHea.with_D PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[50].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[51] /* conLoo.conHea.with_I PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[51].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[52] /* conLoo.disCoo.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[52].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[53] /* conLoo.disHea.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[53].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[54] /* conLoo.enaCooLoo.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[54].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[56] /* conLoo.enaCooLoo.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[56].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[57] /* conLoo.enaHeaLoo.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[57].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[59] /* conLoo.enaHeaLoo.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[59].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[60] /* conLoo.zerCon.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[60].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[62] /* conLoo.zerCon.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[62].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[63] /* conLoo.zerCon1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[63].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[65] /* conLoo.zerCon1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[65].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[66] /* damVal.conDam.cheYMinMax.k PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[66].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[67] /* damVal.conDam.reverseActing PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[67].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[68] /* damVal.conDam.with_D PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[68].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[69] /* damVal.conDam.with_I PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[69].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[70] /* damVal.conTDisHeaSet.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[70].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[71] /* damVal.conTDisHeaSet.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[71].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[72] /* damVal.conVal.cheYMinMax.k PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[72].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[73] /* damVal.conVal.reverseActing PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[73].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[74] /* damVal.conVal.with_D PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[74].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[75] /* damVal.conVal.with_I PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[75].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[77] /* damVal.gre.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[77].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[78] /* damVal.gre.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[78].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[80] /* damVal.greThr.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[80].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[81] /* damVal.greThr.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[81].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[83] /* damVal.greThr1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[83].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[84] /* damVal.greThr1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[84].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[86] /* damVal.greThr2.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[86].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[87] /* damVal.greThr2.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[87].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[88] /* damVal.lin.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[88].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[89] /* damVal.lin.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[89].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[90] /* damVal.lin3.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[90].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[91] /* damVal.lin3.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[91].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[92] /* damVal.lowMin.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[92].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[94] /* damVal.lowMin.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[94].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[95] /* damVal.truFalHol.pre_u_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[95].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[96] /* damVal.truFalHol1.pre_u_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[96].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[97] /* have_CO2Sen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[97].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[98] /* have_hotWatCoi PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[98].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[99] /* have_occSen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[99].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[100] /* have_winSen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[100].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[104] /* setPoi.cooSup.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[104].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[105] /* setPoi.cooSup.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[105].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[106] /* setPoi.have_CO2Sen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[106].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[107] /* setPoi.have_SZVAV PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[107].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[108] /* setPoi.have_occSen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[108].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[109] /* setPoi.have_parFanPowUni PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[109].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[110] /* setPoi.have_typTerUni PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[110].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[111] /* setPoi.have_winSen PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[111].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[112] /* setPoi.lin.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[112].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[113] /* setPoi.lin.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[113].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[114] /* setPoi.occMinAirSet.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[114].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[115] /* setPoi.occMinAirSet.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[115].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[119] /* setPoi.popBreOutAir.limitAbove PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[119].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[120] /* setPoi.popBreOutAir.limitBelow PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[120].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[122] /* sysReq.greEqu.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[122].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[123] /* sysReq.greEqu.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[123].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[125] /* sysReq.greEqu1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[125].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[126] /* sysReq.greEqu1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[126].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[128] /* sysReq.greThr.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[128].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[129] /* sysReq.greThr.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[129].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[131] /* sysReq.greThr1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[131].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[132] /* sysReq.greThr1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[132].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[134] /* sysReq.greThr2.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[134].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[135] /* sysReq.greThr2.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[135].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[137] /* sysReq.greThr3.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[137].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[138] /* sysReq.greThr3.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[138].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[140] /* sysReq.greThr4.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[140].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[141] /* sysReq.greThr4.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[141].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[143] /* sysReq.greThr5.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[143].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[144] /* sysReq.greThr5.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[144].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[146] /* sysReq.greThr6.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[146].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[147] /* sysReq.greThr6.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[147].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[148] /* sysReq.les.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[148].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[150] /* sysReq.les.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[150].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[151] /* sysReq.les1.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[151].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[153] /* sysReq.les1.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[153].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[154] /* sysReq.tim1.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[154].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[155] /* sysReq.tim2.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[155].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[156] /* sysReq.tim3.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[156].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[157] /* sysReq.tim4.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[157].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[158] /* sysReq.tim5.delayOnInit PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[158].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[159] /* timSup.con1.k PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[159].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[160] /* timSup.con5.k PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[160].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[161] /* timSup.edg.pre_u_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[161].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[163] /* timSup.greThr.have_hysteresis PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[163].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[164] /* timSup.greThr.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[164].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[165] /* timSup.pasSup.have_hysteresis PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[165].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[166] /* timSup.pasSup.pre_y_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[166].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[167] /* timSup.pre1.pre_u_start PARAM */) = 0 /* false */;
  data->modelData->booleanParameterData[167].time_unvarying = 1;
  (data->simulationInfo->booleanParameter[168] /* timSup.truDel.delayOnInit PARAM */) = 1 /* true */;
  data->modelData->booleanParameterData[168].time_unvarying = 1;
  (data->simulationInfo->integerParameter[21] /* ala.heaCoi PARAM */) = 2;
  data->modelData->integerParameterData[21].time_unvarying = 1;
  (data->simulationInfo->integerParameter[23] /* conLoo.conCoo.controllerType PARAM */) = 2;
  data->modelData->integerParameterData[23].time_unvarying = 1;
  (data->simulationInfo->integerParameter[24] /* conLoo.conHea.controllerType PARAM */) = 2;
  data->modelData->integerParameterData[24].time_unvarying = 1;
  (data->simulationInfo->integerParameter[25] /* controllerTypeDam PARAM */) = 2;
  data->modelData->integerParameterData[25].time_unvarying = 1;
  (data->simulationInfo->integerParameter[26] /* controllerTypeVal PARAM */) = 2;
  data->modelData->integerParameterData[26].time_unvarying = 1;
  (data->simulationInfo->integerParameter[27] /* damVal.conDam.controllerType PARAM */) = 2;
  data->modelData->integerParameterData[27].time_unvarying = 1;
  (data->simulationInfo->integerParameter[32] /* damVal.conVal.controllerType PARAM */) = 2;
  data->modelData->integerParameterData[32].time_unvarying = 1;
  (data->simulationInfo->integerParameter[33] /* damVal.controllerTypeDam PARAM */) = 2;
  data->modelData->integerParameterData[33].time_unvarying = 1;
  (data->simulationInfo->integerParameter[34] /* damVal.controllerTypeVal PARAM */) = 2;
  data->modelData->integerParameterData[34].time_unvarying = 1;
  (data->simulationInfo->integerParameter[37] /* heaCoi PARAM */) = 2;
  data->modelData->integerParameterData[37].time_unvarying = 1;
  (data->simulationInfo->integerParameter[49] /* sysReq.heaCoi PARAM */) = 2;
  data->modelData->integerParameterData[49].time_unvarying = 1;
  (data->simulationInfo->integerParameter[56] /* venStd PARAM */) = 1;
  data->modelData->integerParameterData[56].time_unvarying = 1;
  ReheatControllerFMU_updateBoundParameters_0(data, threadData);
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif
