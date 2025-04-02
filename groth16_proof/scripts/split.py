#!/usr/bin/env python
import sys
import os

# Split the top-level Verify_XXX_run function in a circom-produced
# witness generator source file into manageable chunks which won't
# choke the aarch64 code generator.
source_file = sys.argv[1]
dest_file = sys.argv[2]

# Scan the file, looking for the 'run' function, which will create and
# then run the top-level template: grab its name.
top_func_name = ""
with open(source_file, 'r') as input:
    look_for_top_func = False
    nesting = 0
    for line in input:
        if 0 == nesting:
            look_for_top_func = line.startswith("void run(Circom_CalcWit*")
        elif 1 == nesting and look_for_top_func:
            if line.startswith("Verify_") and "_run" in line:
                top_func_name, _ = line.split('(', 1)
        nesting += line.count("{")
        nesting -= line.count("}")

shared_params = "(uint ctx_index,Circom_CalcWit* ctx)"
top_level_decl = f"void {top_func_name}{shared_params}{{\n"

# Scan the file again, looking for the top-level run function.
# Pass all preceding lines through unchanged. 
CHUNK_LINES = 1<<18
line_count = 1
with open(source_file, 'r') as input, open(dest_file, 'w') as output:
    nesting = 0
    inside = False
    # Accumulate field and chunk definitions
    struct_def = [f"struct {top_func_name}_state {{\n"]
    # Replacement of the run function
    run_func = [top_level_decl, f"{top_func_name}_state state;\n"]
    # Array of step functions, each one an array of lines
    cur_step = [f"void {top_func_name}_state::step_0{shared_params}{{\n"]
    steps = []
    for line in input:
        if inside:
            if 0 == nesting:
                inside = False
                run_func.append(f"state.step_{len(steps)}(ctx_index,ctx);\n")
                struct_def.append(f"void step_{len(steps)}{shared_params};\n")
                steps.append(cur_step)
                output.writelines(struct_def)
                output.write("};\n\n")
                del struct_def[:]
                for step in steps:
                    output.writelines(step)
                    output.write("}\n\n")
                del steps[:]
                output.writelines(run_func)
                output.write("}\n\n")
                del run_func[:]
            elif 1 == nesting and line.endswith(";\n"):
                if "=" in line:
                    decl, init = line.split("=",2)
                    struct_def.append(decl.rstrip() + ";\n")
                    name = decl.split(" ",2)[1]
                    run_func.append(f"state.{name} ={init}")
                else:
                    struct_def.append(line)
            elif 1 == nesting and len(cur_step) >= CHUNK_LINES:
                run_func.append(f"state.step_{len(steps)}(ctx_index,ctx);\n")
                struct_def.append(f"void step_{len(steps)}{shared_params};\n")
                steps.append(cur_step)                
                cur_step = [f"void {top_func_name}_state::step_{len(steps)}{shared_params}{{\n"]
                cur_step.append(line)
            elif 1 != nesting or line != "}\n":
                cur_step.append(line)
        elif 0 == nesting and line == top_level_decl:
                inside = True
        else:
            output.write(line)
        line_count += 1
        nesting += line.count("{")
        nesting -= line.count("}")

