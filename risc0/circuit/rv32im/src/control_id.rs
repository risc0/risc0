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

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2 + 1;

pub type ControlIds = [Digest; CONTROL_ID_ENTRIES];

/// Control IDs for each power-of-two of the rv32im circuit using SHA-256.
pub const SHA256_CONTROL_IDS: ControlIds = [
    digest!("fa82a26d5e99ae1abcabc424cfb79264fbdb098615d5fc10dc843753f8998d82"), // rv32im po2=13
    digest!("e24a177f14dbc745c6f5ec2b7aecf5e474193aaad1ed13a8e2a9c6ca08b129df"), // rv32im po2=14
    digest!("83b916c5a88ec9d3b39a6a102273fe1f4644a6747a16dda4f52b7e4cf6a595fd"), // rv32im po2=15
    digest!("89a28a558e290bc212520d767344e0ced2fa9faaaf12fdbef67c6a824e0f269d"), // rv32im po2=16
    digest!("9133ae1e559cf7432e89731bbf73ed37d1a14703d7c5cdde1b69d1e0b9307363"), // rv32im po2=17
    digest!("6ee4730e73eb1772750874958e4ffac9291705a1f79e9a11b7712270ea6747e8"), // rv32im po2=18
    digest!("9c0498f6267afc352ed7def9d8421899526139e2909a3cdbd1cbe34ee5d73412"), // rv32im po2=19
    digest!("a7a1079a925e06581200bd943371aa44eaa5a553a5f5a92b27a416cbbc7bee3e"), // rv32im po2=20
    digest!("0d85ecb4d16be50857cf50883e5b66e3f7185b2aeb5a7479cfad24ec61306b9b"), // rv32im po2=21
    digest!("a60d1c94faf9ca4be54d70518502139d260882d0d981d6199152b9e1468db984"), // rv32im po2=22
    digest!("5a10d231bc367d19130b29acb569eb7f3827b67e47a271f947e3e209945283f1"), // rv32im po2=23
    digest!("da30893f75e7b069cb0004874a0bcb0f7b713aa30be88b3135eda6758bfd780b"), // rv32im po2=24
];

/// Control IDs for each power-of-two of the rv32im circuit using Poseidon2.
pub const POSEIDON2_CONTROL_IDS: ControlIds = [
    digest!("30dae603fcd283331d01105ea129ce43a0957a59b4f0013359a5642dfda0ba26"), // rv32im po2=13
    digest!("2afea6024b79430b49f60518f27d7262f2ec5b1306a9030cc2e4d955e5dc5964"), // rv32im po2=14
    digest!("8dc2760e1e24082cb66c83470c24a8017e95ce4d5eab170522f783418d545e72"), // rv32im po2=15
    digest!("35feaa4eebbefd45b0a36a350671c82154f90c660389ed3a8ff7bd2a30805973"), // rv32im po2=16
    digest!("7436486fdf9a7d3a3f8a03263bc7541a3c173c2ab5d2eb2c53939d0243dc0d16"), // rv32im po2=17
    digest!("3abdc115ddf6af1977863c29c0f2b91f8c0c2a1c35e82158104b651f6a07a816"), // rv32im po2=18
    digest!("17d75c070f373f333bbbaf33a688bb74fc05670435cd5d6378d37b608448e300"), // rv32im po2=19
    digest!("f3cf1217485c403cea526b1e52e70835c31bdc6e3016ee12916f6c6561fc0977"), // rv32im po2=20
    digest!("4043ce1426811d4f0e6a9c27256d052513c95739e9b80c74f628f313c739b75c"), // rv32im po2=21
    digest!("b4edfc3f2c49f10285bcdc7493eb81063959820a59569356fb73b62c1586e01f"), // rv32im po2=22
    digest!("cc1bd6753bb8fd41d41bba14bb56e90ffa9ddf4f20f7727734d140675a9cc52b"), // rv32im po2=23
    digest!("278eca2b9c62fe6936b6cf5c1b066b55d7620322f7c4331a21a5f92f851f6c6b"), // rv32im po2=24
];

/// Control IDs for each power-of-two of the rv32im circuit using Blake2b.
pub const BLAKE2B_CONTROL_IDS: ControlIds = [
    digest!("1a7f7747c8716881e4e90c36128958ff730e59994cc624dc37a7ad58b1b55045"), // rv32im po2=13
    digest!("3abb9f97c96ccd3b9c79477a9ffa6aec4cf3a478594158b7996c303131086f1e"), // rv32im po2=14
    digest!("e62527b7ea63e68243d8a2017d3884d08f9124526da3a2cf44a6e117de018404"), // rv32im po2=15
    digest!("3f66b9557123bba91b459ff231e0427e677c216a328b634ff28fc984d2a07529"), // rv32im po2=16
    digest!("50feac663f707817cbc4b9cc0f0fa2852cd8612a8b567e00713e293ecb4d13c0"), // rv32im po2=17
    digest!("c1c16aa53313bccc806643cf08d39d33b8a07ba5665519880d53e2808950da88"), // rv32im po2=18
    digest!("49e896cbd61bee4ab937877a1f62941fb38a728d528487d08fc5e28e84d8c09c"), // rv32im po2=19
    digest!("ba77e8ec037cea89033de1d4c9bc81bdfd7072018f697d0c8189e2d6fc859af6"), // rv32im po2=20
    digest!("87f1d53aa67abf141f10d14075de1c32b6ac818110bc1e5a90021ea9b8024c31"), // rv32im po2=21
    digest!("04d5432e6e4ce69dcf868b08418c1a30ef9e4d0cf350e889e1c2436095b06058"), // rv32im po2=22
    digest!("d0a94a254af9bfc8e457d5f84afe5150d680579cff65e37140720aa112e63b9f"), // rv32im po2=23
    digest!("46b765782f325e05cf04188e530fa6f33c6a8c33050f3b929bd6eedb541eb5a0"), // rv32im po2=24
];
