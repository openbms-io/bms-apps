"""FMU lifecycle management for a single FMU instance."""

import asyncio

from fmpy.fmi2 import FMU2Slave

from src.adapters.exceptions import FmuExecutionError, FmuValidationError
from src.adapters.fmu_data.base import FmuDataType, FMUDataProtocol
from src.adapters.fmu_loader import FmuLoader
from src.adapters.sequence_type import SequenceType
from src.adapters.fmu_instance import FmuInstance, FmuInstanceState


class FmuLifecycleManager:
    """Manages lifecycle of a single FMU instance."""

    def __init__(
        self,
        sequence_type: SequenceType,
        fmu_data: FMUDataProtocol,
    ) -> None:
        self._lock = asyncio.Lock()
        md, unzip_dir = FmuLoader.load(sequence_type)
        value_refs = FmuLoader.build_value_refs(md)

        fmu = FMU2Slave(
            guid=md.guid,
            unzipDirectory=unzip_dir,
            modelIdentifier=md.coSimulation.modelIdentifier,
        )

        fmu.instantiate()
        try:
            fmu.setupExperiment(startTime=0.0)

            self._fmu_instance = FmuInstance(
                fmu=fmu,
                model_description=md,
                unzip_dir=unzip_dir,
                current_time=0.0,
                sequence_type=sequence_type,
                value_refs=value_refs,
                state=FmuInstanceState.CREATED,
            )

            self._validate_output_specs(fmu_data)
            self._apply_configuration(fmu_data)
            self._set_inputs(fmu_data)

            fmu.enterInitializationMode()
            fmu.exitInitializationMode()
            self._fmu_instance.state = FmuInstanceState.INITIALIZED
        except Exception:
            fmu.freeInstance()
            raise

    async def terminate(self) -> None:
        async with self._lock:
            self._fmu_instance.fmu.terminate()
            self._fmu_instance.fmu.freeInstance()
            self._fmu_instance.state = FmuInstanceState.TERMINATED

    async def set_inputs(self, fmu_data: FMUDataProtocol) -> None:
        async with self._lock:
            self._set_inputs(fmu_data)

    async def step(
        self,
        fmu_data: FMUDataProtocol,
        step_size: float = 1.0,
    ) -> dict[str, float | bool | int]:
        async with self._lock:
            self._validate_inputs(fmu_data)
            self._set_inputs(fmu_data)

            self._fmu_instance.state = FmuInstanceState.RUNNING
            self._fmu_instance.fmu.doStep(
                currentCommunicationPoint=self._fmu_instance.current_time,
                communicationStepSize=step_size,
            )
            self._fmu_instance.current_time += step_size

            return self._read_outputs(fmu_data)

    @property
    def state(self) -> FmuInstanceState:
        return self._fmu_instance.state

    @property
    def sequence_type(self) -> SequenceType:
        return self._fmu_instance.sequence_type

    @property
    def current_time(self) -> float:
        return self._fmu_instance.current_time

    def _validate_output_specs(self, fmu_data: FMUDataProtocol) -> None:
        for spec in fmu_data.output_variable_specs():
            if spec.name not in self._fmu_instance.value_refs:
                raise FmuValidationError(
                    f"Unknown FMU output variable: {spec.name}",
                    missing_inputs=[spec.name],
                )
        for spec in fmu_data.calculated_parameter_specs():
            if spec.name not in self._fmu_instance.value_refs:
                raise FmuValidationError(
                    f"Unknown FMU calculated parameter: {spec.name}",
                    missing_inputs=[spec.name],
                )

    def _apply_configuration(self, fmu_data: FMUDataProtocol) -> None:
        for var in fmu_data.configuration_variables:
            ref = self._fmu_instance.value_refs.get(var.name)
            if ref is None:
                continue
            self._set_fmu_value(ref, var.value, var.data_type)

    def _set_inputs(self, fmu_data: FMUDataProtocol) -> None:
        for var in fmu_data.input_variables:
            ref = self._fmu_instance.value_refs.get(var.name)
            if ref is None:
                continue
            self._set_fmu_value(ref, var.value, var.data_type)

    def _set_fmu_value(
        self,
        ref: int,
        value: float | bool | int,
        data_type: FmuDataType,
    ) -> None:
        match data_type:
            case FmuDataType.REAL:
                self._fmu_instance.fmu.setReal([ref], [float(value)])
            case FmuDataType.BOOLEAN:
                self._fmu_instance.fmu.setBoolean([ref], [bool(value)])
            case FmuDataType.INTEGER:
                self._fmu_instance.fmu.setInteger([ref], [int(value)])

    def _read_outputs(
        self,
        fmu_data: FMUDataProtocol,
    ) -> dict[str, float | bool | int]:
        outputs: dict[str, float | bool | int] = {}
        all_specs = list(fmu_data.output_variable_specs()) + list(fmu_data.calculated_parameter_specs())
        for spec in all_specs:
            ref = self._fmu_instance.value_refs[spec.name]

            match spec.data_type:
                case FmuDataType.REAL:
                    outputs[spec.name] = self._fmu_instance.fmu.getReal([ref])[0]
                case FmuDataType.BOOLEAN:
                    outputs[spec.name] = self._fmu_instance.fmu.getBoolean([ref])[0]
                case FmuDataType.INTEGER:
                    outputs[spec.name] = self._fmu_instance.fmu.getInteger([ref])[0]

        return outputs

    def _validate_inputs(self, fmu_data: FMUDataProtocol) -> None:
        required_names = set(fmu_data.required_input_names())
        provided_names = {var.name for var in fmu_data.input_variables}
        missing = required_names - provided_names

        if missing:
            raise FmuValidationError(
                f"Missing required inputs: {sorted(missing)}",
                missing_inputs=sorted(missing),
            )

        for var in fmu_data.input_variables:
            if var.name not in self._fmu_instance.value_refs:
                raise FmuExecutionError(
                    f"Unknown FMU variable: {var.name}",
                    instance_id=None,
                )
