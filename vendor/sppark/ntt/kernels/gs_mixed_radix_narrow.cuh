// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

template<int z_count, bool coalesced = false, class fr_t>
__launch_bounds__(768, 1) __global__
void _GS_NTT(const unsigned int radix, const unsigned int lg_domain_size,
             const unsigned int stage, const unsigned int iterations,
             fr_t* d_inout, const fr_t (*d_partial_twiddles)[WINDOW_SIZE],
             const fr_t (*d_plus_one_twiddles)[1024],
             const fr_t* d_radix6_twiddles, const fr_t* d_radixX_twiddles,
             bool is_intt, const fr_t d_domain_size_inverse)
{
#if (__CUDACC_VER_MAJOR__-0) >= 11 || defined(__clang__)
    __builtin_assume(lg_domain_size <= MAX_LG_DOMAIN_SIZE);
    __builtin_assume(radix <= 10);
    __builtin_assume(iterations <= radix);
    __builtin_assume(stage <= lg_domain_size && stage >= iterations);
#endif
    extern __shared__ fr_t shared_exchange[];

    index_t tid = threadIdx.x + blockDim.x * (index_t)blockIdx.x;

    const index_t diff_mask = (1 << (iterations - 1)) - 1;
    const index_t inp_mask = ((index_t)1 << (stage - 1)) - 1;
    const index_t out_mask = ((index_t)1 << (stage - iterations)) - 1;

    const index_t tiz = (tid & ~diff_mask) * z_count + (tid & diff_mask);

    // rearrange |tiz|'s bits
    index_t idx0 = (tiz & ~inp_mask) * 2;
    idx0 += (tiz << (stage - iterations)) & inp_mask;
    idx0 += (tiz >> (iterations - 1)) & out_mask;
    index_t idx1 = idx0 + ((index_t)1 << (stage - 1));

    fr_t r[2][z_count];

    if (coalesced) {
        coalesced_load<z_count>(r[0], d_inout, idx0, stage - iterations);
        coalesced_load<z_count>(r[1], d_inout, idx1, stage - iterations);
        transpose<z_count>(r[0]);
        transpose<z_count>(r[1]);
    } else {
        unsigned int z_shift = out_mask==0 ? iterations : 0;
        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            r[0][z] = d_inout[idx0 + (z << z_shift)];
            r[1][z] = d_inout[idx1 + (z << z_shift)];
        }
    }

    #pragma unroll 1
    for (unsigned int s = iterations; --s >= 6;) {
        unsigned int laneMask = 1 << (s - 1);
        unsigned int thrdMask = (1 << s) - 1;
        unsigned int rank = threadIdx.x & thrdMask;
        bool pos = rank < laneMask;

        fr_t root = d_radixX_twiddles[rank << (radix - (s + 1))];

        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            fr_t t = root * (r[0][z] - r[1][z]);
            r[0][z] = r[0][z] + r[1][z];
            r[1][z] = t;
        }

        fr_t (*xchg)[z_count] = reinterpret_cast<decltype(xchg)>(shared_exchange);

        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            fr_t t = fr_t::csel(r[1][z], r[0][z], pos);
            xchg[threadIdx.x][z] = t;
        }

        __syncthreads();

        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            fr_t t = xchg[threadIdx.x ^ laneMask][z];
            r[0][z] = fr_t::csel(r[0][z], t, pos);
            r[1][z] = fr_t::csel(t, r[1][z], pos);
        }

        __syncthreads();

        noop();
    }

    #pragma unroll 1
    for (unsigned int s = min(iterations, 6u); --s >= 1;) {
        unsigned int laneMask = 1 << (s - 1);
        unsigned int thrdMask = (1 << s) - 1;
        unsigned int rank = threadIdx.x & thrdMask;
        bool pos = rank < laneMask;

        fr_t root = d_radix6_twiddles[rank << (6 - (s + 1))];

        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            fr_t t = root * (r[0][z] - r[1][z]);
            r[0][z] = r[0][z] + r[1][z];
            r[1][z] = t;

            t = fr_t::csel(r[1][z], r[0][z], pos);

            t.shfl_bfly(laneMask);

            r[0][z] = fr_t::csel(r[0][z], t, pos);
            r[1][z] = fr_t::csel(t, r[1][z], pos);
        }
        noop();
    }

    #pragma unroll
    for (int z = 0; z < z_count; z++) {
        fr_t t = r[0][z] - r[1][z];
        r[0][z] = r[0][z] + r[1][z];
        r[1][z] = t;
    }
    noop();

    if (stage - iterations != 0) {
        index_t thread_ntt_pos = (tiz & inp_mask) >> (iterations - 1);
        unsigned int thread_ntt_idx = (tiz & diff_mask) * 2;
        unsigned int nbits = MAX_LG_DOMAIN_SIZE - (stage - iterations);
        index_t idx0 = bit_rev(thread_ntt_idx, nbits);
        index_t root_idx0 = idx0 * thread_ntt_pos;
        index_t root_idx1 = root_idx0 + (thread_ntt_pos << (nbits - 1));

        fr_t first_root, second_root;
        get_intermediate_roots(first_root, second_root,
                               root_idx0, root_idx1, d_partial_twiddles);
        r[0][0] = r[0][0] * first_root;
        r[1][0] = r[1][0] * second_root;

        if (z_count > 1) {
            unsigned int off = nbits >= 10 ? (nbits - 10) : 0;
            unsigned int scale = nbits >= 10 ? 0 : (10 - nbits);

            thread_ntt_idx <<= scale;
            fr_t first_root_z = d_plus_one_twiddles[off][thread_ntt_idx];
            fr_t second_root_z = d_plus_one_twiddles[off][thread_ntt_idx + (1<<scale)];

            #pragma unroll
            for (int z = 1; z < z_count; z++) {
                first_root *= first_root_z;
                second_root *= second_root_z;
                r[0][z] = r[0][z] * first_root;
                r[1][z] = r[1][z] * second_root;
            }
        }
    }

    if (is_intt && stage == iterations) {
        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            r[0][z] = r[0][z] * d_domain_size_inverse;
            r[1][z] = r[1][z] * d_domain_size_inverse;
        }
    }

    // rotate "iterations" bits in indices
    index_t mask = (index_t)((1 << iterations) - 1) << (stage - iterations);
    index_t rotw = idx0 & mask;
    rotw = (rotw << 1) | (rotw >> (iterations - 1));
    idx0 = (idx0 & ~mask) | (rotw & mask);
    rotw = idx1 & mask;
    rotw = (rotw << 1) | (rotw >> (iterations - 1));
    idx1 = (idx1 & ~mask) | (rotw & mask);

    if (coalesced) {
        transpose<z_count>(r[0]);
        transpose<z_count>(r[1]);
        coalesced_store<z_count>(d_inout, idx0, r[0], stage - iterations + 1);
        coalesced_store<z_count>(d_inout, idx1, r[1], stage - iterations + 1);
    } else {
        unsigned int z_shift = out_mask==0 ? iterations : 0;
        #pragma unroll
        for (int z = 0; z < z_count; z++) {
            d_inout[idx0 + (z << z_shift)] = r[0][z];
            d_inout[idx1 + (z << z_shift)] = r[1][z];
        }
    }
}

class GS_launcher {
    fr_t* d_inout;
    const int lg_domain_size;
    bool is_intt;
    int stage;
    const NTTParameters& ntt_parameters;
    const stream_t& stream;

public:
    GS_launcher(fr_t* d_ptr, int lg_dsz, bool intt,
                const NTTParameters& params, const stream_t& s)
      : d_inout(d_ptr), lg_domain_size(lg_dsz), is_intt(intt), stage(lg_dsz),
        ntt_parameters(params), stream(s)
    {}

    void step(int iterations)
    {
        assert(iterations <= 10);

        const int radix = iterations < 6 ? 6 : iterations;

        index_t num_threads = (index_t)1 << (lg_domain_size - 1);
        index_t block_size = 1 << (radix - 1);
        index_t num_blocks;

        block_size = (num_threads <= block_size) ? num_threads : block_size;
        num_blocks = (num_threads + block_size - 1) / block_size;

        assert(num_blocks == (unsigned int)num_blocks);

        const int Z_COUNT = 256/8/sizeof(fr_t);
        size_t shared_sz = sizeof(fr_t) << (radix - 1);

        #define NTT_ARGUMENTS radix, lg_domain_size, stage, iterations, \
                d_inout, ntt_parameters.partial_twiddles, \
                ntt_parameters.plus_one_twiddles, \
                ntt_parameters.twiddles[0], ntt_parameters.twiddles[radix-6], \
                is_intt, domain_size_inverse[lg_domain_size]

        if (num_blocks < Z_COUNT)
            _GS_NTT<1><<<num_blocks, block_size, shared_sz, stream>>>(NTT_ARGUMENTS);
        else if (stage == iterations || lg_domain_size < 12)
            _GS_NTT<Z_COUNT><<<num_blocks/Z_COUNT, block_size, Z_COUNT*shared_sz, stream>>>(NTT_ARGUMENTS);
        else
            _GS_NTT<Z_COUNT, true><<<num_blocks/Z_COUNT, block_size, Z_COUNT*shared_sz, stream>>>(NTT_ARGUMENTS);

        #undef NTT_ARGUMENTS

        stage -= iterations;
    }
};
