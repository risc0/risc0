#include "risc0/zkp/prove/poly_group.h"

#include "risc0/zkp/circuit/constants.h"

namespace risc0 {

PolyGroup::PolyGroup(AccelSlice<Fp> coeffs, size_t count, size_t size)
    : coeffs(coeffs), count(count), size(coeffs.size() / count), domain(size * kInvRate) {
  REQUIRE(coeffs.size() == count * size);
  evaluated = AccelSlice<Fp>::allocate(count * domain);
  batchExpand(evaluated, coeffs, count);
  batchEvaluateNTT(evaluated, count, log2Ceil(kInvRate));
  batchBitReverse(coeffs, count);
  merkle = std::make_unique<MerkleTreeProver>(evaluated, domain, count, kQueries);
}

} // namespace risc0
