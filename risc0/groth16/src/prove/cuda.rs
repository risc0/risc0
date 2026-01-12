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

use std::{io::Cursor, path::Path};

use anyhow::{Context as _, Result, anyhow};
use memmap2::Mmap;
use risc0_groth16_sys::{Fp, Groth16Proof, ProveParams};
use rzup::{Component, Rzup, Version};

use crate::Seal;

use super::seal_to_json::to_json;

fn fp_to_bytes(fp: &Fp) -> Vec<u8> {
    fp.v.iter().rev().flat_map(|v| v.to_be_bytes()).collect()
}

impl From<Groth16Proof> for Seal {
    fn from(p: Groth16Proof) -> Self {
        Self {
            a: vec![fp_to_bytes(&p.a[0]), fp_to_bytes(&p.a[1])],
            b: vec![
                vec![fp_to_bytes(&p.b[1]), fp_to_bytes(&p.b[0])],
                vec![fp_to_bytes(&p.b[3]), fp_to_bytes(&p.b[2])],
            ],
            c: vec![fp_to_bytes(&p.c[0]), fp_to_bytes(&p.c[1])],
        }
    }
}

#[test]
fn seal_from_groth16_proof() {
    let proof = Groth16Proof {
        a: [
            Fp {
                v: [
                    0x97653ce9, 0x4de17ba7, 0xd9fe883f, 0x284e1f93, 0x2b906502, 0xcb487ca9,
                    0x801ed812, 0x1df995c,
                ],
            },
            Fp {
                v: [
                    0xe2f8a546, 0xe7d88208, 0x3026ff92, 0x7e3cd410, 0x5d8e098c, 0x88eb46e8,
                    0xff1f95f7, 0x11ec25c3,
                ],
            },
        ],
        c: [
            Fp {
                v: [
                    0x734be547, 0x8e5d964c, 0x16ef6b1a, 0x3f825c48, 0xdb61e31c, 0x56ff3103,
                    0xafe6f0db, 0x20e35b42,
                ],
            },
            Fp {
                v: [
                    0x1bc6524a, 0xdd606cf0, 0x716b3b46, 0x3c759e05, 0x539b4276, 0x5a92edf6,
                    0xac1f3e38, 0x236c3939,
                ],
            },
        ],
        b: [
            Fp {
                v: [
                    0x7e4e89e0, 0xbe10e9a7, 0x973b123c, 0xceaa028, 0x3ab8ed05, 0x1a54ee13,
                    0x6610f5df, 0xc2c5b65,
                ],
            },
            Fp {
                v: [
                    0x89bc1f93, 0x2d57295e, 0xe5a0b53e, 0x7b7505d, 0x3607c056, 0x3c982519,
                    0xab8158f6, 0xc70f44b,
                ],
            },
            Fp {
                v: [
                    0xd7012fb7, 0x91435284, 0x3ba20fa8, 0x8435c981, 0x28ca3a44, 0x324214b0,
                    0x75f55532, 0x1c8ea90c,
                ],
            },
            Fp {
                v: [
                    0x4780a44a, 0xc452dab8, 0xfdd24ee2, 0xbe410e89, 0xa345f169, 0xc0c6e72a,
                    0xdff634fc, 0x2064fa3b,
                ],
            },
        ],
    };

    let seal: Seal = proof.into();

    let proof_json: crate::types::ProofJson = serde_json::from_str(
        "{ \
            \"pi_a\":[\
                \"0x01df995c801ed812cb487ca92b906502284e1f93d9fe883f4de17ba797653ce9\", \
                \"0x11ec25c3ff1f95f788eb46e85d8e098c7e3cd4103026ff92e7d88208e2f8a546\", \
                \"1\" \
            ],
            \"pi_b\": [\
                [\
                    \"0x0c2c5b656610f5df1a54ee133ab8ed050ceaa028973b123cbe10e9a77e4e89e0\", \
                    \"0x0c70f44bab8158f63c9825193607c05607b7505de5a0b53e2d57295e89bc1f93\"\
                ],[\
                    \"0x1c8ea90c75f55532324214b028ca3a448435c9813ba20fa891435284d7012fb7\", \
                    \"0x2064fa3bdff634fcc0c6e72aa345f169be410e89fdd24ee2c452dab84780a44a\"\
                ], [\
                    \"1\", \
                    \"0\" \
                ]\
            ], \
            \"pi_c\": [\
                \"0x20e35b42afe6f0db56ff3103db61e31c3f825c4816ef6b1a8e5d964c734be547\", \
                \"0x236c3939ac1f3e385a92edf6539b42763c759e05716b3b46dd606cf01bc6524a\", \
                \"1\" \
            ], \
            \"protocol\":\"groth16\" \
        }",
    )
    .unwrap();
    let expected_seal: Seal = proof_json.try_into().unwrap();

    assert_eq!(seal, expected_seal);
}

struct ProveInputs {
    pcoeffs: Mmap,
    fres: Vec<u8>,
    srs: Mmap,
}

impl ProveInputs {
    fn new(root_dir: &Path) -> Result<Self> {
        let pcoeffs_file = std::fs::File::open(root_dir.join("preprocessed_coeffs.bin"))?;
        let srs_file = std::fs::File::open(root_dir.join("stark_verify_final.zkey"))?;
        Ok(Self {
            pcoeffs: unsafe { Mmap::map(&pcoeffs_file)? },
            fres: std::fs::read(root_dir.join("fuzzed_msm_results.bin"))?,
            srs: unsafe { Mmap::map(&srs_file)? },
        })
    }

    fn prove_params(&self) -> ProveParams<'_> {
        ProveParams {
            pcoeffs: &self.pcoeffs[..],
            fres: &self.fres[..],
            srs: &self.srs[..],
        }
    }
}

pub(crate) fn shrink_wrap(seal_bytes: &[u8]) -> Result<Seal> {
    tracing::info!("shrink_wrap: {} seal bytes", seal_bytes.len());

    let root_dir = Rzup::new()
        .context("failed to initialize rzup")?
        .get_version_dir(&Component::Risc0Groth16, &Version::new(0, 1, 0))
        .context(
            "Missing required `risc0-groth16` rzup component. \
            To install it, ensure that your `rzup` version is >= 0.5.0, \
            and then run `rzup install risc0-groth16`.",
        )?;
    let prove_inputs = ProveInputs::new(&root_dir).context("failed to open groth16 input files")?;

    let inputs = to_json(seal_bytes)?;

    let graph_path = root_dir.join("stark_verify_graph.bin");
    let witness =
        calc_witness(&graph_path, &inputs).context("failed to calculate groth16 witness")?;

    let proof = risc0_groth16_sys::prove(witness.as_bytes(), &prove_inputs.prove_params())
        .context("failed to run groth16 prove operation")?;

    Ok(proof.into())
}

struct CalcWitness {
    witness: Vec<wtns_file::FieldElement<32>>,
}

impl CalcWitness {
    fn as_bytes(&self) -> &[u8] {
        let r: &[wtns_file::FieldElement<32>] = &self.witness[..];
        unsafe { std::slice::from_raw_parts(r.as_ptr() as *const u8, std::mem::size_of_val(r)) }
    }
}

fn calc_witness(graph_path: &Path, inputs: &str) -> Result<CalcWitness> {
    let graph = std::fs::read(graph_path)?;
    let witness_encoded = circom_witnesscalc::calc_witness(inputs, &graph)
        .map_err(|err| anyhow!("witness failure: {err}"))?;
    let wtns_f = wtns_file::WtnsFile::read(Cursor::new(witness_encoded))?;
    Ok(CalcWitness {
        witness: wtns_f.witness.0,
    })
}
