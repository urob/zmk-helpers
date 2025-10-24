/*                              HUMMINGBIRD KEY MATRIX / LAYOUT MAPPING

  ╭────────────────────┬────────────────────╮ ╭─────────────────────┬─────────────────────╮
  │  0   1   2   3   4 │  5   6   7   8   9 │ │ LT4 LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 RT4 │
  │ 10  11  12  13  14 │ 15  16  17  18  19 │ │ LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 │
  ╰───╮ 20  21  22     │     23  24  25 ╭───╯ ╰───╮ LB3 LB2 LB2     │     RB1 RB2 RB3 ╭───╯
      ╰───────╮ 30  31 │ 32  33 ╭───────╯         ╰───────╮ LH1 LH0 │ RH0 RH1 ╭───────╯
              ╰────────┴────────╯                         ╰─────────┴─────────╯             */

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

#define LM0 14  // left-middle row
#define LM1 13
#define LM2 12
#define LM3 11
#define LM4 10

#define RM0 15  // right-middle row
#define RM1 16
#define RM2 17
#define RM3 18
#define RM4 19

#define LB1 22 // left-bottom row
#define LB2 21
#define LB3 20

#define RB1 23 // right-bottom row
#define RB2 24
#define RB3 25

#define LH0 31  // left thumb keys
#define LH1 30

#define RH0 32  // right thumb keys
#define RH1 33
