// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::guest::env;
use wasmi::{Engine, Linker, Module, Store};

fn main() {
    let engine = Engine::default();

    let wasm: Vec<u8> = env::read();
    let iters: i32 = env::read();

    // Derived from the wasmi example: https://docs.rs/wasmi/0.29.0/wasmi/#example
    let module = Module::new(&engine, &mut &wasm[..]).expect("Failed to create module");
    type HostState = u32;

    let linker = <Linker<HostState>>::new(&engine);
    let mut store = Store::new(&engine, 42);
    let instance = linker
        .instantiate(&mut store, &module)
        .expect("failed to instantiate")
        .start(&mut store)
        .expect("Failed to start");

    let fib = instance
        .get_typed_func::<i32, i32>(&store, "fib")
        .expect("Failed to get typed_func");
    let res = fib.call(&mut store, iters).expect("Failed to call");
    env::log(&format!("fib {} - {}", iters, res));
    env::commit(&res);
}
