/*                               GLOVE80 KEY MATRIX / LAYOUT MAPPING
 ╭────────────────────╮       ╭────────────────────╮ ╭────────────────────╮       ╭────────────────────╮
 │  0   1   2   3   4 ╰───┬───╯  5   6   7   8   9 │ │ LC5 LC4 LC3 LC2 LC1╰───┬───╯ RC1 RC2 RC3 RC4 RC5│
 │ 10  11  12  13  14  15 │ 16  17  18  19  20  21 │ │ LN5 LN4 LN3 LN2 LN1 LN0│ RN0 RN1 RN2 RN3 RN4 RN5│
 │ 22  23  24  25  26  27 │ 28  29  30  31  32  33 │ │ LT5 LT4 LT3 LT2 LT1 LT0│ RT0 RT1 RT2 RT3 RT4 RT5│
 │ 34  35  36  37  38  39 │ 40  41  42  43  44  45 │ │ LM5 LM4 LM3 LM2 LM1 LM0│ RM0 RM1 RM2 RM3 RM4 RM5│
 │ 46  47  48  49  50  51 │ 58  59  60  61  62  63 │ │ LB5 LB4 LB3 LB2 LB1 LB0│ RB0 RB1 RB2 RB3 RB4 RB5│
 │ 64  65  66  67  68 ╭───┴───╮ 75  76  77  78  79 │ │ LF5 LF4 LF3 LF2 LF1╭───┴───╮ RF1 RF2 RF3 RF4 RF5│
 ╰───────────┬────────┴───┬───┴────────┬───────────╯ ╰───────────┬────────┴───┬───┴────────┬───────────╯
             │ 52  53  54 │ 55  56  57 │                         │ LH5 LH4 LH3│ RH3 RH4 RH5│
             │ 69  70  71 │ 72  73  74 │                         │ LH2 LH1 LH0│ RH0 RH1 RH2│
             ╰────────────┴────────────╯                         ╰────────────┴────────────╯
 */

#pragma once

/*
 * Convenience macro allowing for layer definitions in a key arrangement like
 * the above key matrix. See https://github.com/urob/zmk-nodefree-config/pull/22
 * for a template. (Mind the commas!)
 *
 * Note that this file needs to be sourced *after* helper.h so that ZMK_LAYER is
 * already defined.
 */

#define GLV80_LAYER(name, start, mid, end, thumb_row_1, thumb_row_2) \
  ZMK_LAYER(name, start thumb_row_1 mid thumb_row_2 end)

#define LC1  4  // left-ceiling row
#define LC2  3
#define LC3  2
#define LC4  1
#define LC5  0

#define RC1  5  // right-ceiling row
#define RC2  6
#define RC3  7
#define RC4  8
#define RC5  9

#define LN0 15  // left-number row
#define LN1 14
#define LN2 13
#define LN3 12
#define LN4 11
#define LN5 10

#define RN0 16  // right-number row
#define RN1 17
#define RN2 18
#define RN3 19
#define RN4 20
#define RN5 21

#define LT0 27  // left-top row
#define LT1 26
#define LT2 25
#define LT3 24
#define LT4 23
#define LT5 22

#define RT0 28  // right-top row
#define RT1 29
#define RT2 30
#define RT3 31
#define RT4 32
#define RT5 33

#define LM0 39  // left-middle row
#define LM1 38
#define LM2 37
#define LM3 36
#define LM4 35
#define LM5 34

#define RM0 40  // right-middle row
#define RM1 41
#define RM2 42
#define RM3 43
#define RM4 44
#define RM5 45

#define LB0 51  // left-bottom row
#define LB1 50
#define LB2 49
#define LB3 48
#define LB4 47
#define LB5 46

#define RB0 58  // right-bottom row
#define RB1 59
#define RB2 60
#define RB3 61
#define RB4 62
#define RB5 63

#define LF1 68  // left-floor row
#define LF2 67
#define LF3 66
#define LF4 65
#define LF5 64

#define RF1 75  // right-floor row
#define RF2 76
#define RF3 77
#define RF4 78
#define RF5 79

#define LH0 71  // left thumb keys
#define LH1 70
#define LH2 69
#define LH3 54
#define LH4 53
#define LH5 52

#define RH0 72  // right thumb keys
#define RH1 73
#define RH2 74
#define RH3 55
#define RH4 56
#define RH5 57
