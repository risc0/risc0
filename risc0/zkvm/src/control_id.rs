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

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2;

pub type RawControlId = [&'static str; CONTROL_ID_ENTRIES];

/// Control ID for SHA-256
pub const SHA256_CONTROL_ID: RawControlId = [
    "f302d53a420a2d418c8a385fb885d828ba3c26f89adb040afaa6836d1aa768a6", //
    "16b10a2dc0b48c4d349f60b874c9e5bb8d2dcba4064098e85bec2c18ec15e85e", //
    "bc1bcf7618de929e867c283fef71443b103df03581545c288e1cdada642b9492", //
    "c35f4d0a9919f00e7f3b215b3d444c1332b1e7cb3c20fb7b0228e616f81dd1ac", //
    "dbd09dd259a1fc088509993f3d2c772a1a2465dc83e45c8f1208e474f122616f", //
    "a09010db92a06fdc15534a11aa33e719a5ff732985dda78b97657a8f96edbb3e", //
    "feebf98abc452bc2fdddda2906c207994040e1fea164be23b576b4da127778a4", //
    "6ae471dad8fe355f54ec17e0dc24ce1dce30429c91a6bca17ef9752acabb3dc4", //
    "2dd0bf90df0d418d19162379496b45db4ff52f2f18d79838820f22419bf19548", //
    "680cd2cf80c15188c0fa2b88e9ada08c81d1c5612a97666b49554c1e7912f4f6", //
    "e51149bf1d6a6c1707c19b81a2cca76b7b874384abba56092a8a813759eff362", //
];

/// Control ID for Poseidon
pub const POSEIDON_CONTROL_ID: RawControlId = [
    "51ae200aff467023cf6a5064d5a09665da8e7070c5c21836094f911546d22e1f", //
    "00c27070b8926f762ab20915eb590b5c24d62e5506700d25955e957609466d66", //
    "70501201355f3e741063ca3ca3fece144bf18f6cffd0d262013b443401b6350c", //
    "c4c8fb3b5c6f64130549b7421820350309071d11b58adc2780288f5a6b4a2418", //
    "0a41ac73e0996610dd8f84121baa9a367628be5dbc291f06f9b55b158a2c146a", //
    "fa1415457323d91a03c16b44dd907a2a4fc99c68d01abd014632db33148d5016", //
    "27cb9541d76cc85b24685d08eed23f4be43aaa284364df21fa8e0070da24326c", //
    "09110c72fc34a73121f27445a8e7884e226628032fbe1b6b89dded6f8c7dda47", //
    "c7bf9a0cd1219d0df8071975bb44db1700623728908cb44600ec832a49500660", //
    "4d0085115c4b4e082fb6285ae25ed44d68d15c2226461a4dd16e0f3a06a45466", //
    "81107f0900d24745915cbc3edf0103709cac2c5a670c6109d1624a57dd464d18", //
];

/// Control ID for Blake2b
pub const BLAKE2B_CONTROL_ID: RawControlId = [
    "42a02f7c14df3fde560c29b2c879c2ac86238e045d6e5c75191856854d51870d", //
    "0f90e6b0944ace480bd9f3ac476307ac46f8044fe0749257f066df584c85edcd", //
    "90ff045c09a657f06124fe340b4002704937f3992c0910c0b231fa3ba8ca4344", //
    "2f32c54330b34accf7aa826c368e0d6a427507277f09638c2288a2a17ff078e5", //
    "6ae8db0bc05d48273731039c7b7f9cabfe54896969ed759112651a5480127229", //
    "4c89b16b52b44e06cd3a46bd78cf588114581f9029db5b9d8ce575fb0aafe360", //
    "e344360d9ccbcc198c274a6809507c92b43e4a33fa9638b300c02f23a619e54d", //
    "cf8ae5cb11854b9f3419b874c6b1f45bdea73e41af21a5d0c0e0ea7f17d866c6", //
    "90dce40e6caff84242828afd5994ba0ad46c97e12cfbc124fab1bb5e0ef846a6", //
    "bc131871045d7e6124b1b36fb3813b7dcf2af0bfe54332bd88d76cfdc4ce9825", //
    "ca2ec341980bc2c0e274d3e12c628413cf90a485bc00049a8b2d4e0918ca1cbd", //
];
