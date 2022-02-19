#include "risc0/zkp/verify/merkle.h"

namespace risc0 {

MerkeTreeParams::MerkeTreeParams(size_t rowSize, size_t colSize, size_t queries)
    : rowSize(rowSize), colSize(colSize), queries(queries), layers(log2Ceil(rowSize)) {
  REQUIRE(1 << layers == rowSize);
  topLayer = 0;
  for (size_t i = 1; i < layers; i++) {
    if ((1 << i) > queries) {
      break;
    }
    topLayer = i;
  }
  topSize = 1 << topLayer;
}

MerkleTreeVerifier::MerkleTreeVerifier(ReadIOP& iop, size_t rowSize, size_t colSize, size_t queries)
    : MerkeTreeParams(rowSize, colSize, queries), top(topSize * 2) {
  iop.read(&top[topSize], topSize);
  for (size_t i = topSize; i-- > 1;) {
    top[i] = shaHashPair(top[i * 2], top[i * 2 + 1]);
  }
  iop.commit(top[1]);
}

ShaDigest MerkleTreeVerifier::getRoot() const {
  return top[1];
}

std::vector<Fp> MerkleTreeVerifier::verify(ReadIOP& iop, size_t idx) const {
  REQUIRE(idx < rowSize);
  std::vector<Fp> out(colSize);
  iop.read(out.data(), colSize);
  ShaDigest cur = shaHash(out.data(), colSize, 1, false);
  idx += rowSize;
  while (idx >= 2 * topSize) {
    size_t lowBit = idx % 2;
    ShaDigest other;
    iop.read(&other, 1);
    idx /= 2;
    if (lowBit) {
      cur = shaHashPair(other, cur);
    } else {
      cur = shaHashPair(cur, other);
    }
  }
  REQUIRE(top[idx] == cur);
  return out;
}

} // namespace risc0
