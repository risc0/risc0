#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __CUDA_ARCH__
typedef uint8_t byte;
#endif

struct coeff_t {
  uint32_t m, c, s;
  fr_t value;
};

class preprocessed_coeffs {
private:
  const gpu_t& gpu;

  gpu_ptr_t<coeff_t> d_coeffs;
  slice_t<coeff_t> d_coeffs_a, d_coeffs_b;

  gpu_ptr_t<uint32_t> d_independent_indices;
  slice_t<uint32_t> d_ind_idx_a, d_ind_idx_b;

public:
  preprocessed_coeffs(const gpu_t& gpu, const slice_t<coeff_t>& coeffs_slice) : gpu(gpu) {
    size_t coeff_count_a = 0, unique_count_a = 0, coeff_count_b = 0, unique_count_b = 0,
           prev_a = (size_t)-1, prev_b = (size_t)-1;

    for (size_t i = 0; i < coeffs_slice.size(); i++) {
      bool is_a = coeffs_slice[i].m == 0;

      if (is_a) {
        coeff_count_a++;
        if (coeffs_slice[i].c != prev_a) {
          prev_a = coeffs_slice[i].c;
          unique_count_a++;
        }
      } else {
        coeff_count_b++;
        if (coeffs_slice[i].c != prev_b) {
          prev_b = coeffs_slice[i].c;
          unique_count_b++;
        }
      }

      if (i > 0)
        if (coeffs_slice[i].c < coeffs_slice[i - 1].c) {
          throw sppark_error{EINVAL,
                             "coeff[%zu].c < coeff[%zu].c (%u < %u) coeffs are expected to be in "
                             "ascending order with respect to their \"c\" field: ",
                             i,
                             i - 1,
                             coeffs_slice[i].c,
                             coeffs_slice[i - 1].c};
        }
    }

    std::vector<coeff_t> coeffs(coeff_count_a + coeff_count_b);
    slice_mut<coeff_t> coeffs_a(&coeffs[0], coeff_count_a),
        coeffs_b(&coeffs[coeff_count_a], coeff_count_b);

    std::vector<uint32_t> independent_indices(2 + unique_count_a + unique_count_b);
    slice_mut<uint32_t> ind_idx_a(&independent_indices[0], 1 + unique_count_a),
        ind_idx_b(&independent_indices[1 + unique_count_a], 1 + unique_count_b);

    coeff_count_a = 0, unique_count_a = 0, coeff_count_b = 0, unique_count_b = 0,
    prev_a = (size_t)-1, prev_b = (size_t)-1;

    for (size_t i = 0; i < coeffs_slice.size(); i++) {
      bool is_a = coeffs_slice[i].m == 0;

      if (is_a) {
        coeffs_a[coeff_count_a] = coeffs_slice[i];

        if (coeffs_slice[i].c != prev_a) {
          prev_a = coeffs_slice[i].c;
          ind_idx_a[unique_count_a] = coeff_count_a;
          unique_count_a++;
        }
        coeff_count_a++;
      }
    }

    for (size_t i = 0; i < coeffs_slice.size(); i++) {
      bool is_a = coeffs_slice[i].m == 0;

      if (!is_a) {
        coeffs_b[coeff_count_b] = coeffs_slice[i];

        if (coeffs_slice[i].c != prev_b) {
          prev_b = coeffs_slice[i].c;
          ind_idx_b[unique_count_b] = coeff_count_b;
          unique_count_b++;
        }
        coeff_count_b++;
      }
    }

    ind_idx_a[unique_count_a] = coeff_count_a;
    ind_idx_b[unique_count_b] = coeff_count_b;

    d_coeffs = gpu_ptr_t<coeff_t>((coeff_t*)gpu.Dmalloc(coeffs.size() * sizeof(coeff_t)));
    d_independent_indices =
        gpu_ptr_t<uint32_t>((uint32_t*)gpu.Dmalloc(independent_indices.size() * sizeof(uint32_t)));

    gpu.HtoD(&d_coeffs[0], &coeffs[0], coeffs.size());
    gpu.HtoD(&d_independent_indices[0], &independent_indices[0], independent_indices.size());

    d_coeffs_a = slice_t<coeff_t>(&d_coeffs[0], coeffs_a.size());
    d_coeffs_b = slice_t<coeff_t>(&d_coeffs[coeffs_a.size()], coeffs_b.size());

    d_ind_idx_a = slice_t<uint32_t>(&d_independent_indices[0], ind_idx_a.size());
    d_ind_idx_b = slice_t<uint32_t>(&d_independent_indices[ind_idx_a.size()], ind_idx_b.size());

    gpu.sync();
  }

  preprocessed_coeffs(const gpu_t& gpu, const byte *input_coeffs) : gpu(gpu) {
    {
      size_t* ptr = (size_t*)input_coeffs;
      size_t coeff_count_a = ptr[0];
      size_t coeff_count_b = ptr[1];
      size_t unique_count_a = ptr[2];
      size_t unique_count_b = ptr[3];

      d_coeffs = gpu_ptr_t<coeff_t>(
          (coeff_t*)gpu.Dmalloc((coeff_count_a + coeff_count_b) * sizeof(coeff_t)));
      d_independent_indices = gpu_ptr_t<uint32_t>(
          (uint32_t*)gpu.Dmalloc((unique_count_a + unique_count_b) * sizeof(uint32_t)));

      d_coeffs_a = slice_t<coeff_t>(&d_coeffs[0], coeff_count_a);
      d_coeffs_b = slice_t<coeff_t>(&d_coeffs[coeff_count_a], coeff_count_b);

      d_ind_idx_a = slice_t<uint32_t>(&d_independent_indices[0], unique_count_a);
      d_ind_idx_b = slice_t<uint32_t>(&d_independent_indices[unique_count_a], unique_count_b);
    }

    const byte* ptr = input_coeffs + 4 * sizeof(size_t);
    gpu.HtoD(&d_coeffs[0], (coeff_t*)&ptr[0], d_coeffs_a.size() + d_coeffs_b.size());

    ptr += (d_coeffs_a.size() + d_coeffs_b.size()) * sizeof(coeff_t);
    gpu.HtoD(
        &d_independent_indices[0], (uint32_t*)&ptr[0], d_ind_idx_a.size() + d_ind_idx_b.size());

    gpu.sync();
  }

  size_t copy_to(size_t preprocessed_coeffs_len, byte *preprocessed_coeffs_out) {
    size_t copy_size = 4 * sizeof(size_t) +
                     (d_coeffs_a.size() + d_coeffs_b.size()) * sizeof(coeff_t) +
                     (d_ind_idx_a.size() + d_ind_idx_b.size()) * sizeof(uint32_t);
    assert(preprocessed_coeffs_len >= copy_size);

    {
      size_t* copy_ptr = (size_t*)preprocessed_coeffs_out;
      copy_ptr[0] = d_coeffs_a.size();
      copy_ptr[1] = d_coeffs_b.size();
      copy_ptr[2] = d_ind_idx_a.size();
      copy_ptr[3] = d_ind_idx_b.size();
    }

    byte* copy_ptr = preprocessed_coeffs_out;

    copy_ptr += 4 * sizeof(size_t);
    gpu.DtoH((coeff_t*)copy_ptr, &d_coeffs[0], d_coeffs_a.size() + d_coeffs_b.size());

    copy_ptr += (d_coeffs_a.size() + d_coeffs_b.size()) * sizeof(coeff_t);
    gpu.DtoH(
        (uint32_t*)copy_ptr, &d_independent_indices[0], d_ind_idx_a.size() + d_ind_idx_b.size());

    return copy_size;
  }

  const slice_t<coeff_t> get_coeffs_a() const { return d_coeffs_a; }

  const slice_t<coeff_t> get_coeffs_b() const { return d_coeffs_b; }

  const slice_t<uint32_t> get_indices_a() const { return d_ind_idx_a; }

  const slice_t<uint32_t> get_indices_b() const { return d_ind_idx_b; }
};
