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

//! CubeClHal: Full HAL implementation using cubecl GPU kernels.

use std::fmt::Debug;

use cubecl::{
    cuda::{CudaDevice, CudaRuntime},
    prelude::*,
    server::Handle,
};
use risc0_core::{
    field::{
        Elem, ExtElem, RootsOfUnity,
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    },
    scope,
};

use super::{
    buffer::CubeClBuffer,
    kernels, ntt,
    poseidon2::{self, generate_m_int_diag, generate_round_constants},
    twiddle,
};
use crate::{
    FRI_FOLD,
    core::{
        digest::{DIGEST_WORDS, Digest},
        hash::{HashSuite, poseidon2::Poseidon2HashSuite},
        log2_ceil,
    },
    hal::{Buffer, Hal},
    prove::MerkleTreeProver,
};

/// Pre-computed twiddle and constant tables stored on GPU.
struct Tables {
    fwd_radix: Handle,
    fwd_partial: Handle,
    fwd_plus_one: Handle,
    inv_radix: Handle,
    inv_partial: Handle,
    inv_plus_one: Handle,
    domain_inv: Handle,
    poseidon2_rc: Handle,
    poseidon2_m_int: Handle,
}

/// cubecl-based HAL backend for ZKP operations.
///
/// Uses cubecl GPU kernels for all polynomial, NTT, hashing, and
/// elementwise operations. Currently targets CUDA via cubecl's CudaRuntime.
pub struct CubeClHal {
    client: ComputeClient<CudaRuntime>,
    suite: HashSuite<BabyBear>,
    tables: Tables,
}

pub type CubeClHalPoseidon2 = CubeClHal;

impl CubeClHal {
    pub fn new() -> Self {
        #[cfg(all(test, feature = "cubecl"))]
        gpu_guard::assert_gpu_semaphore_held();

        let device = CudaDevice::new(0);
        let client = CudaRuntime::client(&device);

        // Generate and upload twiddle tables
        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let inv_plus_one = twiddle::generate_plus_one_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        // Generate and upload Poseidon2 constants
        let poseidon2_rc = generate_round_constants();
        let poseidon2_m_int = generate_m_int_diag();

        let tables = Tables {
            fwd_radix: client.create_from_slice(u32::as_bytes(&fwd_radix)),
            fwd_partial: client.create_from_slice(u32::as_bytes(&fwd_partial)),
            fwd_plus_one: client.create_from_slice(u32::as_bytes(&fwd_plus_one)),
            inv_radix: client.create_from_slice(u32::as_bytes(&inv_radix)),
            inv_partial: client.create_from_slice(u32::as_bytes(&inv_partial)),
            inv_plus_one: client.create_from_slice(u32::as_bytes(&inv_plus_one)),
            domain_inv: client.create_from_slice(u32::as_bytes(&domain_inv)),
            poseidon2_rc: client.create_from_slice(u32::as_bytes(&poseidon2_rc)),
            poseidon2_m_int: client.create_from_slice(u32::as_bytes(&poseidon2_m_int)),
        };

        CubeClHal {
            client,
            suite: Poseidon2HashSuite::new_suite(),
            tables,
        }
    }
}

impl Default for CubeClHal {
    fn default() -> Self {
        Self::new()
    }
}

// --- Table sizes (constant) ---
const RADIX_LEN: usize = 992;
const PARTIAL_LEN: usize = (twiddle::WINDOW_NUM * twiddle::WINDOW_SIZE) as usize;
const PLUS_ONE_LEN: usize = (twiddle::PLUS_ONE_ROWS * twiddle::PLUS_ONE_COLS) as usize;
const INV_LEN: usize = (twiddle::MAX_LG_DOMAIN_SIZE + 1) as usize;
const POSEIDON2_RC_LEN: usize = 213;
const POSEIDON2_M_INT_LEN: usize = 24;

// --- NTT step decomposition (extracted from tests.rs) ---

fn compute_gs_steps(lg_n: u32) -> Vec<u32> {
    if lg_n <= 10 {
        vec![lg_n]
    } else if lg_n <= 18 {
        let step = lg_n / 2;
        vec![step + lg_n % 2, step]
    } else if lg_n <= 27 {
        let step = lg_n / 3;
        let rem = lg_n % 3;
        if lg_n == 29 {
            vec![step + 1, step + 1, step]
        } else {
            vec![step + rem, step, step]
        }
    } else {
        panic!("lg_domain_size {lg_n} too large");
    }
}

#[allow(dead_code)]
fn compute_ct_steps(lg_n: u32) -> Vec<u32> {
    if lg_n <= 10 {
        vec![lg_n]
    } else if lg_n <= 18 {
        let step = lg_n / 2;
        vec![step, step + lg_n % 2]
    } else if lg_n <= 27 {
        let step = lg_n / 3;
        let rem = lg_n % 3;
        if lg_n == 29 {
            vec![step, step + 1, step + 1]
        } else {
            vec![step, step, step + rem]
        }
    } else {
        panic!("lg_domain_size {lg_n} too large");
    }
}

impl CubeClHal {
    /// Run forward NTT (Cooley-Tukey DIT, RN order) on a single polynomial.
    #[allow(dead_code)]
    fn run_ct_ntt(&self, data_handle: &Handle, n: usize, lg_n: u32) {
        const Z_COUNT: usize = 8;
        let steps = compute_ct_steps(lg_n);
        let mut current_stage = 0u32;

        for step_size in steps {
            let cube_size = 1usize << (step_size - 1);
            let num_threads = n / 2;
            let num_cubes = num_threads / cube_size;

            if num_cubes < Z_COUNT {
                unsafe {
                    ntt::ct_ntt_step::launch_unchecked::<CudaRuntime>(
                        &self.client,
                        CubeCount::Static(num_cubes as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.fwd_radix, RADIX_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.fwd_partial, PARTIAL_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.domain_inv, INV_LEN, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        false, // is_intt
                        cube_size,
                    )
                    .unwrap();
                }
            } else {
                let num_cubes_z8 = num_cubes / Z_COUNT;
                let coalesced = current_stage != 0 && lg_n >= 12;

                unsafe {
                    ntt::ct_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                        &self.client,
                        CubeCount::Static(num_cubes_z8 as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.fwd_radix, RADIX_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.fwd_partial, PARTIAL_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(
                            &self.tables.fwd_plus_one,
                            PLUS_ONE_LEN,
                            1,
                        ),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.domain_inv, INV_LEN, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        false,
                        coalesced,
                        cube_size,
                    )
                    .unwrap();
                }
            }

            current_stage += step_size;
        }
    }

    /// Run inverse NTT (Gentleman-Sande DIF, NR order) on a single polynomial.
    fn run_gs_ntt(&self, data_handle: &Handle, n: usize, lg_n: u32) {
        const Z_COUNT: usize = 8;
        let steps = compute_gs_steps(lg_n);
        let mut current_stage = lg_n;

        for step_size in steps {
            let cube_size = 1usize << (step_size - 1);
            let num_threads = n / 2;
            let num_cubes = num_threads / cube_size;

            if num_cubes < Z_COUNT {
                unsafe {
                    ntt::gs_ntt_step::launch_unchecked::<CudaRuntime>(
                        &self.client,
                        CubeCount::Static(num_cubes as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.inv_radix, RADIX_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.inv_partial, PARTIAL_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.domain_inv, INV_LEN, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        true, // is_intt
                        cube_size,
                    )
                    .unwrap();
                }
            } else {
                let num_cubes_z8 = num_cubes / Z_COUNT;
                let coalesced = current_stage != step_size && lg_n >= 12;

                unsafe {
                    ntt::gs_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                        &self.client,
                        CubeCount::Static(num_cubes_z8 as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.inv_radix, RADIX_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.inv_partial, PARTIAL_LEN, 1),
                        ArrayArg::from_raw_parts::<u32>(
                            &self.tables.inv_plus_one,
                            PLUS_ONE_LEN,
                            1,
                        ),
                        ArrayArg::from_raw_parts::<u32>(&self.tables.domain_inv, INV_LEN, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        true,
                        coalesced,
                        cube_size,
                    )
                    .unwrap();
                }
            }

            current_stage -= step_size;
        }
    }

    /// Launch bit-reversal permutation on GPU data.
    fn launch_bit_rev(&self, data_handle: &Handle, n: usize, lg_n: u32) {
        let block_size = n.min(1024) as u32;
        let num_blocks = ((n as u32) + block_size - 1) / block_size;
        unsafe {
            ntt::bit_rev_permutation::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                lg_n,
            )
            .unwrap();
        }
    }
}

// Helper: compute grid dimensions for simple 1D kernels
fn grid_1d(count: usize) -> (u32, u32) {
    let block_size = count.min(256) as u32;
    let num_blocks = ((count as u32) + block_size - 1) / block_size;
    (num_blocks, block_size)
}

impl Hal for CubeClHal {
    type Field = BabyBear;
    type Elem = BabyBearElem;
    type ExtElem = BabyBearExtElem;
    type Buffer<T: Clone + Debug + PartialEq> = CubeClBuffer<T>;

    fn has_unified_memory(&self) -> bool {
        false
    }

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        &self.suite
    }

    // --- Allocation methods ---

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem> {
        CubeClBuffer::new(name, size, self.client.clone())
    }

    fn copy_from_elem(
        &self,
        name: &'static str,
        slice: &[Self::Elem],
    ) -> Self::Buffer<Self::Elem> {
        CubeClBuffer::from_slice(name, slice, self.client.clone())
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        CubeClBuffer::new(name, size, self.client.clone())
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem> {
        CubeClBuffer::from_slice(name, slice, self.client.clone())
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest> {
        CubeClBuffer::new(name, size, self.client.clone())
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest> {
        CubeClBuffer::from_slice(name, slice, self.client.clone())
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32> {
        CubeClBuffer::new(name, size, self.client.clone())
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32> {
        CubeClBuffer::from_slice(name, slice, self.client.clone())
    }

    // --- NTT / Polynomial operations ---

    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        expand_bits: usize,
    ) {
        scope!("batch_expand_into_evaluate_ntt");

        let out_size = output.size() / poly_count;
        let in_size = input.size() / poly_count;
        let expand_bits_actual = log2_ceil(out_size / in_size);
        assert_eq!(output.size(), out_size * poly_count);
        assert_eq!(input.size(), in_size * poly_count);
        assert_eq!(out_size, in_size * (1 << expand_bits_actual));

        // batch_expand: copy input to output with zero-padding
        let total = output.size();
        let (num_blocks, block_size) = grid_1d(total);
        let out_handle = output.handle();
        let in_handle = input.handle();
        unsafe {
            kernels::batch_expand::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, total, 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input.size(), 1),
                in_size as u32,
                out_size as u32,
                expand_bits_actual as u32,
            )
            .unwrap();
        }

        // batch_evaluate_ntt: forward NTT on each polynomial
        //
        // The CPU's evaluate_ntt(data, expand_bits) is a recursive Cooley-Tukey DIT
        // that operates on natural-order data and skips the first `expand_bits` butterfly
        // levels. We match this by dispatching individual butterfly stages from
        // (1 + expand_bits) to n_bits on natural-order data (no bit-reversal).
        let n_bits = log2_ceil(out_size);
        assert_eq!(out_size, 1 << n_bits);
        assert!(n_bits >= expand_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);

        let num_threads = out_size / 2;
        let (num_blocks, block_size) = grid_1d(num_threads);

        for row in 0..poly_count {
            let row_offset = row * out_size;
            let row_handle = out_handle
                .clone()
                .offset_start((row_offset * std::mem::size_of::<Self::Elem>()) as u64);

            for s_bits in (1 + expand_bits_actual)..=n_bits {
                unsafe {
                    ntt::ntt_fwd_step::launch_unchecked::<CudaRuntime>(
                        &self.client,
                        CubeCount::Static(num_blocks, 1, 1),
                        CubeDim::new_1d(block_size),
                        ArrayArg::from_raw_parts::<u32>(&row_handle, out_size, 1),
                        ArrayArg::from_raw_parts::<u32>(
                            &self.tables.fwd_partial,
                            PARTIAL_LEN,
                            1,
                        ),
                        n_bits as u32,
                        s_bits as u32,
                    )
                    .unwrap();
                }
            }
        }
    }

    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        scope!("batch_interpolate_ntt");

        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let n_bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << n_bits);
        assert!(n_bits < Self::Elem::MAX_ROU_PO2);

        let io_handle = io.handle();

        // Process each polynomial row independently: GS NTT (inverse, NR order)
        for row in 0..count {
            let row_offset = row * row_size;
            let row_handle = io_handle
                .clone()
                .offset_start((row_offset * std::mem::size_of::<Self::Elem>()) as u64);

            self.run_gs_ntt(&row_handle, row_size, n_bits as u32);
        }
    }

    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        scope!("batch_bit_reverse");

        let row_size = io.size() / count;
        assert_eq!(row_size * count, io.size());
        let bits = log2_ceil(row_size);
        assert_eq!(row_size, 1 << bits);

        let io_handle = io.handle();

        for row in 0..count {
            let row_offset = row * row_size;
            let row_handle = io_handle
                .clone()
                .offset_start((row_offset * std::mem::size_of::<Self::Elem>()) as u64);

            self.launch_bit_rev(&row_handle, row_size, bits as u32);
        }
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    ) {
        let po2 = log2_ceil(coeffs.size() / poly_count);
        let deg = 1 << po2;
        assert_eq!(poly_count * deg, coeffs.size());
        let eval_count = which.size();
        assert_eq!(xs.size(), eval_count);
        assert_eq!(out.size(), eval_count);

        let cube_size = 256usize;
        let coeffs_handle = coeffs.handle();
        let which_handle = which.handle();
        // xs and out are ExtElem (4 u32 each), pass as u32 arrays
        let xs_handle = xs.handle();
        let out_handle = out.handle();

        unsafe {
            kernels::batch_evaluate_any::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(eval_count as u32, 1, 1),
                CubeDim::new_1d(cube_size as u32),
                ArrayArg::from_raw_parts::<u32>(&out_handle, eval_count * 4, 1),
                ArrayArg::from_raw_parts::<u32>(&coeffs_handle, coeffs.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&which_handle, eval_count, 1),
                ArrayArg::from_raw_parts::<u32>(&xs_handle, eval_count * 4, 1),
                deg as u32,
                cube_size,
            )
            .unwrap();
        }
    }

    // --- Polynomial operations ---

    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, poly_count: usize) {
        scope!("zk_shift");

        let total = io.size();
        let count = total / poly_count;
        let n_bits = log2_ceil(count);
        assert_eq!(total, poly_count * (1 << n_bits));

        // Montgomery form of 3
        let three_mont = BabyBearElem::new(3).to_u32_words()[0];

        let (num_blocks, block_size) = grid_1d(total);
        let io_handle = io.handle();
        unsafe {
            kernels::zk_shift::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&io_handle, total, 1),
                count as u32,
                n_bits as u32,
                poly_count as u32,
                three_mont,
            )
            .unwrap();
        }
    }

    fn mix_poly_coeffs(
        &self,
        output: &Self::Buffer<Self::ExtElem>,
        mix_start: &Self::ExtElem,
        mix: &Self::ExtElem,
        input: &Self::Buffer<Self::Elem>,
        combos: &Self::Buffer<u32>,
        input_size: usize,
        count: usize,
    ) {
        let mix_start_words = mix_start.to_u32_words();
        let mix_words = mix.to_u32_words();

        let (num_blocks, block_size) = grid_1d(count);
        let out_handle = output.handle();
        let in_handle = input.handle();
        let combos_handle = combos.handle();

        unsafe {
            kernels::mix_poly_coeffs::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, output.size() * 4, 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&combos_handle, combos.size(), 1),
                ScalarArg::new(mix_start_words[0]),
                ScalarArg::new(mix_start_words[1]),
                ScalarArg::new(mix_start_words[2]),
                ScalarArg::new(mix_start_words[3]),
                ScalarArg::new(mix_words[0]),
                ScalarArg::new(mix_words[1]),
                ScalarArg::new(mix_words[2]),
                ScalarArg::new(mix_words[3]),
                input_size as u32,
                count as u32,
            )
            .unwrap();
        }
    }

    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    ) {
        scope!("fri_fold");

        let count = output.size() / Self::ExtElem::EXT_SIZE;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), output.size() * FRI_FOLD);

        let mix_words = mix.to_u32_words();
        let (num_blocks, block_size) = grid_1d(count);
        let out_handle = output.handle();
        let in_handle = input.handle();

        unsafe {
            kernels::fri_fold::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, output.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input.size(), 1),
                ScalarArg::new(mix_words[0]),
                ScalarArg::new(mix_words[1]),
                ScalarArg::new(mix_words[2]),
                ScalarArg::new(mix_words[3]),
                count as u32,
            )
            .unwrap();
        }
    }

    // --- Elementwise operations ---

    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    ) {
        assert_eq!(output.size(), input1.size());
        assert_eq!(output.size(), input2.size());
        let count = output.size();

        let (num_blocks, block_size) = grid_1d(count);
        let out_handle = output.handle();
        let in1_handle = input1.handle();
        let in2_handle = input2.handle();

        unsafe {
            kernels::eltwise_add::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, count, 1),
                ArrayArg::from_raw_parts::<u32>(&in1_handle, count, 1),
                ArrayArg::from_raw_parts::<u32>(&in2_handle, count, 1),
                count as u32,
            )
            .unwrap();
        }
    }

    fn eltwise_sum_extelem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::ExtElem>,
    ) {
        let count = output.size() / Self::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);

        let (num_blocks, block_size) = grid_1d(count);
        let out_handle = output.handle();
        let in_handle = input.handle();

        unsafe {
            kernels::eltwise_sum_extelem::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, output.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input.size() * 4, 1),
                to_add as u32,
                count as u32,
            )
            .unwrap();
        }
    }

    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        let count = output.size();
        assert_eq!(count, input.size());

        let (num_blocks, block_size) = grid_1d(count);
        let out_handle = output.handle();
        let in_handle = input.handle();

        unsafe {
            kernels::eltwise_copy::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&out_handle, count, 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, count, 1),
                count as u32,
            )
            .unwrap();
        }
    }

    fn eltwise_copy_elem_slice(
        &self,
        into: &Self::Buffer<Self::Elem>,
        from: &[Self::Elem],
        from_rows: usize,
        from_cols: usize,
        from_offset: usize,
        from_stride: usize,
        into_offset: usize,
        into_stride: usize,
    ) {
        let from_buf = self.copy_from_elem("copy_region_from", from);
        let (num_blocks, block_size) = grid_1d(from_rows);
        let into_handle = into.handle();
        let from_handle = from_buf.handle();

        unsafe {
            kernels::eltwise_copy_region::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&into_handle, into.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&from_handle, from.len(), 1),
                from_rows as u32,
                from_cols as u32,
                from_offset as u32,
                from_stride as u32,
                into_offset as u32,
                into_stride as u32,
            )
            .unwrap();
        }
    }

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>) {
        let count = elems.size();
        let (num_blocks, block_size) = grid_1d(count);
        let handle = elems.handle();

        unsafe {
            kernels::eltwise_zeroize::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&handle, count, 1),
                count as u32,
            )
            .unwrap();
        }
    }

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    ) {
        let (num_blocks, block_size) = grid_1d(size);
        let dst_handle = dst.handle();
        let src_handle = src.handle();

        unsafe {
            kernels::gather_sample::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&dst_handle, size, 1),
                ArrayArg::from_raw_parts::<u32>(&src_handle, src.size(), 1),
                idx as u32,
                size as u32,
                stride as u32,
            )
            .unwrap();
        }
    }

    fn scatter(
        &self,
        into: &Self::Buffer<Self::Elem>,
        index: &[u32],
        offsets: &[u32],
        values: &[Self::Elem],
    ) {
        if index.is_empty() {
            return;
        }
        let count = index.len() - 1;
        if count == 0 {
            return;
        }

        let index_buf = self.copy_from_u32("scatter_index", index);
        let offsets_buf = self.copy_from_u32("scatter_offsets", offsets);
        let values_buf = self.copy_from_elem("scatter_values", values);

        let (num_blocks, block_size) = grid_1d(count);
        let into_handle = into.handle();
        let index_handle = index_buf.handle();
        let offsets_handle = offsets_buf.handle();
        let values_handle = values_buf.handle();

        unsafe {
            kernels::scatter::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(&into_handle, into.size(), 1),
                ArrayArg::from_raw_parts::<u32>(&index_handle, index.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&offsets_handle, offsets.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&values_handle, values.len(), 1),
                count as u32,
            )
            .unwrap();
        }
    }

    // --- Hash operations (Poseidon2) ---

    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>) {
        scope!("hash_rows");

        let row_size = output.size(); // number of rows
        let col_size = matrix.size() / row_size; // number of columns
        assert_eq!(matrix.size(), col_size * row_size);

        let block_size = row_size.min(256);
        let num_blocks = (row_size + block_size - 1) / block_size;

        let out_handle = output.handle();
        let matrix_handle = matrix.handle();

        unsafe {
            poseidon2::poseidon2_rows::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks as u32, 1, 1),
                CubeDim::new_1d(block_size as u32),
                // Output: 8 u32 per row (Digest = 8 words)
                ArrayArg::from_raw_parts::<u32>(&out_handle, row_size * DIGEST_WORDS, 1),
                ArrayArg::from_raw_parts::<u32>(&matrix_handle, matrix.size(), 1),
                ArrayArg::from_raw_parts::<u32>(
                    &self.tables.poseidon2_rc,
                    POSEIDON2_RC_LEN,
                    1,
                ),
                ArrayArg::from_raw_parts::<u32>(
                    &self.tables.poseidon2_m_int,
                    POSEIDON2_M_INT_LEN,
                    1,
                ),
                row_size as u32,
                col_size as u32,
                block_size,
            )
            .unwrap();
        }
    }

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize) {
        scope!("hash_fold");

        assert_eq!(input_size, 2 * output_size);

        // io buffer layout (in Digest units):
        // [0..output_size) = unused/output area
        // [output_size..2*output_size) = output destination
        // [2*output_size..4*output_size) = input area
        //
        // poseidon2_fold: each thread reads 16 u32 (2 Digests) from input,
        // hashes them, writes 8 u32 (1 Digest) to output.
        let io_handle = io.handle();

        // Create sub-handles for input and output regions within the io buffer
        let input_byte_offset = (2 * output_size * std::mem::size_of::<Digest>()) as u64;
        let output_byte_offset = (output_size * std::mem::size_of::<Digest>()) as u64;

        let input_handle = io_handle.clone().offset_start(input_byte_offset);
        let output_handle = io_handle.clone().offset_start(output_byte_offset);

        let block_size = output_size.min(256);
        let num_blocks = (output_size + block_size - 1) / block_size;

        unsafe {
            poseidon2::poseidon2_fold::launch_unchecked::<CudaRuntime>(
                &self.client,
                CubeCount::Static(num_blocks as u32, 1, 1),
                CubeDim::new_1d(block_size as u32),
                // Output: 8 u32 per fold
                ArrayArg::from_raw_parts::<u32>(
                    &output_handle,
                    output_size * DIGEST_WORDS,
                    1,
                ),
                // Input: 16 u32 per fold (2 Digests)
                ArrayArg::from_raw_parts::<u32>(
                    &input_handle,
                    output_size * DIGEST_WORDS * 2,
                    1,
                ),
                ArrayArg::from_raw_parts::<u32>(
                    &self.tables.poseidon2_rc,
                    POSEIDON2_RC_LEN,
                    1,
                ),
                ArrayArg::from_raw_parts::<u32>(
                    &self.tables.poseidon2_m_int,
                    POSEIDON2_M_INT_LEN,
                    1,
                ),
                output_size as u32,
                block_size,
            )
            .unwrap();
        }
    }

    // --- Remaining methods ---

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>) {
        // CPU fallback (same as CudaHal)
        io.view_mut(|io| {
            for i in 1..io.len() {
                io[i] *= io[i - 1];
            }
        });
    }

    fn fri_prove(
        &self,
        out_values: &Self::Buffer<u32>,
        values_column_width: usize,
        out_digests: &Self::Buffer<u32>,
        digests_column_width: usize,
        positions: &Self::Buffer<u32>,
        trees: &[&MerkleTreeProver<Self>],
        groups: &Self::Buffer<u32>,
    ) {
        // CPU implementation: read all data to host and process there.
        // This is a complex tree-walking operation that's not performance-critical.
        assert_eq!(trees.len(), groups.size());

        let positions_vec = positions.to_vec();
        let groups_vec = groups.to_vec();

        out_values.view_mut(|out_values| {
            out_digests.view_mut(|out_digests| {
                let mut out_values_iter = out_values.chunks_mut(values_column_width);
                let mut out_digests_iter = out_digests.chunks_mut(digests_column_width);

                for pos in &positions_vec {
                    for (tree, group) in trees.iter().zip(groups_vec.iter()) {
                        let out_v = out_values_iter.next().unwrap();
                        let out_d = out_digests_iter.next().unwrap();

                        // Get column values
                        let values_out = tree.get_column((*pos % *group) as usize);
                        let values_slice: &[u32] = bytemuck::cast_slice(values_out.as_slice());
                        out_v[0] = values_slice.len().try_into().unwrap();
                        out_v[1..(values_slice.len() + 1)].copy_from_slice(values_slice);

                        // Get digests
                        let digests_out = tree.get_digests((*pos % *group) as usize);
                        let digests_slice: &[u32] = bytemuck::cast_slice(digests_out.as_slice());
                        out_d[0] = digests_slice.len().try_into().unwrap();
                        out_d[1..(digests_slice.len() + 1)].copy_from_slice(digests_slice);
                    }
                }
            });
        });
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::hal::testutil;

    #[test]
    #[gpu_guard::gpu_guard]
    #[should_panic]
    fn check_req() {
        testutil::check_req(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn eltwise_add_elem() {
        testutil::eltwise_add_elem(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn eltwise_copy_elem() {
        testutil::eltwise_copy_elem(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn eltwise_sum_extelem() {
        testutil::eltwise_sum_extelem(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn hash_rows_poseidon2() {
        testutil::hash_rows(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn hash_fold_poseidon2() {
        testutil::hash_fold(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn fri_fold() {
        testutil::fri_fold(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn fri_prove() {
        testutil::fri_prove(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn batch_expand_into_evaluate_ntt() {
        testutil::batch_expand_into_evaluate_ntt(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn batch_interpolate_ntt() {
        testutil::batch_interpolate_ntt(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn batch_bit_reverse() {
        testutil::batch_bit_reverse(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn batch_evaluate_any() {
        testutil::batch_evaluate_any(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn gather_sample() {
        testutil::gather_sample(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn zk_shift() {
        testutil::zk_shift(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn mix_poly_coeffs() {
        testutil::mix_poly_coeffs(CubeClHalPoseidon2::new());
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn slice() {
        testutil::slice(CubeClHalPoseidon2::new());
    }
}
