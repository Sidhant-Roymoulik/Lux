# TODO

Ranked by logical dependency and impact.

## 1. Setup proper SDLC
- [ ] Define branching strategy (feature branches, PR reviews)
- [ ] Establish versioning scheme and release process
- [ ] Document contribution/merge workflow

## 2. Setup OpenBench
- [ ] Register engine on an OpenBench instance
- [ ] Add OpenBench-compatible build target / worker script
- [ ] Establish baseline ELO before making changes

## 3. Add unit tests
- [ ] Test eval correctness (known positions, symmetry, material balance)
- [ ] Test TT probe/store and mate score normalization
- [ ] Test time manager edge cases (movestogo, movetime, increment)
- [ ] Add to CI pipeline

## 4. Upgrade chess library version
- [ ] Check Disservin/chess-library for updates
- [ ] Update `chess.hpp` and resolve any API changes
- [ ] Verify bench output unchanged

## 5. Rework time manager
- [ ] Add soft/hard time limits (currently only hard limit at `time/30`)
- [ ] Scale time usage based on search instability / score change between iterations
- [ ] Re-test with OpenBench after changes

## 6. Refactor / cleanup
- [ ] Audit and clean up `eval.cpp` (tapered eval, EvalInfo usage)
- [ ] Review move ordering in `move_score.h`
- [ ] General code hygiene pass
