# zmk-nodefree-config

ZMK lets user customize their keyboard layout by providing a Devicetree file
(`.keymap`). The specific syntax requirements of the Devicetree file format can,
however, make this process a bit daunting for new users. 

This repository provides simple convenience macros that simplify the configuration for
many common use cases. It results in a "node-free" user configuration with a more
streamlined syntax. Check out [example.keymap](example.keymap) to see it in action.

See [changelog](#changelog) for latest changes.

## Overview

The following convenience macros are provided:
1. `ZMK_BEHAVIOR` creates behaviors such as hold-taps, tap-dances or
   ZMK macros [\[doc\]](#zmk_behavior)
2. `ZMK_LAYER` adds layers to the keymap [\[doc\]](#zmk_layer)
3. `ZMK_COMBO` defines combos [\[doc\]](#zmk_combo)
4. `ZMK_CONDITIONAL_LAYER` sets up "tri-layer" conditions [\[doc\]](#zmk_conditional_layer)
5. `ZMK_UNICODE_SINGLE` and `ZMK_UNICODE_PAIR` create unicode characters [\[doc\]](#zmk_unicode)
6. `international_chars` provides character definitions for some non-English languages
   [\[doc\]](#international-characters)
7. `keypos_def` provides human-readable key position shortcuts for some popular
   keyboards that simplify the configuration of combos and positional hold-taps
   [\[doc\]](#key-position-helpers)

## Quickstart

1. Copy this repository into the root folder of your zmk-config (or add as submodule[^1]). The
   folder structure should look as follows:
   ```
    zmk-config
     ├── config
     │    ├── your.keyboard.conf
     │    ├── your_keyboard.keymap
     │    └── ...
     ├── zmk-nodefree-config
     │    ├── helper.h
     │    ├── ...
   ```
2. Source `helper.h` near the top of your `.keymap` file:
    ```C++
    #include "../zmk-nodefree-config/helper.h"
    ```
3. Customize your keyboard's `.keymap` file. See [example.keymap](example.keymap) or [my
   personal zmk-config](https://github.com/urob/zmk-config/blob/main/config/base.keymap)
   for a complete configuration, and read the documentation below for details.

## Configuration details

### ZMK\_BEHAVIOR

`ZMK_BEHAVIOR` can be used to create any of the following ZMK behaviors: caps-word,
hold-tap, key-repeat, macro, mod-morph, sticky-key, tap-dance or tri-state.

**Syntax:** `ZMK_BEHAVIOR(name, type, specification)`
* `name`: a unique string chosen by the user (e.g., `my_behavior`). The new behavior can
  be added to the keymap using `&name` (e.g., `&my_behavior`).
* `type`: the behavior to be created. It must be one of the following:
  `caps_word`, `hold_tap`, `key_repeat`, `macro`, `macro_one_param`,
  `macro_two_param`, `mod_morph`, `sticky_key`, `tap_dance` or `tri_state`.
  Note that multiword behaviors are separated by underscores (`_`).
* `specification`: the custom behavior code. It should contain the
  body of the corresponding [ZMK behavior configuration](https://zmk.dev/docs/config/behaviors)
  without the `label`, `#binding-cells` and `compatible` properties and without the
  surrounding node-specification.

#### Example 1: Creating a custom "homerow mod" tap-hold behavior

```C++
ZMK_BEHAVIOR(hrm, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&kp>, <&kp>;
)
```

This creates a custom "homerow mod" that can be added to the keymap using `&hrm`. For example,
`&hrm LSHIFT T` creates a key that yields `T` on tap and `LSHIFT` on hold.

#### Example 2: Creating a custom tap-dance key

```C++
ZMK_BEHAVIOR(ss_cw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&sk LSHFT>, <&caps_word>;
)
```
This behavior yields sticky-shift on tap and caps-word on double tap. It can be added to
the keymap using `&ss_cw`. 

#### Example 3: Creating a custom "win-sleep" macro

```C++
ZMK_BEHAVIOR(win_sleep, macro,
    wait-ms = <100>;
    tap-ms = <5>;
    bindings = <&kp LG(X) &kp U &kp S>;
)
```

This creates a "Windows sleep macro" that can be added to the keymap using `&win_sleep`.

### ZMK\_LAYER

`ZMK_LAYER` adds new keymap layers to the configuration.

**Syntax:** `ZMK_LAYER(name, layout, sensors)`
* `name`: a unique identifier string chosen by the user (it will be displayed on keyboards with appropriately configured displays)
* `layout`: the layout specification using the same syntax as the `bindings`
  property of the [ZMK keymap configuration](https://zmk.dev/docs/config/keymap)
* `sensors` (optional): provides sensor-specification if specified

Multiple layers can be added with repeated calls of `ZMK_LAYER`. They will be ordered
in the same order in which they are created, with the first-specified layer being
the "lowest" one ([see here for details](https://zmk.dev/docs/features/keymaps#layers)).

#### Example usage
```C++
ZMK_LAYER(default_layer,
     // ╭─────────────┬─────────────┬─────────────┬─────────────┬─────────────╮   ╭─────────────┬─────────────┬─────────────┬─────────────┬─────────────╮
          &kp Q         &kp W         &kp F         &kp P         &kp B             &kp J         &kp L         &kp U         &kp Y         &kp SQT
     // ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
          &hrm LGUI A   &hrm LALT R   &hrm LCTRL S  &hrm LSHFT T  &kp G             &kp M         &hrm RSHFT N  &hrm LCTRL E  &hrm LALT I   &hrm LGUI O
     // ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
          &kp Z         &kp X         &kp C         &kp D         &kp V             &kp K         &kp H         &kp COMMA     &kp DOT       &kp SEMI
     // ╰─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤   ├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
                                      &kp ESC       &lt NAV SPACE &kp TAB           &kp RET       &ss_cw        &bs_del_num
     //                             ╰─────────────┴──── ────────┴─────────────╯   ╰─────────────┴─────────────┴─────────────╯
)

```

### ZMK\_COMBO

`ZMK_COMBO` defines new combos.

**Syntax:** `ZMK_COMBO(name, bindings, keypos, layers, timeout)`
* `name`: a unique identifier string chosen by the user (usually there is not reason to reference this elsewhere)
* `binding`: the binding triggered by the combo (this can be any stock or previously defined behavior)
* `keypos`: a list of 2 or more key positions that trigger the combo (e.g., `12
  13`). Note that the mapping from key positions to keys depends on your keyboard. To facilitate 
  the combo setup and increase portability, one can use key-position helpers instead.
  See [below](#key-position-helpers) on how to use them.
* `layers`: a list of layers for which the combo is active (e.g., `0 1` for the first
  two layers). If set to `ALL` the combo is active on all layers.
* `timeout` (optional): combo timeout in ms. If omitted the timeout is set to the
  global value of `COMBO_TERM`, which defaults to 30ms and can be overwritten by the
  user as in the second example below.

#### Example: escape combo

```C++
ZMK_COMBO(esc,  &kp ESC, 0 1, ALL, 25)
```
This creates an "escape" combo that is active on all layers and which is triggered when
the 0th and 1st keys are
pressed jointly within 25ms.

#### Example: copy and paste combos (using global COMBO_TERM)

```C++
#undef COMBO_TERM
#define COMBO_TERM 50
ZMK_COMBO(copy,  &kp LC(C), 12 13, ALL)
ZMK_COMBO(paste, &kp LC(V), 13 14, ALL)
```
This sets the global combo timeout to 50ms, and then creates two combos which both are
active on all layers. The first combo is triggered when the 12th and 13th keys are
pressed jointly within the `COMBO_TERM`, sending <kbd>Ctrl</kbd> + <kbd>C</kbd>. The
second combo is triggered when the 13th and 14th keys are pressed jointly, sending
<kbd>Ctrl</kbd> + <kbd>V</kbd>.

### ZMK\_CONDITIONAL\_LAYER

This sets up tri-layer conditions.

**Syntax:** `ZMK_CONDITIONAL_LAYER(if_layers, then_layers)`
* `if_layers`: a list of layers which trigger the `then_layer` if simultaneously active
* `then_layer`: the layer which is activated when the if-condition is met. Due to ZMK's
  layering model, it should generally have a higher number than the `if_layers`

For instance, this triggers "layer 3" if layers "1" and "2" are
simultaneously active. 
```C++
ZMK_CONDITIONAL_LAYER(1 2, 3)
```
Mind that ZMK's layer numbering starts at 0. One can use layer
definitions, as demonstrated in [example.keymap](example.keymap), to simplify life.

### ZMK\_UNICODE

There are two macros that create new unicode characters that
can be added to the keymap. `ZMK_UNICODE_SINGLE` creates single unicode characters such
as <kbd>€</kbd>, and `ZMK_UNICODE_PAIR` creates pairs of shifted/unshifted unicode
characters that are useful for specifying international characters such as
<kbd>ä</kbd>/<kbd>Ä</kbd> or <kbd>δ</kbd>/<kbd>Δ</kbd>.


**Syntax:** `ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3)`
* `name:` a unique string chosen by the user (e.g., `my_char`). The unicode character  can
  be added to the keymap using `&name` (e.g., `&my_char`)
* `L0` to `L3`: a 4-digit sequence defining the unicode string using standard [ZMK key
  codes](https://zmk.dev/docs/codes/keyboard-keypad)

**Syntax:** `ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3)`
* `name:` a unique string chosen by the user (e.g., `my_char`). The unicode character  can
  be added to the keymap using `&name` (e.g., `&my_char`)
* `L0` to `L3`: a 4-digit sequence defining the unshifted unicode string
* `U0` to `U3`: a 4-digit sequence defining the shifted unicode string (which is send when
  holding <kbd>Shift</kbd> while pressing <kbd>&name</kbd>)

Note: 5-digit unicode characters are currently not supported (but would be easy to add
if there is interest).

#### Example 1: Euro sign (€)

```C++
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)
```
This creates a Euro character that can be added to the keymap using `&euro_sign`.

#### Example 2: German umlauts (ä/Ä, ö/Ö, ü/Ü)

```C++
//                name     unshifted         shifted
ZMK_UNICODE_PAIR( de_ae,   N0, N0,  E, N4,   N0, N0,  C, N4 )
ZMK_UNICODE_PAIR( de_oe,   N0, N0,  F, N6,   N0, N0,  D, N6 )
ZMK_UNICODE_PAIR( de_ue,   N0, N0,  F,  C,   N0, N0,  D,  C )
```
The creates "umlaut" pairs that can be added to the keymap using `&de_ae`, `&de_oe` and `&de_ue`.

#### Dependencies for unicode


* `ZMK_UNICODE_PAIR` requires a current ZMK after [PR
  #1412](https://github.com/zmkfirmware/zmk/pull/1412) was merged into main. If you are
  building with Github Actions using the default `west.yml` you are all set.
  <!-- If you need help maintaining
  your own ZMK repository, check out [this
  guide](https://gist.github.com/urob/68a1e206b2356a01b876ed02d3f542c7). If you don't
  want to maintain your own ZMK repository, you can use ZMK's [beta
  testing](https://zmk.dev/docs/features/beta-testing) feature to configure Github
  Actions to build against a patched remote branch of ZMK. To do so, replace the
  contents of `west.yml` in your `zmk-config/config` directory with the following
  contents, which adds the required patch:
    ```
    manifest:
      remotes:
        - name: urob
          url-base: https://github.com/urob
      projects:
        - name: zmk
          remote: urob
          revision: fix-mod-morph
          import: app/west.yml
      self:
        path: config
    ```
    -->
* The input of unicode characters differs across operating systems. By
    default, `ZMK_UNICODE` is configured for Windows (using WinCompose). To set it up
    for another OS, set the variable
    `HOST_OS` **before** sourcing `helper.h`.

    For Linux use:
    ```C++
    #define HOST_OS 1  // set to 1 for Linux, default is 0 (Windows)
    #include helper.h
    ```
    For macOS/Windows-Alt-Codes use:
    ```C++
    #define HOST_OS 2  // set to 2 for macOS/Windows-Alt-Codes, default is 0 (Windows)
    #include helper.h
    ```
    This will send unicode characters using the OS's default input channels.
    For non-default input channels or for other operating systems, one can instead set the
    variables `OS_UNICODE_LEAD` and `OS_UNICODE_TRAIL` to the character sequences that
    initialize/terminate the unicode input.[^2]

* On Windows and macOS there are additional requirements for unicode input to work. On
  Windows, one must install [WinCompose](https://github.com/samhocevar/wincompose) for
  full support (or use Win-Alt-Codes for limited support in select software). On
  macOS one must enable unicode input in the system preferences, by selecting 
  `Unicode Hex Input` as input source.

### International characters

There are pre-defined definitions for international characters for a few languages  ---
currently Danish, French, German, Greek and Swedish (contributions are welcome)[^3].
These can be loaded by sourcing the corresponding files; e.g.:
```C++
#include "../zmk-nodefree-config/international_chars/danish.dtsi"
#include "../zmk-nodefree-config/international_chars/french.dtsi"
#include "../zmk-nodefree-config/international_chars/german.dtsi"
#include "../zmk-nodefree-config/international_chars/greek.dtsi"
#include "../zmk-nodefree-config/international_chars/swedish.dtsi"
```
Once sourced, international characters can be added to the keymap using, e.g., `&de_ae`,
`&dk_ae`, `&fr_a_grave`, `&el_alpha` or `&sv_ao` (each language has its own prefix; see
the language files for a complete list of available characters).

**Dependencies:** These definitions make use of unicode in the background,
see the unicode section above for [prerequisites](#dependencies-for-unicode).

**Note:** Windows-Alt-Codes use different keycode sequences than the
usual unicode sequences, requiring different definitions. Currently, they are
pre-defined for German:
```C++
#include "../zmk-nodefree-config/international_chars/german_alt.dtsi"
```

### Key-position helpers

Certain configuration options such as combos and positional hold-taps are based on the
physical position of keys on the keyboard. This can be cumbersome and reduces
portability of configuration files across keyboards with different layouts. 

To increase portability and ease of use, this repo provides optional key-position
helpers for some popular keyboard layouts (58-key boards such as Lily58, 48-key boards
such as Planck, 42-key boards such as Corne, 36-key boards and 34-key boards).

These key-position helpers provide a map from the physical key positions to human-readable shortcuts.
All shortcuts are of the following form:
* `L/R` for **L**eft/**R**ight hand
* `T/M/B/H` for **T**op/**M**iddle/**B**ottom and t**H**umb row.
* `0/1/2/3/4` for the finger position starting from the inside (`0` is the inner
  index-finger column, `1` is the home position of the index finger, ..., `4` is the home
  position of the pinkie)

For instance, the shortcuts layout for a 36-key board looks as follows:
```
╭─────────────────────┬─────────────────────╮
│ LT4 LT3 LT2 LT1 LT0 │ RT0 RT1 RT2 RT3 RT4 │
│ LM4 LM3 LM2 LM1 LM0 │ RM0 RM1 RM2 RM3 RM4 │
│ LB4 LB3 LB2 LB1 LB0 │ RB0 RB1 RB2 RB3 RB4 │
╰───────╮ LH2 LH1 LH0 │ RH0 RH1 RH2 ╭───────╯
        ╰─────────────┴─────────────╯
```
Schematics for all supported keyboards can be found in the corresponding
definition files in the `keypos_def` folder.

To use these key-position helpers, source the definition file for your keyboard
into your `.keymap` file. E.g., for a 36-key board, use:
```C++
#include "../zmk-nodefree-config/keypos_def/keypos_36keys.h"
```

#### Example 1: Defining combos using key-position helpers

```C++
ZMK_COMBO(copy,  &kp LC(C), LB2 LB3, ALL)
ZMK_COMBO(paste, &kp LC(V), LB1 LB2, ALL)
```

This defines a "copy"-combo for the middle + ring finger on the left bottom row, and a
"paste"-combo for the index + middle finger on the left bottom row. Both combos are active on all layers.

#### Example 2: Home-row mods with positional hold-taps

Here we use ZMK's [positional
hold-tap](https://zmk.dev/docs/behaviors/hold-tap#positional-hold-tap-and-hold-trigger-key-positions)
feature to make home-row mods only trigger with "opposite hand" keys. Using
key-position helpers makes this straightforward: 

```C++
#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left-hand keys
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right-hand keys
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumb keys

ZMK_BEHAVIOR(hml, hold_tap,  // left-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_R THUMBS>;
)

ZMK_BEHAVIOR(hmr, hold_tap,  // right-hand HRMs
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&kp>, <&kp>;
    hold-trigger-key-positions = <KEYS_L THUMBS>;
)
```

## Changelog

* **8/7/2023:** Keypos definition for Glove 80 (added by [@hylophile](https://github.com/hylophile))
* **6/27/2023:** Support for parametrized macros (added by
  [@JeffDess](https://github.com/JeffDess))
* **6/4/2023:** Keypos definitions for Kyria and Hillside keyboards (added by
  [@autoferrit](https://github.com/autoferrit))
* **5/21/2023:** Keypos definitions for Sofle (added by
  [@titus-ong](https://github.com/titus-ong))
* **4/23/2023:** Support for dynamic-macros, requires PR #1351 (added by
  [@theol0403](https://github.com/theol0403))
* **3/7/2023:** Keypos definitions for 44-key boards like Jian/Jorne (added by
  [@alparo](https://github.com/alparo)) and for Kinesis Adv 360 Pro
* **1/3/2023:** Optional `TIMEOUT` argument for `ZMK_COMBO` subsuming the now
  depreciated `ZMK_COMBO_ADV`
* **1/2/2023:** Optional sensor-bindings argument to `ZMK_LAYER` + keypos
  definitions for lily58 (added by [@laureyn](https://github.com/laureyn))
* **12/28/2022:** French chars (added by [@artggd](https://github.com/artggd))
* **12/18/2022:** Use layer name as display label
* **11/16/2022:** Danish chars (added by
  [@zonique2k](https://github.com/zonique2k))
* **11/09/2022:** Support for tri-state behavior (aka "swapper"), requires PR
  #1366
* **10/16/2022:** Remove dependency on PR #1412 as it is now merged into main
* **10/8/2022:** Remove depreciated masked-mods option from unicode helper
* **9/11/2022:** Support for Windows-Alt-Codes
* **8/5/2022:** New macro `ZMK_COMBO_ADV` for "advanced" combo setups.
  **Note:** depreciated as of 1/3/2023
* **7/31/2022:** Switch unicode dependency from PR #1114 to [PR
  #1412](https://github.com/zmkfirmware/zmk/pull/1412)

[^1]: If building with Github Actions, using submodules requires replacing
  `.github/workflows/build.yml` in the local `zmk-config` with
    ```
    on: [push, pull_request, workflow_dispatch]

    jobs:
      build:
        uses: urob/zmk/.github/workflows/build-user-config.yml@build-with-submodules
    ```

[^2]: The default for Windows is `OS_UNICODE_LEAD` set to tap <kbd>Right Alt</kbd>
    followed by <kbd>U</kbd> and `OS_UNICODE_TRAIL` set to tap <kbd>Return</kbd>. 
    The default for Linux is `OS_UNICODE_LEAD` set to tap <kbd>Shift</kbd> +
    <kbd>Ctrl</kbd> + <kbd>U</kbd> and `OS_UNICODE_TRAIL` set to tap <kbd>Space</kbd>. 
    The default for macOS is `OS_UNICODE_LEAD` set to hold <kbd>Left Alt</kbd>
    and `OS_UNICODE_TRAIL` set to release <kbd>Left Alt</kbd>.

[^3]: Swedish character support was added by discord user "captainwoot". Danish
  character support was added by [@zonique2k](https://github.com/zonique2k). French
  character support was added by [@artggd](https://github.com/artggd).
