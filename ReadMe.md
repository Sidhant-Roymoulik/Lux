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
 - [x] Principal Variation Search
 - [x] Reverse Futility Pruning
 - [x] Check Extensions

### Eval Upgrades

 - [x] Material Score
 - [x] Piece-Square Tables

### Move Ordering Upgrades

 - [x] TT-Move
 - [x] MVV-LVA
 - [x] History Heuristic

---

## Benchmarking Results
CPU: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz

Depth = 7
```
Position [ 1] -> cp    71 move     O-O      699646 nodes 3446532 nps
Position [ 2] -> cp    28 move     Bd6     1086642 nodes 3385177 nps
Position [ 3] -> cp    35 move     Ra2     1905104 nodes 3527970 nps
Position [ 4] -> cp  -264 move    Qf4+     1935751 nodes 3538850 nps
Position [ 5] -> cp   -30 move      e4     1942046 nodes 3543879 nps
Position [ 6] -> cp    67 move     Qd1     2322137 nodes 3486692 nps
Position [ 7] -> cp   -13 move    cxd5     2731754 nodes 3479941 nps
Position [ 8] -> cp   -28 move     Kh1     3521398 nodes 3455739 nps
Position [ 9] -> cp  -227 move     Bb5     4316819 nodes 3458989 nps
Position [10] -> cp  -122 move   axb4+     4504652 nodes 3457138 nps
Position [11] -> cp   145 move    Nxd4     4740795 nodes 3465493 nps
Position [12] -> cp    17 move     Rf8     5674740 nodes 3468667 nps
Position [13] -> cp  -243 move     Qb6     5749580 nodes 3467780 nps
Position [14] -> cp   -46 move     Ra5     6185252 nodes 3467069 nps
Position [15] -> cp    35 move    Bxg7     6314030 nodes 3471154 nps
Position [16] -> cp    71 move     Kg4     6336737 nodes 3474088 nps
Position [17] -> cp    19 move    Bxd5     6490220 nodes 3470706 nps
Position [18] -> cp    80 move     Rb6     7681111 nodes 3455290 nps
Position [19] -> cp    34 move     Qe6     8273330 nodes 3457304 nps
Position [20] -> cp    27 move     Qd5     8675625 nodes 3457802 nps
Position [21] -> cp  -261 move     Ke1    10117331 nodes 3471973 nps
Position [22] -> cp   -13 move     Ne2    10687791 nodes 3470062 nps
Position [23] -> cp   133 move      d5    11694728 nodes 3464078 nps
Position [24] -> cp   -66 move     Qf8    15960409 nodes 3519384 nps
Position [25] -> cp    20 move    Bxg7    16204694 nodes 3517407 nps
Position [26] -> cp   219 move    Qg5+    16331003 nodes 3521130 nps
Position [27] -> cp    82 move    Ngf3    16751971 nodes 3520801 nps
Position [28] -> cp    53 move     Qb3    17130948 nodes 3519816 nps
Position [29] -> cp   101 move     Ng5    17259637 nodes 3519501 nps
Position [30] -> cp  -108 move     Rf6    17631774 nodes 3520721 nps
Position [31] -> cp   134 move    Rxd6    17736346 nodes 3521911 nps
Position [32] -> cp   -97 move     Nd4    17947988 nodes 3520594 nps
Position [33] -> cp   -91 move     Kc6    18120120 nodes 3520520 nps
Position [34] -> cp   -85 move     Kc6    18271387 nodes 3519820 nps
Position [35] -> cp   130 move     Rc1    18323906 nodes 3519091 nps
Position [36] -> cp  -195 move     Kg4    18374498 nodes 3520018 nps
Position [37] -> cp  -255 move     Nc2    18423858 nodes 3520033 nps
Position [38] -> cp   354 move    Rxb6    18490096 nodes 3521252 nps
Position [39] -> cp   -21 move     Bg4    20895097 nodes 3520656 nps
Position [40] -> cp   -47 move      b3    21477626 nodes 3524389 nps
Position [41] -> cp    50 move     Bb5    22045669 nodes 3522797 nps
Position [42] -> cp   -91 move    Rxc1    22192196 nodes 3522570 nps
Position [43] -> cp   -47 move     Bb4    22319581 nodes 3522660 nps
Position [44] -> cp    93 move     Rf1    25748498 nodes 3518515 nps
Position [45] -> cp   -28 move     Qb8    26043673 nodes 3515614 nps
Position [46] -> cp    15 move      h5    26288201 nodes 3513995 nps
Position [47] -> cp     4 move      e6    26871710 nodes 3508056 nps
Position [48] -> cp     5 move      a3    29158258 nodes 3515584 nps
Position [49] -> cp    75 move      g4    30251629 nodes 3522956 nps
Position [50] -> cp   106 move     Rh7    30794160 nodes 3524569 nps
Finished:                                 30794160 nodes 3524569 nps
```
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