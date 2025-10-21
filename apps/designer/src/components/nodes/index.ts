import { BacnetNodeUI } from './bacnet-node-ui'
import { CalculationNode } from './calculation-node'
import { ComparisonNode } from './comparison-node'
import { WriteSetpointNode } from './write-setpoint-node'
import { ConstantNodeUI } from './constant-node-ui'
import { FunctionNode } from './function-node'
import { SwitchNode } from './switch-node'
import { TimerNode } from './timer-node'
import { ScheduleNode } from './schedule-node'
import { NodeType, NodeCategory } from '@/types/infrastructure'

// Strongly typed node types for React Flow
export const nodeTypes = {
  // BACnet nodes - all using unified UI
  [`${NodeCategory.BACNET}.${NodeType.ANALOG_INPUT}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.BINARY_INPUT}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.MULTISTATE_INPUT}`]: BacnetNodeUI,

  [`${NodeCategory.BACNET}.${NodeType.ANALOG_OUTPUT}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.BINARY_OUTPUT}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.MULTISTATE_OUTPUT}`]: BacnetNodeUI,

  [`${NodeCategory.BACNET}.${NodeType.ANALOG_VALUE}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.BINARY_VALUE}`]: BacnetNodeUI,
  [`${NodeCategory.BACNET}.${NodeType.MULTISTATE_VALUE}`]: BacnetNodeUI,

  // Logic nodes
  [`${NodeCategory.LOGIC}.${NodeType.CALCULATION}`]: CalculationNode,
  [`${NodeCategory.LOGIC}.${NodeType.COMPARISON}`]: ComparisonNode,
  [`${NodeCategory.LOGIC}.${NodeType.CONSTANT}`]: ConstantNodeUI,
  [`${NodeCategory.LOGIC}.${NodeType.FUNCTION}`]: FunctionNode,

  // Command nodes
  [`${NodeCategory.COMMAND}.${NodeType.WRITE_SETPOINT}`]: WriteSetpointNode,

  // Control flow nodes
  [`${NodeCategory.CONTROL_FLOW}.${NodeType.SWITCH}`]: SwitchNode,
  [`${NodeCategory.CONTROL_FLOW}.${NodeType.TIMER}`]: TimerNode,
  [`${NodeCategory.CONTROL_FLOW}.${NodeType.SCHEDULE}`]: ScheduleNode,
} as const
