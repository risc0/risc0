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

use jwt_core::Validator;
use risc0_zkvm::guest::env;

static PUBLIC_KEY: &str = r#"
    {
      "alg": "RS256",
      "e": "AQAB",
      "key_ops": [
        "verify"
      ],
      "kty": "RSA",
      "n": "zcQwXx3EevOSkfH0VSWqtfmWTL4c2oIzW6u83qKO1W7XjLgTqpryL5vNCaxbVTkpU-GZctit0n6kj570tfny_sy6pb2q9wlvFBmDVyD-nL5oNjP5s3qEfvy15Bl9vMGFf3zycqMaVg_7VRVwK5d8QzpnVC0AGT10QdHnyGCadfPJqazTuVRp1f3ecK7bg7596sgVb8d9Wpaz2XPykQPfphsEb40vcp1tPN95-eRCgA24PwfUaKYHQQFMEQY_atJWbffyJ91zsBRy8fEQdfuQVZIRVQgO7FTsmLmQAHxR1dl2jP8B6zonWmtqWoMHoZfa-kmTPB4wNHa8EaLvtQ1060qYFmQWWumfNFnG7HNq2gTHt1cN1HCwstRGIaU_ZHubM_FKH_gLfJPKNW0KWML9mQQzf4AVov0Yfvk89WxY8ilSRx6KodJuIKKqwVh_58PJPLmBqszEfkTjtyxPwP8X8xRXfSz-vTU6vESCk3O6TRknoJkC2BJZ_ONQ0U5dxLcx",
      "use": "sig",
      "kid": "6ab0e8e4bc121fc287e35d3e5e0efb8a"
    }
    "#;

fn main() {
    // read the token input
    let token: String = env::read();

    // create new validator instance from public key
    let validator = PUBLIC_KEY
        .parse::<Validator>()
        .expect("failed to create validator from key");

    // validate token
    let valid_token = validator
        .validate_token_integrity(token.as_str())
        .expect("token integrity check failed");

    env::commit(&valid_token.claims().custom.subject);
}
