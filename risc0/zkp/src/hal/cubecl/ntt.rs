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

//! NTT (Number Theoretic Transform) GPU kernels using cubecl.
//!
//! Implements mixed-radix NTT with Cooley-Tukey (forward) and Gentleman-Sande
//! (inverse) butterfly algorithms, matching the sppark CUDA implementation.
//!
//! The butterfly stages are explicitly unrolled as individual `comptime` guarded
//! calls rather than using mutable comptime loop counters, because cubecl does
//! not support mutable operations on const (comptime-derived) variables.

use cubecl::prelude::*;

use super::field::{bb_add, bb_mul, bb_sub};

/// Bit-reverse a value with the given number of bits.
#[cube]
fn bit_rev(val: u32, #[comptime] nbits: u32) -> u32 {
    let mut x = val;
    x = ((x >> 1) & 0x55555555u32) | ((x & 0x55555555u32) << 1);
    x = ((x >> 2) & 0x33333333u32) | ((x & 0x33333333u32) << 2);
    x = ((x >> 4) & 0x0F0F0F0Fu32) | ((x & 0x0F0F0F0Fu32) << 4);
    x = ((x >> 8) & 0x00FF00FFu32) | ((x & 0x00FF00FFu32) << 8);
    x = (x >> 16) | (x << 16);
    x >> (32 - nbits)
}

/// Bit-reversal permutation kernel.
///
/// Permutes data such that data[i] and data[bit_reverse(i)] are swapped.
#[cube(launch_unchecked)]
pub fn bit_rev_permutation(data: &mut Array<u32>, #[comptime] lg_domain_size: u32) {
    if ABSOLUTE_POS >= data.len() {
        terminate!();
    }

    let idx = ABSOLUTE_POS as u32;
    let rev = bit_rev(idx, lg_domain_size);

    if idx < rev {
        let a = data[idx as usize];
        let b = data[rev as usize];
        data[idx as usize] = b;
        data[rev as usize] = a;
    }
}

/// Compute an intermediate root of unity from windowed partial twiddles.
///
/// The partial_twiddles array has WINDOW_NUM (5) windows of WINDOW_SIZE (64)
/// entries each, laid out contiguously: [window0[64], window1[64], ..., window4[64]].
#[cube]
fn get_intermediate_root(pow: u32, partial_twiddles: &Array<u32>) -> u32 {
    let mut result = partial_twiddles[(pow % 64) as usize];
    let mut p = pow >> 6;

    if p != 0 {
        result = bb_mul(result, partial_twiddles[(64 + (p % 64)) as usize]);
        p = p >> 6;
    }
    if p != 0 {
        result = bb_mul(result, partial_twiddles[(128 + (p % 64)) as usize]);
        p = p >> 6;
    }
    if p != 0 {
        result = bb_mul(result, partial_twiddles[(192 + (p % 64)) as usize]);
        p = p >> 6;
    }
    if p != 0 {
        result = bb_mul(result, partial_twiddles[(256 + (p % 64)) as usize]);
    }

    result
}

/// Perform a single GS butterfly stage with shared memory exchange.
#[cube]
fn gs_shared_butterfly(
    r0: &mut u32,
    r1: &mut u32,
    xchg: &mut SharedMemory<u32>,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
    #[comptime] radix: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let thrd_mask = (1u32 << s) - 1;
    let rank = unit_pos & thrd_mask;

    let radix_offset = comptime!(1024u32 - (1u32 << radix));
    let twiddle_idx = rank << (radix - s - 1);
    let twiddle = radix_twiddles[(radix_offset + twiddle_idx) as usize];

    let diff = bb_sub(*r0, *r1);
    let t = bb_mul(twiddle, diff);
    *r0 = bb_add(*r0, *r1);
    *r1 = t;

    let pos = rank < lane_mask;
    let to_exchange = if pos { *r1 } else { *r0 };

    sync_cube();
    xchg[UNIT_POS_X as usize] = to_exchange;
    sync_cube();

    let partner_idx = unit_pos ^ lane_mask;
    let partner = xchg[partner_idx as usize];
    if pos {
        *r1 = partner;
    } else {
        *r0 = partner;
    }
}

/// Perform a single GS butterfly stage with warp shuffle exchange.
#[cube]
fn gs_warp_butterfly(
    r0: &mut u32,
    r1: &mut u32,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let thrd_mask = (1u32 << s) - 1;
    let rank = unit_pos & thrd_mask;

    let twiddle_idx = rank << (6 - s - 1);
    let twiddle = radix_twiddles[(960 + twiddle_idx) as usize];

    let diff = bb_sub(*r0, *r1);
    let t = bb_mul(twiddle, diff);
    *r0 = bb_add(*r0, *r1);
    *r1 = t;

    let pos = rank < lane_mask;
    let to_exchange = if pos { *r1 } else { *r0 };
    let partner = plane_shuffle_xor(to_exchange, lane_mask);

    if pos {
        *r1 = partner;
    } else {
        *r0 = partner;
    }
}

/// Perform a single CT butterfly stage with warp shuffle exchange.
#[cube]
fn ct_warp_butterfly(
    r0: &mut u32,
    r1: &mut u32,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let thrd_mask = (1u32 << s) - 1;
    let rank = unit_pos & thrd_mask;
    let pos = rank < lane_mask;

    let to_exchange = if pos { *r1 } else { *r0 };
    let partner = plane_shuffle_xor(to_exchange, lane_mask);

    if pos {
        *r1 = partner;
    } else {
        *r0 = partner;
    }

    let twiddle_idx = rank << (6 - s - 1);
    let twiddle = radix_twiddles[(960 + twiddle_idx) as usize];

    let t = bb_mul(twiddle, *r1);
    *r1 = bb_sub(*r0, t);
    *r0 = bb_add(*r0, t);
}

/// Perform a single CT butterfly stage with shared memory exchange.
#[cube]
fn ct_shared_butterfly(
    r0: &mut u32,
    r1: &mut u32,
    xchg: &mut SharedMemory<u32>,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
    #[comptime] radix: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let thrd_mask = (1u32 << s) - 1;
    let rank = unit_pos & thrd_mask;
    let pos = rank < lane_mask;

    let to_exchange = if pos { *r1 } else { *r0 };

    sync_cube();
    xchg[UNIT_POS_X as usize] = to_exchange;
    sync_cube();

    let partner_idx = unit_pos ^ lane_mask;
    let partner = xchg[partner_idx as usize];
    if pos {
        *r1 = partner;
    } else {
        *r0 = partner;
    }

    let radix_offset = comptime!(1024u32 - (1u32 << radix));
    let twiddle_idx = rank << (radix - s - 1);
    let twiddle = radix_twiddles[(radix_offset + twiddle_idx) as usize];

    let t = bb_mul(twiddle, *r1);
    *r1 = bb_sub(*r0, t);
    *r0 = bb_add(*r0, t);
}

/// Gentleman-Sande (DIF) NTT butterfly kernel — single step.
///
/// Processes `iterations` stages of the GS NTT starting from `stage` down.
/// Each thread handles one butterfly pair (z_count=1).
///
/// The GS butterfly is: given inputs (a, b) and twiddle w,
///   output = (a + b, (a - b) * w)
#[cube(launch_unchecked)]
pub fn gs_ntt_step(
    data: &mut Array<u32>,
    radix_twiddles: &Array<u32>,
    partial_twiddles: &Array<u32>,
    domain_size_inverse: &Array<u32>,
    #[comptime] lg_domain_size: u32,
    #[comptime] stage: u32,
    #[comptime] iterations: u32,
    #[comptime] is_intt: bool,
    #[comptime] cube_size: usize,
) {
    let num_threads = 1u32 << (lg_domain_size - 1);
    let tid = ABSOLUTE_POS as u32;

    if tid >= num_threads {
        terminate!();
    }

    // Index computation matching sppark gs_mixed_radix_narrow.cuh
    let inp_mask = (1u32 << (stage - 1)) - 1;
    let out_mask = (1u32 << (stage - iterations)) - 1;

    let mut idx0 = (tid & !inp_mask) * 2;
    idx0 += (tid << (stage - iterations)) & inp_mask;
    idx0 += (tid >> (iterations - 1)) & out_mask;
    let idx1 = idx0 + (1u32 << (stage - 1));

    let mut r0 = data[idx0 as usize];
    let mut r1 = data[idx1 as usize];

    let mut xchg = SharedMemory::<u32>::new(cube_size);
    let unit_pos = UNIT_POS_X as u32;
    let radix = comptime!(if iterations < 6u32 { 6u32 } else { iterations });

    // Shared memory stages: GS processes s from iterations-1 down to 6 (when s >= 6).
    // Explicitly unrolled to avoid mutable comptime variables.
    if comptime!(iterations > 6u32) {
        gs_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 1u32), radix);
    }
    if comptime!(iterations > 7u32) {
        gs_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 2u32), radix);
    }
    if comptime!(iterations > 8u32) {
        gs_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 3u32), radix);
    }
    if comptime!(iterations > 9u32) {
        gs_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 4u32), radix);
    }

    // Warp shuffle stages: GS processes s from min(5, iterations-1) down to 1.
    if comptime!(iterations > 5u32) {
        gs_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 5u32);
    }
    if comptime!(iterations > 4u32) {
        gs_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 4u32);
    }
    if comptime!(iterations > 3u32) {
        gs_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 3u32);
    }
    if comptime!(iterations > 2u32) {
        gs_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 2u32);
    }
    if comptime!(iterations > 1u32) {
        gs_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 1u32);
    }

    // Final radix-2 butterfly (no twiddle)
    {
        let t = bb_sub(r0, r1);
        r0 = bb_add(r0, r1);
        r1 = t;
    }

    // Intermediate twiddle multiplication for multi-step NTT
    if comptime!(stage != iterations) {
        let thread_ntt_pos = (tid & inp_mask) >> (iterations - 1);

        if thread_ntt_pos != 0 {
            let diff_mask = (1u32 << (iterations - 1)) - 1;
            let thread_ntt_idx = (tid & diff_mask) * 2;
            let nbits = comptime!(27u32 - (stage - iterations));

            let root_idx0 = bit_rev(thread_ntt_idx, nbits) * thread_ntt_pos;
            let root_idx1 = root_idx0 + (thread_ntt_pos << (nbits - 1));

            let root0 = get_intermediate_root(root_idx0, partial_twiddles);
            let root1 = get_intermediate_root(root_idx1, partial_twiddles);

            r0 = bb_mul(r0, root0);
            r1 = bb_mul(r1, root1);
        }
    }

    // Inverse NTT normalization
    if comptime!(is_intt && stage == iterations) {
        let inv = domain_size_inverse[lg_domain_size as usize];
        r0 = bb_mul(r0, inv);
        r1 = bb_mul(r1, inv);
    }

    // Rotate iterations bits in output indices
    let mask = ((1u32 << iterations) - 1) << (stage - iterations);
    let mut rotw0 = idx0 & mask;
    rotw0 = (rotw0 << 1) | (rotw0 >> (iterations - 1));
    let out_idx0 = (idx0 & !mask) | (rotw0 & mask);

    let mut rotw1 = idx1 & mask;
    rotw1 = (rotw1 << 1) | (rotw1 >> (iterations - 1));
    let out_idx1 = (idx1 & !mask) | (rotw1 & mask);

    data[out_idx0 as usize] = r0;
    data[out_idx1 as usize] = r1;
}

/// Cooley-Tukey (DIT) NTT butterfly kernel — single step.
#[cube(launch_unchecked)]
pub fn ct_ntt_step(
    data: &mut Array<u32>,
    radix_twiddles: &Array<u32>,
    partial_twiddles: &Array<u32>,
    domain_size_inverse: &Array<u32>,
    #[comptime] lg_domain_size: u32,
    #[comptime] stage: u32,
    #[comptime] iterations: u32,
    #[comptime] is_intt: bool,
    #[comptime] cube_size: usize,
) {
    let num_threads = 1u32 << (lg_domain_size - 1);
    let tid = ABSOLUTE_POS as u32;

    if tid >= num_threads {
        terminate!();
    }

    let out_mask = (1u32 << (stage + iterations - 1)) - 1;
    let thread_ntt_pos = (tid & out_mask) >> (iterations - 1);

    let mut idx0 = (tid & !out_mask) | ((tid << stage) & out_mask);
    idx0 = idx0 * 2 + thread_ntt_pos;
    let idx1 = idx0 + (1u32 << stage);

    let mut r0 = data[idx0 as usize];
    let mut r1 = data[idx1 as usize];

    // Intermediate twiddle multiplication (applied BEFORE butterfly in CT)
    if comptime!(stage != 0u32) {
        if thread_ntt_pos != 0 {
            let diff_mask = (1u32 << (iterations - 1)) - 1;
            let thread_ntt_idx = (tid & diff_mask) * 2;
            let nbits = comptime!(27u32 - stage);

            let root_idx0 = bit_rev(thread_ntt_idx, nbits) * thread_ntt_pos;
            let root_idx1 = root_idx0 + (thread_ntt_pos << (nbits - 1));

            let root0 = get_intermediate_root(root_idx0, partial_twiddles);
            let root1 = get_intermediate_root(root_idx1, partial_twiddles);

            r0 = bb_mul(r0, root0);
            r1 = bb_mul(r1, root1);
        }
    }

    // First radix-2 butterfly (no twiddle)
    {
        let t = r1;
        r1 = bb_sub(r0, t);
        r0 = bb_add(r0, t);
    }

    let mut xchg = SharedMemory::<u32>::new(cube_size);
    let unit_pos = UNIT_POS_X as u32;
    let radix = comptime!(if iterations < 6u32 { 6u32 } else { iterations });

    // Warp shuffle stages: CT processes s from 1 up to min(5, iterations-1).
    if comptime!(iterations > 1u32) {
        ct_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 1u32);
    }
    if comptime!(iterations > 2u32) {
        ct_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 2u32);
    }
    if comptime!(iterations > 3u32) {
        ct_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 3u32);
    }
    if comptime!(iterations > 4u32) {
        ct_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 4u32);
    }
    if comptime!(iterations > 5u32) {
        ct_warp_butterfly(&mut r0, &mut r1, radix_twiddles, unit_pos, 5u32);
    }

    // Shared memory stages: CT processes s from 6 up to iterations-1.
    if comptime!(iterations > 6u32) {
        ct_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, 6u32, radix);
    }
    if comptime!(iterations > 7u32) {
        ct_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, 7u32, radix);
    }
    if comptime!(iterations > 8u32) {
        ct_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, 8u32, radix);
    }
    if comptime!(iterations > 9u32) {
        ct_shared_butterfly(&mut r0, &mut r1, &mut xchg, radix_twiddles, unit_pos, 9u32, radix);
    }

    // Inverse NTT normalization at the last stage
    if comptime!(is_intt && (stage + iterations == lg_domain_size)) {
        let inv = domain_size_inverse[lg_domain_size as usize];
        r0 = bb_mul(r0, inv);
        r1 = bb_mul(r1, inv);
    }

    // Rotate iterations bits in output indices
    let mask = ((1u32 << iterations) - 1) << stage;
    let mut rotw0 = idx0 & mask;
    rotw0 = (rotw0 >> 1) | (rotw0 << (iterations - 1));
    let out_idx0 = (idx0 & !mask) | (rotw0 & mask);

    let mut rotw1 = idx1 & mask;
    rotw1 = (rotw1 >> 1) | (rotw1 << (iterations - 1));
    let out_idx1 = (idx1 & !mask) | (rotw1 & mask);

    data[out_idx0 as usize] = r0;
    data[out_idx1 as usize] = r1;
}

// ============================================================================
// z_count=8 helper functions
// ============================================================================

/// GS butterfly for one pair: (a, b) -> (a+b, (a-b)*w)
#[cube]
fn gs_butterfly_pair(a: &mut u32, b: &mut u32, w: u32) {
    let diff = bb_sub(*a, *b);
    let t = bb_mul(w, diff);
    *a = bb_add(*a, *b);
    *b = t;
}

/// CT butterfly for one pair: (a, b) -> (a+bw, a-bw)
#[cube]
fn ct_butterfly_pair(a: &mut u32, b: &mut u32, w: u32) {
    let t = bb_mul(w, *b);
    *b = bb_sub(*a, t);
    *a = bb_add(*a, t);
}

/// Simple butterfly: (a, b) -> (a+b, a-b)
#[cube]
fn simple_butterfly_pair(a: &mut u32, b: &mut u32) {
    let t = bb_sub(*a, *b);
    *a = bb_add(*a, *b);
    *b = t;
}

/// Transpose 8 values through shared memory (8x8 within groups of 8 threads).
#[cube]
fn transpose_z8(
    v0: &mut u32, v1: &mut u32, v2: &mut u32, v3: &mut u32,
    v4: &mut u32, v5: &mut u32, v6: &mut u32, v7: &mut u32,
    xchg: &mut SharedMemory<u32>,
    unit_pos: u32,
) {
    let x = unit_pos & 7u32;
    let y = unit_pos & !7u32;
    xchg[((y + 0) * 8 + x) as usize] = *v0;
    xchg[((y + 1) * 8 + x) as usize] = *v1;
    xchg[((y + 2) * 8 + x) as usize] = *v2;
    xchg[((y + 3) * 8 + x) as usize] = *v3;
    xchg[((y + 4) * 8 + x) as usize] = *v4;
    xchg[((y + 5) * 8 + x) as usize] = *v5;
    xchg[((y + 6) * 8 + x) as usize] = *v6;
    xchg[((y + 7) * 8 + x) as usize] = *v7;
    sync_cube();
    let rx = (y + x) * 8;
    *v0 = xchg[(rx + 0) as usize];
    *v1 = xchg[(rx + 1) as usize];
    *v2 = xchg[(rx + 2) as usize];
    *v3 = xchg[(rx + 3) as usize];
    *v4 = xchg[(rx + 4) as usize];
    *v5 = xchg[(rx + 5) as usize];
    *v6 = xchg[(rx + 6) as usize];
    *v7 = xchg[(rx + 7) as usize];
    sync_cube();
}

/// GS shared memory butterfly stage for z_count=8.
#[cube]
#[allow(clippy::too_many_arguments)]
fn gs_shared_stage_z8(
    a0: &mut u32, a1: &mut u32, a2: &mut u32, a3: &mut u32,
    a4: &mut u32, a5: &mut u32, a6: &mut u32, a7: &mut u32,
    b0: &mut u32, b1: &mut u32, b2: &mut u32, b3: &mut u32,
    b4: &mut u32, b5: &mut u32, b6: &mut u32, b7: &mut u32,
    xchg: &mut SharedMemory<u32>,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
    #[comptime] radix: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let rank = unit_pos & ((1u32 << s) - 1);
    let pos = rank < lane_mask;
    let radix_offset = comptime!(1024u32 - (1u32 << radix));
    let tw = radix_twiddles[(radix_offset + (rank << (radix - s - 1))) as usize];

    gs_butterfly_pair(a0, b0, tw);
    gs_butterfly_pair(a1, b1, tw);
    gs_butterfly_pair(a2, b2, tw);
    gs_butterfly_pair(a3, b3, tw);
    gs_butterfly_pair(a4, b4, tw);
    gs_butterfly_pair(a5, b5, tw);
    gs_butterfly_pair(a6, b6, tw);
    gs_butterfly_pair(a7, b7, tw);

    let base = unit_pos * 8;
    xchg[(base + 0) as usize] = if pos { *b0 } else { *a0 };
    xchg[(base + 1) as usize] = if pos { *b1 } else { *a1 };
    xchg[(base + 2) as usize] = if pos { *b2 } else { *a2 };
    xchg[(base + 3) as usize] = if pos { *b3 } else { *a3 };
    xchg[(base + 4) as usize] = if pos { *b4 } else { *a4 };
    xchg[(base + 5) as usize] = if pos { *b5 } else { *a5 };
    xchg[(base + 6) as usize] = if pos { *b6 } else { *a6 };
    xchg[(base + 7) as usize] = if pos { *b7 } else { *a7 };
    sync_cube();

    let pbase = (unit_pos ^ lane_mask) * 8;
    let p0 = xchg[(pbase + 0) as usize];
    let p1 = xchg[(pbase + 1) as usize];
    let p2 = xchg[(pbase + 2) as usize];
    let p3 = xchg[(pbase + 3) as usize];
    let p4 = xchg[(pbase + 4) as usize];
    let p5 = xchg[(pbase + 5) as usize];
    let p6 = xchg[(pbase + 6) as usize];
    let p7 = xchg[(pbase + 7) as usize];
    if pos { *b0 = p0; } else { *a0 = p0; }
    if pos { *b1 = p1; } else { *a1 = p1; }
    if pos { *b2 = p2; } else { *a2 = p2; }
    if pos { *b3 = p3; } else { *a3 = p3; }
    if pos { *b4 = p4; } else { *a4 = p4; }
    if pos { *b5 = p5; } else { *a5 = p5; }
    if pos { *b6 = p6; } else { *a6 = p6; }
    if pos { *b7 = p7; } else { *a7 = p7; }
    sync_cube();
}

/// GS warp shuffle stage for z_count=8.
#[cube]
#[allow(clippy::too_many_arguments)]
fn gs_warp_stage_z8(
    a0: &mut u32, a1: &mut u32, a2: &mut u32, a3: &mut u32,
    a4: &mut u32, a5: &mut u32, a6: &mut u32, a7: &mut u32,
    b0: &mut u32, b1: &mut u32, b2: &mut u32, b3: &mut u32,
    b4: &mut u32, b5: &mut u32, b6: &mut u32, b7: &mut u32,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let rank = unit_pos & ((1u32 << s) - 1);
    let pos = rank < lane_mask;
    let tw = radix_twiddles[(960 + (rank << (6 - s - 1))) as usize];

    gs_butterfly_pair(a0, b0, tw);
    gs_butterfly_pair(a1, b1, tw);
    gs_butterfly_pair(a2, b2, tw);
    gs_butterfly_pair(a3, b3, tw);
    gs_butterfly_pair(a4, b4, tw);
    gs_butterfly_pair(a5, b5, tw);
    gs_butterfly_pair(a6, b6, tw);
    gs_butterfly_pair(a7, b7, tw);

    let v0 = if pos { *b0 } else { *a0 };
    let p0 = plane_shuffle_xor(v0, lane_mask);
    if pos { *b0 = p0; } else { *a0 = p0; }
    let v1 = if pos { *b1 } else { *a1 };
    let p1 = plane_shuffle_xor(v1, lane_mask);
    if pos { *b1 = p1; } else { *a1 = p1; }
    let v2 = if pos { *b2 } else { *a2 };
    let p2 = plane_shuffle_xor(v2, lane_mask);
    if pos { *b2 = p2; } else { *a2 = p2; }
    let v3 = if pos { *b3 } else { *a3 };
    let p3 = plane_shuffle_xor(v3, lane_mask);
    if pos { *b3 = p3; } else { *a3 = p3; }
    let v4 = if pos { *b4 } else { *a4 };
    let p4 = plane_shuffle_xor(v4, lane_mask);
    if pos { *b4 = p4; } else { *a4 = p4; }
    let v5 = if pos { *b5 } else { *a5 };
    let p5 = plane_shuffle_xor(v5, lane_mask);
    if pos { *b5 = p5; } else { *a5 = p5; }
    let v6 = if pos { *b6 } else { *a6 };
    let p6 = plane_shuffle_xor(v6, lane_mask);
    if pos { *b6 = p6; } else { *a6 = p6; }
    let v7 = if pos { *b7 } else { *a7 };
    let p7 = plane_shuffle_xor(v7, lane_mask);
    if pos { *b7 = p7; } else { *a7 = p7; }
}

/// CT shared memory butterfly stage for z_count=8.
#[cube]
#[allow(clippy::too_many_arguments)]
fn ct_shared_stage_z8(
    a0: &mut u32, a1: &mut u32, a2: &mut u32, a3: &mut u32,
    a4: &mut u32, a5: &mut u32, a6: &mut u32, a7: &mut u32,
    b0: &mut u32, b1: &mut u32, b2: &mut u32, b3: &mut u32,
    b4: &mut u32, b5: &mut u32, b6: &mut u32, b7: &mut u32,
    xchg: &mut SharedMemory<u32>,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
    #[comptime] radix: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let rank = unit_pos & ((1u32 << s) - 1);
    let pos = rank < lane_mask;

    // CT: exchange first, then butterfly
    let base = unit_pos * 8;
    xchg[(base + 0) as usize] = if pos { *b0 } else { *a0 };
    xchg[(base + 1) as usize] = if pos { *b1 } else { *a1 };
    xchg[(base + 2) as usize] = if pos { *b2 } else { *a2 };
    xchg[(base + 3) as usize] = if pos { *b3 } else { *a3 };
    xchg[(base + 4) as usize] = if pos { *b4 } else { *a4 };
    xchg[(base + 5) as usize] = if pos { *b5 } else { *a5 };
    xchg[(base + 6) as usize] = if pos { *b6 } else { *a6 };
    xchg[(base + 7) as usize] = if pos { *b7 } else { *a7 };
    sync_cube();

    let pbase = (unit_pos ^ lane_mask) * 8;
    let p0 = xchg[(pbase + 0) as usize];
    let p1 = xchg[(pbase + 1) as usize];
    let p2 = xchg[(pbase + 2) as usize];
    let p3 = xchg[(pbase + 3) as usize];
    let p4 = xchg[(pbase + 4) as usize];
    let p5 = xchg[(pbase + 5) as usize];
    let p6 = xchg[(pbase + 6) as usize];
    let p7 = xchg[(pbase + 7) as usize];
    if pos { *b0 = p0; } else { *a0 = p0; }
    if pos { *b1 = p1; } else { *a1 = p1; }
    if pos { *b2 = p2; } else { *a2 = p2; }
    if pos { *b3 = p3; } else { *a3 = p3; }
    if pos { *b4 = p4; } else { *a4 = p4; }
    if pos { *b5 = p5; } else { *a5 = p5; }
    if pos { *b6 = p6; } else { *a6 = p6; }
    if pos { *b7 = p7; } else { *a7 = p7; }
    sync_cube();

    let radix_offset = comptime!(1024u32 - (1u32 << radix));
    let tw = radix_twiddles[(radix_offset + (rank << (radix - s - 1))) as usize];
    ct_butterfly_pair(a0, b0, tw);
    ct_butterfly_pair(a1, b1, tw);
    ct_butterfly_pair(a2, b2, tw);
    ct_butterfly_pair(a3, b3, tw);
    ct_butterfly_pair(a4, b4, tw);
    ct_butterfly_pair(a5, b5, tw);
    ct_butterfly_pair(a6, b6, tw);
    ct_butterfly_pair(a7, b7, tw);
}

/// CT warp shuffle stage for z_count=8.
#[cube]
#[allow(clippy::too_many_arguments)]
fn ct_warp_stage_z8(
    a0: &mut u32, a1: &mut u32, a2: &mut u32, a3: &mut u32,
    a4: &mut u32, a5: &mut u32, a6: &mut u32, a7: &mut u32,
    b0: &mut u32, b1: &mut u32, b2: &mut u32, b3: &mut u32,
    b4: &mut u32, b5: &mut u32, b6: &mut u32, b7: &mut u32,
    radix_twiddles: &Array<u32>,
    unit_pos: u32,
    #[comptime] s: u32,
) {
    let lane_mask = 1u32 << (s - 1);
    let rank = unit_pos & ((1u32 << s) - 1);
    let pos = rank < lane_mask;

    // CT: exchange first
    let v0 = if pos { *b0 } else { *a0 };
    let p0 = plane_shuffle_xor(v0, lane_mask);
    if pos { *b0 = p0; } else { *a0 = p0; }
    let v1 = if pos { *b1 } else { *a1 };
    let p1 = plane_shuffle_xor(v1, lane_mask);
    if pos { *b1 = p1; } else { *a1 = p1; }
    let v2 = if pos { *b2 } else { *a2 };
    let p2 = plane_shuffle_xor(v2, lane_mask);
    if pos { *b2 = p2; } else { *a2 = p2; }
    let v3 = if pos { *b3 } else { *a3 };
    let p3 = plane_shuffle_xor(v3, lane_mask);
    if pos { *b3 = p3; } else { *a3 = p3; }
    let v4 = if pos { *b4 } else { *a4 };
    let p4 = plane_shuffle_xor(v4, lane_mask);
    if pos { *b4 = p4; } else { *a4 = p4; }
    let v5 = if pos { *b5 } else { *a5 };
    let p5 = plane_shuffle_xor(v5, lane_mask);
    if pos { *b5 = p5; } else { *a5 = p5; }
    let v6 = if pos { *b6 } else { *a6 };
    let p6 = plane_shuffle_xor(v6, lane_mask);
    if pos { *b6 = p6; } else { *a6 = p6; }
    let v7 = if pos { *b7 } else { *a7 };
    let p7 = plane_shuffle_xor(v7, lane_mask);
    if pos { *b7 = p7; } else { *a7 = p7; }

    // Then butterfly
    let tw = radix_twiddles[(960 + (rank << (6 - s - 1))) as usize];
    ct_butterfly_pair(a0, b0, tw);
    ct_butterfly_pair(a1, b1, tw);
    ct_butterfly_pair(a2, b2, tw);
    ct_butterfly_pair(a3, b3, tw);
    ct_butterfly_pair(a4, b4, tw);
    ct_butterfly_pair(a5, b5, tw);
    ct_butterfly_pair(a6, b6, tw);
    ct_butterfly_pair(a7, b7, tw);
}

/// Plus-one twiddle correction for z=1..7.
#[cube]
#[allow(clippy::too_many_arguments)]
fn plus_one_correct_z8(
    first_root: &mut u32, second_root: &mut u32,
    frz: u32, srz: u32,
    a1: &mut u32, b1: &mut u32,
    a2: &mut u32, b2: &mut u32,
    a3: &mut u32, b3: &mut u32,
    a4: &mut u32, b4: &mut u32,
    a5: &mut u32, b5: &mut u32,
    a6: &mut u32, b6: &mut u32,
    a7: &mut u32, b7: &mut u32,
) {
    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a1 = bb_mul(*a1, *first_root);
    *b1 = bb_mul(*b1, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a2 = bb_mul(*a2, *first_root);
    *b2 = bb_mul(*b2, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a3 = bb_mul(*a3, *first_root);
    *b3 = bb_mul(*b3, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a4 = bb_mul(*a4, *first_root);
    *b4 = bb_mul(*b4, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a5 = bb_mul(*a5, *first_root);
    *b5 = bb_mul(*b5, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a6 = bb_mul(*a6, *first_root);
    *b6 = bb_mul(*b6, *second_root);

    *first_root = bb_mul(*first_root, frz);
    *second_root = bb_mul(*second_root, srz);
    *a7 = bb_mul(*a7, *first_root);
    *b7 = bb_mul(*b7, *second_root);
}

// ============================================================================
// z_count=8 kernels
// ============================================================================

/// Gentleman-Sande NTT kernel with z_count=8 per-thread parallelism.
#[cube(launch_unchecked)]
#[allow(clippy::too_many_arguments)]
pub fn gs_ntt_step_z8(
    data: &mut Array<u32>,
    radix_twiddles: &Array<u32>,
    partial_twiddles: &Array<u32>,
    plus_one_twiddles: &Array<u32>,
    domain_size_inverse: &Array<u32>,
    #[comptime] lg_domain_size: u32,
    #[comptime] stage: u32,
    #[comptime] iterations: u32,
    #[comptime] is_intt: bool,
    #[comptime] coalesced: bool,
    #[comptime] cube_size: usize,
) {
    let tid = ABSOLUTE_POS as u32;
    let unit_pos = UNIT_POS_X as u32;
    let diff_mask = (1u32 << (iterations - 1)) - 1;
    let inp_mask = (1u32 << (stage - 1)) - 1;
    let out_mask = (1u32 << (stage - iterations)) - 1;
    let tiz = (tid & !diff_mask) * 8 + (tid & diff_mask);

    let mut idx0 = (tiz & !inp_mask) * 2;
    idx0 += (tiz << (stage - iterations)) & inp_mask;
    idx0 += (tiz >> (iterations - 1)) & out_mask;
    let idx1 = idx0 + (1u32 << (stage - 1));

    let mut xchg = SharedMemory::<u32>::new(cube_size * 8);
    let radix = comptime!(if iterations < 6u32 { 6u32 } else { iterations });

    // --- Load ---
    // Compute load base and stride based on coalesced flag
    let z_shift = comptime!(if coalesced {
        stage - iterations
    } else if stage == iterations {
        iterations
    } else {
        0u32
    });
    let load_step = 1u32 << z_shift;
    let coal_x = unit_pos & 7u32;
    let load_base0 = if comptime!(coalesced) {
        (idx0 & !((7u32) << z_shift)) + coal_x
    } else {
        idx0
    };
    let load_base1 = if comptime!(coalesced) {
        (idx1 & !((7u32) << z_shift)) + coal_x
    } else {
        idx1
    };

    let mut a0 = data[(load_base0) as usize];
    let mut a1 = data[(load_base0 + load_step) as usize];
    let mut a2 = data[(load_base0 + load_step * 2) as usize];
    let mut a3 = data[(load_base0 + load_step * 3) as usize];
    let mut a4 = data[(load_base0 + load_step * 4) as usize];
    let mut a5 = data[(load_base0 + load_step * 5) as usize];
    let mut a6 = data[(load_base0 + load_step * 6) as usize];
    let mut a7 = data[(load_base0 + load_step * 7) as usize];
    if comptime!(coalesced) {
        transpose_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut xchg, unit_pos);
    }
    let mut b0 = data[(load_base1) as usize];
    let mut b1 = data[(load_base1 + load_step) as usize];
    let mut b2 = data[(load_base1 + load_step * 2) as usize];
    let mut b3 = data[(load_base1 + load_step * 3) as usize];
    let mut b4 = data[(load_base1 + load_step * 4) as usize];
    let mut b5 = data[(load_base1 + load_step * 5) as usize];
    let mut b6 = data[(load_base1 + load_step * 6) as usize];
    let mut b7 = data[(load_base1 + load_step * 7) as usize];
    if comptime!(coalesced) {
        transpose_z8(&mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, unit_pos);
    }

    // --- Shared memory butterfly stages ---
    if comptime!(iterations > 6u32) {
        gs_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 1u32), radix);
    }
    if comptime!(iterations > 7u32) {
        gs_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 2u32), radix);
    }
    if comptime!(iterations > 8u32) {
        gs_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 3u32), radix);
    }
    if comptime!(iterations > 9u32) {
        gs_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, comptime!(iterations - 4u32), radix);
    }

    // --- Warp shuffle stages ---
    if comptime!(iterations > 5u32) {
        gs_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 5u32);
    }
    if comptime!(iterations > 4u32) {
        gs_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 4u32);
    }
    if comptime!(iterations > 3u32) {
        gs_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 3u32);
    }
    if comptime!(iterations > 2u32) {
        gs_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 2u32);
    }
    if comptime!(iterations > 1u32) {
        gs_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 1u32);
    }

    // --- Final radix-2 butterfly ---
    simple_butterfly_pair(&mut a0, &mut b0);
    simple_butterfly_pair(&mut a1, &mut b1);
    simple_butterfly_pair(&mut a2, &mut b2);
    simple_butterfly_pair(&mut a3, &mut b3);
    simple_butterfly_pair(&mut a4, &mut b4);
    simple_butterfly_pair(&mut a5, &mut b5);
    simple_butterfly_pair(&mut a6, &mut b6);
    simple_butterfly_pair(&mut a7, &mut b7);

    // --- Intermediate twiddle multiplication ---
    if comptime!(stage != iterations) {
        let thread_ntt_pos = (tiz & inp_mask) >> (iterations - 1);
        let thread_ntt_idx = (tiz & diff_mask) * 2;
        let nbits = comptime!(27u32 - (stage - iterations));
        let root_idx0 = bit_rev(thread_ntt_idx, nbits) * thread_ntt_pos;
        let root_idx1 = root_idx0 + (thread_ntt_pos << (nbits - 1));
        let mut first_root = get_intermediate_root(root_idx0, partial_twiddles);
        let mut second_root = get_intermediate_root(root_idx1, partial_twiddles);
        a0 = bb_mul(a0, first_root);
        b0 = bb_mul(b0, second_root);

        let off = comptime!(if nbits >= 10u32 { nbits - 10u32 } else { 0u32 });
        let scale = comptime!(if nbits >= 10u32 { 0u32 } else { 10u32 - nbits });
        let scaled_idx = thread_ntt_idx << scale;
        let frz = plus_one_twiddles[(off * 1024 + scaled_idx) as usize];
        let srz = plus_one_twiddles[(off * 1024 + scaled_idx + (1u32 << scale)) as usize];
        plus_one_correct_z8(
            &mut first_root, &mut second_root, frz, srz,
            &mut a1, &mut b1, &mut a2, &mut b2, &mut a3, &mut b3, &mut a4, &mut b4,
            &mut a5, &mut b5, &mut a6, &mut b6, &mut a7, &mut b7,
        );
    }

    // --- Inverse NTT normalization ---
    if comptime!(is_intt && stage == iterations) {
        let inv = domain_size_inverse[lg_domain_size as usize];
        a0 = bb_mul(a0, inv); b0 = bb_mul(b0, inv);
        a1 = bb_mul(a1, inv); b1 = bb_mul(b1, inv);
        a2 = bb_mul(a2, inv); b2 = bb_mul(b2, inv);
        a3 = bb_mul(a3, inv); b3 = bb_mul(b3, inv);
        a4 = bb_mul(a4, inv); b4 = bb_mul(b4, inv);
        a5 = bb_mul(a5, inv); b5 = bb_mul(b5, inv);
        a6 = bb_mul(a6, inv); b6 = bb_mul(b6, inv);
        a7 = bb_mul(a7, inv); b7 = bb_mul(b7, inv);
    }

    // --- Rotate iterations bits in output indices ---
    let mask = ((1u32 << iterations) - 1) << (stage - iterations);
    let mut rotw0 = idx0 & mask;
    rotw0 = (rotw0 << 1) | (rotw0 >> (iterations - 1));
    let out_idx0 = (idx0 & !mask) | (rotw0 & mask);
    let mut rotw1 = idx1 & mask;
    rotw1 = (rotw1 << 1) | (rotw1 >> (iterations - 1));
    let out_idx1 = (idx1 & !mask) | (rotw1 & mask);

    // --- Store ---
    if comptime!(coalesced) {
        transpose_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut xchg, unit_pos);
        transpose_z8(&mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, unit_pos);
    }

    let store_shift = comptime!(if coalesced {
        stage - iterations + 1u32
    } else if stage == iterations {
        iterations
    } else {
        0u32
    });
    let store_step = 1u32 << store_shift;
    let store_base0 = if comptime!(coalesced) {
        (out_idx0 & !((7u32) << store_shift)) + coal_x
    } else {
        out_idx0
    };
    let store_base1 = if comptime!(coalesced) {
        (out_idx1 & !((7u32) << store_shift)) + coal_x
    } else {
        out_idx1
    };

    data[(store_base0) as usize] = a0;
    data[(store_base0 + store_step) as usize] = a1;
    data[(store_base0 + store_step * 2) as usize] = a2;
    data[(store_base0 + store_step * 3) as usize] = a3;
    data[(store_base0 + store_step * 4) as usize] = a4;
    data[(store_base0 + store_step * 5) as usize] = a5;
    data[(store_base0 + store_step * 6) as usize] = a6;
    data[(store_base0 + store_step * 7) as usize] = a7;
    data[(store_base1) as usize] = b0;
    data[(store_base1 + store_step) as usize] = b1;
    data[(store_base1 + store_step * 2) as usize] = b2;
    data[(store_base1 + store_step * 3) as usize] = b3;
    data[(store_base1 + store_step * 4) as usize] = b4;
    data[(store_base1 + store_step * 5) as usize] = b5;
    data[(store_base1 + store_step * 6) as usize] = b6;
    data[(store_base1 + store_step * 7) as usize] = b7;
}

/// Cooley-Tukey NTT kernel with z_count=8 per-thread parallelism.
#[cube(launch_unchecked)]
#[allow(clippy::too_many_arguments)]
pub fn ct_ntt_step_z8(
    data: &mut Array<u32>,
    radix_twiddles: &Array<u32>,
    partial_twiddles: &Array<u32>,
    plus_one_twiddles: &Array<u32>,
    domain_size_inverse: &Array<u32>,
    #[comptime] lg_domain_size: u32,
    #[comptime] stage: u32,
    #[comptime] iterations: u32,
    #[comptime] is_intt: bool,
    #[comptime] coalesced: bool,
    #[comptime] cube_size: usize,
) {
    let tid = ABSOLUTE_POS as u32;
    let unit_pos = UNIT_POS_X as u32;
    let diff_mask = (1u32 << (iterations - 1)) - 1;
    let inp_mask = (1u32 << stage) - 1;
    let out_mask = (1u32 << (stage + iterations - 1)) - 1;
    let tiz = (tid & !diff_mask) * 8 + (tid & diff_mask);
    let thread_ntt_pos = (tiz >> (iterations - 1)) & inp_mask;

    let mut idx0 = (tiz & !out_mask) | ((tiz << stage) & out_mask);
    idx0 = idx0 * 2 + thread_ntt_pos;
    let idx1 = idx0 + (1u32 << stage);

    let mut xchg = SharedMemory::<u32>::new(cube_size * 8);
    let radix = comptime!(if iterations < 6u32 { 6u32 } else { iterations });

    // --- Load ---
    let z_shift = comptime!(if coalesced {
        stage + 1u32
    } else if stage == 0u32 {
        iterations
    } else {
        0u32
    });
    let load_step = 1u32 << z_shift;
    let coal_x = unit_pos & 7u32;
    let load_base0 = if comptime!(coalesced) {
        (idx0 & !((7u32) << z_shift)) + coal_x
    } else {
        idx0
    };
    let load_base1 = if comptime!(coalesced) {
        (idx1 & !((7u32) << z_shift)) + coal_x
    } else {
        idx1
    };

    let mut a0 = data[(load_base0) as usize];
    let mut a1 = data[(load_base0 + load_step) as usize];
    let mut a2 = data[(load_base0 + load_step * 2) as usize];
    let mut a3 = data[(load_base0 + load_step * 3) as usize];
    let mut a4 = data[(load_base0 + load_step * 4) as usize];
    let mut a5 = data[(load_base0 + load_step * 5) as usize];
    let mut a6 = data[(load_base0 + load_step * 6) as usize];
    let mut a7 = data[(load_base0 + load_step * 7) as usize];
    if comptime!(coalesced) {
        transpose_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut xchg, unit_pos);
    }
    let mut b0 = data[(load_base1) as usize];
    let mut b1 = data[(load_base1 + load_step) as usize];
    let mut b2 = data[(load_base1 + load_step * 2) as usize];
    let mut b3 = data[(load_base1 + load_step * 3) as usize];
    let mut b4 = data[(load_base1 + load_step * 4) as usize];
    let mut b5 = data[(load_base1 + load_step * 5) as usize];
    let mut b6 = data[(load_base1 + load_step * 6) as usize];
    let mut b7 = data[(load_base1 + load_step * 7) as usize];
    if comptime!(coalesced) {
        transpose_z8(&mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, unit_pos);
    }

    // --- Intermediate twiddle multiplication (before butterfly in CT) ---
    if comptime!(stage != 0u32) {
        let thread_ntt_idx = (tiz & diff_mask) * 2;
        let nbits = comptime!(27u32 - stage);
        let root_idx0 = bit_rev(thread_ntt_idx, nbits) * thread_ntt_pos;
        let root_idx1 = root_idx0 + (thread_ntt_pos << (nbits - 1));
        let mut first_root = get_intermediate_root(root_idx0, partial_twiddles);
        let mut second_root = get_intermediate_root(root_idx1, partial_twiddles);
        a0 = bb_mul(a0, first_root);
        b0 = bb_mul(b0, second_root);

        let off = comptime!(if nbits >= 10u32 { nbits - 10u32 } else { 0u32 });
        let scale = comptime!(if nbits >= 10u32 { 0u32 } else { 10u32 - nbits });
        let scaled_idx = thread_ntt_idx << scale;
        let frz = plus_one_twiddles[(off * 1024 + scaled_idx) as usize];
        let srz = plus_one_twiddles[(off * 1024 + scaled_idx + (1u32 << scale)) as usize];
        plus_one_correct_z8(
            &mut first_root, &mut second_root, frz, srz,
            &mut a1, &mut b1, &mut a2, &mut b2, &mut a3, &mut b3, &mut a4, &mut b4,
            &mut a5, &mut b5, &mut a6, &mut b6, &mut a7, &mut b7,
        );
    }

    // --- First radix-2 butterfly ---
    simple_butterfly_pair(&mut a0, &mut b0);
    simple_butterfly_pair(&mut a1, &mut b1);
    simple_butterfly_pair(&mut a2, &mut b2);
    simple_butterfly_pair(&mut a3, &mut b3);
    simple_butterfly_pair(&mut a4, &mut b4);
    simple_butterfly_pair(&mut a5, &mut b5);
    simple_butterfly_pair(&mut a6, &mut b6);
    simple_butterfly_pair(&mut a7, &mut b7);

    // --- Warp shuffle stages ---
    if comptime!(iterations > 1u32) {
        ct_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 1u32);
    }
    if comptime!(iterations > 2u32) {
        ct_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 2u32);
    }
    if comptime!(iterations > 3u32) {
        ct_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 3u32);
    }
    if comptime!(iterations > 4u32) {
        ct_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 4u32);
    }
    if comptime!(iterations > 5u32) {
        ct_warp_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, radix_twiddles, unit_pos, 5u32);
    }

    // --- Shared memory stages ---
    if comptime!(iterations > 6u32) {
        ct_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, 6u32, radix);
    }
    if comptime!(iterations > 7u32) {
        ct_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, 7u32, radix);
    }
    if comptime!(iterations > 8u32) {
        ct_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, 8u32, radix);
    }
    if comptime!(iterations > 9u32) {
        ct_shared_stage_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, radix_twiddles, unit_pos, 9u32, radix);
    }

    // --- Inverse NTT normalization ---
    if comptime!(is_intt && (stage + iterations == lg_domain_size)) {
        let inv = domain_size_inverse[lg_domain_size as usize];
        a0 = bb_mul(a0, inv); b0 = bb_mul(b0, inv);
        a1 = bb_mul(a1, inv); b1 = bb_mul(b1, inv);
        a2 = bb_mul(a2, inv); b2 = bb_mul(b2, inv);
        a3 = bb_mul(a3, inv); b3 = bb_mul(b3, inv);
        a4 = bb_mul(a4, inv); b4 = bb_mul(b4, inv);
        a5 = bb_mul(a5, inv); b5 = bb_mul(b5, inv);
        a6 = bb_mul(a6, inv); b6 = bb_mul(b6, inv);
        a7 = bb_mul(a7, inv); b7 = bb_mul(b7, inv);
    }

    // --- Rotate iterations bits in output indices ---
    let mask = ((1u32 << iterations) - 1) << stage;
    let mut rotw0 = idx0 & mask;
    rotw0 = (rotw0 >> 1) | (rotw0 << (iterations - 1));
    let out_idx0 = (idx0 & !mask) | (rotw0 & mask);
    let mut rotw1 = idx1 & mask;
    rotw1 = (rotw1 >> 1) | (rotw1 << (iterations - 1));
    let out_idx1 = (idx1 & !mask) | (rotw1 & mask);

    // --- Store ---
    if comptime!(coalesced) {
        transpose_z8(&mut a0, &mut a1, &mut a2, &mut a3, &mut a4, &mut a5, &mut a6, &mut a7, &mut xchg, unit_pos);
        transpose_z8(&mut b0, &mut b1, &mut b2, &mut b3, &mut b4, &mut b5, &mut b6, &mut b7, &mut xchg, unit_pos);
    }

    let store_shift = comptime!(if coalesced {
        stage
    } else if stage == 0u32 {
        iterations
    } else {
        0u32
    });
    let store_step = 1u32 << store_shift;
    let store_base0 = if comptime!(coalesced) {
        (out_idx0 & !((7u32) << store_shift)) + coal_x
    } else {
        out_idx0
    };
    let store_base1 = if comptime!(coalesced) {
        (out_idx1 & !((7u32) << store_shift)) + coal_x
    } else {
        out_idx1
    };

    data[(store_base0) as usize] = a0;
    data[(store_base0 + store_step) as usize] = a1;
    data[(store_base0 + store_step * 2) as usize] = a2;
    data[(store_base0 + store_step * 3) as usize] = a3;
    data[(store_base0 + store_step * 4) as usize] = a4;
    data[(store_base0 + store_step * 5) as usize] = a5;
    data[(store_base0 + store_step * 6) as usize] = a6;
    data[(store_base0 + store_step * 7) as usize] = a7;
    data[(store_base1) as usize] = b0;
    data[(store_base1 + store_step) as usize] = b1;
    data[(store_base1 + store_step * 2) as usize] = b2;
    data[(store_base1 + store_step * 3) as usize] = b3;
    data[(store_base1 + store_step * 4) as usize] = b4;
    data[(store_base1 + store_step * 5) as usize] = b5;
    data[(store_base1 + store_step * 6) as usize] = b6;
    data[(store_base1 + store_step * 7) as usize] = b7;
}
