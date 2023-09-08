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
Position [ 1] -> cp    71 move     O-O    19634037 nodes 4203390 nps
Position [ 2] -> cp    17 move    Nxd3    23002691 nodes 4229991 nps
Position [ 3] -> cp    13 move     Bg2    40456002 nodes 4491119 nps
Position [ 4] -> cp  -266 move   Rxf2+    40675181 nodes 4489039 nps
Position [ 5] -> cp   -23 move      e4    40699467 nodes 4489242 nps
Position [ 6] -> cp    73 move    Rxf4    45658893 nodes 4481194 nps
Position [ 7] -> cp   -13 move    cxd5    55625266 nodes 4436534 nps
Position [ 8] -> cp   -51 move     Kh1    77864768 nodes 4414853 nps
Position [ 9] -> cp  -221 move     Bb5   115005312 nodes 4460163 nps
Position [10] -> cp  -118 move   axb4+   117078301 nodes 4464377 nps
Position [11] -> cp   145 move    Nxd4   120606558 nodes 4460796 nps
Position [12] -> cp    20 move     Rf8   193305831 nodes 4532269 nps
Position [13] -> cp  -243 move     Qb6   199076606 nodes 4525085 nps
Position [14] -> cp   -40 move     Ra5   213171570 nodes 4521424 nps
Position [15] -> cp    35 move    Bxg7   215717752 nodes 4520868 nps
Position [16] -> cp    65 move     Kg6   215981650 nodes 4521471 nps
Position [17] -> cp    19 move    Bxd5   218147223 nodes 4521748 nps
Position [18] -> cp   131 move     Bg7   262694380 nodes 4501969 nps
Position [19] -> cp    33 move     Qe6   282976524 nodes 4514622 nps
Position [20] -> cp    26 move     Qd5   300186854 nodes 4517824 nps
Position [21] -> cp  -261 move     Ke1   305280947 nodes 4515857 nps
Position [22] -> cp    -1 move     Bg5   315949962 nodes 4507710 nps
Position [23] -> cp   133 move      d5   336403437 nodes 4501283 nps
Position [24] -> cp   -66 move     Qf8   373594537 nodes 4531439 nps
Position [25] -> cp   124 move      g4   378860632 nodes 4530146 nps
Position [26] -> cp   192 move    Qg5+   384720623 nodes 4534393 nps
Position [27] -> cp    82 move      h3   392573852 nodes 4530517 nps
Position [28] -> cp    53 move     Qb3   399935054 nodes 4527071 nps
Position [29] -> cp   117 move     Ng5   401905844 nodes 4527853 nps
Position [30] -> cp   -99 move     Rf6   402472924 nodes 4527815 nps
Position [31] -> cp   140 move    Rxd6   403445770 nodes 4528316 nps
Position [32] -> cp   -95 move     Kf6   405426536 nodes 4529804 nps
Position [33] -> cp   -85 move     Kc6   408312382 nodes 4531618 nps
Position [34] -> cp   -84 move     Kc6   409638248 nodes 4532249 nps
Position [35] -> cp   124 move     Rc1   409952417 nodes 4532265 nps
Position [36] -> cp  -195 move     Kg4   410185842 nodes 4532240 nps
Position [37] -> cp  -232 move     Kf8   410679892 nodes 4532440 nps
Position [38] -> cp   356 move    Rxb6   410851015 nodes 4532478 nps
Position [39] -> cp   -21 move     Bg4   469824948 nodes 4548997 nps
Position [40] -> cp   -47 move      b3   478045785 nodes 4545112 nps
Position [41] -> cp    50 move     Bb5   489412098 nodes 4542318 nps
Position [42] -> cp  -133 move    Rxc1   490253076 nodes 4542914 nps
Position [43] -> cp   -39 move     Bb4   491289069 nodes 4543714 nps
Position [44] -> cp    92 move      h3   551154433 nodes 4542643 nps
Position [45] -> cp   -13 move     Qb8   556747370 nodes 4540392 nps
Position [46] -> cp    17 move      h5   558184601 nodes 4540264 nps
Position [47] -> cp     5 move      e6   572950256 nodes 4534592 nps
Position [48] -> cp     5 move      a3   632791279 nodes 4550327 nps
Position [49] -> cp    70 move      g4   661211061 nodes 4553795 nps
Position [50] -> cp   106 move     Kb2   671204761 nodes 4557245 nps
Finished:                                671204761 nodes 4557245 nps
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
