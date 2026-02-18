use cubecl::cuda::{CudaDevice, CudaRuntime};
use cubecl::prelude::*;
use risc0_core::field::{Elem, baby_bear::BabyBearElem};

use super::ntt;
use super::twiddle;

fn get_client() -> ComputeClient<CudaRuntime> {
    let device = CudaDevice::new(0);
    CudaRuntime::client(&device)
}

#[cfg(feature = "cubecl-cpu")]
fn get_cpu_client() -> ComputeClient<cubecl::cpu::CpuRuntime> {
    let device = cubecl::cpu::CpuDevice::default();
    cubecl::cpu::CpuRuntime::client(&device)
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
    let b_elems: Vec<_> = (0..n)
        .map(|i| BabyBearElem::new(i as u32 * 7 + 3))
        .collect();
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
    let b_elems: Vec<_> = (0..n)
        .map(|i| BabyBearElem::new(i as u32 * 7 + 3))
        .collect();
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
        let original: Vec<BabyBearElem> = (1..=n as u32).map(BabyBearElem::new).collect();
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

        let original: Vec<BabyBearElem> = (1..=n as u32).map(BabyBearElem::new).collect();
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

        let data: Vec<BabyBearElem> = (1..=n as u32).map(BabyBearElem::new).collect();

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

        assert_eq!(gpu_fwd, cpu_fwd, "Forward NTT mismatch at lg_n={lg_n}");

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

        assert_eq!(gpu_inv, cpu_inv, "Inverse NTT mismatch at lg_n={lg_n}");
    }
}

// --- Performance Benchmark: cubecl vs sppark CUDA ---

#[cfg(feature = "cuda")]
#[test]
#[ignore]
// Run with: cargo test -p risc0-zkp --features cubecl,cuda -- bench_ntt_cubecl_vs_cuda --ignored --nocapture
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
    let cuda_stream =
        cust::stream::Stream::new(cust::stream::StreamFlags::NON_BLOCKING, None).unwrap();

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
                cuda_buf.async_copy_from(&byte_data, &cuda_stream).unwrap();
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
            cuda_buf.async_copy_from(&byte_data, &cuda_stream).unwrap();
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
                cuda_buf.async_copy_from(&byte_data, &cuda_stream).unwrap();
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
            cuda_buf.async_copy_from(&byte_data, &cuda_stream).unwrap();
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
                println!("  pos {i}: z1=0x{:08x} z8=0x{:08x}", z1_data[i], z8_data[i]);
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
            step_size,  // stage = 5
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
            step_size,  // stage = 5
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

// --- Extension Field Arithmetic Tests ---

/// Test kernel for bb4_mul: multiplies pairs of ExtElem values.
/// Input: interleaved [a0,a1,a2,a3, b0,b1,b2,b3, ...] (8 u32 per pair)
/// Output: [r0,r1,r2,r3, ...] (4 u32 per result)
#[cube(launch_unchecked)]
fn ext_mul_kernel(input: &Array<u32>, out: &mut Array<u32>, #[comptime] count: u32) {
    let idx = ABSOLUTE_POS as u32;
    if idx < count {
        let a_base = (idx * 8u32) as usize;
        let b_base = (idx * 8u32 + 4u32) as usize;
        let o_base = (idx * 4u32) as usize;
        let mut r0: u32 = input[a_base];
        let mut r1: u32 = input[a_base + 1usize];
        let mut r2: u32 = input[a_base + 2usize];
        let mut r3: u32 = input[a_base + 3usize];
        crate::hal::cubecl::ext_field::bb4_mul(
            &mut r0,
            &mut r1,
            &mut r2,
            &mut r3,
            input[b_base],
            input[b_base + 1usize],
            input[b_base + 2usize],
            input[b_base + 3usize],
        );
        out[o_base] = r0;
        out[o_base + 1usize] = r1;
        out[o_base + 2usize] = r2;
        out[o_base + 3usize] = r3;
    }
}

#[test]
#[gpu_guard::gpu_guard]
fn test_ext_field_mul() {
    use risc0_core::field::ExtElem as _;
    use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

    let client = get_client();
    let n = 32usize; // number of multiplications

    // Generate test data: pairs of ExtElem values
    let a_exts: Vec<BabyBearExtElem> = (0..n)
        .map(|i| {
            BabyBearExtElem::from_subelems(
                (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 31337 + 17)),
            )
        })
        .collect();
    let b_exts: Vec<BabyBearExtElem> = (0..n)
        .map(|i| {
            BabyBearExtElem::from_subelems(
                (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 7919 + 42)),
            )
        })
        .collect();

    // Expected: CPU multiplication
    let expected: Vec<BabyBearExtElem> = a_exts.iter().zip(&b_exts).map(|(a, b)| *a * *b).collect();

    // Pack input: [a0,a1,a2,a3, b0,b1,b2,b3, a0,a1,a2,a3, b0,b1,b2,b3, ...]
    let mut input_mont: Vec<u32> = Vec::with_capacity(n * 8);
    for (a, b) in a_exts.iter().zip(&b_exts) {
        input_mont.extend_from_slice(&a.to_u32_words());
        input_mont.extend_from_slice(&b.to_u32_words());
    }

    let input_handle = client.create_from_slice(u32::as_bytes(&input_mont));
    let out_handle = client.empty(n * 4 * size_of::<u32>());

    unsafe {
        ext_mul_kernel::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(n as u32),
            ArrayArg::from_raw_parts::<u32>(&input_handle, n * 8, 1),
            ArrayArg::from_raw_parts::<u32>(&out_handle, n * 4, 1),
            n as u32,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);

    for i in 0..n {
        let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
        assert_eq!(got, expected[i], "ExtElem mul mismatch at index {i}");
    }
}

// --- Phase 9/10: Elementwise kernel tests ---

#[test]
#[gpu_guard::gpu_guard]
fn test_eltwise_add() {
    let client = get_client();
    let n = 64usize;
    let x: Vec<BabyBearElem> = (0..n)
        .map(|i| BabyBearElem::new(i as u32 * 1000 + 1))
        .collect();
    let y: Vec<BabyBearElem> = (0..n)
        .map(|i| BabyBearElem::new(i as u32 * 2000 + 3))
        .collect();
    let expected: Vec<BabyBearElem> = x.iter().zip(&y).map(|(a, b)| *a + *b).collect();
    let x_mont = elems_to_mont(&x);
    let y_mont = elems_to_mont(&y);
    let x_handle = client.create_from_slice(u32::as_bytes(&x_mont));
    let y_handle = client.create_from_slice(u32::as_bytes(&y_mont));
    let out_handle = client.empty(n * size_of::<u32>());
    unsafe {
        super::kernels::eltwise_add::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(n as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
            ArrayArg::from_raw_parts::<u32>(&x_handle, n, 1),
            ArrayArg::from_raw_parts::<u32>(&y_handle, n, 1),
            n as u32,
        )
        .unwrap();
    }
    let result = client.read_one(out_handle);
    let result_elems = mont_to_elems(u32::from_bytes(&result));
    assert_eq!(result_elems, expected, "eltwise_add mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_eltwise_copy() {
    let client = get_client();
    let n = 64usize;
    let input: Vec<BabyBearElem> = (0..n)
        .map(|i| BabyBearElem::new(i as u32 * 777 + 42))
        .collect();
    let input_mont = elems_to_mont(&input);
    let in_handle = client.create_from_slice(u32::as_bytes(&input_mont));
    let out_handle = client.empty(n * size_of::<u32>());
    unsafe {
        super::kernels::eltwise_copy::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(n as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
            ArrayArg::from_raw_parts::<u32>(&in_handle, n, 1),
            n as u32,
        )
        .unwrap();
    }
    let result = client.read_one(out_handle);
    let result_elems = mont_to_elems(u32::from_bytes(&result));
    assert_eq!(result_elems, input, "eltwise_copy mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_eltwise_zeroize() {
    let client = get_client();
    // Mix valid values with INVALID (0xffffffff)
    let data: Vec<u32> = (0..32)
        .map(|i| if i % 3 == 0 { 0xffffffffu32 } else { i * 100 })
        .collect();
    let expected: Vec<u32> = data
        .iter()
        .map(|&v| if v == 0xffffffff { 0 } else { v })
        .collect();
    let handle = client.create_from_slice(u32::as_bytes(&data));
    unsafe {
        super::kernels::eltwise_zeroize::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(data.len() as u32),
            ArrayArg::from_raw_parts::<u32>(&handle, data.len(), 1),
            data.len() as u32,
        )
        .unwrap();
    }
    let result = client.read_one(handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected[..], "eltwise_zeroize mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_gather_sample() {
    let client = get_client();
    // src = 5x4 matrix (5 rows, stride=4), gather column idx=2
    let src: Vec<u32> = (0..20).map(|i| i * 10 + 1).collect();
    let size = 5u32;
    let stride = 4u32;
    let idx = 2u32;
    // Expected: src[0*4+2]=21, src[1*4+2]=61, src[2*4+2]=101, src[3*4+2]=141, src[4*4+2]=181
    let expected: Vec<u32> = (0..size)
        .map(|g| src[(g * stride + idx) as usize])
        .collect();
    let src_handle = client.create_from_slice(u32::as_bytes(&src));
    let dst_handle = client.empty(size as usize * size_of::<u32>());
    unsafe {
        super::kernels::gather_sample::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(size),
            ArrayArg::from_raw_parts::<u32>(&dst_handle, size as usize, 1),
            ArrayArg::from_raw_parts::<u32>(&src_handle, src.len(), 1),
            idx,
            size,
            stride,
        )
        .unwrap();
    }
    let result = client.read_one(dst_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected[..], "gather_sample mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_scatter() {
    let client = get_client();
    // Setup: 3 groups, each scattering a few values
    // index = [0, 2, 3, 6] -> group 0: items 0..2, group 1: items 2..3, group 2: items 3..6
    let index: Vec<u32> = vec![0, 2, 3, 6];
    let offsets: Vec<u32> = vec![5, 1, 7, 0, 3, 9]; // where each value goes
    let values: Vec<u32> = vec![100, 200, 300, 400, 500, 600];
    let count = 3u32; // 3 groups
    let into_size = 10usize;
    // Expected: into[5]=100, into[1]=200, into[7]=300, into[0]=400, into[3]=500, into[9]=600
    let mut expected = vec![0u32; into_size];
    for g in 0..count as usize {
        for i in index[g] as usize..index[g + 1] as usize {
            expected[offsets[i] as usize] = values[i];
        }
    }
    let into_handle = client.create_from_slice(u32::as_bytes(&vec![0u32; into_size]));
    let index_handle = client.create_from_slice(u32::as_bytes(&index));
    let offsets_handle = client.create_from_slice(u32::as_bytes(&offsets));
    let values_handle = client.create_from_slice(u32::as_bytes(&values));
    unsafe {
        super::kernels::scatter::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(count),
            ArrayArg::from_raw_parts::<u32>(&into_handle, into_size, 1),
            ArrayArg::from_raw_parts::<u32>(&index_handle, index.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&offsets_handle, offsets.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&values_handle, values.len(), 1),
            count,
        )
        .unwrap();
    }
    let result = client.read_one(into_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected[..], "scatter mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_eltwise_copy_region() {
    let client = get_client();
    // from: 3 rows x 2 cols, stride=4, offset=1
    // into: stride=5, offset=2
    let from_rows = 3u32;
    let from_cols = 2u32;
    let from_stride = 4u32;
    let from_offset = 1u32;
    let into_stride = 5u32;
    let into_offset = 2u32;
    let from_data: Vec<u32> = (0..12).map(|i| i * 10 + 1).collect();
    let into_size = (into_offset + from_rows * into_stride) as usize;
    let mut expected = vec![0u32; into_size];
    for row in 0..from_rows {
        for col in 0..from_cols {
            expected[(into_offset + row * into_stride + col) as usize] =
                from_data[(from_offset + row * from_stride + col) as usize];
        }
    }
    let from_handle = client.create_from_slice(u32::as_bytes(&from_data));
    let into_handle = client.create_from_slice(u32::as_bytes(&vec![0u32; into_size]));
    unsafe {
        super::kernels::eltwise_copy_region::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(from_rows),
            ArrayArg::from_raw_parts::<u32>(&into_handle, into_size, 1),
            ArrayArg::from_raw_parts::<u32>(&from_handle, from_data.len(), 1),
            from_rows,
            from_cols,
            from_offset,
            from_stride,
            into_offset,
            into_stride,
        )
        .unwrap();
    }
    let result = client.read_one(into_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected[..], "eltwise_copy_region mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_batch_expand() {
    let client = get_client();
    // 2 polynomials, in_size=4, expand by 2 bits -> out_size=16
    let poly_count = 2u32;
    let in_size = 4u32;
    let expand_bits = 2u32;
    let out_size = in_size * (1 << expand_bits);
    let input: Vec<u32> = (0..poly_count * in_size).map(|i| i * 100 + 7).collect();
    // Expected: output[row * out_size + col] = input[row * in_size + (col >> expand_bits)]
    let total = (poly_count * out_size) as usize;
    let expected: Vec<u32> = (0..total as u32)
        .map(|i| {
            let row = i / out_size;
            let col = i % out_size;
            input[(row * in_size + (col >> expand_bits)) as usize]
        })
        .collect();
    let in_handle = client.create_from_slice(u32::as_bytes(&input));
    let out_handle = client.empty(total * size_of::<u32>());
    unsafe {
        super::kernels::batch_expand::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(total as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, total, 1),
            ArrayArg::from_raw_parts::<u32>(&in_handle, input.len(), 1),
            in_size,
            out_size,
            expand_bits,
        )
        .unwrap();
    }
    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected[..], "batch_expand mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_zk_shift() {
    use risc0_core::field::{Elem as _, baby_bear::BabyBearElem as Elem};

    let client = get_client();
    let n_bits = 4u32;
    let count = 1u32 << n_bits; // 16 elements
    let poly_count = 2u32;
    let total = (count * poly_count) as usize;

    // Generate input coefficients
    let input: Vec<Elem> = (0..total)
        .map(|i| Elem::new(i as u32 * 31337 + 17))
        .collect();
    let three = Elem::new(3);

    // CPU reference: multiply each coeff by pow(3, bit_reverse(pos, n_bits))
    let expected: Vec<Elem> = input
        .iter()
        .enumerate()
        .map(|(i, &coeff)| {
            let pos = i as u32 % count;
            let mut rev = 0u32;
            let mut v = pos;
            for _ in 0..n_bits {
                rev = (rev << 1) | (v & 1);
                v >>= 1;
            }
            let mut factor = Elem::ONE;
            for _ in 0..rev {
                factor = factor * three;
            }
            coeff * factor
        })
        .collect();

    let data_mont = elems_to_mont(&input);
    let handle = client.create_from_slice(u32::as_bytes(&data_mont));

    // Montgomery form of 3: Elem::new(3).to_u32_words()[0]
    let three_mont = Elem::new(3).to_u32_words()[0];
    unsafe {
        super::kernels::zk_shift::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(total as u32),
            ArrayArg::from_raw_parts::<u32>(&handle, total, 1),
            count,
            n_bits,
            poly_count,
            three_mont,
        )
        .unwrap();
    }
    let result = client.read_one(handle);
    let result_elems = mont_to_elems(u32::from_bytes(&result));
    assert_eq!(result_elems, expected, "zk_shift mismatch");
}

// --- Phase 11: Extension field kernel tests ---

#[test]
#[gpu_guard::gpu_guard]
fn test_eltwise_sum_extelem() {
    use risc0_core::field::ExtElem as _;
    use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

    let client = get_client();
    let count = 16usize; // output elements
    let to_add = 5usize; // ExtElems to sum per output

    // Generate input: to_add * count ExtElems in AoS layout
    let exts: Vec<BabyBearExtElem> = (0..to_add * count)
        .map(|i| {
            BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new((i * 4 + j) as u32 * 1337 + 7)))
        })
        .collect();

    // CPU reference: sum to_add ExtElems per position
    let expected: Vec<BabyBearExtElem> = (0..count)
        .map(|idx| {
            let mut tot = BabyBearExtElem::ZERO;
            for i in 0..to_add {
                tot += exts[count * i + idx];
            }
            tot
        })
        .collect();

    // Pack input as AoS: each ExtElem is 4 consecutive u32
    let input_mont: Vec<u32> = exts.iter().flat_map(|e| e.to_u32_words()).collect();

    let in_handle = client.create_from_slice(u32::as_bytes(&input_mont));
    let out_handle = client.empty(count * 4 * size_of::<u32>());

    unsafe {
        super::kernels::eltwise_sum_extelem::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(count as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, count * 4, 1),
            ArrayArg::from_raw_parts::<u32>(&in_handle, input_mont.len(), 1),
            to_add as u32,
            count as u32,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);

    // Output is SoA: 4 arrays of count elements
    for i in 0..count {
        let got = BabyBearExtElem::from_u32_words(&[
            result_u32[i],
            result_u32[i + count],
            result_u32[i + 2 * count],
            result_u32[i + 3 * count],
        ]);
        assert_eq!(got, expected[i], "eltwise_sum_extelem mismatch at {i}");
    }
}

#[test]
#[gpu_guard::gpu_guard]
fn test_fri_fold() {
    use risc0_core::field::ExtElem as _;
    use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

    let client = get_client();
    let count = 8usize;
    let fri_fold_count = 16usize;

    // Generate mix value
    let mix = BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 1000 + 42)));

    // Generate input: SoA layout — 4 arrays of count*16
    // Input data: random extension field elements
    let input_exts: Vec<BabyBearExtElem> = (0..count * fri_fold_count)
        .map(|i| {
            BabyBearExtElem::from_subelems(
                (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 7919 + 13)),
            )
        })
        .collect();

    // CPU reference
    let expected: Vec<BabyBearExtElem> = (0..count)
        .map(|idx| {
            let mut tot = BabyBearExtElem::ZERO;
            let mut cur_mix = BabyBearExtElem::ONE;
            for i in 0..fri_fold_count {
                // bit-reverse i within 4 bits
                let rev_i = ((i & 1) << 3) | ((i & 2) << 1) | ((i & 4) >> 1) | ((i & 8) >> 3);
                let rev_idx = rev_i * count + idx;
                tot += cur_mix * input_exts[rev_idx];
                cur_mix = cur_mix * mix;
            }
            tot
        })
        .collect();

    // Pack input in SoA layout: 4 arrays of count*16
    // Component k is at input[k * count * 16 + rev_i * count + idx]
    let total = count * fri_fold_count;
    let mut input_soa = vec![0u32; total * 4];
    for k in 0..4 {
        for i in 0..total {
            input_soa[k * total + i] = input_exts[i].to_u32_words()[k];
        }
    }

    let in_handle = client.create_from_slice(u32::as_bytes(&input_soa));
    let out_handle = client.empty(count * 4 * size_of::<u32>());

    let mix_words = mix.to_u32_words();
    unsafe {
        super::kernels::fri_fold::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(count as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, count * 4, 1),
            ArrayArg::from_raw_parts::<u32>(&in_handle, input_soa.len(), 1),
            ScalarArg::new(mix_words[0]),
            ScalarArg::new(mix_words[1]),
            ScalarArg::new(mix_words[2]),
            ScalarArg::new(mix_words[3]),
            count as u32,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);

    // Output is SoA: 4 arrays of count
    for i in 0..count {
        let got = BabyBearExtElem::from_u32_words(&[
            result_u32[i],
            result_u32[i + count],
            result_u32[i + 2 * count],
            result_u32[i + 3 * count],
        ]);
        assert_eq!(got, expected[i], "fri_fold mismatch at {i}");
    }
}

#[test]
#[gpu_guard::gpu_guard]
fn test_batch_evaluate_any() {
    use risc0_core::field::ExtElem as _;
    use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

    let client = get_client();
    let deg = 32u32; // polynomial degree
    let poly_count = 2u32;
    let eval_count = 3usize; // number of evaluations

    // Generate coefficients for 2 polynomials
    let coeffs: Vec<Elem> = (0..(poly_count * deg) as usize)
        .map(|i| Elem::new(i as u32 * 1337 + 17))
        .collect();

    // which[i] = which polynomial to evaluate
    let which_data: Vec<u32> = vec![0, 1, 0];

    // Evaluation points (ExtElem, AoS layout)
    let xs: Vec<BabyBearExtElem> = (0..eval_count)
        .map(|i| {
            BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new((i * 4 + j) as u32 * 9973 + 5)))
        })
        .collect();

    // CPU reference: Horner evaluation
    let expected: Vec<BabyBearExtElem> = (0..eval_count)
        .map(|e| {
            let poly_idx = which_data[e] as usize;
            let poly_base = poly_idx * deg as usize;
            let x = xs[e];
            let mut tot = BabyBearExtElem::ZERO;
            let mut powx = BabyBearExtElem::ONE;
            for i in 0..deg as usize {
                tot += powx
                    * BabyBearExtElem::from_subelems(
                        std::iter::once(coeffs[poly_base + i])
                            .chain(std::iter::repeat(Elem::ZERO).take(3)),
                    );
                powx = powx * x;
            }
            tot
        })
        .collect();

    // Pack GPU data
    let coeffs_mont = elems_to_mont(&coeffs);
    let xs_mont: Vec<u32> = xs.iter().flat_map(|x| x.to_u32_words()).collect();

    let coeffs_handle = client.create_from_slice(u32::as_bytes(&coeffs_mont));
    let which_handle = client.create_from_slice(u32::as_bytes(&which_data));
    let xs_handle = client.create_from_slice(u32::as_bytes(&xs_mont));
    let out_handle = client.empty(eval_count * 4 * size_of::<u32>());

    let cube_size = 32usize; // threads per block
    unsafe {
        super::kernels::batch_evaluate_any::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::Static(eval_count as u32, 1, 1),
            CubeDim::new_1d(cube_size as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, eval_count * 4, 1),
            ArrayArg::from_raw_parts::<u32>(&coeffs_handle, coeffs_mont.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&which_handle, which_data.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&xs_handle, xs_mont.len(), 1),
            deg,
            cube_size,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);

    // Output is AoS: each ExtElem is 4 consecutive u32
    for i in 0..eval_count {
        let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
        assert_eq!(got, expected[i], "batch_evaluate_any mismatch at {i}");
    }
}

#[test]
#[gpu_guard::gpu_guard]
fn test_mix_poly_coeffs() {
    use risc0_core::field::ExtElem as _;
    use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

    let client = get_client();
    let count = 8u32; // coefficients per polynomial
    let input_size = 4u32; // number of input polynomials
    let combo_count = 3u32; // number of distinct combo groups

    // combos[i] = which group polynomial i belongs to
    let combos_data: Vec<u32> = vec![0, 1, 2, 1];

    // Input coefficients (Fp)
    let input_coeffs: Vec<Elem> = (0..(input_size * count) as usize)
        .map(|i| Elem::new(i as u32 * 2003 + 11))
        .collect();

    // mix_start and mix (ExtElem)
    let mix_start = BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 500 + 1)));
    let mix = BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 300 + 7)));

    // CPU reference
    let mut expected = vec![BabyBearExtElem::ZERO; (combo_count * count) as usize];
    for idx in 0..count as usize {
        let mut cur = mix_start;
        for i in 0..input_size as usize {
            let id = combos_data[i] as usize;
            let coeff = input_coeffs[count as usize * i + idx];
            let ext_coeff = BabyBearExtElem::from_subelems(
                std::iter::once(coeff).chain(std::iter::repeat(Elem::ZERO).take(3)),
            );
            expected[count as usize * id + idx] += cur * ext_coeff;
            cur = cur * mix;
        }
    }

    // Pack GPU data
    let input_mont = elems_to_mont(&input_coeffs);
    // Output is FpExt* (AoS): combo_count * count ExtElems, each 4 u32
    let out_total = (combo_count * count * 4) as usize;
    let out_data = vec![0u32; out_total];

    let input_handle = client.create_from_slice(u32::as_bytes(&input_mont));
    let combos_handle = client.create_from_slice(u32::as_bytes(&combos_data));
    let out_handle = client.create_from_slice(u32::as_bytes(&out_data));

    let ms_words = mix_start.to_u32_words();
    let m_words = mix.to_u32_words();

    unsafe {
        super::kernels::mix_poly_coeffs::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(count),
            ArrayArg::from_raw_parts::<u32>(&out_handle, out_total, 1),
            ArrayArg::from_raw_parts::<u32>(&input_handle, input_mont.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&combos_handle, combos_data.len(), 1),
            ScalarArg::new(ms_words[0]),
            ScalarArg::new(ms_words[1]),
            ScalarArg::new(ms_words[2]),
            ScalarArg::new(ms_words[3]),
            ScalarArg::new(m_words[0]),
            ScalarArg::new(m_words[1]),
            ScalarArg::new(m_words[2]),
            ScalarArg::new(m_words[3]),
            input_size,
            count,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);

    // Output is AoS: each ExtElem is 4 consecutive u32
    for i in 0..(combo_count * count) as usize {
        let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
        assert_eq!(got, expected[i], "mix_poly_coeffs mismatch at {i}");
    }
}

// --- Poseidon2 Tests ---

#[test]
#[gpu_guard::gpu_guard]
fn test_poseidon2_mix() {
    use crate::core::hash::poseidon2::{consts::CELLS, poseidon2_mix as cpu_mix};

    let client = get_client();

    // Input: [0, 1, 2, ..., 23]
    let mut cpu_state = [BabyBearElem::ZERO; CELLS];
    for i in 0..CELLS {
        cpu_state[i] = BabyBearElem::new(i as u32);
    }
    let input_mont: Vec<u32> = cpu_state.iter().map(|e| e.to_u32_words()[0]).collect();

    // Run CPU mix
    cpu_mix(&mut cpu_state);
    let expected_mont: Vec<u32> = cpu_state.iter().map(|e| e.to_u32_words()[0]).collect();

    // Generate GPU constants
    let rc = super::poseidon2::generate_round_constants();
    let m_int_diag = super::poseidon2::generate_m_int_diag();

    let input_handle = client.create_from_slice(u32::as_bytes(&input_mont));
    let rc_handle = client.create_from_slice(u32::as_bytes(&rc));
    let diag_handle = client.create_from_slice(u32::as_bytes(&m_int_diag));
    let out_handle = client.empty(CELLS * size_of::<u32>());

    unsafe {
        super::poseidon2::poseidon2_mix_test::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::new_single(),
            CubeDim::new_1d(1),
            ArrayArg::from_raw_parts::<u32>(&out_handle, CELLS, 1),
            ArrayArg::from_raw_parts::<u32>(&input_handle, CELLS, 1),
            ArrayArg::from_raw_parts::<u32>(&rc_handle, rc.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&diag_handle, m_int_diag.len(), 1),
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(result_u32, &expected_mont[..], "poseidon2_mix mismatch");
}

#[test]
#[gpu_guard::gpu_guard]
fn test_poseidon2_fold() {
    use crate::core::hash::poseidon2::{
        consts::CELLS, poseidon2_mix as cpu_mix, CELLS_OUT, CELLS_RATE,
    };

    let client = get_client();
    let num_hashes = 4usize;

    // Build input and expected output using CPU poseidon2_mix
    let mut inputs = Vec::new();
    let mut expected_outputs = Vec::new();

    for h in 0..num_hashes {
        let mut cpu_state = [BabyBearElem::ZERO; CELLS];
        for j in 0..CELLS_RATE {
            cpu_state[j] = BabyBearElem::new((h * CELLS_RATE + j + 1) as u32);
        }
        // cells[16..23] are zero

        // Collect input (rate portion only)
        for j in 0..CELLS_RATE {
            inputs.push(cpu_state[j].to_u32_words()[0]);
        }

        // Run CPU mix
        cpu_mix(&mut cpu_state);

        // Expected output: first 8 cells
        for j in 0..CELLS_OUT {
            expected_outputs.push(cpu_state[j].to_u32_words()[0]);
        }
    }

    let rc = super::poseidon2::generate_round_constants();
    let m_int_diag = super::poseidon2::generate_m_int_diag();

    let input_handle = client.create_from_slice(u32::as_bytes(&inputs));
    let rc_handle = client.create_from_slice(u32::as_bytes(&rc));
    let diag_handle = client.create_from_slice(u32::as_bytes(&m_int_diag));
    let out_handle = client.empty(num_hashes * CELLS_OUT * size_of::<u32>());

    let block_size = 256usize;
    let num_blocks = (num_hashes as u32 + block_size as u32 - 1) / block_size as u32;

    unsafe {
        super::poseidon2::poseidon2_fold::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::Static(num_blocks, 1, 1),
            CubeDim::new_1d(block_size as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, num_hashes * CELLS_OUT, 1),
            ArrayArg::from_raw_parts::<u32>(&input_handle, inputs.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&rc_handle, rc.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&diag_handle, m_int_diag.len(), 1),
            num_hashes as u32,
            block_size,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(
        result_u32,
        &expected_outputs[..],
        "poseidon2_fold mismatch"
    );
}

#[test]
#[gpu_guard::gpu_guard]
fn test_poseidon2_rows() {
    use crate::core::hash::poseidon2::{unpadded_hash, CELLS_OUT};

    let client = get_client();
    let dim_x = 4usize; // number of rows
    let dim_y = 32usize; // columns per row

    // Create per-row data
    let row_data: Vec<Vec<BabyBearElem>> = (0..dim_x)
        .map(|row| {
            (0..dim_y)
                .map(|col| BabyBearElem::new((row * dim_y + col + 1) as u32))
                .collect()
        })
        .collect();

    // Column-major layout: matrix[row + col * dim_x]
    let mut matrix_mont = vec![0u32; dim_x * dim_y];
    for row in 0..dim_x {
        for col in 0..dim_y {
            matrix_mont[row + col * dim_x] = row_data[row][col].to_u32_words()[0];
        }
    }

    // CPU reference: hash each row
    let mut expected_outputs = Vec::new();
    for row in 0..dim_x {
        let result = unpadded_hash(row_data[row].iter());
        for j in 0..CELLS_OUT {
            expected_outputs.push(result[j].to_u32_words()[0]);
        }
    }

    let rc = super::poseidon2::generate_round_constants();
    let m_int_diag = super::poseidon2::generate_m_int_diag();

    let matrix_handle = client.create_from_slice(u32::as_bytes(&matrix_mont));
    let rc_handle = client.create_from_slice(u32::as_bytes(&rc));
    let diag_handle = client.create_from_slice(u32::as_bytes(&m_int_diag));
    let out_handle = client.empty(dim_x * CELLS_OUT * size_of::<u32>());

    let block_size = 256usize;
    let num_blocks = (dim_x as u32 + block_size as u32 - 1) / block_size as u32;

    unsafe {
        super::poseidon2::poseidon2_rows::launch_unchecked::<CudaRuntime>(
            &client,
            CubeCount::Static(num_blocks, 1, 1),
            CubeDim::new_1d(block_size as u32),
            ArrayArg::from_raw_parts::<u32>(&out_handle, dim_x * CELLS_OUT, 1),
            ArrayArg::from_raw_parts::<u32>(&matrix_handle, matrix_mont.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&rc_handle, rc.len(), 1),
            ArrayArg::from_raw_parts::<u32>(&diag_handle, m_int_diag.len(), 1),
            dim_x as u32,
            dim_y as u32,
            block_size,
        )
        .unwrap();
    }

    let result = client.read_one(out_handle);
    let result_u32 = u32::from_bytes(&result);
    assert_eq!(
        result_u32,
        &expected_outputs[..],
        "poseidon2_rows mismatch"
    );
}

// ==========================================================================
// CPU backend tests — run same cubecl kernels on cubecl's MLIR CPU backend
// ==========================================================================

#[cfg(feature = "cubecl-cpu")]
mod cpu_tests {
    use cubecl::prelude::*;
    use risc0_core::field::Elem;
    use risc0_core::field::baby_bear::BabyBearElem;

    use super::{elems_to_mont, mont_to_elems};

    type R = cubecl::cpu::CpuRuntime;

    fn client() -> ComputeClient<R> {
        super::get_cpu_client()
    }

    #[test]
    fn test_field_add() {
        let client = client();
        let n = 64usize;
        let a_elems: Vec<_> = (0..n).map(|i| BabyBearElem::new(i as u32 + 1)).collect();
        let b_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 7 + 3))
            .collect();
        let expected: Vec<_> = a_elems.iter().zip(&b_elems).map(|(a, b)| *a + *b).collect();
        let a_mont = elems_to_mont(&a_elems);
        let b_mont = elems_to_mont(&b_elems);
        let a_handle = client.create_from_slice(u32::as_bytes(&a_mont));
        let b_handle = client.create_from_slice(u32::as_bytes(&b_mont));
        let out_handle = client.empty(n * size_of::<u32>());
        unsafe {
            super::field_add_kernel::launch_unchecked::<R>(
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
        assert_eq!(result_elems, expected, "CPU field add mismatch");
    }

    #[test]
    fn test_field_sub() {
        let client = client();
        let n = 64usize;
        let a_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 13 + 100))
            .collect();
        let b_elems: Vec<_> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 7 + 3))
            .collect();
        let expected: Vec<_> = a_elems.iter().zip(&b_elems).map(|(a, b)| *a - *b).collect();
        let a_mont = elems_to_mont(&a_elems);
        let b_mont = elems_to_mont(&b_elems);
        let a_handle = client.create_from_slice(u32::as_bytes(&a_mont));
        let b_handle = client.create_from_slice(u32::as_bytes(&b_mont));
        let out_handle = client.empty(n * size_of::<u32>());
        unsafe {
            super::field_sub_kernel::launch_unchecked::<R>(
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
        assert_eq!(result_elems, expected, "CPU field sub mismatch");
    }

    #[test]
    fn test_field_mul() {
        let client = client();
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
            super::field_mul_kernel::launch_unchecked::<R>(
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
        assert_eq!(result_elems, expected, "CPU field mul mismatch");
    }

    #[test]
    fn test_ext_field_mul() {
        use risc0_core::field::ExtElem as _;
        use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

        let client = client();
        let n = 32usize;
        let a_exts: Vec<BabyBearExtElem> = (0..n)
            .map(|i| {
                BabyBearExtElem::from_subelems(
                    (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 31337 + 17)),
                )
            })
            .collect();
        let b_exts: Vec<BabyBearExtElem> = (0..n)
            .map(|i| {
                BabyBearExtElem::from_subelems(
                    (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 7919 + 42)),
                )
            })
            .collect();
        let expected: Vec<BabyBearExtElem> =
            a_exts.iter().zip(&b_exts).map(|(a, b)| *a * *b).collect();
        let mut input_mont: Vec<u32> = Vec::with_capacity(n * 8);
        for (a, b) in a_exts.iter().zip(&b_exts) {
            input_mont.extend_from_slice(&a.to_u32_words());
            input_mont.extend_from_slice(&b.to_u32_words());
        }
        let input_handle = client.create_from_slice(u32::as_bytes(&input_mont));
        let out_handle = client.empty(n * 4 * size_of::<u32>());
        unsafe {
            super::ext_mul_kernel::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(n as u32),
                ArrayArg::from_raw_parts::<u32>(&input_handle, n * 8, 1),
                ArrayArg::from_raw_parts::<u32>(&out_handle, n * 4, 1),
                n as u32,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_u32 = u32::from_bytes(&result);
        for i in 0..n {
            let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
            assert_eq!(got, expected[i], "CPU ExtElem mul mismatch at {i}");
        }
    }

    #[test]
    fn test_eltwise_add() {
        let client = client();
        let n = 64usize;
        let x: Vec<BabyBearElem> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 1000 + 1))
            .collect();
        let y: Vec<BabyBearElem> = (0..n)
            .map(|i| BabyBearElem::new(i as u32 * 2000 + 3))
            .collect();
        let expected: Vec<BabyBearElem> = x.iter().zip(&y).map(|(a, b)| *a + *b).collect();
        let x_mont = elems_to_mont(&x);
        let y_mont = elems_to_mont(&y);
        let x_handle = client.create_from_slice(u32::as_bytes(&x_mont));
        let y_handle = client.create_from_slice(u32::as_bytes(&y_mont));
        let out_handle = client.empty(n * size_of::<u32>());
        unsafe {
            crate::hal::cubecl::kernels::eltwise_add::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(n as u32),
                ArrayArg::from_raw_parts::<u32>(&out_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&x_handle, n, 1),
                ArrayArg::from_raw_parts::<u32>(&y_handle, n, 1),
                n as u32,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_elems = mont_to_elems(u32::from_bytes(&result));
        assert_eq!(result_elems, expected, "CPU eltwise_add mismatch");
    }

    #[test]
    fn test_eltwise_zeroize() {
        let client = client();
        let data: Vec<u32> = (0..32)
            .map(|i| if i % 3 == 0 { 0xffffffffu32 } else { i * 100 })
            .collect();
        let expected: Vec<u32> = data
            .iter()
            .map(|&v| if v == 0xffffffff { 0 } else { v })
            .collect();
        let handle = client.create_from_slice(u32::as_bytes(&data));
        unsafe {
            crate::hal::cubecl::kernels::eltwise_zeroize::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(data.len() as u32),
                ArrayArg::from_raw_parts::<u32>(&handle, data.len(), 1),
                data.len() as u32,
            )
            .unwrap();
        }
        let result = client.read_one(handle);
        let result_u32 = u32::from_bytes(&result);
        assert_eq!(result_u32, &expected[..], "CPU eltwise_zeroize mismatch");
    }

    #[test]
    fn test_gather_sample() {
        let client = client();
        let src: Vec<u32> = (0..20).map(|i| i * 10 + 1).collect();
        let size = 5u32;
        let stride = 4u32;
        let idx = 2u32;
        let expected: Vec<u32> = (0..size)
            .map(|g| src[(g * stride + idx) as usize])
            .collect();
        let src_handle = client.create_from_slice(u32::as_bytes(&src));
        let dst_handle = client.empty(size as usize * size_of::<u32>());
        unsafe {
            crate::hal::cubecl::kernels::gather_sample::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(size),
                ArrayArg::from_raw_parts::<u32>(&dst_handle, size as usize, 1),
                ArrayArg::from_raw_parts::<u32>(&src_handle, src.len(), 1),
                idx,
                size,
                stride,
            )
            .unwrap();
        }
        let result = client.read_one(dst_handle);
        let result_u32 = u32::from_bytes(&result);
        assert_eq!(result_u32, &expected[..], "CPU gather_sample mismatch");
    }

    #[test]
    fn test_scatter() {
        let client = client();
        let index: Vec<u32> = vec![0, 2, 3, 6];
        let offsets: Vec<u32> = vec![5, 1, 7, 0, 3, 9];
        let values: Vec<u32> = vec![100, 200, 300, 400, 500, 600];
        let count = 3u32;
        let into_size = 10usize;
        let mut expected = vec![0u32; into_size];
        for g in 0..count as usize {
            for i in index[g] as usize..index[g + 1] as usize {
                expected[offsets[i] as usize] = values[i];
            }
        }
        let into_handle = client.create_from_slice(u32::as_bytes(&vec![0u32; into_size]));
        let index_handle = client.create_from_slice(u32::as_bytes(&index));
        let offsets_handle = client.create_from_slice(u32::as_bytes(&offsets));
        let values_handle = client.create_from_slice(u32::as_bytes(&values));
        unsafe {
            crate::hal::cubecl::kernels::scatter::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(count),
                ArrayArg::from_raw_parts::<u32>(&into_handle, into_size, 1),
                ArrayArg::from_raw_parts::<u32>(&index_handle, index.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&offsets_handle, offsets.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&values_handle, values.len(), 1),
                count,
            )
            .unwrap();
        }
        let result = client.read_one(into_handle);
        let result_u32 = u32::from_bytes(&result);
        assert_eq!(result_u32, &expected[..], "CPU scatter mismatch");
    }

    #[test]
    fn test_batch_expand() {
        let client = client();
        let poly_count = 2u32;
        let in_size = 4u32;
        let expand_bits = 2u32;
        let out_size = in_size * (1 << expand_bits);
        let input: Vec<u32> = (0..poly_count * in_size).map(|i| i * 100 + 7).collect();
        let total = (poly_count * out_size) as usize;
        let expected: Vec<u32> = (0..total as u32)
            .map(|i| {
                let row = i / out_size;
                let col = i % out_size;
                input[(row * in_size + (col >> expand_bits)) as usize]
            })
            .collect();
        let in_handle = client.create_from_slice(u32::as_bytes(&input));
        let out_handle = client.empty(total * size_of::<u32>());
        unsafe {
            crate::hal::cubecl::kernels::batch_expand::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(total as u32),
                ArrayArg::from_raw_parts::<u32>(&out_handle, total, 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input.len(), 1),
                in_size,
                out_size,
                expand_bits,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_u32 = u32::from_bytes(&result);
        assert_eq!(result_u32, &expected[..], "CPU batch_expand mismatch");
    }

    #[test]
    fn test_zk_shift() {
        use risc0_core::field::Elem as _;

        let client = client();
        let n_bits = 4u32;
        let count = 1u32 << n_bits;
        let poly_count = 2u32;
        let total = (count * poly_count) as usize;
        let input: Vec<BabyBearElem> = (0..total)
            .map(|i| BabyBearElem::new(i as u32 * 31337 + 17))
            .collect();
        let three = BabyBearElem::new(3);
        let expected: Vec<BabyBearElem> = input
            .iter()
            .enumerate()
            .map(|(i, &coeff)| {
                let pos = i as u32 % count;
                let mut rev = 0u32;
                let mut v = pos;
                for _ in 0..n_bits {
                    rev = (rev << 1) | (v & 1);
                    v >>= 1;
                }
                let mut factor = BabyBearElem::ONE;
                for _ in 0..rev {
                    factor = factor * three;
                }
                coeff * factor
            })
            .collect();
        let data_mont = elems_to_mont(&input);
        let handle = client.create_from_slice(u32::as_bytes(&data_mont));
        let three_mont = BabyBearElem::new(3).to_u32_words()[0];
        unsafe {
            crate::hal::cubecl::kernels::zk_shift::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(total as u32),
                ArrayArg::from_raw_parts::<u32>(&handle, total, 1),
                count,
                n_bits,
                poly_count,
                three_mont,
            )
            .unwrap();
        }
        let result = client.read_one(handle);
        let result_elems = mont_to_elems(u32::from_bytes(&result));
        assert_eq!(result_elems, expected, "CPU zk_shift mismatch");
    }

    #[test]
    fn test_fri_fold() {
        use risc0_core::field::ExtElem as _;
        use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

        let client = client();
        let count = 8usize;
        let fri_fold_count = 16usize;
        let mix = BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 1000 + 42)));
        let input_exts: Vec<BabyBearExtElem> = (0..count * fri_fold_count)
            .map(|i| {
                BabyBearExtElem::from_subelems(
                    (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 7919 + 13)),
                )
            })
            .collect();
        let expected: Vec<BabyBearExtElem> = (0..count)
            .map(|idx| {
                let mut tot = BabyBearExtElem::ZERO;
                let mut cur_mix = BabyBearExtElem::ONE;
                for i in 0..fri_fold_count {
                    let rev_i = ((i & 1) << 3) | ((i & 2) << 1) | ((i & 4) >> 1) | ((i & 8) >> 3);
                    let rev_idx = rev_i * count + idx;
                    tot += cur_mix * input_exts[rev_idx];
                    cur_mix = cur_mix * mix;
                }
                tot
            })
            .collect();
        let total = count * fri_fold_count;
        let mut input_soa = vec![0u32; total * 4];
        for k in 0..4 {
            for i in 0..total {
                input_soa[k * total + i] = input_exts[i].to_u32_words()[k];
            }
        }
        let in_handle = client.create_from_slice(u32::as_bytes(&input_soa));
        let out_handle = client.empty(count * 4 * size_of::<u32>());
        let mix_words = mix.to_u32_words();
        unsafe {
            crate::hal::cubecl::kernels::fri_fold::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(count as u32),
                ArrayArg::from_raw_parts::<u32>(&out_handle, count * 4, 1),
                ArrayArg::from_raw_parts::<u32>(&in_handle, input_soa.len(), 1),
                ScalarArg::new(mix_words[0]),
                ScalarArg::new(mix_words[1]),
                ScalarArg::new(mix_words[2]),
                ScalarArg::new(mix_words[3]),
                count as u32,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_u32 = u32::from_bytes(&result);
        for i in 0..count {
            let got = BabyBearExtElem::from_u32_words(&[
                result_u32[i],
                result_u32[i + count],
                result_u32[i + 2 * count],
                result_u32[i + 3 * count],
            ]);
            assert_eq!(got, expected[i], "CPU fri_fold mismatch at {i}");
        }
    }

    #[test]
    fn test_batch_evaluate_any() {
        use risc0_core::field::ExtElem as _;
        use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

        let client = client();
        let deg = 32u32;
        let poly_count = 2u32;
        let eval_count = 3usize;
        let coeffs: Vec<Elem> = (0..(poly_count * deg) as usize)
            .map(|i| Elem::new(i as u32 * 1337 + 17))
            .collect();
        let which_data: Vec<u32> = vec![0, 1, 0];
        let xs: Vec<BabyBearExtElem> = (0..eval_count)
            .map(|i| {
                BabyBearExtElem::from_subelems(
                    (0..4).map(|j| Elem::new((i * 4 + j) as u32 * 9973 + 5)),
                )
            })
            .collect();
        let expected: Vec<BabyBearExtElem> = (0..eval_count)
            .map(|e| {
                let poly_idx = which_data[e] as usize;
                let poly_base = poly_idx * deg as usize;
                let x = xs[e];
                let mut tot = BabyBearExtElem::ZERO;
                let mut powx = BabyBearExtElem::ONE;
                for i in 0..deg as usize {
                    tot += powx
                        * BabyBearExtElem::from_subelems(
                            std::iter::once(coeffs[poly_base + i])
                                .chain(std::iter::repeat(Elem::ZERO).take(3)),
                        );
                    powx = powx * x;
                }
                tot
            })
            .collect();
        let coeffs_mont = elems_to_mont(&coeffs);
        let xs_mont: Vec<u32> = xs.iter().flat_map(|x| x.to_u32_words()).collect();
        let coeffs_handle = client.create_from_slice(u32::as_bytes(&coeffs_mont));
        let which_handle = client.create_from_slice(u32::as_bytes(&which_data));
        let xs_handle = client.create_from_slice(u32::as_bytes(&xs_mont));
        let out_handle = client.empty(eval_count * 4 * size_of::<u32>());
        let cube_size = 32usize;
        unsafe {
            crate::hal::cubecl::kernels::batch_evaluate_any::launch_unchecked::<R>(
                &client,
                CubeCount::Static(eval_count as u32, 1, 1),
                CubeDim::new_1d(cube_size as u32),
                ArrayArg::from_raw_parts::<u32>(&out_handle, eval_count * 4, 1),
                ArrayArg::from_raw_parts::<u32>(&coeffs_handle, coeffs_mont.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&which_handle, which_data.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&xs_handle, xs_mont.len(), 1),
                deg,
                cube_size,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_u32 = u32::from_bytes(&result);
        for i in 0..eval_count {
            let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
            assert_eq!(got, expected[i], "CPU batch_evaluate_any mismatch at {i}");
        }
    }

    #[test]
    #[ignore]
    fn test_mix_poly_coeffs() {
        use risc0_core::field::ExtElem as _;
        use risc0_core::field::baby_bear::{BabyBearElem as Elem, BabyBearExtElem};

        let client = client();
        let count = 8u32;
        let input_size = 4u32;
        let combo_count = 3u32;
        let combos_data: Vec<u32> = vec![0, 1, 2, 1];
        let input_coeffs: Vec<Elem> = (0..(input_size * count) as usize)
            .map(|i| Elem::new(i as u32 * 2003 + 11))
            .collect();
        let mix_start =
            BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 500 + 1)));
        let mix = BabyBearExtElem::from_subelems((0..4).map(|j| Elem::new(j as u32 * 300 + 7)));
        let mut expected = vec![BabyBearExtElem::ZERO; (combo_count * count) as usize];
        for idx in 0..count as usize {
            let mut cur = mix_start;
            for i in 0..input_size as usize {
                let id = combos_data[i] as usize;
                let coeff = input_coeffs[count as usize * i + idx];
                let ext_coeff = BabyBearExtElem::from_subelems(
                    std::iter::once(coeff).chain(std::iter::repeat(Elem::ZERO).take(3)),
                );
                expected[count as usize * id + idx] += cur * ext_coeff;
                cur = cur * mix;
            }
        }
        let input_mont = elems_to_mont(&input_coeffs);
        let out_total = (combo_count * count * 4) as usize;
        let out_data = vec![0u32; out_total];
        let input_handle = client.create_from_slice(u32::as_bytes(&input_mont));
        let combos_handle = client.create_from_slice(u32::as_bytes(&combos_data));
        let out_handle = client.create_from_slice(u32::as_bytes(&out_data));
        let ms_words = mix_start.to_u32_words();
        let m_words = mix.to_u32_words();
        unsafe {
            crate::hal::cubecl::kernels::mix_poly_coeffs::launch_unchecked::<R>(
                &client,
                CubeCount::new_single(),
                CubeDim::new_1d(count),
                ArrayArg::from_raw_parts::<u32>(&out_handle, out_total, 1),
                ArrayArg::from_raw_parts::<u32>(&input_handle, input_mont.len(), 1),
                ArrayArg::from_raw_parts::<u32>(&combos_handle, combos_data.len(), 1),
                ScalarArg::new(ms_words[0]),
                ScalarArg::new(ms_words[1]),
                ScalarArg::new(ms_words[2]),
                ScalarArg::new(ms_words[3]),
                ScalarArg::new(m_words[0]),
                ScalarArg::new(m_words[1]),
                ScalarArg::new(m_words[2]),
                ScalarArg::new(m_words[3]),
                input_size,
                count,
            )
            .unwrap();
        }
        let result = client.read_one(out_handle);
        let result_u32 = u32::from_bytes(&result);
        for i in 0..(combo_count * count) as usize {
            let got = BabyBearExtElem::from_u32_words(&result_u32[i * 4..(i + 1) * 4]);
            assert_eq!(got, expected[i], "CPU mix_poly_coeffs mismatch at {i}");
        }
    }

    #[test]
    #[ignore]
    fn test_ntt_roundtrip_small() {
        use super::twiddle;

        let client = client();
        let fwd_radix = twiddle::generate_radix_twiddles(false);
        let fwd_partial = twiddle::generate_partial_twiddles(false);
        let inv_radix = twiddle::generate_radix_twiddles(true);
        let inv_partial = twiddle::generate_partial_twiddles(true);
        let domain_inv = twiddle::generate_domain_size_inverses();

        let fwd_radix_handle = client.create_from_slice(u32::as_bytes(&fwd_radix));
        let fwd_partial_handle = client.create_from_slice(u32::as_bytes(&fwd_partial));
        let inv_radix_handle = client.create_from_slice(u32::as_bytes(&inv_radix));
        let inv_partial_handle = client.create_from_slice(u32::as_bytes(&inv_partial));
        let inv_handle = client.create_from_slice(u32::as_bytes(&domain_inv));

        let radix_len = 992usize;
        let partial_len = (twiddle::WINDOW_NUM * twiddle::WINDOW_SIZE) as usize;
        let inv_len = (twiddle::MAX_LG_DOMAIN_SIZE + 1) as usize;

        use super::ntt;

        // Test single-step sizes (1-10) using z1 kernels only
        for lg_n in 1u32..=10 {
            let n = 1usize << lg_n;
            let original: Vec<BabyBearElem> = (1..=n as u32).map(BabyBearElem::new).collect();
            let original_mont = elems_to_mont(&original);
            let data_handle = client.create_from_slice(u32::as_bytes(&original_mont));

            // Bit-reverse
            let block_size = n.min(1024) as u32;
            let num_blocks = ((n as u32) + block_size - 1) / block_size;
            unsafe {
                ntt::bit_rev_permutation::launch_unchecked::<R>(
                    &client,
                    CubeCount::Static(num_blocks, 1, 1),
                    CubeDim::new_1d(block_size),
                    ArrayArg::from_raw_parts::<u32>(&data_handle, n, 1),
                    lg_n,
                )
                .unwrap();
            }

            // Forward CT NTT (single step, z1 only)
            let cube_size = 1usize << (lg_n - 1);
            let num_cubes = (n / 2) / cube_size;
            unsafe {
                ntt::ct_ntt_step::launch_unchecked::<R>(
                    &client,
                    CubeCount::Static(num_cubes as u32, 1, 1),
                    CubeDim::new_1d(cube_size as u32),
                    ArrayArg::from_raw_parts::<u32>(&data_handle, n, 1),
                    ArrayArg::from_raw_parts::<u32>(&fwd_radix_handle, radix_len, 1),
                    ArrayArg::from_raw_parts::<u32>(&fwd_partial_handle, partial_len, 1),
                    ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                    lg_n,
                    0u32,
                    lg_n,
                    false,
                    cube_size,
                )
                .unwrap();
            }

            // Inverse GS NTT (single step, z1 only)
            unsafe {
                ntt::gs_ntt_step::launch_unchecked::<R>(
                    &client,
                    CubeCount::Static(num_cubes as u32, 1, 1),
                    CubeDim::new_1d(cube_size as u32),
                    ArrayArg::from_raw_parts::<u32>(&data_handle, n, 1),
                    ArrayArg::from_raw_parts::<u32>(&inv_radix_handle, radix_len, 1),
                    ArrayArg::from_raw_parts::<u32>(&inv_partial_handle, partial_len, 1),
                    ArrayArg::from_raw_parts::<u32>(&inv_handle, inv_len, 1),
                    lg_n,
                    lg_n,
                    lg_n,
                    true,
                    cube_size,
                )
                .unwrap();
            }

            // Bit-reverse back
            unsafe {
                ntt::bit_rev_permutation::launch_unchecked::<R>(
                    &client,
                    CubeCount::Static(num_blocks, 1, 1),
                    CubeDim::new_1d(block_size),
                    ArrayArg::from_raw_parts::<u32>(&data_handle, n, 1),
                    lg_n,
                )
                .unwrap();
            }

            let result = client.read_one(data_handle);
            let result_elems = mont_to_elems(u32::from_bytes(&result));
            assert_eq!(
                result_elems, original,
                "CPU NTT roundtrip failed for lg_n={lg_n}"
            );
        }
    }
}
