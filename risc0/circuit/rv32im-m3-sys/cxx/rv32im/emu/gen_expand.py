
import os

def safe_sys(cmd):
    if os.system(cmd) != 0:
        raise "BAD NEWS"

def expand_one(val):
    if (val % 4 == 3):
        return "c0001073"
    with open("/tmp/short.S", "w") as f:
        print(".section .text", file=f)
        print(f".2byte 0x{val:x}", file=f)
    safe_sys("riscv64-unknown-elf-as -march=rv32gc -o /tmp/short /tmp/short.S")
    safe_sys("riscv64-unknown-elf-strip /tmp/short")
    safe_sys("riscv64-unknown-elf-objdump -d /tmp/short > /tmp/short.dis")
    asm = "unimp"
    with open('/tmp/short.dis', 'r') as f:
        for line in f:
            if line.startswith('   0:') and ".2byte" not in line:
                parts = line.split()
                asm = ' '.join(parts[2:])
    na = "unimp"
    parts = asm.split()
    args = []
    #print(asm)
    if len(parts) > 1:
        args = asm.split()[1].split(',')
    # Expand special c.x instruction to use the same reg for rd + rs1
    if parts[0] in ["c.slli", "c.srli", "c.srai", "c.add"]:
        args = [args[0], args[0], args[1]];
        asm = parts[0].removeprefix("c.") + " " + ",".join(args)
    # Most c. instructions don't need to be changed
    asm = asm.removeprefix("c.")
    if "nop" in asm:  # Turn 'nop #' -> 'nop' 
        asm = "nop"
    # Remove explicitly 64 bit versions of shifts
    if "slli64" in asm or "srli64" in asm or "srai64" in asm:
        asm = "unimp"
    # Remove implicitly 64 bit versions of shifts
    if "sll" in asm or "srl" in asm or "sra" in asm:
        if "0x" in args[2] and int(args[2], 16) >= 32:
            asm = "unimp"
    with open("/tmp/long.S", "w") as f:
        print(".section .text", file=f)
        print(asm, file=f)
    safe_sys("riscv64-unknown-elf-as -march=rv32g -o /tmp/short /tmp/long.S")
    safe_sys("riscv64-unknown-elf-objdump -d /tmp/short > /tmp/long.dis")
    outVal = "00000000"
    with open('/tmp/long.dis', 'r') as f:
        for line in f:
            if line.startswith('   0:'):
                parts = line.split()
                outVal = parts[1]
    return outVal

print("  // Run 'python3 ./gen_expand.py > expand.inc' to generate")
for i in range(65536 // 8):
    line = "  ";
    for j in range(8):
        line += "0x" + expand_one(i * 8 + j) + ", "
    print(line)
