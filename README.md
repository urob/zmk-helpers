# ZMK-Helpers (Version 2)

This is a collection of helper macros (formerly `zmk-nodefree-config`), simplifying the
configuration of ZMK keymaps. The [migration guide](docs/migration-to-v2.md) has instructions on how
to migrate from v1. Version 1 continuous to be available
[here](https://github.com/urob/zmk-helpers/tree/v1).

## Installation

To use the helpers, it is recommended to add them as a module to your `config/west.yml` by adding a
new entry to `remotes` and `projects`:

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: urob
      url-base: https://github.com/urob
  projects:
    - name: zmk
      remote: zmkfirmware
      revision: main
      import: app/west.yml
    - name: zmk-helpers
      remote: urob
      revision: main
  self:
    path: config
```

If you are building locally, see the instructions for
[building with external modules](https://zmk.dev/docs/development/build-flash#building-with-external-modules)
in ZMK docs.

<details><summary>Manual installation</summary>

Alternatively, copy `include/zmk-helpers` into your `config/` directory:

```
zmk-config
├── config
│   ├── corne.keymap
│   ├── zmk-helpers
│   │   ├── helper.h
│   │   └── ...
│   └── ...
└── ...
```

Instead of copying, one could also add a `git-submodule`[^1]:

```sh
cd /path/to/zmk-config/
git submodule add -b v2 -- https://github.com/urob/zmk-helpers config/zmk-helpers-repo
ln -s zmk-helpers-repo/include/zmk-helpers config/zmk-helpers
```

</details>

## Usage

Source `helper.h` near the top of your `.keymap` file. Optionally, source `key-labels` and
`unicode-chars` as needed:

```C++
#include "zmk-helpers/helper.h"

// Source desired key-position labels
#include "zmk-helpers/key-labels/glove80.h"

// Source unicode-chars for desired languages
#include "zmk-helpers/unicode-chars/german.dtsi"
```

The following subsections describe the available helpers. See the
[example configuration](example/zmk-config/config/cradio.keymap) or my
[personal zmk-config](https://github.com/urob/zmk-config/blob/main/config/base.keymap) for a
demonstration.

### Core helpers

The `helper.h` header provides a number of convenience macros for defining behaviors, combos,
layers, etc.

| Macro                          | Purpose                                            |
| ------------------------------ | -------------------------------------------------- |
| [`ZMK_BEHAVIOR`]               | Create a new behavior instance (generic form)      |
| [`ZMK_APPLY_MATRIX_TRANSFORM`] | Apply a `matrix_transform`                         |
| [`ZMK_COMBO`]                  | Create a combo                                     |
| [`ZMK_CONDITIONAl_LAYER`]      | Create a `tri-layer` condition                     |
| [`ZMK_LAYER`]                  | Create a layer and add it to the keymap            |
| [`ZMK_UNICODE_SINGLE`]         | Create a unicode-char                              |
| [`ZMK_UNICODE_PAIR`]           | Create a pair of lowercase/uppercase unicode-chars |

In addition to the generic `ZMK_BEHAVIOR` macro, version 2 also provides the following explicit
variants.

| Macro                   | Purpose                                                       |
| ----------------------- | ------------------------------------------------------------- |
| [`ZMK_CAPS_WORD`]       | Create a new `caps-word` behavior instance                    |
| [`ZMK_HOLD_TAP`]        | Create a new `hold-tap` behavior instance                     |
| [`ZMK_KEY_REPEAT`]      | Create a new `key-repeat` behavior instance                   |
| [`ZMK_MACRO`]           | Create a new `key-macro` behavior instance                    |
| [`ZMK_MACRO_ONE_PARAM`] | Create a new `macro-one-param` behavior instance              |
| [`ZMK_MACRO_TWO_PARAM`] | Create a new `macro-two-param` behavior instance              |
| [`ZMK_MOD_MORPH`]       | Create a new `mod-morph` behavior instance                    |
| [`ZMK_STICKY_KEY`]      | Create a new `sticky-key` behavior instance                   |
| [`ZMK_TAP_DANCE`]       | Create a new `tap-dance` behavior instance                    |
| [`ZMK_TRI_STATE`]       | Create a new `tri-state` behavior instance (requires [#1366]) |

The explicit behavior helpers are inspired by the native ZMK implementation of `ZMK_MACRO`. They
differ in that they automatically create all Devicetree nodes as needed. So instead of calling them
from inside the Devicetree, they should be placed outside the root node.

> [!NOTE]
>
> By default, sourcing `helper.h` will replace the native implementation of `ZMK_MACRO`. To work
> reliably, `helper.h` should be included _after_ `behaviors.dtsi`. To keep the native
> implementation of `ZMK_MACRO`, set `#define ZMK_HELPER_KEEP_NATIVE 1` before including `helper.h`.

### Key-labels collection

These layout headers define _easy to remember_ "key-labels" for many popular keyboards, which can be
used instead of numeric key-positions to configure position-based properties (e.g., in combos).

Key-labels are _standardized_ to make keymaps portable across keyboards. For instance, the labels
for the 60-key _Sofle_ nest the labels for the 34-key _Sweep_ as follows:

![plot](docs/img/key_labels_example.png)

The following layouts are currently implemented.

| Header                  | \# of Keys       | Examples                                   |
| ----------------------- | ---------------- | ------------------------------------------ |
| `34.h`                  | 34               | Ferris, Hypergolic, Sweep                  |
| `36.h`                  | 36               | Corne (5 cols), Corne-ish Zen (5 cols)     |
| `42.h`                  | 42               | Corne, Corne-ish Zen                       |
| `4x12.h`, `4x12_wide.h` | 48               | Planck                                     |
| `adv360_custom.h`       | 76               | Advantage360 Pro (custom matrix transform) |
| `glove80.h`             | 80               | Glove80                                    |
| `hillside_*.h`          | 46, 48, 52 or 56 | Hillside family                            |
| `jian.h`                | 44               | Jian, Jorne                                |
| `kyria.h`               | 50               | Kyria                                      |
| `lily58.h`              | 58               | Lily58                                     |
| `osprette.h`            | 34               | Osprette                                   |
| `sofle.h`               | 60               | Sofle                                      |
| `totem.h`               | 38               | Totem                                      |

### Unicode-characters and language collection

This collection defines unicode behaviors for all relevant characters in a given language. For
instance, sourcing the German language file, one can add `&de_ae` to the keymap, which will send
<kbd>ä</kbd>/<kbd>Ä</kbd> when pressed or shifted.

See the [unicode-chars directory](include/zmk-helpers/unicode-chars/) for a list of all currently
available languages. To use these language files, follow the instructions for your OS below.

<details><summary>Windows</summary>

On your computer, install [WinCompose](https://github.com/samhocevar/wincompose). In your keymap,
source `helper.h` and the desired language files. For example:

```c
#include "zmk-helpers/helper.h"
#include "zmk-helpers/unicode-chars/german.dtsi"
```

</details>

<details><summary>Linux</summary>

In your keymap, set `HOST_OS` to `1`, **_then_** source `helper.h` and the desired language files.
For example:

```c
#define HOST_OS 1
#include "zmk-helpers/helper.h"
#include "zmk-helpers/unicode-chars/german.dtsi"
```

</details>

<details><summary>macOS</summary>

On your computer, enable unicode input in the system preferences by selecting `Unicode Hex Input` as
input source. In your keymap, set `HOST_OS` to `2`, **_then_** source `helper.h` and the desired
language files. For example:

```c
#define HOST_OS 2
#include "zmk-helpers/helper.h"
#include "zmk-helpers/unicode-chars/german.dtsi"
```

</details>

> [!NOTE]
>
> Unicodes allow typing international characters without changing the OS keyboard layout. See
> [zmk-locale-generator](https://github.com/joelspadin/zmk-locale-generator) for a collection of
> headers that configure ZMK to work with non-US layouts set in the OS.

[^1]:
    To enable the submodule when building with Github Actions, replace
    `zmk-config/.github/workflows/build.yml` with

    ```
    on: [push, pull_request, workflow_dispatch]

    jobs:
      build:
        uses: urob/zmk/.github/workflows/build-user-config.yml@build-with-submodules
    ```

## Contributing

Contributions of any form are very welcome! New `key-labels` and `unicode-chars` should follow these
guidelines:

- Key-position labels should stick to the [label conventions](docs/key_labels.md#standardization)
  whenever applicable.
- Language headers should namespace all characters using
  [two-letter ISO language codes](https://en.wikipedia.org/wiki/List_of_ISO_639_language_codes).

[#1366]: https://github.com/zmkfirmware/zmk/pull/1366
[`ZMK_BEHAVIOR`]: docs/core_helpers.md#zmk_behavior
[`ZMK_APPLY_MATRIX_TRANSFORM`]: docs/core_helpers.md#apply_matrix_transform
[`ZMK_COMBO`]: docs/core_helpers.md#zmk_combo
[`ZMK_CONDITIONAL_LAYER`]: docs/core_helpers.md#zmk_conditional_layer
[`ZMK_LAYER`]: docs/core_helpers.md#zmk_layer
[`ZMK_UNICODE_SINGLE`]: docs/core_helpers.md#zmk_unicode
[`ZMK_UNICODE_PAIR`]: docs/core_helpers.md#zmk_unicode
[`ZMK_CAPS_WORD`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_HOLD_TAP`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_KEY_REPEAT`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_MACRO`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_MACRO_ONE_PARAM`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_MACRO_TWO_PARAM`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_MOD_MORPH`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_STICKY_KEY`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_TAP_DANCE`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
[`ZMK_TRI_STATE`]: docs/core_helpers.md#zmk_behavior-(explicit-variants)
