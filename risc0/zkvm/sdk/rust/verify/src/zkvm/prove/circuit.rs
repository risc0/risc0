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

// TODO: WIP

use alloc::vec::Vec;

use paste::paste;
use risc0_zkp::core::{fp::Fp, fp4::Fp4, sha::Sha};
use risc0_zkp::hal::Buffer;

use crate::{
    zkp::{self, prove::write_iop::WriteIOP, INV_RATE},
    zkvm::{prove::exec::ExecState, taps::RISCV_TAPS},
};

pub struct RV32Circuit {
    exec: ExecState,
    accum: Vec<Fp>,
    // MemoryHandler& io_;
    po2: u32,
}

struct MixState {
    tot: Fp4,
    mul: Fp4,
}

// #define do_begin(out) MixState m##out = {Fp4(0), Fp4(1)};
macro_rules! do_begin {
    ($out:literal) => {{
        paste! {
            let [<m $out>] = MixState {
                tot: Fp4::zero(),
                mul: Fp4::one(),
            };
        }
    }};
}

// #define do_get(out, buf, reg, back, id)
//   Fp v##out = buf[reg * domain + ((idx - kInvRate * back) & mask)];
macro_rules! do_get {
    ($out:literal, $buf:ident, $reg:literal, $back:literal, $id:literal) => {{
        paste! {
            let [<v $out>] = $buf[$reg * domain + ((idx - INV_RATE) * $back) & mask];
        }
    }};
}

impl zkp::prove::Circuit for RV32Circuit {
    fn taps(&self) -> &'static zkp::taps::Taps<'static> {
        RISCV_TAPS
    }

    fn execute<S: Sha>(&mut self, iop: &mut WriteIOP<S>) {
        //   // Run actual RISC-V execution
        //   exec_.run(kMaxCycles, io_);

        //   // Get # of timesteps
        //   po2_ = log2Ceil(exec_.context.numSteps);
        //   size_t size = size_t(1) << po2_;
        //   LOG(1, "size = " << size);

        //   // Write final low register state
        //   for (size_t i = 0; i < kOutputRegs; i++) {
        //     const Fp* globals = exec_.context.globals;
        //     uint32_t regVal = globals[2 * i].asUInt32() | (globals[2 * i +
        // 1].asUInt32() << 16);     LOG(2, "x" << i + 1 << " = " <<
        // hex(regVal));     iop.write(&regVal, 1);
        //   }

        //   // Write the po2 for size
        //   iop.write(&po2_, 1);

        //   // Now, do memory verification
        //   for (size_t i = 0; i < size - kZkCycles; i++) {
        //     exec_.context.curStep = i;
        //     dataStepCheck(exec_.context, exec_.code.data(), exec_.data.data());
        //   }

        //   // Fill final cycles of data with noise to make ZK
        //   for (size_t i = 0; i < kDataSize; i++) {
        //     for (size_t j = size - kZkCycles; j < size; j++) {
        //       exec_.data[i * size + j] = Fp::random(CryptoRng::shared());
        //     }
        //   }

        todo!()
    }

    fn accumulate<S: Sha>(&mut self, iop: &mut WriteIOP<S>) {
        todo!()
    }

    fn eval_check(
        &self,
        check: &Buffer<Fp>,
        code: &Buffer<Fp>,
        data: &Buffer<Fp>,
        accum: &Buffer<Fp>,
        poly_mix: Fp4,
    ) {
        let size = 1 << self.po2;
        let domain = size * INV_RATE;
        let mask = domain - 1;
        // Fp* out = check.devicePointer();
        // constexpr size_t expPo2 = log2Ceil(kInvRate);
        // const Fp* code = codeEval.devicePointer();
        // const Fp* data = dataEval.devicePointer();
        // const Fp* accum = accumEval.devicePointer();
        // const Fp* global = exec_.context.globals;
        // for idx in 0..domain {
        //     include!("check_eval.rs");
        // }

        todo!()
    }

    fn po2(&self) -> u32 {
        self.po2
    }

    fn get_code(&self) -> &[Fp] {
        &self.exec.code
    }

    fn get_data(&self) -> &[Fp] {
        &self.exec.data
    }

    fn get_accum(&self) -> &[Fp] {
        &self.accum
    }
}
