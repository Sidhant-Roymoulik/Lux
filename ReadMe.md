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

### Eval Upgrades

 - [x] Material Score
 - [x] Piece-Square Tables

### Move Ordering Upgrades

 - [x] MVV-LVA

---

## Benchmarking Results
CPU: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz

Depth = 7
```
Position [ 1] -> cp    71 move     O-O    11453195 nodes 3486513 nps
Position [ 2] -> cp    17 move    Nxd3    13578677 nodes 3525098 nps
Position [ 3] -> cp    13 move     Bg2    20261984 nodes 3621445 nps
Position [ 4] -> cp  -266 move    Qf4+    20415083 nodes 3620980 nps
Position [ 5] -> cp   -23 move      e4    20424542 nodes 3620730 nps
Position [ 6] -> cp    73 move    Rxf4    23139254 nodes 3611558 nps
Position [ 7] -> cp   -13 move    cxd5    28504427 nodes 3598589 nps
Position [ 8] -> cp   -51 move     Kh1    41739968 nodes 3555060 nps
Position [ 9] -> cp  -221 move     Bb5    55711080 nodes 3563912 nps
Position [10] -> cp  -118 move   axb4+    56654453 nodes 3571033 nps
Position [11] -> cp   145 move    Nxd4    58624242 nodes 3563350 nps
Position [12] -> cp    20 move     Rf8    91708802 nodes 3610156 nps
Position [13] -> cp  -243 move     Qb6    95285518 nodes 3612447 nps
Position [14] -> cp   -40 move     Ra5   103094962 nodes 3616986 nps
Position [15] -> cp    35 move    Bxg7   104570779 nodes 3619869 nps
Position [16] -> cp    65 move     Kg6   104659410 nodes 3620430 nps
Position [17] -> cp    19 move    Bxd5   106060614 nodes 3622289 nps
Position [18] -> cp   131 move     Bg7   129666568 nodes 3604151 nps
Position [19] -> cp    33 move     Qe6   137214952 nodes 3612060 nps
Position [20] -> cp    26 move     Qd5   147193741 nodes 3619666 nps
Position [21] -> cp  -267 move      c4   149641075 nodes 3619151 nps
Position [22] -> cp    -1 move     Bg5   156787570 nodes 3618870 nps
Position [23] -> cp   129 move      d5   170458124 nodes 3614157 nps
Position [24] -> cp   -66 move     Qf8   191352748 nodes 3630706 nps
Position [25] -> cp   124 move      g4   194095200 nodes 3636239 nps
Position [26] -> cp   158 move    Qg5+   195505947 nodes 3639080 nps
Position [27] -> cp    82 move      h3   200652401 nodes 3641604 nps
Position [28] -> cp    53 move     Qb3   205317481 nodes 3641801 nps
Position [29] -> cp   117 move     Ng5   206579675 nodes 3643123 nps
Position [30] -> cp   -99 move     Rf6   206986563 nodes 3643039 nps
Position [31] -> cp   139 move    Rxd6   207384250 nodes 3643625 nps
Position [32] -> cp   -95 move     Kf6   208276634 nodes 3644321 nps
Position [33] -> cp   -85 move     Kc6   209760808 nodes 3645858 nps
Position [34] -> cp   -84 move     Kc6   210436088 nodes 3646188 nps
Position [35] -> cp   124 move     Rb1   210598823 nodes 3646164 nps
Position [36] -> cp  -195 move     Kg4   210711368 nodes 3646471 nps
Position [37] -> cp  -244 move     Kf8   210939198 nodes 3646628 nps
Position [38] -> cp   356 move    Rxb6   211015219 nodes 3646870 nps
Position [39] -> cp   -21 move     Bg4   238754097 nodes 3648889 nps
Position [40] -> cp   -47 move      b3   243772772 nodes 3647764 nps
Position [41] -> cp    50 move     Bb5   250102297 nodes 3650329 nps
Position [42] -> cp  -133 move    Rxc1   250476325 nodes 3650832 nps
Position [43] -> cp   -39 move     Bb4   251080584 nodes 3651550 nps
Position [44] -> cp    92 move      h3   279982899 nodes 3651173 nps
Position [45] -> cp   -28 move     Qb8   284025649 nodes 3647948 nps
Position [46] -> cp    14 move      h5   284934403 nodes 3647720 nps
Position [47] -> cp     5 move      e6   292222996 nodes 3647999 nps
Position [48] -> cp     5 move      a3   321708340 nodes 3656026 nps
Position [49] -> cp    70 move      g4   337185124 nodes 3663542 nps
Position [50] -> cp   106 move     Kb2   341320076 nodes 3668215 nps
Finished:                                341320076 nodes 3668215 nps
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
