#include "risc0/zkp/prove/merkle.h"

#include "risc0/core/log.h"

namespace risc0 {

MerkleTreeProver::MerkleTreeProver(AccelConstSlice<Fp> matrix,
                                   size_t rowSize,
                                   size_t colSize,
                                   size_t queries)
    : MerkeTreeParams(rowSize, colSize, queries), matrix(matrix) {
  REQUIRE(matrix.size() == rowSize * colSize);
  // Allocate nodes
  nodes = AccelSlice<ShaDigest>::allocate(rowSize * 2);
  colTmp = AccelSlice<Fp>::allocate(colSize);
  proofTmp = AccelSlice<ShaDigest>::allocate(std::max(topSize, layers - topLayer));
  // Sha each column
  shaRowsAccel(nodes.slice(rowSize, rowSize), matrix);
  // For each layer, sha up the layer below
  for (size_t i = layers; i-- > 0;) {
    size_t layerSize = (1 << i);
    shaFoldAccel(nodes.slice(layerSize, layerSize), nodes.slice(2 * layerSize, 2 * layerSize));
  }
  // Copy root into the proofTmp top and move back to CPU
  eltwiseCopyShaDigestAccel(proofTmp.slice(0, 1), nodes.slice(1, 1));
  {
    AccelReadLock readProof(proofTmp.slice(0, 1));
    root = readProof[0];
  }
}

void MerkleTreeProver::commit(WriteIOP& iop) const {
  eltwiseCopyShaDigestAccel(proofTmp.slice(0, topSize), nodes.slice(topSize, topSize));
  {
    AccelReadLock readProof(proofTmp.slice(0, topSize));
    iop.write(readProof.data(), topSize);
  }
  iop.commit(getRoot());
}

ShaDigest MerkleTreeProver::getRoot() const {
  return root;
}

std::vector<Fp> MerkleTreeProver::prove(WriteIOP& iop, size_t idx) const {
  REQUIRE(idx < rowSize);
  AccelReadLock<Fp> matrixCpu(matrix);
  AccelReadLock<ShaDigest> nodesCpu(nodes);
  std::vector<Fp> out(colSize);
  for (size_t i = 0; i < colSize; i++) {
    out[i] = matrixCpu[idx + i * rowSize];
  }
  iop.write(out.data(), colSize);
  idx += rowSize;
  while (idx >= 2 * topSize) {
    size_t lowBit = idx % 2;
    idx /= 2;
    size_t otherIdx = 2 * idx + (1 - lowBit);
    iop.write(&nodesCpu[otherIdx], 1);
  }
  return out;
}

} // namespace risc0
