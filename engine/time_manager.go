package engine

import (
	"time"
)

const (
	NoValue      int64 = 0
	InfiniteTime int64 = -1
)

type TimeManager struct {
	// Fields for UCI go command arguments
	TimeLeft     int64
	Increment    int64
	MoveTime     int64
	MovesToGo    int16
	MaxNodeCount uint64
	MaxDepth     int8

	// Fields to calculate when the search should be stopped.
	stop        bool
	TimeForMove int64
	stopTime    time.Time
}

func (tm *TimeManager) Setup(timeLeft, increment, moveTime int64,
	movesToGo int16, maxDepth int8, maxNodeCount uint64) {

	tm.TimeLeft = timeLeft
	tm.Increment = increment
	tm.MovesToGo = movesToGo
	tm.MoveTime = moveTime
	tm.MaxDepth = maxDepth
	tm.MaxNodeCount = maxNodeCount
}

func (tm *TimeManager) ForceStop() {
	tm.stop = true
}

func (tm *TimeManager) IsStopped() bool {
	return tm.stop
}

func (tm *TimeManager) Start(gamePly uint16) {
	tm.stop = false

	if tm.MoveTime != NoValue {
		tm.stopTime = time.Now().Add(time.Duration(tm.MoveTime) * time.Millisecond)
		tm.TimeLeft = NoValue
		return
	}

	if tm.TimeLeft == InfiniteTime {
		return
	}

	if int64(tm.MovesToGo) != NoValue {
		tm.TimeForMove = tm.TimeLeft / int64(tm.MovesToGo)
	} else {
		// Otherwise, calculate the amount of remaining time that will
		// be used by spending more time as the game progresses,
		// assuming that the longer the game continues, the quicker
		// it will end from the current position. Make sure we have
		// an increment though, otherwise we'll likely lose on time
		// doing this approach.
		if tm.Increment > 0 {
			tm.TimeForMove = tm.TimeLeft / max(10, 40-int64(gamePly))
		} else {
			tm.TimeForMove = tm.TimeLeft / 40
		}
	}

	// Give an bonus from the increment
	tm.TimeForMove += (3 * tm.Increment) / 4

	// If the increment bonus puts us outside of the actual time we
	// have left, use the time we have left minus 150ms.
	if tm.TimeForMove >= tm.TimeLeft {
		tm.TimeForMove = tm.TimeLeft - 150
	}

	// If taking away 150ms puts us at orbelow zero, use 100ms
	// to just get a move to return.
	if tm.TimeForMove <= 0 {
		tm.TimeForMove = 100
	}

	tm.stopTime = time.Now().Add(time.Duration(tm.TimeForMove) * time.Millisecond)
}

func (tm *TimeManager) CheckIfTimeIsUp() {
	if tm.stop {
		return
	}

	if tm.TimeLeft == InfiniteTime {
		return
	}

	if time.Now().After(tm.stopTime) {
		tm.stop = true
	}
}
