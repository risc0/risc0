// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
