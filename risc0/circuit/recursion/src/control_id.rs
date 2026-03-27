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
    digest!("8929963bf715f43394bc621061318b281a1efd0de0cc8807aae36a483c513123"), // recursion lift_rv32im_m3_20.zkr
    digest!("b2739446114e741e683d793a9ff5901a7b0bb852fd8ea01592e15c57e89c0a2e"), // recursion lift_rv32im_m3_12.zkr
    digest!("e47473707502945ffa65ba153e475d2a1791cb1c3d828a220ddc3e6e10e4b66d"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("1a3bbc0c5d697b3f37a87e012d19ea2e09da942166e578197daa20141a9e6d73"), // recursion lift_rv32im_m3_17.zkr
    digest!("0bbdf8114f060314563d6339778f8204ec964f3fa5db4734c9f287187e15df33"), // recursion lift_rv32im_m3_21.zkr
    digest!("795f9b30c0d7c94e2374b51147a2e9047c0d013a557b7b222d81b40d1089ee49"), // recursion lift_rv32im_m3_16.zkr
    digest!("d813836d7682750278f8c105d7f16067b0ce7d05a0c5b96ef71dc74a87530710"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("9358401b5fe85022b5979201039d6110f04fda122dc85422fb31af14434d013c"), // recursion lift_rv32im_m3_22.zkr
    digest!("dd87840cad6c8273ec133e066cae6011344ad928fa0dff66a44a9631f840115f"), // recursion lift_rv32im_m3_14.zkr
    digest!("85cce34af124324c4d198906d16a671e7484d44c8b9beb53f6400e177f7d4562"), // recursion lift_rv32im_m3_13.zkr
    digest!("c5b758004746761370f0e1029fd0556ccdd7c0086cf278646fd0ef2de14bfd08"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("67d0955e75f92e2d5658b01241ab76678e75ba1e6cb74431f6fb0d64d5485770"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("19cb7829879c1f4bacccc661b394a076a9d7da3371aee42bad85bf65787a4a37"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("7f76b8619b2e6858703abf64b6e1023ba5f43c3de14d7f4be1f6d25f8afd2b74"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("81fab234e9823113a4e02b02fba9fb16ff65df34c27563120409a52e9aa4fa1b"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("620bc02c82e7cd6732004c4a33993d6fcc3a196846ab2d0e6bc2245a377b7d18"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("231f963979426929d379ca4ab61c244572e1b11f991d5d43ff260a2c85168e07"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("f635510c4fd27c483abf832a234dc874f9a85130a2f1214f8ea64574d22ffb0d"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("8204ed160cd2044cd7baf30e223b5b6ddc076a6843ea2e76053f9d4eef7dfd1e"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("d50621701678010a890d103b0492c209e2d858452bbe7b1dd817276c0accc703"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("c76b2b13a8469b4dfe51a40c7bf7ea2eaadb546fee468d1dfd1e2a405caf4b4b"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("1f9d6d1ff8b50641f8dda252649df81961a81e65158917348dfc312660c68515"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("517f405d5dbda85b2dc15f3ab6f8a05170bde64980ef594a8e9fd923febe1a03");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("8929963bf715f43394bc621061318b281a1efd0de0cc8807aae36a483c513123"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("b2739446114e741e683d793a9ff5901a7b0bb852fd8ea01592e15c57e89c0a2e"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("e47473707502945ffa65ba153e475d2a1791cb1c3d828a220ddc3e6e10e4b66d"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("1a3bbc0c5d697b3f37a87e012d19ea2e09da942166e578197daa20141a9e6d73"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("0bbdf8114f060314563d6339778f8204ec964f3fa5db4734c9f287187e15df33"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("76d1310c7a5f5d3b3f115b0ec58715754f1dd9307f75be430086bd0ff05ad533"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("795f9b30c0d7c94e2374b51147a2e9047c0d013a557b7b222d81b40d1089ee49"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("d813836d7682750278f8c105d7f16067b0ce7d05a0c5b96ef71dc74a87530710"),
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
        digest!("9358401b5fe85022b5979201039d6110f04fda122dc85422fb31af14434d013c"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("dd87840cad6c8273ec133e066cae6011344ad928fa0dff66a44a9631f840115f"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("85cce34af124324c4d198906d16a671e7484d44c8b9beb53f6400e177f7d4562"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("ca941f46775d6251bd3b2216b9e6dc129a004d28adc3912a116271243244650f"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("c5b758004746761370f0e1029fd0556ccdd7c0086cf278646fd0ef2de14bfd08"),
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
        digest!("67d0955e75f92e2d5658b01241ab76678e75ba1e6cb74431f6fb0d64d5485770"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("19cb7829879c1f4bacccc661b394a076a9d7da3371aee42bad85bf65787a4a37"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("7f76b8619b2e6858703abf64b6e1023ba5f43c3de14d7f4be1f6d25f8afd2b74"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("81fab234e9823113a4e02b02fba9fb16ff65df34c27563120409a52e9aa4fa1b"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("620bc02c82e7cd6732004c4a33993d6fcc3a196846ab2d0e6bc2245a377b7d18"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("42a680516b000e5bdf09d4280faf3458e5b9542f0b8b4521a8523d72bb0ab042"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("231f963979426929d379ca4ab61c244572e1b11f991d5d43ff260a2c85168e07"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("ae553d5712fe742102933a1d2dc59e5163f46615e956ba2c35174a3a059cdd44"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("f635510c4fd27c483abf832a234dc874f9a85130a2f1214f8ea64574d22ffb0d"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("8204ed160cd2044cd7baf30e223b5b6ddc076a6843ea2e76053f9d4eef7dfd1e"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("d50621701678010a890d103b0492c209e2d858452bbe7b1dd817276c0accc703"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("c76b2b13a8469b4dfe51a40c7bf7ea2eaadb546fee468d1dfd1e2a405caf4b4b"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("1f9d6d1ff8b50641f8dda252649df81961a81e65158917348dfc312660c68515"),
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
        digest!("f3ede891b6b42da709214342aec282213cb3cba55f88ed0887cefa412dd23609"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("878fef0bb6a0f8f5bd96c11c31345187e38f3f256fc557e695332f30ebd251d1"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("709c11baaa7d95d9dc51ab9ea1d786c7195367229fb9e09be9a5bc8c951abf03"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("44e03fb42ad6fbf84d6984b1d8e51681f759c64a80230c497d30bfe67a351bfa"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("d77fa4094c1b2df4999f5b602d25f27fd12e56f1decdaca59fc00c582eaee650"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("71119072ee181f797984bbedb6af76497576d156d4452c0ef1f937f4570f1343"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("336a0cd02e8e9fb149ac24244d57911e7a974cbdf8bcdc55fd7202f57e51366f"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("817ce1b49dccb620b8dcdab08a151e8f508f4b80ccd1d2fa08a5b3d430e63213"),
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
        digest!("005996cf2d080f3d157e07f0e96f9666019abe111609086b38747c12ff9d4f9f"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("2e4575db04f12e10e38aabfa8dba0a2550dcdaf46854a6af558e00e5e4d791ad"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("27e97a81fe77afb8db5620c5c24e8564b8655976742b130406cd88d7b1d99ab5"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("12bdfe4fa4b0aee5332f22f1737941eac2265d76bb127aa095edf010badd52c9"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("bb6dc4446d37ff3e04e9694b9115339c32e490e596bb8cf8200191ab7ee09ba4"),
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
        digest!("5fbff888bb69a5acb2def18d4a6de0a445b3b7b1fd27ae8de8803e27d727ced5"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("53ee65c0c116345ac1c14b9b057c22b40ec5f47d08a62143cadf47705249b068"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("c2f5b694c8c6681d66d685628066471a4e4b4abc5119a72c5baa9c14e11f52d7"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("eacd84c243cedf13a7cef8fb01349bcae3bc89a5a0231fb3a00f906297ed7522"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("94db4c3c1585ebb141228c48d3da9dac00a8268affb8772ad4eaf4c4511cb8d6"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("3fd5b6cdc2a3bed581e4234ab8a0fee7e1479c0386204dcd95fdc0653e23e7c4"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("39f25b32754a69ae91c3e70e3312483619651da09a1603b8aaa22a7b702539be"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("68177e8a8ed36ed38aeb1a71e15855f5ad5a94db8e27e1c4f665d5019a3506fd"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("ba622d076ac7ad69448987f316936e9724da24cb729cb9c587e24061fd376fad"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("8550102f8646a180760057fea4314ab4dadd9b8f400803aadfb1c424e548cff0"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("90694a217658fc7555aa614352de69125e89a8e4d5baf19b8a38ab450bacb714"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("f463cdf04eecc3944f4df06cc872ee54198fac75f562397b89252b7dc3d06aba"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("5740ec60a824de00301e9cf78f4d36db77ab0e47d201e9978832a504662a103d"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
