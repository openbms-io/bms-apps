/**
 * Control Sequence API - Internal exports
 *
 * Client functions are used internally by data nodes.
 *
 * @module control-sequence/api
 */

export {
  createInstance,
  deleteInstance,
  getInstance,
  updateInstance,
} from './client'
export { useInstanceQuery, instanceQueryKey } from './queries'
export { useUpdateInstanceMutation } from './mutations'
