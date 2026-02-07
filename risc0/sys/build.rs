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

use std::{
    env,
    path::{Path, PathBuf},
};

use risc0_build_kernel::{KernelBuild, KernelType};

fn main() {
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
    let cxx_root = manifest_dir.join("cxx");
    let kernels_root = manifest_dir.join("kernels");
    println!("cargo:cxx_root={}", cxx_root.display());
    println!("cargo:kernels_root={}", kernels_root.display());

    if env::var("CARGO_FEATURE_CUDA").is_ok() {
        println!(
            "cargo:cuda_root={}",
            kernels_root.join("zkp/cuda").display()
        );
        build_cuda_kernels(&cxx_root);
    }

    if env::var("CARGO_CFG_TARGET_OS").is_ok_and(|os| os == "macos" || os == "ios") {
        println!(
            "cargo:metal_root={}",
            kernels_root.join("zkp/metal").display()
        );
        build_metal_kernels();
    }
}

fn build_cuda_kernels(cxx_root: &Path) {
    KernelBuild::new(KernelType::Cuda, "kernel_build.manifest")
        .files([
            "kernels/zkp/cuda/combos.cu",
            "kernels/zkp/cuda/eltwise.cu",
            "kernels/zkp/cuda/ffi.cu",
            "kernels/zkp/cuda/fri_prove.cu",
            "kernels/zkp/cuda/kernels.cu",
            "kernels/zkp/cuda/sha.cu",
            "kernels/zkp/cuda/supra/api.cu",
            "kernels/zkp/cuda/supra/ntt.cu",
            "kernels/zkp/cuda/supra/poseidon2.cu",
        ])
        .flag("-DFEATURE_BABY_BEAR")
        .include(cxx_root)
        .include(env::var("DEP_BLST_C_SRC").unwrap())
        .include(env::var("DEP_RISC0_SPPARK_ROOT").unwrap())
        .compile("risc0_zkp_cuda");
}

fn build_metal_kernels() {
    const METAL_KERNELS: &[(&str, &[&str])] = &[(
        "zkp",
        &[
            "eltwise.metal",
            "fri.metal",
            "mix.metal",
            "ntt.metal",
            "poseidon2.metal",
            "sha.metal",
            "zk.metal",
        ],
    )];

    let inc_path = Path::new("kernels/zkp/metal");
    for (name, srcs) in METAL_KERNELS {
        let dir = Path::new("kernels").join(name).join("metal");
        let src_paths = srcs.iter().map(|x| dir.join(x));
        let out = format!("metal_kernels_{name}");
        KernelBuild::new(KernelType::Metal, "kernel_build.manifest")
            .files(src_paths)
            .include(inc_path)
            .compile(&out);
    }
}
