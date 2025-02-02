# Using keymap-drawer with zmk-helpers

[`keymap-drawer`](https://github.com/caksoylar/keymap-drawer) is a popular tool that parses keymap
files and draws them in vector graphics (SVG). Since version `0.18.0`, keymap-drawer supports using
`zmk-helpers` both as a Zephyr module and for traditional installations.

This document describes how to set up keymap-drawer to use `zmk-helpers` as a Zephyr module. For
traditional installations of `zmk-helpers` inside `zmk-config/config/zmk-helpers`, there is no need
to do anything specials; keymap-drawer will find the headers automatically.

## Running keymap-drawer via Github Actions

1. Set up the Github Actions workflow following the
   [instructions](https://github.com/caksoylar/keymap-drawer#setting-up-an-automated-drawing-workflow)
   on the keymap-drawer repository

2. Add the following line to the `parse_config` section of your
   [config file](https://github.com/caksoylar/keymap-drawer#customization):

   ```yaml
   parse_config:
     zmk_additional_includes: ["zmk-helpers/include"]
   ```

   By default the config file will be expected to be at `keymap-drawer.config.yaml` at the repo root.

## Running keymap-drawer locally

1. Make sure your have `keymap-drawer` version `0.18.0` or later
   [installed](https://github.com/caksoylar/keymap-drawer#command-line-tool-installation)

2. Make sure you have a local copy of `zmk-helpers` somewhere on your computer (or inside a Docker
   container)

3. Add the path to `zmk-helpers/include` to `zmk_additional_includes` in your
   keymap-drawer config file that you use with `keymap -c config.yaml parse ...`:

   ```yaml
   parse_config:
     zmk_additional_includes: ["/path/to/zmk-helpers/include"]
   ```

   Both absolute and relative path arguments are allowed. Relative paths must be specified relative
   to the _working directory from which keymap-drawer is run_.

   For instance, if `zmk-helpers` is installed in the root of `zmk-config` (the default if
   automating the installation using `west`), and if you are running `keymap-drawer` from the root,
   then you would set the path to `zmk-helpers/include`.
