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
#include "risc0/zkp/core/poly.h"
#include "risc0/zkp/core/rou.h"
#include "risc0/zkp/prove/fri.h"
#include "risc0/zkp/prove/poly_group.h"
#include "risc0/zkp/prove/step/exec.h"
#include "risc0/zkp/prove/write_iop.h"

namespace risc0 {

static AccelSlice<Fp> makeCoeffs(std::vector<Fp>& vec, size_t count, bool zkFill) {
  size_t size = vec.size() / count;

  // Fill in noise (if desired)
#ifndef CIRCUIT_DEBUG
  if (zkFill) {
    for (size_t i = 0; i < count; i++) {
      for (size_t j = size - kZkCycles; j < size; j++) {
        vec[i * size + j] = Fp::random(CryptoRng::shared());
      }
    }
  }
#endif

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

// NOLINTNEXTLINE(readability-function-size)
BufferU32 prove(const std::string& elfFile, MemoryHandler& io) {
  // Setup output IOP
  WriteIOP iop;

  // Do main execution + get size
  ExecState exec(elfFile);
  exec.run(kMaxCycles, io);
  size_t size = exec.context.numSteps;
  uint32_t po2 = log2Ceil(size);

  // Write final low register state
  for (size_t i = 0; i < kOutputRegs; i++) {
    const Fp* globals = exec.context.globals;
    uint32_t regVal = globals[2 * i].asUInt32() | (globals[2 * i + 1].asUInt32() << 16);
    LOG(2, "x" << i + 1 << " = " << hex(regVal));
    iop.write(&regVal, 1);
  }

  // Write the po2 for size
  iop.write(&po2, 1);

  // Now, do memory verification
  for (size_t i = 0; i < size - kZkCycles; i++) {
    exec.context.curStep = i;
    dataStepCheck(exec.context, exec.code.data(), exec.data.data());
  }

#ifdef CIRCUIT_DEBUG
  // Set any unset values to dead
  for (Fp& x : exec.data) {
    if (x == Fp::invalid()) {
      x = 0xdead;
    }
  }
#endif

  // Make code + data PolyGroups + commit them
  PolyGroup codeGroup(makeCoeffs(exec.code, kCodeSize, false), kCodeSize, size);
  PolyGroup dataGroup(makeCoeffs(exec.data, kDataSize, true), kDataSize, size);
  codeGroup.getMerkle().commit(iop);
  dataGroup.getMerkle().commit(iop);

  LOG(1, "codeGroup: " << codeGroup.getMerkle().getRoot());
  LOG(1, "dataGroup: " << dataGroup.getMerkle().getRoot());

  // Fill in accum mix
  for (size_t i = 0; i < kAccumMixGlobalSize; i++) {
    exec.context.globals[kAccumMixGlobalOffset + i] = Fp::random(iop);
  }

  // Generate accum
#ifdef CIRCUIT_DEBUG
  std::vector<Fp> accum(kAccumSize * size, Fp::invalid());
#else
  std::vector<Fp> accum(kAccumSize * size);
#endif
  for (size_t i = 0; i < size - kZkCycles; i++) {
    exec.context.curStep = i;
    accumStep(exec.context, exec.code.data(), exec.data.data(), accum.data());
  }

#ifdef CIRCUIT_DEBUG
  // Set any unset values to dead
  for (Fp& x : accum) {
    if (x == Fp::invalid()) {
      x = 0xdead;
    }
  }
#endif

  // Make the accum group + commit
  PolyGroup accumGroup(makeCoeffs(accum, kAccumSize, true), kAccumSize, size);
  accumGroup.getMerkle().commit(iop);
  LOG(1, "accumGroup: " << accumGroup.getMerkle().getRoot());

  // Set the poly mix value
  for (size_t i = 0; i < kPolyMixGlobalSize; i++) {
    exec.context.globals[kPolyMixGlobalOffset + i] = Fp::random(iop);
  }

  // Now generate the check polynomial
  size_t domain = size * kInvRate;
  auto checkPoly = AccelSlice<Fp>::allocate(4 * domain);
  accelBeginProfile();
  evalCheckPolyAccel(checkPoly,
                     codeGroup.getEvaluated(),
                     dataGroup.getEvaluated(),
                     accumGroup.getEvaluated(),
                     AccelSlice<Fp>::copy(exec.context.globals, kGlobalSize),
                     AccelSlice<Fp>::copy(kRouFwd, kMaxRouPo2 + 1),
                     domain);
  accelEndProfile();

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

  // The next step is to convert the degree 4*n check polynomial into 4 degreen n polynomials
  // so that f(x) = g0(x^4) + g1(x^4) x + g2(x^4) x^2 + g3(x^4) x^3.  To do this, we normally
  // would grab all the coeffients of f(x) = sum_i c_i x^i where i % 4 == 0 and put them into
  // a new polynomial g0(x) = sum_i d0_i*x^i, where d0_i = c_(i*4).
  //
  // Amazingingly, since the coefficients are bit reversed, the coefficients of g0 are all
  // aleady next to each other and in bit-reversed for for g0, as are the coeffients of g1, etc.
  // So really, we can just reinterpret 4 polys of invRate*size to 16 polys of size, without
  // actually doing anything.

  // Make the PolyGroup + add it to the IOP;
  PolyGroup checkGroup(checkPoly, kCheckSize, size);
  checkGroup.getMerkle().commit(iop);
  LOG(1, "checkGroup: " << checkGroup.getMerkle().getRoot());

  // Now pick a value for Z
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
  size_t codeSize = kCodeSize;
  size_t dataSize = kDataSize;
  size_t accumSize = kAccumSize;
  std::vector<Fp4> evalU;
#define base_begin(name)                                                                           \
  {                                                                                                \
    AccelConstSlice<Fp> coeffs = name##Group.getCoeffs();                                          \
    size_t polyCount = name##Size;                                                                 \
    std::vector<uint32_t> which;                                                                   \
    std::vector<Fp4> xs;
#define offset_begin(base, off)                                                                    \
  {                                                                                                \
    uint32_t offset = off;
#define tap(base, offset, back)                                                                    \
  which.push_back(offset);                                                                         \
  xs.push_back(pow(backOne, back) * Z);                                                            \
  allXs.push_back(xs[xs.size() - 1]);
#define offset_end(base, off, combo) }
#define base_end(name)                                                                             \
  auto whichAccel = AccelSlice<uint32_t>::copy(which);                                             \
  auto xsAccel = AccelSlice<Fp4>::copy(xs);                                                        \
  auto outAccel = AccelSlice<Fp4>::allocate(which.size());                                         \
  batchEvaluateAny(coeffs, polyCount, whichAccel, xsAccel, outAccel);                              \
  {                                                                                                \
    AccelReadLock out(outAccel);                                                                   \
    std::copy(out.data(), out.data() + out.size(), std::back_inserter(evalU));                     \
  }                                                                                                \
  }
#define TAPS
#include "risc0/zkp/prove/step/step.cpp.inc"

  // Now, convert the values to coefficients via interpolation
  size_t curPos = 0;
  std::vector<Fp4> coeffU(evalU.size());
#define offset_begin(base, off)                                                                    \
  {                                                                                                \
    size_t start = curPos;
#define tap(base, offset, back) curPos++;
#define offset_end(base, offset, combo)                                                            \
  polyInterpolate(                                                                                 \
      coeffU.data() + start, allXs.data() + start, evalU.data() + start, curPos - start);          \
  }
#include "risc0/zkp/prove/step/step.cpp.inc"

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
  iop.write(coeffU.data(), coeffU.size());
  auto hashU = shaHash(reinterpret_cast<const Fp*>(coeffU.data()), coeffU.size() * 4);
  iop.commit(hashU);

  // Set the mix mix value
  Fp4 mix;
  for (size_t i = 0; i < kMixMixGlobalSize; i++) {
    mix.elems[i] = Fp::random(iop);
    exec.context.globals[kMixMixGlobalOffset + i] = mix.elems[i];
  }
  LOG(1, "Mix = " << mix);

  // Do the coefficent mixing
  auto combos = AccelSlice<Fp4>::allocate(size * (kComboCount + 1));
  mixPolyCoeffsAccel(combos,
                     codeGroup.getCoeffs(),
                     dataGroup.getCoeffs(),
                     accumGroup.getCoeffs(),
                     checkGroup.getCoeffs(),
                     AccelSlice<Fp>::copy(exec.context.globals, kGlobalSize),
                     size);

  // Load the near final coefficients back to the CPU
  auto comboCpu = std::make_unique<AccelReadWriteLock<Fp4>>(combos);
  // Subtract the U coeffs from the combos
  curPos = 0;
  Fp4 cur = Fp4(1);
#define offset_begin(base, off)                                                                    \
  {                                                                                                \
    size_t start = curPos;
#define tap(base, offset, back) curPos++;
#define offset_end(base, offset, combo)                                                            \
  for (size_t i = 0; i < curPos - start; i++) {                                                    \
    (*comboCpu)[size * combo + i] -= cur * coeffU[start + i];                                      \
  }                                                                                                \
  cur *= mix;                                                                                      \
  }
#include "risc0/zkp/prove/step/step.cpp.inc"
  // Subtract the final 'check' coefficents
  for (size_t i = 0; i < kCheckSize; i++) {
    (*comboCpu)[size * kComboCount] -= cur * coeffU[curPos++];
    cur *= mix;
  }

  // Divide each element by (x - Z * back1^back) for each back
  size_t curCombo;
#define combo_begin(id) curCombo = id;
#define tap(x)                                                                                     \
  REQUIRE(polyDivide(comboCpu->data() + curCombo * size, size, Z * pow(backOne, x)) == Fp4(0));
#undef TAPS
#define COMBOS
#include "risc0/zkp/prove/step/step.cpp.inc"
  // Divide check polys by Z4
  REQUIRE(polyDivide(comboCpu->data() + kComboCount * size, size, Z4) == Fp4(0));
  comboCpu.reset(); // Free lock, move memory back to accelerator

  // Sum the combos up into one final polynomial + make then make it into 4 Fp polys
  // Additionally, it needs to be bit reversed to make everyone happy
  auto finalPolyCoeffs = AccelSlice<Fp>::allocate(size * 4);
  eltwiseSumFp4Accel(finalPolyCoeffs, combos);

  // Finally do the FRI protocol to prove the degree of the polynomial
  batchBitReverse(finalPolyCoeffs, 4);
  LOG(1, "FRI-proof, size = " << finalPolyCoeffs.size() / 4);
  friProve(iop, finalPolyCoeffs, [&](WriteIOP& iop, size_t idx) {
    codeGroup.getMerkle().prove(iop, idx);
    dataGroup.getMerkle().prove(iop, idx);
    accumGroup.getMerkle().prove(iop, idx);
    checkGroup.getMerkle().prove(iop, idx);
  });

  // Return final proof
  std::vector<uint32_t> ret = iop.getProof();
  LOG(1, "Proof size = " << ret.size());
  return ret;
}

} // namespace risc0
