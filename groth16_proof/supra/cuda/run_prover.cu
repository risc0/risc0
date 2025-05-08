#include <iostream>
#include <cstring>

#if defined(FEATURE_BN254)
# include <ff/alt_bn128-fp2.hpp>
#else
# error "only FEATURE_BN254 is supported"
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

#include "groth16_srs.cuh"
#include "groth16_coeffs.cuh"
#include "groth16_prover.cuh"

extern "C" size_t setup_parallel_graph(const char* graph_path);
extern "C" void calc_witness_with_parallel_graph(const char* graph_path,
                                                 const char* inputs_file,
                                                 fr_t* witness);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("usage: run_prover <precomputations_directory> <srs_path> <inputs_path>\n");
        exit(-1);
    }

    groth16_params params(argv[1]);
    const char* graph_path = params.get_graph_path().c_str();
    const char* pcoeffs_path = params.get_pcoeffs_path().c_str();
    const char* fres_path = params.get_fres_path().c_str();
    const char* srs_path = argv[2];
    const char* inputs_path = argv[3];
    const char* proof_path = "proof.json";
    const char* public_path = "public.json";

    // SETUP
    std::vector<fr_t> witness;
    auto read_thread = std::thread([&] {
        size_t witness_size = setup_parallel_graph(graph_path);
        witness.resize(witness_size);

        calc_witness_with_parallel_graph(graph_path, inputs_path, &witness[0]);
    });

    try {
        SRS srs(0, srs_path);
        groth16_prover prover(srs, pcoeffs_path, fres_path);

        read_thread.join();

        // PROVE
        groth16_proof proof = prover.prove(public_path, witness);

        write_proof_file(proof_path, proof);
    } catch (const sppark_error& e) {
        std::cout << "error encountered during proving: " << e.code() << ", " << e.what() << std::endl;
        if (read_thread.joinable())
            read_thread.join();

        return 1;
    }

    return 0;
}
