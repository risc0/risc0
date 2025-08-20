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

struct ProveParams {
  const uint8_t *pcoeffs;
  const uint8_t *fres;
  const uint8_t *srs;
  size_t srs_len;
};

struct SetupParams {
  const uint8_t *srs;
  size_t srs_len;
  size_t fuzzed_results_len;
  size_t preprocessed_coeffs_len;
  size_t *fuzzed_results_copied;
  size_t *preprocessed_coeffs_copied;
  uint8_t *fuzzed_results_out;
  uint8_t *preprocessed_coeffs_out;
};

struct Groth16Proof {
    fp_t a[2], c[2], b[4];
};

union proof_union {
    groth16_proof proof_in;
    struct Groth16Proof proof_out;
};

extern "C" const char *risc0_groth16_cuda_prove(
    const ProveParams *setup_params,
    const uint8_t *witness,
    struct Groth16Proof *proof_out
) {

  try {
    SRS srs(0, setup_params->srs, setup_params->srs_len);
    groth16_prover prover(srs, setup_params->pcoeffs, (const msm_results *)setup_params->fres);
    groth16_proof proof_in = prover.prove((const fr_t *)witness);

    proof_union pu = proof_union { proof_in };

    pu.proof_out.a[0].from();
    pu.proof_out.a[1].from();

    pu.proof_out.c[0].from();
    pu.proof_out.c[1].from();

    pu.proof_out.b[0].from();
    pu.proof_out.b[1].from();
    pu.proof_out.b[2].from();
    pu.proof_out.b[3].from();

    *proof_out = pu.proof_out;

  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

#ifdef SRS_READ_COEFFS

extern "C" const char* risc0_groth16_cuda_setup(SetupParams *params) {
  try {
    SRS sw(0, params->srs, params->srs_len);
    groth16_prover prover(sw);
    prover.copy_precomputations(
        params->fuzzed_results_len,
        params->preprocessed_coeffs_len,
        params->fuzzed_results_copied,
        params->preprocessed_coeffs_copied,
        params->fuzzed_results_out,
        params->preprocessed_coeffs_out
    );
  } catch (const std::exception& err) {
    return strdup(err.what());
  }
  return nullptr;
}

#endif // SRS_READ_COEFFS
