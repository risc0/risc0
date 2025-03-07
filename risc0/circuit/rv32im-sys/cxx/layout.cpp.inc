using Reg4LayoutArray = std::array<Reg, 4>;
struct MuxLayout {
  Reg4LayoutArray body;
  Reg4LayoutArray ramFini;
  Reg4LayoutArray ramInit;
  Reg4LayoutArray ramLoad;
  Reg4LayoutArray reset;
};
constexpr MuxLayout kAccumLayout = MuxLayout{
    .body = Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
    .ramFini = Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
    .ramInit = Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
    .ramLoad = Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
    .reset = Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27}};
struct RamPlonkElementLayout {
  Reg addr;
  Reg cycle;
  Reg memOp;
  Reg4LayoutArray data;
};
using Reg3LayoutArray = std::array<Reg, 3>;
struct RamPlonkVerifierLayout {
  Reg dirty;
  Reg extra;
  Reg isNewAddr;
  Reg3LayoutArray diff;
};
struct RamHeaderLayout {
  RamPlonkElementLayout element;
  RamPlonkVerifierLayout verifier;
};
struct HaltCycleLayout {
  Reg sysExitCode;
  Reg userExitCode;
  Reg writeAddr;
};
using Reg17LayoutArray = std::array<Reg, 17>;
using Reg2LayoutArray = std::array<Reg, 2>;
struct PcRegLayout {
  Reg2LayoutArray twits;
  Reg3LayoutArray bytes;
};
struct BodyStepLayout {
  Reg nextMajor;
  Reg userMode;
  RamHeaderLayout header;
  HaltCycleLayout majorMux;
  Reg17LayoutArray majorSelect;
  PcRegLayout pc;
};
struct Mux0Layout {
  BodyStepLayout body;
  RamHeaderLayout ramFini;
  RamHeaderLayout ramInit;
  RamHeaderLayout ramLoad;
  RamHeaderLayout reset;
};
struct TopLayout {
  Reg halted;
  Mux0Layout mux;
};
constexpr TopLayout kDataLayout =
    TopLayout{.halted = /*offset=*/2,
              .mux = Mux0Layout{
                  .body = BodyStepLayout{.nextMajor = /*offset=*/100,
                                         .userMode = /*offset=*/99,
                                         .header = RamHeaderLayout{.element =
                                                                       RamPlonkElementLayout{
                                                                           .addr = /*offset=*/89, .cycle = /*offset=*/90, .memOp = /*offset=*/91, .data = Reg4LayoutArray{/*offset=*/92, /*offset=*/93, /*offset=*/94, /*offset=*/95}},
                                                                   .verifier =
                                                                       RamPlonkVerifierLayout{.dirty =
                                                                                                  /*offset=*/97,
                                                                                              .extra =
                                                                                                  /*offset=*/69,
                                                                                              .isNewAddr =
                                                                                                  /*offset=*/96,
                                                                                              .diff =
                                                                                                  Reg3LayoutArray{
                                                                                                      /*offset=*/
                                                                                                      3,
                                                                                                      /*offset=*/4,
                                                                                                      /*offset=*/
                                                                                                      5}}},
                                         .majorMux = HaltCycleLayout{.sysExitCode = /*offset=*/118,
                                                                     .userExitCode = /*offset=*/119,
                                                                     .writeAddr = /*offset=*/120},
                                         .majorSelect = Reg17LayoutArray{/*offset=*/101,
                                                                         /*offset=*/102,
                                                                         /*offset=*/103,
                                                                         /*offset=*/104,
                                                                         /*offset=*/105,
                                                                         /*offset=*/106,
                                                                         /*offset=*/107,
                                                                         /*offset=*/108,
                                                                         /*offset=*/109,
                                                                         /*offset=*/110,
                                                                         /*offset=*/111,
                                                                         /*offset=*/112,
                                                                         /*offset=*/113,
                                                                         /*offset=*/114,
                                                                         /*offset=*/115,
                                                                         /*offset=*/116,
                                                                         /*offset=*/117},
                                         .pc = PcRegLayout{.twits = Reg2LayoutArray{/*offset=*/70,
                                                                                    /*offset=*/71},
                                                           .bytes = Reg3LayoutArray{/*offset=*/6,
                                                                                    /*offset=*/7,
                                                                                    /*offset=*/8}}},
                  .ramFini =
                      RamHeaderLayout{
                          .element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                           .cycle = /*offset=*/90,
                                                           .memOp = /*offset=*/91,
                                                           .data = Reg4LayoutArray{/*offset=*/92,
                                                                                   /*offset=*/93,
                                                                                   /*offset=*/94,
                                                                                   /*offset=*/95}},
                          .verifier =
                              RamPlonkVerifierLayout{.dirty = /*offset=*/97,
                                                     .extra = /*offset=*/69,
                                                     .isNewAddr = /*offset=*/96,
                                                     .diff = Reg3LayoutArray{/*offset=*/3,
                                                                             /*offset=*/4,
                                                                             /*offset=*/5}}},
                  .ramInit =
                      RamHeaderLayout{
                          .element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                           .cycle = /*offset=*/90,
                                                           .memOp = /*offset=*/91,
                                                           .data = Reg4LayoutArray{/*offset=*/92,
                                                                                   /*offset=*/93,
                                                                                   /*offset=*/94,
                                                                                   /*offset=*/95}},
                          .verifier =
                              RamPlonkVerifierLayout{.dirty = /*offset=*/97,
                                                     .extra = /*offset=*/69,
                                                     .isNewAddr = /*offset=*/96,
                                                     .diff = Reg3LayoutArray{/*offset=*/3,
                                                                             /*offset=*/4,
                                                                             /*offset=*/5}}},
                  .ramLoad =
                      RamHeaderLayout{
                          .element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                           .cycle = /*offset=*/90,
                                                           .memOp = /*offset=*/91,
                                                           .data = Reg4LayoutArray{/*offset=*/92,
                                                                                   /*offset=*/93,
                                                                                   /*offset=*/94,
                                                                                   /*offset=*/95}},
                          .verifier =
                              RamPlonkVerifierLayout{.dirty = /*offset=*/97,
                                                     .extra = /*offset=*/69,
                                                     .isNewAddr = /*offset=*/96,
                                                     .diff = Reg3LayoutArray{/*offset=*/3,
                                                                             /*offset=*/4,
                                                                             /*offset=*/5}}},
                  .reset =
                      RamHeaderLayout{
                          .element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                           .cycle = /*offset=*/90,
                                                           .memOp = /*offset=*/91,
                                                           .data = Reg4LayoutArray{/*offset=*/92,
                                                                                   /*offset=*/93,
                                                                                   /*offset=*/94,
                                                                                   /*offset=*/95}},
                          .verifier = RamPlonkVerifierLayout{
                              .dirty = /*offset=*/97,
                              .extra = /*offset=*/69,
                              .isNewAddr = /*offset=*/96,
                              .diff = Reg3LayoutArray{/*offset=*/3, /*offset=*/4, /*offset=*/5}}}}};
using Reg4LayoutArray7LayoutArray = std::array<Reg4LayoutArray, 7>;
struct Mux1Layout {
  Reg4LayoutArray7LayoutArray body;
  Reg4LayoutArray7LayoutArray ramFini;
  Reg4LayoutArray7LayoutArray ramInit;
  Reg4LayoutArray7LayoutArray ramLoad;
  Reg4LayoutArray7LayoutArray reset;
};
constexpr Mux1Layout kMixLayout =
    Mux1Layout{.body =
                   Reg4LayoutArray7LayoutArray{
                       Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                       Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                       Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                       Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                       Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                       Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                       Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramFini =
                   Reg4LayoutArray7LayoutArray{
                       Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                       Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                       Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                       Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                       Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                       Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                       Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramInit =
                   Reg4LayoutArray7LayoutArray{
                       Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                       Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                       Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                       Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                       Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                       Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                       Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramLoad =
                   Reg4LayoutArray7LayoutArray{
                       Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                       Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                       Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                       Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                       Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                       Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                       Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .reset = Reg4LayoutArray7LayoutArray{
                   Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                   Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                   Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                   Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                   Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                   Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                   Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}}};
using Reg4LayoutArray8LayoutArray = std::array<Reg4LayoutArray, 8>;
struct SystemStateLayout {
  Reg4LayoutArray8LayoutArray imageId;
  Reg4LayoutArray pc;
};
struct GlobalLayout {
  Reg sysExitCode;
  Reg userExitCode;
  Reg4LayoutArray8LayoutArray input;
  Reg4LayoutArray8LayoutArray output;
  SystemStateLayout post;
  SystemStateLayout pre;
};
constexpr GlobalLayout kOutLayout =
    GlobalLayout{
        .sysExitCode = /*offset=*/104,
        .userExitCode = /*offset=*/105,
        .input =
            Reg4LayoutArray8LayoutArray{
                Reg4LayoutArray{/*offset=*/0, /*offset=*/1, /*offset=*/2, /*offset=*/3},
                Reg4LayoutArray{/*offset=*/4, /*offset=*/5, /*offset=*/6, /*offset=*/7},
                Reg4LayoutArray{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                Reg4LayoutArray{/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                Reg4LayoutArray{/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                Reg4LayoutArray{/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                Reg4LayoutArray{/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                Reg4LayoutArray{/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31}},
        .output =
            Reg4LayoutArray8LayoutArray{
                Reg4LayoutArray{/*offset=*/106, /*offset=*/107, /*offset=*/108, /*offset=*/109},
                Reg4LayoutArray{/*offset=*/110, /*offset=*/111, /*offset=*/112, /*offset=*/113},
                Reg4LayoutArray{/*offset=*/114, /*offset=*/115, /*offset=*/116, /*offset=*/117},
                Reg4LayoutArray{/*offset=*/118, /*offset=*/119, /*offset=*/120, /*offset=*/121},
                Reg4LayoutArray{/*offset=*/122, /*offset=*/123, /*offset=*/124, /*offset=*/125},
                Reg4LayoutArray{/*offset=*/126, /*offset=*/127, /*offset=*/128, /*offset=*/129},
                Reg4LayoutArray{/*offset=*/130, /*offset=*/131, /*offset=*/132, /*offset=*/133},
                Reg4LayoutArray{/*offset=*/134, /*offset=*/135, /*offset=*/136, /*offset=*/137}},
        .post =
            SystemStateLayout{
                .imageId =
                    Reg4LayoutArray8LayoutArray{
                        Reg4LayoutArray{/*offset=*/72, /*offset=*/73, /*offset=*/74, /*offset=*/75},
                        Reg4LayoutArray{/*offset=*/76, /*offset=*/77, /*offset=*/78, /*offset=*/79},
                        Reg4LayoutArray{/*offset=*/80, /*offset=*/81, /*offset=*/82, /*offset=*/83},
                        Reg4LayoutArray{/*offset=*/84, /*offset=*/85, /*offset=*/86, /*offset=*/87},
                        Reg4LayoutArray{/*offset=*/88, /*offset=*/89, /*offset=*/90, /*offset=*/91},
                        Reg4LayoutArray{/*offset=*/92, /*offset=*/93, /*offset=*/94, /*offset=*/95},
                        Reg4LayoutArray{/*offset=*/96, /*offset=*/97, /*offset=*/98, /*offset=*/99},
                        Reg4LayoutArray{
                            /*offset=*/100, /*offset=*/101, /*offset=*/102, /*offset=*/103}},
                .pc = Reg4LayoutArray{/*offset=*/68, /*offset=*/69, /*offset=*/70, /*offset=*/71}},
        .pre =
            SystemStateLayout{
                .imageId =
                    Reg4LayoutArray8LayoutArray{
                        Reg4LayoutArray{/*offset=*/36, /*offset=*/37, /*offset=*/38, /*offset=*/39},
                        Reg4LayoutArray{/*offset=*/40, /*offset=*/41, /*offset=*/42, /*offset=*/43},
                        Reg4LayoutArray{/*offset=*/44, /*offset=*/45, /*offset=*/46, /*offset=*/47},
                        Reg4LayoutArray{/*offset=*/48, /*offset=*/49, /*offset=*/50, /*offset=*/51},
                        Reg4LayoutArray{/*offset=*/52, /*offset=*/53, /*offset=*/54, /*offset=*/55},
                        Reg4LayoutArray{/*offset=*/56, /*offset=*/57, /*offset=*/58, /*offset=*/59},
                        Reg4LayoutArray{/*offset=*/60, /*offset=*/61, /*offset=*/62, /*offset=*/63},
                        Reg4LayoutArray{
                            /*offset=*/64, /*offset=*/65, /*offset=*/66, /*offset=*/67}},
                .pc = Reg4LayoutArray{/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}}};
