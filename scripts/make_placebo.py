#!/usr/bin/env python3

from pathlib import Path

root = Path(__file__).resolve().parents[1]
key_labels_dir = root / 'include/zmk-helpers/key-labels'

outfile = key_labels_dir / 'placebo.h'
headers = [f for f in key_labels_dir.glob('*.h') if f.name != outfile.name]


# Run some basic sanity checks
def is_keylabel(label):
    return label.startswith(('L', 'R')) and len(label) <= 4


# Generate placebo snippet
def make_placebo_snippet(label):
    return f'#ifndef {label}\n#define {label}\n#endif\n'


# Get all key labels
all_key_labels = []
for header in headers:
    with open(header, 'r') as f:
        for line in f:
            if line.startswith('#define'):
                label = line.split()[1]
                if is_keylabel(label) and label not in all_key_labels:
                    all_key_labels.append(label)


# Write placebo header
with open(outfile, 'w') as f:
    for label in sorted(all_key_labels):
        f.write(make_placebo_snippet(label))
