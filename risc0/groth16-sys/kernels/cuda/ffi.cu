#include <cstring>
#include <iostream>

#define FEATURE_BN254

#include "ff/alt_bn128-fp2.hpp"

#include "ec/affine_t.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wbitwise-instead-of-logical"
#include "ec/jacobian_t.hpp"
#pragma clang diagnostic pop

#include "ec/xyzz_t.hpp"

typedef Affine_t<fp_t> affine_t;
typedef jacobian_t<fp_t> point_t;
typedef xyzz_t<fp_t> bucket_t;

typedef Affine_t<fp2_t> affine_fp2_t;
typedef jacobian_t<fp2_t> point_fp2_t;
typedef xyzz_t<fp2_t> bucket_fp2_t;

typedef fr_t scalar_t;

#define SPPARK_DONT_INSTANTIATE_TEMPLATES
#include "msm/pippenger.cuh"

namespace sppark::bn254 {
#include "ntt/ntt.cuh"
} // namespace sppark::bn254
using namespace sppark::bn254;

#include "util.cuh"

#include "groth16_coeffs.cuh"
#include "groth16_prover.cuh"
#include "groth16_srs.cuh"

// from circom-witnesscalc
extern "C" size_t setup_parallel_graph(const char* graph_path);

// from circom-witnesscalc
extern "C" void
calc_witness_with_parallel_graph(const char* graph_path, const char* inputs_file, fr_t* witness);

struct SetupParams {
  const char* graph_path;
  const char* pcoeffs_path;
  const char* fres_path;
  const char* srs_path;
};

struct ProveParams {
  const char* inputs_path;
  const char* public_path;
  const char* proof_path;
};

extern "C" const char* risc0_groth16_cuda_prove(SetupParams* setup_params,
                                                ProveParams* prover_params) {
  // SETUP
  std::vector<fr_t> witness;
  auto read_thread = std::thread([&] {
    size_t witness_size = setup_parallel_graph(setup_params->graph_path);
    witness.resize(witness_size);

    calc_witness_with_parallel_graph(
        setup_params->graph_path, prover_params->inputs_path, &witness[0]);
  });

  try {
    SRS srs(0, setup_params->srs_path);
    groth16_prover prover(srs, setup_params->pcoeffs_path, setup_params->fres_path);

    read_thread.join();

    // PROVE
    groth16_proof proof = prover.prove(prover_params->public_path, witness);

    write_proof_file(prover_params->proof_path, proof);
  } catch (const std::exception& err) {
    if (read_thread.joinable()) {
      read_thread.join();
    }
    return strdup(err.what());
  }
  return nullptr;
}

#ifdef SRS_READ_COEFFS

extern "C" const char* risc0_groth16_cuda_setup(SetupParams* params) {
  try {
    SRS sw(0, params->srs_path);
    groth16_prover prover(sw);
    prover.write_precomputations_to_file(params->fres_path, params->pcoeffs_path);
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

#endif // SRS_READ_COEFFS
