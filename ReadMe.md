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
 - [x] Promotions

---

## Benchmarking Results
CPU: 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz

Depth = 7
```
Position [ 1] -> cp    71 move     O-O      699646 nodes 3412907 nps
Position [ 2] -> cp    28 move     Bd6     1086642 nodes 3417113 nps
Position [ 3] -> cp    35 move     Ra2     1905104 nodes 3541085 nps
Position [ 4] -> cp  -264 move    Qf4+     1935751 nodes 3545331 nps
Position [ 5] -> cp   -30 move      e4     1942046 nodes 3537424 nps
Position [ 6] -> cp    67 move     Qd1     2322137 nodes 3440203 nps
Position [ 7] -> cp   -13 move    cxd5     2731815 nodes 3431928 nps
Position [ 8] -> cp   -28 move     Kh1     3521500 nodes 3422254 nps
Position [ 9] -> cp  -227 move     Bb5     4284367 nodes 3432986 nps
Position [10] -> cp  -122 move   axb4+     4472192 nodes 3432227 nps
Position [11] -> cp   145 move    Nxd4     4708335 nodes 3441765 nps
Position [12] -> cp    17 move     Rf8     5642320 nodes 3467928 nps
Position [13] -> cp  -243 move     Qb6     5726956 nodes 3466680 nps
Position [14] -> cp   -46 move     Ra5     6162627 nodes 3460206 nps
Position [15] -> cp    35 move    Bxg7     6291409 nodes 3462525 nps
Position [16] -> cp    71 move     Kg4     6313768 nodes 3465295 nps
Position [17] -> cp    19 move    Bxd5     6467250 nodes 3463979 nps
Position [18] -> cp    80 move     Rb6     7661020 nodes 3441608 nps
Position [19] -> cp    34 move     Qe6     8253499 nodes 3447576 nps
Position [20] -> cp    27 move     Qd5     8655749 nodes 3448505 nps
Position [21] -> cp  -261 move     Ke1    10097534 nodes 3454510 nps
Position [22] -> cp   -13 move     Ne2    10668049 nodes 3454679 nps
Position [23] -> cp   133 move      d5    11674976 nodes 3451072 nps
Position [24] -> cp   -66 move     Qf8    15943913 nodes 3509556 nps
Position [25] -> cp    20 move    Bxg7    16188123 nodes 3506959 nps
Position [26] -> cp   219 move    Qg5+    16290952 nodes 3510224 nps
Position [27] -> cp    82 move    Ngf3    16711920 nodes 3507223 nps
Position [28] -> cp    53 move     Qb3    17090929 nodes 3503675 nps
Position [29] -> cp   101 move     Ng5    17219618 nodes 3499922 nps
Position [30] -> cp  -108 move     Rf6    17591756 nodes 3498758 nps
Position [31] -> cp   134 move    Rxd6    17696328 nodes 3500064 nps
Position [32] -> cp   -97 move     Nd4    17907970 nodes 3499701 nps
Position [33] -> cp   -91 move     Kc6    18080102 nodes 3499826 nps
Position [34] -> cp   -85 move     Kc6    18231369 nodes 3500646 nps
Position [35] -> cp   130 move     Rc1    18283891 nodes 3501320 nps
Position [36] -> cp  -195 move     Kg4    18334486 nodes 3501620 nps
Position [37] -> cp  -255 move     Nc2    18383847 nodes 3502352 nps
Position [38] -> cp   354 move    Rxb6    18450087 nodes 3502959 nps
Position [39] -> cp   -21 move     Bg4    20854939 nodes 3499738 nps
Position [40] -> cp   -47 move      b3    21437439 nodes 3503422 nps
Position [41] -> cp    50 move     Bb5    22005525 nodes 3502948 nps
Position [42] -> cp   -91 move    Rxc1    22152029 nodes 3503404 nps
Position [43] -> cp   -47 move     Bb4    22279414 nodes 3503603 nps
Position [44] -> cp    93 move     Rf1    25707191 nodes 3500434 nps
Position [45] -> cp   -28 move     Qb8    26002385 nodes 3497294 nps
Position [46] -> cp    15 move      h5    26246911 nodes 3495393 nps
Position [47] -> cp     4 move      e6    26830426 nodes 3498100 nps
Position [48] -> cp     5 move      a3    29117006 nodes 3502587 nps
Position [49] -> cp    75 move      g4    30210351 nodes 3510382 nps
Position [50] -> cp   106 move     Rh7    30752882 nodes 3510603 nps
Finished:                                 30752882 nodes 3510603 nps
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