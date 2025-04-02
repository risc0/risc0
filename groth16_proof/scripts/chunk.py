#!/usr/bin/env python
import sys
import os

# Break a circom-emitted witness generator source file into chunks.
# Extract declarations into a header file, then split each function into
# its own file, which will include the header.

source_file = sys.argv[1]
dest_base, dest_ext = os.path.splitext(source_file)
decls = []
chunk = [f'#include "{os.path.basename(dest_base)}.hpp"\n']
chunk_index = 1
with open(source_file, 'r') as input:
    nesting = 0
    for line in input:
        nesting += line.count("{")
        if 0 == nesting:
            # top level
            if line.startswith("#include"):
                decls.append(line)
            elif line.startswith("void ") and line.endswith(";\n"):
                decls.append(line)
            elif line == "\n":
                # Split, begin new file
                dest_file = f"{dest_base}-{chunk_index}{dest_ext}"
                chunk_index += 1
                with open(dest_file, 'w') as output:
                    output.writelines(chunk)
                # Preserve starting include line
                del chunk[1:]
        elif 1 == nesting and line.startswith("Circom_TemplateFunction"):
            type, ident, init = line.split(' ', 2)
            decls.append(f"extern {type} {ident};\n")
            chunk.append(line)
        else:
            chunk.append(line)
        nesting -= line.count("}")

# Write final chunk if any lines remain.
if len(chunk) > 1:
    dest_file = f"{dest_base}-{chunk_index}{dest_ext}"
    with open(dest_file, 'w') as output:
        output.writelines(chunk)

# Add one inexplicably missing declaration
decls.append("void release_memory_component(Circom_CalcWit* ctx, uint pos);")
# Write the header file
with open(f"{dest_base}.hpp", "w") as output:
    output.writelines(decls)

