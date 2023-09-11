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
Position [ 1] -> cp    71 move     O-O     1263283 nodes 3558543 nps
Position [ 2] -> cp    17 move    Nxd3     2251827 nodes 3734373 nps
Position [ 3] -> cp    13 move     Bg2     4813083 nodes 3819907 nps
Position [ 4] -> cp  -266 move    Qf4+     4912551 nodes 3817056 nps
Position [ 5] -> cp   -23 move      e4     4918784 nodes 3818931 nps
Position [ 6] -> cp    73 move    Rxf4     6004280 nodes 3727051 nps
Position [ 7] -> cp   -13 move    cxd5     7334111 nodes 3741893 nps
Position [ 8] -> cp   -51 move     Kh1     9721591 nodes 3649245 nps
Position [ 9] -> cp  -221 move     Bb5    10740081 nodes 3663056 nps
Position [10] -> cp  -118 move   axb4+    10921902 nodes 3665067 nps
Position [11] -> cp   145 move    Nxd4    11783148 nodes 3682233 nps
Position [12] -> cp    20 move     Rf8    13788121 nodes 3644758 nps
Position [13] -> cp  -243 move     Qb6    14707627 nodes 3653161 nps
Position [14] -> cp   -40 move     Ra5    15317835 nodes 3666308 nps
Position [15] -> cp    35 move    Bxg7    16171555 nodes 3670348 nps
Position [16] -> cp    65 move     Kg6    16207329 nodes 3670138 nps
Position [17] -> cp    19 move    Bxd5    16708798 nodes 3671456 nps
Position [18] -> cp   131 move     Bg7    19966684 nodes 3654224 nps
Position [19] -> cp    33 move     Qe6    22529720 nodes 3657422 nps
Position [20] -> cp    26 move     Qd5    23530595 nodes 3660071 nps
Position [21] -> cp  -261 move     Ke1    24645790 nodes 3661534 nps
Position [22] -> cp    -1 move     Bg5    25680524 nodes 3663935 nps
Position [23] -> cp   133 move      d5    27117446 nodes 3662539 nps
Position [24] -> cp   -66 move     Qf8    38102369 nodes 3638152 nps
Position [25] -> cp   124 move      g4    39516940 nodes 3620756 nps
Position [26] -> cp   197 move    Qg5+    39624410 nodes 3622968 nps
Position [27] -> cp    82 move    Ngf3    40901218 nodes 3627280 nps
Position [28] -> cp    53 move     Qb3    42107079 nodes 3633993 nps
Position [29] -> cp   117 move     Ng5    42692259 nodes 3640199 nps
Position [30] -> cp   -99 move     Rf6    42807095 nodes 3639749 nps
Position [31] -> cp   139 move    Rxd6    42919027 nodes 3640290 nps
Position [32] -> cp   -95 move     Nd4    43146125 nodes 3640101 nps
Position [33] -> cp   -85 move     Kc6    43322075 nodes 3640204 nps
Position [34] -> cp   -84 move     Kc6    43590775 nodes 3638932 nps
Position [35] -> cp   124 move     Rc1    43659778 nodes 3639831 nps
Position [36] -> cp  -195 move     Kg4    43710423 nodes 3640411 nps
Position [37] -> cp  -244 move     Kf8    43787670 nodes 3640478 nps
Position [38] -> cp   356 move    Rxb6    43845927 nodes 3640478 nps
Position [39] -> cp   -21 move     Bg4    52562445 nodes 3639050 nps
Position [40] -> cp   -47 move      b3    53565533 nodes 3642674 nps
Position [41] -> cp    50 move     Bb5    55732766 nodes 3659887 nps
Position [42] -> cp  -133 move    Rxc1    55854984 nodes 3660941 nps
Position [43] -> cp   -39 move     Bb4    56085210 nodes 3661392 nps
Position [44] -> cp    92 move     Rf1    62581683 nodes 3607221 nps
Position [45] -> cp   -28 move     Qb8    63199878 nodes 3602159 nps
Position [46] -> cp    15 move      h5    63437886 nodes 3598700 nps
Position [47] -> cp     5 move      e6    64679101 nodes 3593682 nps
Position [48] -> cp     5 move      a3    72305743 nodes 3583040 nps
Position [49] -> cp    70 move      g4    74151221 nodes 3589989 nps
Position [50] -> cp   106 move     Rh7    75616430 nodes 3591376 nps
Finished:                                 75616430 nodes 3591376 nps
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
