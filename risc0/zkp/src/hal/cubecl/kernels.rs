// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! ZKP elementwise GPU kernels for cubecl.
//!
//! Simple 1-thread-per-element kernels: add, copy, zeroize, gather, scatter,
//! region copy, batch expand, zk_shift, and extension field operations.

use cubecl::prelude::*;

use crate::hal::cubecl::ext_field::{bb4_add, bb4_mul, bb4_mul_scalar, bb_pow};
use crate::hal::cubecl::field::{bb_add, bb_mul};

/// Elementwise addition: out[i] = x[i] + y[i] in Baby Bear field.
#[cube(launch_unchecked)]
pub fn eltwise_add(out: &mut Array<u32>, x: &Array<u32>, y: &Array<u32>, #[comptime] count: u32) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        out[idx as usize] = bb_add(x[idx as usize], y[idx as usize]);
    }
}

/// Elementwise copy: out[i] = input[i].
#[cube(launch_unchecked)]
pub fn eltwise_copy(out: &mut Array<u32>, input: &Array<u32>, #[comptime] count: u32) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        out[idx as usize] = input[idx as usize];
    }
}

/// Zeroize INVALID values: replaces 0xFFFFFFFF with 0, keeps valid values.
#[cube(launch_unchecked)]
pub fn eltwise_zeroize(elems: &mut Array<u32>, #[comptime] count: u32) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        let val = elems[idx as usize];
        if val == 0xffffffffu32 {
            elems[idx as usize] = 0u32;
        }
    }
}

/// Gather with stride: dst[gid] = src[gid * stride + idx].
#[cube(launch_unchecked)]
pub fn gather_sample(
    dst: &mut Array<u32>,
    src: &Array<u32>,
    #[comptime] idx: u32,
    #[comptime] size: u32,
    #[comptime] stride: u32,
) {
    let gid = ABSOLUTE_POS as u32;
    if gid < size {
        dst[gid as usize] = src[(gid * stride + idx) as usize];
    }
}

/// Scatter values into target buffer using index/offset indirection.
///
/// For each gid in 0..count: copies values[idx..next_idx] to into[offsets[idx..next_idx]]
/// where idx = index[gid], next_idx = index[gid+1].
#[cube(launch_unchecked)]
pub fn scatter(
    into: &mut Array<u32>,
    index: &Array<u32>,
    offsets: &Array<u32>,
    values: &Array<u32>,
    #[comptime] count: u32,
) {
    let gid = ABSOLUTE_POS as u32;
    if gid < count {
        let start = index[gid as usize];
        let end = index[(gid + 1u32) as usize];
        let mut i = start;
        while i < end {
            let off = offsets[i as usize];
            let val = values[i as usize];
            into[off as usize] = val;
            i = i + 1u32;
        }
    }
}

/// 2D strided region copy.
///
/// For each row, copies from_cols elements:
/// into[into_offset + row*into_stride + col] = from[from_offset + row*from_stride + col]
#[cube(launch_unchecked)]
pub fn eltwise_copy_region(
    into: &mut Array<u32>,
    from: &Array<u32>,
    #[comptime] from_rows: u32,
    #[comptime] from_cols: u32,
    #[comptime] from_offset: u32,
    #[comptime] from_stride: u32,
    #[comptime] into_offset: u32,
    #[comptime] into_stride: u32,
) {
    let row = ABSOLUTE_POS as u32;
    if row < from_rows {
        for col in 0..from_cols {
            let dst_idx = (into_offset + row * into_stride + col) as usize;
            let src_idx = (from_offset + row * from_stride + col) as usize;
            into[dst_idx] = from[src_idx];
        }
    }
}

/// Batch expand: zero-padded polynomial expansion.
///
/// output[row * out_size + col] = input[row * in_size + (col >> expand_bits)]
#[cube(launch_unchecked)]
pub fn batch_expand(
    output: &mut Array<u32>,
    input: &Array<u32>,
    #[comptime] in_size: u32,
    #[comptime] out_size: u32,
    #[comptime] expand_bits: u32,
) {
    let idx = ABSOLUTE_POS as u32;
    let row = idx / out_size;
    let col = idx % out_size;
    output[idx as usize] = input[(row * in_size + (col >> expand_bits)) as usize];
}

/// ZK shift: multiply each coefficient by pow(3, bit_reverse(position)).
///
/// For each polynomial row of size `count`, shifts coefficients by
/// random-looking factors derived from powers of 3 with bit-reversed exponents.
#[cube(launch_unchecked)]
pub fn zk_shift(
    io: &mut Array<u32>,
    #[comptime] count: u32,
    #[comptime] n_bits: u32,
    #[comptime] poly_count: u32,
    #[comptime] three_mont: u32,
) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count * poly_count {
        let pos = idx % count;
        // Bit-reverse pos within n_bits
        let mut rev: u32 = 0u32;
        let mut v: u32 = pos;
        for _bit in 0..n_bits {
            rev = (rev << 1u32) | (v & 1u32);
            v = v >> 1u32;
        }
        // Multiply by 3^rev in Montgomery form
        let factor = bb_pow(three_mont, rev);
        io[idx as usize] = bb_mul(io[idx as usize], factor);
    }
}

/// Sum extension field elements: adds `to_add` ExtElem values per output position.
///
/// Input layout: AoS — each ExtElem is 4 consecutive u32 (Montgomery form).
/// Input has `to_add` ExtElems per output position: in[count * i + idx] (as FpExt).
/// Output layout: SoA — 4 separate arrays of `count` Elem each.
#[cube(launch_unchecked)]
pub fn eltwise_sum_extelem(
    out: &mut Array<u32>,
    input: &Array<u32>,
    #[comptime] to_add: u32,
    #[comptime] count: u32,
) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        let mut r0: u32 = 0u32;
        let mut r1: u32 = 0u32;
        let mut r2: u32 = 0u32;
        let mut r3: u32 = 0u32;
        for i in 0..to_add {
            // Input is AoS: each FpExt is 4 consecutive Fp values
            let base = ((count * i + idx) * 4u32) as usize;
            r0 = bb_add(r0, input[base]);
            r1 = bb_add(r1, input[base + 1usize]);
            r2 = bb_add(r2, input[base + 2usize]);
            r3 = bb_add(r3, input[base + 3usize]);
        }
        // Output is SoA: 4 arrays of count elements
        out[idx as usize] = r0;
        out[(idx + count) as usize] = r1;
        out[(idx + 2u32 * count) as usize] = r2;
        out[(idx + 3u32 * count) as usize] = r3;
    }
}

/// FRI fold: fold 16 extension field values with mixing.
///
/// For each output index, accumulates FRI_FOLD=16 ExtElem values with
/// a running mix power. Input is SoA layout (4 separate arrays of count*16).
#[cube(launch_unchecked)]
pub fn fri_fold(
    out: &mut Array<u32>,
    input: &Array<u32>,
    mix0: u32,
    mix1: u32,
    mix2: u32,
    mix3: u32,
    #[comptime] count: u32,
) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        let mut tot0: u32 = 0u32;
        let mut tot1: u32 = 0u32;
        let mut tot2: u32 = 0u32;
        let mut tot3: u32 = 0u32;
        let mut cur0: u32 = 0x0ffffffeu32; // Montgomery 1
        let mut cur1: u32 = 0u32;
        let mut cur2: u32 = 0u32;
        let mut cur3: u32 = 0u32;
        for i in 0..comptime!(16u32) {
            // Bit-reverse i within 4 bits (log2(16) = 4)
            let rev_i = ((i & 1u32) << 3u32)
                | ((i & 2u32) << 1u32)
                | ((i & 4u32) >> 1u32)
                | ((i & 8u32) >> 3u32);
            let rev_idx = (rev_i * count + idx) as usize;
            let stride = (count * 16u32) as usize;
            // factor = ExtElem from 4 SoA arrays
            let f0 = input[rev_idx];
            let f1 = input[rev_idx + stride];
            let f2 = input[rev_idx + 2usize * stride];
            let f3 = input[rev_idx + 3usize * stride];
            // tot += curMix * factor
            let mut t0: u32 = cur0;
            let mut t1: u32 = cur1;
            let mut t2: u32 = cur2;
            let mut t3: u32 = cur3;
            bb4_mul(&mut t0, &mut t1, &mut t2, &mut t3, f0, f1, f2, f3);
            bb4_add(&mut tot0, &mut tot1, &mut tot2, &mut tot3, t0, t1, t2, t3);
            // curMix *= mix
            bb4_mul(&mut cur0, &mut cur1, &mut cur2, &mut cur3, mix0, mix1, mix2, mix3);
        }
        // Output SoA: 4 arrays of count
        out[idx as usize] = tot0;
        out[(idx + count) as usize] = tot1;
        out[(idx + 2u32 * count) as usize] = tot2;
        out[(idx + 3u32 * count) as usize] = tot3;
    }
}

/// Batch polynomial evaluation at extension field points.
///
/// One cube (block) per evaluation point. Threads within the block split the
/// polynomial, each evaluating a strided subset via Horner's method.
/// Shared memory tree reduction sums partial results.
///
/// coeffs: Fp* (base field, all polynomials concatenated)
/// which: u32* (which[blockIdx.x] = polynomial index)
/// xs: FpExt* (AoS, evaluation points)
/// out: FpExt* (AoS, output)
#[cube(launch_unchecked)]
pub fn batch_evaluate_any(
    out: &mut Array<u32>,
    coeffs: &Array<u32>,
    which: &Array<u32>,
    xs: &Array<u32>,
    #[comptime] deg: u32,
    #[comptime] cube_size: usize,
) {
    let block_idx = CUBE_POS_X as u32;
    let tid = UNIT_POS_X as u32;
    let bdim = CUBE_DIM_X as u32;

    // Shared memory for tree reduction (4 u32 per thread)
    let mut smem = SharedMemory::<u32>::new(cube_size * 4);

    // Which polynomial
    let poly_idx = which[block_idx as usize];
    let poly_base = (poly_idx * deg) as usize;

    // x = xs[blockIdx.x] (AoS: 4 consecutive u32)
    let x_base = (block_idx * 4u32) as usize;
    let x0 = xs[x_base];
    let x1 = xs[x_base + 1usize];
    let x2 = xs[x_base + 2usize];
    let x3 = xs[x_base + 3usize];

    // stepx = pow(x, blockDim.x) — use runtime CUBE_DIM_X to avoid comptime mutation
    let mut stepx0: u32 = x0;
    let mut stepx1: u32 = x1;
    let mut stepx2: u32 = x2;
    let mut stepx3: u32 = x3;
    crate::hal::cubecl::ext_field::bb4_pow(
        &mut stepx0, &mut stepx1, &mut stepx2, &mut stepx3, bdim,
    );

    // powx = pow(x, threadIdx.x)
    let mut powx0: u32 = x0;
    let mut powx1: u32 = x1;
    let mut powx2: u32 = x2;
    let mut powx3: u32 = x3;
    crate::hal::cubecl::ext_field::bb4_pow(
        &mut powx0, &mut powx1, &mut powx2, &mut powx3, tid,
    );

    // Strided Horner's evaluation
    let mut tot0: u32 = 0u32;
    let mut tot1: u32 = 0u32;
    let mut tot2: u32 = 0u32;
    let mut tot3: u32 = 0u32;

    let mut i = tid;
    while i < deg {
        // tot += powx * coeffs[poly_base + i]
        let coeff = coeffs[poly_base + i as usize];
        let mut t0: u32 = powx0;
        let mut t1: u32 = powx1;
        let mut t2: u32 = powx2;
        let mut t3: u32 = powx3;
        bb4_mul_scalar(&mut t0, &mut t1, &mut t2, &mut t3, coeff);
        bb4_add(&mut tot0, &mut tot1, &mut tot2, &mut tot3, t0, t1, t2, t3);
        // powx *= stepx
        bb4_mul(
            &mut powx0, &mut powx1, &mut powx2, &mut powx3,
            stepx0, stepx1, stepx2, stepx3,
        );
        i = i + bdim;
    }

    // Store to shared memory (4 u32 per thread)
    let s_base = (tid * 4u32) as usize;
    smem[s_base] = tot0;
    smem[s_base + 1usize] = tot1;
    smem[s_base + 2usize] = tot2;
    smem[s_base + 3usize] = tot3;
    sync_cube();

    // Tree reduction
    let mut half = bdim / 2u32;
    while half > 0u32 {
        if tid < half {
            let other = ((tid + half) * 4u32) as usize;
            let me = (tid * 4u32) as usize;
            let mut m0: u32 = smem[me];
            let mut m1: u32 = smem[me + 1usize];
            let mut m2: u32 = smem[me + 2usize];
            let mut m3: u32 = smem[me + 3usize];
            bb4_add(
                &mut m0, &mut m1, &mut m2, &mut m3,
                smem[other], smem[other + 1usize],
                smem[other + 2usize], smem[other + 3usize],
            );
            smem[me] = m0;
            smem[me + 1usize] = m1;
            smem[me + 2usize] = m2;
            smem[me + 3usize] = m3;
        }
        sync_cube();
        half = half / 2u32;
    }

    // Thread 0 writes result (AoS output)
    if tid == 0u32 {
        let o_base = (block_idx * 4u32) as usize;
        out[o_base] = smem[0usize];
        out[o_base + 1usize] = smem[1usize];
        out[o_base + 2usize] = smem[2usize];
        out[o_base + 3usize] = smem[3usize];
    }
}

/// Mix polynomial coefficients with extension field mixing values.
///
/// For each coefficient position idx, accumulates across input_size polynomials:
/// out[count * combos[i] + idx] += cur * in[count * i + idx]
/// where cur starts at mix_start and multiplies by mix each iteration.
/// Output is FpExt* (AoS: 4 consecutive u32 per ExtElem).
#[cube(launch_unchecked)]
pub fn mix_poly_coeffs(
    out: &mut Array<u32>,
    input: &Array<u32>,
    combos: &Array<u32>,
    mix_start0: u32,
    mix_start1: u32,
    mix_start2: u32,
    mix_start3: u32,
    mix0: u32,
    mix1: u32,
    mix2: u32,
    mix3: u32,
    #[comptime] input_size: u32,
    #[comptime] count: u32,
) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        let mut cur0: u32 = mix_start0;
        let mut cur1: u32 = mix_start1;
        let mut cur2: u32 = mix_start2;
        let mut cur3: u32 = mix_start3;
        for i in 0..input_size {
            let id = combos[i as usize];
            // in[count * i + idx] is a base field element
            let coeff = input[(count * i + idx) as usize];
            // cur * coeff (ExtElem * Elem = ExtElem)
            let mut p0: u32 = cur0;
            let mut p1: u32 = cur1;
            let mut p2: u32 = cur2;
            let mut p3: u32 = cur3;
            bb4_mul_scalar(&mut p0, &mut p1, &mut p2, &mut p3, coeff);
            // out is FpExt* (AoS): out[k] = 4 consecutive u32 at offset k*4
            let k = (count * id + idx) as usize;
            let mut a0: u32 = out[k * 4usize];
            let mut a1: u32 = out[k * 4usize + 1usize];
            let mut a2: u32 = out[k * 4usize + 2usize];
            let mut a3: u32 = out[k * 4usize + 3usize];
            bb4_add(&mut a0, &mut a1, &mut a2, &mut a3, p0, p1, p2, p3);
            out[k * 4usize] = a0;
            out[k * 4usize + 1usize] = a1;
            out[k * 4usize + 2usize] = a2;
            out[k * 4usize + 3usize] = a3;
            // cur *= mix
            bb4_mul(&mut cur0, &mut cur1, &mut cur2, &mut cur3, mix0, mix1, mix2, mix3);
        }
    }
}
