package engine

import (
	"Lux/dragontoothmg"
	"fmt"
	"time"
)

const (
	CHECKMATE_VALUE int16 = 20000
	MATE_CUTOFF     int16 = CHECKMATE_VALUE / 2
	MAX_DEPTH       int16 = 100
)

type Search struct {
	board dragontoothmg.Board
	timer TimeManager

	nodes uint64
}

func (search *Search) Run() (best_move dragontoothmg.Move) {

	pv := PV_Line{}
	search.nodes = 0
	start_time := time.Now()
	search.timer.Start(search.board.Fullmoveno * 2)

	for depth := int16(1); depth < MAX_DEPTH; depth++ {

		score := search.Negamax(depth, 0, &pv)

		if search.timer.Stop {
			break
		}

		total_time := time.Since(start_time).Milliseconds() + 1

		fmt.Printf(
			"info depth %d score %s nodes %d nps %d time %d pv %s\n",
			depth,
			getMateOrCPScore(score),
			search.nodes,
			int64(search.nodes*1000)/total_time,
			total_time,
			pv,
		)
	}

	return pv.GetPVMove()
}

func (search *Search) Negamax(depth int16, ply int16, pv *PV_Line) int16 {

	search.nodes++

	// println(search.nodes)

	if ply == int16(search.timer.MaxDepth) {
		return Evaluate(&search.board)
	}

	if depth <= 0 {
		// search.nodes--
		return Evaluate(&search.board)
	}

	if search.nodes >= search.timer.MaxNodeCount {
		search.timer.Stop = true
	}
	if (search.nodes & 0x7FF) == 0 {
		search.timer.Check()
	}
	if search.timer.Stop && ply > 0 {
		return 0
	}

	moves := search.board.GenerateLegalMoves()

	child_pv := PV_Line{}
	best_score := -CHECKMATE_VALUE
	// best_move := moves[0]

	for _, move := range moves {

		Unapply := search.board.Apply(move)
		score := -search.Negamax(depth-1, ply+1, &child_pv)
		Unapply()

		if score > best_score {
			best_score = score
			// best_move = move

			pv.Update(move, child_pv)
		}

		child_pv.Clear()
	}

	if len(moves) == 0 {
		if search.board.OurKingInCheck() {
			return ply - CHECKMATE_VALUE
		}
		return 0
	}

	return best_score
}
