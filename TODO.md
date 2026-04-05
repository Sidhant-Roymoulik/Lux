# TODO

Ranked by logical dependency and impact.

## 1. SPSA tuning support (OpenBench integration)
- [ ] Expose search constants as UCI options for SPSA (eval is tuned separately via texel-tuner)
- [ ] Follow OpenBench SPSA parameter format (`name, dtype, value, min, max, c_end, r_end`)
- [ ] Wire tunable search params through `uci.cpp` option handling
- [ ] Verify OpenBench can pick up and vary the params correctly

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
