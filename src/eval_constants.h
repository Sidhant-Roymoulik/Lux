#pragma once

#include "types.h"

#define S Score

int PhaseValues[6] = {0, 1, 1, 2, 4, 0};

Score PieceValues[6] = {S(111, 80), S(416, 307), S(402, 306), S(533, 565), S(1293, 944), S(20000, 20000)};

Score PST[6][64] = {
    // Pawn PSTS
    {S(0, 0),     S(0, 0),     S(0, 0),    S(0, 0),     S(0, 0),     S(0, 0),    S(0, 0),    S(0, 0),
     S(119, 173), S(146, 149), S(89, 140), S(145, 103), S(104, 120), S(186, 87), S(12, 155), S(-24, 191),
     S(3, 94),    S(-6, 91),   S(26, 70),  S(35, 46),   S(70, 23),   S(85, 29),  S(18, 64),  S(-4, 76),
     S(-10, 34),  S(1, 19),    S(3, 11),   S(28, -12),  S(29, -7),   S(21, 0),   S(11, 8),   S(-14, 18),
     S(-27, 18),  S(-25, 11),  S(-2, -1),  S(17, -13),  S(23, -9),   S(19, -8),  S(-2, -2),  S(-20, 3),
     S(-18, 6),   S(-27, 6),   S(-5, -4),  S(-5, 3),    S(10, 3),    S(18, -4),  S(23, -12), S(0, -8),
     S(-29, 22),  S(-20, 8),   S(-27, 19), S(-16, 19),  S(-9, 19),   S(36, 1),   S(32, -9),  S(-11, -3),
     S(0, 0),     S(0, 0),     S(0, 0),    S(0, 0),     S(0, 0),     S(0, 0),    S(0, 0),    S(0, 0)},
    // Knight PSTS
    {S(-204, -34), S(-115, -22), S(-55, 9),  S(-50, -11), S(86, -27), S(-109, -10), S(-23, -58), S(-117, -89),
     S(-94, -7),   S(-55, 12),   S(89, -19), S(31, 16),   S(25, 5),   S(84, -20),   S(-3, -10),  S(-19, -40),
     S(-48, -15),  S(74, -11),   S(52, 25),  S(83, 23),   S(114, 2),  S(162, -5),   S(101, -14), S(64, -41),
     S(3, -7),     S(39, 14),    S(31, 42),  S(77, 35),   S(59, 36),  S(98, 22),    S(42, 17),   S(42, -11),
     S(0, -8),     S(26, 4),     S(41, 28),  S(33, 41),   S(52, 30),  S(44, 30),    S(43, 16),   S(8, -8),
     S(-10, -18),  S(8, 10),     S(34, 5),   S(41, 22),   S(54, 19),  S(47, -0),    S(47, -11),  S(1, -21),
     S(-11, -41),  S(-36, -12),  S(7, 3),    S(28, 4),    S(31, 8),   S(42, -12),   S(2, -17),   S(4, -41),
     S(-121, -8),  S(-2, -38),   S(-37, -8), S(-17, -1),  S(13, -13), S(-3, -11),   S(3, -38),   S(-12, -71)},
    // Bishop PSTS
    {S(-28, -2),  S(-6, -9),  S(-145, 19), S(-89, 13), S(-66, 20), S(-57, 9), S(-31, 5),  S(2, -14),
     S(-34, 10),  S(-1, 4),   S(-35, 17),  S(-52, 5),  S(18, 4),   S(48, -2), S(2, 6),    S(-51, 0),
     S(-18, 14),  S(31, -0),  S(37, 2),    S(27, -0),  S(31, 0),   S(57, 3),  S(33, 7),   S(4, 14),
     S(-0, 5),    S(12, 12),  S(12, 15),   S(51, 7),   S(35, 10),  S(30, 8),  S(13, 3),   S(8, 10),
     S(5, -2),    S(20, 4),   S(12, 13),   S(34, 13),  S(39, -1),  S(9, 6),   S(14, -1),  S(22, -6),
     S(13, -8),   S(31, -1),  S(29, 7),    S(16, 7),   S(24, 12),  S(46, -5), S(31, -1),  S(24, -13),
     S(20, -10),  S(40, -21), S(30, -7),   S(16, 3),   S(27, 1),   S(37, -3), S(61, -26), S(19, -27),
     S(-20, -10), S(20, -2),  S(13, 2),    S(5, 4),    S(9, 3),    S(10, 6),  S(-29, 8),  S(-5, -11)},
    // Rook PSTS
    {S(10, 28),  S(24, 21),  S(-14, 37), S(41, 19),  S(44, 21),  S(-14, 31), S(2, 28),  S(17, 22),
     S(12, 27),  S(6, 31),   S(50, 19),  S(55, 17),  S(80, -2),  S(87, 6),   S(-1, 31), S(36, 18),
     S(-26, 27), S(-7, 26),  S(-7, 23),  S(-4, 24),  S(-27, 25), S(48, 4),   S(77, -0), S(8, 10),
     S(-34, 24), S(-29, 22), S(-17, 32), S(-4, 17),  S(-7, 19),  S(32, 12),  S(-4, 11), S(-20, 20),
     S(-40, 22), S(-31, 24), S(-23, 25), S(-19, 20), S(-0, 10),  S(-3, 9),   S(21, 2),  S(-22, 8),
     S(-32, 12), S(-18, 16), S(-13, 7),  S(-15, 12), S(5, 3),    S(17, -1),  S(12, 3),  S(-11, -4),
     S(-22, 6),  S(-7, 8),   S(-14, 14), S(1, 13),   S(14, 1),   S(29, -2),  S(15, -4), S(-43, 11),
     S(8, 9),    S(7, 12),   S(14, 11),  S(26, 4),   S(31, -2),  S(36, 0),   S(-7, 10), S(12, -9)},
    // Queen PSTS
    {S(-30, 3),   S(-27, 49), S(-8, 42),  S(2, 37),   S(113, -8), S(110, -14), S(78, -8),  S(57, 38),
     S(-30, 1),   S(-58, 30), S(-21, 40), S(-20, 57), S(-54, 86), S(59, 18),   S(20, 39),  S(64, 13),
     S(-3, -22),  S(-22, 2),  S(6, -17),  S(-19, 56), S(25, 36),  S(77, 15),   S(62, 17),  S(67, 22),
     S(-37, 25),  S(-28, 17), S(-25, 14), S(-22, 23), S(-6, 46),  S(3, 44),    S(-4, 78),  S(0, 71),
     S(2, -28),   S(-31, 29), S(-0, -7),  S(-11, 33), S(2, 7),    S(4, 22),    S(2, 54),   S(5, 42),
     S(-11, 11),  S(16, -40), S(4, -3),   S(18, -34), S(13, -8),  S(16, 9),    S(22, 24),  S(12, 43),
     S(-17, -12), S(13, -36), S(30, -39), S(30, -40), S(41, -47), S(44, -38),  S(17, -37), S(32, -30),
     S(18, -32),  S(17, -47), S(27, -42), S(35, -7),  S(16, -8),  S(-1, -17),  S(-5, -6),  S(-37, -29)},
    // King PSTS
    {S(-109, -78), S(188, -74), S(180, -57), S(102, -46), S(-151, 13), S(-84, 31), S(50, -6),  S(64, -29),
     S(228, -60),  S(67, 4),    S(37, 8),    S(113, -2),  S(30, 14),   S(43, 34),  S(-34, 30), S(-150, 38),
     S(75, -6),    S(73, 11),   S(97, 10),   S(15, 16),   S(37, 14),   S(110, 36), S(134, 28), S(-10, 11),
     S(11, -19),   S(-14, 24),  S(9, 28),    S(-54, 40),  S(-58, 39),  S(-60, 47), S(-23, 35), S(-97, 16),
     S(-90, -9),   S(14, -5),   S(-74, 37),  S(-136, 50), S(-141, 55), S(-95, 42), S(-89, 25), S(-105, 1),
     S(-4, -26),   S(-17, 0),   S(-57, 23),  S(-98, 38),  S(-96, 42),  S(-83, 34), S(-34, 14), S(-50, -4),
     S(5, -38),    S(9, -13),   S(-41, 16),  S(-101, 28), S(-77, 28),  S(-54, 19), S(2, -4),   S(11, -27),
     S(-21, -67),  S(43, -50),  S(12, -27),  S(-95, 2),   S(-14, -21), S(-50, -5), S(30, -38), S(19, -64)},
};

Score BishopPair   = S(33, 110);
Score OpenFile     = S(28, 31);
Score SemiOpenFile = S(17, 15);
Score PawnDoubled  = S(-11, -48);
Score PawnDoubled2 = S(-10, -25);
Score PawnSupport  = S(22, 17);