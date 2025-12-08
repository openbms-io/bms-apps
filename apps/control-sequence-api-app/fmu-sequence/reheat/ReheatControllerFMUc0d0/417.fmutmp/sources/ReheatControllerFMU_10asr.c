/* Asserts */
#include "ReheatControllerFMU_model.h"
#if defined(__cplusplus)
extern "C" {
#endif


/*
equation index: 2587
type: ALGORITHM

  assert(VSet_flow >= 0.0, "Variable violating min constraint: 0.0 <= VSet_flow, has value: " + String(VSet_flow, "g"));
*/
void ReheatControllerFMU_eqFunction_2587(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2587};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,64,"Variable violating min constraint: 0.0 <= VSet_flow, has value: ");
  modelica_string tmp2;
  modelica_metatype tmpMeta3;
  static int tmp4 = 0;
  if(!tmp4)
  {
    tmp0 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */),0.0);
    if(!tmp0)
    {
      tmp2 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[23]] /* VSet_flow variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta3 = stringAppend(MMC_REFSTRINGLIT(tmp1),tmp2);
      {
        const char* assert_cond = "(VSet_flow >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",304,3,310,59,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta3));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",304,3,310,59,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta3));
        }
      }
      tmp4 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2588
type: ALGORITHM

  assert(yDam >= 0.0 and yDam <= 1.0, "Variable violating min/max constraint: 0.0 <= yDam <= 1.0, has value: " + String(yDam, "g"));
*/
void ReheatControllerFMU_eqFunction_2588(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2588};
  modelica_boolean tmp5;
  modelica_boolean tmp6;
  static const MMC_DEFSTRINGLIT(tmp7,70,"Variable violating min/max constraint: 0.0 <= yDam <= 1.0, has value: ");
  modelica_string tmp8;
  modelica_metatype tmpMeta9;
  static int tmp10 = 0;
  if(!tmp10)
  {
    tmp5 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */),0.0);
    tmp6 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */),1.0);
    if(!(tmp5 && tmp6))
    {
      tmp8 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[190]] /* yDam variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta9 = stringAppend(MMC_REFSTRINGLIT(tmp7),tmp8);
      {
        const char* assert_cond = "(yDam >= 0.0 and yDam <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",311,3,315,59,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta9));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",311,3,315,59,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta9));
        }
      }
      tmp10 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2589
type: ALGORITHM

  assert(yVal >= 0.0 and yVal <= 1.0, "Variable violating min/max constraint: 0.0 <= yVal <= 1.0, has value: " + String(yVal, "g"));
*/
void ReheatControllerFMU_eqFunction_2589(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2589};
  modelica_boolean tmp11;
  modelica_boolean tmp12;
  static const MMC_DEFSTRINGLIT(tmp13,70,"Variable violating min/max constraint: 0.0 <= yVal <= 1.0, has value: ");
  modelica_string tmp14;
  modelica_metatype tmpMeta15;
  static int tmp16 = 0;
  if(!tmp16)
  {
    tmp11 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),0.0);
    tmp12 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */),1.0);
    if(!(tmp11 && tmp12))
    {
      tmp14 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[191]] /* yVal variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta15 = stringAppend(MMC_REFSTRINGLIT(tmp13),tmp14);
      {
        const char* assert_cond = "(yVal >= 0.0 and yVal <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",316,3,321,59,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta15));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Controller.mo",316,3,321,59,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta15));
        }
      }
      tmp16 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2590
type: ALGORITHM

  assert(actAirSet.VActCooMax_flow >= 0.0, "Variable violating min constraint: 0.0 <= actAirSet.VActCooMax_flow, has value: " + String(actAirSet.VActCooMax_flow, "g"));
*/
void ReheatControllerFMU_eqFunction_2590(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2590};
  modelica_boolean tmp17;
  static const MMC_DEFSTRINGLIT(tmp18,80,"Variable violating min constraint: 0.0 <= actAirSet.VActCooMax_flow, has value: ");
  modelica_string tmp19;
  modelica_metatype tmpMeta20;
  static int tmp21 = 0;
  if(!tmp21)
  {
    tmp17 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* actAirSet.VActCooMax_flow variable */),0.0);
    if(!tmp17)
    {
      tmp19 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[24]] /* actAirSet.VActCooMax_flow variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta20 = stringAppend(MMC_REFSTRINGLIT(tmp18),tmp19);
      {
        const char* assert_cond = "(actAirSet.VActCooMax_flow >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",28,3,34,58,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta20));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",28,3,34,58,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta20));
        }
      }
      tmp21 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2591
type: ALGORITHM

  assert(actAirSet.VActMin_flow >= 0.0, "Variable violating min constraint: 0.0 <= actAirSet.VActMin_flow, has value: " + String(actAirSet.VActMin_flow, "g"));
*/
void ReheatControllerFMU_eqFunction_2591(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2591};
  modelica_boolean tmp22;
  static const MMC_DEFSTRINGLIT(tmp23,77,"Variable violating min constraint: 0.0 <= actAirSet.VActMin_flow, has value: ");
  modelica_string tmp24;
  modelica_metatype tmpMeta25;
  static int tmp26 = 0;
  if(!tmp26)
  {
    tmp22 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */),0.0);
    if(!tmp22)
    {
      tmp24 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[27]] /* actAirSet.VActMin_flow variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta25 = stringAppend(MMC_REFSTRINGLIT(tmp23),tmp24);
      {
        const char* assert_cond = "(actAirSet.VActMin_flow >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",42,3,48,58,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta25));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",42,3,48,58,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta25));
        }
      }
      tmp26 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2592
type: ALGORITHM

  assert(actAirSet.VActHeaMin_flow >= 0.0, "Variable violating min constraint: 0.0 <= actAirSet.VActHeaMin_flow, has value: " + String(actAirSet.VActHeaMin_flow, "g"));
*/
void ReheatControllerFMU_eqFunction_2592(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2592};
  modelica_boolean tmp27;
  static const MMC_DEFSTRINGLIT(tmp28,80,"Variable violating min constraint: 0.0 <= actAirSet.VActHeaMin_flow, has value: ");
  modelica_string tmp29;
  modelica_metatype tmpMeta30;
  static int tmp31 = 0;
  if(!tmp31)
  {
    tmp27 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[26]] /* actAirSet.VActHeaMin_flow variable */),0.0);
    if(!tmp27)
    {
      tmp29 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[26]] /* actAirSet.VActHeaMin_flow variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta30 = stringAppend(MMC_REFSTRINGLIT(tmp28),tmp29);
      {
        const char* assert_cond = "(actAirSet.VActHeaMin_flow >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",49,3,55,59,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta30));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",49,3,55,59,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta30));
        }
      }
      tmp31 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2593
type: ALGORITHM

  assert(actAirSet.VActHeaMax_flow >= 0.0, "Variable violating min constraint: 0.0 <= actAirSet.VActHeaMax_flow, has value: " + String(actAirSet.VActHeaMax_flow, "g"));
*/
void ReheatControllerFMU_eqFunction_2593(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2593};
  modelica_boolean tmp32;
  static const MMC_DEFSTRINGLIT(tmp33,80,"Variable violating min constraint: 0.0 <= actAirSet.VActHeaMax_flow, has value: ");
  modelica_string tmp34;
  modelica_metatype tmpMeta35;
  static int tmp36 = 0;
  if(!tmp36)
  {
    tmp32 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* actAirSet.VActHeaMax_flow variable */),0.0);
    if(!tmp32)
    {
      tmp34 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[25]] /* actAirSet.VActHeaMax_flow variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta35 = stringAppend(MMC_REFSTRINGLIT(tmp33),tmp34);
      {
        const char* assert_cond = "(actAirSet.VActHeaMax_flow >= 0.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",56,3,62,60,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta35));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/ActiveAirFlow.mo",56,3,62,60,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta35));
        }
      }
      tmp36 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2594
type: ALGORITHM

  assert(conLoo.yCoo >= 0.0 and conLoo.yCoo <= 1.0, "Variable violating min/max constraint: 0.0 <= conLoo.yCoo <= 1.0, has value: " + String(conLoo.yCoo, "g"));
*/
void ReheatControllerFMU_eqFunction_2594(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2594};
  modelica_boolean tmp37;
  modelica_boolean tmp38;
  static const MMC_DEFSTRINGLIT(tmp39,77,"Variable violating min/max constraint: 0.0 <= conLoo.yCoo <= 1.0, has value: ");
  modelica_string tmp40;
  modelica_metatype tmpMeta41;
  static int tmp42 = 0;
  if(!tmp42)
  {
    tmp37 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */),0.0);
    tmp38 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */),1.0);
    if(!(tmp37 && tmp38))
    {
      tmp40 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[71]] /* conLoo.yCoo variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta41 = stringAppend(MMC_REFSTRINGLIT(tmp39),tmp40);
      {
        const char* assert_cond = "(conLoo.yCoo >= 0.0 and conLoo.yCoo <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/ThermalZones/ControlLoops.mo",44,3,49,55,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta41));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/ThermalZones/ControlLoops.mo",44,3,49,55,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta41));
        }
      }
      tmp42 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2595
type: ALGORITHM

  assert(conLoo.yHea >= 0.0 and conLoo.yHea <= 1.0, "Variable violating min/max constraint: 0.0 <= conLoo.yHea <= 1.0, has value: " + String(conLoo.yHea, "g"));
*/
void ReheatControllerFMU_eqFunction_2595(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2595};
  modelica_boolean tmp43;
  modelica_boolean tmp44;
  static const MMC_DEFSTRINGLIT(tmp45,77,"Variable violating min/max constraint: 0.0 <= conLoo.yHea <= 1.0, has value: ");
  modelica_string tmp46;
  modelica_metatype tmpMeta47;
  static int tmp48 = 0;
  if(!tmp48)
  {
    tmp43 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */),0.0);
    tmp44 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */),1.0);
    if(!(tmp43 && tmp44))
    {
      tmp46 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[72]] /* conLoo.yHea variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta47 = stringAppend(MMC_REFSTRINGLIT(tmp45),tmp46);
      {
        const char* assert_cond = "(conLoo.yHea >= 0.0 and conLoo.yHea <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/ThermalZones/ControlLoops.mo",50,3,55,57,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta47));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/ThermalZones/ControlLoops.mo",50,3,55,57,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta47));
        }
      }
      tmp48 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2596
type: ALGORITHM

  assert(damVal.yDam >= 0.0 and damVal.yDam <= 1.0, "Variable violating min/max constraint: 0.0 <= damVal.yDam <= 1.0, has value: " + String(damVal.yDam, "g"));
*/
void ReheatControllerFMU_eqFunction_2596(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2596};
  modelica_boolean tmp49;
  modelica_boolean tmp50;
  static const MMC_DEFSTRINGLIT(tmp51,77,"Variable violating min/max constraint: 0.0 <= damVal.yDam <= 1.0, has value: ");
  modelica_string tmp52;
  modelica_metatype tmpMeta53;
  static int tmp54 = 0;
  if(!tmp54)
  {
    tmp49 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[139]] /* damVal.yDam variable */),0.0);
    tmp50 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[139]] /* damVal.yDam variable */),1.0);
    if(!(tmp49 && tmp50))
    {
      tmp52 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[139]] /* damVal.yDam variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta53 = stringAppend(MMC_REFSTRINGLIT(tmp51),tmp52);
      {
        const char* assert_cond = "(damVal.yDam >= 0.0 and damVal.yDam <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",176,3,181,58,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta53));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",176,3,181,58,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta53));
        }
      }
      tmp54 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 2597
type: ALGORITHM

  assert(damVal.yVal >= 0.0 and damVal.yVal <= 1.0, "Variable violating min/max constraint: 0.0 <= damVal.yVal <= 1.0, has value: " + String(damVal.yVal, "g"));
*/
void ReheatControllerFMU_eqFunction_2597(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2597};
  modelica_boolean tmp55;
  modelica_boolean tmp56;
  static const MMC_DEFSTRINGLIT(tmp57,77,"Variable violating min/max constraint: 0.0 <= damVal.yVal <= 1.0, has value: ");
  modelica_string tmp58;
  modelica_metatype tmpMeta59;
  static int tmp60 = 0;
  if(!tmp60)
  {
    tmp55 = GreaterEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[140]] /* damVal.yVal variable */),0.0);
    tmp56 = LessEq((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[140]] /* damVal.yVal variable */),1.0);
    if(!(tmp55 && tmp56))
    {
      tmp58 = modelica_real_to_modelica_string_format((data->localData[0]->realVars[data->simulationInfo->realVarsIndex[140]] /* damVal.yVal variable */), (modelica_string) mmc_strings_len1[103]);
      tmpMeta59 = stringAppend(MMC_REFSTRINGLIT(tmp57),tmp58);
      {
        const char* assert_cond = "(damVal.yVal >= 0.0 and damVal.yVal <= 1.0)";
        if (data->simulationInfo->noThrowAsserts) {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",182,3,187,60,0};
          infoStreamPrintWithEquationIndexes(OMC_LOG_ASSERT, info, 0, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta59));
        } else {
          FILE_INFO info = {"/Users/amol/Documents/ai-projects/modelica-buildings/Buildings/Controls/OBC/ASHRAE/G36/TerminalUnits/Reheat/Subsequences/DamperValves.mo",182,3,187,60,0};
          omc_assert_warning_withEquationIndexes(info, equationIndexes, "The following assertion has been violated %sat time %f\n(%s) --> \"%s\"", initial() ? "during initialization " : "", data->localData[0]->timeValue, assert_cond, MMC_STRINGDATA(tmpMeta59));
        }
      }
      tmp60 = 1;
    }
  }
  TRACE_POP
}
/* function to check assert after a step is done */
OMC_DISABLE_OPT
int ReheatControllerFMU_checkForAsserts(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  ReheatControllerFMU_eqFunction_2587(data, threadData);

  ReheatControllerFMU_eqFunction_2588(data, threadData);

  ReheatControllerFMU_eqFunction_2589(data, threadData);

  ReheatControllerFMU_eqFunction_2590(data, threadData);

  ReheatControllerFMU_eqFunction_2591(data, threadData);

  ReheatControllerFMU_eqFunction_2592(data, threadData);

  ReheatControllerFMU_eqFunction_2593(data, threadData);

  ReheatControllerFMU_eqFunction_2594(data, threadData);

  ReheatControllerFMU_eqFunction_2595(data, threadData);

  ReheatControllerFMU_eqFunction_2596(data, threadData);

  ReheatControllerFMU_eqFunction_2597(data, threadData);
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

