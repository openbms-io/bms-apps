# Story 1.4: 223P Mapping Popup Modal Component

**Epic:** Epic 1 - 223P Mapping UI with Mock DTOs
**Status:** done
**Created:** 2025-11-02
**Completed:** 2025-11-02
**Complexity:** 8 (Large)
**Estimated Hours:** 6-8 hours

---

## User Story

**As a** BMS integrator,
**I want** a 223P mapping popup that appears when I drag a BACnet point onto the canvas,
**So that** semantic tagging is embedded in my normal workflow.

---

## Acceptance Criteria

Reference: Tech Spec AC-4

### 1. ✅ Automatic Trigger

- Popup opens automatically when BACnet point dropped onto React Flow canvas
- Modal appears <100ms after drop event (empty shell)
- AI suggestions populate progressively within 500ms

### 2. ✅ Point Context Display

- Shows: Point name, description (if available), present value, units, object type
- Example: "VAV-2-01_ZoneTemp | analog-input | 72.3°F"
- Formatted as card at top of modal

### 3. ✅ Dropdown Pre-fill

- Equipment type dropdown: Pre-filled with AI suggestion, confidence badge visible
- Space name field: Pre-filled with AI suggestion (optional)
- Device type dropdown: Pre-filled with AI suggestion, confidence badge visible
- Observable property dropdown: Pre-filled with AI suggestion, confidence badge visible

### 4. ✅ Confidence Indicators

- Each dropdown shows confidence % next to AI suggestion
- Overall confidence bar at bottom: "Overall AI Confidence: ████████████░░ 94%"
- Color coding: Green (>80%), Yellow (60-80%), Red (<60%)

### 5. ✅ User Actions

- **[Confirm]** button: Saves mapping → closes modal → adds point to canvas → shows badge
- Space selection is **optional** - user can confirm mapping without selecting a space
- **[Skip]** button: Closes modal → adds point to canvas (no mapping, no badge)
- **ESC key**: Same as Skip button
- Manual dropdown override allowed before confirming

### 6. ✅ UI Framework

- Uses shadcn/ui `Dialog` component
- Uses shadcn/ui `Select` components for dropdowns
- Modal is centered, overlay dims background
- Responsive width (max 600px)

---

## Verification Checklist

**Modal Behavior:**

- [ ] Modal opens on point drop event
- [ ] Modal appears within 100ms (empty shell)
- [ ] AI suggestions populate within 500ms
- [ ] Modal closes on Confirm
- [ ] Modal closes on Skip
- [ ] Modal closes on ESC key

**Point Context:**

- [ ] Point name displayed
- [ ] Object type displayed
- [ ] Present value and units displayed (if available)
- [ ] Description displayed (if available)

**Dropdowns:**

- [ ] Equipment type dropdown pre-filled with AI suggestion
- [ ] Device type dropdown pre-filled with AI suggestion
- [ ] Observable property dropdown pre-filled with AI suggestion
- [ ] Space name field pre-filled with AI suggestion (if available)
- [ ] All dropdowns functional and can be manually changed

**Confidence Indicators:**

- [ ] Confidence % shown next to each dropdown
- [ ] Overall confidence bar at bottom
- [ ] Color coding correct (green >80%, yellow 60-80%, red <60%)

**Keyboard Accessibility:**

- [ ] Tab key navigates through dropdowns and buttons
- [ ] ESC key closes modal
- [ ] Enter key on Confirm button saves mapping

**Integration:**

- [ ] AI suggestion service called on modal open
- [ ] Mapping saved to sessionStorage on Confirm
- [ ] No mapping saved on Skip

---

## Implementation Guidance

### File Structure

```
apps/designer/src/domains/223p/
├── components/
│   ├── mapping-popup-modal.tsx           # Main modal component
│   ├── point-context-card.tsx            # Point info display
│   ├── confidence-indicator.tsx          # Confidence badge component
│   └── overall-confidence-bar.tsx        # Bottom confidence bar
└── hooks/
    └── use-223p-mapping.ts               # Hook for AI suggestions and state
```

### Component Architecture

```typescript
// components/mapping-popup-modal.tsx

interface MappingPopupModalProps {
  open: boolean;
  point: BACnetPointDTO;
  onConfirm: (mapping: Equipment223PDTO) => void;
  onSkip: () => void;
  onOpenChange: (open: boolean) => void;
}

export function MappingPopupModal({
  open,
  point,
  onConfirm,
  onSkip,
  onOpenChange,
}: MappingPopupModalProps) {
  // 1. Get AI suggestions
  const suggestion = mockAISuggestionService.suggestMapping(point);

  // 2. Form state
  const [equipmentType, setEquipmentType] = useState(suggestion.equipmentType.value);
  const [deviceType, setDeviceType] = useState(suggestion.deviceType.value);
  const [property, setProperty] = useState(suggestion.observableProperty.value);
  const [spaceName, setSpaceName] = useState(suggestion.space?.value.label);

  // 3. Handle Confirm
  const handleConfirm = () => {
    const mapping: Equipment223PDTO = {
      equipmentType,
      deviceType,
      observableProperty: property,
      propertyType: 'quantifiable', // Infer from property
      externalReference: {
        objectName: point.name,
        objectIdentifier: point.objectType,
      },
      schemaVersion: '223p-2023',
    };
    onConfirm(mapping);
  };

  return (
    <Dialog open={open} onOpenChange={onOpenChange}>
      <DialogContent className="max-w-2xl">
        <DialogHeader>
          <DialogTitle>Tag BACnet Point with ASHRAE 223P</DialogTitle>
        </DialogHeader>

        {/* Point Context Card */}
        <PointContextCard point={point} />

        {/* Form Fields */}
        <div className="space-y-4">
          {/* Equipment Type Dropdown */}
          <div>
            <Label>Equipment Type</Label>
            <Select value={equipmentType} onValueChange={setEquipmentType}>
              {/* ... options */}
            </Select>
            <ConfidenceIndicator
              confidence={suggestion.equipmentType.confidence}
            />
          </div>

          {/* Device Type Dropdown */}
          {/* ... */}

          {/* Observable Property Dropdown */}
          {/* ... */}

          {/* Space Name (Optional) */}
          {/* ... */}
        </div>

        {/* Overall Confidence Bar */}
        <OverallConfidenceBar confidence={suggestion.overallConfidence} />

        {/* Actions */}
        <DialogFooter>
          <Button variant="outline" onClick={onSkip}>Skip</Button>
          <Button onClick={handleConfirm}>Confirm</Button>
        </DialogFooter>
      </DialogContent>
    </Dialog>
  );
}
```

### Point Context Card

```typescript
// components/point-context-card.tsx

interface PointContextCardProps {
  point: BACnetPointDTO;
}

export function PointContextCard({ point }: PointContextCardProps) {
  return (
    <Card>
      <CardContent className="pt-6">
        <div className="space-y-2">
          <div className="font-semibold text-lg">{point.name}</div>
          <div className="text-sm text-muted-foreground space-x-2">
            <span className="inline-flex items-center">
              <Badge variant="outline">{point.objectType}</Badge>
            </span>
            {point.presentValue && (
              <span>
                {point.presentValue}
                {point.units && ` ${point.units}`}
              </span>
            )}
          </div>
          {point.description && (
            <div className="text-sm text-muted-foreground">
              {point.description}
            </div>
          )}
        </div>
      </CardContent>
    </Card>
  );
}
```

### Confidence Indicator

```typescript
// components/confidence-indicator.tsx

interface ConfidenceIndicatorProps {
  confidence: number;
}

export function ConfidenceIndicator({ confidence }: ConfidenceIndicatorProps) {
  const variant = confidence > 80 ? 'success' : confidence > 60 ? 'warning' : 'destructive';

  return (
    <div className="flex items-center gap-2 mt-1">
      <Badge variant={variant} className="text-xs">
        AI: {confidence}%
      </Badge>
    </div>
  );
}
```

### Overall Confidence Bar

```typescript
// components/overall-confidence-bar.tsx

interface OverallConfidenceBarProps {
  confidence: number;
}

export function OverallConfidenceBar({ confidence }: OverallConfidenceBarProps) {
  const color = confidence > 80 ? 'bg-green-500' : confidence > 60 ? 'bg-yellow-500' : 'bg-red-500';

  return (
    <div className="space-y-2">
      <div className="text-sm font-medium">
        Overall AI Confidence: {confidence}%
      </div>
      <div className="w-full bg-secondary rounded-full h-2">
        <div
          className={`${color} h-2 rounded-full transition-all`}
          style={{ width: `${confidence}%` }}
        />
      </div>
    </div>
  );
}
```

---

## Technical Notes

### Integration with React Flow

Epic 1: Modal triggered manually for demo purposes

```typescript
// In React Flow component
const [showMappingModal, setShowMappingModal] = useState(false);
const [selectedPoint, setSelectedPoint] = useState<BACnetPointDTO | null>(null);

// Temporary: Button to open modal
<Button onClick={() => {
  setSelectedPoint({ name: 'VAV-2-01_ZoneTemp', objectType: 'analog-input' });
  setShowMappingModal(true);
}}>
  Test Mapping Modal
</Button>

<MappingPopupModal
  open={showMappingModal}
  point={selectedPoint!}
  onConfirm={(mapping) => {
    // Save to sessionStorage
    sessionStorage.setItem(`223p-${selectedPoint.name}`, JSON.stringify(mapping));
    setShowMappingModal(false);
  }}
  onSkip={() => setShowMappingModal(false)}
  onOpenChange={setShowMappingModal}
/>
```

Epic 2: Modal triggered automatically on point drop

```typescript
// In React Flow component
const onDrop = (event: React.DragEvent) => {
  const pointData = JSON.parse(event.dataTransfer.getData("application/json"));
  setSelectedPoint(pointData);
  setShowMappingModal(true); // Auto-open modal
};
```

### AI Suggestion Performance

- AI suggestion service is synchronous (mock data)
- No async operations, so suggestions appear instantly
- Modal can render immediately with pre-filled values
- No loading spinners needed for Epic 1

### Form State Management

**Epic 1: Local component state (useState)**

- Simple, no external state management needed
- Mapping saved to sessionStorage on Confirm

**Epic 2-6: Consider React Hook Form**

- If validation becomes complex
- If form has many fields

### Keyboard Accessibility

shadcn/ui Dialog provides:

- ESC key to close (built-in)
- Focus trap (Tab cycles through modal elements)
- Return focus to trigger on close

Additional accessibility:

- All form fields have labels
- Confidence indicators have aria-labels
- Buttons have clear text

---

## Prerequisites

**Story 1.3** ✅ Complete

- Requires: `mockAISuggestionService.suggestMapping()`

**Story 1.2** ✅ Complete

- Requires: `mockBuildingMOTIFService` for dropdown options

**Story 1.1** ✅ Complete

- Requires: `Equipment223PDTO`, `BACnetPointDTO` types

**shadcn/ui components:**

- Dialog (likely already installed)
- Select (likely already installed)
- Card, Badge, Button (likely already installed)
- Label (for form fields)

---

## Dependencies

**Stories that depend on this:**

- Story 1.5: Equipment Type Dropdown with Search (enhances dropdown)
- Story 1.6: Device Type and Property Dropdowns (enhances dropdowns)
- Story 1.7: SHACL Validation Mock (adds validation)
- Story 1.8: Left Panel 223P Metadata Badges (uses saved mappings)

---

## Definition of Done

- [ ] MappingPopupModal component created
- [ ] PointContextCard component created
- [ ] ConfidenceIndicator component created
- [ ] OverallConfidenceBar component created
- [ ] AI suggestions pre-fill all dropdowns
- [ ] Confidence scores displayed for each field
- [ ] Overall confidence bar at bottom
- [ ] Confirm button saves mapping to sessionStorage
- [ ] Skip button closes modal without saving
- [ ] ESC key closes modal
- [ ] Tab key navigates through form fields
- [ ] Modal responsive (max 600px width)
- [ ] TypeScript compiles without errors
- [ ] Component follows shadcn/ui patterns
- [ ] Code follows project conventions
- [ ] Manual test with sample point data successful
- [ ] Files committed to git with descriptive commit message

---

## References

- **Tech Spec:** AC-4 (lines 2547-2593)
- **Story 1.3:** AI Suggestion Mock Engine
- **Story 1.2:** Mock BuildingMOTIF Service
- **shadcn/ui Dialog:** https://ui.shadcn.com/docs/components/dialog
- **shadcn/ui Select:** https://ui.shadcn.com/docs/components/select
