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

use risc0_zkvm::ExecutorEnv;

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "wasm";
    const METHOD_ELF: &'static [u8] = wasm_methods::WASM_INTERP_ELF;

    fn run() -> Metrics {
        let wasm = wat2wasm().expect("Failed to parse_str");
        let iters: i32 = 100;
        let env = ExecutorEnv::builder()
            .write(&wasm)
            .unwrap()
            .write(&iters)
            .unwrap()
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}

fn wat2wasm() -> Result<Vec<u8>, wat::Error> {
    let wat = r#"
    (module
        (export "fib" (func $fib))
        (func $fib (; 0 ;) (param $0 i32) (result i32)
        (local $1 i32)
        (local $2 i32)
        (local $3 i32)
        (local $4 i32)
        (local.set $4
         (i32.const 1)
        )
        (block $label$0
         (br_if $label$0
          (i32.lt_s
           (local.get $0)
           (i32.const 1)
          )
         )
         (local.set $3
          (i32.const 0)
         )
         (loop $label$1
          (local.set $1
           (i32.add
            (local.get $3)
            (local.get $4)
           )
          )
          (local.set $2
           (local.get $4)
          )
          (local.set $3
           (local.get $4)
          )
          (local.set $4
           (local.get $1)
          )
          (br_if $label$1
           (local.tee $0
            (i32.add
             (local.get $0)
             (i32.const -1)
            )
           )
          )
         )
         (return
          (local.get $2)
         )
        )
        (i32.const 0)
       )
    )
    "#;
    wat::parse_str(wat)
}
