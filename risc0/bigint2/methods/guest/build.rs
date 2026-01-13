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

use std::{fmt::Write as _, path::Path};

use k256::ecdsa::{Signature, SigningKey, VerifyingKey, signature::Signer as _};

const NUM_SIGNATURES: usize = 7;
const SIGNING_KEY: [u8; 32] = [
    191, 95, 105, 40, 155, 50, 183, 58, 61, 48, 1, 231, 44, 100, 10, 170, 64, 121, 99, 101, 208,
    121, 205, 143, 242, 81, 225, 52, 158, 95, 99, 36,
];

fn byte_slice_fmt(b: &[u8]) -> String {
    format!(
        "[{}]",
        b.iter()
            .map(|b| format!("0x{b:x}"))
            .collect::<Vec<_>>()
            .join(", ")
    )
}

fn main() {
    let mut output = String::new();

    write!(&mut output, "const VERIFYING_KEY: [u8; 33] = ").unwrap();
    let signing_key = SigningKey::from_bytes((&SIGNING_KEY).into()).unwrap();
    let verifying_key = VerifyingKey::from(&signing_key);
    writeln!(
        &mut output,
        "{};",
        byte_slice_fmt(&verifying_key.to_sec1_bytes()[..])
    )
    .unwrap();

    writeln!(&mut output).unwrap();
    writeln!(
        &mut output,
        "const SIGNATURES: [[u8; 64]; {NUM_SIGNATURES}] = ["
    )
    .unwrap();

    for i in 0..NUM_SIGNATURES {
        let payload = i.to_le_bytes();
        let signature: Signature = signing_key.sign(&payload[..]);
        writeln!(
            &mut output,
            "{},",
            byte_slice_fmt(&signature.to_bytes()[..])
        )
        .unwrap();
    }
    write!(&mut output, "];").unwrap();

    writeln!(&mut output).unwrap();
    writeln!(
        &mut output,
        "const PAYLOADS: [[u8; 8]; {NUM_SIGNATURES}] = ["
    )
    .unwrap();

    for i in 0..NUM_SIGNATURES {
        let payload = i.to_le_bytes();
        writeln!(&mut output, "{},", byte_slice_fmt(&payload[..])).unwrap();
    }
    write!(&mut output, "];").unwrap();

    let out_dir = std::env::var_os("OUT_DIR").unwrap();
    std::fs::write(Path::new(&out_dir).join("ecdsa_signatures.rs"), &output).unwrap();
}
