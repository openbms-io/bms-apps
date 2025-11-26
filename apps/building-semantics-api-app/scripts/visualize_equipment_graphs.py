"""
Visualize equipment graphs from JSON extraction output.
Creates Mermaid diagrams for each equipment type.
"""

import json
from pathlib import Path
from collections import defaultdict

# Load the JSON
json_path = Path(__file__).parent / "graph_extraction_output_improved.json"
with open(json_path) as f:
    graph_data = json.load(f)

nodes = {node["id"]: node for node in graph_data["nodes"]}
edges = graph_data["edges"]

# Find all equipment nodes
equipment_nodes = [node for node in graph_data["nodes"] if node["type"] == "equipment"]

# Open output file
output_path = Path(__file__).parent / "equipment_graphs_visualization.md"
output = open(output_path, "w")

output.write("="*80 + "\n")
output.write(f"EQUIPMENT GRAPHS VISUALIZATION\n")
output.write("="*80 + "\n")
output.write(f"\nTotal equipment found: {len(equipment_nodes)}\n\n")

# For each equipment, build its subgraph
for eq in equipment_nodes:
    eq_id = eq["id"]
    eq_label = eq["label"]
    eq_class = eq["rdfClass"]

    output.write("\n" + "="*80 + "\n")
    output.write(f"Equipment: {eq_label} ({eq_class})\n")
    output.write(f"URI: {eq_id}\n")
    output.write("="*80 + "\n")

    # Find all edges connected to this equipment
    outgoing_edges = [e for e in edges if e["source"] == eq_id]
    incoming_edges = [e for e in edges if e["target"] == eq_id]

    # Categorize connected nodes
    devices = []
    properties = []
    connection_points = []
    external_refs = []  # Direct external refs from equipment
    property_external_refs = []  # External refs from properties (nested)
    other = []

    for edge in outgoing_edges:
        target_id = edge["target"]
        if target_id in nodes:
            target = nodes[target_id]
            predicate = edge["property"]

            if target["type"] == "device":
                devices.append((predicate, target))
            elif target["type"] == "property":
                properties.append((predicate, target))
            elif target["type"] == "connectionpoint":
                connection_points.append((predicate, target))
            elif target["type"] == "externalreference":
                external_refs.append((predicate, target))
            else:
                other.append((predicate, target))

    # Pre-scan for property-level external references (for accurate count in summary)
    for pred, dev in devices:
        dev_edges = [e for e in edges if e["source"] == dev["id"]]
        for dev_edge in dev_edges:
            target_id = dev_edge["target"]
            if target_id in nodes and nodes[target_id]["type"] == "property":
                # Check if this property has external references
                prop_edges = [e for e in edges if e["source"] == target_id]
                for prop_edge in prop_edges:
                    prop_target_id = prop_edge["target"]
                    if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                        property_external_refs.append((prop_edge["property"], nodes[prop_target_id]))

    # Also check connection points for properties (handles mis-categorized devices)
    for pred, cp in connection_points:
        cp_edges = [e for e in edges if e["source"] == cp["id"]]
        for cp_edge in cp_edges:
            target_id = cp_edge["target"]
            if target_id in nodes and nodes[target_id]["type"] == "property":
                # Check if this property has external references
                prop_edges = [e for e in edges if e["source"] == target_id]
                for prop_edge in prop_edges:
                    prop_target_id = prop_edge["target"]
                    if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                        property_external_refs.append((prop_edge["property"], nodes[prop_target_id]))

    # Also check direct equipment properties for external refs
    for pred, prop in properties:
        prop_edges = [e for e in edges if e["source"] == prop["id"]]
        for prop_edge in prop_edges:
            prop_target_id = prop_edge["target"]
            if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                property_external_refs.append((prop_edge["property"], nodes[prop_target_id]))

    # Print summary
    total_external_refs = len(external_refs) + len(property_external_refs)
    output.write(f"\nConnected components:\n")
    output.write(f"  - Devices: {len(devices)}\n")
    output.write(f"  - Properties: {len(properties)}\n")
    output.write(f"  - Connection Points: {len(connection_points)}\n")
    output.write(f"  - External References: {total_external_refs}")
    if property_external_refs:
        output.write(f" ({len(property_external_refs)} at property level)\n")
    else:
        output.write("\n")

    # Create Mermaid diagram
    output.write(f"\n### Mermaid Diagram:\n\n")
    output.write("```mermaid\n")
    output.write("graph TD\n")

    # Equipment node (root)
    eq_node_id = "EQ"
    output.write(f"    {eq_node_id}[\"{eq_label}<br/>{eq_class.split(':')[-1]}\"]\n")
    output.write(f"    style {eq_node_id} fill:#ff9999,stroke:#333,stroke-width:3px\n")

    # Devices
    for i, (pred, dev) in enumerate(devices):
        dev_id = f"DEV{i}"
        dev_label = dev["label"].replace('"', "'")
        dev_class = dev["rdfClass"].split(":")[-1]
        output.write(f"    {dev_id}[\"{dev_label}<br/>{dev_class}\"]\n")
        output.write(f"    style {dev_id} fill:#99ccff,stroke:#333,stroke-width:2px\n")
        pred_label = pred.split(":")[-1]
        output.write(f"    {eq_node_id} -->|{pred_label}| {dev_id}\n")

        # Find device's properties and connection points
        dev_edges = [e for e in edges if e["source"] == dev["id"]]
        for j, dev_edge in enumerate(dev_edges):
            target_id = dev_edge["target"]
            if target_id in nodes:
                target = nodes[target_id]
                target_pred = dev_edge["property"].split(":")[-1]

                if target["type"] == "property":
                    prop_id = f"DEV{i}_PROP{j}"
                    prop_label = target["label"].replace('"', "'")[:30]
                    prop_class = target["rdfClass"].split(":")[-1]
                    output.write(f"    {prop_id}[\"{prop_label}<br/>{prop_class}\"]\n")
                    output.write(f"    style {prop_id} fill:#ffff99,stroke:#333,stroke-width:1px\n")
                    output.write(f"    {dev_id} -->|{target_pred}| {prop_id}\n")

                    # Check if this property has external references
                    prop_edges = [e for e in edges if e["source"] == target_id]
                    for k, prop_edge in enumerate(prop_edges):
                        prop_target_id = prop_edge["target"]
                        if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                            ext_ref = nodes[prop_target_id]
                            ext_ref_id = f"DEV{i}_PROP{j}_REF{k}"
                            ext_ref_label = ext_ref["label"].replace('"', "'")[:30]
                            ext_ref_class = ext_ref["rdfClass"].split(":")[-1]
                            ext_ref_pred = prop_edge["property"].split(":")[-1]

                            output.write(f"    {ext_ref_id}[\"{ext_ref_label}<br/>{ext_ref_class}\"]\n")
                            output.write(f"    style {ext_ref_id} fill:#ffccff,stroke:#333,stroke-width:1px\n")
                            output.write(f"    {prop_id} -->|{ext_ref_pred}| {ext_ref_id}\n")

                elif target["type"] == "connectionpoint":
                    cp_id = f"DEV{i}_CP{j}"
                    cp_label = target["label"].replace('"', "'")[:30]
                    cp_class = target["rdfClass"].split(":")[-1]
                    output.write(f"    {cp_id}[\"{cp_label}<br/>{cp_class}\"]\n")
                    output.write(f"    style {cp_id} fill:#99ff99,stroke:#333,stroke-width:1px\n")
                    output.write(f"    {dev_id} -->|{target_pred}| {cp_id}\n")

    # Direct properties (equipment-level)
    for i, (pred, prop) in enumerate(properties):
        prop_id = f"PROP{i}"
        prop_label = prop["label"].replace('"', "'")[:30]
        prop_class = prop["rdfClass"].split(":")[-1]
        output.write(f"    {prop_id}[\"{prop_label}<br/>{prop_class}\"]\n")
        output.write(f"    style {prop_id} fill:#ffff99,stroke:#333,stroke-width:1px\n")
        pred_label = pred.split(":")[-1]
        output.write(f"    {eq_node_id} -->|{pred_label}| {prop_id}\n")

        # Check if this property has external references
        prop_edges = [e for e in edges if e["source"] == prop["id"]]
        for k, prop_edge in enumerate(prop_edges):
            prop_target_id = prop_edge["target"]
            if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                ext_ref = nodes[prop_target_id]
                ext_ref_id = f"PROP{i}_REF{k}"
                ext_ref_label = ext_ref["label"].replace('"', "'")[:30]
                ext_ref_class = ext_ref["rdfClass"].split(":")[-1]
                ext_ref_pred = prop_edge["property"].split(":")[-1]

                output.write(f"    {ext_ref_id}[\"{ext_ref_label}<br/>{ext_ref_class}\"]\n")
                output.write(f"    style {ext_ref_id} fill:#ffccff,stroke:#333,stroke-width:1px\n")
                output.write(f"    {prop_id} -->|{ext_ref_pred}| {ext_ref_id}\n")

    # Connection points (equipment-level)
    for i, (pred, cp) in enumerate(connection_points):
        cp_id = f"CP{i}"
        cp_label = cp["label"].replace('"', "'")[:30]
        cp_class = cp["rdfClass"].split(":")[-1]
        output.write(f"    {cp_id}[\"{cp_label}<br/>{cp_class}\"]\n")
        output.write(f"    style {cp_id} fill:#99ff99,stroke:#333,stroke-width:1px\n")
        pred_label = pred.split(":")[-1]
        output.write(f"    {eq_node_id} -->|{pred_label}| {cp_id}\n")

        # Check for properties with external refs (handles mis-categorized devices)
        cp_edges = [e for e in edges if e["source"] == cp["id"]]
        for j, cp_edge in enumerate(cp_edges):
            target_id = cp_edge["target"]
            if target_id in nodes:
                target = nodes[target_id]
                target_pred = cp_edge["property"].split(":")[-1]

                if target["type"] == "property":
                    prop_id = f"CP{i}_PROP{j}"
                    prop_label = target["label"].replace('"', "'")[:30]
                    prop_class = target["rdfClass"].split(":")[-1]
                    output.write(f"    {prop_id}[\"{prop_label}<br/>{prop_class}\"]\n")
                    output.write(f"    style {prop_id} fill:#ffff99,stroke:#333,stroke-width:1px\n")
                    output.write(f"    {cp_id} -->|{target_pred}| {prop_id}\n")

                    # Check if this property has external references
                    prop_edges = [e for e in edges if e["source"] == target_id]
                    for k, prop_edge in enumerate(prop_edges):
                        prop_target_id = prop_edge["target"]
                        if prop_target_id in nodes and nodes[prop_target_id]["type"] == "externalreference":
                            ext_ref = nodes[prop_target_id]
                            ext_ref_id = f"CP{i}_PROP{j}_REF{k}"
                            ext_ref_label = ext_ref["label"].replace('"', "'")[:30]
                            ext_ref_class = ext_ref["rdfClass"].split(":")[-1]
                            ext_ref_pred = prop_edge["property"].split(":")[-1]

                            output.write(f"    {ext_ref_id}[\"{ext_ref_label}<br/>{ext_ref_class}\"]\n")
                            output.write(f"    style {ext_ref_id} fill:#ffccff,stroke:#333,stroke-width:1px\n")
                            output.write(f"    {prop_id} -->|{ext_ref_pred}| {ext_ref_id}\n")

    # External references
    for i, (pred, ref) in enumerate(external_refs):
        ref_id = f"REF{i}"
        ref_label = ref["label"].replace('"', "'")[:30]
        ref_class = ref["rdfClass"].split(":")[-1]
        output.write(f"    {ref_id}[\"{ref_label}<br/>{ref_class}\"]\n")
        output.write(f"    style {ref_id} fill:#ffccff,stroke:#333,stroke-width:1px\n")
        pred_label = pred.split(":")[-1]
        output.write(f"    {eq_node_id} -->|{pred_label}| {ref_id}\n")

    output.write("```\n")

    # Print statistics
    output.write(f"\n### Component Details:\n\n")

    if devices:
        output.write(f"**Devices ({len(devices)}):**\n")
        for pred, dev in devices:
            output.write(f"  - {dev['label']} ({dev['rdfClass'].split(':')[-1]})\n")

    if properties:
        output.write(f"\n**Properties ({len(properties)}):**\n")
        for pred, prop in properties[:5]:  # Show first 5
            output.write(f"  - {prop['label']} ({prop['rdfClass'].split(':')[-1]})\n")
        if len(properties) > 5:
            output.write(f"  ... and {len(properties) - 5} more\n")

    if connection_points:
        output.write(f"\n**Connection Points ({len(connection_points)}):**\n")
        for pred, cp in connection_points[:5]:  # Show first 5
            output.write(f"  - {cp['label']} ({cp['rdfClass'].split(':')[-1]})\n")
        if len(connection_points) > 5:
            output.write(f"  ... and {len(connection_points) - 5} more\n")

    if property_external_refs:
        output.write(f"\n**External References ({len(property_external_refs)} at property level):**\n")
        for pred, ref in property_external_refs[:5]:  # Show first 5
            output.write(f"  - {ref['label']} ({ref['rdfClass'].split(':')[-1]})\n")
        if len(property_external_refs) > 5:
            output.write(f"  ... and {len(property_external_refs) - 5} more\n")

output.write("\n" + "="*80 + "\n")
output.write("VISUALIZATION COMPLETE\n")
output.write("="*80 + "\n")
output.write("\nLegend:\n")
output.write("  🟥 Red = Equipment\n")
output.write("  🟦 Blue = Device\n")
output.write("  🟨 Yellow = Property\n")
output.write("  🟩 Green = Connection Point\n")
output.write("  🟪 Purple = External Reference\n")
output.write("="*80 + "\n")

# Close output file
output.close()

print(f"\n✅ Visualization saved to: {output_path}")
