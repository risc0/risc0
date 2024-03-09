// Copyright 2024 RISC Zero, Inc.
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

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2;

pub type RawControlId = [&'static str; CONTROL_ID_ENTRIES];

/// Control ID for SHA-256
pub const SHA256_CONTROL_ID: RawControlId = [
    "eab745d650de7f5f837a3fe5f1cb23b4bef2d190b7a470453f92dbdf7083c7a0", //
    "09b42cb611dcaeae5606d6309b1b1aeb8482163cacc3225573c915eb5c28abcc", //
    "dc9424cbe65a98cd160f1450c17ce9a3419b50aea1967f7fedb65e3f3a1db38e", //
    "b687aa43eb3adae3661312ac42eecd123d05dc63c260c586271fc36f48c7588c", //
    "52d851bfbb1ab05e69e9205403d7909d80025fb51c943badd5efc16b2e325da1", //
    "6542f024bfbf6699511baae55c2c9bc85befda6188f54ccdc8d8dc1825567d75", //
    "901332de51232ff2e3c55ba64b217dd82728ec28a6fa087f02ef6f7d409f7d1a", //
    "831fd974bcd951dc3d0d0e802235788d4089b90a9d2578d72b67e0a80ce8715a", //
    "802ce6a9c33242f0ff0dc5e6f63def4dea194c2016137387ef36d1c8d145e462", //
    "ad1eda57cea9446c14c6d93859de058ca8d624e270f1f38aab7336db8aa4ea30", //
    "97be9ed7e5f1f24c3e527c07ded11418900b128725480e179156b5dd6b032cae", //
];

/// Control ID for Poseidon2
pub const POSEIDON2_CONTROL_ID: RawControlId = [
    "bebb4c5f19d4973b590313766e476d3d7cce5c18b2d600188d7476767a4a8614", //
    "0296f8241298c95f780501761519030966b9902bc508b539881b0c49bf326b6e", //
    "b3b5d8727f259c31dfa971583c8db640a4a78b5b791fd76c15e90d2c5a85e45b", //
    "3376da16801abe4c46bf9c508d67c559a6ba4a46e0f8c602bfd9a337c9b0f40b", //
    "61c4fc0b6df2a935904374720c967b081deb844653f81956b71c4e1e863e6e3e", //
    "1f2a072b0e7ae7113aa1193120e2543daf39ad727c2128539c84072ae150c960", //
    "0c31d02a1900786d81bdae23ce96ce474c8b0b7182a91457aeac5a25b79f5c65", //
    "1ef23b55919a8313dfb56057c4174431839660377a3e22738e279c02901ad345", //
    "d695e66e4db81a4b6e8d535a5ba1370757291d1ef7fe1973db9cb83716565637", //
    "9ef20b736835d16fb922710871488552582aee312f0925599d3fee12934b3465", //
    "da824e2ecc179c2c1359bb75b154f8490086cd0f85e3391cc96ffc3b8e3afa11", //
];

/// Control ID for Blake2b
pub const BLAKE2B_CONTROL_ID: RawControlId = [
    "f68c89b078e1a360c7b3d4b9c7de5d47e3f46ce92e8ddf65b8c6ca32befb45fe", //
    "5be8f08be4f88aef8928da60b240832aa73c8e22be2cc06271a5b53b07636a2a", //
    "3a8089e20f6f7cd55d09c861b32fedc4ccd34283ea597a5c98b5de19efc3cca5", //
    "ee2a276a311656871b094b96844424683b1cf5a83e8e6be6cc10b8821ea7d9c5", //
    "59d2053991478d0819e6aaa071b6d9d325093a253798b247c6746c9fc5a57594", //
    "62a99496914f245543f96b6cee785794ce330864eb315639be6253df3ed9a80b", //
    "3e8fc320dc63e512258f638a028b494c6dd767d813d43e1ae270120f63e9dec8", //
    "f6df38c8532e9bb75e0eb5f9413c7feecac464ae43bd117c43e86fb932bed983", //
    "1b368a75de706ab0c103103c65915e21e01079eea654d65180e3a0d6260c2036", //
    "4a507faef43cd9d7bbf7561c7971c12ef0d1429ff73919cfea9479424a476bc6", //
    "3d8fad6ffcd1b9bd31ea4730021df8f882c9afac6a55cda04f419171cf8a848e", //
];
