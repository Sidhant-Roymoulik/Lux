package engine

import (
	"Lux/dragontoothmg"
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

type UCIEngine struct {
	Search Search
}

func (e *UCIEngine) reset() {
	*e = UCIEngine{}
}

func (e *UCIEngine) uci() {
	fmt.Printf("id name %v\n", ENGINE_NAME)
	fmt.Printf("id author %v\n", ENGINE_AUTHOR)

	fmt.Print("\nAvailable UCI commands:\n")

	fmt.Print("    * uci\n    * isready\n    * ucinewgame")
	fmt.Print("\n    * setoption name <NAME> value <VALUE>")
	fmt.Print("\n    * position")
	fmt.Print("\n\t* fen <FEN>")
	fmt.Print("\n\t* startpos")
	fmt.Print("\n    * go")
	fmt.Print("\n\t* wtime <MILLISECONDS>\n\t* btime <MILLISECONDS>")
	fmt.Print("\n\t* winc <MILLISECONDS>\n\t* binc <MILLISECONDS>")
	fmt.Print("\n\t* movestogo <INTEGER>\n\t* depth <INTEGER>\n\t* nodes <INTEGER>\n\t* movetime <MILLISECONDS>")
	fmt.Print("\n\t* infinite")

	fmt.Print("\n    * stop\n    * quit\n\n")
	fmt.Printf("uciok\n")
}

func (e *UCIEngine) setOption(command string) {
	fields := strings.Fields(command)
	var option, value string
	parsingWhat := ""

	for _, field := range fields {
		if field == "name" {
			parsingWhat = "name"
		} else if field == "value" {
			parsingWhat = "value"
		} else if parsingWhat == "name" {
			option += field + " "
		} else if parsingWhat == "value" {
			value += field + " "
		}
	}

	option = strings.TrimSuffix(option, " ")
	value = strings.TrimSuffix(value, " ")
}

func (e *UCIEngine) position(command string) {
	// parse position and moves from args
	// set position in engine
	args := strings.TrimPrefix(command, "position ")
	fen := ""

	if strings.HasPrefix(args, "startpos") {
		args = strings.TrimPrefix(args, "startpos ")
		fen = dragontoothmg.Startpos
	} else if strings.HasPrefix(args, "fen ") {
		args = strings.TrimPrefix(args, "startpos ")
		remaining_args := strings.Fields(args)
		fen = strings.Join(remaining_args[0:6], " ")
		args = strings.Join(remaining_args[6:], " ")
	}

	e.Search.board = dragontoothmg.ParseFen(fen)

	if strings.HasPrefix(args, "moves ") {
		args = strings.TrimSuffix(strings.TrimPrefix(args, "moves"), " ")
		if args != "" {
			for _, smove := range strings.Fields(args) {
				move, err := dragontoothmg.ParseMove(smove)
				if err != nil {
					panic(err)
				}
				e.Search.board.Apply(move)
			}
		}
	}
}

func (e *UCIEngine) Go(command string) {

	command = strings.TrimPrefix(command, "go")
	command = strings.TrimPrefix(command, " ")
	fields := strings.Fields(command)

	colorPrefix := "b"
	if e.Search.board.Wtomove {
		colorPrefix = "w"
	}

	// Parse the go command arguments.
	timeLeft, increment, movesToGo := int(InfiniteTime), int(NoValue), int(NoValue)
	maxDepth, maxNodeCount, moveTime := uint64(MAX_DEPTH), uint64(math.MaxUint64), uint64(NoValue)

	for index, field := range fields {
		if strings.HasPrefix(field, colorPrefix) {
			if strings.HasSuffix(field, "time") {
				timeLeft, _ = strconv.Atoi(fields[index+1])
			} else if strings.HasSuffix(field, "inc") {
				increment, _ = strconv.Atoi(fields[index+1])
			}
		} else if field == "movestogo" {
			movesToGo, _ = strconv.Atoi(fields[index+1])
		} else if field == "depth" {
			maxDepth, _ = strconv.ParseUint(fields[index+1], 10, 8)
		} else if field == "nodes" {
			maxNodeCount, _ = strconv.ParseUint(fields[index+1], 10, 64)
		} else if field == "movetime" {
			moveTime, _ = strconv.ParseUint(fields[index+1], 10, 64)
		}
	}

	// Setup the timer with the go command time control information.
	e.Search.timer.Setup(
		int64(timeLeft),
		int64(increment),
		int64(moveTime),
		int16(movesToGo),
		int8(maxDepth),
		maxNodeCount,
	)

	// Report the best move found by the engine to the GUI.
	_, best_move := e.Search.run()
	fmt.Printf("bestmove %v\n", best_move.String())
}

func (e *UCIEngine) quit() {
	// e.engine.uninitializeTT()
}

func (e *UCIEngine) loop() {
	reader := bufio.NewReader(os.Stdin)

	e.uci()
	e.reset()

	// e.engine.resizeTT(DefaultTTSize, SearchEntrySize)

	for {
		command, err := reader.ReadString('\n')
		if err != nil {
			panic(err)
		}
		command = strings.Replace(command, "\r\n", "\n", -1)

		if command == "uci\n" {
			e.uci()
		} else if command == "isready\n" {
			print("readyok")
		} else if strings.HasPrefix(command, "setoption") {
			e.setOption(command)
		} else if strings.HasPrefix(command, "ucinewgame") {
			e.reset()
		} else if strings.HasPrefix(command, "position") {
			e.position(command)
		} else if strings.HasPrefix(command, "go") {
			go e.Go(command)
		} else if strings.HasPrefix(command, "stop") {
			e.Search.timer.ForceStop()
		} else if command == "quit\n" {
			e.quit()
			break
		}
	}
}
