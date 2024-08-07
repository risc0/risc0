struct RecursionCheckedBytesInst {
  CodeReg evalPoint;
  CodeReg keepCoeffs;
  CodeReg keepUpperState;
  CodeReg prepFull;
};
struct OneHot {
  CodeReg bitAndElem;
  CodeReg bitOpShorts;
  CodeReg nop;
  CodeReg setGlobal;
  CodeReg shaFini;
  CodeReg shaInit;
  CodeReg shaLoad;
  CodeReg shaMix;
  CodeReg womFini;
  CodeReg womInit;
};
using CodeReg3LayoutArray = std::array<CodeReg, 3>;
struct RecursionMacroInst {
  OneHot opcode;
  CodeReg3LayoutArray operand;
};
struct RecursionMicroInst {
  CodeReg opcode;
  CodeReg3LayoutArray operand;
};
using RecursionMicroInst3LayoutArray = std::array<RecursionMicroInst, 3>;
struct OneHot0 {
  CodeReg c0;
  CodeReg c1;
  CodeReg c2;
  CodeReg c3;
};
struct OneHot1 {
  CodeReg g0;
  CodeReg g1;
  CodeReg g2;
};
using CodeReg8LayoutArray = std::array<CodeReg, 8>;
struct RecursionPoseidon2MemInst {
  CodeReg doMont;
  CodeReg keepState;
  CodeReg keepUpperState;
  CodeReg prepFull;
  OneHot1 group;
  CodeReg8LayoutArray inputs;
};
struct Mux {
  RecursionCheckedBytesInst checkedBytes;
  RecursionMacroInst macroOps;
  RecursionMicroInst3LayoutArray microOps;
  OneHot0 poseidon2Full;
  RecursionPoseidon2MemInst poseidon2Load;
  RecursionPoseidon2MemInst poseidon2Store;
};
struct OneHot2 {
  CodeReg checkedBytes;
  CodeReg macroOps;
  CodeReg microOps;
  CodeReg poseidon2Full;
  CodeReg poseidon2Load;
  CodeReg poseidon2Partial;
  CodeReg poseidon2Store;
};
struct RecursionCode {
  CodeReg writeAddr;
  Mux inst;
  OneHot2 select;
};
using DataReg4LayoutArray = std::array<DataReg, 4>;
struct RecursionImplWomPlonkElement {
  DataReg addr;
  DataReg4LayoutArray data;
};
using DataReg31LayoutArray = std::array<DataReg, 31>;
struct RecursionBitAndElem {
  RecursionImplWomPlonkElement inA;
  RecursionImplWomPlonkElement inB;
  RecursionImplWomPlonkElement out;
  DataReg31LayoutArray bitsA;
  DataReg31LayoutArray bitsB;
};
using DataReg32LayoutArray = std::array<DataReg, 32>;
struct RecursionBitOpShorts {
  RecursionImplWomPlonkElement inA;
  RecursionImplWomPlonkElement inB;
  RecursionImplWomPlonkElement out;
  DataReg32LayoutArray bitsA;
  DataReg32LayoutArray bitsB;
};
using OutReg32LayoutArray = std::array<OutReg, 32>;
using RecursionImplWomPlonkElement4LayoutArray = std::array<RecursionImplWomPlonkElement, 4>;
struct RecursionSetGlobal {
  DataReg4LayoutArray select;
  OutReg32LayoutArray out;
  RecursionImplWomPlonkElement4LayoutArray regs;
};
using DataReg2LayoutArray = std::array<DataReg, 2>;
struct RecursionShaCycle {
  DataReg aCarryHi;
  DataReg aCarryLow;
  DataReg eCarryHigh;
  DataReg eCarryLow;
  DataReg wCarryHigh;
  DataReg wCarryLow;
  RecursionImplWomPlonkElement io0;
  RecursionImplWomPlonkElement io1;
  DataReg32LayoutArray a;
  DataReg2LayoutArray aRaw;
  DataReg32LayoutArray e;
  DataReg2LayoutArray eRaw;
  DataReg32LayoutArray w;
  DataReg2LayoutArray wRaw;
};
struct Mux3 {
  RecursionBitAndElem bitAndElem;
  RecursionBitOpShorts bitOpShorts;
  RecursionSetGlobal setGlobal;
  RecursionShaCycle shaFini;
  RecursionShaCycle shaInit;
  RecursionShaCycle shaLoad;
  RecursionShaCycle shaMix;
};
struct OneHot4 {
  DataReg add;
  DataReg constop;
  DataReg eq;
  DataReg extract;
  DataReg inv;
  DataReg mixRng;
  DataReg mul;
  DataReg readIopBody;
  DataReg readIopHeader;
  DataReg select;
  DataReg sub;
};
struct RecursionMicroOp {
  DataReg extra;
  OneHot4 decode;
  RecursionImplWomPlonkElement in0;
  RecursionImplWomPlonkElement in1;
  RecursionMicroInst inst;
  RecursionImplWomPlonkElement out;
};
using RecursionMicroOp3LayoutArray = std::array<RecursionMicroOp, 3>;
struct Mux5 {
  RecursionImplWomPlonkElement checkedBytes;
  Mux3 macroOps;
  RecursionMicroOp3LayoutArray microOps;
};
struct RecursionTop {
  RecursionCode code;
  Mux5 mux;
};
constexpr RecursionTop kLayout = RecursionTop{
    .code =
        RecursionCode{.writeAddr = 0,
                      .inst = Mux{.checkedBytes = RecursionCheckedBytesInst{.evalPoint = 8,
                                                                            .keepCoeffs = 9,
                                                                            .keepUpperState = 10,
                                                                            .prepFull = 11},
                                  .macroOps =
                                      RecursionMacroInst{.opcode = OneHot{.bitAndElem = 11,
                                                                          .bitOpShorts = 12,
                                                                          .nop = 8,
                                                                          .setGlobal = 17,
                                                                          .shaFini = 14,
                                                                          .shaInit = 13,
                                                                          .shaLoad = 15,
                                                                          .shaMix = 16,
                                                                          .womFini = 10,
                                                                          .womInit = 9},
                                                         .operand =
                                                             CodeReg3LayoutArray{18, 19, 20}},
                                  .microOps =
                                      RecursionMicroInst3LayoutArray{
                                          RecursionMicroInst{.opcode = 8,
                                                             .operand =
                                                                 CodeReg3LayoutArray{9, 10, 11}},
                                          RecursionMicroInst{.opcode = 12,
                                                             .operand =
                                                                 CodeReg3LayoutArray{13, 14, 15}},
                                          RecursionMicroInst{.opcode = 16,
                                                             .operand =
                                                                 CodeReg3LayoutArray{17, 18, 19}}},
                                  .poseidon2Full = OneHot0{.c0 = 8, .c1 = 9, .c2 = 10, .c3 = 11},
                                  .poseidon2Load =
                                      RecursionPoseidon2MemInst{
                                          .doMont = 8,
                                          .keepState = 9,
                                          .keepUpperState = 10,
                                          .prepFull =
                                              11,
                                          .group = OneHot1{.g0 = 12, .g1 = 13, .g2 = 14},
                                          .inputs =
                                              CodeReg8LayoutArray{15, 16, 17, 18, 19, 20, 21, 22}},
                                  .poseidon2Store = RecursionPoseidon2MemInst{.doMont = 8,
                                                                              .keepState = 9,
                                                                              .keepUpperState = 10,
                                                                              .prepFull = 11,
                                                                              .group =
                                                                                  OneHot1{.g0 = 12,
                                                                                          .g1 = 13,
                                                                                          .g2 = 14},
                                                                              .inputs =
                                                                                  CodeReg8LayoutArray{15,
                                                                                                      16,
                                                                                                      17,
                                                                                                      18,
                                                                                                      19,
                                                                                                      20,
                                                                                                      21,
                                                                                                      22}}},
                      .select = OneHot2{.checkedBytes = 7,
                                        .macroOps = 2,
                                        .microOps = 1,
                                        .poseidon2Full = 4,
                                        .poseidon2Load = 3,
                                        .poseidon2Partial = 5,
                                        .poseidon2Store = 6}},
    .mux =
        Mux5{
            .checkedBytes =
                RecursionImplWomPlonkElement{.addr = 5, .data = DataReg4LayoutArray{6, 7, 8, 9}},
            .macroOps =
                Mux3{.bitAndElem =
                         RecursionBitAndElem{.inA = RecursionImplWomPlonkElement{.addr = 11,
                                                                                 .data = DataReg4LayoutArray{12,
                                                                                                             13,
                                                                                                             14,
                                                                                                             15}},
                                             .inB = RecursionImplWomPlonkElement{.addr = 16,
                                                                                 .data =
                                                                                     DataReg4LayoutArray{17,
                                                                                                         18,
                                                                                                         19,
                                                                                                         20}},
                                             .out = RecursionImplWomPlonkElement{.addr = 21,
                                                                                 .data =
                                                                                     DataReg4LayoutArray{22,
                                                                                                         23,
                                                                                                         24,
                                                                                                         25}},
                                             .bitsA = DataReg31LayoutArray{36, 38, 40, 42, 44, 46,
                                                                           48, 50, 52, 54, 56, 58,
                                                                           60, 62, 64, 66, 68, 70,
                                                                           72, 74, 76, 78, 80, 82,
                                                                           84, 86, 88, 90, 92, 94,
                                                                           96},
                                             .bitsB = DataReg31LayoutArray{37, 39, 41, 43, 45, 47,
                                                                           49, 51, 53, 55, 57, 59,
                                                                           61, 63, 65, 67, 69, 71,
                                                                           73, 75, 77, 79, 81, 83,
                                                                           85, 87, 89, 91, 93, 95,
                                                                           97}},
                     .bitOpShorts =
                         RecursionBitOpShorts{
                             .inA = RecursionImplWomPlonkElement{.addr = 11,
                                                                 .data = DataReg4LayoutArray{12, 13, 14, 15}},
                             .inB = RecursionImplWomPlonkElement{.addr = 16,
                                                                 .data = DataReg4LayoutArray{17, 18, 19, 20}},
                             .out = RecursionImplWomPlonkElement{.addr = 21,
                                                                 .data = DataReg4LayoutArray{22, 23, 24, 25}},
                             .bitsA = DataReg32LayoutArray{36, 37, 38, 39, 40, 41, 42, 43,
                                                           44, 45, 46, 47, 48, 49, 50, 51,
                                                           52, 53, 54, 55, 56, 57, 58, 59,
                                                           60, 61, 62, 63, 64, 65, 66, 67},
                             .bitsB = DataReg32LayoutArray{68, 69, 70, 71, 72, 73, 74, 75,
                                                           76, 77, 78, 79, 80, 81, 82, 83,
                                                           84, 85, 86, 87, 88, 89, 90, 91,
                                                           92, 93, 94, 95, 96, 97, 98, 99}},
                     .setGlobal = RecursionSetGlobal{.select = DataReg4LayoutArray{11, 12, 13, 14},
                                                     .out =
                                                         OutReg32LayoutArray{
                                                             0,  1,  2,  3,  4,  5,  6,  7,
                                                             8,  9,  10, 11, 12, 13, 14, 15,
                                                             16, 17, 18, 19, 20, 21, 22, 23,
                                                             24, 25, 26, 27, 28, 29, 30, 31},
                                                     .regs =
                                                         RecursionImplWomPlonkElement4LayoutArray{RecursionImplWomPlonkElement{
                                                                                                      .addr =
                                                                                                          15,
                                                                                                      .data = DataReg4LayoutArray{16, 17, 18, 19}},
                                                                                                  RecursionImplWomPlonkElement{
                                                                                                      .addr =
                                                                                                          20,
                                                                                                      .data = DataReg4LayoutArray{21, 22, 23, 24}},
                                                                                                  RecursionImplWomPlonkElement{
                                                                                                      .addr =
                                                                                                          25,
                                                                                                      .data = DataReg4LayoutArray{26, 27, 28, 29}},
                                                                                                  RecursionImplWomPlonkElement{
                                                                                                      .addr =
                                                                                                          30,
                                                                                                      .data = DataReg4LayoutArray{31, 32, 33, 34}}}},
                     .shaFini =
                         RecursionShaCycle{.aCarryHi = 6,
                                           .aCarryLow = 5,
                                           .eCarryHigh = 8,
                                           .eCarryLow = 7,
                                           .wCarryHigh = 10,
                                           .wCarryLow = 9,
                                           .io0 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 11,
                                                   .data = DataReg4LayoutArray{12, 13, 14, 15}},
                                           .io1 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 16,
                                                   .data = DataReg4LayoutArray{17, 18, 19, 20}},
                                           .a =
                                               DataReg32LayoutArray{26, 27, 28, 29, 30, 31, 32, 33,
                                                                    34, 35, 36, 37, 38, 39, 40, 41,
                                                                    42, 43, 44, 45, 46, 47, 48, 49,
                                                                    50, 51, 52, 53, 54, 55, 56, 57},
                                           .aRaw = DataReg2LayoutArray{58, 59},
                                           .e =
                                               DataReg32LayoutArray{60, 61, 62, 63, 64, 65, 66, 67,
                                                                    68, 69, 70, 71, 72, 73, 74, 75,
                                                                    76, 77, 78, 79, 80, 81, 82, 83,
                                                                    84, 85, 86, 87, 88, 89, 90, 91},
                                           .eRaw = DataReg2LayoutArray{92, 93},
                                           .w = DataReg32LayoutArray{94,  95,  96,  97,  98,  99,
                                                                     100, 101, 102, 103, 104, 105,
                                                                     106, 107, 108, 109, 110, 111,
                                                                     112, 113, 114, 115, 116, 117,
                                                                     118, 119, 120, 121, 122, 123,
                                                                     124, 125},
                                           .wRaw = DataReg2LayoutArray{126, 127}},
                     .shaInit =
                         RecursionShaCycle{.aCarryHi = 6,
                                           .aCarryLow = 5,
                                           .eCarryHigh = 8,
                                           .eCarryLow = 7,
                                           .wCarryHigh = 10,
                                           .wCarryLow = 9,
                                           .io0 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 11,
                                                   .data = DataReg4LayoutArray{12, 13, 14, 15}},
                                           .io1 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 16,
                                                   .data = DataReg4LayoutArray{17, 18, 19, 20}},
                                           .a =
                                               DataReg32LayoutArray{26, 27, 28, 29, 30, 31, 32, 33,
                                                                    34, 35, 36, 37, 38, 39, 40, 41,
                                                                    42, 43, 44, 45, 46, 47, 48, 49,
                                                                    50, 51, 52, 53, 54, 55, 56, 57},
                                           .aRaw = DataReg2LayoutArray{58, 59},
                                           .e =
                                               DataReg32LayoutArray{60, 61, 62, 63, 64, 65, 66, 67,
                                                                    68, 69, 70, 71, 72, 73, 74, 75,
                                                                    76, 77, 78, 79, 80, 81, 82, 83,
                                                                    84, 85, 86, 87, 88, 89, 90, 91},
                                           .eRaw = DataReg2LayoutArray{92, 93},
                                           .w = DataReg32LayoutArray{94,  95,  96,  97,  98,  99,
                                                                     100, 101, 102, 103, 104, 105,
                                                                     106, 107, 108, 109, 110, 111,
                                                                     112, 113, 114, 115, 116, 117,
                                                                     118, 119, 120, 121, 122, 123,
                                                                     124, 125},
                                           .wRaw = DataReg2LayoutArray{126, 127}},
                     .shaLoad =
                         RecursionShaCycle{.aCarryHi = 6,
                                           .aCarryLow = 5,
                                           .eCarryHigh = 8,
                                           .eCarryLow = 7,
                                           .wCarryHigh = 10,
                                           .wCarryLow = 9,
                                           .io0 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 11,
                                                   .data = DataReg4LayoutArray{12, 13, 14, 15}},
                                           .io1 =
                                               RecursionImplWomPlonkElement{
                                                   .addr = 16,
                                                   .data = DataReg4LayoutArray{17, 18, 19, 20}},
                                           .a =
                                               DataReg32LayoutArray{26, 27, 28, 29, 30, 31, 32, 33,
                                                                    34, 35, 36, 37, 38, 39, 40, 41,
                                                                    42, 43, 44, 45, 46, 47, 48, 49,
                                                                    50, 51, 52, 53, 54, 55, 56, 57},
                                           .aRaw = DataReg2LayoutArray{58, 59},
                                           .e =
                                               DataReg32LayoutArray{60, 61, 62, 63, 64, 65, 66, 67,
                                                                    68, 69, 70, 71, 72, 73, 74, 75,
                                                                    76, 77, 78, 79, 80, 81, 82, 83,
                                                                    84, 85, 86, 87, 88, 89, 90, 91},
                                           .eRaw = DataReg2LayoutArray{92, 93},
                                           .w = DataReg32LayoutArray{94,  95,  96,  97,  98,  99,
                                                                     100, 101, 102, 103, 104, 105,
                                                                     106, 107, 108, 109, 110, 111,
                                                                     112, 113, 114, 115, 116, 117,
                                                                     118, 119, 120, 121, 122, 123,
                                                                     124, 125},
                                           .wRaw = DataReg2LayoutArray{126, 127}},
                     .shaMix = RecursionShaCycle{.aCarryHi = 6,
                                                 .aCarryLow = 5,
                                                 .eCarryHigh = 8,
                                                 .eCarryLow = 7,
                                                 .wCarryHigh = 10,
                                                 .wCarryLow = 9,
                                                 .io0 =
                                                     RecursionImplWomPlonkElement{.addr = 11,
                                                                                  .data =
                                                                                      DataReg4LayoutArray{12,
                                                                                                          13,
                                                                                                          14,
                                                                                                          15}},
                                                 .io1 =
                                                     RecursionImplWomPlonkElement{.addr = 16,
                                                                                  .data =
                                                                                      DataReg4LayoutArray{17,
                                                                                                          18,
                                                                                                          19,
                                                                                                          20}},
                                                 .a = DataReg32LayoutArray{26, 27, 28, 29, 30, 31,
                                                                           32, 33, 34, 35, 36, 37,
                                                                           38, 39, 40, 41, 42, 43,
                                                                           44, 45, 46, 47, 48, 49,
                                                                           50, 51, 52, 53, 54, 55,
                                                                           56, 57},
                                                 .aRaw = DataReg2LayoutArray{58, 59},
                                                 .e = DataReg32LayoutArray{60, 61, 62, 63, 64, 65,
                                                                           66, 67, 68, 69, 70, 71,
                                                                           72, 73, 74, 75, 76, 77,
                                                                           78, 79, 80, 81, 82, 83,
                                                                           84, 85, 86, 87, 88, 89,
                                                                           90, 91},
                                                 .eRaw = DataReg2LayoutArray{92, 93},
                                                 .w =
                                                     DataReg32LayoutArray{
                                                         94,  95,  96,  97,  98,  99,  100, 101,
                                                         102, 103, 104, 105, 106, 107, 108, 109,
                                                         110, 111, 112, 113, 114, 115, 116, 117,
                                                         118, 119, 120, 121, 122, 123, 124, 125},
                                                 .wRaw = DataReg2LayoutArray{126, 127}}},
            .microOps = RecursionMicroOp3LayoutArray{
                RecursionMicroOp{
                    .extra = 101,
                    .decode = OneHot4{.add = 91,
                                      .constop = 90,
                                      .eq = 95,
                                      .extract = 100,
                                      .inv = 94,
                                      .mixRng = 98,
                                      .mul = 93,
                                      .readIopBody = 97,
                                      .readIopHeader = 96,
                                      .select = 99,
                                      .sub = 92},
                    .in0 = RecursionImplWomPlonkElement{.addr = 5,
                                                        .data = DataReg4LayoutArray{6, 7, 8, 9}},
                    .in1 =
                        RecursionImplWomPlonkElement{.addr = 10,
                                                     .data = DataReg4LayoutArray{11, 12, 13, 14}},
                    .inst =
                        RecursionMicroInst{.opcode = 8, .operand = CodeReg3LayoutArray{9, 10, 11}},
                    .out =
                        RecursionImplWomPlonkElement{.addr = 15,
                                                     .data = DataReg4LayoutArray{16, 17, 18, 19}}},
                RecursionMicroOp{
                    .extra = 113,
                    .decode = OneHot4{.add = 103,
                                      .constop = 102,
                                      .eq = 107,
                                      .extract = 112,
                                      .inv = 106,
                                      .mixRng = 110,
                                      .mul = 105,
                                      .readIopBody = 109,
                                      .readIopHeader = 108,
                                      .select = 111,
                                      .sub = 104},
                    .in0 =
                        RecursionImplWomPlonkElement{
                            .addr = 20, .data = DataReg4LayoutArray{21, 22, 23, 24}},
                    .in1 =
                        RecursionImplWomPlonkElement{
                            .addr = 25, .data = DataReg4LayoutArray{26, 27, 28, 29}},
                    .inst = RecursionMicroInst{.opcode = 12,
                                               .operand = CodeReg3LayoutArray{13, 14, 15}},
                    .out =
                        RecursionImplWomPlonkElement{.addr = 30,
                                                     .data = DataReg4LayoutArray{31, 32, 33, 34}}},
                RecursionMicroOp{.extra = 125,
                                 .decode = OneHot4{.add = 115,
                                                   .constop = 114,
                                                   .eq = 119,
                                                   .extract = 124,
                                                   .inv = 118,
                                                   .mixRng = 122,
                                                   .mul = 117,
                                                   .readIopBody = 121,
                                                   .readIopHeader = 120,
                                                   .select = 123,
                                                   .sub = 116},
                                 .in0 =
                                     RecursionImplWomPlonkElement{
                                         .addr = 35, .data = DataReg4LayoutArray{36, 37, 38, 39}},
                                 .in1 =
                                     RecursionImplWomPlonkElement{
                                         .addr = 40, .data = DataReg4LayoutArray{41, 42, 43, 44}},
                                 .inst =
                                     RecursionMicroInst{.opcode = 16,
                                                        .operand = CodeReg3LayoutArray{17, 18, 19}},
                                 .out = RecursionImplWomPlonkElement{
                                     .addr = 45, .data = DataReg4LayoutArray{46, 47, 48, 49}}}}}};
