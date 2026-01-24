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

use jwt_compact::{
    AlgorithmExt, Claims, CreationError, Header, ParseError, Token, UntrustedToken,
    ValidationError,
    alg::{Rsa, RsaPrivateKey, RsaPublicKey},
    jwk::{JsonWebKey, JwkError},
};
use serde::{Deserialize, Serialize};
use std::str::FromStr;
use thiserror::Error;

#[derive(Error, Debug)]
pub enum Err {
    #[error("Failed to generate token: {0}")]
    TokenGenerationError(#[from] CreationError),

    #[error("Failed to validate token: {0}")]
    TokenValidationError(#[from] ValidationError),

    #[error("Failed to parse token: {0}")]
    TokenParseError(#[from] ParseError),

    #[error("Failed to parse jwk: {0}")]
    JwkParseError(#[from] JwkError),

    #[error("Failed to parse key string: {0}")]
    KeyParseError(#[from] serde_json::Error),
}

#[derive(Deserialize, Serialize)]
pub struct CustomClaims {
    pub subject: String,
}

pub struct Issuer {
    alg: Rsa,
    s_k: RsaPrivateKey,
    pub p_k: RsaPublicKey,
}

impl Issuer {
    pub fn generate_token(&self, claims: &CustomClaims) -> Result<String, Err> {
        let header = Header::empty();
        let claims = Claims::new(claims);

        self.alg
            .token(&header, &claims, &self.s_k)
            .map_err(Err::TokenGenerationError)
    }
}

impl FromStr for Issuer {
    type Err = Err;
    fn from_str(jwk_str: &str) -> Result<Self, Self::Err> {
        let jwk = serde_json::from_str::<JsonWebKey>(jwk_str)?;
        let alg = Rsa::rs256();
        let s_k = RsaPrivateKey::try_from(&jwk)?;
        let p_k = RsaPublicKey::try_from(&jwk)?;
        Ok(Self { alg, s_k, p_k })
    }
}

pub struct Validator {
    alg: Rsa,
    pub p_k: RsaPublicKey,
}

impl Validator {
    pub fn validate_token_integrity(&self, token: &str) -> Result<Token<CustomClaims>, Err> {
        let token: UntrustedToken = UntrustedToken::new(token).map_err(Err::TokenParseError)?;

        self.alg
            .validator(&self.p_k)
            .validate(&token)
            .map_err(Err::TokenValidationError)
    }
}

impl FromStr for Validator {
    type Err = Err;
    fn from_str(jwk_str: &str) -> Result<Self, Self::Err> {
        let jwk = serde_json::from_str::<JsonWebKey>(jwk_str)?;
        let alg = Rsa::rs256();
        let p_k = RsaPublicKey::try_from(&jwk)?;
        Ok(Self { alg, p_k })
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    const SECRET_KEY: &str = r#"
    {
      "alg": "RS256",
      "d": "YuO1XZkYSwDRgauXQe6q1u8fET3S7x7g4N8uE49rdt7g3-O9q-Hwn_nQNiRr9o7Uslf7X8sL6txraQy7TdPUuSkaULpRNo2FoVLLoO2eACWwPtCG4n9wuvjnz7qCh9s3tfgOKxMA_riKkS8O7BxPH54rd7Ry1i6HN3TSYKYwxZxG4HFLhcewX6Q1KdGXdP7xVAsZ5lEpCQbhY5IKUzBZ5WIZpSTk10AadkVuwS622QT-9efk6PBWDyM48_udMdDo1HEcHsAdxrUMRdw_5uzVajQzZhNAmALXHCPT79P0qahzdYlUSHauT1XxU7z-KoCYVqt3z6epgYDcKmLzGkqIkSXUHxcVN-MTSGNET_dhio0tHG-jV3wB5jfsgayoIZCeTPF-F-nDwn8Cyz18uee_Y7U53NTtEXGqB9npZyu7SibTztwSeLs6zH965d1VTmUCxH8CWqizugfQY8ibNgVCd42naAuWbOmxYEjyelmHf_BS0Vb7NwpW9cuaODOjpjCz",
      "dp": "DOIAbWzet_-ZSED61WWvG9Byao9uQh3SSvtvAUa4WhWEq3lfGqt1wEDneOds1IrxNF7Y2rV_iHBVA2DWB9ctdMxau3DteGumbMzEObQIjDs7SP45plImxHzZbXgTIB-DWiujJmwDNJUIaB80q1sjeeBTJ9rfaU0ZNMFO26koOKQGoNDuuJTgejnRwGdIGhoOLcT_dus-7CNWY1pRBvTGhcEOygRE_icb8JzNoKo90fwZf0ACdxiFc6G_RUCXapap",
      "dq": "0yFAtOVm0-fPLg62RcALyhIXsyEOd25W0YFmWIzb6Bh5kbMruA-befX-ANnNGcktBGgY7QGN6myb-K8zRCOYfVt5zs0EFEFCHc6NO8UoSJCItOZFMdaLsG21MqOdtQRQi4F_TJ2yoqu1S81O-Y08wtFE0F8hVe7sGuJIoRtY5yF_Swwaw3ST-XMfghpbhvc71zVF7VyPlyrqU-NeKimBpuEfHuTKQSSudY9eLNdypyE71RC6q_xWxWzTSqu3pih5",
      "e": "AQAB",
      "key_ops": [
        "sign"
      ],
      "kty": "RSA",
      "n": "zcQwXx3EevOSkfH0VSWqtfmWTL4c2oIzW6u83qKO1W7XjLgTqpryL5vNCaxbVTkpU-GZctit0n6kj570tfny_sy6pb2q9wlvFBmDVyD-nL5oNjP5s3qEfvy15Bl9vMGFf3zycqMaVg_7VRVwK5d8QzpnVC0AGT10QdHnyGCadfPJqazTuVRp1f3ecK7bg7596sgVb8d9Wpaz2XPykQPfphsEb40vcp1tPN95-eRCgA24PwfUaKYHQQFMEQY_atJWbffyJ91zsBRy8fEQdfuQVZIRVQgO7FTsmLmQAHxR1dl2jP8B6zonWmtqWoMHoZfa-kmTPB4wNHa8EaLvtQ1060qYFmQWWumfNFnG7HNq2gTHt1cN1HCwstRGIaU_ZHubM_FKH_gLfJPKNW0KWML9mQQzf4AVov0Yfvk89WxY8ilSRx6KodJuIKKqwVh_58PJPLmBqszEfkTjtyxPwP8X8xRXfSz-vTU6vESCk3O6TRknoJkC2BJZ_ONQ0U5dxLcx",
      "p": "-TQVt9yl_0S0uvUM37L3WSDPkOn_gy34zpAEllhgx1HQUg_pVbqEDwKzEIpBlZfbrcszMlmiJhKL6q4y0_a6e3O5QnfB1vrGTjhLcfcaUK6o-I7bxabrpZmvLIsTqSdAgUijXe8yhQFIoCjc1MPD7icRPc-V7P9IYE2ls9X6sgo4lUZjQAuQtOo8ndlZ3uqP2sMKRR3CS7tHiF1r_zq_NXcf98Sve-1rRnqT6GpGcJRcvVFu2wy8TyCPMAvWh903",
      "q": "02DUlUJrcTQ-mHMmg-V5qjxrtTKMmjqXpN0pgkXhM8_DWCrqKL9sXb1MKXQcbAZYr-lWmtBwzXeF4Qn66dRHpjlQLhSA947UxjuEtbhWx3wKGG460ZH026qcRr3QspcKZuiX2zISHb8suMl2lhDDSggCAjybs0l72pNHPIny9pucnwqc9ihrbeu68LlUpnQtS-Okt4j5ndVc1l1Vwv2PFt2PxrLmQkqdwRMla1F7r0vtgM7NIZz9XPszSrkxTILX",
      "qi": "3yweZ6b2adwqUrCvyvK5ub5XAjKOh1N7AoFqYQFpD_ho41ThyWErfjTztDlgqqTHo3wHyR49cq-L6aAuerNTPW7VAXTobC8vZSxIKazOU9p0xcDYSaGGH_IES62MAxJu1rdyAOrq_MLsqvBckVancmW6lVWQr27wDNTNwskkPpgDXwAygWSCBbM-oZOsWamge0SadQJOCd7Rr33aLfWFKaajl7FnQzX6Wh8Q0gLn2PRDnC7V1gEVWY3fWSzs4obj",
      "use": "sig",
      "kid": "6ab0e8e4bc121fc287e35d3e5e0efb8a"
    }
    "#;

    const PUBLIC_KEY: &str = r#"
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

    #[test]
    fn it_works() {
        let claims = CustomClaims {
            subject: "Hello, world!".to_string(),
        };

        let iss = SECRET_KEY.parse::<Issuer>().unwrap();
        let token = iss.generate_token(&claims).unwrap();

        let validator = PUBLIC_KEY.parse::<Validator>().unwrap();
        let valid_token = validator.validate_token_integrity(&token).unwrap();

        assert_eq!(valid_token.claims().custom.subject, "Hello, world!");
    }

    #[test]
    fn it_fails_on_altered_token() {
        let claims = CustomClaims {
            subject: "Test Subject".to_string(),
        };

        let iss = SECRET_KEY.parse::<Issuer>().unwrap();
        let mut token = iss.generate_token(&claims).unwrap();

        // Break the token integrity
        token.replace_range(0..10, "INVALIDSTR");

        let validator = PUBLIC_KEY.parse::<Validator>().unwrap();

        let result = validator.validate_token_integrity(&token);
        assert!(
            result.is_err(),
            "Token validation should fail, but it passed."
        );
    }
}
