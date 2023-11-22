// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

pub const RECURSION_CONTROL_IDS: [&str; 15] = [
    "3a8de34cd9c65059ff59a5311e038556d63345070749052e6110576d5e36c83c",
    "1987251f3589eb2eaac24f23dd35345c28e388752b49760a3dc80574f822891c",
    "26fdac1de5970b2b05d4b320a550fc47c942a960db500877bbe96c187a965a74",
    "6491e73707b9dc76e7b00224d5fd472058c7ce3a06dc7064ec63ab6e20e2e851",
    "bf7f2031bed5337296093a54e7f3d636811c50187c00c51d9a386f3ba2600f0d",
    "9058842f3d182a4f0c5837089302116f2d757902ae0d7414ee3ea7284f27ad34",
    "2b3aa1752bfb62157005d95c7650394f0978236b118c4338bc833557c52f7624",
    "162fbe4c178a3633b49beb6f16ee6e709d2be7682998526dc17273359e674745",
    "6af58c4e7f2ebd61d5e8560ad154ec4b7c762428d9c8ad74facfc1471d863515",
    "63645f59076d4124742d5b5a8c325d6c45dbd166a881cf6996f4d5316f2e5071",
    "e569af067d234020b6d0d715d1bc0c5b82b54264255b272241a616573184fb47",
    "a69d8761f3ab76093195571860f0262635e8253bc2324771d6768266277e5d36",
    "b7068836a9f6ba4af9f9390cfdc5d24d14331a4a4feadb16f0ab332c1f667465",
    "7ee9de703123af4b6854de0e7afe5a29e17e365e6193a2075459745991209a28",
    "93ddfd13ad326c73317033379bda035dd1e97a056aaed01c5beca909d764d213",
];

/// Merkle root of the RECURSION_CONTROL_IDS
pub const ALLOWED_IDS_ROOT: &str =
    "48062923d32b9b6f53983e29fb83b63d07da85088fe62d4c06b13336e6dfa63e";
