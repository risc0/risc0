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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 12;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("3626772ee728c274a0a1eb7099eafc598ebd501ccd5e640f6ea9401a95cb6747"), // recursion lift_rv32im_m3_20.zkr
    digest!("01f98f5948c1e047fb73095310b2874413daf80e3e07021e0ed7916584fb2274"), // recursion lift_rv32im_m3_12.zkr
    digest!("db17d63f73664911b42e234943fccc478b7cb971537c9004716c151d5449bc37"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("a31e694579d5ae0e2407a62d7b4e1027e6b58d4a3e849d4fe000f03070881629"), // recursion lift_rv32im_m3_17.zkr
    digest!("8f946a452bbd96163df82c77ffb6463a4d6ac1067ca45c1d3e218e75f32c6a31"), // recursion lift_rv32im_m3_21.zkr
    digest!("ab15245db7753d0fce5fac4aec3b3d1ddcf4204daaa2aa6091cb5a358b7a111a"), // recursion lift_rv32im_m3_16.zkr
    digest!("8db2981f14abda2d622d12080c32772fec353f49f0a3ed123bd48a7577b71315"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("e77b1828ce323b22b06f662cb840ba47f07ad4439c80e56dde7c7d3bafa74c51"), // recursion lift_rv32im_m3_22.zkr
    digest!("e357ba11e57edf4126457f5657a9d366e0a9e044f10e2960b573a013f70f5968"), // recursion lift_rv32im_m3_14.zkr
    digest!("be13fc46d1d28b402a20e267b4d0990afd07df408fee8273fe8a4b42be9f1e1d"), // recursion lift_rv32im_m3_13.zkr
    digest!("86bfd427c451f12ba10d8f696ce67176c6cc03145c44082dc90c5c2cd14be61a"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("5954030478436f478dad2056dcd51e2fd48f6253ec26cf53c589851c5355b048"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("5c137c5816b275054ce575228b1994300680a17779554e2fc88a5b367595234a"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("d51eed66e0c74516cdc4f8475f04fe54cad33c64f833ca31541b8e3278c9ca1b"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("55c5191eb3f1240ed4d4f14a520d1d724d1f972262c26b318a91066ad5a7573b"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("0427065cf67c704619713a38a9325471a30c34442924e863dc93916162f50110"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("58e442235864806334589758f2767d5cbecedd45f38c431213aa985793117f09"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("bc892058f310710ed260327784a61f09a164a172b3dbfc57a30afc19e6ccd619"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("39e8534366e849204e99ef6373ef0124d979133691631813b2a9ec44201fc603"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("5684860ccff2eb1c1911523b39637732f59b394c4f461a3183a5af2bed546622"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("eeee8e16fcaaa827d345240e5a7ea51173872f5def3d0d3e5e23ed5d3f717b09"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("43e0f871e75e1a10c2ae0f6ba2bfc84ffc84425eabd57068f594fc5d14e15408"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("e88b234e68ff3b1fc8a99d0100fb19721060436d27db0a66de907b74deb47727");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("3626772ee728c274a0a1eb7099eafc598ebd501ccd5e640f6ea9401a95cb6747"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("01f98f5948c1e047fb73095310b2874413daf80e3e07021e0ed7916584fb2274"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("db17d63f73664911b42e234943fccc478b7cb971537c9004716c151d5449bc37"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("a31e694579d5ae0e2407a62d7b4e1027e6b58d4a3e849d4fe000f03070881629"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("8f946a452bbd96163df82c77ffb6463a4d6ac1067ca45c1d3e218e75f32c6a31"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("3934745dad26e35f7ced39329646b6061074b3388095403738cfc51d9d0ee148"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("ab15245db7753d0fce5fac4aec3b3d1ddcf4204daaa2aa6091cb5a358b7a111a"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("8db2981f14abda2d622d12080c32772fec353f49f0a3ed123bd48a7577b71315"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
    (
        "identity.zkr",
        digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("e77b1828ce323b22b06f662cb840ba47f07ad4439c80e56dde7c7d3bafa74c51"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("e357ba11e57edf4126457f5657a9d366e0a9e044f10e2960b573a013f70f5968"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("be13fc46d1d28b402a20e267b4d0990afd07df408fee8273fe8a4b42be9f1e1d"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("2258ba24d41a721183eabd760c9814242c9fcb48b54e6a5a592bd26edcb69049"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("86bfd427c451f12ba10d8f696ce67176c6cc03145c44082dc90c5c2cd14be61a"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("5954030478436f478dad2056dcd51e2fd48f6253ec26cf53c589851c5355b048"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("5c137c5816b275054ce575228b1994300680a17779554e2fc88a5b367595234a"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("d51eed66e0c74516cdc4f8475f04fe54cad33c64f833ca31541b8e3278c9ca1b"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("55c5191eb3f1240ed4d4f14a520d1d724d1f972262c26b318a91066ad5a7573b"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("0427065cf67c704619713a38a9325471a30c34442924e863dc93916162f50110"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("488838719a75fb0884eeeb0100d41d147e333f4b484f864f18d7a635da5ee33a"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("58e442235864806334589758f2767d5cbecedd45f38c431213aa985793117f09"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("bf12ac1790ad105eb714495244fdc576c860d763770a9f765ce9b14d9ad3dc2b"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("bc892058f310710ed260327784a61f09a164a172b3dbfc57a30afc19e6ccd619"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("39e8534366e849204e99ef6373ef0124d979133691631813b2a9ec44201fc603"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("5684860ccff2eb1c1911523b39637732f59b394c4f461a3183a5af2bed546622"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("eeee8e16fcaaa827d345240e5a7ea51173872f5def3d0d3e5e23ed5d3f717b09"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("43e0f871e75e1a10c2ae0f6ba2bfc84ffc84425eabd57068f594fc5d14e15408"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("31842dbb94a1c4974888a096605239b12d9f38aa8954adfb5fb87aa4fcfcf6bc"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("c98982e4583ad49dd20203f8a01f9e80321d4a3655486e11ca1a00bbde20173b"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("5e38843d24e08d8cd832ceef4adc464bcb8b53cbf1bbdc29d5f4ac2392f31091"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("d8a9bcef317c3a17a421405f54883ca2c8906e3211c9f6320c57df4cb07b0314"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("a1333977d116421b3bbc6b0ee7d463a21936869dc80d0f0bcb820d974c928d8a"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("040dda73ce66d40b94f6c074181e20f882e446800a0f3024ba0066ac49229503"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("1d81085548f107c5ffa111c2b9405719bd5d150545977395b337ea3d7f905049"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("5c926e91a3e6048235d5ba38339e87fab24e87756dc9007e528766037f9a3261"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
    (
        "identity.zkr",
        digest!("d7ecd18c7d06fc468166147cf20869aa10f32e097a0c166146a5a62dd2d975ea"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("e646c357d915e397b3972580efcb5a605964b496d6c249d615fa4655fdea68bb"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("994e773bfc379112f00d52c695fa996be7e8642fe82938ac0efeac5b03aa9681"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("8dd1997448cb557af39cb1f8bc8fbe43471eaf4adcafdebf65e4e62c5c243256"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("c5e5a0732327f376b4cc9327d79eb2524fc2cca1ab8f2fffe11ef25fc9071aba"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("a4613d57ba23fd6126aab8c01a6e082f078801172a42d012f070708ed074f63b"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("f6b505550f0c558b52ba7d02d3a6c2d707c13c4c264aaf0a2036a99355e6ea59"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("a23ca4df0a087817e4a25077907ec70e4a6987044aaabd64f3b5e213543ead68"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("384a3546c9cd294e1c584601dd7fbae0b5e27319ab7fc0e965f0ade0e07ec816"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("62d502a6dda6d840c2d5239233988fdda31a46cd92f00de2fbe09fcbd4c83acc"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("eea71e67e99c53693084b7a6bb2cbba91ad164344f313280b8329d470dd558b3"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("52a4430cce51c2c9e85014353ce9e4c0b104747c6af64fdecd59bfa74294c3d4"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("f45afe021447a27032534713eb98fa36fd1c8fb249979d3ac251ac2291be4b97"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("bd3cbe7d699b1ea41e74ff0e258d7e49d7332149cc804b3e370876b15de14e38"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("d8245ae7aa72bdb73271f8a5791ac5ba26426cc5f1b9e49a1c6685399784df33"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("222d2e7eeeaac7365abc7ddb108ae7a0b40659e19e96e50f5ffb53ad4dfb081e"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("13b763cb3ea22260e6cd382fc45b5827832d25d5860d49de9d152e4906d9e011"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("1c5cd955597ec358eb35bde88a73d0e4c45928fe0f8f093c240a66bd9d557a24"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("2306d6aa60b4dd5d5cc4649d751c3dcd673e9ddeaa51dadd6f5ee08a54187405"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
