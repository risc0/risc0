// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#define X -1
// Predefined values:
//   R1: The value read from rs1 by instruction decoder
//   R2: The value read from rs2 by instruction decoder
//   IM: The immediate value decoded from the instruction
// Macros
//   MM: Read from memory at location X1 // 4
//   MS: Read from memory at location X1 // 4, but then decode the low + high 16 bits
//       seperately from the results and rs2 based on bit 1 of X1
//   GET(sign_ext, bits): Get `bits` bits from X2, at position of lower bits of X1,
//                        Sign extend or zero extend based on flag
//   SET(bits): Set `bits` bits of X3 to match the low bits of R2 based on the index
//              given by the low order bits of X1
//   LT: 1 if X1 - X2 == X3 < 0, 0 otherwise (signed)
//   LTU: 1 if X1 - X2 == X3 < 0, 0 otherwise (unsigned)
//   EQ: 1 if X3 == 0, 0 otherwise
//   BR_TRUE: If result == 1, PC + IM, else PC + 4
//   BR_FALSE: If result == 0, PC + IM, else PC + 4
// OPC(  // Define a bit op
//   id,        // unique numeric value
//   mnemonic,  // The assembly mnemonic from the spec
//   opcode,    // The top 5 bits of the opcode (lowest 2 bits are always 11)
//   func3,     // The value of func3 required, X == don't care
//   func7,     // The value of func7 requirex, X = don't case,
//   immFmt,    // The format for the immediate value
//   x1,        // What to set register X1 to.
//   doLoad,    // Should we load from address in X1?
//   x2,        // What to set register X2 to.
//   x3,        // What to set register X3 to.
//   result,    // What to make the 'result' equal to.
//   setReg,    // 1 if we should set rd to the result
//   doStore,   // 1 if we should write the result to memory at X1 // 4
//   pc)        // New value of PC

// clang-format off
OPC(  0, ADD,   0b01100, 0,  0, R, R1,    0, R2, X1 + X2,    X3,  1, 0, PC + 4)
OPC(  1, SUB,   0b01100, 0, 32, R, R1,    0, R2, X1 - X2,    X3,  1, 0, PC + 4)
OPC(  2, XOR,   0b01100, 4,  0, R, R1,    0, R2, X1 ^ X2,    X3,  1, 0, PC + 4)
OPC(  3, OR,    0b01100, 6,  0, R, R1,    0, R2, X1 | X2,    X3,  1, 0, PC + 4)
OPC(  4, AND,   0b01100, 7,  0, R, R1,    0, R2, X1 & X2,    X3,  1, 0, PC + 4)
OPC(  5, SLT,   0b01100, 2,  0, R, R1,    0, R2, X1 - X2,    LT,  1, 0, PC + 4)
OPC(  6, SLTU,  0b01100, 3,  0, R, R1,    0, R2, X1 - X2,    LTU, 1, 0, PC + 4)
OPC(  7, ADDI,  0b00100, 0,  X, I, R1,    0, IM, X1 + X2,    X3,  1, 0, PC + 4)
OPC(  8, XORI,  0b00100, 4,  X, I, R1,    0, IM, X1 ^ X2,    X3,  1, 0, PC + 4)
OPC(  9, ORI,   0b00100, 6,  X, I, R1,    0, IM, X1 | X2,    X3,  1, 0, PC + 4)
OPC( 10, ANDI,  0b00100, 7,  X, I, R1,    0, IM, X1 & X2,    X3,  1, 0, PC + 4)
OPC( 11, SLTI,  0b00100, 2,  X, I, R1,    0, IM, X1 - X2,    LT,  1, 0, PC + 4)
OPC( 13, SLTIU, 0b00100, 3,  X, I, R1,    0, IM, X1 - X2,    LTU, 1, 0, PC + 4)
OPC( 14, LB,    0b00000, 0,  X, I, R1+IM, 1, MM, GET(1, 8),  X3,  1, 0, PC + 4)
OPC( 15, LH,    0b00000, 1,  X, I, R1+IM, 1, MM, GET(1, 16), X3,  1, 0, PC + 4)
OPC( 16, LW,    0b00000, 2,  X, I, R1+IM, 1, MM, GET(0, 32), X3,  1, 0, PC + 4)
OPC( 17, LBU,   0b00000, 4,  X, I, R1+IM, 1, MM, GET(0, 8),  X3,  1, 0, PC + 4)
OPC( 18, LHU,   0b00000, 5,  X, I, R1+IM, 1, MM, GET(0, 16), X3,  1, 0, PC + 4)
OPC( 19, SB,    0b01000, 0,  X, S, R1+IM, 1, MS, PUT(8),     X3,  0, 1, PC + 4)
OPC( 20, SH,    0b01000, 1,  X, S, R1+IM, 1, MS, PUT(16),    X3,  0, 1, PC + 4)
OPC( 21, SW,    0b01000, 2,  X, S, R1+IM, 0, R2, PUT(32),    X3,  0, 1, PC + 4)
OPC( 22, BEQ,   0b11000, 0,  X, B, R1,    0, R2, X1 - X2,    EQ,  0, 0, BR_TRUE)
OPC( 23, BNE,   0b11000, 1,  X, B, R1,    0, R2, X1 - X2,    EQ,  0, 0, BR_FALSE)
OPC( 24, BLT,   0b11000, 4,  X, B, R1,    0, R2, X1 - X2,    LT,  0, 0, BR_TRUE)
OPC( 25, BGE,   0b11000, 5,  X, B, R1,    0, R2, X1 - X2,    LT,  0, 0, BR_FALSE)
OPC( 26, BLTU,  0b11000, 6,  X, B, R1,    0, R2, X1 - X2,    LTU, 0, 0, BR_TRUE)
OPC( 27, BGEU,  0b11000, 7,  X, B, R1,    0, R2, X1 - X2,    LTU, 0, 0, BR_FALSE)
OPC( 28, JAL,   0b11011, X,  X, J, R1,    0, R2, PC + 4,     X3,  1, 0, PC + IM)
OPC( 29, JALR,  0b11001, 0,  X, I, R1,    0, R2, PC + 4,     X3,  1, 0, R1 + IM)
OPC( 30, LUI,   0b01101, X,  X, U, R1,    0, R2, IM,         X3,  1, 0, PC + 4)
OPC( 31, AUIPC, 0b00101, X,  X, U, R1,    0, R2, PC + IM,    X3,  1, 0, PC + 4)
// clang-format on

// OPM(  // Define a multiply op
//   id,        // unique numeric value
//   mnemonic,  // The assembly mnemonic from the spec
//   opcode,    // The top 5 bits of the opcode (lowest 2 bits are always 11)
//   func3,     // The value of func3 required, X == don't care
//   func7,     // The value of func7 requirex, X = don't case,
//   immFmt,    // The format for the immediate value
//   i0,        // What to set register i0 to.
//   i1,        // What to set register i1 to.
//   i0Signed,  // Is i0 signed
//   i1Signed,  // Is i1 signed
//   high)      // Set result to high part (otherwise low)
//   We start at a multiple of 8 to allow skipping the check on upper ID
// clang-format off
OPM( 32, MUL,   0b01100, 0,  1, R, R1, R2, 0, 0, 0)
OPM( 33, MULH,  0b01100, 1,  1, R, R1, R2, 1, 1, 1)
OPM( 34, MULSU, 0b01100, 2,  1, R, R1, R2, 1, 0, 1)
OPM( 35, MULU,  0b01100, 3,  1, R, R1, R2, 0, 0, 1)
OPM( 36, SLL,   0b01100, 1,  0, R, R1, V2, 0, 0, 0)
OPM( 37, SLLI,  0b00100, 1,  0, I, R1, V2, 0, 0, 0)
// clang-format on

// OPD(  // Define a divide op
//   id,        // unique numeric value
//   mnemonic,  // The assembly mnemonic from the spec
//   opcode,    // The top 5 bits of the opcode (lowest 2 bits are always 11)
//   func3,     // The value of func3 required, X == don't care
//   func7,     // The value of func7 requirex, X = don't case,
//   immFmt,    // The format for the immediate value
//   numer,     // What to set numerator to
//   denom,     // What to set denominator to
//   signType,  // Sign type: 0 = unsigned, 1 = signed, 2 = SRA
//   rem)       // Return the remainder (instead of the qoutient)
//   We start at a multiple of 8 to allow skipping the check on upper ID
// clang-format off
OPD( 42, DIV,   0b01100, 4,  1, R, R1, R2, 1, 0)
OPD( 43, DIVU,  0b01100, 5,  1, R, R1, R2, 0, 0)
OPD( 44, REM,   0b01100, 6,  1, R, R1, R2, 1, 1)
OPD( 45, REMU,  0b01100, 7,  1, R, R1, R2, 0, 1)
OPD( 46, SRL,   0b01100, 5,  0, R, R1, V2, 0, 0)
OPD( 47, SRA,   0b01100, 5, 32, R, R1, V2, 2, 0)
OPD( 48, SRLI,  0b00100, 5,  0, I, R1, V2, 0, 0)
OPD( 49, SRAI,  0b00100, 5, 32, I, R1, V2, 2, 0)
// clang-format on

#undef X
