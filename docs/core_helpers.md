## Table of Contents

- [`ZMK_BEHAVIOR`](#zmk_behavior)
- [`ZMK_BEHAVIOR` (explicit variants)](<#zmk_behavior-(explicit-variants)>)
- [`ZMK_APPLY_MATRIX_TRANSFORM`](#zmk_apply_matrix_transform)
- [`ZMK_COMBO`](#zmk_combo)
- [`ZMK_CONDITIONAL_LAYER`](#zmk_conditional_layer)
- [`ZMK_LAYER`](#zmk_layer)
- [`ZMK_UNICODE`](#zmk_unicode)

## ZMK_BEHAVIOR

### Synopsis

`ZMK_BEHAVIOR(name, type, specification)`

Create a behavior instance of type `type` and make it accessible under `&name`.

- `name`: a unique string to reference the behavior.
- `type`: any valid [ZMK behavior](https://zmk.dev/docs/config/behaviors); e.g., `hold_tap`.
  Multiword behaviors are separated by underscores (`_`).
- `specification`: the configuration of the behavior without the `#binding-cells` and `compatible`
  properties and without the surrounding node specification.

### Examples

<details><summary>Tap-hold</summary>

This creates a custom "homerow mod" that can be added to the keymap using `&hrm`. For example,
`&hrm LSHIFT T` creates a key that yields `T` on tap and `LSHIFT` on hold.

```C++
ZMK_BEHAVIOR(hrm, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <280>;
    quick-tap-ms = <125>;
    bindings = <&kp>, <&kp>;
)
```

</details>

<details><summary>Tap-dance</summary>

This creates a behavior that yields sticky-shift on tap and caps-word on double tap. It can be added
to the keymap using `&ss_cw`.

```C++
ZMK_BEHAVIOR(ss_cw, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&sk LSHFT>, <&caps_word>;
)
```

</details>

<details><summary>Macro</summary>

This creates a "Windows sleep macro" that can be added to the keymap using `&win_sleep`.

```C++
ZMK_BEHAVIOR(win_sleep, macro,
    wait-ms = <100>;
    tap-ms = <5>;
    bindings = <&kp LG(X) &kp U &kp S>;
)
```

</details>

## ZMK_BEHAVIOR (explicit variants)

Instead of using `ZMK_BEHAVIOR(name, type, specification)`, each behavior `type` also has an
explicit variant accessible under `ZMK_type(name, specification)`.

For instance, `ZMK_MOD_MORPH(name, ...)` is equivalent to `ZMK_BEHAVIOR(name, mod_morph, ...)`.

> [!NOTE]
>
> By default, sourcing `helper.h` will replace the native implementation of `ZMK_MACRO`. To work
> reliably, `helper.h` should be included _after_ `behaviors.dtsi`. To keep the native
> implementation of `ZMK_MACRO`, set `#define ZMK_HELPER_KEEP_NATIVE 1` before including `helper.h`.

## ZMK_APPLY_MATRIX_TRANSFORM

### Synopsis

`ZMK_APPLY_MATRIX_TRANSFORM(transform)`

Apply a non-default matrix transform to the keymap.

- `transform`: node name of a valid `matrix_transform` without the leading `&`

### Example

This applies the `five_column_transform` on a Corne that has the last columns snapped off.

```c
ZMK_APPLY_MATRIX_TRANSFORM(five_column_transform)
```

## ZMK_COMBO

### Synopsis

`ZMK_COMBO(name, bindings, keypos, layers, timeout, prior_idle, extra)`

Create a combo that triggers `binding` if all keys in position `keypos` are pressed.

- `name`: a unique identifier string
- `binding`: a behavior instance that is triggered by the combo
- `keypos`: a list of 2 or more key positions that activate the combo
- `layers` (optional): a list of layers on which the combo can be activated (defaults to `All`)
- `timeout` (optional): combo timeout in ms (defaults to `COMBO_TERM`, see below)
- `prior_idle` (optional): require-prior-idle timout in ms (disabled by default)
- `extra` (optional): additional configuration options (e.g., `slow-release;`)

If not specified, `timeout` defaults to the `COMBO_TERM`, which in turn default to `30`ms. The
default can be globally overwritten with:

```c
#undef COMBO_TERM
#define COMBO_TERM 50
```

### Examples

<details><summary>Simple combo</summary>

This creates an "escape" combo that is active on all layers and which is triggered when the 0th and
1st keys are pressed jointly within 25ms.

```C++
ZMK_COMBO(esc,  &kp ESC, 0 1, ALL, 25)
```

</details>

<details><summary>Using `key-labels` to define combos</summary>

This sources [key-labels](../readme.md#key-labels-collection) for a 34-keys board like the Sweep. It
then creates a "copy"-combo for the middle + ring finger on the left bottom row, and a "paste"-combo
for the index + middle finger on the left bottom row. Both combos are active on all layers.

```C++
#include "zmk-helpers/key-labels/34.h" // replace with layout file for your keyboard
ZMK_COMBO(copy,  &kp LC(C), LB2 LB3)
ZMK_COMBO(paste, &kp LC(V), LB1 LB2)
```

</details>

## ZMK_CONDITIONAL_LAYER

### Synopsis

`ZMK_CONDITIONAL_LAYER(if_layers, then_layers)`

Set up a `tri-layer` condition, which activates `then_layer` if all layers in `if_layers` are
active.

- `if_layers`: a list of layers which trigger the `then_layer` if simultaneously active
- `then_layer`: the layer which is activated when the if-condition is met. Due to ZMK's layering
  model, it should generally have a higher number than the `if_layers`

### Example

This triggers "layer 3" if layers "1" and "2" are simultaneously active.

```C++
ZMK_CONDITIONAL_LAYER(1 2, 3)
```

Mind that ZMK's layer numbering starts at 0. One can use layer definitions, as demonstrated in this
[../example/zmk-config/config/cradio.keymap](example), to simplify life.

## ZMK_LAYER

### Synopsis

`ZMK_LAYER(name, layout, sensors)`

Create a layer with layout `layout` and add it to the keymap.

- `name`: a unique identifier string (this also sets the `display-name` if available)
- `layout`: the layout as specified by the `bindings` property of the
  [ZMK keymap](https://zmk.dev/docs/config/keymap) node
- `sensors` (optional): sensor-specification if applicable

Multiple layers can be added with repeated calls of `ZMK_LAYER`. They will be ordered in the same
order in which they are created, with the first-specified layer being the "lowest" one
([see here for details](https://zmk.dev/docs/features/keymaps#layers)).

### Example

```C++
ZMK_LAYER(base,
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

## ZMK_UNICODE

### Synopsis

`ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3)`  
`ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3)`

Create Unicode characters that can be added to the keymap with `&name`. `ZMK_UNICODE_SINGLE` creates
a single character. `ZMK_UNICODE_PAIR` creates pairs of shifted/unshifted characters.

- `name:` a unique string to reference the character
- `L0` to `L3`: a 4-digit sequence defining the Unicode string using standard
  [ZMK key codes](https://zmk.dev/docs/codes/keyboard-keypad)
- `U0` to `U3` (only for `ZMK_UNICODE_PAIR`): a 4-digit sequence defining the shifted unicode string

### Prerequisites

The usage of the Unicode helpers is OS-specific. See the following instructions for details.

<details><summary>Windows</summary>

On your computer, install [WinCompose](https://github.com/samhocevar/wincompose).

</details>

<details><summary>Linux</summary>

In your keymap, set `HOST_OS` to `1` **_before_** sourcing `helper.h`:

```c
#define HOST_OS 1
#include "zmk-helpers/helper.h"
```

</details>

<details><summary>macOS</summary>

On your computer, enable Unicode input in the system preferences by selecting `Unicode Hex Input` as
input source. In your keymap, set `HOST_OS` to `2` **_before_** sourcing `helper.h`.

```c
#define HOST_OS 2
#include "zmk-helpers/helper.h"
```

</details>

<details><summary>Other OS</summary>

For non-default input channels or for other operating systems, one can set the variables
`OS_UNICODE_LEAD` and `OS_UNICODE_TRAIL` to the character sequences that initialize/terminate the
Unicode input.

</details>

### Examples

<details><summary>Euro sign (€)</summary>

This creates a Euro character that can be added to the keymap using `&euro_sign`.

```C++
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)
```

</details>

<details><summary>German umlauts (ä/Ä, ö/Ö, ü/Ü)</summary>

The creates "umlaut" pairs that can be added to the keymap using `&de_ae`, `&de_oe` and `&de_ue`.

```C++
//                name     unshifted         shifted
ZMK_UNICODE_PAIR( de_ae,   N0, N0,  E, N4,   N0, N0,  C, N4 )
ZMK_UNICODE_PAIR( de_oe,   N0, N0,  F, N6,   N0, N0,  D, N6 )
ZMK_UNICODE_PAIR( de_ue,   N0, N0,  F,  C,   N0, N0,  D,  C )
```

</details>
