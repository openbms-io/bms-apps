import type { TreeNode } from '@/types/infrastructure'

export function filterTreeNodes({
  nodes,
  searchTerm,
}: {
  nodes: TreeNode[]
  searchTerm: string
}): TreeNode[] {
  return nodes.reduce<TreeNode[]>((filtered, node) => {
    const nodeMatches =
      node.label.toLowerCase().includes(searchTerm) ||
      node.sublabel?.toLowerCase().includes(searchTerm)

    let filteredChildren: TreeNode[] = []
    if (node.children) {
      filteredChildren = filterTreeNodes({
        nodes: node.children,
        searchTerm,
      })
    }

    if (nodeMatches || filteredChildren.length > 0) {
      filtered.push({
        ...node,
        children: filteredChildren,
        isExpanded: filteredChildren.length > 0,
      })
    }

    return filtered
  }, [])
}
