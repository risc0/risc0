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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2;

pub type ControlIds = [Digest; CONTROL_ID_ENTRIES];

/// Control IDs for each power-of-two of the rv32im circuit using SHA-256.
pub const SHA256_CONTROL_IDS: ControlIds = [
    digest!("6d0ed860e3effc3cc00114075cb29630b583d227b5654adaf0e9a4e4926144a4"), //
    digest!("8f4880393dbb0dccf06e78081ca4f81b56e57ca5a0d056d927d41d1f19d0eb78"), //
    digest!("5461f6a04636ec3e513511de5b324e92ec027de3c3c2d5b56edcf28f21a2797e"), //
    digest!("aa0fe87d397a845d6c63b7896a031e2fd9d221e02625741ce631cf060542842d"), //
    digest!("fd2551902a296fcdc2d49ecbd7b2140b5b8adfb86023e4e2c1ad433e9d4e5487"), //
    digest!("204f8e50713cd5da7a41c128d1dd27b722ea0d6c21c785a9a608df13dcadc108"), //
    digest!("90d0d9c5bbb5ad02dd004a83e29a6ede8ed35d33a762bbf14f8fd323a8053fbf"), //
    digest!("3b652874501bcbb2d3283f4a6640fbc292f9db0c3353b1b5d058c79ab9e684ed"), //
    digest!("23ef25c5d5e356bab81c4905e499de9161596435839366c2b0e8fb3c6d8f2232"), //
    digest!("bb795263e615f72c0fb6b8d07c8dba82d1a8b5a53870b106ffe738a4f8943dc0"), //
    digest!("55330f0d062c6972bf3f65c4e5055544e20c9f776f6797f4428f7b3a6fbf0573"), //
];

/// Control IDs for each power-of-two of the rv32im circuit using Poseidon2.
pub const POSEIDON2_CONTROL_IDS: ControlIds = [
    digest!("55ba2d763ec3c016c0f97c298507115c77e0a25215e5771ba501d016edca522c"), //
    digest!("c265954c4dcb2155e041286a246bfe400ba9d042d919aa3cb1a299651f84c13e"), //
    digest!("467cd61da86f37347b45e64b5d4665308871bc301c67ba6c6d13c9470c3e4840"), //
    digest!("57b2031d3881e92b85d73d2d0800a223fdaccd5e7bdd0a569c10556ec138f551"), //
    digest!("c1f19103f8376c00fe20f62aa4370f628efe3a4a5eb1a5739466c944cf7dfe31"), //
    digest!("548ec1774c6c833b18db2e2a1464cb1923c6c721df87b437509ba87292d20529"), //
    digest!("ce535b3b10e4cc212842b90a918553633c4f5375dee51d4788798765df5a8750"), //
    digest!("7dea3854a91c906f92f23a291340066ecbd5375669fe752a5047c926e4d56747"), //
    digest!("dca31f53c5bf4c67ecdc9f1035cf5934072afc29573a1845100d6140befab657"), //
    digest!("12da4520930b1740810a69428c02fb2fcb586763a0e3794c45196608b594dd69"), //
    digest!("5c2dce7226ff9073b8e38919583c01375f11395111e9ae3bfd519b57f84a5e00"), //
];

/// Control IDs for each power-of-two of the rv32im circuit using Blake2b.
pub const BLAKE2B_CONTROL_IDS: ControlIds = [
    digest!("1f682e2ecfc82580667b8549ce548310f79f7055195d1f3a70d11565dd7c8311"), //
    digest!("66c3c1e1293ec0deea97cd1531a4fb202f7c57c3fa9908598519b12776272f37"), //
    digest!("e8a718749c38e77f1a52856568669d38591e5ee3deed15e251b4cd45994e56f7"), //
    digest!("3010f3679241489056004ab35e7b0c5feae8a6b45fe46f2c17e65e681e43ef25"), //
    digest!("a01d6a57f7aec62ffec3edcc5347c2acb88abdb0460e516d1b7d984f487dfce4"), //
    digest!("ba388a957a36a9a514fe5efe738f497fec585e267bcb6fb0a9d79b22f5cb34b1"), //
    digest!("e2fba32638e85de83c7ce06c41d48bb159efa0ec58de2e3ed4c172c7fc82b6e5"), //
    digest!("d9edf22d1c828087fec2fce4cf46261e8b6e8072b29f4beffbfc36309ae0e9d9"), //
    digest!("f04cfc7c358eaa225ee249e88b804a92679b43adf51b5cef1d0fef40c3afbc06"), //
    digest!("98b1e437c659b0435b5829a5d2fe697d08fc4b02641747d0f7d6b171b9c83415"), //
    digest!("68ada0a6c57d353b2a3645d42854365acd1aa453faebda9988b75c5802f4a1be"), //
];
