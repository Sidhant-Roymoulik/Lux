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
 - [x] History Heuristic
 - [x] Killer Moves

---

## Building
Default build (g++):

```bash
git clone https://github.com/Sidhant-Roymoulik/Lux
cd Lux/src
make 
./Lux
```

Clang build:
```bash
git clone https://github.com/Sidhant-Roymoulik/Lux
cd Lux/src
make CXX=clang++
./Lux
```

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
