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
    }
}
