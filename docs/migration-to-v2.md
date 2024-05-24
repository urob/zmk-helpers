1. Remove the v1 `zmk-nodefree-config` folder from your `zmk-config`
2. Add the new Zephyr Module (recommended) or manually copy `include/zmk-helpers` into
   `zmk-config/config/` (see [installation instructions](../README.md#installation))
3. Fix `#include paths`:

   1. replace the root-path `../zmk-nodefree-config/` with `zmk-helpers/`
   2. replace the sub-path `keypos_def/` with `key-labels/`
   3. replace the sub-path `international_chars/` with `unicode-chars/`
   4. rename key-position headers as [needed](../README.md#key-labels-collection) (e.g.,
      `keypos_34keys.h` becomes `34.h`)

   For example:

   ```c
   // old:
   #include "../zmk-nodefree-config/helper.h"
   #include "../zmk-nodefree-config/keypos_def/keypos_34keys.h"
   #include "../zmk-nodefree-config/international_chars/german.dtsi"

   // new:
   #include "zmk-helpers/helper.h"
   #include "zmk-helpers/key-labels/34.h"
   #include "zmk-helpers/unicode-chars/german.dtsi"
   ```

4. Change prefix of Danish unicode characters from `dk_` to the ISO language code `da_`
5. (optional) replace `ZMK_BEHAVIOR` with explicit behavior helpers
