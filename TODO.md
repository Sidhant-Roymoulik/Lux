# TODO

Ranked by logical dependency and impact.

## 1. Add unit tests
- [ ] Test eval correctness (known positions, symmetry, material balance)
- [ ] Test TT probe/store and mate score normalization
- [ ] Test time manager edge cases (movestogo, movetime, increment)
- [ ] Add to CI pipeline

## 2. Fix PV truncation at draw conditions
- [x] Stop PV extraction when fifty-move rule (or other draw) is hit
- [x] Verify PV does not include moves past a terminal node
- [x] Confirmed occurring in practice: engine reports score cp 61 with PV extending well past fifty-move rule trigger (warning logged by OpenBench)
- [x] Also confirmed with threefold repetition: score cp 0 but PV cycles through repeated positions (e.g. f5e3 d1e1 e3f5 e1d1 loop)

## 3. Rework time manager
- [ ] Add soft/hard time limits (currently only hard limit at `time/30`)
- [ ] Scale time usage based on search instability / score change between iterations
- [ ] Re-test with OpenBench after changes

## 4. Refactor / cleanup
- [ ] Audit and clean up `eval.cpp` (tapered eval, EvalInfo usage)
- [ ] Review move ordering in `move_score.h`
- [ ] General code hygiene pass
