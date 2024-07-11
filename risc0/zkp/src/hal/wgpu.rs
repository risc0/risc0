// Copyright 2024 RISC Zero, Inc.
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

// The GPU becomes unstable as the number of concurrent provers grow.
// fn singleton() -> &'static ReentrantMutex<()> {
//     static ONCE: OnceLock<ReentrantMutex<()>> = OnceLock::new();
//     ONCE.get_or_init(|| ReentrantMutex::new(()))
// }

// pub trait GpuHash {
//     /// Create a hash implementation
//     fn new(hal: &WGpuHal<Self>) -> Self;

//     /// Run the hash_fold function
//     fn hash_fold(&self, hal: &MetalHal<Self>, io: &BufferImpl<Digest>, output_size: usize);

//     /// Run the hash_rows function
//     fn hash_rows(
//         &self,
//         hal: &MetalHal<Self>,
//         output: &BufferImpl<Digest>,
//         matrix: &BufferImpl<BabyBearElem>,
//     );

//     /// Return the HashSuite
//     fn get_hash_suite(&self) -> &HashSuite<BabyBear>;
// }

// pub struct MetalHashSha256 {
//     suite: HashSuite<BabyBear>,
// }

// impl MetalHash for MetalHashSha256 {
//     fn new(_hal: &MetalHal<Self>) -> Self {
//         MetalHashSha256 {
//             suite: Sha256HashSuite::new_suite(),
//         }
//     }

//     fn hash_fold(&self, hal: &MetalHal<Self>, io: &BufferImpl<Digest>, output_size: usize) {
//         let args = &[
//             io.as_arg_with_offset(output_size),
//             io.as_arg_with_offset(output_size * 2),
//         ];
//         hal.dispatch_by_name("sha_fold", args, output_size as u64);
//     }

//     fn hash_rows(
//         &self,
//         hal: &MetalHal<Self>,
//         output: &BufferImpl<Digest>,
//         matrix: &BufferImpl<BabyBearElem>,
//     ) {
//         let row_size = output.size();
//         let col_size = matrix.size() / output.size();
//         assert_eq!(matrix.size(), col_size * row_size);
//         let args = &[
//             output.as_arg(),
//             matrix.as_arg(),
//             KernelArg::Integer(row_size as u32),
//             KernelArg::Integer(col_size as u32),
//         ];
//         hal.dispatch_by_name("sha_rows", args, row_size as u64);
//     }

//     fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
//         &self.suite
//     }
// }

// pub struct MetalHashPoseidon {
//     suite: HashSuite<BabyBear>,
//     round_constants: BufferImpl<BabyBearElem>,
//     mds: BufferImpl<BabyBearElem>,
//     partial_comp_matrix: BufferImpl<BabyBearElem>,
//     partial_comp_offset: BufferImpl<BabyBearElem>,
// }

// impl MetalHash for MetalHashPoseidon {
//     fn new(hal: &MetalHal<Self>) -> Self {
//         let round_constants =
//             hal.copy_from_elem("round_constants", poseidon::consts::ROUND_CONSTANTS);
//         let mds = hal.copy_from_elem("mds", poseidon::consts::MDS);
//         let partial_comp_matrix =
//             hal.copy_from_elem("partial_comp_matrix", poseidon::consts::PARTIAL_COMP_MATRIX);
//         let partial_comp_offset =
//             hal.copy_from_elem("partial_comp_offset", poseidon::consts::PARTIAL_COMP_OFFSET);
//         MetalHashPoseidon {
//             suite: PoseidonHashSuite::new_suite(),
//             round_constants,
//             mds,
//             partial_comp_matrix,
//             partial_comp_offset,
//         }
//     }

//     fn hash_fold(&self, hal: &MetalHal<Self>, io: &BufferImpl<Digest>, output_size: usize) {
//         let args = &[
//             self.round_constants.as_arg(),
//             self.mds.as_arg(),
//             self.partial_comp_matrix.as_arg(),
//             self.partial_comp_offset.as_arg(),
//             io.as_arg_with_offset(output_size),
//             io.as_arg_with_offset(output_size * 2),
//         ];
//         hal.dispatch_by_name("poseidon_fold", args, output_size as u64);
//     }

//     fn hash_rows(
//         &self,
//         hal: &MetalHal<Self>,
//         output: &BufferImpl<Digest>,
//         matrix: &BufferImpl<BabyBearElem>,
//     ) {
//         let row_size = output.size();
//         let col_size = matrix.size() / output.size();
//         assert_eq!(matrix.size(), col_size * row_size);
//         let args = &[
//             self.round_constants.as_arg(),
//             self.mds.as_arg(),
//             self.partial_comp_matrix.as_arg(),
//             self.partial_comp_offset.as_arg(),
//             output.as_arg(),
//             matrix.as_arg(),
//             KernelArg::Integer(row_size as u32),
//             KernelArg::Integer(col_size as u32),
//         ];
//         hal.dispatch_by_name("poseidon_rows", args, row_size as u64);
//     }

//     fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
//         &self.suite
//     }
// }

// pub struct MetalHashPoseidon2 {
//     suite: HashSuite<BabyBear>,
//     round_constants: BufferImpl<BabyBearElem>,
//     m_int_diag: BufferImpl<BabyBearElem>,
// }

// impl MetalHash for MetalHashPoseidon2 {
//     fn new(hal: &MetalHal<Self>) -> Self {
//         let round_constants =
//             hal.copy_from_elem("round_constants", poseidon2::consts::ROUND_CONSTANTS);
//         let m_int_diag = hal.copy_from_elem("m_int_diag", poseidon2::consts::M_INT_DIAG_HZN);
//         MetalHashPoseidon2 {
//             suite: Poseidon2HashSuite::new_suite(),
//             round_constants,
//             m_int_diag,
//         }
//     }

//     fn hash_fold(&self, hal: &MetalHal<Self>, io: &BufferImpl<Digest>, output_size: usize) {
//         let args = &[
//             self.round_constants.as_arg(),
//             self.m_int_diag.as_arg(),
//             io.as_arg_with_offset(output_size),
//             io.as_arg_with_offset(output_size * 2),
//         ];
//         hal.dispatch_by_name("poseidon2_fold", args, output_size as u64);
//     }

//     fn hash_rows(
//         &self,
//         hal: &MetalHal<Self>,
//         output: &BufferImpl<Digest>,
//         matrix: &BufferImpl<BabyBearElem>,
//     ) {
//         let row_size = output.size();
//         let col_size = matrix.size() / output.size();
//         assert_eq!(matrix.size(), col_size * row_size);
//         let args = &[
//             self.round_constants.as_arg(),
//             self.m_int_diag.as_arg(),
//             output.as_arg(),
//             matrix.as_arg(),
//             KernelArg::Integer(row_size as u32),
//             KernelArg::Integer(col_size as u32),
//         ];
//         hal.dispatch_by_name("poseidon2_rows", args, row_size as u64);
//     }

//     fn get_hash_suite(&self) -> &HashSuite<BabyBear> {
//         &self.suite
//     }
// }

use core::mem;

use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use wgpu::{
    util::{BufferInitDescriptor, DeviceExt},
    BufferDescriptor, BufferUsages, Device, Queue,
};

use crate::core::digest::Digest;

use super::Hal;

#[derive(Debug)]
pub struct WgpuHal {
    // pub device: Device,
    // pub cmd_queue: CommandQueue,
    // kernels: HashMap<String, ComputePipelineDescriptor>,
    // hash: Option<Box<Hash>>,
    // _lock: ReentrantMutexGuard<'static, ()>,
    device: wgpu::Device,
    queue: wgpu::Queue,
    pipeline: wgpu::ComputePipeline,
    // bind_group: wgpu::BindGroup,
    // storage_buffer: wgpu::Buffer,
    // output_staging_buffer: wgpu::Buffer,
}

#[derive(Clone, Debug)]
pub struct BufferImpl<T> {
    // name: &'static str,
    // cmd_queue: CommandQueue,
    // buffer: TrackedBuffer,
    // offset: usize,
    // size: usize,
    // marker: PhantomData<T>,
    buffer: wgpu::Buffer,
}

impl<T> BufferImpl<T> {
    pub fn new(name: &'static str, device: &Device, size: usize) -> Self {
        let bytes_len = size * mem::size_of::<T>();
        let desc = BufferDescriptor {
            label: Some(name),
            size: bytes_len as u64,
            usage: BufferUsages::MAP_READ | BufferUsages::MAP_WRITE,
            mapped_at_creation: false,
        };
        // TODO: does this panic on OOM?
        Self {
            buffer: device.create_buffer(&desc),
        }
    }

    pub fn copy_from(name: &'static str, device: &Device, slice: &[T]) -> Self {
        let bytes_len = mem::size_of_val(slice);
        let desc = BufferInitDescriptor {
            label: Some(name),
            contents: bytemuck::cast_slice(slice),
            usage: BufferUsages::MAP_READ | BufferUsages::MAP_WRITE,
        };
        // TODO: does this panic on OOM?
        Self {
            buffer: device.create_buffer_init(&desc),
        }
    }

    // fn sync(&self) {
    //     let cmd_buffer = self.cmd_queue.new_command_buffer();
    //     let blit_encoder = cmd_buffer.new_blit_command_encoder();
    //     blit_encoder.synchronize_resource(&self.buffer.0);
    //     blit_encoder.end_encoding();
    //     cmd_buffer.commit();
    //     cmd_buffer.wait_until_completed();
    // }

    // pub fn as_device_ptr(&self) -> *mut c_void {
    //     self.buffer.0.gpu_address() as *mut c_void
    // }

    // pub fn as_ptr(&self) -> *mut c_void {
    //     self.buffer.0.contents()
    // }

    // pub fn as_buf(&self) -> MetalBuffer {
    //     self.buffer.0.clone()
    // }
}

impl<T: Clone> Buffer<T> for BufferImpl<T> {
    fn name(&self) -> &'static str {
        unimplemented!()
    }

    fn size(&self) -> usize {
        unimplemented!()
    }

    fn slice(&self, offset: usize, size: usize) -> BufferImpl<T> {
        unimplemented!()
    }

    fn get_at(&self, idx: usize) -> T {
        unimplemented!()
    }

    fn view<F: FnOnce(&[T])>(&self, f: F) {
        unimplemented!()
    }

    fn view_mut<F: FnOnce(&mut [T])>(&self, f: F) {
        unimplemented!()
    }

    fn to_vec(&self) -> Vec<T> {
        unimplemented!()
    }
}

// impl<MH: MetalHash> Default for MetalHal<MH> {
//     fn default() -> Self {
//         Self::new()
//     }
// }

impl WgpuHal {
    pub fn new() -> Self {
        // let lock = singleton().lock();
        // let device = Device::system_default().expect("no device found");
        // assert_eq!(
        //     device.argument_buffers_support(),
        //     MTLArgumentBuffersTier::Tier2
        // );
        // let library = device.new_library_with_data(METAL_LIB).unwrap();
        // let cmd_queue = device.new_command_queue();
        // let mut kernels = HashMap::new();
        // for name in KERNEL_NAMES {
        //     let function = library.get_function(name, None).unwrap();
        //     let pipeline = ComputePipelineDescriptor::new();
        //     pipeline.set_compute_function(Some(&function));
        //     kernels.insert(name.to_string(), pipeline);
        // }
        // let mut hal = Self {
        //     device,
        //     cmd_queue,
        //     kernels,
        //     hash: None,
        //     _lock: lock,
        // };
        // hal.hash = Some(Box::new(MH::new(&hal)));
        // hal
    }
}

#[allow(unused_variables)]
impl Hal for WgpuHal {
    type Elem = BabyBearElem;
    type ExtElem = BabyBearExtElem;
    type Field = BabyBear;
    type Buffer<T: Clone + Debug + PartialEq> = BufferImpl<T>;

    fn alloc_elem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::Elem> {
        BufferImpl::new(name, &self.device, size)
    }

    fn copy_from_elem(&self, name: &'static str, slice: &[Self::Elem]) -> Self::Buffer<Self::Elem> {
        BufferImpl::copy_from(name, &self.device, slice)
    }

    fn alloc_extelem(&self, name: &'static str, size: usize) -> Self::Buffer<Self::ExtElem> {
        BufferImpl::new(name, &self.device, size)
    }

    fn copy_from_extelem(
        &self,
        name: &'static str,
        slice: &[Self::ExtElem],
    ) -> Self::Buffer<Self::ExtElem> {
        BufferImpl::copy_from(name, &self.device, slice)
    }

    fn alloc_digest(&self, name: &'static str, size: usize) -> Self::Buffer<Digest> {
        BufferImpl::new(name, &self.device, size)
    }

    fn copy_from_digest(&self, name: &'static str, slice: &[Digest]) -> Self::Buffer<Digest> {
        BufferImpl::copy_from(name, &self.device, slice)
    }

    fn alloc_u32(&self, name: &'static str, size: usize) -> Self::Buffer<u32> {
        BufferImpl::new(name, &self.device, size)
    }

    fn copy_from_u32(&self, name: &'static str, slice: &[u32]) -> Self::Buffer<u32> {
        BufferImpl::copy_from(name, &self.device, slice)
    }

    #[tracing::instrument(skip_all)]
    fn batch_bit_reverse(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        // let row_size = io.size() / count;
        // assert_eq!(row_size * count, io.size());
        // let bits = log2_ceil(row_size);
        // assert_eq!(row_size, 1 << bits);
        // tracing::debug!(
        //     "io: {}, count: {count}, row_size: {row_size}, bits: {bits}",
        //     io.size()
        // );
        // let args = &[io.as_arg(), KernelArg::Integer(bits as u32)];
        // self.dispatch_by_name("multi_bit_reverse", args, row_size as u64 * count as u64);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn batch_expand_into_evaluate_ntt(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        count: usize,
        expand_bits: usize,
    ) {
        // batch_expand
        // {
        //     tracing::debug!(
        //         "output: {}, input: {}, count: {count}",
        //         output.size(),
        //         input.size()
        //     );
        //     let out_size = output.size() / count;
        //     let in_size = input.size() / count;
        //     let expand_bits = log2_ceil(out_size / in_size);
        //     assert_eq!(output.size(), out_size * count);
        //     assert_eq!(input.size(), in_size * count);
        //     assert_eq!(out_size, in_size * (1 << expand_bits));
        //     let args = &[
        //         output.as_arg(),
        //         input.as_arg(),
        //         KernelArg::Integer(count as u32),
        //         KernelArg::Integer(out_size as u32),
        //         KernelArg::Integer(in_size as u32),
        //         KernelArg::Integer(expand_bits as u32),
        //     ];
        //     self.dispatch_by_name("batch_expand", args, out_size as u64);
        // }

        // // batch_evaluate_ntt
        // {
        //     tracing::debug!(
        //         "output: {}, count: {count}, expand_bits: {expand_bits}",
        //         output.size()
        //     );
        //     let row_size = output.size() / count;
        //     assert_eq!(row_size * count, output.size());
        //     let n_bits = log2_ceil(row_size);
        //     assert_eq!(row_size, 1 << n_bits);
        //     assert!(n_bits >= expand_bits);
        //     assert!(n_bits < Self::Elem::MAX_ROU_PO2);
        //     let rou = self.copy_from_elem("rou", Self::Elem::ROU_FWD);
        //     let kernel = self.kernels.get("multi_ntt_fwd_step").unwrap();
        //     for s_bits in 1 + expand_bits..=n_bits {
        //         let args = &[
        //             output.as_arg(),
        //             rou.as_arg(),
        //             KernelArg::Integer(n_bits as u32),
        //             KernelArg::Integer(s_bits as u32),
        //             KernelArg::Integer(count as u32),
        //         ];
        //         let params = compute_launch_params(n_bits as u32, s_bits as u32, count as u32);
        //         self.dispatch(kernel, args, count as u64, Some(params));
        //     }
        // }
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn batch_interpolate_ntt(&self, io: &Self::Buffer<Self::Elem>, count: usize) {
        // tracing::debug!("io: {}, count: {count}", io.size());
        // let row_size = io.size() / count;
        // assert_eq!(row_size * count, io.size());
        // let n_bits = log2_ceil(row_size);
        // assert_eq!(row_size, 1 << n_bits);
        // assert!(n_bits < Self::Elem::MAX_ROU_PO2);

        // let rou = self.copy_from_elem("rou", Self::Elem::ROU_REV);
        // let kernel = self.kernels.get("multi_ntt_rev_step").unwrap();
        // for s_bits in (1..=n_bits).rev() {
        //     let args = &[
        //         io.as_arg(),
        //         rou.as_arg(),
        //         KernelArg::Integer(n_bits as u32),
        //         KernelArg::Integer(s_bits as u32),
        //         KernelArg::Integer(count as u32),
        //     ];
        //     let params = compute_launch_params(n_bits as u32, s_bits as u32, count as u32);
        //     self.dispatch(kernel, args, count as u64, Some(params));
        // }

        // let norm = self.copy_from_elem("norm", &[Self::Elem::new(row_size as u32).inv()]);
        // let args = &[io.as_arg(), norm.as_arg()];
        // self.dispatch_by_name("eltwise_mul_factor_fp", args, io.size() as u64);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn batch_evaluate_any(
        &self,
        coeffs: &Self::Buffer<Self::Elem>,
        poly_count: usize,
        which: &Self::Buffer<u32>,
        xs: &Self::Buffer<Self::ExtElem>,
        out: &Self::Buffer<Self::ExtElem>,
    ) {
        // let po2 = log2_ceil(coeffs.size() / poly_count);
        // let count = 1 << po2;
        // assert_eq!(poly_count * count, coeffs.size());
        // let eval_count = which.size();
        // assert_eq!(xs.size(), eval_count);
        // assert_eq!(out.size(), eval_count);
        // let args = &[
        //     out.as_arg(),
        //     coeffs.as_arg(),
        //     which.as_arg(),
        //     xs.as_arg(),
        //     KernelArg::Integer(count as u32),
        // ];
        // let kernel = self.kernels.get("multi_poly_eval").unwrap();
        // let params = simple_launch_params(out.size() as u32 * 256, 256);
        // self.dispatch(kernel, args, count as u64, Some(params));
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_add_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input1: &Self::Buffer<Self::Elem>,
        input2: &Self::Buffer<Self::Elem>,
    ) {
        // assert_eq!(output.size(), input1.size());
        // assert_eq!(output.size(), input2.size());
        // let count = output.size() as u64;
        // let args = &[output.as_arg(), input1.as_arg(), input2.as_arg()];
        // self.dispatch_by_name("eltwise_add_fp", args, count);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_sum_extelem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::ExtElem>,
    ) {
        // let count = output.size() / Self::ExtElem::EXT_SIZE;
        // let to_add = input.size() / count;
        // assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        // assert_eq!(input.size(), count * to_add);
        // let args = &[
        //     output.as_arg(),
        //     input.as_arg(),
        //     KernelArg::Integer(count as u32),
        //     KernelArg::Integer(to_add as u32),
        // ];
        // self.dispatch_by_name("eltwise_sum_fpext", args, count as u64);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn eltwise_copy_elem(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
    ) {
        assert_eq!(output.size(), input.size());
        let count = output.size() as u64;

        let shader = self
            .device
            .create_shader_module(wgpu::ShaderModuleDescriptor {
                label: None,
                source: wgpu::ShaderSource::Wgsl(std::borrow::Cow::Borrowed(include_str!(
                    "kernels.wgsl"
                ))),
            });

        let bind_group_layout =
            self.device
                .create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
                    label: None,
                    entries: &[wgpu::BindGroupLayoutEntry {
                        binding: 0,
                        visibility: wgpu::ShaderStages::COMPUTE,
                        ty: wgpu::BindingType::Buffer {
                            ty: wgpu::BufferBindingType::Storage { read_only: false },
                            has_dynamic_offset: false,
                            // Going to have this be None just to be safe.
                            min_binding_size: None,
                        },
                        count: None,
                    }],
                });

        let bind_group = self.device.create_bind_group(&wgpu::BindGroupDescriptor {
            label: None,
            layout: &bind_group_layout,
            entries: &[wgpu::BindGroupEntry {
                binding: 0,
                resource: input.buffer.as_entire_binding(),
            }],
        });

        let pipeline_layout = self
            .device
            .create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                label: None,
                bind_group_layouts: &[&bind_group_layout],
                push_constant_ranges: &[],
            });

        let pipeline = self
            .device
            .create_compute_pipeline(&wgpu::ComputePipelineDescriptor {
                label: None,
                layout: Some(&pipeline_layout),
                module: &shader,
                entry_point: "main",
                compilation_options: Default::default(),
            });

        let mut command_encoder = self
            .device
            .create_command_encoder(&wgpu::CommandEncoderDescriptor { label: None });

        {
            let mut compute_pass =
                command_encoder.begin_compute_pass(&wgpu::ComputePassDescriptor {
                    label: None,
                    timestamp_writes: None,
                });
            compute_pass.set_pipeline(&pipeline);
            compute_pass.set_bind_group(0, &bind_group, &[]);
            compute_pass.dispatch_workgroups(2000, 1, 1);
        }

        // let args = &[output.as_arg(), input.as_arg()];
        // self.dispatch_by_name("eltwise_copy_fp", args, count);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn fri_fold(
        &self,
        output: &Self::Buffer<Self::Elem>,
        input: &Self::Buffer<Self::Elem>,
        mix: &Self::ExtElem,
    ) {
        // let count = output.size() / Self::ExtElem::EXT_SIZE;
        // assert_eq!(output.size(), count * Self::ExtElem::EXT_SIZE);
        // assert_eq!(input.size(), output.size() * FRI_FOLD);
        // let mix = self.copy_from_extelem("mix", &[*mix]);
        // let args = &[
        //     output.as_arg(),
        //     input.as_arg(),
        //     mix.as_arg(),
        //     KernelArg::Integer(count as u32),
        // ];
        // self.dispatch_by_name("fri_fold", args, count as u64);
        unimplemented!()
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
        // tracing::debug!(
        //     "output: {}, input: {}, combos: {}, input_size: {input_size}, count: {count}",
        //     output.size(),
        //     input.size(),
        //     combos.size(),
        // );

        // let mix_start = self.copy_from_extelem("mix_start", &[*mix_start]);
        // let mix = self.copy_from_extelem("mix", &[*mix]);
        // let args = &[
        //     output.as_arg(),
        //     input.as_arg(),
        //     combos.as_arg(),
        //     mix_start.as_arg(),
        //     mix.as_arg(),
        //     KernelArg::Integer(input_size as u32),
        //     KernelArg::Integer(count as u32),
        // ];
        // self.dispatch_by_name("mix_poly_coeffs", args, count as u64);
        unimplemented!()
    }

    fn hash_fold(&self, io: &Self::Buffer<Digest>, input_size: usize, output_size: usize) {
        // assert_eq!(input_size, 2 * output_size);
        // self.hash.as_ref().unwrap().hash_fold(self, io, output_size);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn hash_rows(&self, output: &Self::Buffer<Digest>, matrix: &Self::Buffer<Self::Elem>) {
        // self.hash.as_ref().unwrap().hash_rows(self, output, matrix);
        unimplemented!()
    }

    #[tracing::instrument(skip_all)]
    fn zk_shift(&self, io: &Self::Buffer<Self::Elem>, poly_count: usize) {
        // let bits = log2_ceil(io.size() / poly_count);
        // let count = io.size();
        // assert_eq!(io.size(), poly_count * (1 << bits));
        // let args = &[io.as_arg(), KernelArg::Integer(bits as u32)];
        // self.dispatch_by_name("zk_shift", args, count as u64);
        unimplemented!()
    }

    fn gather_sample(
        &self,
        dst: &Self::Buffer<Self::Elem>,
        src: &Self::Buffer<Self::Elem>,
        idx: usize,
        size: usize,
        stride: usize,
    ) {
        // let args = &[
        //     dst.as_arg(),
        //     src.as_arg(),
        //     KernelArg::Integer(idx as u32),
        //     KernelArg::Integer(stride as u32),
        // ];
        // self.dispatch_by_name("gather_sample", args, size as u64);
        unimplemented!()
    }

    fn has_unified_memory(&self) -> bool {
        // self.device.has_unified_memory()
        unimplemented!()
    }

    fn get_hash_suite(&self) -> &HashSuite<Self::Field> {
        // self.hash.as_ref().unwrap().get_hash_suite()
        unimplemented!()
    }

    fn prefix_products(&self, io: &Self::Buffer<Self::ExtElem>) {
        io.view_mut(|io| {
            for i in 1..io.len() {
                io[i] *= io[i - 1];
            }
        });
    }

    fn eltwise_zeroize_elem(&self, elems: &Self::Buffer<Self::Elem>) {
        elems.view_mut(|slice| {
            slice.par_iter_mut().for_each(|elem| {
                *elem = elem.valid_or_zero();
            });
        })
    }
}

#[cfg(test)]
mod tests {
    use test_log::test;

    // use super::{MetalHalPoseidon, MetalHalPoseidon2, MetalHalSha256};
    use crate::hal::testutil;

    #[test]
    fn batch_bit_reverse() {
        testutil::batch_bit_reverse(MetalHalSha256::new());
    }

    #[test]
    fn batch_evaluate_any() {
        testutil::batch_evaluate_any(MetalHalSha256::new());
    }

    #[test]
    fn batch_expand_into_evaluate_ntt() {
        testutil::batch_expand_into_evaluate_ntt(MetalHalSha256::new());
    }

    #[test]
    fn batch_interpolate_ntt() {
        testutil::batch_interpolate_ntt(MetalHalSha256::new());
    }

    #[test]
    #[should_panic]
    fn check_req() {
        testutil::check_req(MetalHalSha256::new());
    }

    #[test]
    fn eltwise_add_fp() {
        testutil::eltwise_add_elem(MetalHalSha256::new());
    }

    #[test]
    fn eltwise_copy_fp() {
        testutil::eltwise_copy_elem(MetalHalSha256::new());
    }

    #[test]
    fn eltwise_sum_extelem() {
        testutil::eltwise_sum_extelem(MetalHalSha256::new());
    }

    #[test]
    fn fri_fold() {
        testutil::fri_fold(MetalHalSha256::new());
    }

    #[test]
    fn mix_poly_coeffs() {
        testutil::mix_poly_coeffs(MetalHalSha256::new());
    }

    #[test]
    fn hash_fold_sha256() {
        testutil::hash_fold(MetalHalSha256::new());
    }

    #[test]
    fn hash_rows_sha256() {
        testutil::hash_rows(MetalHalSha256::new());
    }

    #[test]
    fn hash_fold_poseidon() {
        testutil::hash_fold(MetalHalPoseidon::new());
    }

    #[test]
    fn hash_rows_poseidon() {
        testutil::hash_rows(MetalHalPoseidon::new());
    }

    #[test]
    fn hash_fold_poseidon2() {
        testutil::hash_fold(MetalHalPoseidon2::new());
    }

    #[test]
    fn hash_rows_poseidon2() {
        testutil::hash_rows(MetalHalPoseidon2::new());
    }

    #[test]
    fn slice() {
        testutil::slice(MetalHalSha256::new());
    }

    #[test]
    fn zk_shift() {
        testutil::zk_shift(MetalHalSha256::new());
    }

    #[test]
    fn gather_sample() {
        testutil::gather_sample(MetalHalSha256::new());
    }

    #[test]
    fn prefix_products() {
        use crate::hal::{cpu::CpuHal, dual::DualHal, Hal as _};
        use risc0_core::field::baby_bear::BabyBearExtElem;
        use std::rc::Rc;

        fn test(size: usize) {
            let hal_gpu = MetalHalSha256::new();
            let hal_cpu = CpuHal::new(hal_gpu.get_hash_suite().clone());
            let hal = DualHal::new(Rc::new(hal_cpu), Rc::new(hal_gpu));

            use rand::thread_rng;
            use risc0_core::field::Elem as _;
            let mut rng = thread_rng();
            let io: Vec<_> = (0..size)
                .map(|_| BabyBearExtElem::random(&mut rng))
                .collect();
            let io = hal.copy_from_extelem("io", io.as_slice());

            hal.prefix_products(&io);
        }

        for i in 15..=20 {
            println!("po2: {i}");
            test(1 << i);
        }
    }
}
