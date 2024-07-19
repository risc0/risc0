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

macro_rules! println_build {
    ($($tokens: tt)*) => {
        println!("cargo:warning={}", format!($($tokens)*))
    }
}

fn main() {
    let client_version = risc0_zkvm::get_version().unwrap();
    let server_version = risc0_zkvm::get_server_version().unwrap();
    if !client_version.pre.is_empty()
        && server_version.pre.is_empty()
        && client_version != server_version
    {
        println_build!("");
        println_build!("");
        println_build!("       WARNING: The example code that you are trying to run is not compatible with your");
        println_build!("       installation of RISC Zero and the cargo command you ran to build or run this example");
        println_build!("       will be terminated. Run the command below to checkout the correct version of the");
        println_build!("       example code and run your cargo command again.");
        println_build!("");
        println_build!("                     git checkout origin/release-{}.{}", server_version.major, server_version.minor);
        println_build!("");
        println_build!("       Version of the current example code:    {client_version} (pre-release)");
        println_build!("       Version of your RISC Zero installation: {server_version}");
        println_build!("");
        println_build!("");
        return;
    }
    risc0_build::embed_methods();
}
