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

use clap::Parser;

#[derive(Parser)]
pub struct BootstrapProtos;

impl BootstrapProtos {
    pub fn run(&self) {
        unsafe {
            std::env::set_var("PROTOC", protobuf_src::protoc());
        }

        prost_build::Config::new()
            .out_dir("risc0/zkvm/src/host/server/exec")
            .compile_protos(
                &["risc0/zkvm/src/host/server/exec/profile.proto"],
                &["risc0/zkvm/src/host/server/exec"],
            )
            .unwrap();

        prost_build::Config::new()
            .out_dir("risc0/zkvm/src/host/protos")
            .skip_debug(["api.Asset", "api.OnIoReply", "api.SliceIo", "api.PosixCmd"])
            .compile_protos(
                &[
                    "risc0/zkvm/src/host/protos/api.proto",
                    "risc0/zkvm/src/host/protos/core.proto",
                ],
                &["risc0/zkvm/src/host/protos"],
            )
            .unwrap();
    }
}
