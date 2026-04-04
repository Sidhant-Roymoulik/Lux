# TODO

Ranked by logical dependency and impact.

## 1. Fix Claude Code build/run environment
- [x] Claude cannot invoke `make` or run the compiled binary reliably in this session
- [x] Needed for: verifying bench counts, running search tests, iterative development
- [x] Root causes: (1) MSYS2 Make doesn't inherit `OS` env var, so temp dir defaults to `C:\WINDOWS\` — fixed via `cygpath` detection. (2) Dev builds needed `-static` to find MinGW DLLs at runtime.

## 2. Add unit tests
- [ ] Test eval correctness (known positions, symmetry, material balance)
- [ ] Test TT probe/store and mate score normalization
- [ ] Test time manager edge cases (movestogo, movetime, increment)
- [ ] Add to CI pipeline

## 3. Rework time manager
- [ ] Add soft/hard time limits (currently only hard limit at `time/30`)
- [ ] Scale time usage based on search instability / score change between iterations
- [ ] Re-test with OpenBench after changes

## 4. Refactor / cleanup
- [ ] Audit and clean up `eval.cpp` (tapered eval, EvalInfo usage)
- [ ] Review move ordering in `move_score.h`
- [ ] General code hygiene pass
