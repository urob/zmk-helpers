/*  Zilpzalp keyboard layout

     ╭─────────────────┬────────────────╮        ╭──────────────────┬─────────────────╮
  ╭──╯   0   1   2   3 │  4   5   6   7 ╰───╮ ╭──╯  LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 ╰───╮
  │  8   9  10  11  12 │ 13  14  15  16  17 │ │ LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 │
  ╰───╮ 18  19  20     │     21  22  23 ╭───╯ ╰───╮ LB3 LB2 LB1     │     RB1 RB2 RB3 ╭───╯
      ╰───────╮ 24  25 │ 26  27 ╭───────╯         ╰───────╮ LH1 LH0 │ RH0 RH1 ╭───────╯
              ╰────────┴────────╯                         ╰─────────┴─────────╯             */

#pragma once

#define LT0  3  // left-top row
#define LT1  2
#define LT2  1
#define LT3  0

#define RT0  4  // right-top row
#define RT1  5
#define RT2  6
#define RT3  7

#define LM0 12  // left-middle row
#define LM1 11
#define LM2 10
#define LM3 9
#define LM4 8

#define RM0 13  // right-middle row
#define RM1 14
#define RM2 15
#define RM3 16
#define RM4 17

#define LB1 20 // left-bottom row
#define LB2 19
#define LB3 18

#define RB1 21 // right-bottom row
#define RB2 22
#define RB3 23

#define LH0 25  // left thumb keys
#define LH1 24

#define RH0 26  // right thumb keys
#define RH1 27

#define NUMROW 
#define KEYS_L LT0 LT1 LT2 LT3 LM0 LM1 LM2 LM3 LM4 LB1 LB2 LB3
#define KEYS_R RT0 RT1 RT2 RT3 RM0 RM1 RM2 RM3 RM4 RB1 RB2 RB3
#define THUMBS_L LH0 LH1
#define THUMBS_R RH0 RH1
#define THUMBS THUMBS_L THUMBS_R
