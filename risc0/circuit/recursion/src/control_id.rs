// Copyright 2025 RISC Zero, Inc.
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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 14;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("0876966863d879322be4a526df9aab59f4c9ed35cf76be5cf762712936736e32"), // recursion lift_rv32im_v2_14.zkr
    digest!("181d2a5befaefb37428d86306663164e428532416c42e7730b1e3e6c02298e11"), // recursion lift_rv32im_v2_15.zkr
    digest!("a0d45d2c075f502ada6fd23bbdadc645dedb6839abc04259475ea805fef4d83d"), // recursion lift_rv32im_v2_16.zkr
    digest!("82445f4afd5949261a8b9d5ed01ac20be56f5e0a9f87bc75ef5ac438e160e740"), // recursion lift_rv32im_v2_17.zkr
    digest!("8eb61603a710c032909de21ddab4ea230376af72c2b96077e572521e96632170"), // recursion lift_rv32im_v2_18.zkr
    digest!("641ae36a86e3313577d808616754a81129ade72c78a5c66a510bbb75be3a3900"), // recursion lift_rv32im_v2_19.zkr
    digest!("28640f5bacc13e5e8d6ddd2ac54c3453fa85133004bd9b1dfa72e40e28fb416d"), // recursion lift_rv32im_v2_20.zkr
    digest!("d1587427e916422bb86508640a234e39ef1efe70f350a5620551356c7b4cac6f"), // recursion lift_rv32im_v2_21.zkr
    digest!("8c05541367b3b33d4a9f6261ee709861f3fd73074bdf3a5c8cf9552ec8fbb32e"), // recursion lift_rv32im_v2_22.zkr
    digest!("a0b388636cb71051ffcf6853b57a575a320a466bf3156e56a8d6ce1eaf471268"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("7906ed1c0f5bc7774dcd181e5d88a96a74ba9f3b09db4565ee06e01cf1e17836"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("e05e774f4e226a379322c404b9f7f10e9b169e5885fbd10710615d5aa393b221"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("77111d409f710158c4f43573a266555713e5e701ed4a1447c82bda3134cb6e0f"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("c61d3d4b06dddb2ecb9db04041013716527322479a519c2633953b5404532875"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("85a95127201be06ce77ff427f3b331368235b56b6d82a648dea13e1d503e701f"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("dd01d5324b23f164be5c8358fd59d45ec4154b4c7cba9a2ccfe7a71742f0c343"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("3a4b391048d4a92c8a9fe52a2e8e0b4afd9fae45986f7b2776f530242dabb331"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("0efdc151dcd7173373756c56235590134ea5e31a6f00740124abb46212779a46"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("e99ea75d1ada9944e96c080d31ab9b2fc3744361e1b5fd0c27848a773d53ea08");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 32] = [
    (
        "identity.zkr",
        digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("0876966863d879322be4a526df9aab59f4c9ed35cf76be5cf762712936736e32"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("181d2a5befaefb37428d86306663164e428532416c42e7730b1e3e6c02298e11"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("a0d45d2c075f502ada6fd23bbdadc645dedb6839abc04259475ea805fef4d83d"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("82445f4afd5949261a8b9d5ed01ac20be56f5e0a9f87bc75ef5ac438e160e740"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("8eb61603a710c032909de21ddab4ea230376af72c2b96077e572521e96632170"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("641ae36a86e3313577d808616754a81129ade72c78a5c66a510bbb75be3a3900"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("28640f5bacc13e5e8d6ddd2ac54c3453fa85133004bd9b1dfa72e40e28fb416d"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("d1587427e916422bb86508640a234e39ef1efe70f350a5620551356c7b4cac6f"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("8c05541367b3b33d4a9f6261ee709861f3fd73074bdf3a5c8cf9552ec8fbb32e"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("42e8ba5abc1c4b75e8b25263a855aa646bb71458033ecc20f9c5cc1a6767d949"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("35968e41952cab513ec5b070de6c892bcae6052c27dff009c2b8545eb6d9f120"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("a0b388636cb71051ffcf6853b57a575a320a466bf3156e56a8d6ce1eaf471268"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("7906ed1c0f5bc7774dcd181e5d88a96a74ba9f3b09db4565ee06e01cf1e17836"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("e05e774f4e226a379322c404b9f7f10e9b169e5885fbd10710615d5aa393b221"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("77111d409f710158c4f43573a266555713e5e701ed4a1447c82bda3134cb6e0f"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("c61d3d4b06dddb2ecb9db04041013716527322479a519c2633953b5404532875"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("85a95127201be06ce77ff427f3b331368235b56b6d82a648dea13e1d503e701f"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("dd01d5324b23f164be5c8358fd59d45ec4154b4c7cba9a2ccfe7a71742f0c343"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("3a4b391048d4a92c8a9fe52a2e8e0b4afd9fae45986f7b2776f530242dabb331"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("0efdc151dcd7173373756c56235590134ea5e31a6f00740124abb46212779a46"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("0a0bdd51cc75d91a7989fe730d2fcd55e98a3769ffbcb74d2991440317b6956b"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("613ae737db516e163b5d8d607101932029e1ba23cc6cbf5d050b9053216da30d"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 32] = [
    (
        "identity.zkr",
        digest!("d7ecd18c7d06fc468166147cf20869aa10f32e097a0c166146a5a62dd2d975ea"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("172c640c4d953fb9435addd4558af26edc76a6c6dab2f1d101151b07ddbacc13"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("721997b264a1771bae57ac7231407326cb631f0bcafed8498ade4863864c081a"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("32b6e90548560e00bd39bf681cbf0662b3c7c87fd0ae5f00b28d777ace2f73d7"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("51d66d13e9e7b77ea2b0d0406af1762d7e68a252814999614e8b7c08b0d20178"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("1a8dca1040de20c8bed4fc847511cbccd5433d15c40026c2a75996a72d347cd9"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("34227d1dfd347ff529cc6b536c4faa28db8e010a957ba98a1fc0c8b20c7816b7"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("061222e9aaaeeb9b0d60401242528ef2fd4490dd8e749e53b3f7c22fbad3e478"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("9e7196006ff067949ed7ef561014a3398fbc641cf52707f171e942849cfd04b9"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("4639fec1b9a3c53f63f9dc01b632385908e81f6003e999094def697ff2ce8eb1"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("1860cf4e9188be1d56bb222f0cf07eaf204cbd983fbd20e2f18d31a4020ea806"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("b9931a05b040f6453e9d9fc03edb489d6f43a4552b33b9f78ff11a304ba33740"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("64388c720c3c2698b574f77bc7ca1411b9145220c9e21ca4ae19abe7c9343fd1"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("2fb49484844370764857ed2dc6aa875d3a95742145a8916fc59e3cde5b8ba18d"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("2981d687307af10cbd0d5e4e0dca4551a290fcc9cfe006fe1be79c122df23120"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("e0e0b04a2c668f48c600431df5c7738e07a6e483a2330b9eef6482ad2442dfa5"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("57fb991de9d6569586444c194698d91925162578439630f8ac5d972be1ce77f7"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("45be86c55b2d5f7765659b6aeff99facad9bcb06a7779a2cb6e1976c256d0a7e"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("2559ae6954cad6d088cb705de614a0842d4875701c6add801a4f17277df4559c"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("5524bce2d00ba25764299e722c7c317f7178c2ab1f0c7355af15874a2781c114"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("cdeae4ea398384c3a7aa79744e8f784ea6d6f4b88b8bd2aa1f41989799a16125"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("8e6963120866e7ec21ed9d96bf3902e0b781a756cfa13820b82e0ac7fe23c0e5"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("d7c51827d05d22fe6ab03701dbe991469551db52739bee53c6fb92ebeaf1c4f5"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
];
