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

#include "risc0/zkp/prove/prove.h"

#include "risc0/core/log.h"
#include "risc0/core/rng.h"
#include "risc0/zkp/core/constants.h"
#include "risc0/zkp/core/poly.h"
#include "risc0/zkp/core/rou.h"
#include "risc0/zkp/prove/fri.h"
#include "risc0/zkp/prove/poly_group.h"
#include "risc0/zkp/prove/write_iop.h"

namespace risc0 {

static AccelSlice<Fp> makeCoeffs(const std::vector<Fp>& vec, size_t count) {
  // Copy into accel buffer
  auto ret = AccelSlice<Fp>::copy(vec);

  // Do interpolate
  batchInterpolateNTT(ret, count);

  // Convert f(x) -> f(3x), which effective multiplies cofficent c_i by 3^i.
#ifndef CIRCUIT_DEBUG
  zkShiftAccel(ret, count);
#endif
  return ret;
}

void runWithoutSeal(ProveCircuit& circuit) {
  WriteIOP iop;
  circuit.execute(iop);
}

// NOLINTNEXTLINE(readability-function-size)
std::vector<uint32_t> prove(ProveCircuit& circuit) {
  // Get taps
  TapSetRef tapSet = circuit.getTaps();
  // Setup output IOP
  WriteIOP iop;

  // Do main execution + get size
  circuit.execute(iop);
  uint32_t po2 = circuit.getPo2();
  REQUIRE(po2 <= kMaxCyclesPo2);
  size_t size = size_t(1) << po2;

  // Get sizes
  size_t codeSize = tapSet.groupSize(RegisterGroup::CODE);
  size_t dataSize = tapSet.groupSize(RegisterGroup::DATA);
  size_t accumSize = tapSet.groupSize(RegisterGroup::ACCUM);
  size_t comboCount = tapSet.combosSize();

  // Make code + data PolyGroups + commit a Merkle root for each
  PolyGroup codeGroup(makeCoeffs(circuit.getCode(), codeSize), codeSize, size);
  PolyGroup dataGroup(makeCoeffs(circuit.getData(), dataSize), dataSize, size);
  codeGroup.getMerkle().commit(iop);
  dataGroup.getMerkle().commit(iop);

  LOG(1, "codeGroup: " << codeGroup.getMerkle().getRoot());
  LOG(1, "dataGroup: " << dataGroup.getMerkle().getRoot());

  circuit.accumulate(iop);

  // Make PLONK accum group and commit a Merkle root
  LOG(1, "size = " << size << ", accumSize = " << accumSize);
  LOG(1, "getAccum.size() = " << circuit.getAccum().size());
  PolyGroup accumGroup(makeCoeffs(circuit.getAccum(), accumSize), accumSize, size);
  accumGroup.getMerkle().commit(iop);
  LOG(1, "accumGroup: " << accumGroup.getMerkle().getRoot());

  // Choose Fiat-Shamir constraint mixing paramater
  Fp4 polyMix = Fp4::random(iop);

  // Make the High Degree Validity Polynomial
  size_t domain = size * kInvRate;
  auto checkPoly = AccelSlice<Fp>::allocate(4 * domain);
  circuit.evalCheck(checkPoly,
                    codeGroup.getEvaluated(),
                    dataGroup.getEvaluated(),
                    accumGroup.getEvaluated(),
                    polyMix);

#ifdef CIRCUIT_DEBUG
  Fp4 badZ; // = Fp4(1);
  {
    AccelReadLock<Fp> lock(checkPoly);
    for (size_t i = 0; i < 4 * domain; i += 4) {
      if (lock[i] != 0) {
        LOG(1, "ERROR AT i = " << i << " value = " << lock[i]);
        badZ = Fp4(pow(kRouFwd[po2], i / 4));
        break;
      }
    }
  }
#endif

  // Convert to coefficients.  Some tricky bizness here with the fact that checkPoly is really
  // an Fp4 polynomial.  Nicely for us, since all the roots of unity (which are the only thing that
  // and values get multiplied by) are in Fp, Fp4 values act like simple vectors of Fp for the
  // purposes of interpolate/evaluate.
  batchInterpolateNTT(checkPoly, 4);

  // Now split the High Degree Validity Polynomial into 4 Low Degree Validity Polynomials
  // so that f(x) = g0(x^4) + g1(x^4) x + g2(x^4) x^2 + g3(x^4) x^3.  To do this, we normally
  // would grab all the coeffients of f(x) = sum_i c_i x^i where i % 4 == 0 and put them into
  // a new polynomial g0(x) = sum_i d0_i*x^i, where d0_i = c_(i*4).
  //
  // Amazingingly, since the coefficients are bit reversed, the coefficients of g0 are all
  // aleady next to each other and in bit-reversed for for g0, as are the coeffients of g1, etc.
  // So really, we can just reinterpret 4 polys of invRate*size to 16 polys of size, without
  // actually doing anything.

  // Make the Low Degree Validity Polynomials + commit a Merkle root
  PolyGroup checkGroup(checkPoly, kCheckSize, size);
  checkGroup.getMerkle().commit(iop);
  LOG(1, "checkGroup: " << checkGroup.getMerkle().getRoot());

  // Now choose the DEEP test point Z
  Fp4 Z = Fp4::random(iop);
#ifdef CIRCUIT_DEBUG
  if (badZ != Fp4(0)) {
    Z = badZ;
  }
  iop.write(&Z, 1);
#endif
  LOG(1, "Z = " << Z);

  // Get rev rou for size
  Fp backOne = kRouRev[po2];
  std::vector<Fp4> allXs;

  // Do evaluations of all of the various polynomials at the appropriate points
  // Compute evalU
  std::vector<Fp4> evalU;
  auto evalGroup = [&](RegisterGroup id, PolyGroup& pg) {
    AccelConstSlice<Fp> coeffs = pg.getCoeffs();
    std::vector<uint32_t> which;
    std::vector<Fp4> xs;
    for (auto tap : tapSet.groupTaps(id)) {
      which.push_back(tap.offset());
      xs.push_back(pow(backOne, tap.back()) * Z);
      allXs.push_back(xs.back());
    }
    auto whichAccel = AccelSlice<uint32_t>::copy(which);
    auto xsAccel = AccelSlice<Fp4>::copy(xs);
    auto outAccel = AccelSlice<Fp4>::allocate(which.size());
    batchEvaluateAny(coeffs, pg.getCount(), whichAccel, xsAccel, outAccel);
    {
      AccelReadLock out(outAccel);
      std::copy(out.data(), out.data() + out.size(), std::back_inserter(evalU));
    }
  };
  // Now, we evaluate each group at the approriate points (relative to Z).
  // From here on out, we always process groups in accum, code, data order,
  // since this is the order used by the codegen system (alphabetical).
  // Sometimes it's a requirement for matching generated code, but even when
  // it's not we keep the order for consistency.
  evalGroup(RegisterGroup::ACCUM, accumGroup);
  evalGroup(RegisterGroup::CODE, codeGroup);
  evalGroup(RegisterGroup::DATA, dataGroup);

  // Now, convert the values to coefficients via interpolation
  size_t curPos = 0;
  std::vector<Fp4> coeffU(evalU.size());
  for (auto reg : tapSet.regs()) {
    polyInterpolate(
        coeffU.data() + curPos, allXs.data() + curPos, evalU.data() + curPos, reg.size());
    curPos += reg.size();
  }

  Fp4 Z4 = pow(Z, 4);
  // Add in the coeffs of the check polynomials.
  {
    std::vector<uint32_t> which;
    for (size_t i = 0; i < kCheckSize; i++) {
      which.push_back(i);
    }
    std::vector<Fp4> xs(kCheckSize, Z4);
    auto out = AccelSlice<Fp4>::allocate(kCheckSize);
    batchEvaluateAny(checkGroup.getCoeffs(),
                     kCheckSize,
                     AccelSlice<uint32_t>::copy(which),
                     AccelSlice<Fp4>::copy(xs),
                     out);
    AccelReadLock outLock(out);
    std::copy(outLock.data(), outLock.data() + out.size(), std::back_inserter(coeffU));
  }

  LOG(1, "Size of U = " << coeffU.size());
  // Write coefficients of DEEP polynomials publicly
  iop.write(coeffU.data(), coeffU.size());
  auto hashU = shaHash(reinterpret_cast<const Fp*>(coeffU.data()), coeffU.size() * 4, 1, false);
  iop.commit(hashU);

  // Set the Fiat Shamir parameter for mixing DEEP polynomials
  Fp4 mix = Fp4::random(iop);
  LOG(1, "Mix = " << mix);

  // Do the coefficent mixing
  // Begin by making a zeroed output buffer
  auto combos = AccelSlice<Fp4>::copy(std::vector<Fp4>(size * (comboCount + 1)));
  Fp4 curMix(1);
  auto mixGroup = [&](RegisterGroup id, PolyGroup& pg) {
    std::vector<uint32_t> which;
    for (auto reg : tapSet.groupRegs(id)) {
      which.push_back(reg.comboID());
    }
    auto whichAccel = AccelSlice<uint32_t>::copy(which);
    auto curMixAccel = AccelSlice<Fp4>::copy(&curMix, 1);
    auto mixAccel = AccelSlice<Fp4>::copy(&mix, 1);
    size_t gsize = tapSet.groupSize(id);
    mixPolyCoeffsAccel(combos, curMixAccel, mixAccel, pg.getCoeffs(), whichAccel, gsize, size);
    curMix *= pow(mix, gsize);
  };
  mixGroup(RegisterGroup::ACCUM, accumGroup);
  mixGroup(RegisterGroup::CODE, codeGroup);
  mixGroup(RegisterGroup::DATA, dataGroup);
  {
    std::vector<uint32_t> which(kCheckSize, comboCount);
    auto whichAccel = AccelSlice<uint32_t>::copy(which);
    auto curMixAccel = AccelSlice<Fp4>::copy(&curMix, 1);
    auto mixAccel = AccelSlice<Fp4>::copy(&mix, 1);
    mixPolyCoeffsAccel(
        combos, curMixAccel, mixAccel, checkGroup.getCoeffs(), whichAccel, kCheckSize, size);
  }

  // Load the near final coefficients back to the CPU
  auto comboCpu = std::make_unique<AccelReadWriteLock<Fp4>>(combos);
  // Subtract the U coeffs from the combos
  curPos = 0;
  Fp4 cur = Fp4(1);
  for (auto reg : tapSet.regs()) {
    for (size_t i = 0; i < reg.size(); i++) {
      (*comboCpu)[size * reg.comboID() + i] -= cur * coeffU[curPos + i];
    }
    cur *= mix;
    curPos += reg.size();
  }
  // Subtract the final 'check' coefficents
  for (size_t i = 0; i < kCheckSize; i++) {
    (*comboCpu)[size * comboCount] -= cur * coeffU[curPos++];
    cur *= mix;
  }

  // Divide each element by (x - Z * back1^back) for each back
  for (size_t combo = 0; combo < tapSet.combosSize(); combo++) {
    for (size_t back : tapSet.getCombo(combo)) {
      REQUIRE(polyDivide(comboCpu->data() + combo * size, size, Z * pow(backOne, back)) == Fp4(0));
    }
  }
  // Divide check polys by Z4
  REQUIRE(polyDivide(comboCpu->data() + comboCount * size, size, Z4) == Fp4(0));
  comboCpu.reset(); // Free lock, move memory back to accelerator

  // Sum the combos up into one final polynomial + make then make it into 4 Fp polys
  // Additionally, it needs to be bit reversed to make everyone happy
  auto finalPolyCoeffs = AccelSlice<Fp>::allocate(size * 4);
  eltwiseSumFp4Accel(finalPolyCoeffs, combos);

  // Finally do the FRI protocol to prove the degree of the polynomial
  batchBitReverse(finalPolyCoeffs, 4);
  LOG(1, "FRI-proof, size = " << finalPolyCoeffs.size() / 4);
  friProve(iop, finalPolyCoeffs, [&](WriteIOP& iop, size_t idx) {
    accumGroup.getMerkle().prove(iop, idx);
    codeGroup.getMerkle().prove(iop, idx);
    dataGroup.getMerkle().prove(iop, idx);
    checkGroup.getMerkle().prove(iop, idx);
  });

  // Return final proof
  std::vector<uint32_t> ret = iop.getProof();
  LOG(1, "Proof size = " << ret.size());
  return ret;
}

} // namespace risc0
