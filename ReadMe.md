<div align="center">

  <img src="./img/logo.jpg" width="30%">
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
| Version | Estimated | [CCRL Blitz (2'+1")](https://ccrl.chessdom.com/ccrl/404/)  |
|-------- |-----------|------------------------------------------------------------|
| 1.0     | 1711      | -                                                          |
| 2.0     | 1857      | -                                                          |
| 2.1     | 1986      | -                                                          |
| 2.2     | 2063      | -                                                          |
| 2.3     | 2140      | 2140                                                       |
| 3.0     | 2318      | -                                                          |
| 3.1     | 2394      | -                                                          |
| 3.2     | 2464      | -                                                          |
| 3.3     | 2487      | -                                                          |
| 3.4     | 2519      | -                                                          |

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
 - [x] Check Extensions
 - [x] Reverse Futility Pruning
 - [x] Null Move Pruning
 - [x] History Pruning
 - [x] Late Move Reduction

### Eval Upgrades

 - [x] Material Score
 - [x] Piece-Square Tables

### Move Ordering Upgrades

 - [x] TT-Move
 - [x] Promotions
 - [x] MVV-LVA
 - [x] History Heuristic \[Piece\]\[To\]
 - [x] Killer Moves

---

## Resources

[Chessprogramming wiki](https://www.chessprogramming.org/Main_Page) has a lot of information but can be outdated and can lack pseudocode.

### Libraries 

Chess package for C++: https://github.com/Disservin/chess-library

### Other Engine Insiprations

[antikythera](https://github.com/0hq/antikythera)

[Bit-Genie](https://github.com/Aryan1508/Bit-Genie)

[Blunder](https://github.com/algerbrex/blunder)

[Rice](https://github.com/rafid-dev/rice)

And of course, [Stockfish](https://github.com/official-stockfish/Stockfish)


[downloads-badge]:https://img.shields.io/github/downloads/Sidhant-Roymoulik/Lux/total?color=success&style=for-the-badge

[license-badge]:https://img.shields.io/github/license/Sidhant-Roymoulik/Lux?style=for-the-badge&label=license&color=success
[license-link]:https://github.com/Sidhant-Roymoulik/Lux/blob/main/LICENSE
[release-badge]:https://img.shields.io/github/v/release/Sidhant-Roymoulik/Lux?style=for-the-badge&label=official%20release
[release-link]:https://github.com/Sidhant-Roymoulik/Lux/releases/latest
[commits-badge]:https://img.shields.io/github/commits-since/Sidhant-Roymoulik/Lux/latest?style=for-the-badge
[commits-link]:https://github.com/Sidhant-Roymoulik/Lux/commits/main
