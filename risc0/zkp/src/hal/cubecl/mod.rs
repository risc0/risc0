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

//! CubeCL-based GPU HAL implementation for the ZKP system.
//!
//! This module provides a portable GPU implementation using cubecl,
//! supporting CUDA, WGPU, ROCm, and Metal backends from a single codebase.

pub mod field;
pub mod ntt;
pub mod twiddle;

#[cfg(test)]
mod tests {
    use cubecl::prelude::*;
    use cubecl::cuda::{CudaDevice, CudaRuntime};
    use risc0_core::field::{Elem, baby_bear::BabyBearElem};

    use super::ntt;
    use super::twiddle;

    fn get_client() -> ComputeClient<CudaRuntime> {
        let device = CudaDevice::new(0);
        CudaRuntime::client(&device)
    }

    /// Convert BabyBearElem slice to raw Montgomery u32 slice
    fn elems_to_mont(elems: &[BabyBearElem]) -> Vec<u32> {
        elems.iter().map(|e| e.to_u32_words()[0]).collect()
    }

    /// Convert raw Montgomery u32 slice back to BabyBearElem slice
    fn mont_to_elems(vals: &[u32]) -> Vec<BabyBearElem> {
        vals.iter()
            .map(|v| BabyBearElem::from_u32_words(&[*v]))
            .collect()
    }

    // --- Field Arithmetic Tests ---

    #[cube(launch_unchecked)]
    fn field_add_kernel(a: &Array<u32>, b: &Array<u32>, out: &mut Array<u32>) {
        let idx = ABSOLUTE_POS as u32;
        if ABSOLUTE_POS < out.len() {
            out[idx as usize] = crate::hal::cubecl::field::bb_add(a[idx as usize], b[idx as usize]);
        }
    }

    #[cube(launch_unchecked)]
    fn field_sub_kernel(a: &Array<u32>, b: &Array<u32>, out: &mut Array<u32>) {
        let idx = ABSOLUTE_POS as u32;
        if ABSOLUTE_POS < out.len() {
            out[idx as usize] = crate::hal::cubecl::field::bb_sub(a[idx as usize], b[idx as usize]);
        }
    }

    #[cube(launch_unchecked)]
    fn field_mul_kernel(a: &Array<u32>, b: &Array<u32>, out: &mut Array<u32>) {
        let idx = ABSOLUTE_POS as u32;
        if ABSOLUTE_POS < out.len() {
            out[idx as usize] = crate::hal::cubecl::field::bb_mul(a[idx as usize], b[idx as usize]);
        }
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn test_field_add() {
        let client = get_client();
        let n = 64usize;

        let a_elems: Vec<_> = (0..n).map(|i| BabyBearElem::new(i as u32 + 1)).collect();
        let b_elems: Vec<_> = (0..n).map(|i| BabyBearElem::new(i as u32 * 7 + 3)).collect();
        let expected: Vec<_> = a_elems.iter().zip(&b_elems).map(|(a, b)| *a + *b).collect();

        let a_mont = elems_to_mont(&a_elems);
        let b_mont = elems_to_mont(&b_elems);

        let a_handle = client.create_from_slice(u32::as_bytes(&a_mont));
        let b_handle = client.create_from_slice(u32::as_bytes(&b_mont));
        let out_handle = client.empty(n * size_of::<u32>());

        unsafe {
            field_add_kernel::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(n as u32),
                ArrayArg::from_raw_parts::<u32>(&a_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&b_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
            )
            .unwrap();
        }

        let result = client.read_one(out_handle);
        let result_elems = mont_to_elems(u32::from_bytes(&result));
        assert_eq!(result_elems, expected, "Field add mismatch");
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn test_field_sub() {
        let client = get_client();
        let n = 64usize;

        let a_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 13 + 100))
            .collect();
        let b_elems: Vec<_> = (0..n).map(|i| BabyBearElem::new(i as u32 * 7 + 3)).collect();
        let expected: Vec<_> = a_elems.iter().zip(&b_elems).map(|(a, b)| *a - *b).collect();

        let a_mont = elems_to_mont(&a_elems);
        let b_mont = elems_to_mont(&b_elems);

        let a_handle = client.create_from_slice(u32::as_bytes(&a_mont));
        let b_handle = client.create_from_slice(u32::as_bytes(&b_mont));
        let out_handle = client.empty(n * size_of::<u32>());

        unsafe {
            field_sub_kernel::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(n as u32),
                ArrayArg::from_raw_parts::<u32>(&a_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&b_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
            )
            .unwrap();
        }

        let result = client.read_one(out_handle);
        let result_elems = mont_to_elems(u32::from_bytes(&result));
        assert_eq!(result_elems, expected, "Field sub mismatch");
    }

    #[test]
    #[gpu_guard::gpu_guard]
    fn test_field_mul() {
        let client = get_client();
        let n = 64usize;

        let a_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 13 + 100))
            .collect();
        let b_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 31337 + 42))
            .collect();
        let expected: Vec<_> = a_elems.iter().zip(&b_elems).map(|(a, b)| *a * *b).collect();

        let a_mont = elems_to_mont(&a_elems);
        let b_mont = elems_to_mont(&b_elems);

        let a_handle = client.create_from_slice(u32::as_bytes(&a_mont));
        let b_handle = client.create_from_slice(u32::as_bytes(&b_mont));
        let out_handle = client.empty(n * size_of::<u32>());

        unsafe {
            field_mul_kernel::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(n as u32),
                ArrayArg::from_raw_parts::<u32>(&a_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&b_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
            )
            .unwrap();
        }

        let result = client.read_one(out_handle);
        let result_elems = mont_to_elems(u32::from_bytes(&result));
        assert_eq!(result_elems, expected, "Field mul mismatch");
    }

    // --- Bit-Reversal Permutation Test ---

    #[test]
    #[gpu_guard::gpu_guard]
    fn test_bit_rev_permutation() {
        let client = get_client();

        for lg_n in 1u32..=10 {
            let n = 1usize << lg_n;
            let data: Vec<u32> = (0..n as u32).collect();

            let handle = client.create_from_slice(u32::as_bytes(&data));

            unsafe {
                ntt::bit_rev_permutation::launch_unchecked::<CudaRuntime>(
                    &client,
                    CubeCount::new_single(),
                    CubeDim::new_1d(n as u32),
                    ArrayArg::from_raw_parts::<u32>(&handle, n, 1),
                    lg_n,
                )
                .unwrap();
            }

            let result = client.read_one(handle);
            let result = u32::from_bytes(&result);

            // Verify: result[i] should be the original data[bit_reverse(i)]
            for i in 0..n {
                let rev = (i as u32).reverse_bits() >> (32 - lg_n);
                assert_eq!(
                    result[i], rev,
                    "Bit-rev mismatch at index {i} for lg_n={lg_n}: got {}, expected {rev}",
                    result[i]
                );
            }
        }
    }

    // --- NTT Roundtrip Tests ---

    /// Run GS NTT (inverse direction, NR order) on GPU data.
    ///
    /// This matches sppark's GS_NTT with the same stage decomposition.
    /// Uses z_count=8 kernels when there are enough blocks, falling back
    /// to z_count=1 for small sizes.
    fn run_gs_ntt(
        client: &ComputeClient<CudaRuntime>,
        data_handle: &cubecl::server::Handle,
        n: usize,
        lg_n: u32,
        is_intt: bool,
        radix_handle: &cubecl::server::Handle,
        partial_handle: &cubecl::server::Handle,
        plus_one_handle: &cubecl::server::Handle,
        inv_handle: &cubecl::server::Handle,
    ) {
        let radix_len = 992usize;
        let partial_len = (twiddle::WINDOW_NUM * twiddle::WINDOW_SIZE) as usize;
        let plus_one_len = (twiddle::PLUS_ONE_ROWS * twiddle::PLUS_ONE_COLS) as usize;
        let inv_len = (twiddle::MAX_LG_DOMAIN_SIZE + 1) as usize;

        const Z_COUNT: usize = 8;

        // GS stage decomposition matching sppark ntt.cuh
        let steps = compute_gs_steps(lg_n);
        let mut current_stage = lg_n;

        for step_size in steps {
            let cube_size = 1usize << (step_size - 1);
            let num_threads = n / 2;
            let num_cubes = num_threads / cube_size;

            if num_cubes < Z_COUNT {
                // z_count=1 path for small sizes
                unsafe {
                    ntt::gs_ntt_step::launch_unchecked::<CudaRuntime>(
                        client,
                        CubeCount::Static(num_cubes as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(radix_handle, radix_len, 1),
                        ArrayArg::from_raw_parts::<u32>(partial_handle, partial_len, 1),
                        ArrayArg::from_raw_parts::<u32>(inv_handle, inv_len, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        is_intt,
                        cube_size,
                    )
                    .unwrap();
                }
            } else {
                // z_count=8 path: each thread handles 8 butterfly pairs
                let num_cubes_z8 = num_cubes / Z_COUNT;
                // Coalesced when not last step and domain large enough
                // (matches sppark: stage == iterations → non-coalesced)
                let coalesced = current_stage != step_size && lg_n >= 12;

                unsafe {
                    ntt::gs_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                        client,
                        CubeCount::Static(num_cubes_z8 as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(radix_handle, radix_len, 1),
                        ArrayArg::from_raw_parts::<u32>(partial_handle, partial_len, 1),
                        ArrayArg::from_raw_parts::<u32>(plus_one_handle, plus_one_len, 1),
                        ArrayArg::from_raw_parts::<u32>(inv_handle, inv_len, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        is_intt,
                        coalesced,
                        cube_size,
                    )
                    .unwrap();
                }
            }

            current_stage -= step_size;
        }
    }

    /// Run CT NTT (forward direction, RN order) on GPU data.
    ///
    /// Uses z_count=8 kernels when there are enough blocks.
    fn run_ct_ntt(
        client: &ComputeClient<CudaRuntime>,
        data_handle: &cubecl::server::Handle,
        n: usize,
        lg_n: u32,
        is_intt: bool,
        radix_handle: &cubecl::server::Handle,
        partial_handle: &cubecl::server::Handle,
        plus_one_handle: &cubecl::server::Handle,
        inv_handle: &cubecl::server::Handle,
    ) {
        let radix_len = 992usize;
        let partial_len = (twiddle::WINDOW_NUM * twiddle::WINDOW_SIZE) as usize;
        let plus_one_len = (twiddle::PLUS_ONE_ROWS * twiddle::PLUS_ONE_COLS) as usize;
        let inv_len = (twiddle::MAX_LG_DOMAIN_SIZE + 1) as usize;

        const Z_COUNT: usize = 8;

        // CT stage decomposition matching sppark ntt.cuh
        let steps = compute_ct_steps(lg_n);
        let mut current_stage = 0u32;

        for step_size in steps {
            let cube_size = 1usize << (step_size - 1);
            let num_threads = n / 2;
            let num_cubes = num_threads / cube_size;

            if num_cubes < Z_COUNT {
                // z_count=1 path for small sizes
                unsafe {
                    ntt::ct_ntt_step::launch_unchecked::<CudaRuntime>(
                        client,
                        CubeCount::Static(num_cubes as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(radix_handle, radix_len, 1),
                        ArrayArg::from_raw_parts::<u32>(partial_handle, partial_len, 1),
                        ArrayArg::from_raw_parts::<u32>(inv_handle, inv_len, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        is_intt,
                        cube_size,
                    )
                    .unwrap();
                }
            } else {
                // z_count=8 path
                let num_cubes_z8 = num_cubes / Z_COUNT;
                // Coalesced when not first step and domain large enough
                // (matches sppark: stage == 0 → non-coalesced)
                let coalesced = current_stage != 0 && lg_n >= 12;

                unsafe {
                    ntt::ct_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                        client,
                        CubeCount::Static(num_cubes_z8 as u32, 1, 1),
                        CubeDim::new_1d(cube_size as u32),
                        ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                        ArrayArg::from_raw_parts::<u32>(radix_handle, radix_len, 1),
                        ArrayArg::from_raw_parts::<u32>(partial_handle, partial_len, 1),
                        ArrayArg::from_raw_parts::<u32>(plus_one_handle, plus_one_len, 1),
                        ArrayArg::from_raw_parts::<u32>(inv_handle, inv_len, 1),
                        lg_n,
                        current_stage,
                        step_size,
                        is_intt,
                        coalesced,
                        cube_size,
                    )
                    .unwrap();
                }
            }

            current_stage += step_size;
        }
    }

    /// Compute GS step sizes (inverse of CT order).
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

    /// Compute CT step sizes.
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

    /// Launch bit-reversal permutation kernel with proper block sizing.
    fn launch_bit_rev(
        client: &ComputeClient<CudaRuntime>,
        data_handle: &cubecl::server::Handle,
        n: usize,
        lg_n: u32,
    ) {
        let block_size = n.min(1024) as u32;
        let num_blocks = ((n as u32) + block_size - 1) / block_size;
        unsafe {
            ntt::bit_rev_permutation::launch_unchecked::<CudaRuntime>(
                client,
                CubeCount::Static(num_blocks, 1, 1),
                CubeDim::new_1d(block_size),
                ArrayArg::from_raw_parts::<u32>(data_handle, n, 1),
                lg_n,
            )
            .unwrap();
        }
    }

    /// Test NTT roundtrip: forward(inverse(x)) == x
    #[test]
    #[gpu_guard::gpu_guard]
    fn test_ntt_roundtrip_small() {
        let client = get_client();

        // Pre-compute twiddle tables
        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let inv_plus_one = twiddle::generate_plus_one_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let fwd_radix_handle = client.create_from_slice(u32::as_bytes(&fwd_radix));
        let fwd_partial_handle = client.create_from_slice(u32::as_bytes(&fwd_partial));
        let fwd_plus_one_handle = client.create_from_slice(u32::as_bytes(&fwd_plus_one));
        let inv_radix_handle = client.create_from_slice(u32::as_bytes(&inv_radix));
        let inv_partial_handle = client.create_from_slice(u32::as_bytes(&inv_partial));
        let inv_plus_one_handle = client.create_from_slice(u32::as_bytes(&inv_plus_one));
        let inv_handle = client.create_from_slice(u32::as_bytes(&domain_inv));

        for lg_n in 1u32..=10 {
            let n = 1usize << lg_n;

            // Create test data: elements 1, 2, 3, ..., n
            let original: Vec<BabyBearElem> =
                (1..=n as u32).map(BabyBearElem::new).collect();
            let original_mont = elems_to_mont(&original);

            let data_handle = client.create_from_slice(u32::as_bytes(&original_mont));

            // Forward NTT (RN order): bit_rev + CT
            launch_bit_rev(&client, &data_handle, n, lg_n);

            run_ct_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                false,
                &fwd_radix_handle,
                &fwd_partial_handle,
                &fwd_plus_one_handle,
                &inv_handle,
            );

            // Inverse NTT (NR order): GS
            run_gs_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                true,
                &inv_radix_handle,
                &inv_partial_handle,
                &inv_plus_one_handle,
                &inv_handle,
            );

            // Bit-reverse to get back to natural order
            launch_bit_rev(&client, &data_handle, n, lg_n);

            let result = client.read_one(data_handle);
            let result_elems = mont_to_elems(u32::from_bytes(&result));

            assert_eq!(
                result_elems, original,
                "NTT roundtrip failed for lg_n={lg_n}"
            );
        }
    }

    /// Test NTT roundtrip for medium sizes (multi-step, lg_n 11-18).
    #[test]
    #[gpu_guard::gpu_guard]
    fn test_ntt_roundtrip_medium() {
        let client = get_client();

        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let inv_plus_one = twiddle::generate_plus_one_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let fwd_radix_handle = client.create_from_slice(u32::as_bytes(&fwd_radix));
        let fwd_partial_handle = client.create_from_slice(u32::as_bytes(&fwd_partial));
        let fwd_plus_one_handle = client.create_from_slice(u32::as_bytes(&fwd_plus_one));
        let inv_radix_handle = client.create_from_slice(u32::as_bytes(&inv_radix));
        let inv_partial_handle = client.create_from_slice(u32::as_bytes(&inv_partial));
        let inv_plus_one_handle = client.create_from_slice(u32::as_bytes(&inv_plus_one));
        let inv_handle = client.create_from_slice(u32::as_bytes(&domain_inv));

        for lg_n in 11u32..=18 {
            let n = 1usize << lg_n;

            let original: Vec<BabyBearElem> =
                (1..=n as u32).map(BabyBearElem::new).collect();
            let original_mont = elems_to_mont(&original);

            let data_handle = client.create_from_slice(u32::as_bytes(&original_mont));

            // Forward NTT
            launch_bit_rev(&client, &data_handle, n, lg_n);
            run_ct_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                false,
                &fwd_radix_handle,
                &fwd_partial_handle,
                &fwd_plus_one_handle,
                &inv_handle,
            );

            // Inverse NTT
            run_gs_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                true,
                &inv_radix_handle,
                &inv_partial_handle,
                &inv_plus_one_handle,
                &inv_handle,
            );

            // Bit-reverse to get back to natural order
            launch_bit_rev(&client, &data_handle, n, lg_n);

            let result = client.read_one(data_handle);
            let result_elems = mont_to_elems(u32::from_bytes(&result));

            assert_eq!(
                result_elems, original,
                "NTT roundtrip failed for lg_n={lg_n}"
            );
        }
    }

    /// Test GPU NTT against CPU reference implementation (small + medium sizes).
    #[test]
    #[gpu_guard::gpu_guard]
    fn test_ntt_vs_cpu() {
        use crate::core::ntt::{bit_reverse, evaluate_ntt, interpolate_ntt};

        let client = get_client();

        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let inv_plus_one = twiddle::generate_plus_one_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let fwd_radix_handle = client.create_from_slice(u32::as_bytes(&fwd_radix));
        let fwd_partial_handle = client.create_from_slice(u32::as_bytes(&fwd_partial));
        let fwd_plus_one_handle = client.create_from_slice(u32::as_bytes(&fwd_plus_one));
        let inv_radix_handle = client.create_from_slice(u32::as_bytes(&inv_radix));
        let inv_partial_handle = client.create_from_slice(u32::as_bytes(&inv_partial));
        let inv_plus_one_handle = client.create_from_slice(u32::as_bytes(&inv_plus_one));
        let inv_handle = client.create_from_slice(u32::as_bytes(&domain_inv));

        // Test single-step (1-10) and multi-step (11-16) sizes
        for lg_n in 1u32..=16 {
            let n = 1usize << lg_n;

            let data: Vec<BabyBearElem> =
                (1..=n as u32).map(BabyBearElem::new).collect();

            // CPU forward NTT: bit_reverse + evaluate_ntt gives natural-order output
            let mut cpu_fwd = data.clone();
            bit_reverse(&mut cpu_fwd);
            evaluate_ntt::<BabyBearElem, BabyBearElem>(&mut cpu_fwd, 0);

            // GPU forward NTT (RN order: bit_rev + CT)
            let gpu_data = elems_to_mont(&data);
            let data_handle = client.create_from_slice(u32::as_bytes(&gpu_data));

            launch_bit_rev(&client, &data_handle, n, lg_n);

            run_ct_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                false,
                &fwd_radix_handle,
                &fwd_partial_handle,
                &fwd_plus_one_handle,
                &inv_handle,
            );

            let result = client.read_one(data_handle);
            let gpu_fwd = mont_to_elems(u32::from_bytes(&result));

            assert_eq!(
                gpu_fwd, cpu_fwd,
                "Forward NTT mismatch at lg_n={lg_n}"
            );

            // CPU inverse NTT: interpolate_ntt produces bit-reversed output
            let mut cpu_inv = data.clone();
            interpolate_ntt::<BabyBearElem, BabyBearElem>(&mut cpu_inv);

            // GPU inverse NTT (NR order: GS)
            let gpu_data = elems_to_mont(&data);
            let data_handle = client.create_from_slice(u32::as_bytes(&gpu_data));

            run_gs_ntt(
                &client,
                &data_handle,
                n,
                lg_n,
                true,
                &inv_radix_handle,
                &inv_partial_handle,
                &inv_plus_one_handle,
                &inv_handle,
            );

            // GS produces NR (bit-reversed) output — don't bit-reverse,
            // since CPU interpolate_ntt also produces bit-reversed output
            let result = client.read_one(data_handle);
            let gpu_inv = mont_to_elems(u32::from_bytes(&result));

            assert_eq!(
                gpu_inv, cpu_inv,
                "Inverse NTT mismatch at lg_n={lg_n}"
            );
        }
    }

    // --- Performance Benchmark: cubecl vs sppark CUDA ---

    #[cfg(feature = "cuda")]
    #[test]
    #[ignore] // Run with: cargo test -p risc0-zkp --features cubecl,cuda -- bench_ntt_cubecl_vs_cuda --ignored --nocapture
    #[gpu_guard::gpu_guard]
    fn bench_ntt_cubecl_vs_cuda() {
        use std::time::Instant;

        // ---- cubecl setup ----
        let cl_client = get_client();

        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let inv_plus_one = twiddle::generate_plus_one_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let fwd_radix_handle = cl_client.create_from_slice(u32::as_bytes(&fwd_radix));
        let fwd_partial_handle = cl_client.create_from_slice(u32::as_bytes(&fwd_partial));
        let fwd_plus_one_handle = cl_client.create_from_slice(u32::as_bytes(&fwd_plus_one));
        let inv_radix_handle = cl_client.create_from_slice(u32::as_bytes(&inv_radix));
        let inv_partial_handle = cl_client.create_from_slice(u32::as_bytes(&inv_partial));
        let inv_plus_one_handle = cl_client.create_from_slice(u32::as_bytes(&inv_plus_one));
        let inv_handle = cl_client.create_from_slice(u32::as_bytes(&domain_inv));

        // ---- CUDA/sppark setup ----
        use cust::memory::{AsyncCopyDestination as _, GpuBuffer as _};
        use risc0_sys::cuda::{sppark_batch_NTT, sppark_batch_iNTT};

        cust::init(cust::CudaFlags::empty()).unwrap();
        let device = cust::device::Device::get_device(0).unwrap();
        let _ctx = cust::context::Context::new(device).unwrap();
        let cuda_stream = cust::stream::Stream::new(
            cust::stream::StreamFlags::NON_BLOCKING,
            None,
        )
        .unwrap();

        println!("\n{}", "=".repeat(80));
        println!("NTT Performance: cubecl (z_count=8) vs sppark CUDA (z_count=8)");
        println!("{}", "=".repeat(80));
        println!(
            "{:<8} {:>12} {:>12} {:>12} {:>12}",
            "lg_n", "cubecl_fwd", "cuda_fwd", "cubecl_inv", "cuda_inv"
        );
        println!("{}", "-".repeat(68));

        let warmup_iters = 3;
        let bench_iters = 10;

        for lg_n in [12u32, 14, 16, 18, 20, 22, 24] {
            let n = 1usize << lg_n;
            let data: Vec<u32> = (0..n)
                .map(|i| ((i as u64 * 31337 + 42) % 0x78000001) as u32)
                .collect();

            // ---- cubecl forward NTT ----
            let cl_handle = cl_client.create_from_slice(u32::as_bytes(&data));

            // Warmup
            for _ in 0..warmup_iters {
                launch_bit_rev(&cl_client, &cl_handle, n, lg_n);
                run_ct_ntt(
                    &cl_client,
                    &cl_handle,
                    n,
                    lg_n,
                    false,
                    &fwd_radix_handle,
                    &fwd_partial_handle,
                    &fwd_plus_one_handle,
                    &inv_handle,
                );
                // Reset data for next iteration
                let _ = cl_client.read_one(cl_handle.clone());
            }

            // Benchmark cubecl forward
            let cl_fwd_handle = cl_client.create_from_slice(u32::as_bytes(&data));
            let start = Instant::now();
            for _ in 0..bench_iters {
                launch_bit_rev(&cl_client, &cl_fwd_handle, n, lg_n);
                run_ct_ntt(
                    &cl_client,
                    &cl_fwd_handle,
                    n,
                    lg_n,
                    false,
                    &fwd_radix_handle,
                    &fwd_partial_handle,
                    &fwd_plus_one_handle,
                    &inv_handle,
                );
            }
            // Sync by reading back
            let _ = cl_client.read_one(cl_fwd_handle);
            let cl_fwd_us = start.elapsed().as_micros() / bench_iters as u128;

            // ---- cubecl inverse NTT ----
            let cl_inv_handle = cl_client.create_from_slice(u32::as_bytes(&data));
            // Warmup
            for _ in 0..warmup_iters {
                run_gs_ntt(
                    &cl_client,
                    &cl_inv_handle,
                    n,
                    lg_n,
                    true,
                    &inv_radix_handle,
                    &inv_partial_handle,
                    &inv_plus_one_handle,
                    &inv_handle,
                );
                let _ = cl_client.read_one(cl_inv_handle.clone());
            }

            let cl_inv_handle = cl_client.create_from_slice(u32::as_bytes(&data));
            let start = Instant::now();
            for _ in 0..bench_iters {
                run_gs_ntt(
                    &cl_client,
                    &cl_inv_handle,
                    n,
                    lg_n,
                    true,
                    &inv_radix_handle,
                    &inv_partial_handle,
                    &inv_plus_one_handle,
                    &inv_handle,
                );
            }
            let _ = cl_client.read_one(cl_inv_handle);
            let cl_inv_us = start.elapsed().as_micros() / bench_iters as u128;

            // ---- sppark CUDA forward NTT ----
            let byte_data: Vec<u8> = data.iter().flat_map(|v| v.to_le_bytes()).collect();
            let mut cuda_buf =
                unsafe { cust::memory::DeviceBuffer::uninitialized(byte_data.len()) }.unwrap();

            // Warmup
            for _ in 0..warmup_iters {
                unsafe {
                    cuda_buf
                        .async_copy_from(&byte_data, &cuda_stream)
                        .unwrap();
                }
                cuda_stream.synchronize().unwrap();
                let err = unsafe {
                    sppark_batch_NTT(cuda_stream.as_inner(), cuda_buf.as_device_ptr(), lg_n, 1)
                };
                assert_eq!(err.code, 0, "sppark_batch_NTT failed");
                cuda_stream.synchronize().unwrap();
            }

            // Benchmark sppark forward
            unsafe {
                cuda_buf
                    .async_copy_from(&byte_data, &cuda_stream)
                    .unwrap();
            }
            cuda_stream.synchronize().unwrap();
            let start = Instant::now();
            for _ in 0..bench_iters {
                let err = unsafe {
                    sppark_batch_NTT(cuda_stream.as_inner(), cuda_buf.as_device_ptr(), lg_n, 1)
                };
                assert_eq!(err.code, 0);
            }
            cuda_stream.synchronize().unwrap();
            let cuda_fwd_us = start.elapsed().as_micros() / bench_iters as u128;

            // ---- sppark CUDA inverse NTT ----
            // Warmup
            for _ in 0..warmup_iters {
                unsafe {
                    cuda_buf
                        .async_copy_from(&byte_data, &cuda_stream)
                        .unwrap();
                }
                cuda_stream.synchronize().unwrap();
                let err = unsafe {
                    sppark_batch_iNTT(cuda_stream.as_inner(), cuda_buf.as_device_ptr(), lg_n, 1)
                };
                assert_eq!(err.code, 0, "sppark_batch_iNTT failed");
                cuda_stream.synchronize().unwrap();
            }

            // Benchmark sppark inverse
            unsafe {
                cuda_buf
                    .async_copy_from(&byte_data, &cuda_stream)
                    .unwrap();
            }
            cuda_stream.synchronize().unwrap();
            let start = Instant::now();
            for _ in 0..bench_iters {
                let err = unsafe {
                    sppark_batch_iNTT(cuda_stream.as_inner(), cuda_buf.as_device_ptr(), lg_n, 1)
                };
                assert_eq!(err.code, 0);
            }
            cuda_stream.synchronize().unwrap();
            let cuda_inv_us = start.elapsed().as_micros() / bench_iters as u128;

            println!(
                "{:<8} {:>9} us {:>9} us {:>9} us {:>9} us  ({:.1}x / {:.1}x)",
                lg_n,
                cl_fwd_us,
                cuda_fwd_us,
                cl_inv_us,
                cuda_inv_us,
                cl_fwd_us as f64 / cuda_fwd_us.max(1) as f64,
                cl_inv_us as f64 / cuda_inv_us.max(1) as f64,
            );
        }

        println!("{}", "-".repeat(68));
        println!("Note: both cubecl and sppark use z_count=8");
        println!("Ratio >1 means cubecl is slower.\n");
    }

    /// Debug test: compare z8 single-step output against z1 for CT.
    #[test]
    #[gpu_guard::gpu_guard]
    fn test_ct_z8_vs_z1_single_step() {
        let client = get_client();

        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let fwd_plus_one = twiddle::generate_plus_one_twiddles(false);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let radix_handle = client.create_from_slice(u32::as_bytes(&fwd_radix));
        let partial_handle = client.create_from_slice(u32::as_bytes(&fwd_partial));
        let plus_one_handle = client.create_from_slice(u32::as_bytes(&fwd_plus_one));
        let inv_handle = client.create_from_slice(u32::as_bytes(&domain_inv));

        let radix_len = 992usize;
        let partial_len = (twiddle::WINDOW_NUM * twiddle::WINDOW_SIZE) as usize;
        let plus_one_len = (twiddle::PLUS_ONE_ROWS * twiddle::PLUS_ONE_COLS) as usize;
        let inv_len = (twiddle::MAX_LG_DOMAIN_SIZE + 1) as usize;

        let lg_n = 11u32;
        let n = 1usize << lg_n;
        let steps = compute_ct_steps(lg_n); // [5, 6]

        // Create test data (pre-bit-reversed)
        let data: Vec<BabyBearElem> = (1..=n as u32).map(BabyBearElem::new).collect();
        let data_mont = elems_to_mont(&data);

        // --- Run first CT step with z1 ---
        let z1_handle = client.create_from_slice(u32::as_bytes(&data_mont));
        launch_bit_rev(&client, &z1_handle, n, lg_n);
        let step_size = steps[0]; // 5
        let cube_size = 1usize << (step_size - 1);
        let num_threads = n / 2;
        let num_cubes = num_threads / cube_size;
        unsafe {
            ntt::ct_ntt_step::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::Static(num_cubes as u32, 1, 1),
                CubeDim::new_1d(cube_size as u32),
                ArrayArg::from_raw_parts::<u32>(&z1_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&radix_handle, radix_len, 1),
                ArrayArg::from_raw_parts::<u32>(&partial_handle, partial_len, 1),
                ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                lg_n,
                0u32,
                step_size,
                false,
                cube_size,
            )
            .unwrap();
        }
        let z1_result = client.read_one(z1_handle);
        let z1_data = u32::from_bytes(&z1_result).to_vec();

        // --- Run first CT step with z8 ---
        let z8_handle = client.create_from_slice(u32::as_bytes(&data_mont));
        launch_bit_rev(&client, &z8_handle, n, lg_n);
        let num_cubes_z8 = num_cubes / 8;
        unsafe {
            ntt::ct_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::Static(num_cubes_z8 as u32, 1, 1),
                CubeDim::new_1d(cube_size as u32),
                ArrayArg::from_raw_parts::<u32>(&z8_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&radix_handle, radix_len, 1),
                ArrayArg::from_raw_parts::<u32>(&partial_handle, partial_len, 1),
                ArrayArg::from_raw_parts::<u32>(&plus_one_handle, plus_one_len, 1),
                ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                lg_n,
                0u32,
                step_size,
                false,
                false, // coalesced
                cube_size,
            )
            .unwrap();
        }
        let z8_result = client.read_one(z8_handle);
        let z8_data = u32::from_bytes(&z8_result).to_vec();

        // Compare
        let mut mismatches = 0;
        for i in 0..n {
            if z1_data[i] != z8_data[i] {
                if mismatches < 20 {
                    println!(
                        "  pos {i}: z1=0x{:08x} z8=0x{:08x}",
                        z1_data[i], z8_data[i]
                    );
                }
                mismatches += 1;
            }
        }
        if mismatches > 0 {
            println!("Total mismatches: {mismatches} / {n}");
            // Also print first 40 values from each
            println!("z1[0..40]: {:08x?}", &z1_data[0..40]);
            println!("z8[0..40]: {:08x?}", &z8_data[0..40]);
        }
        assert_eq!(mismatches, 0, "z8 step 1 CT mismatch at lg_n={lg_n}");

        // --- Now run step 2 on step 1's output ---
        // Run z1 step 2 on z1 step 1 output
        let z1_step2_handle = client.create_from_slice(u32::as_bytes(&z1_data));
        let step2_size = steps[1]; // 6
        let cube_size2 = 1usize << (step2_size - 1);
        let num_cubes2 = num_threads / cube_size2;
        unsafe {
            ntt::ct_ntt_step::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::Static(num_cubes2 as u32, 1, 1),
                CubeDim::new_1d(cube_size2 as u32),
                ArrayArg::from_raw_parts::<u32>(&z1_step2_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&radix_handle, radix_len, 1),
                ArrayArg::from_raw_parts::<u32>(&partial_handle, partial_len, 1),
                ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                lg_n,
                step_size, // stage = 5
                step2_size, // iterations = 6
                false,
                cube_size2,
            )
            .unwrap();
        }
        let z1_s2_result = client.read_one(z1_step2_handle);
        let z1_s2_data = u32::from_bytes(&z1_s2_result).to_vec();

        // Run z8 step 2 on z8 step 1 output (which matches z1 step 1)
        let z8_step2_handle = client.create_from_slice(u32::as_bytes(&z8_data));
        let num_cubes2_z8 = num_cubes2 / 8;
        let coalesced2 = step_size != 0 && lg_n >= 12; // stage=5, lg_n=11 → false
        unsafe {
            ntt::ct_ntt_step_z8::launch_unchecked::<CudaRuntime>(
                &client,
                CubeCount::Static(num_cubes2_z8 as u32, 1, 1),
                CubeDim::new_1d(cube_size2 as u32),
                ArrayArg::from_raw_parts::<u32>(&z8_step2_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&radix_handle, radix_len, 1),
                ArrayArg::from_raw_parts::<u32>(&partial_handle, partial_len, 1),
                ArrayArg::from_raw_parts::<u32>(&plus_one_handle, plus_one_len, 1),
                ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                lg_n,
                step_size, // stage = 5
                step2_size, // iterations = 6
                false,
                coalesced2,
                cube_size2,
            )
            .unwrap();
        }
        let z8_s2_result = client.read_one(z8_step2_handle);
        let z8_s2_data = u32::from_bytes(&z8_s2_result).to_vec();

        // Compare step 2
        let mut mismatches2 = 0;
        for i in 0..n {
            if z1_s2_data[i] != z8_s2_data[i] {
                if mismatches2 < 20 {
                    println!(
                        "  step2 pos {i}: z1=0x{:08x} z8=0x{:08x}",
                        z1_s2_data[i], z8_s2_data[i]
                    );
                }
                mismatches2 += 1;
            }
        }
        if mismatches2 > 0 {
            println!("Step 2 total mismatches: {mismatches2} / {n}");
            println!("z1_s2[0..40]: {:08x?}", &z1_s2_data[0..40]);
            println!("z8_s2[0..40]: {:08x?}", &z8_s2_data[0..40]);
            println!("z1_s2[32..40]: {:08x?}", &z1_s2_data[32..40]);
            println!("z8_s2[32..40]: {:08x?}", &z8_s2_data[32..40]);
        }
        assert_eq!(mismatches2, 0, "z8 step 2 CT mismatch at lg_n={lg_n}");
    }
}
