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

use cxx_build::CFG;

fn main() {
    CFG.include_prefix = "risc0/zkvm/circuit";
    CFG.exported_header_links = vec!["risc0-zkp-core", "risc0-zkvm-platform"];

    cxx_build::bridge("src/lib.rs")
        .file("accum_regs.cpp")
        .file("compute_cycle.cpp")
        .file("context.cpp")
        .file("data_regs.cpp")
        .file("decode_cycle.cpp")
        .file("divide_cycle.cpp")
        .file("final_cycle.cpp")
        .file("gen_context.cpp")
        .file("make_circuit.cpp")
        .file("mem_check.cpp")
        .file("mem_io_regs.cpp")
        .file("multiply_cycle.cpp")
        .file("poly_context.cpp")
        .file("sha_cycle.cpp")
        .file("step_state.cpp")
        .flag_if_supported("/std:c++17")
        .flag_if_supported("/Zc:preprocessor")
        .flag_if_supported("/EHsc")
        .flag_if_supported("-std=c++17")
        .warnings(false)
        .compile("risc0-zkp-circuit");

    println!("cargo:rustc-link-lib=static=risc0-core");
}
