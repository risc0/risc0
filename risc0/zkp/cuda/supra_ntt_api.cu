#ifdef FEATURE_BABY_BEAR
# include <ff/baby_bear.hpp>
#endif

#include <ntt/ntt.cuh>

#ifndef __CUDA_ARCH__

extern "C"
RustError::by_value sppark_init()
{
    uint32_t lg_domain_size = 1;
    uint32_t domain_size = 1U << lg_domain_size;

    std::vector<fr_t> inout{domain_size};
    inout[0] = fr_t(1); inout[1] = fr_t(1);

    const gpu_t& gpu = select_gpu();

    try {
        NTT::Base(gpu, &inout[0], lg_domain_size, NTT::InputOutputOrder::NR,
                  NTT::Direction::forward, NTT::Type::standard);
        gpu.sync();
    } catch (const cuda_error& e) {
        gpu.sync();
    #ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
        return RustError{e.code(), e.what()};
    #else
        return RustError{e.code()};
    #endif
    }

    return RustError{cudaSuccess};
}

extern "C"
RustError::by_value batch_expand(fr_t* d_out, fr_t* d_in, uint32_t lg_domain_size,
                                 uint32_t lg_blowup, uint32_t poly_count)
{
    if (lg_domain_size == 0)
        return RustError{cudaSuccess};

    uint32_t domain_size = 1U << lg_domain_size;
    uint32_t ext_domain_size = domain_size << lg_blowup;

    cudaDeviceSynchronize();
    const gpu_t& gpu = select_gpu();

    // Determine the max power of 2 SM count
    size_t kernel_sms = gpu.sm_count();
    while (kernel_sms & (kernel_sms - 1))
        kernel_sms -= (kernel_sms & (0 - kernel_sms));

    try {
        for (size_t c = 0; c < poly_count; c++) {
            NTT::batch_expand(gpu, kernel_sms, &d_out[c * ext_domain_size],
                              &d_in[c * domain_size], lg_domain_size,
                              lg_blowup);
        }

        gpu.sync();
    } catch (const cuda_error& e) {
        gpu.sync();
#ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
        return RustError{e.code(), e.what()};
#else
        return RustError{e.code()};
#endif
    }

    return RustError{cudaSuccess};
}

extern "C"
RustError::by_value batch_NTT(fr_t* d_inout, uint32_t lg_domain_size,
                              uint32_t poly_count)
{
    if (lg_domain_size == 0)
        return RustError{cudaSuccess};

    uint32_t domain_size = 1U << lg_domain_size;

    cudaDeviceSynchronize();
    const gpu_t& gpu = select_gpu();

    try {
        for (size_t c = 0; c < poly_count; c++) {
            NTT::Base_on_device(gpu, &d_inout[c * domain_size], lg_domain_size,
                                NTT::InputOutputOrder::RN,
                                NTT::Direction::forward, NTT::Type::standard);
        }

        gpu.sync();
    } catch (const cuda_error& e) {
        gpu.sync();
#ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
        return RustError{e.code(), e.what()};
#else
        return RustError{e.code()};
#endif
    }

    return RustError{cudaSuccess};
}

extern "C"
RustError::by_value batch_iNTT(fr_t* d_inout, uint32_t lg_domain_size,
                               uint32_t poly_count)
{
    if (lg_domain_size == 0)
        return RustError{cudaSuccess};

    uint32_t domain_size = 1U << lg_domain_size;

    cudaDeviceSynchronize();
    const gpu_t& gpu = select_gpu();

    try {
        for (size_t c = 0; c < poly_count; c++) {
            NTT::Base_on_device(gpu, &d_inout[c * domain_size], lg_domain_size,
                                NTT::InputOutputOrder::NR,
                                NTT::Direction::inverse, NTT::Type::standard);
        }

        gpu.sync();
    } catch (const cuda_error& e) {
        gpu.sync();
#ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
        return RustError{e.code(), e.what()};
#else
        return RustError{e.code()};
#endif
    }

    return RustError{cudaSuccess};
}

extern "C"
RustError::by_value batch_zk_shift(fr_t* d_inout, uint32_t lg_domain_size,
                                   uint32_t poly_count)
{
    if (lg_domain_size == 0)
        return RustError{cudaSuccess};

    uint32_t domain_size = 1U << lg_domain_size;

    cudaDeviceSynchronize();
    const gpu_t& gpu = select_gpu();

    try {
        for (size_t c = 0; c < poly_count; c++) {
            NTT::zk_shift(gpu, &d_inout[c * domain_size], lg_domain_size);
        }

        gpu.sync();
    } catch (const cuda_error& e) {
        gpu.sync();
#ifdef TAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE
        return RustError{e.code(), e.what()};
#else
        return RustError{e.code()};
#endif
    }

    return RustError{cudaSuccess};
}

#endif
