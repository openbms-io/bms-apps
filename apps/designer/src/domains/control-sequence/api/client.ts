import {
  convertParametersApiV1ParametersConvertPost,
  createInstanceApiV1G36VavReheatInstancesPost,
  deleteInstanceApiV1G36VavReheatInstancesInstanceIdDelete,
  deleteFmuApiV1G36VavReheatInstancesInstanceIdFmuDelete,
  getDefaultsApiV1ParametersDefaultsGet,
  getInstanceApiV1G36VavReheatInstancesInstanceIdGet,
  stepApiV1G36VavReheatInstancesInstanceIdStepPost,
  updateInstanceApiV1G36VavReheatInstancesInstanceIdPut,
} from './generated/sdk.gen'
import type {
  AirflowUnit,
  CreateInstanceRequestReheatParameters,
  DeleteInstanceResponse,
  ErrorResponse,
  InstanceResponseWithCategoriesReheatParameters,
  ReheatParameters,
  SequenceType,
  StepRequest,
  StepResponse,
  TemperatureUnit,
} from './generated/types.gen'

export async function createInstance(
  request: CreateInstanceRequestReheatParameters
): Promise<InstanceResponseWithCategoriesReheatParameters> {
  const response = await createInstanceApiV1G36VavReheatInstancesPost({
    body: request,
  })

  if (response.error) {
    const errorResponse = response.error as ErrorResponse
    throw new Error(
      errorResponse.detail ?? 'Failed to create control sequence instance'
    )
  }

  return response.data!
}

export async function deleteInstance(
  instanceId: string
): Promise<DeleteInstanceResponse> {
  const response =
    await deleteInstanceApiV1G36VavReheatInstancesInstanceIdDelete({
      path: { instance_id: instanceId },
    })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(
      errorResponse.detail ?? 'Failed to delete control sequence instance'
    )
  }

  return response.data!
}

export async function deleteFmu(
  instanceId: string
): Promise<DeleteInstanceResponse> {
  const response = await deleteFmuApiV1G36VavReheatInstancesInstanceIdFmuDelete(
    {
      path: { instance_id: instanceId },
    }
  )

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(errorResponse.detail ?? 'Failed to delete FMU instance')
  }

  return response.data!
}

export async function stepInstance(
  instanceId: string,
  request: StepRequest
): Promise<StepResponse> {
  const response = await stepApiV1G36VavReheatInstancesInstanceIdStepPost({
    path: { instance_id: instanceId },
    body: request,
  })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(
      errorResponse.detail ??
        errorResponse.error ??
        'Failed to execute control sequence step'
    )
  }

  return response.data!
}

export async function getInstance({
  instanceId,
}: {
  instanceId: string
}): Promise<InstanceResponseWithCategoriesReheatParameters> {
  const response = await getInstanceApiV1G36VavReheatInstancesInstanceIdGet({
    path: { instance_id: instanceId },
  })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(
      errorResponse.detail ?? 'Failed to get control sequence instance'
    )
  }

  return response.data!
}

export async function updateInstance({
  instanceId,
  parameters,
}: {
  instanceId: string
  parameters: ReheatParameters
}): Promise<InstanceResponseWithCategoriesReheatParameters> {
  const response = await updateInstanceApiV1G36VavReheatInstancesInstanceIdPut({
    path: { instance_id: instanceId },
    body: { parameters },
  })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(
      errorResponse.detail ?? 'Failed to update control sequence instance'
    )
  }

  return response.data!
}

export async function convertParameters({
  sequenceType,
  parameters,
  targetTemperatureUnit,
  targetAirflowUnit,
}: {
  sequenceType: SequenceType
  parameters: ReheatParameters
  targetTemperatureUnit: TemperatureUnit
  targetAirflowUnit: AirflowUnit
}): Promise<ReheatParameters> {
  const response = await convertParametersApiV1ParametersConvertPost({
    body: {
      sequence_type: sequenceType,
      parameters,
      target_temperature_unit: targetTemperatureUnit,
      target_airflow_unit: targetAirflowUnit,
    },
  })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(errorResponse.detail ?? 'Failed to convert parameters')
  }

  return response.data!.parameters
}

export async function getDefaultParameters(
  sequenceType: SequenceType
): Promise<ReheatParameters> {
  const response = await getDefaultsApiV1ParametersDefaultsGet({
    query: { sequenceType },
  })

  if (response.error) {
    const errorResponse = response.error as unknown as ErrorResponse
    throw new Error(errorResponse.detail ?? 'Failed to get default parameters')
  }

  return response.data!.parameters
}
