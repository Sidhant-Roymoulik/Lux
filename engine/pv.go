package engine

import (
	"Lux/dragontoothmg"
	"strings"
)

// A struct representing a principal variation line.
type PV_Line struct {
	Moves []dragontoothmg.Move
}

// Clear the principal variation line.
func (pvLine *PV_Line) Clear() {
	pvLine.Moves = nil
}

// Update the principal variation line with a new best move,
// and a new line of best play after the best move.
func (pvLine *PV_Line) Update(move dragontoothmg.Move, newPVLine PV_Line) {
	pvLine.Clear()
	pvLine.Moves = append(pvLine.Moves, move)
	pvLine.Moves = append(pvLine.Moves, newPVLine.Moves...)
}

// Get the best move from the principal variation line.
func (pvLine *PV_Line) GetPVMove() dragontoothmg.Move {
	return pvLine.Moves[0]
}

// Convert the principal variation line to a string.
func (pvLine PV_Line) String() string {
	pv := strings.Builder{}
	for i := 0; i < len(pvLine.Moves); i++ {
		move := pvLine.Moves[i]
		// if move == NullMove {
		// 	break
		// }
		pv.WriteString(move.String())
		pv.WriteString(" ")
	}
	return pv.String()
}
