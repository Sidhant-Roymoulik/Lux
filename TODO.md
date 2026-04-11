# TODO

Ranked by logical dependency and impact.

## 1. Add unit tests

- [ ] Test eval correctness (known positions, symmetry, material balance)
- [ ] Test TT probe/store and mate score normalization
- [ ] Test time manager edge cases (movestogo, movetime, increment)
- [ ] Add to CI pipeline

## 2. Multithreading (Lazy SMP)
- [ ] Implement Lazy SMP: run N copies of the search on the same position with shared TT
- [ ] Wire Threads UCI option through `handle_setoption` in `uci.cpp`
- [ ] Aggregate node counts across threads for accurate bench output
- [ ] Re-test with OpenBench after changes

## 3. Rework time manager

- [ ] Add soft/hard time limits (currently only hard limit at `time/30`)
- [ ] Scale time usage based on search instability / score change between iterations
- [ ] Re-test with OpenBench after changes
