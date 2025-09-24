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

namespace {

#define DLOG(...) LOG(2, __VA_ARGS__)
//#define DLOG(...) /**/

struct Emulator {
  Emulator(Trace& trace, MemoryImage& image, HostIO& io, size_t rowCount)
      : trace(trace)
      , memory(trace, image)
      , io(io)
      , pages(MEMORY_SIZE_PAGES)
      , regPage(memory.pageIn(MACHINE_REGS_WORD >> 8))
  {
    pages[MACHINE_REGS_WORD >> 8] = regPage;
  }

  static constexpr uint32_t regPageAddr = MACHINE_REGS_WORD & 0xffffff00;

  inline uint32_t peekMemory(uint32_t wordAddr) {
    PageDetails* page = pages[wordAddr >> 8];
    if (!page) {
      page = memory.pageIn(wordAddr >> 8);
      pages[wordAddr >> 8] = page;
    }
    return (*page)[wordAddr & 0xff].value;
  }

  inline uint8_t peekByte(uint32_t addr) {
    uint32_t word = peekMemory(addr / 4);
    return word >> ((addr % 4) * 8);
  }

  inline uint32_t readMemory(MemReadWitness& record, uint32_t wordAddr) {
    PageDetails* page = pages[wordAddr>> 8];
    if (!page) {
      page = memory.pageIn(wordAddr >> 8);
      pages[wordAddr >> 8] = page;
    }
    uint32_t wordNum = wordAddr & 0xff;
    record.wordAddr = wordAddr;
    record.prevCycle = (*page)[wordNum].cycle;
    record.value = (*page)[wordNum].value;
    (*page)[wordNum].cycle = curCycle * 2;
    return record.value;
  }

  inline void writeMemory(MemWriteWitness& record, uint32_t wordAddr, uint32_t value) {
    PageDetails* page = pages[wordAddr >> 8];
    if (!page) {
      page = memory.pageIn(wordAddr >> 8);
      pages[wordAddr >> 8] = page;
    }
    uint32_t wordNum = wordAddr & 0xff;
    record.wordAddr = wordAddr;
    record.prevCycle = (*page)[wordNum].cycle;
    record.prevValue = (*page)[wordNum].value;
    (*page)[wordNum].value = value;
    (*page)[wordNum].cycle = curCycle * 2 + 1;
    record.value = value;
  }

  inline uint32_t readReg(MemReadWitness& record, uint32_t reg, bool sameReg = false) {
    uint32_t wordNum = regOffset + reg + (sameReg ? 64 : 0);
    record.wordAddr = regPageAddr + wordNum;
    record.prevCycle = (*regPage)[wordNum].cycle;
    record.value = (*regPage)[wordNum].value;
    (*regPage)[wordNum].cycle = curCycle * 2;
    return (sameReg ? (*regPage)[regOffset + reg].value : record.value);
  }

  inline void writeReg(MemWriteWitness& record, uint32_t reg, uint32_t value) {
    uint32_t wordNum = regOffset + reg + (reg == 0 ? 64 : 0);
    record.wordAddr = regPageAddr + wordNum;
    record.prevCycle = (*regPage)[wordNum].cycle;
    record.prevValue = (*regPage)[wordNum].value;
    (*regPage)[wordNum].value = value;
    (*regPage)[wordNum].cycle = curCycle * 2 + 1;
    record.value = value;
  }

#define UNIT_COMMON(name) \
    auto& unit = trace.makeUnit ## name(); \
    unit.count = 1; \
    unit.opts = opt; \
    unit.a = a; \
    unit.b = b; \
    [[maybe_unused]] constexpr Option optInner = Option(opt).popRet<UnitKind>()

  template<uint32_t opt>
  inline UnitBaseWitness* unitAddSub(uint32_t a, uint32_t b) {
    UNIT_COMMON(AddSub);
    switch(optInner.peek<AsKind>()) {
      case AS_ADD: unit.out0 = a + b; break;
      case AS_SUB: unit.out0 = a - b; break;
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template<uint32_t opt>
  inline UnitBaseWitness* unitBit(uint32_t a, uint32_t b) {
    UNIT_COMMON(Bit);
    switch(optInner.peek<BitKind>()) {
      case BIT_XOR: unit.out0 = a ^ b; break;
      case BIT_OR: unit.out0 = a | b; break;
      case BIT_AND: unit.out0 = a & b; break;
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template<uint32_t opt>
  inline UnitBaseWitness* unitLt(uint32_t a, uint32_t b) {
    UNIT_COMMON(Lt);
    unit.out0 = int32_t(a) < int32_t(b);
    unit.out1 = a < b;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template<uint32_t opt>
  inline UnitBaseWitness* unitMul(uint32_t a, uint32_t b) {
    UNIT_COMMON(Mul);
    uint64_t out;
    switch(optInner.peek<MulKind>()) {
      case MUL_SS: out = int64_t(int32_t(a)) * int64_t(int32_t(b)); break;
      case MUL_SU: out = int64_t(int32_t(a)) * uint64_t(b); break;
      case MUL_UU: out = uint64_t(a) * uint64_t(b); break;
    }
    unit.out0 = uint32_t(out); \
    unit.out1 = out >> 32; \
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template<uint32_t opt>
  inline UnitBaseWitness* unitDiv(uint32_t a, uint32_t b) {
    UNIT_COMMON(Div);
    if (optInner.peek<DivKind>() == DIV_S) {
      // Intel processors actually fault if you do a signed division on MIN_INT by 1/-1
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

  template<uint32_t opt>
  inline UnitBaseWitness* unitShift(uint32_t a, uint32_t b) {
    UNIT_COMMON(Shift);
    uint32_t po2 = (1 << (b & 0x1f));
    if (optInner.peek<ShiftKind>() == SHIFT_LL) {
      unitMul<EncodeOptions(UNIT_MUL, MUL_UU).val>(a, po2);
      unit.out0 = (a << (b & 0x1f));
    } else {
      bool neg = optInner.peek<ShiftKind>() == SHIFT_RA && (a & 0x80000000) != 0;
      if (neg) { a = ~a; }
      unitDiv<EncodeOptions(UNIT_DIV, DIV_U).val>(a, po2);
      unit.out0 = a >> (b & 0x1f);
      if (neg) { unit.out0 = ~unit.out0; }
    }
    unit.out1 = 0;
    return reinterpret_cast<UnitBaseWitness*>(&unit);
  }

  template<uint32_t opt>
  inline UnitBaseWitness* doUnit(uint32_t a, uint32_t b) {
    switch(Option(opt).peek<UnitKind>()) {
      case UNIT_ADDSUB: return unitAddSub<opt>(a, b);
      case UNIT_BIT: return unitBit<opt>(a, b);
      case UNIT_LT: return unitLt<opt>(a, b);
      case UNIT_MUL: return unitMul<opt>(a, b);
      case UNIT_DIV: return unitDiv<opt>(a, b);
      case UNIT_SHIFT: return unitShift<opt>(a, b);
    }
  }

  void doResume() {
    auto& resumeWit = trace.makeInstResume();
    pc = readMemory(resumeWit.pc, SUSPEND_PC_WORD);
    mm = readMemory(resumeWit.mm, SUSPEND_MODE_WORD);
    regOffset = (mm ? (MACHINE_REGS_WORD & 0xff) : (USER_REGS_WORD & 0xff));
    curCycle++;
  }

  void doSuspend() {
    auto& suspendWit = trace.makeInstSuspend();
    suspendWit.cycle = curCycle;
    suspendWit.iCacheCycle = iCacheCycle;
    writeMemory(suspendWit.pc, SUSPEND_PC_WORD, pc);
    writeMemory(suspendWit.mm, SUSPEND_MODE_WORD, mm);
    curCycle++;
  }

  void trap(const std::string& reason) {
    // TODO: Properly implement trap handling
    throw std::runtime_error("Trap: " + reason);
  }

  template<uint32_t opt>
  inline void do_INST_REG() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto ok = opts2.peek<OutKind>();
    constexpr Option opts3 = opts2.popRet<OutKind>();
    auto& wit = trace.makeInstReg();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val = readReg(wit.rs1, decoded.rs1);
    uint32_t rs2Val = readReg(wit.rs2, decoded.rs2, decoded.rs1 == decoded.rs2);
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts3.val>(rs1Val, rs2Val);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t rdVal = (ok == OUT_0 ? unit->out0 : unit->out1);
    writeReg(wit.rd, decoded.rd, rdVal);
    DLOG("  rs1Val = " << rs1Val << ", rs2Val = " << rs2Val);
    DLOG("  rdVal = " << rdVal);
  }

  template<uint32_t opt>
  inline void do_INST_IMM() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto ok = opts2.peek<OutKind>();
    constexpr Option opts3 = opts2.popRet<OutKind>();
    auto& wit = trace.makeInstImm();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val = readReg(wit.rs1, decoded.rs1);
    wit.rs2 = decoded.rs2;
    wit.imm = opts3.is(UNIT_SHIFT) ? decoded.immIL() : decoded.immI();
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts3.val>(rs1Val, wit.imm);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t rdVal = (ok == OUT_0 ? unit->out0 : unit->out1);
    writeReg(wit.rd, decoded.rd, rdVal);
    DLOG("  rs1Val = " << rs1Val << ", imm = " << wit.imm);
    DLOG("  rdVal = " << rdVal);
  }

  template<uint32_t opt>
  inline void do_INST_LOAD() {
    auto& wit = trace.makeInstLoad();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val = readReg(wit.rs1, decoded.rs1);
    wit.rs2 = decoded.rs2;
    wit.imm = decoded.immI();
    uint32_t addr = rs1Val + wit.imm;
    uint32_t shift = 8 * (addr % 4);
    uint32_t in = readMemory(wit.mem, addr/4);
    wit.options = opt;
    constexpr Option optInner = Option(opt).popRet<InstKind>();
    uint32_t out;
    switch(optInner.peek<LoadKind>()) {
      case LOAD_LB:
        out = uint32_t(int32_t(int8_t((in >> shift) & 0xff)));
        break;
      case LOAD_LH:
        if (shift % 16 != 0) { trap("Alignment error"); }
        out = uint32_t(int32_t(int16_t((in >> shift) & 0xfffff)));
        break;
      case LOAD_LW:
        if (shift != 0) { trap("Alignment error"); }
        out = in;
        break;
      case LOAD_LBU:
        out = (in >> shift) & 0xff;
        break;
      case LOAD_LHU:
        if (shift % 16 != 0) { trap("Alignment error"); }
        out = (in >> shift) & 0xffff;
        break;
    }
    writeReg(wit.rd, decoded.rd, out);
    DLOG("  RS1 = " << decoded.rs1 << ", value = " << std::hex << wit.rs1.value << std::dec);
    DLOG("  IMM = " << std::hex << wit.imm << std::dec);
    DLOG("  RD = " << decoded.rd << ", value = " << std::hex << wit.rd.value << std::dec);
  }

  template<uint32_t opt>
  inline void do_INST_STORE() {
    auto& wit = trace.makeInstStore();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val = readReg(wit.rs1, decoded.rs1);
    uint32_t data = readReg(wit.rs2, decoded.rs2, decoded.rs1 == decoded.rs2);
    wit.rd = decoded.rd;
    wit.imm = decoded.immS();
    wit.options = opt;
    constexpr Option optInner = Option(opt).popRet<InstKind>();
    uint32_t addr = rs1Val + wit.imm;
    uint32_t shift = 8 * (addr % 4);
    uint32_t in = peekMemory(addr/4);
    uint32_t out;
    switch(optInner.peek<StoreKind>()) {
      case STORE_SB:
        out = (in & ~(0xff << shift)) | ((data & 0xff)  << shift);
        break;
      case STORE_SH:
        if (shift % 16 != 0) { trap("Alignment error"); }
        out = (in & ~(0xffff << shift)) | ((data & 0xffff)  << shift);
        break;
      case STORE_SW:
        if (shift != 0) { trap("Alignment error"); }
        out = data;
        break;
    }
    writeMemory(wit.mem, addr/4, out);
    DLOG("  RS1 = " << decoded.rs1 << ", value = " << std::hex << wit.rs1.value << std::dec);
    DLOG("  RS2 = " << decoded.rs2 << ", value = " << std::hex << wit.rs2.value << std::dec);
    DLOG("  IMM = " << std::hex << wit.imm << std::dec);
    DLOG("  MEM addr = " << std::hex << addr << ", value = " << out << std::dec);
}

  template<uint32_t opt>
  inline void do_INST_BRANCH() {
    constexpr Option opts(opt);
    constexpr Option opts2 = opts.popRet<InstKind>();
    auto br = opts2.peek<BrKind>();
    constexpr Option opts3 = opts2.popRet<BrKind>();
    auto ok = opts3.peek<OutKind>();
    constexpr Option opts4 = opts3.popRet<OutKind>();
    auto& wit = trace.makeInstBranch();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val = readReg(wit.rs1, decoded.rs1);
    uint32_t rs2Val = readReg(wit.rs2, decoded.rs2, decoded.rs1 == decoded.rs2);
    wit.rd = decoded.rd;
    wit.imm = decoded.immB();
    wit.options = opt;
    UnitBaseWitness* unit = doUnit<opts4.val>(rs1Val, rs2Val);
    wit.out0 = unit->out0;
    wit.out1 = unit->out1;
    uint32_t ret = (ok == OUT_0 ? unit->out0 : unit->out1);
    bool doBr = (br == BR_Z ? ret == 0 : ret != 0);
    wit.didBranch = doBr;
    if (doBr) { newPc = pc + wit.imm; }
    DLOG("  rs1Val = " << rs1Val << ", rs2Val = " << rs2Val);
    DLOG("  PC = " << std::hex << pc << std::dec);
  }

  template<uint32_t opt>
  inline void do_INST_JAL() {
    auto& wit = trace.makeInstJal();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    wit.rs1 = decoded.rs1;
    wit.rs2 = decoded.rs2;
    writeReg(wit.rd, decoded.rd, newPc);
    wit.imm = decoded.immJ();
    newPc = pc + wit.imm;
    DLOG("  RD = " << decoded.rd << ", value = " << std::hex << wit.rd.value << std::dec);
    DLOG("  PC = " << std::hex << pc << std::dec);
  }

  template<uint32_t opt>
  inline void do_INST_JALR() {
    auto& wit = trace.makeInstJalr();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    uint32_t rs1Val= readReg(wit.rs1, decoded.rs1);
    wit.rs2 = decoded.rs2;
    writeReg(wit.rd, decoded.rd, newPc);
    wit.imm = decoded.immI();
    newPc = rs1Val + wit.imm;
    DLOG("  RS1 = " << decoded.rs1 << ", value = " << std::hex << wit.rs1.value << std::dec);
    DLOG("  RD = " << decoded.rd << ", value = " << std::hex << wit.rd.value << std::dec);
    DLOG("  PC = " << std::hex << pc << std::dec);
  }

  template<uint32_t opt>
  inline void do_INST_LUI() {
    auto& wit = trace.makeInstLui();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    wit.rs1 = decoded.rs1;
    wit.rs2 = decoded.rs2;
    writeReg(wit.rd, decoded.rd, decoded.immU());
  }

  template<uint32_t opt>
  inline void do_INST_AUIPC() {
    auto& wit = trace.makeInstAuipc();
    wit.cycle = curCycle;
    wit.mm = mm;
    wit.fetch = *curFetch;
    wit.rs1 = decoded.rs1;
    wit.rs2 = decoded.rs2;
    writeReg(wit.rd, decoded.rd, pc + decoded.immU());
    wit.imm = decoded.immU();
  }

  template<uint32_t opt>
  inline void do_INST_ECALL() {
    if (!mm) {
      // Save PC + jump to dispatch address
      auto& wit = trace.makeInstEcall();
      wit.cycle = curCycle;
      wit.fetch = *curFetch;
      writeMemory(wit.savePc, MEPC_WORD, newPc);
      mm = 1;
      pc = readMemory(wit.dispatch, ECALL_DISPATCH_WORD);
      return;
    }
    uint32_t which = peekMemory(MACHINE_REGS_WORD + REG_A7);
    switch(which) {
      case HOST_ECALL_TERMINATE:
        do_ECALL_TERMINATE();
        break;
      case HOST_ECALL_READ:
        do_ECALL_READ();
        break;
      case HOST_ECALL_WRITE:
        do_ECALL_WRITE();
        break;
      case HOST_ECALL_BIGINT:
        do_ECALL_BIG_INT();
        break;
      default:
        trap("Invalid ECALL in machine mode");
    }
  }

  void do_ECALL_TERMINATE() {
    auto& wit = trace.makeEcallTerminate();
    wit.cycle = curCycle;
    wit.fetch = *curFetch;
    readMemory(wit.a7, MACHINE_REGS_WORD + REG_A7);
    done = true;
  }

  void do_ECALL_READ() {
    auto& wit = trace.makeEcallRead();
    wit.cycle = curCycle;
    wit.fetch = *curFetch;
    readMemory(wit.a7, MACHINE_REGS_WORD + REG_A7);
    uint32_t fd = peekMemory(MACHINE_REGS_WORD + REG_A0);
    uint32_t buf = readMemory(wit.a1, MACHINE_REGS_WORD + REG_A1);
    uint32_t len = readMemory(wit.a2, MACHINE_REGS_WORD + REG_A2);
    if (len > 0xffff) {
      trap("Invalid READ, too long");
    }
    // TODO: Based on read length, decide if we have enough room for read
    std::vector<uint8_t> hostData(len);
    uint32_t ret = io.onRead(fd, hostData.data(), len);
    if (ret > len) {
      throw std::runtime_error("Invalid host read");
    }
    writeMemory(wit.a0, MACHINE_REGS_WORD + REG_A0, ret);
    curCycle++;
    uint32_t offset = 0;
    while (ret) {
      if (buf % 4 != 0 || ret < 4) {
        auto& bWit = trace.makeReadByte();
        bWit.cycle = curCycle;
        bWit.size = ret;
        bWit.lowBits = buf % 4;
        uint32_t data = peekMemory(buf / 4);
        data &= ~(0xff << (buf % 4)*8);
        data |= hostData[offset++] << (buf%4)*8;
        writeMemory(bWit.io, buf / 4, data);
        ret--;
        buf++;
        curCycle++;
      } else {
        auto& bWit = trace.makeReadWord();
        bWit.cycle = curCycle;
        bWit.size = ret;
        uint32_t data = 0;
        for (size_t i=0; i < 4; i++) {
          data |= hostData[offset++] << (i*8);
        }
        writeMemory(bWit.io, buf / 4, data);
        ret-=4;
        buf+=4;
        curCycle++;
      }
    }
    wit.finalCycle = curCycle;
  }

  void do_ECALL_WRITE() {
    auto& wit = trace.makeEcallWrite();
    wit.cycle = curCycle;
    wit.fetch = *curFetch;
    readMemory(wit.a7, MACHINE_REGS_WORD + REG_A7);
    uint32_t fd = peekMemory(MACHINE_REGS_WORD + REG_A0);
    uint32_t buf = peekMemory(MACHINE_REGS_WORD + REG_A1);
    uint32_t len = readMemory(wit.a2, MACHINE_REGS_WORD + REG_A2);
    if (len > 0xffff) {
      trap("Invalid WRITE, too long");
    }
    std::vector<uint8_t> hostData(len);
    for (size_t i = 0; i < len; i++) {
      hostData[i] = peekByte(buf + i);
    }
    uint32_t ret = io.onWrite(fd, hostData.data(), len);
    if (ret > len) {
      throw std::runtime_error("Invalid host write");
    }
    writeMemory(wit.a0, MACHINE_REGS_WORD + REG_A0, ret);
  }

  void do_ECALL_BIG_INT() {
    std::map<uint32_t, uint32_t> polyWitness;
    size_t count = witgenBigInt(polyWitness, [&](uint32_t addr) { return peekMemory(addr); });
    // TODO: Based on count + polyWitness paging, decide if we need to abort
    auto& wit = trace.makeEcallBigInt();
    wit.cycle = curCycle;
    wit.fetch = *curFetch;
    wit.count = count;
    readMemory(wit.a7, MACHINE_REGS_WORD + REG_A7);
    uint32_t biMm = readMemory(wit.t0, MACHINE_REGS_WORD + REG_T0);
    uint32_t biPcWord = readMemory(wit.t2, MACHINE_REGS_WORD + REG_T2) / 4;
    curCycle++;
    BigIntPreflight pf;
    for (size_t i = 0; i < count; i++) {
      auto& biWit = trace.makeBigInt();
      biWit.cycle = curCycle;
      biWit.mm = biMm;
      uint32_t inst = readMemory(biWit.inst, biPcWord++);
      auto decoded = BigIntInstruction::decode(inst);
      uint32_t base = readMemory(biWit.baseReg, (biMm ? MACHINE_REGS_WORD : USER_REGS_WORD) + decoded.reg);
      uint32_t addr = base / 4 + decoded.offset * 4;
      switch (decoded.memOp) {
      case 0: { // read
        for (size_t i = 0; i < 4; i++) {
          MemReadWitness mw;
          biWit.data[i] = readMemory(mw, addr + i);
          biWit.prevCycle[i] = mw.prevCycle;
          biWit.prevValue[i] = mw.value;
        }
      } break;
      case 1: { // write
        for (size_t i = 0; i < 4; i++) {
          MemWriteWitness mw;
          writeMemory(mw, addr + i, polyWitness[addr+i]);
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

  void fetchAndDecode(DecodeWitness* wit) {
    // We always read the memory address at pc/4
    uint32_t l0 = readMemory(wit->load0, pc/4);
    // If pc == 2 (mod 4), shift to lower value
    uint32_t inst = (pc % 4 == 2) ? l0 >> 16 : l0;
    bool compressed = false;
    // Check is low bits are 11 (normal) or anything else (compressed)
    if ((inst & 3) == 3) {
      // For normal instructions, always read next address
      uint32_t l1 = readMemory(wit->load1, pc/4 + 1);
      // if needed, add in second half to inst
      if (pc % 4 == 2) {
        inst |= l1 << 16;
      }
    } else {
      // Remove any high bits, and then do a lookup to convert
      inst &= 0xffff;
      compressed = true;
      inst = readMemory(wit->load1, COMPRESSED_INST_LOOKUP_WORD + inst);
    }
    wit->fetch.iCacheCycle = iCacheCycle;
    wit->fetch.pc = pc;
    wit->fetch.nextPc = pc + (compressed ? 2 : 4);
    wit->loadCycle = curCycle;
    wit->inst = inst;
    wit->count = 1;
  }

  bool run(size_t rowCount) {
    doResume();
    while(!done &&
        trace.getRowCount() +
        ceilDiv(curCycle, 24) + // How many rows we need for cycle table
        memory.getPagingCost() < rowCount) {
      DecodeWitness*& decodeWit = iCache[pc];
      if (!decodeWit) {
        decodeWit = &trace.makeDecode();
        fetchAndDecode(decodeWit);
      } else {
        decodeWit->count++;
      }
      curFetch = &decodeWit->fetch;
      newPc = curFetch->nextPc;
      decoded = DecodedInst(decodeWit->inst);
      Opcode opcode = getOpcode(decoded);
      DLOG("cycle: " << curCycle << ", pc: " << std::hex << pc << std::dec << ", inst: " << getOpcodeName(opcode));
      switch(opcode) {
#define ENTRY(name, idx, opcode, immType, func3, func7, itype, ...) \
        case Opcode::name: do_ ## itype <EncodeOptions(itype, ## __VA_ARGS__).val>(); break;
#include "rv32im/base/rv32im.inc"
#undef ENTRY
        case Opcode::INVALID:
          trap("Invalid opcde");
          break;
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

  void commit() {
    memory.commit(pages);
  }

  // The trace
  Trace& trace;

  // The memory image + paging info
  PagedMemory memory;

  // IO with host
  HostIO& io;

  std::vector<PageDetails*> pages;
  PageDetails* regPage;

  // Machine state
  bool done = false;
  uint32_t regOffset = 0;
  uint32_t curCycle = 1;
  uint32_t iCacheCycle = 1;
  uint32_t mm = 0;
  uint32_t pc = 0;
  uint32_t newPc = 0;
  DecodedInst decoded;
  FetchWitness* curFetch;

  // Keep track of decoded instructions (and how many times each is used).
  // 'FetchKey' is (iCacheCyce, PC)
  ankerl::unordered_dense::map<uint32_t, DecodeWitness*> iCache;
};

} // namespace

bool emulate(Trace& trace, MemoryImage& image, HostIO& io, size_t rowCount) {
  Emulator emu(trace, image, io, rowCount);
  emu.addTables();
  bool done = emu.run(rowCount);
  LOG(0, "Cycle = " << emu.curCycle);
  emu.commit();
  return done;
}

} // namespace risc0;:rv32im
