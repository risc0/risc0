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

use anyhow::{Context, Result};
use risc0_zkvm::{get_prover_server, ExecutorEnv, ProverOpts, Receipt, ReceiptKind};
use risc0_zkvm_methods::{multi_test::MultiTestSpec, MULTI_TEST_ELF};

fn prove_nothing(kind: ReceiptKind) -> Result<Receipt> {
    let opts = ProverOpts::default().with_receipt_kind(kind);
    let env = ExecutorEnv::builder()
        .write(&MultiTestSpec::DoNothing)
        .context("failed to write DoNothing input")?
        .build()
        .context("failed to build ExecutorEnv")?;

    Ok(get_prover_server(&opts)
        .context("failed to get prover")?
        .prove(env, MULTI_TEST_ELF)
        .context("failed to prove MULTI_TEST_ELF")?
        .receipt)
}

fn write_seed_bytes(path: &PathBuf, bytes: &[u8]) -> Result<()> {
    fs::write(path, bytes).with_context(|| format!("failed to write {}", path.display()))?;
    println!("Wrote {} bytes to {}", bytes.len(), path.display());
    Ok(())
}

fn seed_receipt_seal_verify_corpus(composite_receipt: &Receipt) -> Result<()> {
    let receipt_seal_verify_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"))
        .join("corpus")
        .join("receipt_seal_verify");
    fs::create_dir_all(&receipt_seal_verify_dir)
        .with_context(|| format!("failed to create {}", receipt_seal_verify_dir.display()))?;

    let composite = composite_receipt
        .inner
        .composite()
        .context("expected a composite receipt")?;
    let segment = composite
        .segments
        .first()
        .ok_or_else(|| anyhow::anyhow!("composite receipt had no segments"))?;
    let segment_seal_path = receipt_seal_verify_dir.join("segment_do_nothing_seal.bin");
    write_seed_bytes(&segment_seal_path, &segment.get_seal_bytes())
}

fn seed_receipt_decode_and_verify_corpus() -> Result<()> {
    let receipt_dir = PathBuf::from(env!("CARGO_MANIFEST_DIR"))
        .join("corpus")
        .join("receipt_decode_and_verify");
    fs::create_dir_all(&receipt_dir)
        .with_context(|| format!("failed to create {}", receipt_dir.display()))?;

    let receipt_seeds = [
        (
            "receipt_composite_do_nothing.bin",
            prove_nothing(ReceiptKind::Composite)?,
        ),
        (
            "receipt_succinct_do_nothing.bin",
            prove_nothing(ReceiptKind::Succinct)?,
        ),
        (
            "receipt_groth16_do_nothing.bin",
            prove_nothing(ReceiptKind::Groth16)?,
        ),
    ];

    for (filename, receipt) in receipt_seeds {
        let encoded = bincode::serialize(&receipt)
            .with_context(|| format!("failed to serialize seed receipt {filename}"))?;
        let out_path = receipt_dir.join(filename);
        write_seed_bytes(&out_path, &encoded)?;
    }

    Ok(())
}

fn main() -> Result<()> {
    let composite_receipt = prove_nothing(ReceiptKind::Composite)?;
    seed_receipt_seal_verify_corpus(&composite_receipt)?;
    seed_receipt_decode_and_verify_corpus()?;

    Ok(())
}
