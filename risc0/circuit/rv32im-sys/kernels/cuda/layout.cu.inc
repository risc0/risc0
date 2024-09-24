using Reg4LayoutArray = Reg[4];
struct MuxLayout {
  Reg4LayoutArray body;
  Reg4LayoutArray ramFini;
  Reg4LayoutArray ramInit;
  Reg4LayoutArray ramLoad;
  Reg4LayoutArray reset;
};
__device__ constexpr MuxLayout kAccumLayout =
    MuxLayout{.body = {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
              .ramFini = {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
              .ramInit = {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
              .ramLoad = {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
              .reset = {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27}};
struct RamPlonkElementLayout {
  Reg addr;
  Reg cycle;
  Reg memOp;
  Reg4LayoutArray data;
};
using Reg3LayoutArray = Reg[3];
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
using Reg16LayoutArray = Reg[16];
using Reg2LayoutArray = Reg[2];
struct PcRegLayout {
  Reg2LayoutArray twits;
  Reg3LayoutArray bytes;
};
struct BodyStepLayout {
  Reg nextMajor;
  Reg userMode;
  RamHeaderLayout header;
  HaltCycleLayout majorMux;
  Reg16LayoutArray majorSelect;
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
__device__ constexpr TopLayout kDataLayout =
    TopLayout{.halted = /*offset=*/2,
              .mux = Mux0Layout{
                  .body = BodyStepLayout{.nextMajor = /*offset=*/100,
                                         .userMode = /*offset=*/99,
                                         .header = RamHeaderLayout{.element =
                                                                       RamPlonkElementLayout{
                                                                           .addr = /*offset=*/89, .cycle = /*offset=*/90, .memOp = /*offset=*/91, .data = {/*offset=*/92, /*offset=*/93, /*offset=*/94, /*offset=*/95}},
                                                                   .verifier =
                                                                       RamPlonkVerifierLayout{.dirty =
                                                                                                  /*offset=*/97,
                                                                                              .extra =
                                                                                                  /*offset=*/69,
                                                                                              .isNewAddr =
                                                                                                  /*offset=*/96,
                                                                                              .diff = {/*offset=*/
                                                                                                       3,
                                                                                                       /*offset=*/4,
                                                                                                       /*offset=*/
                                                                                                       5}}},
                                         .majorMux = HaltCycleLayout{.sysExitCode = /*offset=*/117,
                                                                     .userExitCode = /*offset=*/118,
                                                                     .writeAddr = /*offset=*/119},
                                         .majorSelect = {/*offset=*/101,
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
                                                         /*offset=*/116},
                                         .pc = PcRegLayout{.twits = {/*offset=*/70, /*offset=*/71},
                                                           .bytes = {/*offset=*/6,
                                                                     /*offset=*/7,
                                                                     /*offset=*/8}}},
                  .ramFini =
                      RamHeaderLayout{.element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                                       .cycle = /*offset=*/90,
                                                                       .memOp = /*offset=*/91,
                                                                       .data = {/*offset=*/92,
                                                                                /*offset=*/93,
                                                                                /*offset=*/94,
                                                                                /*offset=*/95}},
                                      .verifier =
                                          RamPlonkVerifierLayout{
                                              .dirty = /*offset=*/97,
                                              .extra = /*offset=*/69,
                                              .isNewAddr = /*offset=*/96,
                                              .diff = {/*offset=*/3, /*offset=*/4, /*offset=*/5}}},
                  .ramInit =
                      RamHeaderLayout{.element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                                       .cycle = /*offset=*/90,
                                                                       .memOp = /*offset=*/91,
                                                                       .data = {/*offset=*/92,
                                                                                /*offset=*/93,
                                                                                /*offset=*/94,
                                                                                /*offset=*/95}},
                                      .verifier =
                                          RamPlonkVerifierLayout{
                                              .dirty = /*offset=*/97,
                                              .extra = /*offset=*/69,
                                              .isNewAddr = /*offset=*/96,
                                              .diff = {/*offset=*/3, /*offset=*/4, /*offset=*/5}}},
                  .ramLoad =
                      RamHeaderLayout{.element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                                       .cycle = /*offset=*/90,
                                                                       .memOp = /*offset=*/91,
                                                                       .data = {/*offset=*/92,
                                                                                /*offset=*/93,
                                                                                /*offset=*/94,
                                                                                /*offset=*/95}},
                                      .verifier =
                                          RamPlonkVerifierLayout{
                                              .dirty = /*offset=*/97,
                                              .extra = /*offset=*/69,
                                              .isNewAddr = /*offset=*/96,
                                              .diff = {/*offset=*/3, /*offset=*/4, /*offset=*/5}}},
                  .reset =
                      RamHeaderLayout{.element = RamPlonkElementLayout{.addr = /*offset=*/89,
                                                                       .cycle = /*offset=*/90,
                                                                       .memOp = /*offset=*/91,
                                                                       .data = {/*offset=*/92,
                                                                                /*offset=*/93,
                                                                                /*offset=*/94,
                                                                                /*offset=*/95}},
                                      .verifier = RamPlonkVerifierLayout{
                                          .dirty = /*offset=*/97,
                                          .extra = /*offset=*/69,
                                          .isNewAddr = /*offset=*/96,
                                          .diff = {/*offset=*/3, /*offset=*/4, /*offset=*/5}}}}};
using Reg4LayoutArray7LayoutArray = Reg4LayoutArray[7];
struct Mux1Layout {
  Reg4LayoutArray7LayoutArray body;
  Reg4LayoutArray7LayoutArray ramFini;
  Reg4LayoutArray7LayoutArray ramInit;
  Reg4LayoutArray7LayoutArray ramLoad;
  Reg4LayoutArray7LayoutArray reset;
};
__device__ constexpr Mux1Layout kMixLayout =
    Mux1Layout{.body = {{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                        {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                        {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                        {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                        {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                        {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                        {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramFini = {{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                           {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                           {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                           {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                           {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                           {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                           {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramInit = {{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                           {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                           {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                           {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                           {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                           {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                           {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .ramLoad = {{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                           {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                           {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                           {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                           {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                           {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                           {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}},
               .reset = {{/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                         {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                         {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                         {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                         {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                         {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31},
                         {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}}};
using Reg4LayoutArray8LayoutArray = Reg4LayoutArray[8];
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
__device__ constexpr GlobalLayout kOutLayout =
    GlobalLayout{
        .sysExitCode = /*offset=*/104,
        .userExitCode = /*offset=*/105,
        .input = {{/*offset=*/0, /*offset=*/1, /*offset=*/2, /*offset=*/3},
                  {/*offset=*/4, /*offset=*/5, /*offset=*/6, /*offset=*/7},
                  {/*offset=*/8, /*offset=*/9, /*offset=*/10, /*offset=*/11},
                  {/*offset=*/12, /*offset=*/13, /*offset=*/14, /*offset=*/15},
                  {/*offset=*/16, /*offset=*/17, /*offset=*/18, /*offset=*/19},
                  {/*offset=*/20, /*offset=*/21, /*offset=*/22, /*offset=*/23},
                  {/*offset=*/24, /*offset=*/25, /*offset=*/26, /*offset=*/27},
                  {/*offset=*/28, /*offset=*/29, /*offset=*/30, /*offset=*/31}},
        .output = {{/*offset=*/106, /*offset=*/107, /*offset=*/108, /*offset=*/109},
                   {/*offset=*/110, /*offset=*/111, /*offset=*/112, /*offset=*/113},
                   {/*offset=*/114, /*offset=*/115, /*offset=*/116, /*offset=*/117},
                   {/*offset=*/118, /*offset=*/119, /*offset=*/120, /*offset=*/121},
                   {/*offset=*/122, /*offset=*/123, /*offset=*/124, /*offset=*/125},
                   {/*offset=*/126, /*offset=*/127, /*offset=*/128, /*offset=*/129},
                   {/*offset=*/130, /*offset=*/131, /*offset=*/132, /*offset=*/133},
                   {/*offset=*/134, /*offset=*/135, /*offset=*/136, /*offset=*/137}},
        .post =
            SystemStateLayout{
                .imageId = {{/*offset=*/72, /*offset=*/73, /*offset=*/74, /*offset=*/75},
                            {/*offset=*/76, /*offset=*/77, /*offset=*/78, /*offset=*/79},
                            {/*offset=*/80, /*offset=*/81, /*offset=*/82, /*offset=*/83},
                            {/*offset=*/84, /*offset=*/85, /*offset=*/86, /*offset=*/87},
                            {/*offset=*/88, /*offset=*/89, /*offset=*/90, /*offset=*/91},
                            {/*offset=*/92, /*offset=*/93, /*offset=*/94, /*offset=*/95},
                            {/*offset=*/96, /*offset=*/97, /*offset=*/98, /*offset=*/99},
                            {/*offset=*/100, /*offset=*/101, /*offset=*/102, /*offset=*/103}},
                .pc = {/*offset=*/68, /*offset=*/69, /*offset=*/70, /*offset=*/71}},
        .pre = SystemStateLayout{
            .imageId = {{/*offset=*/36, /*offset=*/37, /*offset=*/38, /*offset=*/39},
                        {/*offset=*/40, /*offset=*/41, /*offset=*/42, /*offset=*/43},
                        {/*offset=*/44, /*offset=*/45, /*offset=*/46, /*offset=*/47},
                        {/*offset=*/48, /*offset=*/49, /*offset=*/50, /*offset=*/51},
                        {/*offset=*/52, /*offset=*/53, /*offset=*/54, /*offset=*/55},
                        {/*offset=*/56, /*offset=*/57, /*offset=*/58, /*offset=*/59},
                        {/*offset=*/60, /*offset=*/61, /*offset=*/62, /*offset=*/63},
                        {/*offset=*/64, /*offset=*/65, /*offset=*/66, /*offset=*/67}},
            .pc = {/*offset=*/32, /*offset=*/33, /*offset=*/34, /*offset=*/35}}};
