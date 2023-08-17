package engine

import (
	"Lux/dragontoothmg"
	"math/bits"
)

func Evaluate(board *dragontoothmg.Board) int16 {

	turn := 0
	if board.Wtomove {
		turn = 1
	}

	score := [2]int16{}

	score[0] += int16(bits.OnesCount64(board.Black.Pawns)) * 100
	score[0] += int16(bits.OnesCount64(board.Black.Knights)) * 300
	score[0] += int16(bits.OnesCount64(board.Black.Bishops)) * 300
	score[0] += int16(bits.OnesCount64(board.Black.Rooks)) * 500
	score[0] += int16(bits.OnesCount64(board.Black.Queens)) * 900

	score[1] += int16(bits.OnesCount64(board.White.Pawns)) * 100
	score[1] += int16(bits.OnesCount64(board.White.Knights)) * 300
	score[1] += int16(bits.OnesCount64(board.White.Bishops)) * 300
	score[1] += int16(bits.OnesCount64(board.White.Rooks)) * 500
	score[1] += int16(bits.OnesCount64(board.White.Queens)) * 900

	return score[turn] - score[turn^1]
}
