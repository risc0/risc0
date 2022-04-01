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

#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkvm/prove/step.h"

#include <array>
#include <cstdio>

namespace risc0 {

Fp StepContext::get(const Fp* buf, size_t offset, size_t back) { // NOLINT
  if (back > curStep) {
    return Fp::invalid();
    // throw std::runtime_error("Get of negative timestep");
  }
  LOG(3,
      "get offset=" << offset << ", back=" << back << " -> "
                    << buf[offset * numSteps + (curStep - back)]);
  return buf[offset * numSteps + (curStep - back)];
}

void StepContext::set(Fp* buf, size_t offset, Fp val) { // NOLINT
#ifdef CIRCUIT_DEBUG
  if (val == Fp::invalid()) {
    LOG(0, "Set of invalid value, offset = " << offset);
    throw std::runtime_error("Invalid set");
  }
  if (buf[offset * numSteps + curStep] != Fp::invalid() &&
      buf[offset * numSteps + curStep] != val) {
    LOG(0,
        "Resetting offset " << offset << " from " << buf[offset * numSteps + curStep] << " to "
                            << val);
    throw std::runtime_error("Overwriting value");
  }
#endif
  LOG(3, "set offset=" << offset << " <- " << val);
  buf[offset * numSteps + curStep] = val;
}

Fp StepContext::getDigits(const Fp* buf, size_t bits, size_t offset, size_t back, size_t size) {
  LOG(3,
      "getDigits, bits=" << bits << ", offset=" << offset << ", back=" << back
                         << ", size=" << size);
  uint64_t tot = 0;
  uint64_t mul = 1;
  for (size_t i = 0; i < size; i++) {
    tot += get(buf, offset + i, back).asUInt32() * mul;
    mul <<= bits;
  }
  Fp ret = tot % Fp::P;
  LOG(3, "  ret=" << ret);
  return ret;
}

Fp StepContext::setDigits(Fp* buf, size_t bits, size_t offset, size_t size, Fp val) {
  LOG(3,
      "setDigits, bits=" << bits << ", offset=" << offset << ", size=" << size << ", val=" << val);
  uint32_t cur = val.asUInt32();
  uint32_t mask = (1 << bits) - 1;
  for (size_t i = 0; i < size; i++) {
    set(buf, offset + i, cur & mask);
    cur >>= bits;
  }
  return cur;
}

Fp StepContext::getMux(const Fp* buf, size_t offset, size_t back, size_t size) {
  LOG(3, "getMux, offset=" << offset << ", back=" << back << ", size=" << size);
  uint64_t tot = 0;
  for (uint64_t i = 0; i < size; i++) {
    tot += get(buf, offset + i, back).asUInt32() * i;
  }
  return Fp(tot % Fp::P);
}

void StepContext::setMux(Fp* buf, size_t offset, size_t size, Fp val) {
  LOG(3, "setMux, offset=" << offset << ", size=" << size << ", val=" << val);
  for (uint32_t i = 0; i < size; i++) {
    if (val.asUInt32() == i) {
      set(buf, offset + i, 1);
    } else {
      set(buf, offset + i, 0);
    }
  }
}

void StepContext::memWrite(Fp cycle, Fp addr, Fp low, Fp high) {
  uint32_t data = low.asUInt32() | (high.asUInt32() << 16);
  bool doWrite = addr.asUInt32() < (1 << (kMemBits - 1));
  MemoryEvent evt = {addr.asUInt32(), cycle.asUInt32(), doWrite, data};
  mem.history.emplace(evt);
  mem.data[addr.asUInt32()] = data;
  io->onWrite(mem, cycle.asUInt32(), addr.asUInt32() * 4, data);
}

std::array<Fp, 2> StepContext::memRead(Fp cycle, Fp addr) {
  if (mem.data.find(addr.asUInt32()) == mem.data.end()) {
    mem.data[addr.asUInt32()] = io->onRead(mem, addr.asUInt32() * 4);
  }
  uint32_t data = mem.data[addr.asUInt32()];
  MemoryEvent evt = {addr.asUInt32(), cycle.asUInt32(), false, data};
  mem.history.emplace(evt);
  return {data & 0xffff, data >> 16};
}

std::array<Fp, 5> StepContext::memCheck() {
  if (mem.history.empty()) {
    throw std::runtime_error("memCheck on empty history");
  }
  MemoryEvent evt = *mem.history.begin();
  mem.history.erase(mem.history.begin());
  return {evt.cycle, evt.addr, evt.isWrite, evt.data & 0xffff, evt.data >> 16};
}

std::array<Fp, 4> StepContext::divide(Fp numerLow, Fp numerHigh, Fp denomLow, Fp denomHigh) {
  uint32_t numer = numerLow.asUInt32() | (numerHigh.asUInt32() << 16);
  uint32_t denom = denomLow.asUInt32() | (denomHigh.asUInt32() << 16);
  uint32_t quot;
  uint32_t rem;
  if (denom == 0) {
    quot = 0xffffffff;
    rem = numer;
  } else {
    quot = numer / denom;
    rem = numer % denom;
  }
  return {quot & 0xffff, quot >> 16, rem & 0xffff, rem >> 16};
}

void StepContext::requireDigits(Fp* buf, size_t bits, size_t offset, size_t size) {

  for (size_t i = 0; i < size; i++) {
#ifdef CIRCUIT_DEBUG
    if (get(buf, offset + i, 0) == Fp::invalid()) {
      set(buf, offset + i, Fp(0));
    }
#endif
    if (get(buf, offset + i, 0).asUInt32() >= (1 << bits)) {
      throw std::runtime_error("Invalid requireDigits\n");
    }
  }
}

void StepContext::requireMux(Fp* buf, size_t offset, size_t size, const char* msg) {
  size_t tot = 0;
  for (size_t i = 0; i < size; i++) {
#ifdef CIRCUIT_DEBUG
    if (get(buf, offset + i, 0) == Fp::invalid()) {
      set(buf, offset + i, Fp(0));
    }
#endif
    uint32_t val = get(buf, offset + i, 0).asUInt32();
    tot += val;
    if (val >= 2) {
      throw std::runtime_error(std::string("Invalid requireMux: " + std::string(msg)));
    }
  }
  if (tot != 1) {
    throw std::runtime_error(std::string("Invalid requireMux: ") + std::string(msg));
  }
}

void StepContext::requireZero(Fp val, const char* msg) {
  if (val != 0) {
    throw std::runtime_error(std::string("Invalid requireZero: ") + std::string(msg));
  }
}

static constexpr uint32_t kInit[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

static constexpr uint32_t kRound[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void setupCode(Fp* code,
               size_t numSteps,
               uint32_t startAddr,
               const std::map<uint32_t, uint32_t>& image) {
  size_t kCyclePos = 0;
  size_t kTypePos = kCyclePos + 1;
  size_t kShaPos = kTypePos + CodeCycleType::NUM_TYPES;
  size_t kP1Pos = kShaPos + ShaCycleType::NUM_TYPES;
  size_t kP2Pos = kP1Pos + 1;
  size_t kDataPos = kP2Pos + 1;
  size_t kData2Pos = kDataPos + 2;
  if (image.size() + 3 /* INIT/RESET/FINI*/ + kZkCycles > numSteps) {
    throw std::runtime_error("Unable to generate code");
  }
  for (uint32_t i = 0; i < numSteps; i++) {
    code[i] = i;
  }
  code[(kTypePos + CodeCycleType::INIT) * numSteps] = 1;
  uint32_t cycle = 1;
  for (const auto& kvp : image) {
    code[(kTypePos + CodeCycleType::MEM_WRITE) * numSteps + cycle] = 1;
    code[kP1Pos * numSteps + cycle] = kvp.first / 4;
    code[kP2Pos * numSteps + cycle] = (kvp.first / 4) >= (1 << (kMemBits - 1));
    code[(kDataPos + 0) * numSteps + cycle] = kvp.second & 0xffff;
    code[(kDataPos + 1) * numSteps + cycle] = kvp.second >> 16;
    cycle++;
  }
  code[(kTypePos + CodeCycleType::RESET) * numSteps + cycle] = 1;
  code[kP1Pos * numSteps + cycle] = startAddr;
  cycle++;
  uint32_t base_cycle = cycle;
  for (; cycle + 1 + kZkCycles < numSteps; cycle++) {
    size_t inst_phase = (cycle - base_cycle) % 3;
    size_t sha_phase = (cycle - base_cycle) % 72;
    if (inst_phase == 2) {
      code[(kTypePos + CodeCycleType::FINAL) * numSteps + cycle] = 1;
    } else {
      code[(kTypePos + CodeCycleType::NORMAL) * numSteps + cycle] = 1;
    }
    if (sha_phase < 4) {
      code[(kShaPos + ShaCycleType::CONTROL) * numSteps + cycle] = 1;
      code[kP1Pos * numSteps + cycle] = sha_phase;
      code[kP2Pos * numSteps + cycle] = (sha_phase == 0);
      code[(kDataPos + 0) * numSteps + cycle] = kInit[3 - sha_phase] & 0xffff;
      code[(kDataPos + 1) * numSteps + cycle] = kInit[3 - sha_phase] >> 16;
      code[(kData2Pos + 0) * numSteps + cycle] = kInit[7 - sha_phase] & 0xffff;
      code[(kData2Pos + 1) * numSteps + cycle] = kInit[7 - sha_phase] >> 16;
    } else if (sha_phase < 20) {
      code[(kShaPos + ShaCycleType::LOAD) * numSteps + cycle] = 1;
      code[(kDataPos + 0) * numSteps + cycle] = kRound[sha_phase - 4] & 0xffff;
      code[(kDataPos + 1) * numSteps + cycle] = kRound[sha_phase - 4] >> 16;
    } else if (sha_phase < 68) {
      code[(kShaPos + ShaCycleType::MIX) * numSteps + cycle] = 1;
      code[kP1Pos * numSteps + cycle] = (sha_phase >= 64);
      code[kP2Pos * numSteps + cycle] = (sha_phase == 67);
      code[(kDataPos + 0) * numSteps + cycle] = kRound[sha_phase - 4] & 0xffff;
      code[(kDataPos + 1) * numSteps + cycle] = kRound[sha_phase - 4] >> 16;
    } else {
      code[kP1Pos * numSteps + cycle] = sha_phase - 68 + 4;
      code[(kShaPos + ShaCycleType::CONTROL) * numSteps + cycle] = 1;
    }
  }
  code[(kTypePos + CodeCycleType::FINI) * numSteps + cycle] = 1;
}

} // namespace risc0
