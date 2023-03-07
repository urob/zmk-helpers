/*                                      44 KEY MATRIX / LAYOUT MAPPING

    ╭────────────────────────┬────────────────────────╮       ╭─────────────────────────┬─────────────────────────╮
 ╭──╯  1   2   3   4   5   6 │  7   8   9  10  11  12 ╰──╮ ╭──╯ LT5 LT4 LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 RT4 RT5 ╰──╮
 │ 0  14  15  16  17  18  19 │ 20  21  22  23  24  25  13│ │LT6 LM5 LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 RM5 RT6│
 ╰──╮ 26  27  28  29  30  31 │ 32  33  34  35  36  37 ╭──╯ ╰──╮ LB5 LB4 LB3 LB2 LB1 LB0 │ RB0 RB1 RB2 RB3 RB4 RB5 ╭──╯
    ╰───────────╮ 38  39  40 │ 41  42  43 ╭───────────╯       ╰───────────╮ LH2 LH1 LH0 │ RH0 RH1 RH2 ╭───────────╯
                ╰────────────┴────────────╯                               ╰─────────────┴─────────────╯             */

#pragma once

#define LT0  6  // left-top row + appendix
#define LT1  5
#define LT2  4
#define LT3  3
#define LT4  2
#define LT5  1
#define LT6  0

#define RT0  7 // right-top row + appendix
#define RT1  8
#define RT2  9
#define RT3 10
#define RT4 11
#define RT5 12
#define RT6 13

#define LM0 19  // left-middle row
#define LM1 18
#define LM2 17
#define LM3 16
#define LM4 15
#define LM5 14

#define RM0 20  // right-middle row
#define RM1 21
#define RM2 22
#define RM3 23
#define RM4 24
#define RM5 25

#define LB0 31  // left-bottom row
#define LB1 30
#define LB2 29
#define LB3 28
#define LB4 27
#define LB5 26

#define RB0 32  // right-bottom row
#define RB1 33
#define RB2 34
#define RB3 35
#define RB4 36
#define RB5 37

#define LH0 40  // left thumb keys
#define LH1 39
#define LH2 38

#define RH0 41  // right thumb keys
#define RH1 42
#define RH2 43
