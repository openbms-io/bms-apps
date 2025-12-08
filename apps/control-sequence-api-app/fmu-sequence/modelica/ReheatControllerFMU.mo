within ;
model ReheatControllerFMU
  "FMU wrapper for G36 VAV Reheat Terminal Unit Controller with all parameters tunable"

  // Ventilation standard
  parameter Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard venStd_in =
    Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1
    "Ventilation standard, ASHRAE 62.1 or Title 24";

  // Sensor configuration
  parameter Boolean have_winSen_in = true "True: the zone has window sensor";
  parameter Boolean have_occSen_in = true "True: the zone has occupancy sensor";
  parameter Boolean have_CO2Sen_in = true "True: the zone has CO2 sensor";
  parameter Boolean have_hotWatCoi_in = true
    "True: the unit has the hot water coil; False: the unit has the modulated electric coil";
  parameter Boolean permit_occStandby_in = true "True: occupied-standby mode is permitted";

  // Outdoor airflow parameters
  parameter Real VOccMin_flow_in(unit="m3/s") = 0 "Zone minimum outdoor airflow for occupants";
  parameter Real VAreMin_flow_in(unit="m3/s") = 0 "Zone minimum outdoor airflow for building area";

  // Design conditions
  parameter Real VAreBreZon_flow_in(unit="m3/s") = 0.006
    "Design area component of the breathing zone outdoor airflow";
  parameter Real VPopBreZon_flow_in(unit="m3/s") = 0.005
    "Design population component of the breathing zone outdoor airflow";
  parameter Real VMin_flow_in(unit="m3/s") = 0.5 "Design zone minimum airflow setpoint";
  parameter Real VCooMax_flow_in(unit="m3/s") = 1.5 "Design zone cooling maximum airflow rate";
  parameter Real VHeaMin_flow_in(unit="m3/s") = 0.5 "Design zone heating minimum airflow rate";
  parameter Real VHeaMax_flow_in(unit="m3/s") = 1.2 "Design zone heating maximum airflow rate";

  // Control loops - Cooling
  parameter Real kCooCon_in = 0.1 "Gain of controller for cooling control loop";
  parameter Real TiCooCon_in(unit="s") = 120 "Time constant of integrator block for cooling control loop";

  // Control loops - Heating
  parameter Real kHeaCon_in = 0.1 "Gain of controller for heating control loop";
  parameter Real TiHeaCon_in(unit="s") = 120 "Time constant of integrator block for heating control loop";

  // Damper and valve control
  parameter Real dTDisZonSetMax_in(unit="K") = 11
    "Zone maximum discharge air temperature above heating setpoint";
  parameter Real TDisMin_in(unit="K") = 283.15 "Lowest discharge air temperature";

  // Valve control
  parameter Buildings.Controls.OBC.CDL.Types.SimpleController controllerTypeVal_in =
    Buildings.Controls.OBC.CDL.Types.SimpleController.PI "Type of controller for valve";
  parameter Real kVal_in = 0.5 "Gain of controller for valve control";
  parameter Real TiVal_in(unit="s") = 300 "Time constant of integrator block for valve control";
  parameter Real TdVal_in(unit="s") = 0.1 "Time constant of derivative block for valve control";

  // Damper control
  parameter Buildings.Controls.OBC.CDL.Types.SimpleController controllerTypeDam_in =
    Buildings.Controls.OBC.CDL.Types.SimpleController.PI "Type of controller for damper";
  parameter Real kDam_in = 0.5 "Gain of controller for damper control";
  parameter Real TiDam_in(unit="s") = 300 "Time constant of integrator block for damper control";
  parameter Real TdDam_in(unit="s") = 0.1 "Time constant of derivative block for damper control";

  // System requests
  parameter Real thrTemDif_in(unit="K") = 3
    "Threshold difference between zone temperature and cooling setpoint for generating 3 cooling SAT reset requests";
  parameter Real twoTemDif_in(unit="K") = 2
    "Threshold difference between zone temperature and cooling setpoint for generating 2 cooling SAT reset requests";
  parameter Real thrTDis_1_in(unit="K") = 17
    "Threshold difference between discharge air temperature and its setpoint for generating 3 hot water reset requests";
  parameter Real thrTDis_2_in(unit="K") = 8
    "Threshold difference between discharge air temperature and its setpoint for generating 2 hot water reset requests";

  // Duration time
  parameter Real durTimTem_in(unit="s") = 120 "Duration time of zone temperature exceeds setpoint";
  parameter Real durTimFlo_in(unit="s") = 60 "Duration time of airflow rate less than setpoint";
  parameter Real durTimDisAir_in(unit="s") = 300
    "Duration time of discharge air temperature less than setpoint";

  // Alarms
  parameter Real staPreMul_in = 1 "Importance multiplier for the zone static pressure reset control loop";
  parameter Real hotWatRes_in = 1 "Importance multiplier for the hot water reset control loop";
  parameter Real lowFloTim_in(unit="s") = 300 "Threshold time to check low flow rate";
  parameter Real lowTemTim_in(unit="s") = 600 "Threshold time to check low discharge temperature";
  parameter Real fanOffTim_in(unit="s") = 600 "Threshold time to check fan off";
  parameter Real leaFloTim_in(unit="s") = 600 "Threshold time to check damper leaking airflow";
  parameter Real valCloTim_in(unit="s") = 900 "Threshold time to check valve leaking water flow";

  // Time-based suppression
  parameter Real samplePeriod_in(unit="s") = 120 "Sample period of component";
  parameter Real chaRat_in(unit="s/K") = 540
    "Gain factor to calculate suppression time based on the change of the setpoint";
  parameter Real maxSupTim_in(unit="s") = 1800 "Maximum suppression time";

  // Advanced
  parameter Real dTHys_in(unit="K") = 0.25
    "Near zero temperature difference, below which the difference will be seen as zero";
  parameter Real looHys_in(unit="1") = 0.01
    "Loop output hysteresis below which the output will be seen as zero";
  parameter Real floHys_in(unit="m3/s") = 0.01*VMin_flow_in
    "Near zero flow rate, below which the flow rate or difference will be seen as zero";
  parameter Real damPosHys_in(unit="1") = 0.005
    "Near zero damper position, below which the damper will be seen as closed";
  parameter Real valPosHys_in(unit="1") = 0.005
    "Near zero valve position, below which the valve will be seen as closed";
  parameter Real staTim_in(unit="s") = 1800 "Delay triggering alarms after enabling AHU supply fan";
  parameter Real iniDam_in(unit="1") = 0.01 "Initial damper position when the damper control is enabled";
  parameter Real timChe_in(unit="s") = 30 "Threshold time to check the zone temperature status";

  // Distribution effectiveness
  parameter Real zonDisEff_cool_in(unit="1") = 1.0 "Zone cooling air distribution effectiveness";
  parameter Real zonDisEff_heat_in(unit="1") = 0.8 "Zone heating air distribution effectiveness";

  extends Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller(
    venStd = venStd_in,
    have_winSen = have_winSen_in,
    have_occSen = have_occSen_in,
    have_CO2Sen = have_CO2Sen_in,
    have_hotWatCoi = have_hotWatCoi_in,
    permit_occStandby = permit_occStandby_in,
    VOccMin_flow = VOccMin_flow_in,
    VAreMin_flow = VAreMin_flow_in,
    VAreBreZon_flow = VAreBreZon_flow_in,
    VPopBreZon_flow = VPopBreZon_flow_in,
    VMin_flow = VMin_flow_in,
    VCooMax_flow = VCooMax_flow_in,
    VHeaMin_flow = VHeaMin_flow_in,
    VHeaMax_flow = VHeaMax_flow_in,
    kCooCon = kCooCon_in,
    TiCooCon = TiCooCon_in,
    kHeaCon = kHeaCon_in,
    TiHeaCon = TiHeaCon_in,
    dTDisZonSetMax = dTDisZonSetMax_in,
    TDisMin = TDisMin_in,
    controllerTypeVal = controllerTypeVal_in,
    kVal = kVal_in,
    TiVal = TiVal_in,
    TdVal = TdVal_in,
    controllerTypeDam = controllerTypeDam_in,
    kDam = kDam_in,
    TiDam = TiDam_in,
    TdDam = TdDam_in,
    thrTemDif = thrTemDif_in,
    twoTemDif = twoTemDif_in,
    thrTDis_1 = thrTDis_1_in,
    thrTDis_2 = thrTDis_2_in,
    durTimTem = durTimTem_in,
    durTimFlo = durTimFlo_in,
    durTimDisAir = durTimDisAir_in,
    staPreMul = staPreMul_in,
    hotWatRes = hotWatRes_in,
    lowFloTim = lowFloTim_in,
    lowTemTim = lowTemTim_in,
    fanOffTim = fanOffTim_in,
    leaFloTim = leaFloTim_in,
    valCloTim = valCloTim_in,
    samplePeriod = samplePeriod_in,
    chaRat = chaRat_in,
    maxSupTim = maxSupTim_in,
    dTHys = dTHys_in,
    looHys = looHys_in,
    floHys = floHys_in,
    damPosHys = damPosHys_in,
    valPosHys = valPosHys_in,
    staTim = staTim_in,
    iniDam = iniDam_in,
    timChe = timChe_in,
    zonDisEff_cool = zonDisEff_cool_in,
    zonDisEff_heat = zonDisEff_heat_in);

  annotation (
    experiment(StopTime=86400, Tolerance=1e-6),
    Documentation(info="<html>
<p>
FMU export wrapper for the ASHRAE Guideline 36 VAV Reheat Terminal Unit Controller.
</p>
<p>
This model extends the base Controller with all parameters exposed as tunable
FMU parameters. Each parameter is declared explicitly and passed through to
the base controller, ensuring they appear as configurable parameters in the FMU.
</p>
<p>
For parameter documentation, see:
<a href=\"https://simulationresearch.lbl.gov/modelica/releases/v11.1.0/help/Buildings_Controls_OBC_ASHRAE_G36_TerminalUnits_Reheat.html\">
Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller</a>
</p>
</html>"));
end ReheatControllerFMU;
