#pragma once

#include "groth16_coeffs.cuh"
#include "groth16_srs.cuh"

#include <cmath>
#include <fstream>
#include <random>

// from https://github.com/iden3/rapidsnark/blob/main/src/random_generator.hpp
static inline void randombytes_buf(void* buf, size_t size) {
  static std::random_device engine;
  static std::uniform_int_distribution<uint8_t> distr;

  uint8_t* buffer = static_cast<uint8_t*>(buf);

  for (size_t i = 0; i < size; i++) {
    buffer[i] = distr(engine);
  }
}

class LDE_launcher : NTT {
public:
  static void LDE_powers(fr_t* inout,
                         bool bitrev,
                         uint32_t lg_dsz,
                         uint32_t lg_blowup,
                         stream_t& stream,
                         const fr_t (*powers)[WINDOW_SIZE]) {
    size_t domain_size = (size_t)1 << lg_dsz;
    const uint32_t warpSize = gpu_props(stream).warpSize;

    if (domain_size < warpSize)
      LDE_distribute_powers<<<1, domain_size, 0, stream>>>(
          inout, lg_dsz, lg_blowup, bitrev, powers);
    else if (lg_dsz < 32)
      LDE_distribute_powers<<<domain_size / warpSize, warpSize, 0, stream>>>(
          inout, lg_dsz, lg_blowup, bitrev, powers);
    else
      LDE_distribute_powers<<<stream.sm_count(), 1024, 0, stream>>>(
          inout, lg_dsz, lg_blowup, bitrev, powers);

    CUDA_OK(cudaGetLastError());
  }
};

__global__ __launch_bounds__(512) void witness_into_poly(fr_t* out,
                                                         const coeff_t* coeffs,
                                                         slice_t<uint32_t> indices,
                                                         const fr_t* witness) {

  size_t tid = threadIdx.x + (size_t)blockIdx.x * blockDim.x;

  for (size_t i = tid; i < indices.size() - 1; i += (size_t)gridDim.x * blockDim.x) {
    uint32_t start_idx = indices[i];
    // There will always be some coeffs
    uint32_t coeff_count = indices[i + 1] - start_idx;

    fr_t sum;
    sum.zero();

    coeff_t coeff;
    for (size_t j = 0; j < coeff_count; j++) {
      coeff = coeffs[start_idx + j];
      fr_t val = witness[coeff.s];
      fr_t aux = val * coeff.value;
      sum += aux;
    }

    // "c" field of the coeffs gone over in above loop will be equal to each other
    out[coeff.c] = sum;
  }
}

struct groth16_proof {
  affine_t a, c;
  affine_fp2_t b;
};

void write_public_file(const char* file_path, slice_t<fr_t> public_vars) {
  std::ofstream public_file(file_path);
  if (!public_file.is_open()) {
    throw sppark_error{errno, "open(\"%s\") failed: ", file_path};
  }

  public_file << "[";
  for (size_t i = 0; i < public_vars.size(); i++) {
    fr_t v = public_vars[i];
    v.to();
#ifndef __CUDA_ARCH__
    public_file << "\"" << v << "\"";
#endif
    if (i < public_vars.size() - 1) {
      public_file << ",";
    }
  }
  public_file << "]";

  public_file.flush();

  if (public_file.fail()) {
    throw sppark_error{EIO, "failed to write public inputs to \"%s\": ", file_path};
  }
}

void write_proof_file(const char* file_path, groth16_proof proof) {
  union proof_and_fp_t {
    groth16_proof proof;
    struct {
      fp_t a[2], c[2], b[4];
    };
  };

  std::ofstream proof_file(file_path);
  if (!proof_file.is_open()) {
    throw sppark_error{errno, "open(\"%s\") failed: ", file_path};
  }

#ifndef __CUDA_ARCH__
  proof_and_fp_t p = proof_and_fp_t{proof};

  proof_file << "{ \"pi_a\":[\"" << p.a[0] << "\",\"" << p.a[1] << "\",\"1\"],  \"pi_b\": [[\""
             << p.b[0] << "\",\"" << p.b[1] << "\"],[\"" << p.b[2] << "\",\"" << p.b[3]
             << "\"], [\"1\",\"0\"]],  \"pi_c\": [\"" << p.c[0] << "\",\"" << p.c[1]
             << "\",\"1\"],  \"protocol\":\"groth16\" }";
#endif

  proof_file.flush();

  if (proof_file.fail()) {
    throw sppark_error{EIO, "failed to write proof to \"%s\": ", file_path};
  }
}

class groth16_prover {
private:
  struct msm_results {
    point_t a, b_g1, c, h;
    point_fp2_t b_g2;
  };

  const gpu_t& gpu;

public:
  const SRS& srs;
  preprocessed_coeffs coeffs;
  size_t witness_size;

  uint32_t lg_domain_size;
  gpu_ptr_t<fr_t> d_poly_a_b_c, d_fuzz, _partial_shift_powers;

  fr_t *d_a, *d_b, *d_c, (*partial_shift_powers)[WINDOW_SIZE];

  msm_t<bucket_t, point_t, affine_t, fr_t> msm_g1;
  msm_t<bucket_fp2_t, point_fp2_t, affine_fp2_t, fr_t> msm_g2;
  msm_results fuzzed_results;

  gpu_ptr_t<fr_t> d_witness;

  void NTT_sequence(stream_t& stream, fr_t* d_poly, uint32_t lg_domain_size) {
    NTT::Base_dev_ptr(stream,
                      d_poly,
                      lg_domain_size,
                      NTT::InputOutputOrder::NR,
                      NTT::Direction::inverse,
                      NTT::Type::standard);
    LDE_launcher::LDE_powers(d_poly, true, lg_domain_size, 0, stream, partial_shift_powers);
    NTT::Base_dev_ptr(stream,
                      d_poly,
                      lg_domain_size,
                      NTT::InputOutputOrder::RN,
                      NTT::Direction::forward,
                      NTT::Type::standard);
  }

  void write_fuzzed_results_to_file(const char* file_path) {
    std::ofstream file(file_path, std::ofstream::binary);
    if (!file.is_open()) {
      throw sppark_error{errno, "open(\"%s\") failed: ", file_path};
    }

    file.write((const char*)&fuzzed_results, sizeof(msm_results));
    file.flush();

    if (file.fail()) {
      throw sppark_error{EIO, "failed to write fuzzed results to \"%s\": ", file_path};
    }
  }

  msm_results read_fuzzed_results_from_file(const char* file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
      throw sppark_error{errno, "open(\"%s\") failed: ", file_path};
    }

    msm_results fuzzed_results;

    file.read((char*)&fuzzed_results, sizeof(fuzzed_results));

    if (file.gcount() != sizeof(msm_results)) {
      throw sppark_error{
          EINVAL,
          "fuzzed results file(\"%s\") is not the correct size. expected %zu, got %zu: ",
          file_path,
          sizeof(msm_results),
          file.gcount()};
    }

    return fuzzed_results;
  }

  void init_memory() {
    d_poly_a_b_c = gpu_ptr_t<fr_t>((fr_t*)gpu.Dmalloc(3 * srs.get_h_size() * sizeof(fr_t)));
    _partial_shift_powers =
        gpu_ptr_t<fr_t>((fr_t*)gpu.Dmalloc(WINDOW_NUM * WINDOW_SIZE * sizeof(fr_t)));
    d_witness = gpu_ptr_t<fr_t>((fr_t*)gpu.Dmalloc(witness_size * sizeof(fr_t)));

    size_t domain_size = srs.get_h_size();
    if ((domain_size & (domain_size - 1)) != 0) {
      throw sppark_error{
          EINVAL, "size of h is expected to be a power of 2, but is %zu: ", domain_size};
    }
    lg_domain_size = std::log2(domain_size);

    d_a = &d_poly_a_b_c[0];
    d_b = &d_a[domain_size];
    d_c = &d_b[domain_size];

    partial_shift_powers =
        reinterpret_cast<decltype(partial_shift_powers)>(&_partial_shift_powers[0]);

    fr_t shift = forward_roots_of_unity[lg_domain_size + 1];
    generate_partial_twiddles<<<WINDOW_SIZE / 32, 32, 0, gpu>>>(partial_shift_powers, shift);
    CUDA_OK(cudaGetLastError());

    size_t fuzz_size = srs.get_a_size();
    d_fuzz = generate_random_scalars(gpu, fuzz_size);
  }

  groth16_prover(const SRS& srs,
                 const char* preprocessed_coeffs_file,
                 const char* fuzzed_results_file)
      : gpu(srs.gpu)
      , srs(srs)
      , coeffs(gpu, preprocessed_coeffs_file)
      , witness_size(srs.get_a_size())
      , msm_g1(nullptr, srs.get_h_size())
      , msm_g2(nullptr, srs.get_b_g2_size()) {
    init_memory();

    fuzzed_results = read_fuzzed_results_from_file(fuzzed_results_file);
  }

#ifdef SRS_READ_COEFFS
  groth16_prover(const SRS& srs)
      : gpu(srs.gpu)
      , srs(srs)
      , coeffs(gpu, srs.get_coeffs_slice())
      , witness_size(srs.get_a_size())
      , msm_g1(nullptr, srs.get_h_size())
      , msm_g2(nullptr, srs.get_b_g2_size()) {
    init_memory();

    msm_g1.invoke(fuzzed_results.a, srs.get_a(), srs.get_a_size(), d_fuzz, false);
    msm_g1.invoke(fuzzed_results.b_g1, srs.get_b_g1(), srs.get_b_g1_size(), d_fuzz, false);
    msm_g2.invoke(fuzzed_results.b_g2, srs.get_b_g2(), srs.get_b_g2_size(), d_fuzz, false);
    msm_g1.invoke(fuzzed_results.c,
                  srs.get_c(),
                  srs.get_c_size(),
                  dev_ptr_t<fr_t>{&d_fuzz[witness_size - srs.get_c_size()]},
                  false);

    fuzzed_results.a.cneg(true);
    fuzzed_results.b_g1.cneg(true);
    fuzzed_results.b_g2.cneg(true);
    fuzzed_results.c.cneg(true);
  }
#endif

  groth16_proof prove(const char* public_file_path, const fr_t* witness) {
    size_t domain_size = (size_t)1 << lg_domain_size;

    msm_results results;

    gpu.HtoD(&d_witness[0], &witness[0], witness_size);

    std::exception_ptr eptr = nullptr;
    std::thread write_public_file_thread = std::thread([&] {
      try {
        write_public_file(public_file_path, slice_t<fr_t>{&witness[1], srs.get_num_public()});
      } catch (const sppark_error& e) {
        eptr = std::current_exception();
      }
    });

    try {
      event_t sync_event;

      gpu[0].bzero(&d_a[0], domain_size);
      witness_into_poly<<<gpu.sm_count(), 512, 0, gpu[0]>>>(
          &d_a[0], coeffs.get_coeffs_a().data(), coeffs.get_indices_a(), &d_witness[0]);
      CUDA_OK(cudaGetLastError());
      sync_event.record(gpu[0]);

      gpu.bzero(&d_b[0], domain_size);
      witness_into_poly<<<gpu.sm_count(), 512, 0, gpu>>>(
          &d_b[0], coeffs.get_coeffs_b().data(), coeffs.get_indices_b(), &d_witness[0]);
      CUDA_OK(cudaGetLastError());

      sync_event.wait(gpu);

      coeff_wise_mul<<<gpu.sm_count(), 1024, 0, gpu>>>(&d_c[0], &d_a[0], &d_b[0], lg_domain_size);
      CUDA_OK(cudaGetLastError());
      NTT_sequence(gpu, d_a, lg_domain_size);
      NTT_sequence(gpu, d_b, lg_domain_size);
      NTT_sequence(gpu, d_c, lg_domain_size);
      coeff_wise_mul_and_sub<<<gpu.sm_count(), 1024, 0, gpu>>>(
          &d_a[0], &d_b[0], &d_c[0], lg_domain_size);
      CUDA_OK(cudaGetLastError());
      gpu.sync();
      msm_g1.invoke(results.h, srs.get_h(), domain_size, d_poly_a_b_c);

      coeff_wise_add<<<gpu.sm_count(), 1024, 0, gpu>>>(&d_witness[0], &d_fuzz[0], witness_size);
      CUDA_OK(cudaGetLastError());

      msm_g1.invoke(results.a, srs.get_a(), srs.get_a_size(), d_witness, false);
      msm_g1.invoke(results.b_g1, srs.get_b_g1(), srs.get_b_g1_size(), d_witness, false);
      msm_g2.invoke(results.b_g2, srs.get_b_g2(), srs.get_b_g2_size(), d_witness, false);
      msm_g1.invoke(results.c,
                    srs.get_c(),
                    srs.get_c_size(),
                    dev_ptr_t<fr_t>{&d_witness[witness_size - srs.get_c_size()]},
                    false);

      write_public_file_thread.join();
      if (eptr != nullptr) {
        std::rethrow_exception(eptr);
      }
    } catch (const sppark_error& e) {
      if (write_public_file_thread.joinable())
        write_public_file_thread.join();
      throw;
    }

    results.a.add(fuzzed_results.a);
    results.b_g1.add(fuzzed_results.b_g1);
    results.b_g2.add(fuzzed_results.b_g2);
    results.c.add(fuzzed_results.c);

    fr_t r, s;
    r.zero();
    s.zero();
    randombytes_buf((void*)&r, sizeof(fr_t) - 1);
    randombytes_buf((void*)&s, sizeof(fr_t) - 1);

    point_t p1;
    point_fp2_t p2;

    const verifying_key& vk = srs.get_vk();

    results.a.add(vk.alpha_g1);
    mult(p1, vk.delta_g1, r);
    results.a.add(p1);

    results.b_g2.add(vk.beta_g2);
    mult(p2, vk.delta_g2, s);
    results.b_g2.add(p2);

    results.b_g1.add(vk.beta_g1);
    mult(p1, vk.delta_g1, s);
    results.b_g1.add(p1);

    results.c.add(results.h);

    mult(p1, results.a, s);
    results.c.add(p1);

    mult(p1, results.b_g1, r);
    results.c.add(p1);

    fr_t rs = r * s;

    mult(p1, vk.delta_g1, rs);
    p1.cneg(true);
    results.c.add(p1);

    return groth16_proof{results.a, results.c, results.b_g2};
  }

  void write_precomputations_to_file(const char* fuzzed_results_path,
                                     const char* preprocessed_coeffs_path) {
    write_fuzzed_results_to_file(fuzzed_results_path);
    coeffs.write_to_file(preprocessed_coeffs_path);
  }
};
