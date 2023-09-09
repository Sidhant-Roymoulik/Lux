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

 - [x] TT-Move
 - [x] MVV-LVA

---

## Benchmarking Results
CPU: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz

Depth = 7
```
Position [ 1] -> cp    71 move     O-O     1947712 nodes 3038552 nps
Position [ 2] -> cp    17 move    Nxd3     2990178 nodes 3232625 nps
Position [ 3] -> cp    13 move     Bg2     5905884 nodes 3451715 nps
Position [ 4] -> cp  -266 move    Qf4+     5996901 nodes 3454436 nps
Position [ 5] -> cp   -23 move      e4     6003436 nodes 3456209 nps
Position [ 6] -> cp    73 move    Rxf4     7686678 nodes 3425435 nps
Position [ 7] -> cp   -13 move    cxd5     9383141 nodes 3459860 nps
Position [ 8] -> cp   -51 move     Kh1    14121295 nodes 3382346 nps
Position [ 9] -> cp  -221 move     Bb5    15316939 nodes 3376006 nps
Position [10] -> cp  -118 move   axb4+    15533433 nodes 3373899 nps
Position [11] -> cp   145 move    Nxd4    16435674 nodes 3365207 nps
Position [12] -> cp    20 move     Rf8    20681200 nodes 3404312 nps
Position [13] -> cp  -243 move     Qb6    21693270 nodes 3410355 nps
Position [14] -> cp   -40 move     Ra5    22342058 nodes 3421448 nps
Position [15] -> cp    35 move    Bxg7    23281418 nodes 3432318 nps
Position [16] -> cp    65 move     Kg6    23330601 nodes 3433495 nps
Position [17] -> cp    19 move    Bxd5    23981428 nodes 3437212 nps
Position [18] -> cp   131 move     Bg7    28764763 nodes 3440761 nps
Position [19] -> cp    33 move     Qe6    31821757 nodes 3447644 nps
Position [20] -> cp    26 move     Qd5    33306684 nodes 3456843 nps
Position [21] -> cp  -261 move     Ke1    34582232 nodes 3459261 nps
Position [22] -> cp    -1 move     Bg5    35660421 nodes 3460161 nps
Position [23] -> cp   133 move      d5    38209613 nodes 3461015 nps
Position [24] -> cp   -66 move     Qf8    48428448 nodes 3499165 nps
Position [25] -> cp   124 move      g4    49907278 nodes 3508913 nps
Position [26] -> cp   197 move    Qg5+    50015562 nodes 3510110 nps
Position [27] -> cp    82 move    Ngf3    51472778 nodes 3513740 nps
Position [28] -> cp    53 move     Qb3    52796902 nodes 3516745 nps
Position [29] -> cp   117 move     Ng5    53434387 nodes 3515883 nps
Position [30] -> cp   -99 move     Rf6    53579785 nodes 3514350 nps
Position [31] -> cp   139 move    Rxd6    53700509 nodes 3514891 nps
Position [32] -> cp   -95 move     Nd4    53965823 nodes 3514315 nps
Position [33] -> cp   -85 move     Kc6    54191107 nodes 3513427 nps
Position [34] -> cp   -84 move     Kc6    54464096 nodes 3512226 nps
Position [35] -> cp   124 move     Rc1    54541579 nodes 3512466 nps
Position [36] -> cp  -195 move     Kg4    54602886 nodes 3512795 nps
Position [37] -> cp  -235 move     Kf8    54679371 nodes 3513195 nps
Position [38] -> cp   356 move    Rxb6    54737241 nodes 3514204 nps
Position [39] -> cp   -21 move     Bg4    69408375 nodes 3497700 nps
Position [40] -> cp   -47 move      b3    70678800 nodes 3496700 nps
Position [41] -> cp    50 move     Bb5    72954929 nodes 3504415 nps
Position [42] -> cp  -133 move    Rxc1    73083622 nodes 3505209 nps
Position [43] -> cp   -39 move     Bb4    73327142 nodes 3505456 nps
Position [44] -> cp    92 move     Rf1    85497223 nodes 3519273 nps
Position [45] -> cp   -28 move     Qb8    86175417 nodes 3518225 nps
Position [46] -> cp    14 move      h5    86458986 nodes 3517309 nps
Position [47] -> cp     5 move      e6    88451256 nodes 3518907 nps
Position [48] -> cp     5 move      a3   100598897 nodes 3532761 nps
Position [49] -> cp    70 move      g4   102866636 nodes 3540776 nps
Position [50] -> cp   106 move     Rh7   104815796 nodes 3547185 nps
Finished:                                104815796 nodes 3547185 nps
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
