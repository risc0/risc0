// This code is automatically generated

#include "ffi.h"
#include "fp.h"

#include <stdexcept>
#include <vector>

// clang-format off
namespace risc0::circuit::rv32im {

Fp step_accum(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::vector<Fp> host_args;
  std::vector<Fp> host_outs;
  Fp x0(2);
  Fp x1(11);
  Fp x2(2013265910);
  Fp x3(1);
  Fp x4 = args[0][0 * steps + ((cycle - 0) & mask)];
  Fp x5 = args[0][3 * steps + ((cycle - 0) & mask)];
  Fp x6 = args[0][4 * steps + ((cycle - 0) & mask)];
  Fp x7 = args[0][5 * steps + ((cycle - 0) & mask)];
  Fp x8 = args[0][6 * steps + ((cycle - 0) & mask)];
  Fp x9 = args[0][1 * steps + ((cycle - 0) & mask)];
  Fp x10 = args[0][2 * steps + ((cycle - 0) & mask)];
  Fp x11 = x9 + x10;
  Fp x12 = x11 + x5;
  Fp x13 = x12 + x6;
  Fp x14 = x13 + x7;
  Fp x15 = x14 + x8;
  if (x15 != 0) {
    Fp x16 = args[2][148 * steps + ((cycle - 0) & mask)];
    Fp x17 = args[2][128 * steps + ((cycle - 0) & mask)];
    Fp x18 = args[2][144 * steps + ((cycle - 0) & mask)];
    Fp x19 = args[2][129 * steps + ((cycle - 0) & mask)];
    Fp x20 = args[2][145 * steps + ((cycle - 0) & mask)];
    Fp x21 = args[2][130 * steps + ((cycle - 0) & mask)];
    Fp x22 = args[2][146 * steps + ((cycle - 0) & mask)];
    Fp x23 = args[2][131 * steps + ((cycle - 0) & mask)];
    Fp x24 = args[2][147 * steps + ((cycle - 0) & mask)];
    Fp x25 = args[3][0];
    Fp x26 = x4 * x25;
    Fp x27 = x26 + x3;
    Fp x28 = x17 * x25;
    Fp x29 = x27 + x28;
    Fp x30 = x26 + x28;
    Fp x31 = x19 * x25;
    Fp x32 = x29 + x31;
    Fp x33 = x30 + x31;
    Fp x34 = x21 * x25;
    Fp x35 = x32 + x34;
    Fp x36 = x33 + x34;
    Fp x37 = x23 * x25;
    Fp x38 = x35 + x37;
    Fp x39 = x36 + x37;
    Fp x40 = x16 * x25;
    Fp x41 = x40 + x3;
    Fp x42 = x18 * x25;
    Fp x43 = x41 + x42;
    Fp x44 = x40 + x42;
    Fp x45 = x20 * x25;
    Fp x46 = x43 + x45;
    Fp x47 = x44 + x45;
    Fp x48 = x22 * x25;
    Fp x49 = x46 + x48;
    Fp x50 = x47 + x48;
    Fp x51 = x24 * x25;
    Fp x52 = x49 + x51;
    Fp x53 = x50 + x51;
    Fp x54 = x3 - x5;
    Fp x55 = args[4][0 * steps + ((cycle - 1) & mask)];
    Fp x56 = x54 * x55;
    Fp x57 = x5 + x56;
    Fp x58 = args[4][1 * steps + ((cycle - 1) & mask)];
    Fp x59 = x54 * x58;
    Fp x60 = x5 + x59;
    Fp x61 = args[4][2 * steps + ((cycle - 1) & mask)];
    Fp x62 = x54 * x61;
    Fp x63 = x5 + x62;
    Fp x64 = args[4][3 * steps + ((cycle - 1) & mask)];
    Fp x65 = x54 * x64;
    Fp x66 = x5 + x65;
    Fp x67 = args[4][4 * steps + ((cycle - 1) & mask)];
    Fp x68 = x54 * x67;
    Fp x69 = x5 + x68;
    Fp x70 = args[4][5 * steps + ((cycle - 1) & mask)];
    Fp x71 = x54 * x70;
    Fp x72 = x5 + x71;
    Fp x73 = args[4][6 * steps + ((cycle - 1) & mask)];
    Fp x74 = x54 * x73;
    Fp x75 = x5 + x74;
    Fp x76 = args[4][7 * steps + ((cycle - 1) & mask)];
    Fp x77 = x54 * x76;
    Fp x78 = x5 + x77;
    Fp x79 = x57 * x38;
    Fp x80 = x60 * x39;
    Fp x81 = x63 * x39;
    Fp x82 = x80 + x81;
    Fp x83 = x66 * x39;
    Fp x84 = x82 + x83;
    Fp x85 = x84 * x2;
    Fp x86 = x79 + x85;
    args[4][0 * steps + cycle] = x86;
    Fp x87 = x57 * x39;
    Fp x88 = x60 * x38;
    Fp x89 = x87 + x88;
    Fp x90 = x81 + x83;
    Fp x91 = x90 * x2;
    Fp x92 = x89 + x91;
    args[4][1 * steps + cycle] = x92;
    Fp x93 = x87 + x80;
    Fp x94 = x63 * x38;
    Fp x95 = x93 + x94;
    Fp x96 = x83 * x2;
    Fp x97 = x95 + x96;
    args[4][2 * steps + cycle] = x97;
    Fp x98 = x93 + x81;
    Fp x99 = x66 * x38;
    Fp x100 = x98 + x99;
    args[4][3 * steps + cycle] = x100;
    Fp x101 = x69 * x52;
    Fp x102 = x72 * x53;
    Fp x103 = x75 * x53;
    Fp x104 = x102 + x103;
    Fp x105 = x78 * x53;
    Fp x106 = x104 + x105;
    Fp x107 = x106 * x2;
    Fp x108 = x101 + x107;
    args[4][4 * steps + cycle] = x108;
    Fp x109 = x69 * x53;
    Fp x110 = x72 * x52;
    Fp x111 = x109 + x110;
    Fp x112 = x103 + x105;
    Fp x113 = x112 * x2;
    Fp x114 = x111 + x113;
    args[4][5 * steps + cycle] = x114;
    Fp x115 = x109 + x102;
    Fp x116 = x75 * x52;
    Fp x117 = x115 + x116;
    Fp x118 = x105 * x2;
    Fp x119 = x117 + x118;
    args[4][6 * steps + cycle] = x119;
    Fp x120 = x115 + x103;
    Fp x121 = x78 * x52;
    Fp x122 = x120 + x121;
    args[4][7 * steps + cycle] = x122;
    Fp x123 = args[4][0 * steps + ((cycle - 0) & mask)];
    Fp x124 = args[4][1 * steps + ((cycle - 0) & mask)];
    Fp x125 = args[4][2 * steps + ((cycle - 0) & mask)];
    Fp x126 = args[4][3 * steps + ((cycle - 0) & mask)];
    Fp x127 = x123 * x123;
    Fp x128 = x124 * x0;
    Fp x129 = x128 * x126;
    Fp x130 = x125 * x125;
    Fp x131 = x129 - x130;
    Fp x132 = x131 * x1;
    Fp x133 = x127 + x132;
    Fp x134 = x123 * x0;
    Fp x135 = x134 * x125;
    Fp x136 = x124 * x124;
    Fp x137 = x135 - x136;
    Fp x138 = x126 * x126;
    Fp x139 = x138 * x1;
    Fp x140 = x137 + x139;
    Fp x141 = x133 * x133;
    Fp x142 = x140 * x1;
    Fp x143 = x142 * x140;
    Fp x144 = x141 + x143;
    args[4][8 * steps + cycle] = x144;
    if (x8 != 0) {
      {
        Fp x145 = args[4][8 * steps + ((cycle - 0) & mask)];
        Fp x146 = inv(x145);
        args[4][9 * steps + cycle] = x146;
      }
      Fp x147 = args[4][4 * steps + ((cycle - 0) & mask)];
      Fp x148 = x123 - x147;
      if (x148 != 0) throw std::runtime_error("eqz failed at: external/risc0/risc0/zkvm/circuit/accum_regs.cpp:91");
      Fp x149 = args[4][5 * steps + ((cycle - 0) & mask)];
      Fp x150 = x124 - x149;
      if (x150 != 0) throw std::runtime_error("eqz failed at: external/risc0/risc0/zkvm/circuit/accum_regs.cpp:91");
      Fp x151 = args[4][6 * steps + ((cycle - 0) & mask)];
      Fp x152 = x125 - x151;
      if (x152 != 0) throw std::runtime_error("eqz failed at: external/risc0/risc0/zkvm/circuit/accum_regs.cpp:91");
      Fp x153 = args[4][7 * steps + ((cycle - 0) & mask)];
      Fp x154 = x126 - x153;
      if (x154 != 0) throw std::runtime_error("eqz failed at: external/risc0/risc0/zkvm/circuit/accum_regs.cpp:91");
      Fp x155 = args[4][9 * steps + ((cycle - 0) & mask)];
      Fp x156 = args[4][8 * steps + ((cycle - 0) & mask)];
      Fp x157 = x155 * x156;
      Fp x158 = x157 - x3;
      if (x158 != 0) throw std::runtime_error("eqz failed at: external/risc0/risc0/zkvm/circuit/accum_regs.cpp:93");
    }
  }
  return x3;
}

} // namespace risc0::circuit::rv32im
// clang-format on
