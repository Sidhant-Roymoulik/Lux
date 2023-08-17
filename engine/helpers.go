package engine

import "fmt"

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
