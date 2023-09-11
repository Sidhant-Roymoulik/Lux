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
Position [ 1] -> cp    71 move     O-O      701278 nodes 3559787 nps
Position [ 2] -> cp    17 move    Nxd3      949719 nodes 3557000 nps
Position [ 3] -> cp    13 move     Bg2     3025770 nodes 3754057 nps
Position [ 4] -> cp  -266 move    Qf4+     3033440 nodes 3758909 nps
Position [ 5] -> cp   -23 move      e4     3038339 nodes 3755672 nps
Position [ 6] -> cp    73 move    Rxf4     3814861 nodes 3654081 nps
Position [ 7] -> cp   -13 move    cxd5     4514168 nodes 3637524 nps
Position [ 8] -> cp   -51 move     Kh1     5827900 nodes 3599691 nps
Position [ 9] -> cp  -221 move     Bb5     6241551 nodes 3601587 nps
Position [10] -> cp  -118 move   axb4+     6281807 nodes 3604020 nps
Position [11] -> cp   145 move    Nxd4     6466875 nodes 3606734 nps
Position [12] -> cp    20 move     Rf8     7601417 nodes 3612841 nps
Position [13] -> cp  -243 move     Qb6     7666598 nodes 3611209 nps
Position [14] -> cp   -40 move     Ra5     7946914 nodes 3617166 nps
Position [15] -> cp    35 move    Bxg7     8083792 nodes 3618528 nps
Position [16] -> cp    65 move     Kg6     8118259 nodes 3620989 nps
Position [17] -> cp    19 move    Bxd5     8329210 nodes 3611973 nps
Position [18] -> cp   131 move     Bg7     9181768 nodes 3596462 nps
Position [19] -> cp    33 move     Qe6    11346138 nodes 3615722 nps
Position [20] -> cp    26 move     Qd5    11796225 nodes 3617364 nps
Position [21] -> cp  -261 move     Ke1    12204446 nodes 3612920 nps
Position [22] -> cp    -1 move     Bg5    12581030 nodes 3601783 nps
Position [23] -> cp   133 move      d5    13339978 nodes 3598591 nps
Position [24] -> cp   -66 move     Qf8    19218323 nodes 3614505 nps
Position [25] -> cp   124 move      g4    19293810 nodes 3613073 nps
Position [26] -> cp   197 move    Qg5+    19363422 nodes 3616627 nps
Position [27] -> cp    82 move    Ngf3    19839022 nodes 3609063 nps
Position [28] -> cp    53 move     Qb3    20222751 nodes 3590050 nps
Position [29] -> cp   117 move     Ng5    20310954 nodes 3589142 nps
Position [30] -> cp   -99 move     Rf6    20390819 nodes 3587406 nps
Position [31] -> cp   139 move    Rxd6    20462397 nodes 3588634 nps
Position [32] -> cp   -95 move     Nd4    20638072 nodes 3587982 nps
Position [33] -> cp   -85 move     Kc6    20802757 nodes 3586682 nps
Position [34] -> cp   -84 move     Kc6    20995812 nodes 3582903 nps
Position [35] -> cp   124 move     Rc1    21053698 nodes 3582998 nps
Position [36] -> cp  -195 move     Kg4    21099306 nodes 3584050 nps
Position [37] -> cp  -244 move     Kf8    21163434 nodes 3584592 nps
Position [38] -> cp   356 move    Rxb6    21203152 nodes 3584641 nps
Position [39] -> cp   -21 move     Bg4    26510373 nodes 3530950 nps
Position [40] -> cp   -47 move      b3    27132483 nodes 3531036 nps
Position [41] -> cp    50 move     Bb5    27613309 nodes 3525703 nps
Position [42] -> cp  -133 move    Rxc1    27668951 nodes 3525156 nps
Position [43] -> cp   -39 move     Bb4    27854649 nodes 3524566 nps
Position [44] -> cp    93 move     Rf1    32253706 nodes 3414536 nps
Position [45] -> cp   -28 move     Qb8    32486188 nodes 3410981 nps
Position [46] -> cp    15 move      h5    32631723 nodes 3408013 nps
Position [47] -> cp     5 move      e6    33509524 nodes 3406478 nps
Position [48] -> cp    10 move      c5    36588027 nodes 3391863 nps
Position [49] -> cp    70 move      g4    37915470 nodes 3399881 nps
Position [50] -> cp   106 move     Rh7    39116060 nodes 3413268 nps
Finished:                                 39116060 nodes 3413268 nps
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
