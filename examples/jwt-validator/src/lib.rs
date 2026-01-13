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

use jwt_methods::VALIDATOR_ELF;
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover};

use jwt_core::{CustomClaims, Issuer};

static SECRET_KEY: &str = r#"
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

pub fn prove_token_validation(claims: &CustomClaims) -> (Receipt, String) {
    let iss = SECRET_KEY
        .parse::<Issuer>()
        .expect("failed to create issuer from secret key");

    let token = iss.generate_token(claims).expect("failed to create claims");

    let env = ExecutorEnv::builder()
        .write(&token.as_str())
        .expect("failed to write JWT to env")
        .build()
        .expect("failed to build env");

    let prover = default_prover();

    let receipt = prover
        .prove(env, VALIDATOR_ELF)
        .expect("failed to prove")
        .receipt;

    let output: String = receipt
        .journal
        .decode()
        .expect("Journal should decode to string.");

    (receipt, output)
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    #[gpu_guard::gpu_guard(skip_if_dev_mode = true)]
    fn test_token_validation() {
        let claims = CustomClaims {
            subject: "Hello, world!".to_string(),
        };

        let (_, output) = prove_token_validation(&claims);

        assert_eq!(
            output, claims.subject,
            "we expect the VM to decode and output the claim subject"
        );
    }
}
