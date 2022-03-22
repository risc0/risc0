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

#include "risc0/zkp/verify/verify.h"
#include "risc0/core/log.h"
#include "risc0/zkp/circuit/constants.h"
#include "risc0/zkp/core/poly.h"
#include "risc0/zkp/core/rou.h"
#include "risc0/zkp/verify/fri.h"
#include "risc0/zkp/verify/merkle.h"
#include "risc0/zkp/verify/read_iop.h"
#include "risc0/zkp/verify/riscv.h"

namespace risc0 {

// NOLINTNEXTLINE(readability-function-size)
void verify(const VerifyCircuit& circuit,
            const CodeID& code,
            const uint32_t* proofData,
            size_t proofSize) {
  TapSetRef tapSet = circuit.tapSet;
  // Construct the IOP object
  ReadIOP iop(proofData, proofSize);

  // Read the low registers + write to globals
  Fp globals[kGlobalSize];
  for (size_t i = 0; i < kOutputRegs; i++) {
    uint32_t reg;
    iop.read(&reg, 1);
    globals[2 * i] = reg & 0xffff;
    globals[2 * i + 1] = reg >> 16;
  }

  // Get the size
  uint32_t po2;
  iop.read(&po2, 1);
  size_t size = size_t(1) << po2;
  size_t domain = size * kInvRate;
  LOG(1, "size = " << size);

  // Read the code + data merkle roots
  MerkleTreeVerifier codeMerkle(iop, domain, kCodeSize, kQueries);
  LOG(1, "codeRoot = " << codeMerkle.getRoot());
  MerkleTreeVerifier dataMerkle(iop, domain, kDataSize, kQueries);
  LOG(1, "dataRoot = " << dataMerkle.getRoot());

  // Verify the code is what we expect
  size_t whichCode = po2 - log2Ceil(kMinCycles);
  REQUIRE(code[whichCode] == codeMerkle.getRoot());

  // Fill in accum mix
  for (size_t i = 0; i < kAccumMixGlobalSize; i++) {
    globals[kAccumMixGlobalOffset + i] = Fp::random(iop);
  }

  MerkleTreeVerifier accumMerkle(iop, domain, kAccumSize, kQueries);
  LOG(1, "accumRoot = " << accumMerkle.getRoot());

  // Set the poly mix value
  Fp4 polyMix = Fp4::random(iop);

  MerkleTreeVerifier checkMerkle(iop, domain, kCheckSize, kQueries);
  LOG(1, "checkRoot = " << checkMerkle.getRoot());

  Fp4 Z = Fp4::random(iop);

#ifdef CIRCUIT_DEBUG
  iop.read(&Z, 1);
#endif
  LOG(1, "Z = " << Z);
  Fp backOne = kRouRev[po2];

  // Read the U coeffs, and define the tap variables
  size_t numTaps = tapSet.tapsSize();
  std::vector<Fp4> coeffU(numTaps + 16);
  iop.read(coeffU.data(), coeffU.size());
  auto hashU = shaHash(reinterpret_cast<const Fp*>(coeffU.data()), coeffU.size() * 4);
  iop.commit(hashU);

  // Now, convert to evaluated values
  size_t curPos = 0;
  std::vector<Fp4> evalU;
  for (auto reg : tapSet.regs()) {
    for (size_t i = 0; i < reg.size(); i++) {
      auto x = pow(backOne, reg[i]) * Z;
      auto fx = polyEval(coeffU.data() + curPos, reg.size(), x);
      evalU.push_back(fx);
    }
    curPos += reg.size();
  }

  Fp4 result = circuit.poly(evalU.data(), globals, polyMix);
  LOG(1, "Result = " << result);

  // Now generate the check polynomial
  Fp4 check;
  size_t remap[4] = {0, 2, 1, 3};
  for (size_t i = 0; i < 4; i++) {
    size_t rmi = remap[i];
    check += coeffU[numTaps + rmi + 0] * pow(Z, i) * Fp4(1, 0, 0, 0);
    check += coeffU[numTaps + rmi + 4] * pow(Z, i) * Fp4(0, 1, 0, 0);
    check += coeffU[numTaps + rmi + 8] * pow(Z, i) * Fp4(0, 0, 1, 0);
    check += coeffU[numTaps + rmi + 12] * pow(Z, i) * Fp4(0, 0, 0, 1);
  }
  check *= (pow(3 * Z, size) - Fp4(Fp(1)));
  LOG(1, "Check = " << check);

  // Make sure they match
  REQUIRE(check == result);

  // Set the mix mix value
  Fp4 mix = Fp4::random(iop);
  LOG(1, "mix = " << mix);

  // Make the mixed U polynomials
  std::vector<std::vector<Fp4>> comboU(tapSet.combosSize());
  for (size_t i = 0; i < tapSet.combosSize(); i++) {
    comboU[i].resize(tapSet.getCombo(i).size());
  }
  Fp4 curMix(1);
  curPos = 0;
  for (auto reg : tapSet.regs()) {
    for (size_t i = 0; i < reg.size(); i++) {
      comboU[reg.comboID()][i] += curMix * coeffU[curPos + i];
    }
    curMix *= mix;
    curPos += reg.size();
  }
  // Handle check group
  comboU.emplace_back();
  comboU.back().emplace_back();
  for (size_t i = 0; i < kCheckSize; i++) {
    comboU.back()[0] += curMix * coeffU[curPos++];
    curMix *= mix;
  }

  // Finally, do a FRI verification
  LOG(1, "FRI-verify, size = " << size);
  friVerify(iop, size, [&](ReadIOP& iop, size_t idx) {
    auto x = pow(kRouFwd[log2Ceil(domain)], idx);
    std::vector<std::vector<Fp>> rows(kNumRegisterGroups);
    rows[static_cast<int>(RegisterGroup::CODE)] = codeMerkle.verify(iop, idx);
    rows[static_cast<int>(RegisterGroup::DATA)] = dataMerkle.verify(iop, idx);
    rows[static_cast<int>(RegisterGroup::ACCUM)] = accumMerkle.verify(iop, idx);
    auto checkRow = checkMerkle.verify(iop, idx);
    Fp4 cur = Fp4(1);
    Fp4 tot[kComboCount + 1];
    for (auto reg : tapSet.regs()) {
      tot[reg.comboID()] += cur * rows[static_cast<int>(reg.group())][reg.offset()];
      cur *= mix;
    }
    for (size_t i = 0; i < kCheckSize; i++) {
      tot[kComboCount] += cur * checkRow[i];
      cur *= mix;
    }
    Fp4 ret;
    for (size_t id = 0; id < tapSet.combosSize(); id++) {
      Fp4 num = tot[id] - polyEval(comboU[id].data(), comboU[id].size(), Fp4(x));
      Fp4 divisor(1);
      for (auto back : tapSet.getCombo(id)) {
        divisor *= (Fp4(x) - Z * pow(backOne, back));
      }
      ret += num * inv(divisor);
    }
    Fp4 checkNum = tot[kComboCount] - comboU[kComboCount][0];
    Fp4 checkDivisor = (Fp4(x) - pow(Z, 4));
    ret += checkNum * inv(checkDivisor);
    return ret;
  });
}

} // namespace risc0
