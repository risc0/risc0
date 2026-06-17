// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_NTT_LDE_CUH__
#define __SPPARK_NTT_LDE_CUH__

#include <ntt/parameters.cuh>
// Ensure ntt_kernels.cu is included - undefine guard if already defined to force inclusion
#ifdef __NTT_KERNELS_CU__
#undef __NTT_KERNELS_CU__
#undef __NTT_KERNELS_CU__  // Also undefine the closing endif marker if needed
#endif
#include "ntt_kernels.cu"
#include <cuda_runtime.h>
#include <util/gpu_t.cuh>
#include <util/exception.cuh>
#include <util/rusterror.h>

// This matches the original NTT::LDE_powers implementation exactly
class NTTLDE {
private:
    static void LDE_powers(fr_t* inout, bool innt, bool bitrev,
                           uint32_t lg_dsz, uint32_t lg_blowup,
                           stream_t& stream)
    {
        size_t domain_size = (size_t)1 << lg_dsz;
        const uint32_t warpSize = gpu_props(stream).warpSize;
        const auto gen_powers = get_partial_group_gen_powers(innt, stream, group_gen);

        if (domain_size < warpSize)
            LDE_distribute_pows<<<1, domain_size, 0, stream>>>
                (inout, lg_dsz, lg_blowup, bitrev, gen_powers);
        else if (lg_dsz < 32)
            LDE_distribute_pows<<<domain_size / warpSize, warpSize, 0, stream>>>
                (inout, lg_dsz, lg_blowup, bitrev, gen_powers);
        else
            LDE_distribute_pows<<<stream.sm_count(), 1024, 0, stream>>>
                (inout, lg_dsz, lg_blowup, bitrev, gen_powers);

        CUDA_OK(cudaGetLastError());
    }

    static void LDE_shift(fr_t* inout, bool innt, bool bitrev,
                           uint32_t lg_dsz, uint32_t factor,
                           stream_t& stream, fr_t beta, uint32_t poly_count)
    {
        size_t domain_size = (size_t)1 << lg_dsz;
        const uint32_t warpSize = gpu_props(stream).warpSize;
        const auto gen_powers = get_partial_group_gen_powers(innt, stream, beta);

        if (domain_size < warpSize)
            LDE_distribute_shift<<<1, domain_size, 0, stream>>>
                (inout, lg_dsz, factor, bitrev, gen_powers, poly_count);
        else if (lg_dsz < 32) {
            int block = 256;
            int grid  = domain_size / block;
            LDE_distribute_shift<<<grid, block, 0, stream>>>
                (inout, lg_dsz, factor, bitrev, gen_powers, poly_count);
        }
        else
            LDE_distribute_shift<<<stream.sm_count(), 1024, 0, stream>>>
                (inout, lg_dsz, factor, bitrev, gen_powers, poly_count);

        CUDA_OK(cudaGetLastError());
    }

    static void LDE_shift_outplace(fr_t* d_in, fr_t* d_out, bool innt, bool bitrev,
                           uint32_t lg_dsz, uint32_t factor,
                           stream_t& stream, fr_t beta, uint32_t poly_count)
    {
        size_t domain_size = (size_t)1 << lg_dsz;
        const uint32_t warpSize = gpu_props(stream).warpSize;
        const auto gen_powers = get_partial_group_gen_powers(innt, stream, beta);

        if (domain_size < warpSize)
            LDE_distribute_shift_outplace<<<1, domain_size, 0, stream>>>
                (d_in, d_out, lg_dsz, factor, bitrev, gen_powers, poly_count);
        else if (lg_dsz < 32) {
            int block = 256;
            int grid  = domain_size / (block*4);
            LDE_distribute_shift_outplace<<<grid, block, 0, stream>>>
                (d_in, d_out, lg_dsz, factor, bitrev, gen_powers, poly_count);
        }
        else
            LDE_distribute_shift_outplace<<<stream.sm_count(), 1024, 0, stream>>>
                (d_in, d_out, lg_dsz, factor, bitrev, gen_powers, poly_count);

        CUDA_OK(cudaGetLastError());
    }

    static auto get_partial_group_gen_powers(bool innt, stream_t& stream, fr_t beta) -> fr_t (*)[WINDOW_SIZE]
    {
        static fr_t (*partial_group_gen_powers)[WINDOW_SIZE] = nullptr;
        static fr_t* partial_twiddles_base = nullptr;  // Store base pointer for deallocation
        static fr_t beta_prv(0);

        if (beta_prv != beta) {
            // Free old memory if it exists
            if (partial_twiddles_base != nullptr) {
                CUDA_OK(cudaFree(partial_twiddles_base));
                partial_twiddles_base = nullptr;
                partial_group_gen_powers = nullptr;
            }

            const size_t partial_sz = WINDOW_NUM * WINDOW_SIZE;
            partial_twiddles_base = reinterpret_cast<fr_t*>(stream.Dmalloc(2 * partial_sz * sizeof(fr_t)));
            partial_group_gen_powers = reinterpret_cast<decltype(partial_group_gen_powers)>(&partial_twiddles_base[WINDOW_NUM]);

            // Generate partial_group_gen_powers using group_gen (which is 3 for Baby Bear, or group_gen_inverse if innt)
            // const fr_t gen = innt ? group_gen_inverse : group_gen; // commented by He
            generate_partial_twiddles<<<WINDOW_SIZE/32, 32, 0, stream>>>
                (partial_group_gen_powers, beta);
            CUDA_OK(cudaGetLastError());
            CUDA_OK(cudaStreamSynchronize(stream));

            beta_prv = beta;
        }

        return partial_group_gen_powers;
    }

    static void bit_rev(fr_t* d_out, const fr_t* d_inp,
        uint32_t lg_domain_size, stream_t& stream)
{
assert(lg_domain_size <= MAX_LG_DOMAIN_SIZE);

size_t domain_size = (size_t)1 << lg_domain_size;
// aim to read 4 cache lines of consecutive data per read
const uint32_t Z_COUNT = 256 / sizeof(fr_t);
// const uint32_t Z_COUNT = 256 / sizeof(fr_t);
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

public:
    static void LDE_powers(stream_t& stream, fr_t* d_inout, uint32_t lg_domain_size)
    {
        LDE_powers(d_inout, false, true, lg_domain_size, 0, stream);
    }

    // Overload to accept gpu_t (which can be implicitly converted to stream_t&)
    static void LDE_powers(const gpu_t& gpu, fr_t* d_inout, uint32_t lg_domain_size)
    {
        stream_t& stream = const_cast<gpu_t&>(gpu);
        LDE_powers(stream, d_inout, lg_domain_size);
    }

    static void LDE_shift(stream_t& stream, fr_t* d_inout, uint32_t lg_domain_size, fr_t beta, uint32_t factor, uint32_t poly_count)
    {
        bool bitrev = true;
        bool prvrev = factor & 0x100;
        bool postrev = factor & 0x80;

        factor &= ~0x80;
        factor &= ~0x100;
        uint32_t size = 1<<lg_domain_size;

        if (prvrev) {
            for (uint32_t i=0; i<poly_count; i++)
                bit_rev(&d_inout[i*size], &d_inout[i*size], lg_domain_size, stream);
        }
        LDE_shift(d_inout, false, bitrev, lg_domain_size, factor, stream, beta, poly_count);
        if (postrev) {
            for (uint32_t i=0; i<poly_count; i++)
                bit_rev(&d_inout[i*size], &d_inout[i*size], lg_domain_size, stream);
        }
    }

    static void LDE_shift_outplace(stream_t& stream, fr_t* d_in, fr_t* d_out, uint32_t lg_domain_size, fr_t beta, uint32_t factor, uint32_t poly_count)
    {
        bool bitrev = true;
        bool prvrev = factor & 0x100;
        bool postrev = factor & 0x80;

        factor &= ~0x80;
        factor &= ~0x100;
        uint32_t size = 1<<lg_domain_size;

        if (prvrev) {
            for (uint32_t i=0; i<poly_count; i++)
                bit_rev(&d_in[i*size], &d_in[i*size], lg_domain_size, stream);
        }
        LDE_shift_outplace(d_in, d_out, false, bitrev, lg_domain_size, factor, stream, beta, poly_count);
        if (postrev) {
            for (uint32_t i=0; i<poly_count; i++)
                bit_rev(&d_in[i*size], &d_in[i*size], lg_domain_size, stream);
        }
    }

    static void LDE_coeffs_bitrev(stream_t& stream, fr_t* d_inout, uint32_t lg_domain_size)
    {
        bit_rev(&d_inout[0], &d_inout[0], lg_domain_size, stream);
    }

    // Overload to accept gpu_t (which can be implicitly converted to stream_t&)
    static void LDE_shift(const gpu_t& gpu, fr_t* d_inout, uint32_t lg_domain_size, fr_t beta, uint32_t factor, uint32_t poly_count)
    {
        stream_t& stream = const_cast<gpu_t&>(gpu);
        LDE_shift(stream, d_inout, lg_domain_size, beta, factor, poly_count);
    }

    // Overload to accept gpu_t (which can be implicitly converted to stream_t&)
    static void LDE_shift_outplace(const gpu_t& gpu, fr_t* d_in, fr_t* d_out, uint32_t lg_domain_size, fr_t beta, uint32_t factor, uint32_t poly_count)
    {
        stream_t& stream = const_cast<gpu_t&>(gpu);
        LDE_shift_outplace(stream, d_in, d_out, lg_domain_size, beta, factor, poly_count);
    }

    static void LDE_coeffs_bitrev(const gpu_t& gpu, fr_t* d_inout, uint32_t lg_domain_size)
    {
        stream_t& stream = const_cast<gpu_t&>(gpu);
        LDE_coeffs_bitrev(stream, d_inout, lg_domain_size);
    }

};

#endif // __SPPARK_NTT_LDE_CUH__

