using OutReg4LayoutArray = std::array<OutReg, 4>;
using OutReg4LayoutArray8LayoutArray = std::array<OutReg4LayoutArray, 8>;
struct SystemState {
  OutReg4LayoutArray8LayoutArray imageId;
  OutReg4LayoutArray pc;
};
struct Global {
  OutReg sysExitCode;
  OutReg userExitCode;
  OutReg4LayoutArray8LayoutArray input;
  OutReg4LayoutArray8LayoutArray output;
  SystemState post;
  SystemState pre;
};
using AccumReg4LayoutArray = std::array<AccumReg, 4>;
using DataReg4LayoutArray = std::array<DataReg, 4>;
struct RamPlonkElement {
  DataReg addr;
  DataReg cycle;
  DataReg memOp;
  DataReg4LayoutArray data;
};
using DataReg3LayoutArray = std::array<DataReg, 3>;
struct RamPlonkVerifier {
  DataReg dirty;
  DataReg extra;
  DataReg isNewAddr;
  DataReg3LayoutArray diff;
};
using MixReg4LayoutArray = std::array<MixReg, 4>;
using MixReg4LayoutArray7LayoutArray = std::array<MixReg4LayoutArray, 7>;
struct RamHeader {
  AccumReg4LayoutArray accum;
  RamPlonkElement element;
  RamPlonkVerifier verifier;
  MixReg4LayoutArray7LayoutArray mix;
};
struct HaltCycle {
  DataReg sysExitCode;
  DataReg userExitCode;
  DataReg writeAddr;
};
using DataReg16LayoutArray = std::array<DataReg, 16>;
using DataReg2LayoutArray = std::array<DataReg, 2>;
struct PcReg {
  DataReg2LayoutArray twits;
  DataReg3LayoutArray bytes;
};
struct BodyStep {
  DataReg nextMajor;
  DataReg userMode;
  Global global;
  RamHeader header;
  HaltCycle majorMux;
  DataReg16LayoutArray majorSelect;
  PcReg pc;
};
struct Mux {
  BodyStep body;
  RamHeader ramFini;
  RamHeader ramInit;
  RamHeader ramLoad;
  RamHeader reset;
};
struct Top {
  DataReg halted;
  Mux mux;
};
constexpr Top kLayout =
    Top{.halted = 2,
        .mux = Mux{.body = BodyStep{.nextMajor = 100,
                                    .userMode = 99,
                                    .global =
                                        Global{.sysExitCode = 104,
                                               .userExitCode = 105,
                                               .input =
                                                   OutReg4LayoutArray8LayoutArray{
                                                       OutReg4LayoutArray{0, 1, 2, 3},
                                                       OutReg4LayoutArray{4, 5, 6, 7},
                                                       OutReg4LayoutArray{8, 9, 10, 11},
                                                       OutReg4LayoutArray{12, 13, 14, 15},
                                                       OutReg4LayoutArray{16, 17, 18, 19},
                                                       OutReg4LayoutArray{20, 21, 22, 23},
                                                       OutReg4LayoutArray{24, 25, 26, 27},
                                                       OutReg4LayoutArray{28, 29, 30, 31}},
                                               .output =
                                                   OutReg4LayoutArray8LayoutArray{
                                                       OutReg4LayoutArray{106, 107, 108, 109},
                                                       OutReg4LayoutArray{110, 111, 112, 113},
                                                       OutReg4LayoutArray{114, 115, 116, 117},
                                                       OutReg4LayoutArray{118, 119, 120, 121},
                                                       OutReg4LayoutArray{122, 123, 124, 125},
                                                       OutReg4LayoutArray{126, 127, 128, 129},
                                                       OutReg4LayoutArray{130, 131, 132, 133},
                                                       OutReg4LayoutArray{134, 135, 136, 137}},
                                               .post =
                                                   SystemState{
                                                       .imageId =
                                                           OutReg4LayoutArray8LayoutArray{
                                                               OutReg4LayoutArray{72, 73, 74, 75},
                                                               OutReg4LayoutArray{76, 77, 78, 79},
                                                               OutReg4LayoutArray{80, 81, 82, 83},
                                                               OutReg4LayoutArray{84, 85, 86, 87},
                                                               OutReg4LayoutArray{88, 89, 90, 91},
                                                               OutReg4LayoutArray{92, 93, 94, 95},
                                                               OutReg4LayoutArray{96, 97, 98, 99},
                                                               OutReg4LayoutArray{100,
                                                                                  101,
                                                                                  102,
                                                                                  103}},
                                                       .pc = OutReg4LayoutArray{68, 69, 70, 71}},
                                               .pre =
                                                   SystemState{
                                                       .imageId =
                                                           OutReg4LayoutArray8LayoutArray{
                                                               OutReg4LayoutArray{36, 37, 38, 39},
                                                               OutReg4LayoutArray{40, 41, 42, 43},
                                                               OutReg4LayoutArray{44, 45, 46, 47},
                                                               OutReg4LayoutArray{48, 49, 50, 51},
                                                               OutReg4LayoutArray{52, 53, 54, 55},
                                                               OutReg4LayoutArray{56, 57, 58, 59},
                                                               OutReg4LayoutArray{60, 61, 62, 63},
                                                               OutReg4LayoutArray{64, 65, 66, 67}},
                                                       .pc = OutReg4LayoutArray{32, 33, 34, 35}}},
                                    .header =
                                        RamHeader{
                                            .accum = AccumReg4LayoutArray{24, 25, 26, 27},
                                            .element =
                                                RamPlonkElement{
                                                    .addr = 89,
                                                    .cycle = 90,
                                                    .memOp = 91,
                                                    .data = DataReg4LayoutArray{92, 93, 94, 95}},
                                            .verifier =
                                                RamPlonkVerifier{.dirty = 97,
                                                                 .extra = 69,
                                                                 .isNewAddr = 96,
                                                                 .diff =
                                                                     DataReg3LayoutArray{3, 4, 5}},
                                            .mix =
                                                MixReg4LayoutArray7LayoutArray{
                                                    MixReg4LayoutArray{8, 9, 10, 11},
                                                    MixReg4LayoutArray{12, 13, 14, 15},
                                                    MixReg4LayoutArray{16, 17, 18, 19},
                                                    MixReg4LayoutArray{20, 21, 22, 23},
                                                    MixReg4LayoutArray{24, 25, 26, 27},
                                                    MixReg4LayoutArray{28, 29, 30, 31},
                                                    MixReg4LayoutArray{32, 33, 34, 35}}},
                                    .majorMux = HaltCycle{.sysExitCode = 117,
                                                          .userExitCode = 118,
                                                          .writeAddr = 119},
                                    .majorSelect = DataReg16LayoutArray{101,
                                                                        102,
                                                                        103,
                                                                        104,
                                                                        105,
                                                                        106,
                                                                        107,
                                                                        108,
                                                                        109,
                                                                        110,
                                                                        111,
                                                                        112,
                                                                        113,
                                                                        114,
                                                                        115,
                                                                        116},
                                    .pc = PcReg{.twits = DataReg2LayoutArray{70, 71},
                                                .bytes = DataReg3LayoutArray{6, 7, 8}}},
                   .ramFini =
                       RamHeader{
                           .accum = AccumReg4LayoutArray{24, 25, 26, 27},
                           .element = RamPlonkElement{.addr = 89,
                                                      .cycle = 90,
                                                      .memOp = 91,
                                                      .data = DataReg4LayoutArray{92, 93, 94, 95}},
                           .verifier = RamPlonkVerifier{.dirty = 97,
                                                        .extra = 69,
                                                        .isNewAddr = 96,
                                                        .diff = DataReg3LayoutArray{3, 4, 5}},
                           .mix =
                               MixReg4LayoutArray7LayoutArray{MixReg4LayoutArray{8, 9, 10, 11},
                                                              MixReg4LayoutArray{12, 13, 14, 15},
                                                              MixReg4LayoutArray{16, 17, 18, 19},
                                                              MixReg4LayoutArray{20, 21, 22, 23},
                                                              MixReg4LayoutArray{24, 25, 26, 27},
                                                              MixReg4LayoutArray{28, 29, 30, 31},
                                                              MixReg4LayoutArray{32, 33, 34, 35}}},
                   .ramInit =
                       RamHeader{
                           .accum = AccumReg4LayoutArray{24, 25, 26, 27},
                           .element = RamPlonkElement{.addr = 89,
                                                      .cycle = 90,
                                                      .memOp = 91,
                                                      .data = DataReg4LayoutArray{92, 93, 94, 95}},
                           .verifier = RamPlonkVerifier{.dirty = 97,
                                                        .extra = 69,
                                                        .isNewAddr = 96,
                                                        .diff = DataReg3LayoutArray{3, 4, 5}},
                           .mix =
                               MixReg4LayoutArray7LayoutArray{MixReg4LayoutArray{8, 9, 10, 11},
                                                              MixReg4LayoutArray{12, 13, 14, 15},
                                                              MixReg4LayoutArray{16, 17, 18, 19},
                                                              MixReg4LayoutArray{20, 21, 22, 23},
                                                              MixReg4LayoutArray{24, 25, 26, 27},
                                                              MixReg4LayoutArray{28, 29, 30, 31},
                                                              MixReg4LayoutArray{32, 33, 34, 35}}},
                   .ramLoad =
                       RamHeader{
                           .accum = AccumReg4LayoutArray{24, 25, 26, 27},
                           .element = RamPlonkElement{.addr = 89,
                                                      .cycle = 90,
                                                      .memOp = 91,
                                                      .data = DataReg4LayoutArray{92, 93, 94, 95}},
                           .verifier = RamPlonkVerifier{.dirty = 97,
                                                        .extra = 69,
                                                        .isNewAddr = 96,
                                                        .diff = DataReg3LayoutArray{3, 4, 5}},
                           .mix =
                               MixReg4LayoutArray7LayoutArray{MixReg4LayoutArray{8, 9, 10, 11},
                                                              MixReg4LayoutArray{12, 13, 14, 15},
                                                              MixReg4LayoutArray{16, 17, 18, 19},
                                                              MixReg4LayoutArray{20, 21, 22, 23},
                                                              MixReg4LayoutArray{24, 25, 26, 27},
                                                              MixReg4LayoutArray{28, 29, 30, 31},
                                                              MixReg4LayoutArray{32, 33, 34, 35}}},
                   .reset = RamHeader{
                       .accum = AccumReg4LayoutArray{24, 25, 26, 27},
                       .element = RamPlonkElement{.addr = 89,
                                                  .cycle = 90,
                                                  .memOp = 91,
                                                  .data = DataReg4LayoutArray{92, 93, 94, 95}},
                       .verifier = RamPlonkVerifier{.dirty = 97,
                                                    .extra = 69,
                                                    .isNewAddr = 96,
                                                    .diff = DataReg3LayoutArray{3, 4, 5}},
                       .mix = MixReg4LayoutArray7LayoutArray{MixReg4LayoutArray{8, 9, 10, 11},
                                                             MixReg4LayoutArray{12, 13, 14, 15},
                                                             MixReg4LayoutArray{16, 17, 18, 19},
                                                             MixReg4LayoutArray{20, 21, 22, 23},
                                                             MixReg4LayoutArray{24, 25, 26, 27},
                                                             MixReg4LayoutArray{28, 29, 30, 31},
                                                             MixReg4LayoutArray{32, 33, 34, 35}}}}};
