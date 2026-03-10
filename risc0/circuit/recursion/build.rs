// Copyright 2026 RISC Zero, Inc.
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

use std::env;

fn main() {
    let prove = std::env::var("CARGO_FEATURE_PROVE").is_ok();
    let metal = (std::env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos")
        && std::env::var("CARGO_CFG_TARGET_ARCH").is_ok_and(|arch| arch == "aarch64"))
        || std::env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "ios");

    if prove && metal {
        println!(
            "cargo:rustc-env=RECURSION_METAL_PATH={}",
            env::var("DEP_RISC0_CIRCUIT_RECURSION_SYS_METAL_KERNEL")
                .expect("on macos risc0-circuit-recursion-sys should build metal kernels")
        );
    }
}
