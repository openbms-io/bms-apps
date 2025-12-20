import { screen, fireEvent } from '@testing-library/react'
import { renderWithProviders as render } from '@test-utils/render'
import userEvent from '@testing-library/user-event'
import { ControlSequencesSection } from './control-sequences-section'

describe('ControlSequencesSection', () => {
  describe('rendering', () => {
    it('renders section header', () => {
      render(<ControlSequencesSection />)

      expect(screen.getByText('Control Sequences')).toBeInTheDocument()
    })

    it('renders ASHRAE G36 subsection', () => {
      render(<ControlSequencesSection />)

      expect(screen.getByText('ASHRAE G36')).toBeInTheDocument()
    })

    it('renders G36 VAV Reheat item', () => {
      render(<ControlSequencesSection />)

      expect(screen.getByText('G36 VAV Reheat')).toBeInTheDocument()
    })

    it('renders expanded by default', () => {
      render(<ControlSequencesSection />)

      expect(screen.getByText('G36 VAV Reheat')).toBeVisible()
    })
  })

  describe('expand/collapse behavior', () => {
    it('collapses section when header is clicked', async () => {
      const user = userEvent.setup()
      render(<ControlSequencesSection />)

      const headerButton = screen.getByRole('button', {
        name: /control sequences/i,
      })
      await user.click(headerButton)

      expect(screen.queryByText('G36 VAV Reheat')).not.toBeInTheDocument()
    })

    it('expands section when collapsed header is clicked', async () => {
      const user = userEvent.setup()
      render(<ControlSequencesSection />)

      const headerButton = screen.getByRole('button', {
        name: /control sequences/i,
      })
      await user.click(headerButton)
      await user.click(headerButton)

      expect(screen.getByText('G36 VAV Reheat')).toBeVisible()
    })
  })

  describe('drag behavior', () => {
    it('sets correct drag data on drag start', () => {
      render(<ControlSequencesSection />)

      const draggableItem = screen.getByText('G36 VAV Reheat').closest('div')
      expect(draggableItem).toHaveAttribute('draggable', 'true')

      const setDataMock = jest.fn()
      const dataTransfer = {
        effectAllowed: '',
        setData: setDataMock,
      }

      fireEvent.dragStart(draggableItem!, {
        dataTransfer,
      })

      expect(dataTransfer.effectAllowed).toBe('copy')
      expect(setDataMock).toHaveBeenCalledWith(
        'application/json',
        JSON.stringify({
          type: 'control-sequence-node',
          nodeType: 'g36-vav-reheat',
          label: 'G36 VAV Reheat',
          metadata: {},
          draggedFrom: 'control-sequences-section',
        })
      )
    })

    it('item is draggable', () => {
      render(<ControlSequencesSection />)

      const draggableItem = screen.getByText('G36 VAV Reheat').closest('div')
      expect(draggableItem).toHaveAttribute('draggable', 'true')
    })
  })
})
