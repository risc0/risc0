
#pragma once

#include <memory>
#include <vector>

#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/prove/merkle.h"

namespace risc0 {

// A PolyGroup represents a group of polynomials, all of the same maximum degree, as well as the
// evaluation of those polynomials over some domain that is larger than that degree by some invRate.
// Additionally, it includes a dense Merkle tree, where each entry is a single point of the domain,
// and the leaf hash is a simple linear hash of all of the values at that point.  That is, if we
// have 100 polynomials evaluated on 2^16 points, the merkle tree has 2^16 entries, each being a
// hash of 100 values.  The size of the domain is always a power of 2 so that we can use NTTs.
//
// The primary purpose of the PolyGroup is for use in the DEEP-ALI protocol, which basically needs
// 4 methods during proof generation, specifically we need to:
// 1) Resolve queries (i.e. make MerkleColProofs)
// 2) Do evaluation of the polynomials at 'randomly' chosen points
// 3) Mix the polynomials via a random set of linear coefficients
// 4) Access the raw values in the evaluation domain to 'evaluate' the constraint polynomial
//
// The poly group holds 3 buffers:
// 1) The per-polynomial coefficients, used for evaluation + mixing
// 2) The points evaluated on the domain in question (for the 'col' part of merkle proofs)
// 3) The Merkle tree itself.
//
// PolyGroups are constructed from two basic sources: steps of a computations, and a single higher
// degree polynomial that has been split into lower degree parts.  In the case of computations, the
// resulting steps must be padded (possibly with randomized data), which is presumed to be done by
// the caller. The constructor additionally 'shifts' the polynomial so that f(x) -> f(3*x), which
// means that the normal NTT evaluation domain does not reveal anything about the original
// datapoints (i.e. is zero knowledge) so long as the number of queries is less than the randomized
// padding.

class PolyGroup {
public:
  // We take in a polynomial coefficients of 'count' polynomials each of 'size' coefficients (i.e.
  // degree of size-1), where coeffs.size() == count * size.  The input buffer is cofficient major,
  // that is for polynomial i and coefficent j, the location in the buffer is i * size + j.  The
  // coefficent buffer is retained locally by poly-group.  Also note: coefficients are given in
  // bit-reversed order, but are eventually stored in standard order.
  PolyGroup(AccelSlice<Fp> coeffs, size_t count, size_t size);

  // Basic accessors
  size_t getCount() const { return count; }   // Number of polynomials
  size_t getSize() const { return size; };    // # of coeffs in each polynomial;
  size_t getDomain() const { return domain; } // Size of the evaluation domain (invRate * size)

  // Get the raw buffers.
  AccelConstSlice<Fp> getCoeffs() { return coeffs; }
  AccelConstSlice<Fp> getEvaluated() { return evaluated; }

  // Get merkle tree
  const MerkleTreeProver& getMerkle() const { return *merkle; }

private:
  // Polymomial coeffients
  AccelSlice<Fp> coeffs;
  size_t count;
  size_t size;
  size_t domain;
  // Evaluated datapoints
  AccelSlice<Fp> evaluated;
  // The merkle tree, one entry per domain point.
  std::unique_ptr<MerkleTreeProver> merkle;
};

} // End namespace risc0
