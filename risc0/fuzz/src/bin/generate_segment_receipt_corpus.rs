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

use std::{fs, path::PathBuf};

use anyhow::{Context, Result, bail};
use risc0_zkvm::{ExecutorEnv, ProverOpts, ReceiptKind, get_prover_server};
use risc0_zkvm_methods::{MULTI_TEST_ELF, multi_test::MultiTestSpec};

fn main() -> Result<()> {
    let opts = ProverOpts::default().with_receipt_kind(ReceiptKind::Composite);
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .context("failed to write DoNothing input")?
        .build()
        .context("failed to build ExecutorEnv")?;

    let receipt = get_prover_server(&opts)
        .context("failed to get prover")?
        .prove(env, MULTI_TEST_ELF)
        .context("failed to prove MULTI_TEST_ELF")?
        .receipt;

    let composite = receipt
        .inner
        .composite()
        .context("expected a composite receipt")?;
    let segment = composite
        .segments
        .first()
        .ok_or_else(|| anyhow::anyhow!("composite receipt had no segments"))?;

    let seal_bytes = segment.get_seal_bytes();
    if seal_bytes.is_empty() {
        bail!("segment seal was empty");
    }

    let out_path = PathBuf::from(env!("CARGO_MANIFEST_DIR"))
        .join("corpus")
        .join("receipt_seal")
        .join("segment_do_nothing_seal.bin");

    fs::write(&out_path, &seal_bytes)
        .with_context(|| format!("failed to write {}", out_path.display()))?;

    println!(
        "Wrote {} bytes to {}",
        seal_bytes.len(),
        out_path.display()
    );

    Ok(())
}
