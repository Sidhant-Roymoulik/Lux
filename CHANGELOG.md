# Changelog

All notable changes to Lux are documented here.
Format based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

### Added
- Evaluation benchmarking (`bencheval` command)

### Changed
- Tuned eval constants using lichess-big3-resolved dataset
- Refactored print statements and simplified search classes
- Improved UCI `setoption` handling
- Moved Makefile to repo root

### Fixed
- Corrected time calculations in `Time_Manager`
- Fixed feature flags regression introduced after 4.2

---

## [4.2]

### Changed
- Updated CCRL ratings in README

---

## [4.1]

### Changed
- Tuned HCE values without normalization (+110 Elo)

---

## [4.0]

### Added
- Major eval and search overhaul (see README feature list)

---

## [3.5]

### Changed
- Minor tuning and README updates

---

## [3.4]

### Changed
- Optimized boolean check ordering in search

---

## [3.3]

### Added
- History move pruning

---

## [3.2]

### Changed
- Internal refactoring and version bump

---

## [3.1]

### Added
- Late Move Reductions (LMR)

---

## [3.0]

### Added
- Null move pruning

---

## [2.3]

### Added
- History heuristic for move ordering

---

## [2.2]

### Fixed
- Corrected TT flag calculation

---

## [2.1]

### Added
- Reverse futility pruning (RFP)

---

## [2.0]

### Added
- Version 2.0 — transposition table, quiescence search, aspiration windows

---

## [1.0]

### Added
- Initial release — alpha-beta negamax with iterative deepening and piece-square tables
