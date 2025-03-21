#!/usr/bin/env python
import sys
import os

# Given a file containing one circom-generated verify_run function, split
# the body of the function into chunks, write these chunks into separate
# files, and rewrite the function to call them.

# We will read from one .cpp file and emit:
# - header file containing all of the function's locals, converted to globals
# - header file declaring all of the chunk functions
# - main file to replace the original, including both headers
# - one source file for each chunk, including the globals header

source_file = sys.argv[1]
dest_base, dest_ext = os.path.splitext(source_file)
dest_dir = os.path.dirname(dest_base)
global_decls = []
global_defs = []
main = []
chunkdecls = []
cur_chunk = []
func_name = ""
with open(source_file, "r") as input:
    nesting = 0
    for line in input:
        nesting += line.count("{")
        if 0 == nesting:
            # anything outside the function goes in the shared header
            global_decls.append(line)
        elif 1 == nesting:
            if line.startswith("void "):
                # top-level function declaration
                main.append(line)
                func_name = line.split(' ',1)[1].split('(',1)[0]
            elif line.startswith("}"):
                main.append(line)
            else:
                # variable declaration & optional initialization
                stmt = line.rstrip('\n;')
                type, decl = stmt.split(' ',1)
                ident = decl.split(' ',1)[0]
                global_decls.append(f"extern {type} {ident};\n")
                if "=" in decl:
                    main.append(f"{decl};\n")
                global_defs.append(f"{type} {ident};\n")
        else:
            cur_chunk.append(line)
            # If this line ended a block, and the chunk is big enough,
            # write it out and start the next chunk.
            if 2 == nesting and line.startswith("}") and len(cur_chunk) >= 8192:
                chunkname = f"{func_name}_{len(chunkdecls)}"
                param_decls = "(uint ctx_index,Circom_CalcWit* ctx)"
                chunkdecls.append(f"void {chunkname}{param_decls};\n")
                main.append(f"{chunkname}(ctx_index,ctx);\n")
                chunk_path = os.path.join(dest_dir, chunkname + ".cpp")
                with open(chunk_path, "w") as output:
                    output.write(f'#include "{func_name}.h"\n')
                    output.write(f'void {chunkname}{param_decls}{{\n')
                    output.writelines(cur_chunk)
                    output.write("}\n")
                cur_chunk = []
        nesting -= line.count("}")

globals_path = os.path.join(dest_dir, func_name + ".h")
with open(globals_path, "w") as output:
    output.writelines(global_decls)

main_path = os.path.join(dest_dir, func_name + ".cpp")
with open(main_path, "w") as output:
    output.write(f'#include "{func_name}.h"\n')
    output.writelines(global_defs)
    output.writelines(chunkdecls)
    output.writelines(main)
