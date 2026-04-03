# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What This Is

Lux is a UCI-compatible chess engine written in C++. It implements standard chess engine techniques including alpha-beta negamax search with iterative deepening, a transposition table, quiescence search, and a handcrafted evaluation function with piece-square tables.

## Build Commands

The project uses a `Makefile` at the repo root. From the repo root:

```bash
make dev       # development build (warnings-as-errors, output to src/executables/)
make release   # optimized release build (multiple CPU variants)
make EXE=Lux   # OpenBench-compatible build (also the default target)
```

The compiled binary communicates via stdin/stdout using the UCI protocol. Connect it to a GUI like Cutechess or interact directly with UCI commands.

## Running / Debugging

Run the binary directly and type UCI commands:

```
uci
isready
position startpos
go depth 10
```

Debug commands available at runtime (not part of UCI spec):
- `print` — print the current board
- `eval` — print static evaluation of current position
- `bench` — run benchmark on 50 fixed positions at depth 10
- `bencheval` — benchmark eval speed in ns/call

`bench` can also be passed as a command-line argument (`./Lux bench`), which runs the benchmark and exits — this is how OpenBench invokes it.

## Code Architecture

All source lives in `src/`. Entry point is `main.cpp`, which calls `init_search_tables()`, `init_eval_tables()`, then `uci_loop()`.

**Key files and their roles:**

- `types.h` — foundational constants (`VERSION`, `MATE`, `MAX_PLY`, score packing via `S(mg, eg)`) and includes `chess.hpp`
- `chess.hpp` — third-party chess library (Disservin) providing `Board`, `Move`, bitboard types, move generation
- `uci.cpp` / `uci.h` — UCI protocol loop; owns the global `TranspositionTable* table` and `SearchThread`
- `search.h` / `search.cpp` — `SearchThread` struct (board + time manager + history), `iterative_deepening`, `negamax`, `q_search`, `aspiration_window`
- `tt.h` — `TranspositionTable` with `TTEntry` (key, score, eval, depth, flag, move); `score_to_tt`/`score_from_tt` for mate distance normalization
- `eval.h` / `eval.cpp` — `evaluate(board)` with tapered middlegame/endgame scoring via `EvalInfo`
- `eval_constants.h` — all PST and eval tuning constants using `S(mg, eg)` packed integers
- `time_manager.h` — `Time_Manager` struct for time control
- `thread.h` — `ThreadHandler` wraps `std::thread` to run `iterative_deepening` asynchronously
- `move_score.h` — move ordering logic (TT move, promotions, MVV-LVA, killers, history)
- `history.h` — history heuristic table `[piece][to_square]`
- `pv.h` — principal variation tracking
- `bench.h` — `StartBenchmark` and `StartEvalBenchmark` implementations; contains the 50 fixed bench FENs

**Score encoding:** Scores are packed middlegame/endgame pairs using `S(mg, eg)` in `types.h`. Extract with `mg_score(s)` and `eg_score(s)`. This is used throughout `eval_constants.h`.

**Eval initialization:** `init_eval_tables()` bakes material values directly into the PST arrays, so `pst[piece][sq]` already includes material. Do not add material separately when reading PSTs after init.

**Per-node state:** `SearchStack` (in `search.h`) holds ply, killer moves, current move, static eval, and move count for each ply in the search tree. It is stack-allocated and passed by pointer through the recursive search calls.

**Search flow:** `uci_loop` → `ThreadHandler::start` → `iterative_deepening<true>` (in a thread) → `aspiration_window` → `negamax` / `q_search`.

## Code Style

Formatting uses clang-format 17 based on Google style with 4-space indent and 120-column limit (see `.clang-format`). The CI format check is advisory (`continue-on-error: true`).

## OpenBench

Self-hosted OpenBench instance for SPRT testing. Server and all data live at `C:\Users\SidRo\Projects\OpenBench`. The database (`db.sqlite3`) persists all test results, users, and engine configs across restarts.

### Starting the server

```bash
cd C:\Users\SidRo\Projects\OpenBench
python manage.py runserver 0.0.0.0:8000
```

Web UI at http://localhost:8000. Admin panel at http://localhost:8000/admin/.

### Starting a worker (this machine)

```bash
cd C:\Users\SidRo\Projects\OpenBench\Client
python client.py -U <username> -P <password> -S http://localhost:8000 -T 1 -N 1 --no-client-downloads
```

Use `-T 1` on Windows — higher thread counts hit Python multiprocessing timeouts during bench. `--no-client-downloads` prevents the client from overwriting the local `bench.py` (which has `MAX_BENCH_TIME_SECONDS = 300`).

### Workers on other machines (LAN)

Find this machine's local IP (`ipconfig`), then on each worker machine:
```bash
python client.py -U <user> -P <pass> -S http://<local-ip>:8000 -T <threads> -N 1
```
For machines outside the LAN, use ngrok (`ngrok http 8000`) to get a public URL.

### Creating a test

1. Go to http://localhost:8000 → Create Test
2. Select Lux as both Dev and Base engine, set branches
3. The `Bench:` value autofills from the commit message — see convention below
4. Use the **STC** preset (8.0+0.08, SPRT elo0=0 elo1=5)

### Bench convention

Every commit that changes search or eval **must** include `Bench: <nodes>` in the commit message. OpenBench uses this to verify the binary is correct before running games.

Current bench count (main, depth 10, 50 positions): **5129387**

To get the bench count after making changes:
```bash
make dev                          # rebuild
.\src\executables\Lux.exe bench   # run via argv (not echo bench | Lux.exe)
```

**Important:** Always use `Lux.exe bench` (argv), not `echo bench | Lux.exe` (stdin). The two paths produce the same count now, but argv is what OpenBench actually calls.

### Build flag notes

- `-flto` is intentionally absent from all Makefile targets — it changes move ordering via inlining, producing different node counts than OpenBench worker builds
- `make dev` = local dev build with warnings, output to `src/executables/Lux.exe`
- `make EXE=<name>` (default target) = OpenBench build with `RFLAGS + -march=native`, output to bare `<name>`

### Engine config

`C:\Users\SidRo\Projects\OpenBench\Engines\Lux.json` — contains build config and STC/LTC test presets.
`C:\Users\SidRo\Projects\OpenBench\Config\config.json` — lists all active engines; Lux is included.

## Planned Work

See `TODO.md` at the repo root for the ranked list of in-progress and upcoming work.
