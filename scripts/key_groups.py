#!/usr/bin/env python3

import argparse
from pathlib import Path

MACROS = """\
#define NUMROW {numrow}
#define KEYS_L {keys_l}
#define KEYS_R {keys_r}
#define THUMBS_L {thumbs_l}
#define THUMBS_R {thumbs_r}
#define THUMBS THUMBS_L THUMBS_R
"""

parser = argparse.ArgumentParser(description="Add key groups to header file")
parser.add_argument("filename")

args = parser.parse_args()
file = Path(args.filename)


def is_keylabel(label):
    return label.startswith(("L", "R")) and len(label) <= 4


def parse_label(label):
    if label.startswith(("LN", "RN")):
        groups["numrow"].append(label)
    if label.startswith(("LT", "LM", "LB")):
        groups["keys_l"].append(label)
    if label.startswith(("RT", "RM", "RB")):
        groups["keys_r"].append(label)
    if label.startswith("LH"):
        groups["thumbs_l"].append(label)
    if label.startswith("RH"):
        groups["thumbs_r"].append(label)


groups = {
    "keys_l": [],
    "keys_r": [],
    "thumbs_l": [],
    "thumbs_r": [],
    "numrow": [],
}

with open(file, "r") as f:
    for line in f:
        if line.startswith("#define"):
            label = line.split()[1]
            if is_keylabel(label):
                parse_label(label)

        # Check if file ends in blank line.
        ends_in_blank = line == "\n"


groups_as_string = {k: " ".join(v) for k, v in groups.items()}
group_macros = MACROS.format(**groups_as_string)

with open(file, "a") as f:
    if not ends_in_blank:
        f.write("\n")
    f.write(group_macros)
