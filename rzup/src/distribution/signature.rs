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

use crate::{Result, RzupError};

use std::{fmt, str};

#[derive(Debug, PartialEq, Eq)]
pub struct Signature(rsa::pss::Signature);

impl fmt::Display for Signature {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        use rsa::signature::SignatureEncoding as _;

        write!(f, "{}", hex::encode(self.0.to_bytes()))
    }
}

impl str::FromStr for Signature {
    type Err = String;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let signature = hex::decode(s).map_err(|e| format!("invalid RSA signature: {s:?}: {e}"))?;
        Ok(Self(
            rsa::pss::Signature::try_from(&signature[..])
                .map_err(|e| format!("invalid RSA signature: {s:?}: {e}"))?,
        ))
    }
}

#[test]
fn signature_encode_round_trip() {
    let mut rng = rand::thread_rng();
    let pk: PrivateKey = rsa::RsaPrivateKey::new(&mut rng, 2048).unwrap().into();
    let sig = pk.sign(&[1, 2, 3, 4]);

    let rt_sig: Signature = sig.to_string().parse().unwrap();
    assert_eq!(rt_sig, sig);
}

#[derive(Clone)]
#[cfg_attr(not(feature = "publish"), allow(dead_code))]
pub struct PrivateKey(rsa::pss::SigningKey<sha2::Sha256>);

impl PrivateKey {
    pub fn new(pem: &str) -> Result<Self> {
        use rsa::pkcs8::DecodePrivateKey as _;

        let private_key = rsa::RsaPrivateKey::from_pkcs8_pem(pem)
            .map_err(|e| RzupError::Other(format!("invalid private-key PEM: {e}")))?;
        Ok(private_key.into())
    }

    #[cfg(feature = "publish")]
    pub fn sign(&self, data: &[u8]) -> Signature {
        use rsa::signature::RandomizedSigner as _;

        let mut rng = rand::thread_rng();
        Signature(self.0.sign_with_rng(&mut rng, data))
    }

    #[cfg(test)]
    pub fn public_key(&self) -> PublicKey {
        use rsa::signature::Keypair as _;

        PublicKey(self.0.verifying_key())
    }
}

impl From<rsa::RsaPrivateKey> for PrivateKey {
    fn from(k: rsa::RsaPrivateKey) -> Self {
        Self(rsa::pss::SigningKey::new(k))
    }
}

pub struct PublicKey(rsa::pss::VerifyingKey<sha2::Sha256>);

impl PublicKey {
    pub fn official() -> Self {
        use rsa::pkcs8::DecodePublicKey as _;

        let pub_key =
            rsa::RsaPublicKey::from_public_key_pem(include_str!("public_key.pem")).unwrap();
        Self(rsa::pss::VerifyingKey::new(pub_key))
    }

    pub fn verify(&self, data: &[u8], signature: &Signature) -> Result<()> {
        use rsa::signature::Verifier as _;

        self.0
            .verify(data, &signature.0)
            .map_err(|e| RzupError::InvalidSignature(e.to_string()))
    }
}
