// Copyright 2022 Risc0, Inc.
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

#![no_std]
#![no_main]

use core::mem;

use risc0_zkp::{
    core::{fp::Fp, fp4::Fp4},
    verify::VerifyHal,
};
use risc0_zkvm::receipt::verify_with_hal;
use risc0_zkvm_guest::{entry, env, memory_barrier, sha_insecure};
use risc0_zkvm_platform::{
    io::{
        ComputePolyDescriptor, PolyEvalDescriptor, SliceDescriptor, GPIO_COMPUTE_POLY,
        GPIO_POLY_EVAL, SENDRECV_CHANNEL_INITIAL_INPUT,
    },
    rt::host_io::host_recv,
};

entry!(main);

struct GuestVerifyHal {
    sha: sha_insecure::Impl,
}

impl GuestVerifyHal {
    fn new() -> Self {
        let sha = sha_insecure::Impl {};
        Self { sha }
    }
}

impl VerifyHal for GuestVerifyHal {
    type Sha = sha_insecure::Impl;

    fn sha(&self) -> &Self::Sha {
        &self.sha
    }

    fn debug(&self, msg: &str) {
        env::log(msg);
    }

    fn compute_polynomial(&self, u: &[Fp4], poly_mix: Fp4, out: &[Fp], mix: &[Fp]) -> Fp4 {
        let desc = &ComputePolyDescriptor {
            eval_u: SliceDescriptor::new(u),
            poly_mix: &poly_mix as *const Fp4 as u32,
            out: SliceDescriptor::new(out),
            mix: SliceDescriptor::new(mix),
        };

        memory_barrier(desc);
        unsafe { GPIO_COMPUTE_POLY.as_ptr().write_volatile(desc) }

        const FP4_WORDS: usize = mem::size_of::<Fp4>() / mem::size_of::<u32>();
        let words: &[u32; FP4_WORDS] = host_recv(FP4_WORDS).try_into().unwrap();

        *bytemuck::cast_ref(words)
    }

    fn poly_eval(&self, coeffs: &[Fp4], x: Fp4, y: Fp) -> Fp4 {
        let desc = &PolyEvalDescriptor {
            coeffs: SliceDescriptor::new(coeffs),
            x: &x as *const Fp4 as u32,
            y: &y as *const Fp as u32,
        };

        memory_barrier(desc);
        unsafe { GPIO_POLY_EVAL.as_ptr().write_volatile(desc) }

        const FP4_WORDS: usize = mem::size_of::<Fp4>() / mem::size_of::<u32>();
        let words: &[u32; FP4_WORDS] = host_recv(FP4_WORDS).try_into().unwrap();

        // This is here to try to get more accurate cycle estimations.
        for _ in 0..coeffs.len() {
            unsafe {
                core::arch::asm!(
                    r#"
                nop // loads
                nop // muls
                nop // adds/stores
            "#
                )
            };
        }

        *bytemuck::cast_ref(words)
    }
}

pub fn main() {
    env::log("main");

    let (words, _) = env::send_recv_as_u32(SENDRECV_CHANNEL_INITIAL_INPUT, &[]);
    let seal_len = words[0] as usize;
    let seal = &words[1..1 + seal_len];
    let id_len = words[1 + seal_len] as usize;
    let method_id = &words[2 + seal_len..2 + seal_len + id_len];

    let hal = GuestVerifyHal::new();
    verify_with_hal(&hal, method_id, seal).unwrap();

    env::log("done");
}
