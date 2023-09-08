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
Position [ 1] -> cp    71 move   O-O nodes    19646231 nps 4296136
Position [ 2] -> cp    17 move  Nxd3 nodes    23014885 nps 4318799
Position [ 3] -> cp    13 move   Bg2 nodes    40468196 nps 4455378
Position [ 4] -> cp  -266 move Rxf2+ nodes    40687375 nps 4452547
Position [ 5] -> cp   -23 move    e4 nodes    40711661 nps 4452768
Position [ 6] -> cp    73 move  Rxf4 nodes    45671087 nps 4374625
Position [ 7] -> cp   -13 move  cxd5 nodes    55637460 nps 4299981
Position [ 8] -> cp   -51 move   Kh1 nodes    77896127 nps 4230496
Position [ 9] -> cp  -221 move   Bb5 nodes   115036671 nps 4268680
Position [10] -> cp  -118 move axb4+ nodes   117109660 nps 4272827
Position [11] -> cp   145 move  Nxd4 nodes   120637917 nps 4245123
Position [12] -> cp    20 move   Rf8 nodes   193337190 nps 4182252
Position [13] -> cp  -243 move   Qb6 nodes   199107965 nps 4176710
Position [14] -> cp   -40 move   Ra5 nodes   213202929 nps 4150581
Position [15] -> cp    35 move  Bxg7 nodes   215749111 nps 4145991
Position [16] -> cp    65 move   Kg6 nodes   216013009 nps 4147078
Position [17] -> cp    19 move  Bxd5 nodes   218178582 nps 4145044
Position [18] -> cp   131 move   Bg7 nodes   262731226 nps 4089711
Position [19] -> cp    33 move   Qe6 nodes   283013370 nps 4097961
Position [20] -> cp    26 move   Qd5 nodes   300223700 nps 4102874
Position [21] -> cp  -261 move   Ke1 nodes   305317793 nps 4099051
Position [22] -> cp    -1 move   Bg5 nodes   315986808 nps 4073517
Position [23] -> cp   133 move    d5 nodes   336440283 nps 4050228
Position [24] -> cp   -66 move   Qf8 nodes   373632348 nps 4065109
Position [25] -> cp   124 move    g4 nodes   378898443 nps 4057944
Position [26] -> cp   192 move  Qg5+ nodes   384758807 nps 4059964
Position [27] -> cp    82 move    h3 nodes   392612036 nps 4045503
Position [28] -> cp    53 move   Qb3 nodes   399973238 nps 4044137
Position [29] -> cp   117 move   Ng5 nodes   401944028 nps 4045737
Position [30] -> cp   -99 move   Rf6 nodes   402511108 nps 4045581
Position [31] -> cp   140 move  Rxd6 nodes   403483954 nps 4046615
Position [32] -> cp   -95 move   Kf6 nodes   405465852 nps 4048787
Position [33] -> cp   -85 move   Kc6 nodes   408351698 nps 4050585
Position [34] -> cp   -84 move   Kc6 nodes   409677564 nps 4051199
Position [35] -> cp   124 move   Rc1 nodes   409991733 nps 4050781
Position [36] -> cp  -195 move   Kg4 nodes   410225164 nps 4050846
Position [37] -> cp  -232 move   Kf8 nodes   410719224 nps 4050885
Position [38] -> cp   356 move  Rxb6 nodes   410890479 nps 4051135
Position [39] -> cp   -21 move   Bg4 nodes   469864412 nps 4085386
Position [40] -> cp   -47 move    b3 nodes   478085249 nps 4084034
Position [41] -> cp    50 move   Bb5 nodes   489451562 nps 4083152
Position [42] -> cp  -133 move  Rxc1 nodes   490292540 nps 4083695
Position [43] -> cp   -39 move   Bb4 nodes   491328533 nps 4082531
Position [44] -> cp    92 move    h3 nodes   551205537 nps 4103918
Position [45] -> cp   -13 move   Qb8 nodes   556798474 nps 4105698
Position [46] -> cp    17 move    h5 nodes   558235705 nps 4106274
Position [47] -> cp     5 move    e6 nodes   573001360 nps 4110394
Position [48] -> cp     5 move    a3 nodes   632842383 nps 4133955
Position [49] -> cp    70 move    g4 nodes   661262165 nps 4148159
Position [50] -> cp   106 move   Kb2 nodes   671255865 nps 4157052
Finished: nodes                              671255865 nps 4157052
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
[license-link]:https://github.com/Sidhant-Roymoulik/Lux/blob/master/LICENSE
[release-badge]:https://img.shields.io/github/v/release/Sidhant-Roymoulik/Lux?style=for-the-badge&label=official%20release
[release-link]:https://github.com/Sidhant-Roymoulik/Lux/releases/latest
[commits-badge]:https://img.shields.io/github/commits-since/Sidhant-Roymoulik/Lux/latest?style=for-the-badge
[commits-link]:https://github.com/Sidhant-Roymoulik/Lux/commits/master
