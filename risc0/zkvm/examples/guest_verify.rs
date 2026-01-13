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

use clap::Parser;
use risc0_zkvm::{ExecutorEnv, ExitCode, ProverOpts, Receipt, default_executor, get_prover_server};
use risc0_zkvm_methods::{MULTI_TEST_ELF, MULTI_TEST_ID, VERIFY_ELF, multi_test::MultiTestSpec};

#[derive(Parser)]
struct CliOptions {
    #[arg(long, default_value = "false")]
    dev_mode: bool,
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();
    let cli_options = CliOptions::parse();

    if cli_options.dev_mode {
        guest_verify_dev_mode()
    } else {
        guest_verify();
    }
}

#[cfg_attr(test, test)]
#[cfg_attr(feature = "cuda", gpu_guard::gpu_guard)]
fn guest_verify() {
    let receipt = generate_receipt(&ProverOpts::default());
    exec_verify(&receipt, false /* dev_mode */);
}

#[cfg_attr(test, test)]
fn guest_verify_dev_mode() {
    let receipt = generate_receipt(&ProverOpts::default().with_dev_mode(true));
    exec_verify(&receipt, true /* dev_mode */);
}

fn generate_receipt(opts: &ProverOpts) -> Receipt {
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .unwrap()
        .build()
        .unwrap();
    let prover = get_prover_server(opts).unwrap();
    prover.prove(env, MULTI_TEST_ELF).unwrap().receipt
}

fn exec_verify(receipt: &Receipt, dev_mode: bool) {
    let input = (receipt.clone(), MULTI_TEST_ID, dev_mode);
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();
    let session = default_executor().execute(env, VERIFY_ELF).unwrap();
    assert_eq!(session.exit_code, ExitCode::Halted(0));
}
