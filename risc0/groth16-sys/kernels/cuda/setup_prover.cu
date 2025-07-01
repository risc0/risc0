#include <cstring>
#include <iostream>

#if defined(FEATURE_BN254)
#include <ff/alt_bn128-fp2.hpp>
#else
#error "only FEATURE_BN254 is supported"
#endif

#include <ec/affine_t.hpp>
#include <ec/jacobian_t.hpp>
#include <ec/xyzz_t.hpp>

typedef Affine_t<fp_t> affine_t;
typedef jacobian_t<fp_t> point_t;
typedef xyzz_t<fp_t> bucket_t;

typedef Affine_t<fp2_t> affine_fp2_t;
typedef jacobian_t<fp2_t> point_fp2_t;
typedef xyzz_t<fp2_t> bucket_fp2_t;

typedef fr_t scalar_t;

#define SPPARK_DONT_INSTANTIATE_TEMPLATES
#include <msm/pippenger.cuh>
#include <ntt/ntt.cuh>

#include "util.cuh"

#include "groth16_coeffs.cuh"
#include "groth16_prover.cuh"
#include "groth16_srs.cuh"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("usage: setup_prover <precomputations_directory> <srs_path>\n");
    exit(-1);
  }

  groth16_params params(argv[1]);
  const char* pcoeffs_path = params.get_pcoeffs_path().c_str();
  const char* fres_path = params.get_fres_path().c_str();
  const char* srs_path = argv[2];

  try {
    SRS sw(0, srs_path);
    groth16_prover prover(sw);
    prover.write_precomputations_to_file(fres_path, pcoeffs_path);
  } catch (const sppark_error& e) {
    std::cout << "error encountered during setup prover: " << e.code() << ", " << e.what()
              << std::endl;

    return 1;
  }

  return 0;
}
