using OutReg4LayoutArray = OutReg[4];
using OutReg4LayoutArray8LayoutArray = OutReg4LayoutArray[8];
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
using AccumReg4LayoutArray = AccumReg[4];
using DataReg4LayoutArray = DataReg[4];
struct RamPlonkElement {
  DataReg addr;
  DataReg cycle;
  DataReg memOp;
  DataReg4LayoutArray data;
};
using DataReg3LayoutArray = DataReg[3];
struct RamPlonkVerifier {
  DataReg dirty;
  DataReg extra;
  DataReg isNewAddr;
  DataReg3LayoutArray diff;
};
using MixReg4LayoutArray = MixReg[4];
using MixReg4LayoutArray7LayoutArray = MixReg4LayoutArray[7];
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
using DataReg16LayoutArray = DataReg[16];
using DataReg2LayoutArray = DataReg[2];
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
__device__ constexpr Top kLayout =
    Top{.halted = 2,
        .mux = Mux{
            .body = BodyStep{.nextMajor = 100,
                             .userMode = 99,
                             .global = Global{.sysExitCode = 104,
                                              .userExitCode = 105,
                                              .input = {{0, 1, 2, 3},
                                                        {4, 5, 6, 7},
                                                        {8, 9, 10, 11},
                                                        {12, 13, 14, 15},
                                                        {16, 17, 18, 19},
                                                        {20, 21, 22, 23},
                                                        {24, 25, 26, 27},
                                                        {28, 29, 30, 31}},
                                              .output = {{106, 107, 108, 109},
                                                         {110, 111, 112, 113},
                                                         {114, 115, 116, 117},
                                                         {118, 119, 120, 121},
                                                         {122, 123, 124, 125},
                                                         {126, 127, 128, 129},
                                                         {130, 131, 132, 133},
                                                         {134, 135, 136, 137}},
                                              .post = SystemState{.imageId = {{72, 73, 74, 75},
                                                                              {76, 77, 78, 79},
                                                                              {80, 81, 82, 83},
                                                                              {84, 85, 86, 87},
                                                                              {88, 89, 90, 91},
                                                                              {92, 93, 94, 95},
                                                                              {96, 97, 98, 99},
                                                                              {100, 101, 102, 103}},
                                                                  .pc = {68, 69, 70, 71}},
                                              .pre = SystemState{.imageId = {{36, 37, 38, 39},
                                                                             {40, 41, 42, 43},
                                                                             {44, 45, 46, 47},
                                                                             {48, 49, 50, 51},
                                                                             {52, 53, 54, 55},
                                                                             {56, 57, 58, 59},
                                                                             {60, 61, 62, 63},
                                                                             {64, 65, 66, 67}},
                                                                 .pc = {32, 33, 34, 35}}},
                             .header = RamHeader{.accum = {24, 25, 26, 27},
                                                 .element = RamPlonkElement{.addr = 89,
                                                                            .cycle = 90,
                                                                            .memOp = 91,
                                                                            .data =
                                                                                {92, 93, 94, 95}},
                                                 .verifier = RamPlonkVerifier{.dirty = 97,
                                                                              .extra = 69,
                                                                              .isNewAddr = 96,
                                                                              .diff = {3, 4, 5}},
                                                 .mix = {{8, 9, 10, 11},
                                                         {12, 13, 14, 15},
                                                         {16, 17, 18, 19},
                                                         {20, 21, 22, 23},
                                                         {24, 25, 26, 27},
                                                         {28, 29, 30, 31},
                                                         {32, 33, 34, 35}}},
                             .majorMux =
                                 HaltCycle{
                                     .sysExitCode = 117, .userExitCode = 118, .writeAddr = 119},
                             .majorSelect =
                                 {101,
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
                             .pc = PcReg{.twits = {70, 71}, .bytes = {6, 7, 8}}},
            .ramFini = RamHeader{.accum = {24, 25, 26, 27},
                                 .element = RamPlonkElement{.addr = 89,
                                                            .cycle = 90,
                                                            .memOp = 91,
                                                            .data = {92, 93, 94, 95}},
                                 .verifier = RamPlonkVerifier{.dirty = 97,
                                                              .extra = 69,
                                                              .isNewAddr = 96,
                                                              .diff = {3, 4, 5}},
                                 .mix = {{8, 9, 10, 11},
                                         {12, 13, 14, 15},
                                         {16, 17, 18, 19},
                                         {20, 21, 22, 23},
                                         {24, 25, 26, 27},
                                         {28, 29, 30, 31},
                                         {32, 33, 34, 35}}},
            .ramInit = RamHeader{.accum = {24, 25, 26, 27},
                                 .element = RamPlonkElement{.addr = 89,
                                                            .cycle = 90,
                                                            .memOp = 91,
                                                            .data = {92, 93, 94, 95}},
                                 .verifier = RamPlonkVerifier{.dirty = 97,
                                                              .extra = 69,
                                                              .isNewAddr = 96,
                                                              .diff = {3, 4, 5}},
                                 .mix = {{8, 9, 10, 11},
                                         {12, 13, 14, 15},
                                         {16, 17, 18, 19},
                                         {20, 21, 22, 23},
                                         {24, 25, 26, 27},
                                         {28, 29, 30, 31},
                                         {32, 33, 34, 35}}},
            .ramLoad = RamHeader{.accum = {24, 25, 26, 27},
                                 .element = RamPlonkElement{.addr = 89,
                                                            .cycle = 90,
                                                            .memOp = 91,
                                                            .data = {92, 93, 94, 95}},
                                 .verifier = RamPlonkVerifier{.dirty = 97,
                                                              .extra = 69,
                                                              .isNewAddr = 96,
                                                              .diff = {3, 4, 5}},
                                 .mix = {{8, 9, 10, 11},
                                         {12, 13, 14, 15},
                                         {16, 17, 18, 19},
                                         {20, 21, 22, 23},
                                         {24, 25, 26, 27},
                                         {28, 29, 30, 31},
                                         {32, 33, 34, 35}}},
            .reset = RamHeader{
                .accum = {24, 25, 26, 27},
                .element =
                    RamPlonkElement{.addr = 89, .cycle = 90, .memOp = 91, .data = {92, 93, 94, 95}},
                .verifier =
                    RamPlonkVerifier{.dirty = 97, .extra = 69, .isNewAddr = 96, .diff = {3, 4, 5}},
                .mix = {{8, 9, 10, 11},
                        {12, 13, 14, 15},
                        {16, 17, 18, 19},
                        {20, 21, 22, 23},
                        {24, 25, 26, 27},
                        {28, 29, 30, 31},
                        {32, 33, 34, 35}}}}};
