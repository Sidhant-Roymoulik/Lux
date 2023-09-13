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

---

## Benchmarking Results
CPU: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz

Depth = 7
```
Position [ 1] -> cp    71 move     O-O      816742 nodes 3490350 nps
Position [ 2] -> cp    28 move     Bd6     1326604 nodes 3481900 nps
Position [ 3] -> cp    35 move     Ra2     2378341 nodes 3614500 nps
Position [ 4] -> cp  -258 move    Qf4+     2430884 nodes 3617387 nps
Position [ 5] -> cp   -30 move      e4     2437440 nodes 3621753 nps
Position [ 6] -> cp    67 move     Qd1     3553852 nodes 3560973 nps
Position [ 7] -> cp   -13 move    cxd5     4202570 nodes 3531571 nps
Position [ 8] -> cp   -28 move     Kh1     5951439 nodes 3553097 nps
Position [ 9] -> cp  -227 move     Bb5     7607572 nodes 3500953 nps
Position [10] -> cp  -122 move   axb4+     7859371 nodes 3500833 nps
Position [11] -> cp   145 move    Nxd4     8111967 nodes 3495031 nps
Position [12] -> cp    17 move     Rf8    10645316 nodes 3546074 nps
Position [13] -> cp  -243 move     Qb6    10713902 nodes 3545301 nps
Position [14] -> cp   -46 move     Ra5    11288075 nodes 3534150 nps
Position [15] -> cp    35 move    Bxg7    11432759 nodes 3535176 nps
Position [16] -> cp    65 move     Kg6    11473260 nodes 3536763 nps
Position [17] -> cp    19 move    Bxd5    11683776 nodes 3535182 nps
Position [18] -> cp    77 move     Rb6    20208244 nodes 3540337 nps
Position [19] -> cp    34 move     Qe6    21837997 nodes 3542828 nps
Position [20] -> cp    27 move     Qd5    22546210 nodes 3543330 nps
Position [21] -> cp  -261 move     Ke1    23939641 nodes 3547138 nps
Position [22] -> cp   -13 move     Ne2    24901829 nodes 3543735 nps
Position [23] -> cp   133 move      d5    26794453 nodes 3544708 nps
Position [24] -> cp   -66 move     Qf8    34986315 nodes 3596085 nps
Position [25] -> cp    20 move    Bxg7    35375867 nodes 3595108 nps
Position [26] -> cp   219 move    Qg5+    35717765 nodes 3596955 nps
Position [27] -> cp    82 move    Ngf3    36262255 nodes 3596019 nps
Position [28] -> cp    53 move     Qb3    36672903 nodes 3593621 nps
Position [29] -> cp   101 move     Ng5    36838059 nodes 3593606 nps
Position [30] -> cp  -108 move     Rf6    37444503 nodes 3594557 nps
Position [31] -> cp   134 move    Rxd6    37575824 nodes 3595084 nps
Position [32] -> cp   -97 move     Nd4    37840606 nodes 3594965 nps
Position [33] -> cp   -91 move     Kc6    38116068 nodes 3594499 nps
Position [34] -> cp   -85 move     Kc6    38315597 nodes 3595345 nps
Position [35] -> cp   130 move     Rc1    38391842 nodes 3595415 nps
Position [36] -> cp  -195 move     Kg4    38457022 nodes 3596131 nps
Position [37] -> cp  -255 move     Nc2    38550697 nodes 3596818 nps
Position [38] -> cp   354 move    Rxb6    38635492 nodes 3597680 nps
Position [39] -> cp   -21 move     Bg4    44733421 nodes 3603755 nps
Position [40] -> cp   -47 move      b3    45437195 nodes 3605840 nps
Position [41] -> cp    50 move     Bb5    46084315 nodes 3604843 nps
Position [42] -> cp   -91 move    Rxc1    46274071 nodes 3605303 nps
Position [43] -> cp   -47 move     Bb4    46448646 nodes 3604862 nps
Position [44] -> cp    93 move     Rf1    50559297 nodes 3612926 nps
Position [45] -> cp   -28 move     Qb8    50961971 nodes 3609716 nps
Position [46] -> cp    15 move      h5    51269901 nodes 3608777 nps
Position [47] -> cp     5 move      e6    52425152 nodes 3606573 nps
Position [48] -> cp    10 move      c5    56988723 nodes 3613055 nps
Position [49] -> cp    75 move      g4    58468561 nodes 3616985 nps
Position [50] -> cp   106 move     Rh7    59870451 nodes 3621708 nps
Finished:                                 59870451 nodes 3621708 nps
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
