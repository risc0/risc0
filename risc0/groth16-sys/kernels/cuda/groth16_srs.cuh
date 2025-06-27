#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __CUDA_ARCH__
typedef uint8_t byte;
#endif

struct coeff_t {
  uint32_t m, c, s;
  fr_t value;
};

#pragma pack(push, 1)
struct coeff_file_t {
  uint32_t m, c, s;
  fr_t value;
};
#pragma pack(pop)

struct verifying_key {
  affine_t alpha_g1;
  affine_t beta_g1;
  affine_fp2_t beta_g2;
  affine_fp2_t gamma_g2;
  affine_t delta_g1;
  affine_fp2_t delta_g2;
};

class SRS {
public:
  const gpu_t& gpu;

private:
  // size of coeff, p1 affine and p2 affine points in the SRS file in bytes
#ifdef SRS_READ_COEFFS
  static const size_t coeff_size = sizeof(coeff_file_t);
#endif
  static const size_t p1_affine_size = 64;
  static const size_t p2_affine_size = 128;

  // 3 p1 affine and 3 p2 affine points are in the verification key. 660 bytes
  static const size_t vk_offset = p1_affine_size * 3 + p2_affine_size * 3;

  static inline uint32_t read_u32(const byte* srs_ptr, size_t& cursor) {
    uint32_t ret = *(const uint32_t*)(srs_ptr + cursor);
    cursor += sizeof(uint32_t);
    return ret;
  }

  static inline uint32_t read_u64(const byte* srs_ptr, size_t& cursor) {
    uint64_t ret = *(const uint64_t*)(srs_ptr + cursor);
    cursor += sizeof(uint64_t);
    return ret;
  }

  static inline void check_section_id(const byte* srs_ptr, size_t& cursor, uint32_t expected) {
    uint32_t section_id = read_u32(srs_ptr, cursor);

    if (section_id != expected) {
      throw sppark_error{EINVAL,
                         "SRS file's sections are expected to be in ascending order. expected "
                         "section %u, got %u: ",
                         expected,
                         section_id};
    }
  }

  static inline uint64_t
  read_section_size(const byte* srs_ptr, size_t srs_file_size, size_t& cursor) {
    uint64_t section_size = read_u64(srs_ptr, cursor);

    if (srs_file_size < cursor + section_size) {
      throw sppark_error{
          EINVAL,
          "SRS file size/layout mismatch. file size is %zu but expected to be at least %zu: ",
          srs_file_size,
          cursor + section_size};
    }

    return section_size;
  }

#ifdef SRS_READ_COEFFS
  static size_t get_batch_size(size_t num_elements, size_t num_threads) {
    size_t batch_size = (num_elements + num_threads - 1) / num_threads;
    batch_size = (batch_size + 64 - 1) / 64;
    return batch_size;
  }

  static inline size_t read_coeff(coeff_t* coeff, const byte* srs_ptr) {
    coeff_file_t unpadded = *(const coeff_file_t*)srs_ptr;
    coeff->m = unpadded.m;
    coeff->c = unpadded.c;
    coeff->s = unpadded.s;
    coeff->value = unpadded.value;
    return coeff_size;
  }

  static void read_coeffs(const gpu_t& gpu, slice_t<coeff_t> coeffs, const byte* srs_ptr) {
    size_t num_coeffs = coeffs.size();
    size_t num_threads = gpu.ncpus();
    size_t batch_size = get_batch_size(num_coeffs, num_threads);

    const byte(*srs)[coeff_size] = reinterpret_cast<decltype(srs)>(srs_ptr);

    gpu.par_map(
        num_coeffs,
        batch_size,
        [&](size_t i) { (void)read_coeff(const_cast<coeff_t*>(&coeffs[i]), srs[i]); },
        num_threads);
  }
#endif

  static inline size_t read_g1_point(affine_t* point, const byte* srs_ptr) {
    *point = *(const affine_t*)srs_ptr;
    return p1_affine_size;
  }

  static inline size_t read_g2_point(affine_fp2_t* point, const byte* srs_ptr) {
    *point = *(const affine_fp2_t*)srs_ptr;
    return p2_affine_size;
  }
  std::string srs_path;

  verifying_key vk;

  size_t num_public, num_vars;

  // TODO: wrap these in something like slice_device_t?
  gpu_ptr_t<affine_t> a, b_g1, c, h;
  gpu_ptr_t<affine_fp2_t> b_g2;

  size_t a_size, b_g1_size, b_g2_size, c_size, h_size;

#ifdef SRS_READ_COEFFS
  std::vector<coeff_t> coeffs;
#endif

  SRS(SRS const&) = delete;
  void operator=(SRS const&) = delete;

public:
  SRS(size_t gpu_id, const char* srs_path) : gpu(select_gpu(gpu_id)), srs_path(srs_path) {
    struct {
      struct {
        uint32_t size;
        size_t off; // in bytes
      } coeffs, a, b_g1, b_g2, c, h;
    } data;

    int srs_file = open(srs_path, O_RDONLY);

    if (srs_file < 0) {
      throw sppark_error{errno, "open(\"%s\") failed: ", srs_path};
    }

    struct stat st;
    fstat(srs_file, &st);
    size_t srs_file_size = st.st_size;

    const byte* srs_ptr =
        (const byte*)mmap(NULL, srs_file_size, PROT_READ, MAP_PRIVATE, srs_file, 0);

    {
      int err = errno;
      close(srs_file);
      if (srs_ptr == MAP_FAILED) {
        throw sppark_error{err, "mmap(\"%s\") failed: ", srs_file};
      }
    }

    try {
      if (memcmp(srs_ptr, "zkey", 4) != 0) {
        throw sppark_error{EINVAL, "srs file's (\"%s\") type is not \"zkey\": ", srs_file};
      }

      size_t cursor = 4;

      // Version number, unused here
      (void)read_u32(srs_ptr, cursor);

      uint32_t num_sections = read_u32(srs_ptr, cursor);
      if (num_sections != 10) {
        throw sppark_error{EINVAL,
                           "srs file (\"%s\") does not have the expected number of sections of 10; "
                           "it has %u sections: ",
                           srs_file,
                           num_sections};
      }

      uint64_t section_size;

      // Section 1: Protocol id
      check_section_id(srs_ptr, cursor, 1);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      uint32_t protocol = read_u32(srs_ptr, cursor);
      if (protocol != 1) {
        throw sppark_error{EINVAL, "srs file's (\"%s\") protocol is not groth16: ", srs_file};
      }

      // Section 2: Metadata and verification key
      check_section_id(srs_ptr, cursor, 2);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      uint32_t q_bytes = read_u32(srs_ptr, cursor);
      cursor += q_bytes;
      uint32_t r_bytes = read_u32(srs_ptr, cursor);
      cursor += r_bytes;

      num_vars = (size_t)read_u32(srs_ptr, cursor);
      num_public = (size_t)read_u32(srs_ptr, cursor);
      size_t domain_size = (size_t)read_u32(srs_ptr, cursor);

      cursor += read_g1_point(&vk.alpha_g1, srs_ptr + cursor);
      cursor += read_g1_point(&vk.beta_g1, srs_ptr + cursor);
      cursor += read_g2_point(&vk.beta_g2, srs_ptr + cursor);
      cursor += read_g2_point(&vk.gamma_g2, srs_ptr + cursor);
      cursor += read_g1_point(&vk.delta_g1, srs_ptr + cursor);
      cursor += read_g2_point(&vk.delta_g2, srs_ptr + cursor);

      // Section 3: Skipped
      check_section_id(srs_ptr, cursor, 3);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      cursor += section_size;

      // Section 4: Coeffs
      check_section_id(srs_ptr, cursor, 4);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.coeffs.size = section_size / sizeof(coeff_file_t);
      data.coeffs.off = cursor + 4; // padded up to 8 bytes
      cursor += section_size;

      // Section 5: Points A
      check_section_id(srs_ptr, cursor, 5);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.a.size = section_size / p1_affine_size;
      data.a.off = cursor;
      cursor += section_size;

      // Section 6: Points B (G1)
      check_section_id(srs_ptr, cursor, 6);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.b_g1.size = section_size / p1_affine_size;
      data.b_g1.off = cursor;
      cursor += section_size;

      // Section 7: Points B (G2)
      check_section_id(srs_ptr, cursor, 7);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.b_g2.size = section_size / p2_affine_size;
      data.b_g2.off = cursor;
      cursor += section_size;

      // Section 8: Points C
      check_section_id(srs_ptr, cursor, 8);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.c.size = section_size / p1_affine_size;
      data.c.off = cursor;
      cursor += section_size;

      // Section 9: Points H
      check_section_id(srs_ptr, cursor, 9);
      section_size = read_section_size(srs_ptr, srs_file_size, cursor);

      data.h.size = section_size / p1_affine_size;
      data.h.off = cursor;

      a_size = data.a.size;
      b_g1_size = data.b_g1.size;
      c_size = data.c.size;
      h_size = data.h.size;
      b_g2_size = data.b_g2.size;

      a = gpu_ptr_t<affine_t>((affine_t*)gpu.Dmalloc(data.a.size * sizeof(affine_t)));
      b_g1 = gpu_ptr_t<affine_t>((affine_t*)gpu.Dmalloc(data.b_g1.size * sizeof(affine_t)));
      c = gpu_ptr_t<affine_t>((affine_t*)gpu.Dmalloc(data.c.size * sizeof(affine_t)));
      h = gpu_ptr_t<affine_t>((affine_t*)gpu.Dmalloc(data.h.size * sizeof(affine_t)));
      b_g2 = gpu_ptr_t<affine_fp2_t>(
          (affine_fp2_t*)gpu.Dmalloc(data.b_g2.size * sizeof(affine_fp2_t)));

      gpu.HtoD(&a[0], srs_ptr + data.a.off, a_size);
      gpu.HtoD(&b_g1[0], srs_ptr + data.b_g1.off, b_g1_size);
      gpu.HtoD(&c[0], srs_ptr + data.c.off, c_size);
      gpu.HtoD(&h[0], srs_ptr + data.h.off, h_size);
      gpu.HtoD(&b_g2[0], srs_ptr + data.b_g2.off, b_g2_size);

#ifdef SRS_READ_COEFFS
      coeffs.resize(data.coeffs.size);
      read_coeffs(gpu, coeffs, srs_ptr + data.coeffs.off);
#endif

      gpu.sync();
      munmap(const_cast<byte*>(srs_ptr), srs_file_size);
    } catch (const sppark_error& e) {
      gpu.sync();
      munmap(const_cast<byte*>(srs_ptr), srs_file_size);

      throw;
    }
  }

#ifdef SRS_READ_COEFFS
  const slice_t<coeff_t> get_coeffs_slice() const {
    return {coeffs.data(), coeffs.size()};
  }
#endif

  const verifying_key& get_vk() const {
    return vk;
  }

  size_t get_num_vars() const {
    return num_vars;
  }

  const gpu_ptr_t<affine_t> get_a() const {
    return a;
  }

  const gpu_ptr_t<affine_t> get_b_g1() const {
    return b_g1;
  }

  const gpu_ptr_t<affine_fp2_t> get_b_g2() const {
    return b_g2;
  }

  const gpu_ptr_t<affine_t> get_c() const {
    return c;
  }

  const gpu_ptr_t<affine_t> get_h() const {
    return h;
  }

  size_t get_a_size() const {
    return a_size;
  }

  size_t get_b_g1_size() const {
    return b_g1_size;
  }

  size_t get_b_g2_size() const {
    return b_g2_size;
  }

  size_t get_c_size() const {
    return c_size;
  }

  size_t get_h_size() const {
    return h_size;
  }

  size_t get_num_public() const {
    return num_public;
  }
};
