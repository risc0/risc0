use alloc::sync::Arc;
use core::{
    cell::{Ref, RefMut},
    marker::PhantomData,
    ops::Range,
    slice::{from_raw_parts, from_raw_parts_mut},
};
use std::{
    cell::RefCell,
    rc::Rc,
    sync::{Once, RwLock},
};

use bytemuck::Pod;
use ec_gpu::GpuField;
use ec_gpu_gen::{
    rust_gpu_tools::{opencl, program_closures, Device, GPUError, Program},
    threadpool::{Worker, THREAD_POOL},
    EcError, EcResult, SourceBuilder,
};
use ndarray::{ArrayView, ArrayViewMut, Axis};
use rayon::prelude::*;

use crate::{
    adapter::{PolyExt, PolyExtContext, PolyFp, PolyFpContext},
    core::{
        fp::Fp,
        fp4::Fp4,
        log2_ceil,
        ntt::{bit_rev_32, bit_reverse, evaluate_ntt, expand, interpolate_ntt},
        rou::ROU_FWD,
        sha::{Digest, Sha},
        sha_cpu,
    },
    field::{baby_bear::BabyBear, Elem, ExtElem, Field},
    hal::{
        cpu::{CpuBuffer, CpuHal},
        Buffer, EvalCheck, Hal,
    },
    verify::VerifyHal,
    FRI_FOLD, INV_RATE,
};

/// Marker trait for [`Field`]s that support GPU operations via [`ec-gpu`].
pub trait GpuHalField: sealed::Sealed {}
impl<F: sealed::Sealed> GpuHalField for F {}
mod sealed {
    use super::*;

    #[doc(hidden)]
    pub trait Sealed<Elem = <Self as Field>::Elem, ExtElem = <Self as Field>::ExtElem>:
        Field
    {
    }
    impl<F: Field> Sealed<F::Elem, F::ExtElem> for F
    where
        F::Elem: GpuField,
        F::ExtElem: GpuField,
    {
    }
}

pub struct GpuHal<F: GpuHalField> {
    cpu: CpuHal<F>,
    kernel: FieldKernel<F>,
}

impl<F: GpuHalField> GpuHal<F> {
    pub fn new() -> Self {
        Self {
            cpu: CpuHal::new(),
            kernel: FieldKernel::new(),
        }
    }
}

impl<F: GpuHalField> Hal for GpuHal<F> {
    type Field = F;

    type BufferFp = CpuBuffer<F::Elem>;
    type BufferFp4 = CpuBuffer<F::ExtElem>;
    type BufferDigest = CpuBuffer<Digest>;
    type BufferU32 = CpuBuffer<u32>;

    fn alloc_fp(&self, size: usize) -> Self::BufferFp {
        self.cpu.alloc_fp(size)
    }

    fn copy_fp_from(&self, slice: &[F::Elem]) -> Self::BufferFp {
        self.cpu.copy_fp_from(slice)
    }

    fn alloc_fp4(&self, size: usize) -> Self::BufferFp4 {
        self.cpu.alloc_fp4(size)
    }

    fn copy_fp4_from(&self, slice: &[F::ExtElem]) -> Self::BufferFp4 {
        self.cpu.copy_fp4_from(slice)
    }

    fn alloc_digest(&self, size: usize) -> Self::BufferDigest {
        self.cpu.alloc_digest(size)
    }

    fn copy_digest_from(&self, slice: &[Digest]) -> Self::BufferDigest {
        self.cpu.copy_digest_from(slice)
    }

    fn alloc_u32(&self, size: usize) -> Self::BufferU32 {
        self.cpu.alloc_u32(size)
    }

    fn copy_u32_from(&self, slice: &[u32]) -> Self::BufferU32 {
        self.cpu.copy_u32_from(slice)
    }

    fn batch_expand(&self, output: &Self::BufferFp, input: &Self::BufferFp, count: usize) {
        // let out_size = output.size() / count;
        // let in_size = input.size() / count;
        // let expand_bits = log2_ceil(out_size / in_size);
        // assert_eq!(out_size, in_size * (1 << expand_bits));
        // assert_eq!(out_size * count, output.size());
        // assert_eq!(in_size * count, input.size());
        // output
        //     .as_slice_mut()
        //     .par_chunks_exact_mut(out_size)
        //     .zip(input.as_slice().par_chunks_exact(in_size))
        //     .for_each(|(output, input)| {
        //         expand(output, input, expand_bits);
        //     });

        self.cpu.batch_expand(output, input, count)
    }

    fn batch_evaluate_ntt(&self, io: &Self::BufferFp, count: usize, expand_bits: usize) {
        // let row_size = io.size() / count;
        // assert_eq!(row_size * count, io.size());
        // io.as_slice_mut()
        //     .par_chunks_exact_mut(row_size)
        //     .for_each(|row| {
        //         evaluate_ntt::<F::Elem, F::Elem>(row, expand_bits);
        //     });

        self.cpu.batch_evaluate_ntt(io, count, expand_bits)
    }

    fn batch_interpolate_ntt(&self, io: &Self::BufferFp, count: usize) {
        // let row_size = io.size() / count;
        // assert_eq!(row_size * count, io.size());
        // io.as_slice_mut()
        //     .par_chunks_exact_mut(row_size)
        //     .for_each(|row| {
        //         interpolate_ntt::<F::Elem, F::Elem>(row);
        //     });

        self.cpu.batch_interpolate_ntt(io, count)
    }

    fn batch_bit_reverse(&self, io: &Self::BufferFp, count: usize) {
        // let row_size = io.size() / count;
        // assert_eq!(row_size * count, io.size());
        // io.as_slice_mut()
        //     .par_chunks_exact_mut(row_size)
        //     .for_each(|row| {
        //         bit_reverse(row);
        //     });

        self.cpu.batch_bit_reverse(io, count)
    }

    fn batch_evaluate_any(
        &self,
        coeffs: &Self::BufferFp,
        poly_count: usize,
        which: &Self::BufferU32,
        xs: &Self::BufferFp4,
        out: &Self::BufferFp4,
    ) {
        // let po2 = log2_ceil(coeffs.size() / poly_count);
        // assert_eq!(poly_count * (1 << po2), coeffs.size());
        // let eval_count = which.size();
        // assert_eq!(xs.size(), eval_count);
        // assert_eq!(out.size(), eval_count);

        // let coeffs = coeffs.as_slice().to_vec(); // TODO: avoid copy
        // let which = which.as_slice();
        // let xs = xs.as_slice();
        // let mut out = out.as_slice_mut();
        // (&which[..], &xs[..], &mut out[..])
        //     .into_par_iter()
        //     .for_each(|(id, x, out)| {
        //         let mut tot = F::ExtElem::ZERO;
        //         let mut cur = F::ExtElem::ONE;
        //         let id = *id as usize;
        //         let count = 1 << po2;
        //         let local = &coeffs[count * id..count * id + count];
        //         for coeff in local {
        //             tot += cur * *coeff;
        //             cur *= *x;
        //         }
        //         *out = tot;
        //     });

        self.cpu
            .batch_evaluate_any(coeffs, poly_count, which, xs, out)
    }

    fn zk_shift(&self, io: &Self::BufferFp, poly_count: usize) {
        // let bits = log2_ceil(io.size() / poly_count);
        // let count = io.size();
        // assert_eq!(io.size(), poly_count * (1 << bits));

        // let mut io = io.as_slice_mut();
        // (&mut io[..], 0..count)
        //     .into_par_iter()
        //     .for_each(|(io, idx)| {
        //         let pos = idx & ((1 << bits) - 1);
        //         let rev = bit_rev_32(pos as u32) >> (32 - bits);
        //         let pow3 = F::Elem::from_u64(3).pow(rev as usize);
        //         *io = *io * pow3;
        //     });

        self.cpu.zk_shift(io, poly_count)
    }

    fn mix_poly_coeffs(
        &self,
        output: &Self::BufferFp4,
        mix_start: &F::ExtElem,
        mix: &F::ExtElem,
        input: &Self::BufferFp,
        combos: &Self::BufferU32,
        input_size: usize,
        count: usize,
    ) {
        // let mut output = output.as_slice_mut();
        // let input = input.as_slice();
        // let combos = combos.as_slice();
        // // TODO: parallelize
        // for idx in 0..count {
        //     let mut cur = *mix_start;
        //     for i in 0..input_size {
        //         let id = combos[i] as usize;
        //         output[count * id + idx] += cur * input[count * i + idx];
        //         cur *= *mix;
        //     }
        // }

        self.cpu
            .mix_poly_coeffs(output, mix_start, mix, input, combos, input_size, count)
    }

    /// every method call follows the same loop:
    /// - be provided GPU program
    /// - do prep work (creating buffers, etc)
    /// - use program to create and call a kernel
    /// - gather any output, return any result
    ///
    /// better arch:
    /// - alloc everything into GPU global space
    /// - adds to a stack of commands to run
    /// - when accessing a buffer that contains a previous command's output exec
    ///   commands until buffer
    fn eltwise_add_fp(
        &self,
        output: &Self::BufferFp,
        input1: &Self::BufferFp,
        input2: &Self::BufferFp,
    ) {
        self.cpu.eltwise_add_fp(output, input1, input2)

        // let closures = program_closures!(|program, inputs| -> Result<(),
        // GPUError> {     let (in1, in2) = inputs;
        //     let kernel = program.create_kernel("name", 0, 0)?;

        //     Ok(())
        // });
        // let inputs = input1.as_slice().iter().zip(input2.as_slice().iter())
        // self.kernel.run_many(closures, (input1, input2)).unwrap()

        // assert_eq!(output.size(), input1.size());
        // assert_eq!(output.size(), input2.size());

        // let mut output = output.as_slice_mut();
        // let input1 = input1.as_slice();
        // let input2 = input2.as_slice();
        // (&mut output[..], &input1[..], &input2[..])
        //     .into_par_iter()
        //     .for_each(|(o, a, b)| {
        //         *o = *a + *b;
        //     });
    }

    fn eltwise_sum_fp4(&self, output: &Self::BufferFp, input: &Self::BufferFp4) {
        // self.cpu.eltwise_sum_fp4(output, input)

        let count = output.size() / F::ExtElem::EXT_SIZE;
        let to_add = input.size() / count;
        assert_eq!(output.size(), count * F::ExtElem::EXT_SIZE);
        assert_eq!(input.size(), count * to_add);

        let mut output = output.as_slice_mut();
        let mut output =
            ArrayViewMut::from_shape((F::ExtElem::EXT_SIZE, count), &mut output).unwrap();
        let output = output.axis_iter_mut(Axis(1)).into_par_iter();

        let input = input.as_slice();
        let input = ArrayView::from_shape((to_add, count), &input).unwrap();
        let input = input.axis_iter(Axis(1)).into_par_iter();

        output.zip(input).for_each(|(mut output, input)| {
            let mut sum = F::ExtElem::ZERO;
            for i in input {
                sum += *i;
            }
            for i in 0..F::ExtElem::EXT_SIZE {
                output[i] = sum.subelems()[i]
            }
        });
    }

    fn eltwise_copy_fp(&self, output: &Self::BufferFp, input: &Self::BufferFp) {
        // let count = output.size();
        // assert_eq!(count, input.size());

        // let mut output = output.as_slice_mut();
        // let input = input.as_slice();
        // (&mut output[..], &input[..])
        //     .into_par_iter()
        //     .for_each(|(output, input)| {
        //         *output = *input;
        //     });

        self.cpu.eltwise_copy_fp(output, input)
    }

    fn eltwise_copy_digest(&self, output: &Self::BufferDigest, input: &Self::BufferDigest) {
        // let count = output.size();
        // assert_eq!(count, input.size());

        // let mut output = output.as_slice_mut();
        // let input = input.as_slice();
        // (&mut output[..], &input[..])
        //     .into_par_iter()
        //     .for_each(|(output, input)| {
        //         *output = *input;
        //     });

        self.cpu.eltwise_copy_digest(output, input)
    }

    fn fri_fold(&self, output: &Self::BufferFp, input: &Self::BufferFp, mix: &F::ExtElem) {
        // let count = output.size() / F::ExtElem::EXT_SIZE;
        // assert_eq!(output.size(), count * F::ExtElem::EXT_SIZE);
        // assert_eq!(input.size(), output.size() * FRI_FOLD);

        // let mut output = output.as_slice_mut();
        // let input = input.as_slice();

        // // TODO: parallelize
        // for idx in 0..count {
        //     let mut tot = F::ExtElem::ZERO;
        //     let mut cur_mix = F::ExtElem::ONE;
        //     for i in 0..FRI_FOLD {
        //         let rev_i = bit_rev_32(i as u32) >> (32 - log2_ceil(FRI_FOLD));
        //         let rev_idx = rev_i as usize * count + idx;
        //         let factor = F::ExtElem::from_subelems(
        //             (0..F::ExtElem::EXT_SIZE).map(|i| input[i * count * FRI_FOLD +
        // rev_idx]),         );
        //         tot += cur_mix * factor;
        //         cur_mix *= *mix;
        //     }
        //     for i in 0..F::ExtElem::EXT_SIZE {
        //         output[count * i + idx] = tot.subelems()[i];
        //     }
        // }

        self.cpu.fri_fold(output, input, mix)
    }

    fn sha_rows(&self, output: &Self::BufferDigest, matrix: &Self::BufferFp) {
        // let count = output.size();
        // let col_size = matrix.size() / output.size();
        // assert_eq!(matrix.size(), col_size * count);

        // let mut output = output.as_slice_mut();
        // let matrix = matrix.as_slice().to_vec(); // TODO: avoid copy
        // let sha = sha_cpu::Impl {};
        // output.par_iter_mut().enumerate().for_each(|(idx, output)| {
        //     *output = *sha.hash_pod_stride(matrix.as_slice(), idx, col_size, count);
        // });

        self.cpu.sha_rows(output, matrix)
    }

    fn sha_fold(&self, io: &Self::BufferDigest, input_size: usize, output_size: usize) {
        // assert_eq!(input_size, 2 * output_size);

        // let mut io = io.as_slice_mut();
        // let sha = sha_cpu::Impl {};
        // let (output, input) = unsafe {
        //     (
        //         from_raw_parts_mut(io.as_mut_ptr().add(output_size), output_size),
        //         from_raw_parts(io.as_ptr().add(input_size), input_size),
        //     )
        // };
        // output
        //     .par_iter_mut()
        //     .zip(input.par_chunks_exact(2))
        //     .for_each(|(output, input)| {
        //         *output = *sha.hash_pair(&input[0], &input[1]);
        //     });

        self.cpu.sha_fold(io, input_size, output_size)
    }
}

pub use verify::*;
mod verify {
    use super::*;

    // TODO:
    pub struct GpuVerifyHal<'a, S: Sha, C: PolyExt, F: GpuHalField> {
        sha: &'a S,
        circuit: &'a C,
        kernel: FieldKernel<F>,
        // inner: CpuVerifyHal<'a, S, C, F>,
    }

    impl<'a, S: Sha, C: PolyExt, F: GpuHalField> GpuVerifyHal<'a, S, C, F> {
        pub fn new(sha: &'a S, circuit: &'a C) -> Self {
            Self {
                sha,
                circuit,
                kernel: FieldKernel::new(),
            }
        }
    }

    impl<'a, S: Sha, C: PolyExt, F: GpuHalField> VerifyHal for GpuVerifyHal<'a, S, C, F> {
        type Sha = S;
        type Field = F;

        fn sha(&self) -> &Self::Sha {
            self.sha
        }

        fn debug(&self, msg: &str) {
            log::debug!("{}", msg);
        }

        fn fold_eval(&self, io: &mut [F::ExtElem], mix: F::ExtElem, inv_wk: F::Elem) -> F::ExtElem {
            interpolate_ntt::<F::Elem, F::ExtElem>(io);
            bit_reverse(io);
            self.poly_eval(io, mix, inv_wk)
        }

        fn compute_polynomial(
            &self,
            u: &[F::ExtElem],
            poly_mix: F::ExtElem,
            out: &[F::Elem],
            mix: &[F::Elem],
        ) -> F::ExtElem {
            let ctx = PolyExtContext {
                mix: <Self as VerifyHal>::to_baby_bear_fp4(poly_mix),
            };
            let args: &[&[_]] = &[
                <Self as VerifyHal>::to_baby_bear_fp_slice(out),
                <Self as VerifyHal>::to_baby_bear_fp_slice(mix),
            ];
            let result =
                self.circuit
                    .poly_ext(&ctx, <Self as VerifyHal>::to_baby_bear_fp4_slice(u), args);
            <Self as VerifyHal>::from_baby_bear_fp4(result.tot)
        }

        /// Evaluate a polynomial whose coefficients are in the extension field
        /// at a point.
        fn poly_eval(&self, coeffs: &[F::ExtElem], x: F::ExtElem, y: F::Elem) -> F::ExtElem {
            let mut tot = F::ExtElem::ZERO;
            let mut mul_fp4 = F::ExtElem::ONE;
            let mut mul_fp = F::Elem::ONE;
            for i in 0..coeffs.len() {
                tot += coeffs[i] * mul_fp * mul_fp4;
                mul_fp4 *= x;
                mul_fp *= y;
            }
            tot
        }
    }
}

pub use eval::*;
mod eval {
    use super::*;

    // TODO: copied from CPU hal
    pub struct GpuEvalCheck<'a, C: PolyFp> {
        circuit: &'a C,
    }

    impl<'a, C: PolyFp> GpuEvalCheck<'a, C> {
        pub fn new(circuit: &'a C) -> Self {
            Self { circuit }
        }
    }

    impl<'a, C: PolyFp> EvalCheck<GpuHal<BabyBear>> for GpuEvalCheck<'a, C> {
        fn eval_check(
            &self,
            check: &CpuBuffer<<BabyBear as Field>::Elem>,
            code: &CpuBuffer<<BabyBear as Field>::Elem>,
            data: &CpuBuffer<<BabyBear as Field>::Elem>,
            accum: &CpuBuffer<<BabyBear as Field>::Elem>,
            mix: &CpuBuffer<<BabyBear as Field>::Elem>,
            out: &CpuBuffer<<BabyBear as Field>::Elem>,
            poly_mix: <BabyBear as Field>::ExtElem,
            po2: usize,
            steps: usize,
        ) {
            type Elem = <BabyBear as Field>::Elem;

            const EXP_PO2: usize = log2_ceil(INV_RATE);

            let domain = steps * INV_RATE;
            let code = code.as_slice();
            let data = data.as_slice();
            let accum = accum.as_slice();
            let mix = mix.as_slice();
            let out = out.as_slice();
            let mut check = check.as_slice_mut();
            // TODO: parallelize
            for cycle in 0..domain {
                let args: &[&[Elem]] = &[&code, &out, &data, &mix, &accum];
                let cond = self.circuit.poly_fp(
                    &PolyFpContext {
                        size: domain,
                        cycle,
                        mix: poly_mix,
                        // mix: <Self as VerifyHal>::to_baby_bear_fp4(poly_mix),
                    },
                    args,
                );
                let x = Elem::new(ROU_FWD[po2 + EXP_PO2]).pow(cycle);
                // TODO: what is this magic number 3?
                let y = (Elem::new(3) * x).pow(1 << po2);
                let ret = cond.tot * (y - Elem::new(1)).inv();
                for i in 0..<<BabyBear as Field>::ExtElem as ExtElem>::EXT_SIZE {
                    check[i * domain + cycle] = ret.elems()[i];
                }
            }
        }
    }
}

/// A field kernel for a single GPU.
pub struct FieldKernel<F: GpuHalField> {
    programs: Vec<Program>,
    // /// An optional function which will be called at places where it is possible
    // /// to abort the FFT calculations. If it returns true, the calculation
    // /// will be aborted with an [`EcError::Aborted`].
    // maybe_abort: Option<&'a (dyn Fn() -> bool + Send + Sync)>,
    _f: std::marker::PhantomData<F>,
}

// impl AsRef<>

impl<F: GpuHalField> FieldKernel<F> {
    // /// The `maybe_abort` function is called when it is possible to abort the
    // /// computation, without leaving the GPU in a weird state. If that
    // /// function returns `true`, execution is aborted.
    // fn create(
    //     program: Program,
    //     maybe_abort: Option<&'a (dyn Fn() -> bool + Send + Sync)>,
    // ) -> EcResult<Self> {
    //     Ok(FieldKernel {
    //         program,
    //         maybe_abort,
    //         _f: Default::default(),
    //     })
    // }

    fn new() -> Self {
        let worker = Worker::new();
        let log_threads = worker.log_num_threads();
        let programs = Device::all()
            .iter()
            .map(|device| ec_gpu_gen::program!(device))
            .collect::<Result<_, _>>()
            .expect("cannot create programs");
        Self {
            programs,
            // maybe_abort: None,
            _f: PhantomData,
        }
    }

    // fn elem_kernel_name(name: &str) -> String {
    //     use ec_gpu::GpuName;
    //     format!("{}_{}", <F::Elem as GpuName>::name(), name)
    // }

    // fn extelem_kernel_name(name: &str) -> String {
    //     use ec_gpu::GpuName;
    //     format!("{}_{}", <F::ExtElem as GpuName>::name(), name)
    // }

    // fn create_kernel()

    // fn run<A, F1, F2>(&self, arg: A, fns: (F1, F2)) -> Result<(), EcError>
    // where
    //     F1: FnOnce(&opencl::Program, A) -> Result<(), EcError>,
    //     // F2: FnOnce(&cuda::Program, A) -> Result<(), EcError>,
    // {
    //     match self.program[0] {
    //         Program::Opencl(program) => program.run(fns.0, arg),
    //     }
    // }

    fn run_many<A, F1, F2>(&self, args: &[A], fns: (F1, F2)) -> Result<(), EcError>
    where
        A: Send,
        F1: FnOnce(&opencl::Program, A) -> Result<(), EcError> + Send,
        // F2: FnOnce(&cuda::Program, A) -> Result<(), EcError>,
    {
        let num_args = args.len();
        let num_devices = self.programs.len();
        let chunk_size = ((num_args as f64) / (num_devices as f64)).ceil() as usize;

        let result = Arc::new(RwLock::new(Ok(())));

        THREAD_POOL.scoped(|s| {
            let params = args.chunks_mut(chunk_size).zip(self.programs.iter_mut());
            for (arg_chunk, program) in params {
                let result = result.clone();
                s.execute(move || {
                    for arg in arg_chunk.iter_mut() {
                        if result.read().unwrap().is_err() {
                            break;
                        }

                        let res = match program {
                            Program::Opencl(prog) => prog.run(fns.0, *arg),
                        };
                        if let Err(err) = res {
                            *result.write().unwrap() = Err(err);
                            break;
                        }
                    }
                });
            }
        });

        Arc::try_unwrap(result).unwrap().into_inner().unwrap()
    }
}
