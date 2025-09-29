// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_NTT_NTT_CUH__
#define __SPPARK_NTT_NTT_CUH__

#include <cassert>
#include <iostream>

#include <util/exception.cuh>
#include <util/rusterror.h>
#include <util/gpu_t.cuh>

#if defined(__NVCC__)
# define noop()
#elif defined(__HIPCC__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wunused-function"
__device__ __noinline__ static void noop() { asm(""); }
# pragma clang diagnostic push
#endif

#include "parameters.cuh"
#include "kernels.cuh"

#ifdef noop
# undef noop
#endif

class NTT {
public:
    enum class InputOutputOrder { NN, NR, RN, RR };
    enum class Direction { forward, inverse };
    enum class Type { standard, coset };
    enum class Algorithm { GS, CT };

protected:
    static void bit_rev(fr_t* d_out, const fr_t* d_inp,
                        uint32_t lg_domain_size, stream_t& stream)
    {
        assert(lg_domain_size <= MAX_LG_DOMAIN_SIZE);

        size_t domain_size = (size_t)1 << lg_domain_size;
        // aim to read 4 cache lines of consecutive data per read
        const uint32_t Z_COUNT = 256 / sizeof(fr_t);
        const uint32_t warpSize = gpu_props(stream).warpSize;
        const uint32_t bsize = Z_COUNT>warpSize ? Z_COUNT : warpSize;
#ifdef __HIPCC__
        const uint32_t lg_switch = 17;
#else
        const uint32_t lg_switch = 32;
#endif

        if (domain_size <= 1024)
            bit_rev_permutation<<<1, domain_size, 0, stream>>>
                               (d_out, d_inp, lg_domain_size);
        else if (domain_size < bsize * Z_COUNT)
            bit_rev_permutation<<<domain_size / bsize, bsize, 0, stream>>>
                               (d_out, d_inp, lg_domain_size);
        else if (Z_COUNT > warpSize || lg_domain_size <= lg_switch)
            bit_rev_permutation_z<Z_COUNT><<<domain_size / Z_COUNT / bsize, bsize,
                                             bsize * Z_COUNT * sizeof(fr_t),
                                             stream>>>
                                 (d_out, d_inp, lg_domain_size);
        else
            // Those GPUs that can reserve 96KB of shared memory can
            // schedule 2 blocks to each SM...
            bit_rev_permutation_z<Z_COUNT><<<stream.sm_count()*2, 192,
                                             192 * Z_COUNT * sizeof(fr_t),
                                             stream>>>
                                 (d_out, d_inp, lg_domain_size);

        CUDA_OK(cudaGetLastError());
    }

private:
    static void LDE_powers(fr_t* inout, bool innt, bool bitrev,
                           uint32_t lg_dsz, uint32_t lg_blowup,
                           stream_t& stream)
    {
        size_t domain_size = (size_t)1 << lg_dsz;
        const uint32_t warpSize = gpu_props(stream).warpSize;
        const auto gen_powers =
            NTTParameters::all(innt)[stream].partial_group_gen_powers;

        if (domain_size < warpSize)
            LDE_distribute_powers<<<1, domain_size, 0, stream>>>
                                 (inout, lg_dsz, lg_blowup, bitrev, gen_powers);
        else if (lg_dsz < 32)
            LDE_distribute_powers<<<domain_size / warpSize, warpSize, 0, stream>>>
                                 (inout, lg_dsz, lg_blowup, bitrev, gen_powers);
        else
            LDE_distribute_powers<<<stream.sm_count(), 1024, 0, stream>>>
                                 (inout, lg_dsz, lg_blowup, bitrev, gen_powers);

        CUDA_OK(cudaGetLastError());
    }

    static void CT_NTT(fr_t* d_inout, const int lg_domain_size, bool intt,
                       const NTTParameters& ntt_parameters,
                       const stream_t& stream)
    {
        CT_launcher params{d_inout, lg_domain_size, intt, ntt_parameters, stream};

        if (lg_domain_size <= 10) {
            params.step(lg_domain_size);
        } else if (lg_domain_size <= 18) {
            int step = lg_domain_size / 2;
            params.step(step + lg_domain_size % 2);
            params.step(step);
        } else if (lg_domain_size <= 30) {
            int step = lg_domain_size / 3;
            int rem = lg_domain_size % 3;
            params.step(step);
            params.step(step + (lg_domain_size == 29 ? 1 : 0));
            params.step(step + (lg_domain_size == 29 ? 1 : rem));
        } else if (lg_domain_size <= 40) {
            int step = lg_domain_size / 4;
            int rem = lg_domain_size % 4;
            params.step(step);
            params.step(step + (rem > 2));
            params.step(step + (rem > 1));
            params.step(step + (rem > 0));
        } else {
            assert(false);
        }
    }

    static void GS_NTT(fr_t* d_inout, const int lg_domain_size, const bool is_intt,
                       const NTTParameters& ntt_parameters,
                       const stream_t& stream)
    {
        GS_launcher params{d_inout, lg_domain_size, is_intt, ntt_parameters, stream};

        if (lg_domain_size <= 10) {
            params.step(lg_domain_size);
        } else if (lg_domain_size <= 18) {
            int step = lg_domain_size / 2;
            params.step(step);
            params.step(step + lg_domain_size % 2);
        } else if (lg_domain_size <= 30) {
            int step = lg_domain_size / 3;
            int rem = lg_domain_size % 3;
            params.step(step + (lg_domain_size == 29 ? 1 : rem));
            params.step(step + (lg_domain_size == 29 ? 1 : 0));
            params.step(step);
        } else if (lg_domain_size <= 40) {
            int step = lg_domain_size / 4;
            int rem = lg_domain_size % 4;
            params.step(step + (rem > 0));
            params.step(step + (rem > 1));
            params.step(step + (rem > 2));
            params.step(step);
        } else {
            assert(false);
        }
    }

protected:
    static void NTT_internal(fr_t* d_inout, uint32_t lg_domain_size,
                             InputOutputOrder order, Direction direction,
                             Type type, stream_t& stream)
    {
        // Pick an NTT algorithm based on the input order and the desired output
        // order of the data. In certain cases, bit reversal can be avoided which
        // results in a considerable performance gain.

        const bool intt = direction == Direction::inverse;
        const auto& ntt_parameters = NTTParameters::all(intt)[stream];
        bool bitrev;
        Algorithm algorithm;

        switch (order) {
            case InputOutputOrder::NN:
                bit_rev(d_inout, d_inout, lg_domain_size, stream);
                bitrev = true;
                algorithm = Algorithm::CT;
                break;
            case InputOutputOrder::NR:
                bitrev = false;
                algorithm = Algorithm::GS;
                break;
            case InputOutputOrder::RN:
                bitrev = true;
                algorithm = Algorithm::CT;
                break;
            case InputOutputOrder::RR:
                bitrev = true;
                algorithm = Algorithm::GS;
                break;
            default:
                assert(false);
        }

        if (!intt && type == Type::coset)
            LDE_powers(d_inout, intt, bitrev, lg_domain_size, 0, stream);

        switch (algorithm) {
            case Algorithm::GS:
                GS_NTT(d_inout, lg_domain_size, intt, ntt_parameters, stream);
                break;
            case Algorithm::CT:
                CT_NTT(d_inout, lg_domain_size, intt, ntt_parameters, stream);
                break;
        }

        if (intt && type == Type::coset)
            LDE_powers(d_inout, intt, !bitrev, lg_domain_size, 0, stream);

        if (order == InputOutputOrder::RR)
            bit_rev(d_inout, d_inout, lg_domain_size, stream);
    }

public:
    static RustError Base(const gpu_t& gpu, fr_t* inout, uint32_t lg_domain_size,
                          InputOutputOrder order, Direction direction,
                          Type type)
    {
        if (lg_domain_size == 0)
            return RustError{cudaSuccess};

        try {
            gpu.select();

            size_t domain_size = (size_t)1 << lg_domain_size;
            dev_ptr_t<fr_t> d_inout{domain_size, gpu};
            gpu.HtoD(&d_inout[0], inout, domain_size);

            NTT_internal(&d_inout[0], lg_domain_size, order, direction, type, gpu);

            gpu.DtoH(inout, &d_inout[0], domain_size);
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

protected:
    static void LDE_launch(stream_t& stream,
                           fr_t* ext_domain_data, fr_t* domain_data,
                           const fr_t (*gen_powers)[WINDOW_SIZE],
                           uint32_t lg_domain_size, uint32_t lg_blowup,
                           bool perform_shift = true, bool ext_pow = false)
    {
        assert(lg_domain_size + lg_blowup <= MAX_LG_DOMAIN_SIZE);
        size_t domain_size = (size_t)1 << lg_domain_size;

        // Determine the max power of 2 SM count
        size_t kernel_sms = stream.sm_count();
        while (kernel_sms & (kernel_sms - 1))
            kernel_sms -= (kernel_sms & (0 - kernel_sms));

        size_t device_max_threads = kernel_sms * 1024;
        uint32_t num_blocks, block_size;

        if (device_max_threads < domain_size) {
            num_blocks = kernel_sms;
            block_size = 1024;
        } else if (domain_size < 1024) {
            num_blocks = 1;
            block_size = domain_size;
        } else {
            num_blocks = domain_size / 1024;
            block_size = 1024;
        }

        stream.launch_coop(LDE_spread_distribute_powers,
                        {dim3(num_blocks), dim3(block_size),
                         sizeof(fr_t) * block_size},
                        ext_domain_data, domain_data, gen_powers,
                        lg_domain_size, lg_blowup, perform_shift, ext_pow);
    }

public:
    static RustError LDE_aux(const gpu_t& gpu, fr_t* inout,
                             uint32_t lg_domain_size, uint32_t lg_blowup,
                             fr_t *aux_out = nullptr)
    {
        try {
            size_t domain_size = (size_t)1 << lg_domain_size;
            size_t ext_domain_size = domain_size << lg_blowup;
            size_t aux_size = aux_out != nullptr ? domain_size : 0;
            // The 2nd to last 'domain_size' chunk will hold the original data
            // The last chunk will get the bit reversed iNTT data
            dev_ptr_t<fr_t> d_inout{ext_domain_size + aux_size, gpu}; // + domain_size for aux buffer
            fr_t* aux_data = &d_inout[ext_domain_size];
            fr_t* domain_data = &d_inout[ext_domain_size - domain_size]; // aligned to the end
            fr_t* ext_domain_data = &d_inout[0];

            gpu.HtoD(domain_data, inout, domain_size);

            NTT_internal(domain_data, lg_domain_size,
                         InputOutputOrder::NR, Direction::inverse,
                         Type::standard, gpu);

            const auto gen_powers =
                NTTParameters::all()[gpu.id()].partial_group_gen_powers;

            event_t sync_event;

            if (aux_out != nullptr) {
                bit_rev(aux_data, domain_data, lg_domain_size, gpu);
                sync_event.record(gpu);
            }

            LDE_launch(gpu, ext_domain_data, domain_data, gen_powers,
                       lg_domain_size, lg_blowup);

            // NTT - RN
            NTT_internal(ext_domain_data, lg_domain_size + lg_blowup,
                         InputOutputOrder::RN, Direction::forward,
                         Type::standard, gpu);

            if (aux_out != nullptr) {
                sync_event.wait(gpu[0]);
                gpu[0].DtoH(aux_out, aux_data, aux_size);
            }
            gpu.DtoH(inout, ext_domain_data, ext_domain_size);
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

    static RustError LDE(const gpu_t& gpu, fr_t* inout,
                         uint32_t lg_domain_size, uint32_t lg_blowup)
    {   return LDE_aux(gpu, inout, lg_domain_size, lg_blowup);   }

    static void Base_dev_ptr(stream_t& stream, fr_t* d_inout,
                             uint32_t lg_domain_size, InputOutputOrder order,
                             Direction direction, Type type)
    {
        NTT_internal(&d_inout[0], lg_domain_size, order, direction, type,
                     stream);
    }

    static void LDE_powers(stream_t& stream, fr_t* d_inout,
                           uint32_t lg_domain_size)
    {
        LDE_powers(d_inout, false, true, lg_domain_size, 0, stream);
    }

    // If d_out and d_in overlap, d_out is expected to encompass d_in and
    // d_in is expected to be aligned to the end of d_out
    // The input is expected to be in bit-reversed order
    static void LDE_expand(stream_t& stream, fr_t* d_out, fr_t* d_in,
                           uint32_t lg_domain_size, uint32_t lg_blowup)
    {
        LDE_launch(stream, d_out, d_in, NULL, lg_domain_size, lg_blowup, false);
    }
};
#endif
