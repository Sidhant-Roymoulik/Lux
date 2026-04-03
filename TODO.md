# TODO

Ranked by logical dependency and impact.

## 1. Add unit tests
- [ ] Test eval correctness (known positions, symmetry, material balance)
- [ ] Test TT probe/store and mate score normalization
- [ ] Test time manager edge cases (movestogo, movetime, increment)
- [ ] Add to CI pipeline

## 2. Fix PV truncation at draw conditions
- [ ] Stop PV extraction when fifty-move rule (or other draw) is hit
- [ ] Verify PV does not include moves past a terminal node

## 3. Rework time manager
- [ ] Add soft/hard time limits (currently only hard limit at `time/30`)
- [ ] Scale time usage based on search instability / score change between iterations
- [ ] Re-test with OpenBench after changes

## 4. Refactor / cleanup
- [ ] Audit and clean up `eval.cpp` (tapered eval, EvalInfo usage)
- [ ] Review move ordering in `move_score.h`
- [ ] General code hygiene pass
