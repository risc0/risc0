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

use risc0_zkvm::{ExecutorEnv, default_prover};
use wasm_methods::{WASM_INTERP_ELF, WASM_INTERP_ID};

fn wat2wasm(wat: &str) -> Result<Vec<u8>, wat::Error> {
    wat::parse_str(wat)
}

fn run_guest(iters: i32) -> i32 {
    let wat = r#"
    (module
        (export "fib" (func $fib))
        (func $fib (; 0 ;) (param $0 i32) (result i32)
        (local $1 i32)
        (local $2 i32)
        (local $3 i32)
        (local $4 i32)
        (set_local $4
         (i32.const 1)
        )
        (block $label$0
         (br_if $label$0
          (i32.lt_s
           (get_local $0)
           (i32.const 1)
          )
         )
         (set_local $3
          (i32.const 0)
         )
         (loop $label$1
          (set_local $1
           (i32.add
            (get_local $3)
            (get_local $4)
           )
          )
          (set_local $2
           (get_local $4)
          )
          (set_local $3
           (get_local $4)
          )
          (set_local $4
           (get_local $1)
          )
          (br_if $label$1
           (tee_local $0
            (i32.add
             (get_local $0)
             (i32.const -1)
            )
           )
          )
         )
         (return
          (get_local $2)
         )
        )
        (i32.const 0)
       )
    )
    "#;

    let wasm = wat2wasm(wat).expect("Failed to parse_str");

    let env = ExecutorEnv::builder()
        .write(&wasm)
        .unwrap()
        .write(&iters)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, WASM_INTERP_ELF).unwrap().receipt;

    receipt.verify(WASM_INTERP_ID).expect(
        "Code you have proven should successfully verify; did you specify the correct image ID?",
    );
    let result: i32 = receipt.journal.decode().unwrap();

    result
}

fn main() {
    let fib_iters: i32 = 100;
    let _ = run_guest(fib_iters);
}

#[cfg(test)]
mod tests {
    fn fibonacci(n: i32) -> i32 {
        let (mut a, mut b) = (0, 1);
        for _ in 0..n {
            let c = a;
            a = b;
            b += c;
        }
        a
    }

    #[test]
    fn wasm_fib() {
        let fib_iters: i32 = 10;
        let result = super::run_guest(fib_iters);
        assert_eq!(
            result,
            fibonacci(fib_iters),
            "We expect the zkVM output to be the product of the inputs"
        )
    }
}
