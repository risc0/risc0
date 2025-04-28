struct RecursionCheckedBytesInstLayout {
  Reg evalPoint;
  Reg keepCoeffs;
  Reg keepUpperState;
  Reg prepFull;
};
struct OneHotLayout {
  Reg bitAndElem;
  Reg bitOpShorts;
  Reg nop;
  Reg setGlobal;
  Reg shaFini;
  Reg shaInit;
  Reg shaLoad;
  Reg shaMix;
  Reg womFini;
  Reg womInit;
};
using Reg3LayoutArray = ::cuda::std::array<Reg, 3>;
struct RecursionMacroInstLayout {
  OneHotLayout opcode;
  Reg3LayoutArray operand;
};
struct RecursionMicroInstLayout {
  Reg opcode;
  Reg3LayoutArray operand;
};
using RecursionMicroInstLayout3LayoutArray = ::cuda::std::array<RecursionMicroInstLayout, 3>;
struct OneHot0Layout {
  Reg c0;
  Reg c1;
  Reg c2;
  Reg c3;
};
struct OneHot1Layout {
  Reg g0;
  Reg g1;
  Reg g2;
};
using Reg8LayoutArray = ::cuda::std::array<Reg, 8>;
struct RecursionPoseidon2MemInstLayout {
  Reg doMont;
  Reg keepState;
  Reg keepUpperState;
  Reg prepFull;
  OneHot1Layout group;
  Reg8LayoutArray inputs;
};
struct MuxLayout {
  RecursionCheckedBytesInstLayout checkedBytes;
  RecursionMacroInstLayout macroOps;
  RecursionMicroInstLayout3LayoutArray microOps;
  OneHot0Layout poseidon2Full;
  RecursionPoseidon2MemInstLayout poseidon2Load;
  RecursionPoseidon2MemInstLayout poseidon2Store;
};
struct OneHot2Layout {
  Reg checkedBytes;
  Reg macroOps;
  Reg microOps;
  Reg poseidon2Full;
  Reg poseidon2Load;
  Reg poseidon2Partial;
  Reg poseidon2Store;
};
struct RecursionCodeLayout {
  Reg writeAddr;
  MuxLayout inst;
  OneHot2Layout select;
};
struct RecursionTopLayout {
  RecursionCodeLayout code;
  RecursionMicroInstLayout3LayoutArray mux;
};
__device__ constexpr RecursionTopLayout kCodeLayout =
    RecursionTopLayout{.code = RecursionCodeLayout{.writeAddr = /*offset=*/0,
                                                   .inst = MuxLayout{.checkedBytes =
                                                                         RecursionCheckedBytesInstLayout{.evalPoint = /*offset=*/8, .keepCoeffs = /*offset=*/9, .keepUpperState = /*offset=*/10, .prepFull = /*offset=*/11},
                                                                     .macroOps = RecursionMacroInstLayout{.opcode = OneHotLayout{.bitAndElem = /*offset=*/11, .bitOpShorts = /*offset=*/12, .nop = /*offset=*/8, .setGlobal = /*offset=*/17, .shaFini = /*offset=*/14, .shaInit = /*offset=*/13, .shaLoad = /*offset=*/15, .shaMix = /*offset=*/16, .womFini = /*offset=*/10, .womInit = /*offset=*/9},
                                                                                                          .operand =
                                                                                                              Reg3LayoutArray{
                                                                                                                  /*offset=*/
                                                                                                                  18,
                                                                                                                  /*offset=*/19,
                                                                                                                  /*offset=*/
                                                                                                                  20}},
                                                                     .microOps = RecursionMicroInstLayout3LayoutArray{RecursionMicroInstLayout{.opcode = /*offset=*/8, .operand = Reg3LayoutArray{/*offset=*/9, /*offset=*/10, /*offset=*/11}},
                                                                                                                      RecursionMicroInstLayout{
                                                                                                                          .opcode =
                                                                                                                              /*offset=*/12,
                                                                                                                          .operand =
                                                                                                                              Reg3LayoutArray{/*offset=*/13, /*offset=*/14, /*offset=*/15}},
                                                                                                                      RecursionMicroInstLayout{.opcode = /*offset=*/16,
                                                                                                                                               .operand =
                                                                                                                                                   Reg3LayoutArray{/*offset=*/17, /*offset=*/18, /*offset=*/19}}},
                                                                     .poseidon2Full =
                                                                         OneHot0Layout{.c0 = /*offset=*/8, .c1 = /*offset=*/9, .c2 = /*offset=*/10, .c3 = /*offset=*/11},
                                                                     .poseidon2Load =
                                                                         RecursionPoseidon2MemInstLayout{.doMont = /*offset=*/
                                                                                                         8,
                                                                                                         .keepState =
                                                                                                             /*offset=*/9,
                                                                                                         .keepUpperState =
                                                                                                             /*offset=*/
                                                                                                         10,
                                                                                                         .prepFull =
                                                                                                             /*offset=*/
                                                                                                         11,
                                                                                                         .group = OneHot1Layout{.g0 =
                                                                                                                                    /*offset=*/12,
                                                                                                                                .g1 =
                                                                                                                                    /*offset=*/13,
                                                                                                                                .g2 =
                                                                                                                                    /*offset=*/14},
                                                                                                         .inputs = Reg8LayoutArray{/*offset=*/15, /*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19, /*offset=*/20, /*offset=*/21, /*offset=*/22}},
                                                                     .poseidon2Store = RecursionPoseidon2MemInstLayout{.doMont =
                                                                                                                           /*offset=*/
                                                                                                                       8,
                                                                                                                       .keepState =
                                                                                                                           /*offset=*/9,
                                                                                                                       .keepUpperState = /*offset=*/
                                                                                                                       10,
                                                                                                                       .prepFull =
                                                                                                                           /*offset=*/
                                                                                                                       11,
                                                                                                                       .group =
                                                                                                                           OneHot1Layout{
                                                                                                                               .g0 =
                                                                                                                                   /*offset=*/
                                                                                                                               12,
                                                                                                                               .g1 =
                                                                                                                                   /*offset=*/
                                                                                                                               13,
                                                                                                                               .g2 =
                                                                                                                                   /*offset=*/
                                                                                                                               14},
                                                                                                                       .inputs =
                                                                                                                           Reg8LayoutArray{
                                                                                                                               /*offset=*/
                                                                                                                               15,
                                                                                                                               /*offset=*/
                                                                                                                               16,
                                                                                                                               /*offset=*/
                                                                                                                               17,
                                                                                                                               /*offset=*/
                                                                                                                               18,
                                                                                                                               /*offset=*/19,
                                                                                                                               /*offset=*/
                                                                                                                               20,
                                                                                                                               /*offset=*/
                                                                                                                               21,
                                                                                                                               /*offset=*/
                                                                                                                               22}}},
                                                   .select =
                                                       OneHot2Layout{
                                                           .checkedBytes = /*offset=*/7,
                                                           .macroOps = /*offset=*/2,
                                                           .microOps = /*offset=*/1,
                                                           .poseidon2Full = /*offset=*/4,
                                                           .poseidon2Load = /*offset=*/3,
                                                           .poseidon2Partial = /*offset=*/5,
                                                           .poseidon2Store = /*offset=*/6}},
                       .mux = RecursionMicroInstLayout3LayoutArray{
                           RecursionMicroInstLayout{
                               .opcode = /*offset=*/8,
                               .operand =
                                   Reg3LayoutArray{/*offset=*/9, /*offset=*/10, /*offset=*/11}},
                           RecursionMicroInstLayout{
                               .opcode = /*offset=*/12,
                               .operand =
                                   Reg3LayoutArray{/*offset=*/13, /*offset=*/14, /*offset=*/15}},
                           RecursionMicroInstLayout{
                               .opcode = /*offset=*/16,
                               .operand =
                                   Reg3LayoutArray{/*offset=*/17, /*offset=*/18, /*offset=*/19}}}};
using Reg4LayoutArray = ::cuda::std::array<Reg, 4>;
struct RecursionImplWomPlonkElementLayout {
  Reg addr;
  Reg4LayoutArray data;
};
using Reg31LayoutArray = ::cuda::std::array<Reg, 31>;
struct RecursionBitAndElemLayout {
  RecursionImplWomPlonkElementLayout inA;
  RecursionImplWomPlonkElementLayout inB;
  RecursionImplWomPlonkElementLayout out;
  Reg31LayoutArray bitsA;
  Reg31LayoutArray bitsB;
};
using Reg32LayoutArray = ::cuda::std::array<Reg, 32>;
struct RecursionBitOpShortsLayout {
  RecursionImplWomPlonkElementLayout inA;
  RecursionImplWomPlonkElementLayout inB;
  RecursionImplWomPlonkElementLayout out;
  Reg32LayoutArray bitsA;
  Reg32LayoutArray bitsB;
};
using RecursionImplWomPlonkElementLayout4LayoutArray =
    ::cuda::std::array<RecursionImplWomPlonkElementLayout, 4>;
struct RecursionSetGlobalLayout {
  Reg4LayoutArray select;
  RecursionImplWomPlonkElementLayout4LayoutArray regs;
};
using Reg2LayoutArray = ::cuda::std::array<Reg, 2>;
struct RecursionShaCycleLayout {
  Reg aCarryHi;
  Reg aCarryLow;
  Reg eCarryHigh;
  Reg eCarryLow;
  Reg wCarryHigh;
  Reg wCarryLow;
  RecursionImplWomPlonkElementLayout io0;
  RecursionImplWomPlonkElementLayout io1;
  Reg32LayoutArray a;
  Reg2LayoutArray aRaw;
  Reg32LayoutArray e;
  Reg2LayoutArray eRaw;
  Reg32LayoutArray w;
  Reg2LayoutArray wRaw;
};
struct Mux3Layout {
  RecursionBitAndElemLayout bitAndElem;
  RecursionBitOpShortsLayout bitOpShorts;
  RecursionSetGlobalLayout setGlobal;
  RecursionShaCycleLayout shaFini;
  RecursionShaCycleLayout shaInit;
  RecursionShaCycleLayout shaLoad;
  RecursionShaCycleLayout shaMix;
};
struct OneHot4Layout {
  Reg add;
  Reg constop;
  Reg eq;
  Reg extract;
  Reg inv;
  Reg mixRng;
  Reg mul;
  Reg readIopBody;
  Reg readIopHeader;
  Reg select;
  Reg sub;
};
struct RecursionMicroOpLayout {
  Reg extra;
  OneHot4Layout decode;
  RecursionImplWomPlonkElementLayout in0;
  RecursionImplWomPlonkElementLayout in1;
  RecursionImplWomPlonkElementLayout out;
};
using RecursionMicroOpLayout3LayoutArray = ::cuda::std::array<RecursionMicroOpLayout, 3>;
struct Mux5Layout {
  RecursionImplWomPlonkElementLayout checkedBytes;
  Mux3Layout macroOps;
  RecursionMicroOpLayout3LayoutArray microOps;
};
__device__ constexpr Mux5Layout kDataLayout =
    Mux5Layout{
        .checkedBytes =
            RecursionImplWomPlonkElementLayout{
                .addr = /*offset=*/5,
                .data = Reg4LayoutArray{/*offset=*/6, /*offset=*/7, /*offset=*/8, /*offset=*/9}},
        .macroOps =
            Mux3Layout{
                .bitAndElem =
                    RecursionBitAndElemLayout{
                        .inA =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/11,
                                .data = Reg4LayoutArray{
                                    /*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15}},
                        .inB =
                            RecursionImplWomPlonkElementLayout{.addr = /*offset=*/16,
                                                               .data = Reg4LayoutArray{
                                                                   /*offset=*/17,
                                                                   /*offset=*/18,
                                                                   /*offset=*/19,
                                                                   /*offset=*/20}},
                        .out =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/21,
                                .data = Reg4LayoutArray{/*offset=*/22,
                                                        /*offset=*/23,
                                                        /*offset=*/24,
                                                        /*offset=*/25}},
                        .bitsA =
                            Reg31LayoutArray{/*offset=*/36, /*offset=*/38, /*offset=*/40,
                                             /*offset=*/42, /*offset=*/44, /*offset=*/46,
                                             /*offset=*/48, /*offset=*/50, /*offset=*/52,
                                             /*offset=*/54, /*offset=*/56, /*offset=*/58,
                                             /*offset=*/60, /*offset=*/62, /*offset=*/64,
                                             /*offset=*/66, /*offset=*/68, /*offset=*/70,
                                             /*offset=*/72, /*offset=*/74, /*offset=*/76,
                                             /*offset=*/78, /*offset=*/80, /*offset=*/82,
                                             /*offset=*/84, /*offset=*/86, /*offset=*/88,
                                             /*offset=*/90, /*offset=*/92, /*offset=*/94,
                                             /*offset=*/96},
                        .bitsB =
                            Reg31LayoutArray{/*offset=*/37, /*offset=*/39, /*offset=*/41,
                                             /*offset=*/43, /*offset=*/45, /*offset=*/47,
                                             /*offset=*/49, /*offset=*/51, /*offset=*/53,
                                             /*offset=*/55, /*offset=*/57, /*offset=*/59,
                                             /*offset=*/61, /*offset=*/63, /*offset=*/65,
                                             /*offset=*/67, /*offset=*/69, /*offset=*/71,
                                             /*offset=*/73, /*offset=*/75, /*offset=*/77,
                                             /*offset=*/79, /*offset=*/81, /*offset=*/83,
                                             /*offset=*/85, /*offset=*/87, /*offset=*/89,
                                             /*offset=*/91, /*offset=*/93, /*offset=*/95,
                                             /*offset=*/97}},
                .bitOpShorts =
                    RecursionBitOpShortsLayout{
                        .inA = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/11,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/12,
                                                                      /*offset=*/13,
                                                                      /*offset=*/14,
                                                                      /*offset=*/15}},
                        .inB =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/16,
                                .data = Reg4LayoutArray{/*offset=*/17,
                                                        /*offset=*/18,
                                                        /*offset=*/19,
                                                        /*offset=*/20}},
                        .out =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/21,
                                .data = Reg4LayoutArray{/*offset=*/22,
                                                        /*offset=*/23,
                                                        /*offset=*/24,
                                                        /*offset=*/25}},
                        .bitsA =
                            Reg32LayoutArray{/*offset=*/36, /*offset=*/37, /*offset=*/38,
                                             /*offset=*/39, /*offset=*/40, /*offset=*/41,
                                             /*offset=*/42, /*offset=*/43, /*offset=*/44,
                                             /*offset=*/45, /*offset=*/46, /*offset=*/47,
                                             /*offset=*/48, /*offset=*/49, /*offset=*/50,
                                             /*offset=*/51, /*offset=*/52, /*offset=*/53,
                                             /*offset=*/54, /*offset=*/55, /*offset=*/56,
                                             /*offset=*/57, /*offset=*/58, /*offset=*/59,
                                             /*offset=*/60, /*offset=*/61, /*offset=*/62,
                                             /*offset=*/63, /*offset=*/64, /*offset=*/65,
                                             /*offset=*/66, /*offset=*/67},
                        .bitsB =
                            Reg32LayoutArray{/*offset=*/68, /*offset=*/69, /*offset=*/70,
                                             /*offset=*/71, /*offset=*/72, /*offset=*/73,
                                             /*offset=*/74, /*offset=*/75, /*offset=*/76,
                                             /*offset=*/77, /*offset=*/78, /*offset=*/79,
                                             /*offset=*/80, /*offset=*/81, /*offset=*/82,
                                             /*offset=*/83, /*offset=*/84, /*offset=*/85,
                                             /*offset=*/86, /*offset=*/87, /*offset=*/88,
                                             /*offset=*/89, /*offset=*/90, /*offset=*/91,
                                             /*offset=*/92, /*offset=*/93, /*offset=*/94,
                                             /*offset=*/95, /*offset=*/96, /*offset=*/97,
                                             /*offset=*/98, /*offset=*/99}},
                .setGlobal = RecursionSetGlobalLayout{.select = Reg4LayoutArray{/*offset=*/11,
                                                                                /*offset=*/12,
                                                                                /*offset=*/13,
                                                                                /*offset=*/14},
                                                      .regs =
                                                          RecursionImplWomPlonkElementLayout4LayoutArray{
                                                              RecursionImplWomPlonkElementLayout{
                                                                  .addr = /*offset=*/15,
                                                                  .data =
                                                                      Reg4LayoutArray{
                                                                          /*offset=*/16,
                                                                          /*offset=*/17,
                                                                          /*offset=*/18,
                                                                          /*offset=*/19}},
                                                              RecursionImplWomPlonkElementLayout{
                                                                  .addr = /*offset=*/20,
                                                                  .data =
                                                                      Reg4LayoutArray{
                                                                          /*offset=*/21,
                                                                          /*offset=*/22,
                                                                          /*offset=*/23,
                                                                          /*offset=*/24}},
                                                              RecursionImplWomPlonkElementLayout{
                                                                  .addr = /*offset=*/25,
                                                                  .data =
                                                                      Reg4LayoutArray{
                                                                          /*offset=*/26,
                                                                          /*offset=*/27,
                                                                          /*offset=*/28,
                                                                          /*offset=*/29}},
                                                              RecursionImplWomPlonkElementLayout{
                                                                  .addr = /*offset=*/30,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/31,
                                                                      /*offset=*/32,
                                                                      /*offset=*/33,
                                                                      /*offset=*/34}}}},
                .shaFini =
                    RecursionShaCycleLayout{
                        .aCarryHi = /*offset=*/6,
                        .aCarryLow = /*offset=*/5,
                        .eCarryHigh = /*offset=*/8,
                        .eCarryLow = /*offset=*/7,
                        .wCarryHigh = /*offset=*/10,
                        .wCarryLow = /*offset=*/9,
                        .io0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/11,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/12,
                                                                      /*offset=*/13,
                                                                      /*offset=*/14,
                                                                      /*offset=*/15}},
                        .io1 =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/16,
                                .data = Reg4LayoutArray{/*offset=*/17,
                                                        /*offset=*/18,
                                                        /*offset=*/19,
                                                        /*offset=*/20}},
                        .a =
                            Reg32LayoutArray{/*offset=*/26, /*offset=*/27, /*offset=*/28,
                                             /*offset=*/29, /*offset=*/30, /*offset=*/31,
                                             /*offset=*/32, /*offset=*/33, /*offset=*/34,
                                             /*offset=*/35, /*offset=*/36, /*offset=*/37,
                                             /*offset=*/38, /*offset=*/39, /*offset=*/40,
                                             /*offset=*/41, /*offset=*/42, /*offset=*/43,
                                             /*offset=*/44, /*offset=*/45, /*offset=*/46,
                                             /*offset=*/47, /*offset=*/48, /*offset=*/49,
                                             /*offset=*/50, /*offset=*/51, /*offset=*/52,
                                             /*offset=*/53, /*offset=*/54, /*offset=*/55,
                                             /*offset=*/56, /*offset=*/57},
                        .aRaw = Reg2LayoutArray{/*offset=*/58, /*offset=*/59},
                        .e =
                            Reg32LayoutArray{/*offset=*/60, /*offset=*/61, /*offset=*/62,
                                             /*offset=*/63, /*offset=*/64, /*offset=*/65,
                                             /*offset=*/66, /*offset=*/67, /*offset=*/68,
                                             /*offset=*/69, /*offset=*/70, /*offset=*/71,
                                             /*offset=*/72, /*offset=*/73, /*offset=*/74,
                                             /*offset=*/75, /*offset=*/76, /*offset=*/77,
                                             /*offset=*/78, /*offset=*/79, /*offset=*/80,
                                             /*offset=*/81, /*offset=*/82, /*offset=*/83,
                                             /*offset=*/84, /*offset=*/85, /*offset=*/86,
                                             /*offset=*/87, /*offset=*/88, /*offset=*/89,
                                             /*offset=*/90, /*offset=*/91},
                        .eRaw = Reg2LayoutArray{/*offset=*/92, /*offset=*/93},
                        .w =
                            Reg32LayoutArray{
                                /*offset=*/94,  /*offset=*/95,  /*offset=*/96,
                                /*offset=*/97,  /*offset=*/98,  /*offset=*/99,
                                /*offset=*/100, /*offset=*/101, /*offset=*/102,
                                /*offset=*/103, /*offset=*/104, /*offset=*/105,
                                /*offset=*/106, /*offset=*/107, /*offset=*/108,
                                /*offset=*/109, /*offset=*/110, /*offset=*/111,
                                /*offset=*/112, /*offset=*/113, /*offset=*/114,
                                /*offset=*/115, /*offset=*/116, /*offset=*/117,
                                /*offset=*/118, /*offset=*/119, /*offset=*/120,
                                /*offset=*/121, /*offset=*/122, /*offset=*/123,
                                /*offset=*/124, /*offset=*/125},
                        .wRaw = Reg2LayoutArray{/*offset=*/126, /*offset=*/127}},
                .shaInit =
                    RecursionShaCycleLayout{
                        .aCarryHi = /*offset=*/6,
                        .aCarryLow = /*offset=*/5,
                        .eCarryHigh = /*offset=*/8,
                        .eCarryLow = /*offset=*/7,
                        .wCarryHigh = /*offset=*/10,
                        .wCarryLow = /*offset=*/9,
                        .io0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/11,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/12,
                                                                      /*offset=*/13,
                                                                      /*offset=*/14,
                                                                      /*offset=*/15}},
                        .io1 =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/16,
                                .data = Reg4LayoutArray{/*offset=*/17,
                                                        /*offset=*/18,
                                                        /*offset=*/19,
                                                        /*offset=*/20}},
                        .a =
                            Reg32LayoutArray{/*offset=*/26, /*offset=*/27, /*offset=*/28,
                                             /*offset=*/29, /*offset=*/30, /*offset=*/31,
                                             /*offset=*/32, /*offset=*/33, /*offset=*/34,
                                             /*offset=*/35, /*offset=*/36, /*offset=*/37,
                                             /*offset=*/38, /*offset=*/39, /*offset=*/40,
                                             /*offset=*/41, /*offset=*/42, /*offset=*/43,
                                             /*offset=*/44, /*offset=*/45, /*offset=*/46,
                                             /*offset=*/47, /*offset=*/48, /*offset=*/49,
                                             /*offset=*/50, /*offset=*/51, /*offset=*/52,
                                             /*offset=*/53, /*offset=*/54, /*offset=*/55,
                                             /*offset=*/56, /*offset=*/57},
                        .aRaw = Reg2LayoutArray{/*offset=*/58, /*offset=*/59},
                        .e =
                            Reg32LayoutArray{/*offset=*/60, /*offset=*/61, /*offset=*/62,
                                             /*offset=*/63, /*offset=*/64, /*offset=*/65,
                                             /*offset=*/66, /*offset=*/67, /*offset=*/68,
                                             /*offset=*/69, /*offset=*/70, /*offset=*/71,
                                             /*offset=*/72, /*offset=*/73, /*offset=*/74,
                                             /*offset=*/75, /*offset=*/76, /*offset=*/77,
                                             /*offset=*/78, /*offset=*/79, /*offset=*/80,
                                             /*offset=*/81, /*offset=*/82, /*offset=*/83,
                                             /*offset=*/84, /*offset=*/85, /*offset=*/86,
                                             /*offset=*/87, /*offset=*/88, /*offset=*/89,
                                             /*offset=*/90, /*offset=*/91},
                        .eRaw = Reg2LayoutArray{/*offset=*/92, /*offset=*/93},
                        .w =
                            Reg32LayoutArray{
                                /*offset=*/94,  /*offset=*/95,  /*offset=*/96,
                                /*offset=*/97,  /*offset=*/98,  /*offset=*/99,
                                /*offset=*/100, /*offset=*/101, /*offset=*/102,
                                /*offset=*/103, /*offset=*/104, /*offset=*/105,
                                /*offset=*/106, /*offset=*/107, /*offset=*/108,
                                /*offset=*/109, /*offset=*/110, /*offset=*/111,
                                /*offset=*/112, /*offset=*/113, /*offset=*/114,
                                /*offset=*/115, /*offset=*/116, /*offset=*/117,
                                /*offset=*/118, /*offset=*/119, /*offset=*/120,
                                /*offset=*/121, /*offset=*/122, /*offset=*/123,
                                /*offset=*/124, /*offset=*/125},
                        .wRaw = Reg2LayoutArray{/*offset=*/126, /*offset=*/127}},
                .shaLoad =
                    RecursionShaCycleLayout{
                        .aCarryHi = /*offset=*/6,
                        .aCarryLow = /*offset=*/5,
                        .eCarryHigh = /*offset=*/8,
                        .eCarryLow = /*offset=*/7,
                        .wCarryHigh = /*offset=*/10,
                        .wCarryLow = /*offset=*/9,
                        .io0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/11,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/12,
                                                                      /*offset=*/13,
                                                                      /*offset=*/14,
                                                                      /*offset=*/15}},
                        .io1 =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/16,
                                .data = Reg4LayoutArray{/*offset=*/17,
                                                        /*offset=*/18,
                                                        /*offset=*/19,
                                                        /*offset=*/20}},
                        .a =
                            Reg32LayoutArray{/*offset=*/26, /*offset=*/27, /*offset=*/28,
                                             /*offset=*/29, /*offset=*/30, /*offset=*/31,
                                             /*offset=*/32, /*offset=*/33, /*offset=*/34,
                                             /*offset=*/35, /*offset=*/36, /*offset=*/37,
                                             /*offset=*/38, /*offset=*/39, /*offset=*/40,
                                             /*offset=*/41, /*offset=*/42, /*offset=*/43,
                                             /*offset=*/44, /*offset=*/45, /*offset=*/46,
                                             /*offset=*/47, /*offset=*/48, /*offset=*/49,
                                             /*offset=*/50, /*offset=*/51, /*offset=*/52,
                                             /*offset=*/53, /*offset=*/54, /*offset=*/55,
                                             /*offset=*/56, /*offset=*/57},
                        .aRaw = Reg2LayoutArray{/*offset=*/58, /*offset=*/59},
                        .e =
                            Reg32LayoutArray{/*offset=*/60, /*offset=*/61, /*offset=*/62,
                                             /*offset=*/63, /*offset=*/64, /*offset=*/65,
                                             /*offset=*/66, /*offset=*/67, /*offset=*/68,
                                             /*offset=*/69, /*offset=*/70, /*offset=*/71,
                                             /*offset=*/72, /*offset=*/73, /*offset=*/74,
                                             /*offset=*/75, /*offset=*/76, /*offset=*/77,
                                             /*offset=*/78, /*offset=*/79, /*offset=*/80,
                                             /*offset=*/81, /*offset=*/82, /*offset=*/83,
                                             /*offset=*/84, /*offset=*/85, /*offset=*/86,
                                             /*offset=*/87, /*offset=*/88, /*offset=*/89,
                                             /*offset=*/90, /*offset=*/91},
                        .eRaw = Reg2LayoutArray{/*offset=*/92, /*offset=*/93},
                        .w =
                            Reg32LayoutArray{
                                /*offset=*/94,  /*offset=*/95,  /*offset=*/96,
                                /*offset=*/97,  /*offset=*/98,  /*offset=*/99,
                                /*offset=*/100, /*offset=*/101, /*offset=*/102,
                                /*offset=*/103, /*offset=*/104, /*offset=*/105,
                                /*offset=*/106, /*offset=*/107, /*offset=*/108,
                                /*offset=*/109, /*offset=*/110, /*offset=*/111,
                                /*offset=*/112, /*offset=*/113, /*offset=*/114,
                                /*offset=*/115, /*offset=*/116, /*offset=*/117,
                                /*offset=*/118, /*offset=*/119, /*offset=*/120,
                                /*offset=*/121, /*offset=*/122, /*offset=*/123,
                                /*offset=*/124, /*offset=*/125},
                        .wRaw = Reg2LayoutArray{/*offset=*/126, /*offset=*/127}},
                .shaMix =
                    RecursionShaCycleLayout{
                        .aCarryHi = /*offset=*/6,
                        .aCarryLow = /*offset=*/5,
                        .eCarryHigh = /*offset=*/8,
                        .eCarryLow = /*offset=*/7,
                        .wCarryHigh = /*offset=*/10,
                        .wCarryLow = /*offset=*/9,
                        .io0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/11,
                                                                  .data = Reg4LayoutArray{
                                                                      /*offset=*/12,
                                                                      /*offset=*/13,
                                                                      /*offset=*/14,
                                                                      /*offset=*/15}},
                        .io1 =
                            RecursionImplWomPlonkElementLayout{
                                .addr = /*offset=*/16,
                                .data = Reg4LayoutArray{/*offset=*/17,
                                                        /*offset=*/18,
                                                        /*offset=*/19,
                                                        /*offset=*/20}},
                        .a =
                            Reg32LayoutArray{/*offset=*/26, /*offset=*/27, /*offset=*/28,
                                             /*offset=*/29, /*offset=*/30, /*offset=*/31,
                                             /*offset=*/32, /*offset=*/33, /*offset=*/34,
                                             /*offset=*/35, /*offset=*/36, /*offset=*/37,
                                             /*offset=*/38, /*offset=*/39, /*offset=*/40,
                                             /*offset=*/41, /*offset=*/42, /*offset=*/43,
                                             /*offset=*/44, /*offset=*/45, /*offset=*/46,
                                             /*offset=*/47, /*offset=*/48, /*offset=*/49,
                                             /*offset=*/50, /*offset=*/51, /*offset=*/52,
                                             /*offset=*/53, /*offset=*/54, /*offset=*/55,
                                             /*offset=*/56, /*offset=*/57},
                        .aRaw = Reg2LayoutArray{/*offset=*/58, /*offset=*/59},
                        .e =
                            Reg32LayoutArray{/*offset=*/60, /*offset=*/61, /*offset=*/62,
                                             /*offset=*/63, /*offset=*/64, /*offset=*/65,
                                             /*offset=*/66, /*offset=*/67, /*offset=*/68,
                                             /*offset=*/69, /*offset=*/70, /*offset=*/71,
                                             /*offset=*/72, /*offset=*/73, /*offset=*/74,
                                             /*offset=*/75, /*offset=*/76, /*offset=*/77,
                                             /*offset=*/78, /*offset=*/79, /*offset=*/80,
                                             /*offset=*/81, /*offset=*/82, /*offset=*/83,
                                             /*offset=*/84, /*offset=*/85, /*offset=*/86,
                                             /*offset=*/87, /*offset=*/88, /*offset=*/89,
                                             /*offset=*/90, /*offset=*/91},
                        .eRaw = Reg2LayoutArray{/*offset=*/92, /*offset=*/93},
                        .w =
                            Reg32LayoutArray{
                                /*offset=*/94,  /*offset=*/95,  /*offset=*/96,
                                /*offset=*/97,  /*offset=*/98,  /*offset=*/99,
                                /*offset=*/100, /*offset=*/101, /*offset=*/102,
                                /*offset=*/103, /*offset=*/104, /*offset=*/105,
                                /*offset=*/106, /*offset=*/107, /*offset=*/108,
                                /*offset=*/109, /*offset=*/110, /*offset=*/111,
                                /*offset=*/112, /*offset=*/113, /*offset=*/114,
                                /*offset=*/115, /*offset=*/116, /*offset=*/117,
                                /*offset=*/118, /*offset=*/119, /*offset=*/120,
                                /*offset=*/121, /*offset=*/122, /*offset=*/123,
                                /*offset=*/124, /*offset=*/125},
                        .wRaw = Reg2LayoutArray{/*offset=*/126, /*offset=*/127}}},
        .microOps = RecursionMicroOpLayout3LayoutArray{
            RecursionMicroOpLayout{
                .extra = /*offset=*/101,
                .decode = OneHot4Layout{.add = /*offset=*/91,
                                        .constop = /*offset=*/90,
                                        .eq = /*offset=*/95,
                                        .extract = /*offset=*/100,
                                        .inv = /*offset=*/94,
                                        .mixRng = /*offset=*/98,
                                        .mul = /*offset=*/93,
                                        .readIopBody = /*offset=*/97,
                                        .readIopHeader = /*offset=*/96,
                                        .select = /*offset=*/99,
                                        .sub = /*offset=*/92},
                .in0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/5,
                                                          .data = Reg4LayoutArray{/*offset=*/6,
                                                                                  /*offset=*/7,
                                                                                  /*offset=*/8,
                                                                                  /*offset=*/9}},
                .in1 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/10,
                                                          .data = Reg4LayoutArray{/*offset=*/11,
                                                                                  /*offset=*/12,
                                                                                  /*offset=*/13,
                                                                                  /*offset=*/14}},
                .out = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/15,
                                                          .data = Reg4LayoutArray{/*offset=*/16,
                                                                                  /*offset=*/17,
                                                                                  /*offset=*/18,
                                                                                  /*offset=*/19}}},
            RecursionMicroOpLayout{
                .extra = /*offset=*/113,
                .decode = OneHot4Layout{.add = /*offset=*/103,
                                        .constop = /*offset=*/102,
                                        .eq = /*offset=*/107,
                                        .extract = /*offset=*/112,
                                        .inv = /*offset=*/106,
                                        .mixRng = /*offset=*/110,
                                        .mul = /*offset=*/105,
                                        .readIopBody = /*offset=*/109,
                                        .readIopHeader = /*offset=*/108,
                                        .select = /*offset=*/111,
                                        .sub = /*offset=*/104},
                .in0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/20,
                                                          .data = Reg4LayoutArray{/*offset=*/21,
                                                                                  /*offset=*/22,
                                                                                  /*offset=*/23,
                                                                                  /*offset=*/24}},
                .in1 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/25,
                                                          .data = Reg4LayoutArray{/*offset=*/26,
                                                                                  /*offset=*/27,
                                                                                  /*offset=*/28,
                                                                                  /*offset=*/29}},
                .out = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/30,
                                                          .data = Reg4LayoutArray{/*offset=*/31,
                                                                                  /*offset=*/32,
                                                                                  /*offset=*/33,
                                                                                  /*offset=*/34}}},
            RecursionMicroOpLayout{
                .extra = /*offset=*/125,
                .decode = OneHot4Layout{.add = /*offset=*/115,
                                        .constop = /*offset=*/114,
                                        .eq = /*offset=*/119,
                                        .extract = /*offset=*/124,
                                        .inv = /*offset=*/118,
                                        .mixRng = /*offset=*/122,
                                        .mul = /*offset=*/117,
                                        .readIopBody = /*offset=*/121,
                                        .readIopHeader = /*offset=*/120,
                                        .select = /*offset=*/123,
                                        .sub = /*offset=*/116},
                .in0 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/35,
                                                          .data = Reg4LayoutArray{/*offset=*/36,
                                                                                  /*offset=*/37,
                                                                                  /*offset=*/38,
                                                                                  /*offset=*/39}},
                .in1 = RecursionImplWomPlonkElementLayout{.addr = /*offset=*/40,
                                                          .data = Reg4LayoutArray{/*offset=*/41,
                                                                                  /*offset=*/42,
                                                                                  /*offset=*/43,
                                                                                  /*offset=*/44}},
                .out = RecursionImplWomPlonkElementLayout{
                    .addr = /*offset=*/45,
                    .data = Reg4LayoutArray{
                        /*offset=*/46, /*offset=*/47, /*offset=*/48, /*offset=*/49}}}}};
__device__ constexpr Reg32LayoutArray kOutLayout = Reg32LayoutArray{
    /*offset=*/0,  /*offset=*/1,  /*offset=*/2,  /*offset=*/3,  /*offset=*/4,
    /*offset=*/5,  /*offset=*/6,  /*offset=*/7,  /*offset=*/8,  /*offset=*/9,
    /*offset=*/10, /*offset=*/11, /*offset=*/12, /*offset=*/13, /*offset=*/14,
    /*offset=*/15, /*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19,
    /*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23, /*offset=*/24,
    /*offset=*/25, /*offset=*/26, /*offset=*/27, /*offset=*/28, /*offset=*/29,
    /*offset=*/30, /*offset=*/31};
