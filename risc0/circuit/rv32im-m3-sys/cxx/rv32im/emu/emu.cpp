// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#include "rv32im/emu/emu.h"

#include <ankerl/unordered_dense.h>

#include "core/log.h"
#include "rv32im/emu/bigint.h"
#include "rv32im/emu/decode.h"
#include "rv32im/emu/paging.h"
#include "zkp/fp.h"

#include "rv32im/base/opt.h"

namespace risc0::rv32im {

FILE* pcFile = nullptr;

namespace {

//#define DLOG(...) if (debug && mode != MODE_MACHINE) LOG(0, __VA_ARGS__)
#define DLOG(...) LOG(2, __VA_ARGS__)
// #define DLOG(...) if (mode != MODE_MACHINE) LOG(2, __VA_ARGS__)
// #define DLOG(...) /**/

struct Emulator {
  Emulator(Trace& trace, MemoryImage& image, HostIO& io, size_t rowCount)
      : trace(trace)
      , memory(trace, image)
      , io(io)
      , pages(MEMORY_SIZE_MPAGES)
      , regPage(memory.pageIn(MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2)) {
    pages[MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2] = regPage;
  }

  static constexpr uint32_t regPageAddr = MACHINE_REGS_WORD & ~MPAGE_MASK_WORDS;

  inline uint32_t peekReg(uint32_t reg) { return (*regPage)[regOffset + reg].value; }

  inline uint32_t readReg(RegMemReadWitness& record, uint32_t reg, bool sameReg = false) {
    uint32_t wordNum = regOffset + reg + (sameReg ? 64 : 0);
    record.wordAddr = regPageAddr + wordNum;
    record.prevCycle = (*regPage)[wordNum].cycle;
    record.value = (*regPage)[wordNum].value;
    (*regPage)[wordNum].cycle = curCycle * 2;
    return (sameReg ? (*regPage)[regOffset + reg].value : record.value);
  }

  inline void writeReg(RegMemWriteWitness& record, uint32_t reg, uint32_t value) {
    uint32_t wordNum = regOffset + reg + (reg == 0 ? 64 : 0);
    record.wordAddr = regPageAddr + wordNum;
    record.prevCycle = (*regPage)[wordNum].cycle;
    record.prevValue = (*regPage)[wordNum].value;
    (*regPage)[wordNum].value = value;
    (*regPage)[wordNum].cycle = curCycle * 2 + 1;
    record.value = value;
  }

  inline uint32_t peekPhysMemory(uint32_t wordAddr) {
    uint32_t pageId = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    PageDetails* page = pages[pageId];
    if (!page) {
      page = memory.pageIn(pageId);
      pages[pageId] = page;
    }
    return (*page)[wordAddr & MPAGE_MASK_WORDS].value;
  }

  inline uint8_t peekPhysByte(uint32_t addr) {
    uint32_t word = peekPhysMemory(addr / BYTES_PER_WORD);
    return word >> ((addr % BYTES_PER_WORD) * BITS_PER_BYTE);
  }

  inline uint32_t readPhysMemory(PhysMemReadWitness& record, uint32_t wordAddr) {
    uint32_t pageId = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    PageDetails* page = pages[pageId];
    if (!page) {
      page = memory.pageIn(pageId);
      pages[pageId] = page;
    }
    uint32_t wordNum = wordAddr & MPAGE_MASK_WORDS;
    record.wordAddr = wordAddr;
    record.prevCycle = (*page)[wordNum].cycle;
    record.value = (*page)[wordNum].value;
    (*page)[wordNum].cycle = curCycle * 2;
    return record.value;
  }

  inline void writePhysMemory(PhysMemWriteWitness& record, uint32_t wordAddr, uint32_t value) {
    uint32_t pageId = wordAddr >> MPAGE_SIZE_WORDS_PO2;
    PageDetails* page = pages[pageId];
    if (!page) {
      page = memory.pageIn(pageId);
      pages[pageId] = page;
    }
    uint32_t wordNum = wordAddr & MPAGE_MASK_WORDS;
    record.wordAddr = wordAddr;
    record.prevCycle = (*page)[wordNum].cycle;
    record.prevValue = (*page)[wordNum].value;
    (*page)[wordNum].value = value;
    (*page)[wordNum].cycle = curCycle * 2 + 1;
    record.value = value;
  }

  inline void undoPhysMemory(PhysMemReadWitness& record) {
    uint32_t pageId = record.wordAddr >> MPAGE_SIZE_WORDS_PO2;
    PageDetails* page = pages[pageId];
    uint32_t wordNum = record.wordAddr & MPAGE_MASK_WORDS;
    (*page)[wordNum].cycle = record.prevCycle;
  }

  std::pair<bool, uint32_t> translatePage(uint32_t vPage, uint32_t aType) {
    if (mode == MODE_MACHINE) { return { true, vPage }; } 
    uint32_t vinfo = peekPhysMemory(CSR_WORD(MVINFO));
    if ((vinfo & 0x80000000) == 0) { return { true, vPage }; }
    uint32_t a = vinfo << 12;
    uint32_t smode = mode == MODE_SUPERVISOR;
    uint32_t sum = (vinfo >> 29) & 1;
    uint32_t mxr = (vinfo >> 30) & 1;
    uint32_t i, xwr, pte, pteAddr;
    for (i = 2; i-- > 0;) {
      pteAddr = a + ((vPage >> (10 * i)) & 0x3ff)*4;
      if (pteAddr >= FIRMWARE_START_ADDR) { return { false, 0 }; }
      pte = peekPhysMemory(pteAddr/4);
      if ((pte & 1) == 0) { return { false, 0 }; }
      xwr = (pte >> 1) & 7;
      if (xwr == 2 || xwr == 6) { return { false, 0 }; }
      a = (pte << 2) & 0xfffff000;
      if (xwr != 0) break;
    }
    if (!xwr) { return { false, 0 }; }
    if (i == 1) {
      if (((pte >> 10) & 0x3ff) != 0) { return { false, 0 }; }
      a |= ((vPage & 0x3ff) << 12);
    }
    uint32_t u = (pte >> 4) & 1;
    uint32_t x = (pte >> 3) & 1;
    uint32_t w = (pte >> 2) & 1;
    uint32_t r = (pte >> 1) & 1;
    if (mxr && x) { r = 1; }
    if (!u && !smode) { return { false, 0 }; }
    if (u && !sum && smode) { return { false, 0 }; }
    if ((aType == ACCESS_FETCH && !x) ||
        (aType == ACCESS_LOAD && !r) ||
        (aType == ACCESS_STORE && !w)) {
      return { false, 0 };
    }
    pte |= (1 << 6);  // Set A bit always
    if (aType == ACCESS_STORE) { pte |= (1 << 7); } // Set D if write
    // TODO: Actually write
    PhysMemWriteWitness ignore;
    writePhysMemory(ignore, pteAddr/4, pte);
    //LOG(0, "vPage=" << HexWord{vPage} << ", pPage=" << HexWord{(a >> 12)} << ", key=" << key);
    return { true, a >> 12 };
  }

  std::pair<bool, uint32_t> computePhysPage(uint32_t vPage, uint32_t aType) {
    uint32_t key = vPage | (mode << 30) | aType << 28;
    auto it = virtualMem.find(key);
    if (it != virtualMem.end()) { return { true, it->second }; }
    auto [ok, pPage] = translatePage(vPage, aType);
    if (!ok) { return { false, 0 }; }
    virtualMem[key] = pPage;
    return { true, pPage };
  }

  inline std::pair<bool, uint32_t> translateAddress(VirtAddrWitness& record, uint32_t vWordAddr, uint32_t accessMode) {
    record.vpage = vWordAddr >> VPAGE_SIZE_WORDS_PO2;
    auto [ok, ppage] = computePhysPage(record.vpage, accessMode);
    if (!ok) { return { false, 0 }; }
    record.ppage = ppage;
    record.wordOffset = vWordAddr & VPAGE_MASK_WORDS;
    uint32_t pWordAddr = (record.ppage << VPAGE_SIZE_WORDS_PO2) | record.wordOffset;
    return { true, pWordAddr };
  }

  inline std::pair<bool, uint32_t> peekVirtMemory(uint32_t vWordAddr, uint32_t accessMode) {
    uint32_t vpage = vWordAddr >> VPAGE_SIZE_WORDS_PO2;
    auto [ok, ppage] = computePhysPage(vpage, accessMode);
    if (!ok) { return { false, 0 }; }
    uint32_t wordOffset = vWordAddr & VPAGE_MASK_WORDS;
    uint32_t pWordAddr = (ppage << VPAGE_SIZE_WORDS_PO2) | wordOffset; 
    return { true, peekPhysMemory(pWordAddr) };
  }

  inline std::pair<bool, uint32_t> fetchVirtMemory(VirtMemReadWitness& record, uint32_t vWordAddr) {
    auto [ok, pWordAddr] = translateAddress(record.addr, vWordAddr, ACCESS_FETCH);
    if (!ok) { return { false, 0 }; }
    PhysMemReadWitness phys;
    readPhysMemory(phys, pWordAddr);
    record.prevCycle = phys.prevCycle;
    record.value = phys.value;
    return { true, record.value };
  }

  inline std::pair<bool, uint32_t> readVirtMemory(VirtMemReadWitness& record, uint32_t vWordAddr) {
    auto [ok, pWordAddr] = translateAddress(record.addr, vWordAddr, ACCESS_LOAD);
    if (!ok) { return { false, 0 }; }
    PhysMemReadWitness phys;
    readPhysMemory(phys, pWordAddr);
    record.prevCycle = phys.prevCycle;
    record.value = phys.value;
    return { true, record.value };
  }

  inline bool writeVirtMemory(VirtMemWriteWitness& record, uint32_t vWordAddr, uint32_t value) {
    auto [ok, pWordAddr] = translateAddress(record.addr, vWordAddr, ACCESS_STORE);
    PhysMemWriteWitness phys;
    writePhysMemory(phys, pWordAddr, value);
    record.prevCycle = phys.prevCycle;
    record.prevValue = phys.prevValue;
    record.value = phys.value;
    return ok;
  }

  inline void undoVirtMemory(VirtMemReadWitness& record) {
    PhysMemReadWitness phys;
    phys.wordAddr = (record.addr.ppage << VPAGE_SIZE_WORDS_PO2) | record.addr.wordOffset;
    phys.prevCycle = record.prevCycle;
    undoPhysMemory(phys);
  }

#define UNIT_COMMON(name)                                                                          \
  auto& unit = trace.makeUnit##name();                                                             \
  unit.count = 1;                                                                                  \
  unit.opts = opt;                                                                                 \
  unit.a = a;                                                                                      \
  unit.b = b;                                                                                      \
  [[maybe_unused]] constexpr Option optInner = Option(opt).popRet<UnitKind>()

  template <uint32_t opt> inline UnitBaseWitness* unitAddSub(uint32_t a, uint32_t b) {
    UNIT_COMMON(AddSub);
    switch (optInner.peek<AsKind>()) {
    case AS_ADD:
      unit.out0 = a + b;
      break;
    case AS_SUB:
      unit.out0 = a - b;
      break;
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* unitBit(uint32_t a, uint32_t b) {
    UNIT_COMMON(Bit);
    switch (optInner.peek<BitKind>()) {
    case BIT_XOR:
      unit.out0 = a ^ b;
      break;
    case BIT_OR:
      unit.out0 = a | b;
      break;
    case BIT_AND:
      unit.out0 = a & b;
      break;
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* unitLt(uint32_t a, uint32_t b) {
    UNIT_COMMON(Lt);
    unit.out0 = int32_t(a) < int32_t(b);
    unit.out1 = a < b;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* unitMul(uint32_t a, uint32_t b) {
    UNIT_COMMON(Mul);
    uint64_t out;
    switch (optInner.peek<MulKind>()) {
    case MUL_SS:
      out = int64_t(int32_t(a)) * int64_t(int32_t(b));
      break;
    case MUL_SU:
      out = int64_t(int32_t(a)) * uint64_t(b);
      break;
    case MUL_UU:
      out = uint64_t(a) * uint64_t(b);
      break;
    }
    unit.out0 = uint32_t(out);
    unit.out1 = out >> 32;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* unitDiv(uint32_t a, uint32_t b) {
    UNIT_COMMON(Div);
    if (optInner.peek<DivKind>() == DIV_S) {
      // Intel processors actually fault if you do a signed division on MIN_INT
      // by 1/-1
      if (a == 0x80000000 && std::abs(int32_t(b)) == 1) {
        unit.out0 = 0x80000000;
        unit.out1 = 0;
      } else {
        if (b == 0) {
          unit.out0 = 0xffffffff;
          unit.out1 = a;
        } else {
          unit.out0 = int32_t(a) / int32_t(b);
          unit.out1 = int32_t(a) % int32_t(b);
        }
      }
      uint32_t absQuot = (b == 0 ? 0xffffffff : std::abs(int32_t(unit.out0)));
      unitMul<EncodeOptions(UNIT_MUL, MUL_UU).val>(absQuot, std::abs(int32_t(b)));
    } else {
      if (b == 0) {
        unit.out0 = 0xffffffff;
        unit.out1 = a;
      } else {
        unit.out0 = a / b;
        unit.out1 = a % b;
      }
      unitMul<EncodeOptions(UNIT_MUL, MUL_UU).val>(unit.out0, b);
    }
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* unitShift(uint32_t a, uint32_t b) {
    UNIT_COMMON(Shift);
    uint32_t po2 = (1 << (b & 0x1f));
    if (optInner.peek<ShiftKind>() == SHIFT_LL) {
      unitMul<EncodeOptions(UNIT_MUL, MUL_UU).val>(a, po2);
      unit.out0 = (a << (b & 0x1f));
    } else {
      bool neg = optInner.peek<ShiftKind>() == SHIFT_RA && (a & 0x80000000) != 0;
      if (neg) {
        a = ~a;
      }
      unitDiv<EncodeOptions(UNIT_DIV, DIV_U).val>(a, po2);
      unit.out0 = a >> (b & 0x1f);
      if (neg) {
        unit.out0 = ~unit.out0;
      }
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template <uint32_t opt> inline UnitBaseWitness* doUnit(uint32_t a, uint32_t b) {
    switch (Option(opt).peek<UnitKind>()) {
    case UNIT_ADDSUB:
      return unitAddSub<opt>(a, b);
    case UNIT_BIT:
      return unitBit<opt>(a, b);
    case UNIT_LT:
      return unitLt<opt>(a, b);
    case UNIT_MUL:
      return unitMul<opt>(a, b);
    case UNIT_DIV:
      return unitDiv<opt>(a, b);
    case UNIT_SHIFT:
      return unitShift<opt>(a, b);
    }
  }

  void setMode(uint32_t newMode) {
    mode = newMode;
    regOffset = (mode == MODE_MACHINE) ? (MACHINE_REGS_WORD & MPAGE_MASK_WORDS)
                                       : (USER_REGS_WORD & MPAGE_MASK_WORDS);
  }

  void doResume() {
    auto& wit = trace.makeInstResume();
    v2Compat = 1 - readPhysMemory(wit.v2Compat, CSR_WORD(MNOV2COMPAT));
    trace.getGlobals().v2Compat = v2Compat;
    if (v2Compat) {
      pc = readPhysMemory(wit.pc, V2_COMPAT_SPC);
      setMode(readPhysMemory(wit.mode, V2_COMPAT_SMODE) ? MODE_MACHINE : MODE_USER);
      writePhysMemory(wit.version, V2_COMPAT_VERSION, RV32IM_CIRCUIT_VERSION);
    } else {
      pc = readPhysMemory(wit.pc, CSR_WORD(MSPC));
      setMode(readPhysMemory(wit.mode, CSR_WORD(MSMODE)));
      writePhysMemory(wit.version, CSR_WORD(MVERSION), RV32IM_CIRCUIT_VERSION);
    }
    writePhysMemory(wit.writeCycle, CSR_WORD(MSCYCLE), curCycle + 1);
    countdown = peekPhysMemory(CSR_WORD(MCOUNTDOWN));
    curCycle++;
  }

  void doSuspend() {
    auto& wit = trace.makeInstSuspend();
    wit.cycle = curCycle;
    wit.iCacheCycle = iCacheCycle;
    if (v2Compat) {
      writePhysMemory(wit.pc, V2_COMPAT_SPC, pc);
      writePhysMemory(wit.mode, V2_COMPAT_SMODE, mode == MODE_MACHINE);
    } else {
      writePhysMemory(wit.pc, CSR_WORD(MSPC), pc);
      writePhysMemory(wit.mode, CSR_WORD(MSMODE), mode);
    }
    uint32_t oldCycle = readPhysMemory(wit.readCycle, CSR_WORD(MSCYCLE));
    if (mode == MODE_MACHINE) { oldCycle = curCycle; }
    uint32_t delta = curCycle - oldCycle;
    // Add delta to time
    uint64_t time = peekPhysMemory(CSR_WORD(MTIME)) | (uint64_t(peekPhysMemory(CSR_WORD(MTIMEH))) << 32);
    time += delta;
    writePhysMemory(wit.updateTime, CSR_WORD(MTIME), time & 0xffffffff);
    writePhysMemory(wit.updateTime, CSR_WORD(MTIMEH), time >> 32);
    // Subtract delta from countdown, is < 0 fatal
    countdown = peekPhysMemory(CSR_WORD(MCOUNTDOWN));
    countdown -= delta;
    if (countdown & 0x80000000) {
      // Underflow, die
      fatal("Counter underflow");
    }
    writePhysMemory(wit.updateTime, CSR_WORD(MCOUNTDOWN), countdown);
    curCycle++;
  }

  void trap(const std::string& reason, uint32_t trapType) {
    if (mode == MODE_MACHINE) {
      fatal("Double Trap: " + reason);
    }
    auto& wit = trace.makeInstTrap();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t mepcWord = v2Compat ? V2_COMPAT_MEPC : CSR_WORD(MEPC);
    wit.trapType = trapType;
    writePhysMemory(wit.writePc, mepcWord, pc);
    writePhysMemory(wit.writeMode, CSR_WORD(MEMODE), mode);
    uint32_t imm = trapType == TRAP_ECALL ? 0 : dinst->inst;
    writePhysMemory(wit.writeVal, CSR_WORD(MTVAL), imm);
    uint32_t dispatchWord;
    switch(trapType) {
      case TRAP_ECALL:
        dispatchWord = v2Compat ? V2_COMPAT_ECALL_DISPATCH : CSR_WORD(MTRAPECALL);
        break;
      case TRAP_INST:
        dispatchWord = CSR_WORD(MTRAPINST);
        break;
      case TRAP_FETCH:
        dispatchWord = CSR_WORD(MTRAPFETCH);
        break;
      case TRAP_INTER:
        dispatchWord = CSR_WORD(MTRAPINTER);
        break;
      default:
        throw std::runtime_error("Unknown trap call");
    }
    newPc = readPhysMemory(wit.readDispatch, dispatchWord);
    setMode(MODE_MACHINE);
    uint32_t oldCycle = readPhysMemory(wit.readCycle, CSR_WORD(MSCYCLE));
    uint32_t delta = curCycle - oldCycle;
    // Add delta to time
    uint64_t time = peekPhysMemory(CSR_WORD(MTIME)) | (uint64_t(peekPhysMemory(CSR_WORD(MTIMEH))) << 32);
    time += delta;
    writePhysMemory(wit.updateTime, CSR_WORD(MTIME), time & 0xffffffff);
    writePhysMemory(wit.updateTime, CSR_WORD(MTIMEH), time >> 32);
    // Subtract delta from countdown, is < 0 fatal
    countdown = peekPhysMemory(CSR_WORD(MCOUNTDOWN));
    countdown -= delta;
    if (countdown & 0x80000000) {
      // Underflow, die
      fatal("Counter underflow");
    }
    writePhysMemory(wit.updateTime, CSR_WORD(MCOUNTDOWN), countdown);
  }

  void fatal(const std::string& reason) { throw std::runtime_error("Fatal Error: " + reason); }

  template <uint32_t opt> inline void do_INST_REG() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto ok = opts2.peek<OutKind>();
    constexpr Option opts3 = opts2.popRet<OutKind>();
    auto& wit = trace.makeInstReg();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t rs1Val = readReg(wit.rs1, dinst->rs1);
    uint32_t rs2Val = readReg(wit.rs2, dinst->rs2, dinst->rs1 == dinst->rs2);
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts3.val>(rs1Val, rs2Val);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t rdVal = (ok == OUT_0 ? unit->out0 : unit->out1);
    writeReg(wit.rd, dinst->rd, rdVal);
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{rs1Val});
    DLOG("  RS2 = " << uint32_t(dinst->rs2) << ", val = " << HexWord{rs2Val});
    DLOG("  RD = " << uint32_t(dinst->rd) << ", val = " << HexWord{rdVal});
  }

  template <uint32_t opt> inline void do_INST_IMM() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto ok = opts2.peek<OutKind>();
    constexpr Option opts3 = opts2.popRet<OutKind>();
    auto& wit = trace.makeInstImm();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t rs1Val = readReg(wit.rs1, dinst->rs1);
    wit.rs2 = dinst->rs2;
    wit.imm = dinst->imm;
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts3.val>(rs1Val, wit.imm);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t rdVal = (ok == OUT_0 ? unit->out0 : unit->out1);
    writeReg(wit.rd, dinst->rd, rdVal);
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{rs1Val});
    DLOG("  IMM= " << HexWord{dinst->imm});
    DLOG("  RD = " << uint32_t(dinst->rd) << ", val = " << HexWord{rdVal});
  }

  template <uint32_t opt> inline void do_INST_LOAD() {
    constexpr Option optInner = Option(opt).popRet<InstKind>();
    auto kind = optInner.peek<LoadKind>();
    // Check alignment + trap if reqired
    uint32_t addr = peekReg(dinst->rs1) + dinst->imm;
    uint32_t alignmentReq = 1;
    switch (kind) {
    case LOAD_LH:
    case LOAD_LHU:
      alignmentReq = 2;
      break;
    case LOAD_LW:
      alignmentReq = 4;
      break;
    default:
      break;
    }
    if (addr % alignmentReq != 0) {
      trap("Alignement error on load", TRAP_INST);
      return;
    }
    // Preattempt virtual read
    VirtMemReadWitness readWit;
    auto [ok, in] = readVirtMemory(readWit, addr / BYTES_PER_WORD);
    if (!ok) {
      trap("VM error on read", TRAP_INST);
      return;
    }
    auto& wit = trace.makeInstLoad();
    wit.mem = readWit;
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    readReg(wit.rs1, dinst->rs1);
    wit.rs2 = dinst->rs2;
    wit.imm = dinst->imm;
    uint32_t shift = BITS_PER_BYTE * (addr % BYTES_PER_WORD);
    wit.options = opt;
    uint32_t out;
    switch (kind) {
    case LOAD_LB:
      out = uint32_t(int32_t(int8_t((in >> shift) & 0xff)));
      break;
    case LOAD_LH:
      out = uint32_t(int32_t(int16_t((in >> shift) & 0xfffff)));
      break;
    case LOAD_LW:
      out = in;
      break;
    case LOAD_LBU:
      out = (in >> shift) & 0xff;
      break;
    case LOAD_LHU:
      out = (in >> shift) & 0xffff;
      break;
    }
    writeReg(wit.rd, dinst->rd, out);
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{wit.rs1.value});
    DLOG("  IMM = " << HexWord{dinst->imm});
    DLOG("  RD = " << uint32_t(dinst->rd) << ", val = " << HexWord{out});
  }

  template <uint32_t opt> inline void do_INST_STORE() {
    constexpr Option optInner = Option(opt).popRet<InstKind>();
    auto kind = optInner.peek<StoreKind>();
    // Check alignement
    uint32_t peekAddr = peekReg(dinst->rs1) + dinst->imm;
    uint32_t alignmentReq = 1;
    switch (kind) {
    case STORE_SH:
      alignmentReq = 2;
      break;
    case STORE_SW:
      alignmentReq = 4;
      break;
    default:
      break;
    }
    if (peekAddr % alignmentReq != 0) {
      trap("Alignement error on store", TRAP_INST);
      return;
    }
    // Peek VM in advance + fault if needed
    auto [ok, in] = peekVirtMemory(peekAddr / BYTES_PER_WORD, ACCESS_STORE);
    if (!ok) {
      trap("VM error on read", TRAP_INST);
      return;
    }
    auto& wit = trace.makeInstStore();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t rs1Val = readReg(wit.rs1, dinst->rs1);
    uint32_t data = readReg(wit.rs2, dinst->rs2, dinst->rs1 == dinst->rs2);
    wit.rd = dinst->rd;
    wit.imm = dinst->imm;
    wit.options = opt;
    uint32_t addr = rs1Val + wit.imm;
    uint32_t shift = BITS_PER_BYTE * (addr % BYTES_PER_WORD);
    uint32_t out;
    switch (optInner.peek<StoreKind>()) {
    case STORE_SB:
      out = (in & ~(0xff << shift)) | ((data & 0xff) << shift);
      break;
    case STORE_SH:
      out = (in & ~(0xffff << shift)) | ((data & 0xffff) << shift);
      break;
    case STORE_SW:
      out = data;
      break;
    }
    if (!writeVirtMemory(wit.mem, addr / BYTES_PER_WORD, out)) {
      // THis should never occur
      fatal("Write failed");
    }
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{rs1Val});
    DLOG("  RS1 = " << uint32_t(dinst->rs2) << ", val = " << HexWord{data});
    DLOG("  IMM = " << HexWord{dinst->imm});
  }

  template <uint32_t opt> inline void do_INST_BRANCH() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto br = opts2.peek<BrKind>();
    constexpr Option opts3 = opts2.popRet<BrKind>();
    auto ok = opts3.peek<OutKind>();
    constexpr Option opts4 = opts3.popRet<OutKind>();
    auto& wit = trace.makeInstBranch();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t rs1Val = readReg(wit.rs1, dinst->rs1);
    uint32_t rs2Val = readReg(wit.rs2, dinst->rs2, dinst->rs1 == dinst->rs2);
    wit.rd = dinst->rd;
    wit.imm = dinst->imm;
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts4.val>(rs1Val, rs2Val);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t ret = (ok == OUT_0 ? unit->out0 : unit->out1);
    bool doBr = (br == BR_Z ? ret == 0 : ret != 0);
    wit.didBranch = doBr;
    if (doBr) {
      newPc = pc + wit.imm;
    }
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{rs1Val});
    DLOG("  RS2 = " << uint32_t(dinst->rs2) << ", val = " << HexWord{rs2Val});
    DLOG("  NEW PC = " << HexWord{newPc});
  }

  template <uint32_t opt> inline void do_INST_JAL() {
    auto& wit = trace.makeInstJal();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    wit.rs1 = dinst->rs1;
    wit.rs2 = dinst->rs2;
    writeReg(wit.rd, dinst->rd, newPc);
    wit.imm = dinst->imm;
    newPc = pc + wit.imm;
    DLOG("  RD = " << uint32_t(dinst->rd) << ", val = " << HexWord{wit.rd.value});
    DLOG("  PC = " << HexWord{pc});
  }

  template <uint32_t opt> inline void do_INST_JALR() {
    auto& wit = trace.makeInstJalr();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t rs1Val = readReg(wit.rs1, dinst->rs1);
    wit.rs2 = dinst->rs2;
    writeReg(wit.rd, dinst->rd, newPc);
    wit.imm = dinst->imm;
    newPc = rs1Val + wit.imm;
    DLOG("  RS1 = " << uint32_t(dinst->rs1) << ", val = " << HexWord{wit.rs1.value});
    DLOG("  RD = " << uint32_t(dinst->rd) << ", val = " << HexWord{wit.rd.value});
    DLOG("  PC = " << HexWord{pc});
  }

  template <uint32_t opt> inline void do_INST_LUI() {
    auto& wit = trace.makeInstLui();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    wit.rs1 = dinst->rs1;
    wit.rs2 = dinst->rs2;
    writeReg(wit.rd, dinst->rd, dinst->imm);
  }

  template <uint32_t opt> inline void do_INST_AUIPC() {
    auto& wit = trace.makeInstAuipc();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    wit.rs1 = dinst->rs1;
    wit.rs2 = dinst->rs2;
    writeReg(wit.rd, dinst->rd, pc + dinst->imm);
    wit.imm = dinst->imm;
  }

  template <uint32_t opt> inline void do_INST_ECALL() {
    if (mode != MODE_MACHINE) {
      trap("ECALL", TRAP_ECALL);
      return;
    }
    uint32_t which = peekReg(REG_A7);
    switch (which) {
    case HOST_ECALL_TERMINATE:
      do_ECALL_TERMINATE();
      break;
    case HOST_ECALL_READ:
      do_ECALL_READ();
      break;
    case HOST_ECALL_WRITE:
      do_ECALL_WRITE();
      break;
    case HOST_ECALL_POSEIDON2:
      do_ECALL_P2();
      break;
    case HOST_ECALL_BIGINT:
      do_ECALL_BIG_INT();
      break;
    default:
      LOG(0, "Invalid ECALL in machine mode: " << which);
      fatal("Invalid ECALL in machine mode");
    }
  }

  template <uint32_t opt> inline void do_INST_MRET() {
    if (mode != MODE_MACHINE) {
      trap("MRET not in machine mode", TRAP_INST);
      return;
    }
    auto& wit = trace.makeInstMret();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    uint32_t add = v2Compat ? 4 : 0;
    uint32_t mepcWord = v2Compat ? V2_COMPAT_MEPC : CSR_WORD(MEPC);
    newPc = readPhysMemory(wit.readPc, mepcWord) + add;
    uint32_t newMode = readPhysMemory(wit.readMode, CSR_WORD(MEMODE));
    writePhysMemory(wit.updateClearCache, CSR_WORD(MCLEARCACHE), 0);
    if (wit.updateClearCache.prevValue) {
      //LOG(0, "Clearing caches");
      instCache.clear();
      virtualMem.clear();
      iCacheCycle = curCycle;
    }
    writePhysMemory(wit.writeCycle, CSR_WORD(MSCYCLE), wit.cycle + 1);
    DLOG("  NEW PC = " << HexWord{newPc});
    if (peekPhysMemory(CSR_WORD(MDEBUG))) {
      debug = true;
    }
    setMode(newMode);
    countdown = peekPhysMemory(CSR_WORD(MCOUNTDOWN));
  }

  void do_ECALL_TERMINATE() {
    auto& wit = trace.makeEcallTerminate();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    readReg(wit.a7, REG_A7);
    readReg(wit.a0, REG_A0);
    readReg(wit.a1, REG_A1);
    for (size_t i = 0; i < 8; i++) {
      readPhysMemory(wit.output[i], OUTPUT_WORD + i);
    }
    done = true;
  }

  void do_ECALL_READ() {
    auto& wit = trace.makeEcallRead();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    readReg(wit.a7, REG_A7);
    uint32_t fd = peekReg(REG_A0);
    uint32_t buf = readReg(wit.a1, REG_A1);
    uint32_t len = readReg(wit.a2, REG_A2);
    if (len > 0xffff) {
      fatal("Invalid READ, too long");
    }
    // TODO: Based on read length, decide if we have enough room for read
    std::vector<uint8_t> hostData(len);
    uint32_t ret = io.onRead(fd, hostData.data(), len);
    if (ret > len) {
      throw std::runtime_error("Invalid host read");
    }
    writeReg(wit.a0, REG_A0, ret);
    curCycle++;
    uint32_t offset = 0;
    while (ret) {
      if (buf % 4 != 0 || ret < 4) {
        auto& bWit = trace.makeReadByte();
        bWit.cycle = curCycle;
        bWit.size = ret;
        bWit.lowBits = buf % 4;
        uint32_t data = peekPhysMemory(buf / 4);
        data &= ~(0xff << (buf % 4) * 8);
        data |= hostData[offset++] << (buf % 4) * 8;
        writePhysMemory(bWit.io, buf / 4, data);
        ret--;
        buf++;
        curCycle++;
      } else {
        auto& bWit = trace.makeReadWord();
        bWit.cycle = curCycle;
        bWit.size = ret;
        uint32_t data = 0;
        for (size_t i = 0; i < 4; i++) {
          data |= hostData[offset++] << (i * 8);
        }
        writePhysMemory(bWit.io, buf / 4, data);
        ret -= 4;
        buf += 4;
        curCycle++;
      }
    }
    wit.finalCycle = curCycle;
  }

  void do_ECALL_WRITE() {
    auto& wit = trace.makeEcallWrite();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    readReg(wit.a7, REG_A7);
    uint32_t fd = peekReg(REG_A0);
    uint32_t buf = peekReg(REG_A1);
    uint32_t len = readReg(wit.a2, REG_A2);
    if (len > 0xffff) {
      fatal("Invalid WRITE, too long");
    }
    std::vector<uint8_t> hostData(len);
    for (size_t i = 0; i < len; i++) {
      hostData[i] = peekPhysByte(buf + i);
    }
    uint32_t ret = io.onWrite(fd, hostData.data(), len);
    if (ret > len) {
      throw std::runtime_error("Invalid host write");
    }
    writeReg(wit.a0, REG_A0, ret);
  }

  void do_ECALL_P2() {
    auto& wit = trace.makeEcallP2();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    readReg(wit.a0, REG_A0);
    readReg(wit.a1, REG_A1);
    readReg(wit.a2, REG_A2);
    readReg(wit.a3, REG_A3);
    readReg(wit.a7, REG_A7);
    uint32_t stateInWordAddr = wit.a0.value ? wit.a0.value / 4 : P2_ZEROS_WORD;
    uint32_t stateOutWordAddr = wit.a0.value ? wit.a0.value / 4 : P2_TRASH_WORD;
    Digest state;
    for (size_t i = 0; i < CELLS_DIGEST; i++) {
      state.words[i] = Fp(readPhysMemory(wit.stateIn[i], stateInWordAddr + i)).asRaw();
    }
    curCycle++;
    P2State p2;
    p2.cycle = curCycle;
    p2.count = wit.a3.value & 0xffff;
    p2.inWordAddr = wit.a1.value / 4;
    p2.outWordAddr = wit.a2.value / 4;
    p2.isElem = (wit.a3.value & PFLAG_IS_ELEM) != 0;
    p2.isCheck = (wit.a3.value & PFLAG_CHECK_OUT) != 0;
    while (p2.count > 0) {
      auto& p2Wit = trace.makeP2Step();
      p2Wit.state = p2;
      std::array<Fp, CELLS_RATE> in;
      for (size_t i = 0; i < CELLS_DIGEST; i++) {
        uint32_t i2 = CELLS_DIGEST + i;
        p2Wit.stateIn[i] = Fp::fromRaw(state.words[i]).asUInt32();
        if (p2.isElem) {
          in[i] = readPhysMemory(p2Wit.dataIn[i], p2.inWordAddr + i);
          in[i2] = readPhysMemory(p2Wit.dataIn[i2], p2.inWordAddr + i2);
        } else {
          uint32_t word = readPhysMemory(p2Wit.dataIn[i], p2.inWordAddr + i);
          readPhysMemory(p2Wit.dataIn[i2], P2_ZEROS_WORD + i);
          in[2 * i] = word & 0xffff;
          in[2 * i + 1] = word >> 16;
        }
      }
      Digest out = memory.getP2().doBlock(*reinterpret_cast<Digest*>(&state), in, true);
      state = memory.getP2().doBlock(*reinterpret_cast<Digest*>(&state), in, false);
      uint32_t outAddr = (p2.count != 1) ? P2_TRASH_WORD : p2.outWordAddr;
      for (size_t i = 0; i < CELLS_DIGEST; i++) {
        p2Wit.stateOut[i] = Fp::fromRaw(state.words[i]).asUInt32();
        writePhysMemory(p2Wit.dataOut[i], outAddr + i, Fp::fromRaw(out.words[i]).asUInt32());
        if (p2.isCheck && p2.count == 1) {
          if (p2Wit.dataOut[i].prevValue != p2Wit.dataOut[i].value) {
            DLOG("Mismatch on check");
            throw std::runtime_error("BAD");
          }
        }
      }
      if (p2.isElem) {
        p2.inWordAddr += 16;
      } else {
        p2.inWordAddr += 8;
      }
      curCycle++;
      p2.cycle = curCycle;
      p2.count--;
    }
    for (size_t i = 0; i < CELLS_DIGEST; i++) {
      writePhysMemory(
          wit.stateOut[i], stateOutWordAddr + i, Fp::fromRaw(state.words[i]).asUInt32());
    }
  }

  void do_ECALL_BIG_INT() {
    std::map<uint32_t, uint32_t> polyWitness;
    size_t count = witgenBigInt(polyWitness, [&](uint32_t addr) { return peekPhysMemory(addr); });
    LOG(1, "BIGINT ecall with count = " << count);
    // TODO: Based on count + polyWitness paging, decide if we need to abort
    auto& wit = trace.makeEcallBigInt();
    wit.cycle = curCycle;
    wit.fetch = dinst->fetch;
    wit.count = count;
    readReg(wit.a7, REG_A7);
    uint32_t biMm = readReg(wit.t0, REG_T0);
    uint32_t biPcWord = readReg(wit.t2, REG_T2) / 4;
    curCycle++;
    BigIntPreflight pf;
    for (size_t i = 0; i < count; i++) {
      auto& biWit = trace.makeBigInt();
      biWit.cycle = curCycle;
      biWit.mm = biMm;
      uint32_t inst = readPhysMemory(biWit.inst, biPcWord++);
      auto decoded = BigIntInstruction::decode(inst);
      uint32_t base =
          readPhysMemory(biWit.baseReg, (biMm ? MACHINE_REGS_WORD : USER_REGS_WORD) + decoded.reg);
      uint32_t addr = base / 4 + decoded.offset * 4;
      switch (decoded.memOp) {
      case 0: { // read
        for (size_t i = 0; i < 4; i++) {
          PhysMemReadWitness mw;
          biWit.data[i] = readPhysMemory(mw, addr + i);
          biWit.prevCycle[i] = mw.prevCycle;
          biWit.prevValue[i] = mw.value;
        }
      } break;
      case 1: { // write
        for (size_t i = 0; i < 4; i++) {
          PhysMemWriteWitness mw;
          writePhysMemory(mw, addr + i, polyWitness[addr + i]);
          biWit.data[i] = mw.value;
          biWit.prevCycle[i] = mw.prevCycle;
          biWit.prevValue[i] = mw.prevValue;
        }
      } break;
      case 2: { // check
        for (size_t i = 0; i < 4; i++) {
          biWit.data[i] = 0;
          biWit.prevCycle[i] = 0;
          biWit.prevValue[i] = 0;
        }
      } break;
      }
      pf.step(decoded, biWit.data);
      curCycle++;
    }
  }

  bool fetchAndDecode(DecodeWitness* wit) {
    // We always read the memory address at pc/4
    auto [ok, l0] = fetchVirtMemory(wit->load0, pc / 4);
    if (!ok) { return false; }
    // If pc == 2 (mod 4), shift to lower value
    uint32_t inst = (pc % 4 == 2) ? l0 >> 16 : l0;
    bool compressed = false;
    uint32_t longInst;
    // Check if low bits are 11 (normal) or anything else (compressed)
    if ((inst & 3) == 3) {
      // if needed, add in second half to inst
      if (pc % 4 == 2) {
        // For unaligned addresses, always read next address
        auto [ok2, l1] = fetchVirtMemory(wit->load1, pc / 4 + 1);
        if (!ok2) {
          undoVirtMemory(wit->load0);
          return false;
        }
        inst |= l1 << 16;
      } else {
        // For aligned addresses, read from a `null` word (and ignore the value)
        uint32_t curMode = mode;
        mode = MODE_MACHINE;
        // Cannot fail
        readVirtMemory(wit->load1, COMPRESSED_INST_LOOKUP_WORD);
        mode = curMode;
      }
      longInst = inst;
    } else {
      // Remove any high bits, and then do a lookup to convert
      inst &= 0xffff;
      compressed = true;
      uint32_t curMode = mode;
      mode = MODE_MACHINE;
      // Cannot fail
      auto [ok2, inst2] = readVirtMemory(wit->load1, COMPRESSED_INST_LOOKUP_WORD + inst);
      mode = curMode;
      longInst = inst2;
    }
    wit->fetch.iCacheCycle = iCacheCycle;
    wit->fetch.loadCycle = curCycle;
    wit->fetch.mode = mode;
    wit->fetch.pc = pc;
    wit->fetch.nextPc = pc + (compressed ? 2 : 4);
    wit->inst = inst;
    wit->count = 1;
    auto decoded = DecodedInst(longInst);
    wit->opcode = uint32_t(getOpcode(decoded));
    wit->rd = decoded.rd;
    wit->rs1 = decoded.rs1;
    wit->rs2 = decoded.rs2;
    switch (Opcode(wit->opcode)) {
#define ENTRY(name, idx, opcode, immType, ...)                                                     \
  case Opcode::name:                                                                               \
    wit->imm = decoded.imm##immType();                                                             \
    break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
    default:
      wit->imm = 0;
    }
    return true;
  }

  void makeNoDecodeTrap(uint32_t trapType) {
    DecodeWitness*& decodeWit = instCache[{MACHINE_REGS_ADDR,  mode}];
    if (!decodeWit) {
      decodeWit = &trace.makeDecode();
      uint32_t oldMode = mode;
      mode = MODE_MACHINE;
      fetchAndDecode(decodeWit);
      mode = oldMode;
    }
    dinst = decodeWit;
    trap("No decode trap", trapType);
    curCycle++;
    pc = newPc;
  }

  bool run(size_t rowCount) {
    doResume();
    while (!done && trace.getRowCount() +
                            ceilDiv(curCycle, 24) + // How many rows we need for cycle table
                            memory.getPagingCost() <
                        rowCount) {
      if (mode != MODE_MACHINE) {
        if (countdown == 0) {
          makeNoDecodeTrap(TRAP_INTER);
          continue;
        }
        countdown--;
      }
      DecodeWitness*& decodeWit = instCache[{pc, mode}];
      if (!decodeWit) {
        DecodeWitness maybeSave;
        if (!fetchAndDecode(&maybeSave)) {
          makeNoDecodeTrap(TRAP_FETCH);
          continue;
        }
        decodeWit = &trace.makeDecode();
        *decodeWit = maybeSave;
      } else {
        decodeWit->count++;
      }
      dinst = decodeWit;
      newPc = dinst->fetch.nextPc;
      DLOG("cycle: " << curCycle << ", pc: " << HexWord{pc} << ", mode: " << mode
                     << ", inst: " << getOpcodeName(Opcode(dinst->opcode)));

      switch (Opcode(decodeWit->opcode)) {
#define ENTRY(name, idx, opcode, immType, func3, func7, itype, ...)                                \
  case Opcode::name:                                                                               \
    do_##itype<EncodeOptions(itype, ##__VA_ARGS__).val>();                                         \
    break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
      case Opcode::ANY:
        trap("INVALID INSTRUCTION", TRAP_INST);
      }
      curCycle++;
      pc = newPc;
    }
    if (!done) {
      doSuspend();
    }
    trace.getGlobals().finalCycle = curCycle;
    size_t cycleCount = ceilDiv(curCycle * 2, 16) * 16;
    for (size_t i = 0; i < cycleCount; i += 16) {
      auto& makeTable = trace.makeMakeTable();
      makeTable.table = 2;
      makeTable.start = i;
    }

    return done;
  }

  void addTables() {
    for (size_t i = 0; i < 256; i += 16) {
      auto& makeTable = trace.makeMakeTable();
      makeTable.table = 0;
      makeTable.start = i;
    }
    for (size_t i = 0; i < 65536; i += 16) {
      auto& makeTable = trace.makeMakeTable();
      makeTable.table = 1;
      makeTable.start = i;
    }
  }

  void commit() { memory.commit(pages); }

  // The trace
  Trace& trace;

  // The memory image + paging info
  PagedMemory memory;

  // IO with host
  HostIO& io;

  ankerl::unordered_dense::map<uint32_t, uint32_t> virtualMem;
  std::vector<PageDetails*> pages;
  PageDetails* regPage;
  ankerl::unordered_dense::map<std::pair<uint32_t, uint32_t>, DecodeWitness*> instCache;

  // Machine state
  bool v2Compat = true;
  bool done = false;
  uint32_t regOffset = 0;
  uint32_t curCycle = 1;
  uint32_t iCacheCycle = 1;
  uint32_t mode = 0;
  uint32_t pc = 0;
  uint32_t newPc = 0;
  uint32_t countdown = 0x7fffffff;;
  DecodeWitness* dinst;
  bool debug = false;
};

} // namespace

bool emulate(Trace& trace, MemoryImage& image, HostIO& io, size_t rowCount) {
  if (pcFile == nullptr) {
    pcFile = fopen("/tmp/pcdata", "rb");
  }
  Emulator emu(trace, image, io, rowCount);
  emu.addTables();
  bool done = emu.run(rowCount);
  LOG(1, "Cycle = " << emu.curCycle);
  emu.commit();
  return done;
}

} // namespace risc0::rv32im
