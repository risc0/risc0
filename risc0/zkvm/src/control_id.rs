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

// Values of the control ID were calculated using the
// risc0/bootstrap/src/main.rs script.
pub const CONTROL_ID: [&'static str; risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "26aaf5e87e2df3a5b2ba1c07764a9755b8fa5221b5f0bfd96a129427d016ece1", //
    "f9ec28d3b9cea704a33a130529ef1e75cb5f510ca1de612acc78846f359c6238", //
    "81aa8820d35d26c8c59ff074969f4eb73eae5921ab43903fe8b7118a600e3120", //
    "71251994363af2c1d2e2e3de5799d31af6d367aef39a5cd286db3a1c361ddfaf", //
    "30fcb1b29ed01c40325213b81d9ef014226a69a583a6118b63054d00b3c66715", //
    "56a136e93436dba448df87c0f1c8dbd2cf5f49b6d873a8e99502710266f4d5a5", //
    "cebb191e47a7834cc581d789a2691542c1b6ed84b1c79c7fe507b848f2504f61", //
    "799fec354f0d7a06bfe8f4e42f5dd649a33b8bf23e42a02c93a9eb8a6f1f5f3d", //
    "14ff550c9be4f0f248795418b9a248dc7b964a6f9ebdb3374e3331f92b4ff508", //
    "fe2114ab387219e7b1abc8772a30e93e449e327efb8e664751c16da5dbbc107d", //
    "797965fd8b7a33c9a6addfb7eb611910fec0ee5f79d02bc6a490bbf1ecbf0a61", //
    "443f6afe8119c42405924f9f6480895a54d6629833feda228f9e69b5f3b1e1bf", //
    "29260d269d38036082e666aa221d3b977881eab8accdaa1ff5fd8b30b0b06e5d", //
];

pub const POSEIDON_CONTROL_ID: [&'static str;
    risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "5c836f57798f110a16f9cf4c698a7503d3360404cd0c5853581067201832cb54", //
    "ffe3567178f68d5b9feec90cb772852f2030b85563fd51240b1635215fb74921", //
    "9983743f036f104b1d06471ef679e74967d44c083fe37974e2fe7502f212790b", //
    "40e9ca3ee7e73c33576e033a4123a822c75a347603923377299f9b63b7fca734", //
    "c7e6634ce309db0bd93a2103bf7dde7259e8f020aaf4e21d6f1fb7109590104d", //
    "dc177a2cd707a1771ebd0072adaa713772592f77bd779a67335aa9641456fe03", //
    "a8bec31ad86fb40627c3355d07b7d51f28b0a9061591404abe40ca526de18532", //
    "515670149ca9af637e70d95ab4cc61729af5fd4f1f4d6f4ea0c8a2776820c51c", //
    "9a07134424d38214ca7a6555aa62373f5243ea445d98232bd77918716ac83f2f", //
    "66d70121ad68454c2c22b016761785095b69c6454d6c6832c58c9b53354c301f", //
    "1a9d8a06a5d4ed0dc6bbfa6c3d06e7140ff9a3051d64c37456c0171286281211", //
    "61c9ea4e60f1276b6d28db11ba3438200a41a256358d4d1d86caa90886288475", //
    "d0286431d057fa42df74b572dd1c6870818d2a7094e4ef6d4b7ae44c4b4dd56a", //
];

pub const BLAKE2B_CONTROL_ID: [&'static str;
    risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "51265ccd3158b166191ebc9d6851c2bc1719d9dcff42bde84669ec6d1d1033b1", //
    "c452124fb40f79255cd1b6508d2fa528fe842c5157721eb0f51b236c5479aa4d", //
    "90b8aa518f2795a68dd98715d22040a883fcc48827231d20a02b60aed5aa9c6c", //
    "110045267c6de55c5c6ece41fb9643a40e2f50242f7becc434751e6a080eac56", //
    "6a87fceae16dc30a090dcbf78b416c3cabc0ff473ec374ee4d6dbfa2ad1b2caa", //
    "07134a794a282ca9181d758193eb06792cff6b9a019a93631805a0d624604536", //
    "94291ff35262bef14b38af3057748e8c2f5cb1bafc9b761a86a11b8e05dd4972", //
    "ebaf330b59e48e72c1551c23d4947dbd2ef0a6740fbb0f24ce806d6abdc1d123", //
    "ee59bbe1ac9902297b684a41df66a15d47da93b6f7b647c25d2f0df2c4c0eefb", //
    "be13930445d9097cb20841c3afcd0a63c9d9673429acecd58a3cf0e762cc3ab6", //
    "b2323de771f4d31035aae557346e6aa84023b5bcef77ec9c4e39f01aba11b567", //
    "db6584f5b284b622f3ad08afaea9ab669fd493f460a11f999d285301214ee595", //
    "2a9517ab4454868bb07d4d39043512f46f1df2b623722507b3346ee69c7d4cbc", //
];
