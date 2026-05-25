// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

pub(crate) mod cpu;
#[cfg(feature = "cuda")]
pub(crate) mod cuda;

use std::rc::Rc;

use anyhow::Result;
use risc0_core::scope;
use risc0_zkp::{
    adapter::{CircuitInfo as _, PROOF_SYSTEM_INFO},
    field::Elem as _,
    hal::{Buffer, CircuitHal, Hal},
    prove::Prover,
};
#[cfg(all(feature = "low_vram", feature = "cuda"))]
use risc0_zkp::{core::digest::Digest, LARGE_SEGMENT_PO2};

use super::{
    witgen::{preflight::PreflightTrace, PreflightResults, WitnessGenerator},
    Seal, SegmentProver,
};
use crate::{
    execute::segment::Segment,
    zirgen::{
        circuit::{
            CircuitField, ExtVal, Val, REGCOUNT_MIX, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE,
            REGISTER_GROUP_DATA,
        },
        taps::TAPSET,
        CircuitImpl,
    },
    RV32IM_SEAL_VERSION,
};

#[cfg(all(feature = "low_vram", feature = "cuda"))]
use anyhow::anyhow;
#[cfg(all(feature = "low_vram", feature = "cuda"))]
use std::sync::Once;

cfg_if::cfg_if! {
    if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
        use risc0_zkp::hal::cuda::init_pinned_arena;
        use risc0_zkp::hal::{release_buffer};
        use std::mem;
    }
}

pub(crate) struct MetaBuffer<H: Hal> {
    pub buf: H::Buffer<H::Elem>,
    pub rows: usize,
    pub cols: usize,
    pub checked: bool,
}

impl<H> MetaBuffer<H>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
{
    pub fn new(name: &'static str, hal: &H, rows: usize, cols: usize, checked: bool) -> Self {
        let buf = hal.alloc_elem_init(name, rows * cols, Val::INVALID);
        Self {
            buf,
            rows,
            cols,
            checked,
        }
    }

    #[cfg(test)]
    pub fn to_vec(&self) -> Vec<Val> {
        self.buf.to_vec()
    }
}

#[allow(dead_code)]
#[derive(Clone, Copy, PartialEq)]
pub(crate) enum StepMode {
    Parallel,
    SeqForward,
    SeqReverse,
}

pub(crate) trait CircuitWitnessGenerator<H: Hal> {
    fn generate_witness(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace,
        global: &MetaBuffer<H>,
        data: &MetaBuffer<H>,
    ) -> Result<()>;
}

pub(crate) trait CircuitAccumulator<H: Hal> {
    fn step_accum(
        &self,
        preflight: &PreflightTrace,
        data: &MetaBuffer<H>,
        accum: &MetaBuffer<H>,
        global: &MetaBuffer<H>,
        mix: &MetaBuffer<H>,
    ) -> Result<()>;
}

pub(crate) struct SegmentProverImpl<H, C, F>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
    // F: Fn() -> (Rc<H>, Rc<C>),
    F: Fn() -> (Rc<H>, Rc<C>),
{
    hal_factory: F,
}

impl<H, C, F> SegmentProverImpl<H, C, F>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    C: CircuitHal<H> + CircuitWitnessGenerator<H>,
    // F: Fn() -> (Rc<H>, Rc<C>),
    F: Fn() -> (Rc<H>, Rc<C>),
{
    pub fn new(hal_factory: F) -> Self {
        Self { hal_factory }
    }
}

#[allow(dead_code)]
#[cfg(all(feature = "low_vram", feature = "cuda"))]
fn release_digest_buf<H>(
    name: &'static str,
    _hal: &H,
    buf: &mut H::Buffer<Digest>,
    newbuf: &H::Buffer<Digest>,
) where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    H::Buffer<Digest>: Clone,
{
    tracing::debug!("Release {}", name);

    let _dropped = mem::replace(buf, newbuf.clone());
    drop(_dropped);
}

#[cfg(all(feature = "low_vram", feature = "cuda"))]
fn copy_merkle2host<H>(
    _hal: &H,
    nodes: &H::Buffer<Digest>,
    name: &'static str,
) -> Result<H::Buffer<Digest>>
where
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal> + 'static,
{
    use risc0_zkp::hal::cuda::{BufferImpl, TrackedLockedBuffer};
    let nodes_size = nodes.size();
    let nodes_size_bytes = nodes_size * std::mem::size_of::<Digest>();

    let host_buf = TrackedLockedBuffer::new(name, nodes_size_bytes)
        .map_err(|e| anyhow!("Failed to allocate from pinned arena: {}", e))?;
    let host_ptr = host_buf.as_raw_ptr();

    unsafe {
        let host_digests = std::slice::from_raw_parts(host_ptr as *const Digest, nodes_size);

        if nodes.get_at(1) == host_digests[1] {
            let host_buffer_impl =
                BufferImpl::from_tracked_locked_buffer(name, host_buf, nodes_size);
            let host_buffer: H::Buffer<Digest> = std::ptr::read(
                &host_buffer_impl as *const BufferImpl<Digest> as *const H::Buffer<Digest>,
            );

            std::mem::forget(host_buffer_impl); // Prevent double-drop
            return Ok(host_buffer);
        }
    }

    unsafe {
        extern "C" {
            fn cudaStreamCreate(stream: *mut *mut std::ffi::c_void) -> i32;
            fn cudaMemcpyAsync(
                dst: *mut std::ffi::c_void,
                src: *const std::ffi::c_void,
                count: usize,
                kind: u32,
                stream: *mut std::ffi::c_void,
            ) -> i32;
            fn cudaStreamSynchronize(stream: *mut std::ffi::c_void) -> i32;
            fn cudaStreamDestroy(stream: *mut std::ffi::c_void) -> i32;
        }

        // Create CUDA stream for async operations
        let mut stream_ptr: *mut std::ffi::c_void = std::ptr::null_mut();
        let stream_result = cudaStreamCreate(&mut stream_ptr);
        if stream_result != 0 {
            return Err(anyhow!(
                "cudaStreamCreate failed: error code {}",
                stream_result
            ));
        }

        let buffer_impl: &BufferImpl<Digest> = std::mem::transmute(nodes);
        let device_ptr = buffer_impl.as_device_ptr();

        let result = cudaMemcpyAsync(
            host_ptr as *mut std::ffi::c_void,
            device_ptr.as_raw() as *const std::ffi::c_void,
            nodes_size_bytes,
            2, // cudaMemcpyDeviceToHost
            stream_ptr,
        );

        if result != 0 {
            let _ = cudaStreamDestroy(stream_ptr);
            return Err(anyhow!("cudaMemcpyAsync failed: error code {}", result));
        }

        let sync_result = cudaStreamSynchronize(stream_ptr);
        if sync_result != 0 {
            let _ = cudaStreamDestroy(stream_ptr);
            return Err(anyhow!(
                "cudaStreamSynchronize failed: error code {}",
                sync_result
            ));
        }

        let host_buffer_impl = BufferImpl::from_tracked_locked_buffer(name, host_buf, nodes_size);
        let host_buffer: H::Buffer<Digest> = std::ptr::read(
            &host_buffer_impl as *const BufferImpl<Digest> as *const H::Buffer<Digest>,
        );

        std::mem::forget(host_buffer_impl); // Prevent double-drop
        Ok(host_buffer)
    }
}

impl<H, C, F> SegmentProver for SegmentProverImpl<H, C, F>
where
    // H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal>,
    H: Hal<Field = CircuitField, Elem = Val, ExtElem = ExtVal> + 'static,
    C: CircuitHal<H> + CircuitWitnessGenerator<H> + CircuitAccumulator<H>,
    // F: Fn() -> (Rc<H>, Rc<C>),
    F: Fn() -> (Rc<H>, Rc<C>),
{
    fn preflight(&self, segment: &Segment) -> Result<PreflightResults> {
        scope!("preflight");

        cfg_if::cfg_if! {
            if #[cfg(feature = "witgen_debug")] {
                let rand_z = ExtVal::ONE;
            } else {
                let mut rng = rand::rng();
                let rand_z = ExtVal::random(&mut rng);
            }
        }
        PreflightResults::new(segment, rand_z)
    }

    fn prove_core(&self, preflight_results: PreflightResults) -> Result<Seal> {
        scope!("prove_core");

        cfg_if::cfg_if! {
            if #[cfg(feature = "witgen_debug")] {
                let mode = if std::env::var_os("RISC0_WITGEN_DEBUG").is_some() {
                    StepMode::SeqForward
                } else {
                    StepMode::Parallel
                };
            } else {
                let mode = StepMode::Parallel;
            }
        }

        let (hal, circuit_hal) = (self.hal_factory)();

        let po2 = preflight_results.po2();
        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                let mut witgen =
                    WitnessGenerator::new(hal.as_ref(), circuit_hal.as_ref(), preflight_results, mode)?;
            } else {
                let witgen =
                    WitnessGenerator::new(hal.as_ref(), circuit_hal.as_ref(), preflight_results, mode)?;
            }
        }

        let code = &witgen.code.buf;
        let data = &witgen.data.buf;
        let global = &witgen.global.buf;

        cfg_if::cfg_if! {
            if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                static INIT_ARENA: Once = Once::new();
                INIT_ARENA.call_once(|| {
                    if let Err(e) = init_pinned_arena(Some(1)) {
                        tracing::error!("Failed to initialize pinned memory arena: {}", e);
                        tracing::warn!("Falling back to slow per-allocation cudaMallocHost");
                    }
                });
            }
        }

        Ok(scope!("prove_inner", {
            tracing::debug!("prove_inner");

            let mut prover = Prover::new(hal.as_ref(), TAPSET);
            let hashfn = &hal.get_hash_suite().hashfn;

            // Add a version tag to the start of the seal. It's not intended for
            // this value to be consumed by downstream lift predicates. Instead
            // it's meant to be a header which can be used by future versions in
            // case we'd like to adjust the encoding of the seal.
            //
            // We write via the IOP to avoid having to prepend a value to an
            // already allocated vector.
            prover.iop().write_u32_slice(&[RV32IM_SEAL_VERSION]);

            let mix = scope!("main", {
                // At the start of the protocol, seed the Fiat-Shamir transcript with context information
                // about the proof system and circuit.
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&PROOF_SYSTEM_INFO.encode()));
                prover
                    .iop()
                    .commit(&hashfn.hash_elem_slice(&CircuitImpl::CIRCUIT_INFO.encode()));

                // Concat globals and po2 into a vector.
                let global_len = global.size();
                let mut header = vec![Val::ZERO; global_len + 1];
                global.view_mut(|view| {
                    for (i, elem) in view.iter_mut().enumerate() {
                        *elem = elem.valid_or_zero();
                        header[i] = *elem;
                    }
                    header[global_len] = Val::new_raw(po2);
                });

                let header_digest = hashfn.hash_elem_slice(&header);
                prover.iop().commit(&header_digest);
                prover.iop().write_field_elem_slice(header.as_slice());
                prover.set_po2(po2 as usize);

                prover.commit_group(REGISTER_GROUP_CODE, code);

                cfg_if::cfg_if! {
                    if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                        if po2 >= LARGE_SEGMENT_PO2 as u32 {
                            let code_g = prover.groups[REGISTER_GROUP_CODE].as_mut().unwrap();
                            let code_h = copy_merkle2host(hal.as_ref(), &code_g.merkle.nodes, "code.merkle.nodes")?;
                            release_digest_buf("code merkle tree", hal.as_ref(), &mut code_g.merkle.nodes, &code_h);
                        }
                    }
                }

                prover.commit_group(REGISTER_GROUP_DATA, data);

                // Make the mixing values
                let mix: [Val; REGCOUNT_MIX] = std::array::from_fn(|_| prover.iop().random_elem());

                let mix = witgen.accum(hal.as_ref(), circuit_hal.as_ref(), &mix)?;
                cfg_if::cfg_if! {
                    if #[cfg(all(feature = "low_vram", feature = "cuda"))] {
                        release_buffer("witgen.data.buf", hal.as_ref(), &mut witgen.data.buf);
                    }
                }

                prover.commit_group(REGISTER_GROUP_ACCUM, &witgen.accum.buf);

                mix
            });

            prover.finalize(&[&mix.buf, global], circuit_hal.as_ref())
        }))
    }
}
