// Copyright 2025 RISC Zero, Inc.
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
