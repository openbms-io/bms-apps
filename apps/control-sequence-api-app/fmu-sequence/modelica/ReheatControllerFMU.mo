within ;
model ReheatControllerFMU
  "FMU wrapper for G36 VAV Reheat Terminal Unit Controller with all parameters tunable"

  extends Buildings.Controls.OBC.ASHRAE.G36.TerminalUnits.Reheat.Controller(
    // Required parameters (no defaults in base) - provide defaults without 'final'
    venStd=Buildings.Controls.OBC.ASHRAE.G36.Types.VentilationStandard.ASHRAE62_1,
    VAreBreZon_flow=0.006,
    VPopBreZon_flow=0.005,
    VMin_flow=0.5,
    VCooMax_flow=1.5,
    VHeaMin_flow=0.5,
    VHeaMax_flow=1.2,
    VOccMin_flow=0,
    VAreMin_flow=0);
    // All ~40 other parameters inherit defaults from base Controller and are tunable

  annotation (
    experiment(StopTime=86400, Tolerance=1e-6),
    Documentation(info="<html>
<p>
FMU export wrapper for the ASHRAE Guideline 36 VAV Reheat Terminal Unit Controller.
</p>
<p>
This model extends the base Controller and provides default parameter values
for required parameters. All ~50 parameters are tunable in the exported FMU.
</p>
</html>"));
end ReheatControllerFMU;
