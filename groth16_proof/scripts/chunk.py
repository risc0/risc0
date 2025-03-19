#!/usr/bin/env python
import sys
import os

# Break a circom-emitted witness generator source file into chunks, splitting
# at each blank line which is not contained in a brace block, thereby putting
# each function into its own translation unit.
source_file = sys.argv[1]
dest_base, dest_ext = os.path.splitext(source_file)
with open(source_file, 'r') as input:
    nesting_count = 0
    chunk = []
    index = 1
    for line in input:
        if line == "\n" and nesting_count == 0:
            dest_file = dest_base + "-" + str(index) + dest_ext
            index += 1
            with open(dest_file, 'w') as output:
                output.writelines(chunk)
            chunk = []
            continue
        chunk.append(line)
        nesting_count += line.count("{")
        nesting_count -= line.count("}")

