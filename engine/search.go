package engine

import "Lux/dragontoothmg"

const (
	CHECKMATE_VALUE = 1000000
	MATE_CUTOFF     = CHECKMATE_VALUE / 2
	MAX_DEPTH       = 100
)

type Search struct {
	board dragontoothmg.Board
}

func (search Search) run() (score int, best_move dragontoothmg.Move) {
	return 0, search.board.GenerateLegalMoves()[0]
}
