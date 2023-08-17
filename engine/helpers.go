package engine

import (
	"fmt"
	"math/bits"
)

func getMateOrCPScore(score int16) string {
	if score > MATE_CUTOFF {
		pliesToMate := CHECKMATE_VALUE - score
		mateInN := (pliesToMate / 2) + (pliesToMate % 2)
		return fmt.Sprintf("mate %d", mateInN)
	} else if score < -MATE_CUTOFF {
		pliesToMate := -CHECKMATE_VALUE - score
		mateInN := (pliesToMate / 2) + (pliesToMate % 2)
		return fmt.Sprintf("mate %d", mateInN)
	}

	return fmt.Sprintf("cp %d", score)
}

func ClearBit(bb uint64, sq uint8) uint64 {
	bb &= ^(0x1 << sq)
	return bb
}

func Msb(bb uint64) uint8 {
	return uint8(bits.TrailingZeros64(bb))
}

func PopBit(bb uint64) uint64 {
	sq := Msb(bb)
	return ClearBit(bb, sq)
}

func CountBits(bb uint64) int16 {
	return int16(bits.OnesCount64(bb))
}
