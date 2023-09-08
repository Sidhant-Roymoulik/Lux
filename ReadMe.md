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
Position [ 1] -> cp    71 move     O-O    19646231 nodes 4257038 nps
Position [ 2] -> cp    17 move    Nxd3    23014885 nodes 4280246 nps
Position [ 3] -> cp    13 move     Bg2    40468196 nodes 4528670 nps
Position [ 4] -> cp  -266 move   Rxf2+    40687375 nodes 4526855 nps
Position [ 5] -> cp   -23 move      e4    40711661 nodes 4527542 nps
Position [ 6] -> cp    73 move    Rxf4    45671087 nodes 4518311 nps
Position [ 7] -> cp   -13 move    cxd5    55637460 nodes 4490151 nps
Position [ 8] -> cp   -51 move     Kh1    77896127 nodes 4500845 nps
Position [ 9] -> cp  -221 move     Bb5   115036671 nodes 4456195 nps
Position [10] -> cp  -118 move   axb4+   117109660 nodes 4460471 nps
Position [11] -> cp   145 move    Nxd4   120637917 nodes 4453391 nps
Position [12] -> cp    20 move     Rf8   193337190 nodes 4492557 nps
Position [13] -> cp  -243 move     Qb6   199107965 nodes 4487547 nps
Position [14] -> cp   -40 move     Ra5   213202929 nodes 4489711 nps
Position [15] -> cp    35 move    Bxg7   215749111 nodes 4490469 nps
Position [16] -> cp    65 move     Kg6   216013009 nodes 4491475 nps
Position [17] -> cp    19 move    Bxd5   218178582 nodes 4492136 nps
Position [18] -> cp   131 move     Bg7   262731226 nodes 4496435 nps
Position [19] -> cp    33 move     Qe6   283013370 nodes 4510604 nps
Position [20] -> cp    26 move     Qd5   300223700 nodes 4516884 nps
Position [21] -> cp  -261 move     Ke1   305317793 nodes 4515199 nps
Position [22] -> cp    -1 move     Bg5   315986808 nodes 4507850 nps
Position [23] -> cp   133 move      d5   336440283 nodes 4502921 nps
Position [24] -> cp   -66 move     Qf8   373632348 nodes 4520110 nps
Position [25] -> cp   124 move      g4   378898443 nodes 4521407 nps
Position [26] -> cp   192 move    Qg5+   384758807 nodes 4526734 nps
Position [27] -> cp    82 move      h3   392612036 nodes 4524014 nps
Position [28] -> cp    53 move     Qb3   399973238 nodes 4520749 nps
Position [29] -> cp   117 move     Ng5   401944028 nodes 4521712 nps
Position [30] -> cp   -99 move     Rf6   402511108 nodes 4521783 nps
Position [31] -> cp   140 move    Rxd6   403483954 nodes 4522805 nps
Position [32] -> cp   -95 move     Kf6   405465852 nodes 4524480 nps
Position [33] -> cp   -85 move     Kc6   408351698 nodes 4526729 nps
Position [34] -> cp   -84 move     Kc6   409677564 nodes 4527274 nps
Position [35] -> cp   124 move     Rc1   409991733 nodes 4527544 nps
Position [36] -> cp  -195 move     Kg4   410225164 nodes 4527921 nps
Position [37] -> cp  -232 move     Kf8   410719224 nodes 4525732 nps
Position [38] -> cp   356 move    Rxb6   410890479 nodes 4526023 nps
Position [39] -> cp   -21 move     Bg4   469864412 nodes 4526850 nps
Position [40] -> cp   -47 move      b3   478085249 nodes 4523724 nps
Position [41] -> cp    50 move     Bb5   489451562 nodes 4520657 nps
Position [42] -> cp  -133 move    Rxc1   490292540 nodes 4521117 nps
Position [43] -> cp   -39 move     Bb4   491328533 nodes 4522038 nps
Position [44] -> cp    92 move      h3   551205537 nodes 4482621 nps
Position [45] -> cp   -13 move     Qb8   556798474 nodes 4474325 nps
Position [46] -> cp    17 move      h5   558235705 nodes 4473006 nps
Position [47] -> cp     5 move      e6   573001360 nodes 4457940 nps
Position [48] -> cp     5 move      a3   632842383 nodes 4381290 nps
Position [49] -> cp    70 move      g4   661262165 nodes 4355423 nps
Position [50] -> cp   106 move     Kb2   671255865 nodes 4355410 nps
Finished:                                671255865 nodes 4355410 nps
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
