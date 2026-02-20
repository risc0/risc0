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
    digest!("211f68494a2ff84dbaf9a93b22b28a09cceae10a939c2f20d7f3f41167e2252b"), // recursion lift_rv32im_m3_20.zkr
    digest!("8bd78154bfc2c658001d3a0da3792972aa636014178bb41f1b27f31001bee323"), // recursion lift_rv32im_m3_12.zkr
    digest!("ff85e015a25545048493b255cde81804da614c5d2d3ed7491d904a0e41952974"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("c073001817ca6c0a65273e0d6e6d9265218d973858fbc333f54d74234cd0020a"), // recursion lift_rv32im_m3_17.zkr
    digest!("ec2ba40f75380e6259ffaa5040135c404f7dd877c1639f63a1e0e523d53ece71"), // recursion lift_rv32im_m3_21.zkr
    digest!("578df80e93890322eeee1873a9b3b96c83ed134789d6f167b7d0491b56dbd14d"), // recursion lift_rv32im_m3_16.zkr
    digest!("d6550869c6ea1e473e13b7238301a86adffe842a7d35633fa3145d225b695932"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("bdba1a75fb31fc51fbedd614c368b54fd286ab609250cb18e96c665cad83b303"), // recursion lift_rv32im_m3_22.zkr
    digest!("7fc7186f4882a8541834a76439e0503b174dee13173d5501ccd3fc227dc96815"), // recursion lift_rv32im_m3_14.zkr
    digest!("e9e5b51b8400832a52ec0e40b585476d0d17ed755dfaf75472921a4a619a3309"), // recursion lift_rv32im_m3_13.zkr
    digest!("fa73c80b83e2095a02936869bc931c5832cebd1ff71f191513265f6ab2adfb65"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("5535520b9a8ad8233ac87c1b553cb831a2d42b37021a7a0ad422a636bbf46f68"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("0cd55942e23a33289d946a2d2710a91eaac1a87721d20237cf144b137247d312"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("4b2f7f2a2b79774c87686d52032991297943716d8276c74d25f1db14d9404508"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("49e8450765fc3e62846a4a54e1eaf813ef880e10f2cdfe0925522734e9e41448"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("19e3ef2fa6fc3c6a791c10204d51b771518a85271a7fe31ff90be64b4c2c5b04"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("74a1ec602fe9845e34da8e40043fd304824c315629f7244bcedd901727906b4f"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("7fafd3534244df535c233643aba16921d578f20183f5864b3297d47100913115"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("0998a806f06a2669e66a2a34a751cc74438c762fb612ae1925d9df042eded63c"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("3919820adb805075567d7e27849d764cf24b404b3ded672da49fcf228849a461"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("1c33f645650bce503071ad2395d7810a706d5218d010dd1d14c09e5c2c6ddf3c"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("ca43f63c4034092e5e136f6ebe5c510b36c2f76607d0385dca62102af566f46e"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("82345423834a2f7074d5bc411153ff75072ac04dc784596d44856a0c3de7d017");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("211f68494a2ff84dbaf9a93b22b28a09cceae10a939c2f20d7f3f41167e2252b"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("8bd78154bfc2c658001d3a0da3792972aa636014178bb41f1b27f31001bee323"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("ff85e015a25545048493b255cde81804da614c5d2d3ed7491d904a0e41952974"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("c073001817ca6c0a65273e0d6e6d9265218d973858fbc333f54d74234cd0020a"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("ec2ba40f75380e6259ffaa5040135c404f7dd877c1639f63a1e0e523d53ece71"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("03eb521f5723b74a4698274fa3ed894953b4d27268ab7f6eb414991f2e6f5a6a"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("578df80e93890322eeee1873a9b3b96c83ed134789d6f167b7d0491b56dbd14d"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("d6550869c6ea1e473e13b7238301a86adffe842a7d35633fa3145d225b695932"),
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
        digest!("bdba1a75fb31fc51fbedd614c368b54fd286ab609250cb18e96c665cad83b303"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("7fc7186f4882a8541834a76439e0503b174dee13173d5501ccd3fc227dc96815"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("e9e5b51b8400832a52ec0e40b585476d0d17ed755dfaf75472921a4a619a3309"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("c9ed4f26d18b2b17637d9f3358556e300e425b2c3e25cb6a77b2235accdfcc18"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("fa73c80b83e2095a02936869bc931c5832cebd1ff71f191513265f6ab2adfb65"),
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
        digest!("5535520b9a8ad8233ac87c1b553cb831a2d42b37021a7a0ad422a636bbf46f68"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("0cd55942e23a33289d946a2d2710a91eaac1a87721d20237cf144b137247d312"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("4b2f7f2a2b79774c87686d52032991297943716d8276c74d25f1db14d9404508"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("49e8450765fc3e62846a4a54e1eaf813ef880e10f2cdfe0925522734e9e41448"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("19e3ef2fa6fc3c6a791c10204d51b771518a85271a7fe31ff90be64b4c2c5b04"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("f0c7e838d1c92d2ff3127e6ccce4da6d925b8015fdd8bb1be576ca0be65e1b2f"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("74a1ec602fe9845e34da8e40043fd304824c315629f7244bcedd901727906b4f"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("8b7ac51101e2503aa2c1c14e698bf026909eb5175394ef2cdc0ec41cbfc0f704"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("7fafd3534244df535c233643aba16921d578f20183f5864b3297d47100913115"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("0998a806f06a2669e66a2a34a751cc74438c762fb612ae1925d9df042eded63c"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("3919820adb805075567d7e27849d764cf24b404b3ded672da49fcf228849a461"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("1c33f645650bce503071ad2395d7810a706d5218d010dd1d14c09e5c2c6ddf3c"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("ca43f63c4034092e5e136f6ebe5c510b36c2f76607d0385dca62102af566f46e"),
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
        digest!("aaca2f8ea2c7c4b4ea7df39a76d7840f7fbd17c6bf66bd3be087f3306a9719e4"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("bf52abd0dde1c10f9217c3d5bebdb2e263d1feabf3276820a7f1932ceacfd346"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("1c78467e3e23dec16a9584c099076e56efdf8a2ecdd7da4e809b73a1e8ce1938"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("812c56491c2b61d3eead0a69fc9b384c5949ad82e789860d3571997aa8598362"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("68fb4c830465d3d6ce5d3b41577ad2a42dd580b421e956c444b676f5b7d1a172"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("472747d9154f5d005f037fa3bd6499f6408f15922ce6126167a594d796c60061"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("291925c961c7c14b14c77542a5d0fdccdfb7c416d71aa2f109a2c10325ecbb07"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("53ee9459903e0dd32f0399b401d10f628df9649bcbc89deb05791fe443b00a8a"),
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
        digest!("7afc1d6c0f61bc9212e08516cec14d252aa5b1577bf25fc32ef958863fb3b44d"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("cc241baf9ea6c67890c603e0643f62a42df1806f21345cd5d24ca1f85c5f670f"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("a91d152ec40fa03d487574178ddfdbfe600d859e4d0751301c64573673094c7b"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("340a0da710605146bebdbf0477fd216ec6b74a4a5301e142dbcd4ba4b3cee4ad"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("8b5f8adda5d0c00ccec6c34717469923dcfe9d463b9e3fe59cd01d559bc131bd"),
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
        digest!("26491a2550e92bdb778b5ad8cd9d365728080fe3d8a70e60f5e1d32dc89adac6"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("a1078f4573337d7267964ca5b23867d05ccf6df1397b9fef85ae12b028b755ab"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("f2dd8a1c40aaa3f1a0b0ee29094512460bef69c5686ef4965e333de82709a57c"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("2207bbc55e4ede6699badf7eaae5c03e6eba6742f66f916d73e1c02bb0fbb040"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("7b7c96b856e337a817099c390f9b5055c6dd502175ccafc4c3357182853ceff6"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("3251d7b3b0ded84c9fc368a22ff48406f79e2e8a500bbb63be727591c0ded735"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("e5e83073c48808b08f86ab982e706a174fe4767da82a57dcaf7c88f76c473e0b"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("f9c2fa7f4d1676b1fb522af0e162f314668c70489b229f2ded485c5a2cf13952"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("21c97bf0ba143510ee3f8b4bc4a8dede803492a0048850343222e37f0c0aa71d"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("1caa01d12dd2022563db0c268a95b5cb427d4c6cba4d23bbc0dbca93093ab0de"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("8c4a5a0dbd5035ccae76a0a76b5f7951aa1ba3ab09c713dd6811e3a1522ff73c"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("44280155dc3724edc76e2bc0634c5a454a8a5cb08edce82eb0724400264a7d18"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("cac5966d179969ece624321cff35bf8e49ca411761fa10ec26fde3a32a9f4fac"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
