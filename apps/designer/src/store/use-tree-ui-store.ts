import { create } from 'zustand'
import { createTreeUISlice, TreeUISlice } from './slices/tree-ui-slice'

export const useTreeUIStore = create<TreeUISlice>()((...a) => ({
  ...createTreeUISlice(...a),
}))
