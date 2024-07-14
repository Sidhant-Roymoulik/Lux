<div align="center">

  <img src="./img/logo_2.jfif" width="30%">
  <br>
  <br>
  <b><i>UCI-Compatible Chess Engine Built in C++</i></b>
  <br>
  <br>
  <b><i>Surely never been done before</i></b>
  <br>
  <br>

  ![Downloads][downloads-badge]
  [![License][license-badge]][license-link]
  
  [![Release][release-badge]][release-link]
  [![Commits][commits-badge]][commits-link]

</div>


## Rating
| Version | Estimated | [CCRL 40/15](https://computerchess.org.uk/ccrl/4040/) | [CCRL Blitz (2'+1")](https://www.computerchess.org.uk/ccrl/404/)  | [MCERL 1' + 0.6"](https://www.chessengeria.eu/mcerl)  |
|-------- |-----------|-------------------------------------------------------|-------------------------------------------------------------------|-------------------------------------------------------|
| 1.0     | 1700      | -                                                     | -                                                                 | 2026
| 2.0     | 1850      | -                                                     | -                                                                 | 2139
| 2.1     | 2000      | -                                                     | -                                                                 | 2256
| 2.2     | 2050      | -                                                     | -                                                                 | -
| 2.3     | 2100      | 2017                                                  | 2039                                                              | -
| 3.0     | 2200      | -                                                     | -                                                                 | 2498
| 3.1     | 2300      | -                                                     | -                                                                 | -
| 3.2     | 2350      | -                                                     | -                                                                 | -
| 3.3     | 2375      | -                                                     | -                                                                 | 2564
| 3.4     | 2400      | -                                                     | 2349                                                              | -
| 3.5     | 2450      | -                                                     | -                                                                 | -
| 4.0     | 2550      | 2519                                                  | -                                                                 | 2670
| 4.1     | 2600      | 2601                                                  | 2578                                                              | 2733
| 4.2     | 2670      | 2764                                                  | 2689                                                              | -
---

## Current Version Upgrades

### Basic Requirements

 - [x] UCI Protocol
 - [x] Time Management
 - [x] Negamax
 - [x] Iterative Deepening

### Search Upgrades

 - [x] AlphaBeta Negamax
 - [x] Quiescence Search
 - [x] Transposition Table
 - [x] Aspiration Window
 - [x] Principal Variation Search
 - [x] Improving Heuristic
 - [x] Check Extensions
 - [x] Reverse Futility Pruning
 - [x] Null Move Pruning
 - [x] History Pruning
 - [x] Late Move Reduction

### Eval Upgrades

 - [x] Material Score
 - [x] Piece-Square Tables
 - Pawn Eval
   - [x] Passed
   - [x] Phalanx
   - [x] Isolated
   - [x] Supported
 - Piece Eval
   - [x] Mobility
   - [x] Attacked by Pawn
   - [x] Open / Semi-Open File
   - [x] Bishop Pair
   - [x] Minor Piece Behind Pawn
   - [x] Minor Piece Outpost
 - King Eval
   - [x] King Openness
   - [x] Attacking Pawn
   - [x] Pawn In Front

### Move Ordering Upgrades

 - [x] TT-Move
 - [x] Promotions
 - [x] MVV-LVA
 - [x] History Heuristic \[Piece\]\[To\]
 - [x] Killer Moves

---

### Useful Tools

[Cutechess](https://github.com/cutechess/cutechess) - Use the Cutechess CLI to run SPRT on your engine

[Texel Tuner](https://github.com/GediminasMasaitis/texel-tuner) - Tune your handcrafted eval function
- [Dataset of quiet positions](https://github.com/KierenP/ChessTrainingSets)

### Libraries 

Chess package for C++: https://github.com/Disservin/chess-library

### Resources

[Chessprogramming wiki](https://www.chessprogramming.org/Main_Page) has a lot of information but can be outdated and lacks pseudocode.

### Other Engine Insiprations

[Altair](https://github.com/Alex2262/AltairChessEngine)  [Bit-Genie](https://github.com/Aryan1508/Bit-Genie)  [Blunder](https://github.com/algerbrex/blunder)  [Rice](https://github.com/rafid-dev/rice)  [Weiss](https://github.com/TerjeKir/weiss)

And of course, [Stockfish](https://github.com/official-stockfish/Stockfish)


[downloads-badge]:https://img.shields.io/github/downloads/Sidhant-Roymoulik/Lux/total?color=success&style=for-the-badge

[license-badge]:https://img.shields.io/github/license/Sidhant-Roymoulik/Lux?style=for-the-badge&label=license&color=success
[license-link]:https://github.com/Sidhant-Roymoulik/Lux/blob/main/LICENSE
[release-badge]:https://img.shields.io/github/v/release/Sidhant-Roymoulik/Lux?style=for-the-badge&label=official%20release
[release-link]:https://github.com/Sidhant-Roymoulik/Lux/releases/latest
[commits-badge]:https://img.shields.io/github/commits-since/Sidhant-Roymoulik/Lux/latest?style=for-the-badge
[commits-link]:https://github.com/Sidhant-Roymoulik/Lux/commits/main
