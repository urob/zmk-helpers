# Using keymap-drawer with zmk-helpers

[Keymap-drawer](https://github.com/caksoylar/keymap-drawer) is a popular tool that parses keymap
files and draws them in vector graphics (SVG). Since version `0.18.0`, Keymap-drawer supports using
`zmk-helpers` both as a Zephyr module and for traditional installations.

This document describes how to set up Keymap-drawer to use `zmk-helpers` as a Zephyr module. For
traditional installations of `zmk-helpers` inside `zmk-config/config/zmk-helpers`, there is no need
to do anything specials; Keymap-drawer will find the headers automatically.

## Running Keymap-drawer via Github Actions

1. Set up the Github Actions workflow following the
   [instructions](https://github.com/caksoylar/keymap-drawer?tab=readme-ov-file#setting-up-an-automated-drawing-workflow)
   on the Keymap-drawer repository

2. Add the following line to the `parse_config` section of your `keymap-drawer-config.yaml`:

   ```yaml
   parse_config:
     zmk_additional_includes: ["zmk-helpers/include"]
   ```

3. Add `west_config_path: "config"` to the workflow file:

   ```yaml
   jobs:
     draw:
       with:
         west_config_path: "config"
   ```

## Running Keymap-drawer locally

1. Make sure your have `keymap-drawer` version `0.18.0` or later installed

2. Make sure you have a local copy of `zmk-helpers` somewhere on your computer (or inside a Docker
   container)

3. Add the path to `zmk-helpers/include` to `zmk_additional_includes` in your
   `keymap-drawer-config.yaml`:

   ```yaml
   parse_config:
     zmk_additional_includes: ["/path/to/zmk-helpers/include"]
   ```

   Both absolute and relative path arguments are allowed. Relative paths must be specified relative
   to the _working directory from which Keymap-drawer is run_.

   For instance, if `zmk-helpers` is installed in the root of `zmk-config` (the default if
   automating the installation using `west`), and if you are running `keymap-drawer` from the root,
   then you would set the path to `zmk-helpers/include`.
