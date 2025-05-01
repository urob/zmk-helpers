/*                                      42 KEY MATRIX / LAYOUT MAPPING

  ╭────────────────────────────┬────────────────────────────╮ ╭──────────────────────────────┬─────────────────────────────╮
  │      0   1   2   3   4     │      5   6   7   8   9     │ │     LT4 LT3 LT2 LT1 LT0      │     RT0 RT1 RT2 RT3 RT4     │
  │ 10  11  12  13  14  15     │     16  17  18  19  20  21 │ │ LM5 LM4 LM3 LM2 LM1 LM0      │     RM0 RM1 RM2 RM3 RM4 RM5 │
  │ 22  23  24  25  26  27  28 │ 29  30  31  32  33  34  35 │ │ LB5 LB4 LB3 LB2 LB1 LB0  LEC │ REC RB0 RB1 RB2 RB3 RB4 RB5 │
  ╰───────────╮ 36  37  38  39 │ 40  41  42  43   ╭─────────╯ ╰────────────╮ LH3 LH2 LH1 LH0 │ RH0 RH1 RH2 RH3 ╭───────────╯
              ╰────────────────┴──────────────────╯                        ╰─────────────────┴─────────────────╯             */

#pragma once

#define LT0  4  // left-top row
#define LT1  3
#define LT2  2
#define LT3  1
#define LT4  0

#define RT0  5  // right-top row
#define RT1  6
#define RT2  7
#define RT3  8
#define RT4  9

#define LM0 15  // left-middle row
#define LM1 14
#define LM2 13
#define LM3 12
#define LM4 11
#define LM5 10

#define RM0 16  // right-middle row
#define RM1 17
#define RM2 18
#define RM3 19
#define RM4 20
#define RM5 21

#define LB0 27  // left-bottom row
#define LB1 26
#define LB2 25
#define LB3 24
#define LB4 23
#define LB5 22

#define RB0 30  // right-bottom row
#define RB1 31
#define RB2 32
#define RB3 33
#define RB4 34
#define RB5 35

#define LH0 39  // left thumb keys
#define LH1 38
#define LH2 37
#define LH3 36

#define RH0 40  // right thumb keys
#define RH1 41
#define RH2 42
#define RH3 43

#define LEC 28  // encoders
#define REC 29

