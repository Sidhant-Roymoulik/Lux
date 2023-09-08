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
Depth = 7
```
Position [ 1] -> cp    71 move     O-O    19634037 nodes 4283167 nps
Position [ 2] -> cp    17 move    Nxd3    23002691 nodes 4313274 nps
Position [ 3] -> cp    13 move     Bg2    40456002 nodes 4502114 nps
Position [ 4] -> cp  -266 move   Rxf2+    40675181 nodes 4501458 nps
Position [ 5] -> cp   -23 move      e4    40699467 nodes 4502153 nps
Position [ 6] -> cp    73 move    Rxf4    45658893 nodes 4493101 nps
Position [ 7] -> cp   -13 move    cxd5    55625266 nodes 4475081 nps
Position [ 8] -> cp   -51 move     Kh1    77864768 nodes 4492544 nps
Position [ 9] -> cp  -221 move     Bb5   115005312 nodes 4533658 nps
Position [10] -> cp  -118 move   axb4+   117078301 nodes 4537391 nps
Position [11] -> cp   145 move    Nxd4   120606558 nodes 4533229 nps
Position [12] -> cp    20 move     Rf8   193305831 nodes 4527174 nps
Position [13] -> cp  -243 move     Qb6   199076606 nodes 4522104 nps
Position [14] -> cp   -40 move     Ra5   213171570 nodes 4523150 nps
Position [15] -> cp    35 move    Bxg7   215717752 nodes 4523617 nps
Position [16] -> cp    65 move     Kg6   215981650 nodes 4524597 nps
Position [17] -> cp    19 move    Bxd5   218147223 nodes 4526251 nps
Position [18] -> cp   131 move     Bg7   262694380 nodes 4531479 nps
Position [19] -> cp    33 move     Qe6   282976524 nodes 4544201 nps
Position [20] -> cp    26 move     Qd5   300186854 nodes 4549251 nps
Position [21] -> cp  -261 move     Ke1   305280947 nodes 4547338 nps
Position [22] -> cp    -1 move     Bg5   315949962 nodes 4539771 nps
Position [23] -> cp   133 move      d5   336403437 nodes 4531479 nps
Position [24] -> cp   -66 move     Qf8   373594537 nodes 4539754 nps
Position [25] -> cp   124 move      g4   378860632 nodes 4541332 nps
Position [26] -> cp   192 move    Qg5+   384720623 nodes 4546127 nps
Position [27] -> cp    82 move      h3   392573852 nodes 4543573 nps
Position [28] -> cp    53 move     Qb3   399935054 nodes 4540846 nps
Position [29] -> cp   117 move     Ng5   401905844 nodes 4541925 nps
Position [30] -> cp   -99 move     Rf6   402472924 nodes 4541917 nps
Position [31] -> cp   140 move    Rxd6   403445770 nodes 4542899 nps
Position [32] -> cp   -95 move     Kf6   405426536 nodes 4544733 nps
Position [33] -> cp   -85 move     Kc6   408312382 nodes 4546858 nps
Position [34] -> cp   -84 move     Kc6   409638248 nodes 4547998 nps
Position [35] -> cp   124 move     Rc1   409952417 nodes 4548255 nps
Position [36] -> cp  -195 move     Kg4   410185842 nodes 4548675 nps
Position [37] -> cp  -232 move     Kf8   410679892 nodes 4549260 nps
Position [38] -> cp   356 move    Rxb6   410851015 nodes 4549543 nps
Position [39] -> cp   -21 move     Bg4   469824948 nodes 4564332 nps
Position [40] -> cp   -47 move      b3   478045785 nodes 4561375 nps
Position [41] -> cp    50 move     Bb5   489412098 nodes 4557588 nps
Position [42] -> cp  -133 move    Rxc1   490253076 nodes 4558458 nps
Position [43] -> cp   -39 move     Bb4   491289069 nodes 4559569 nps
Position [44] -> cp    92 move      h3   551154433 nodes 4573781 nps
Position [45] -> cp   -13 move     Qb8   556747370 nodes 4571747 nps
Position [46] -> cp    17 move      h5   558184601 nodes 4571648 nps
Position [47] -> cp     5 move      e6   572950256 nodes 4566505 nps
Position [48] -> cp     5 move      a3   632791279 nodes 4544772 nps
Position [49] -> cp    70 move      g4   661211061 nodes 4546218 nps
Position [50] -> cp   106 move     Kb2   671204761 nodes 4550478 nps
Finished:                                671204761 nodes 4550478 nps
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
