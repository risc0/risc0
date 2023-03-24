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

pub const CONTROL_ID: [&'static str; risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "e381e3e393ce236957923168f4e121c8ea4e9c6d902f347b384ab02a2fd9cbc1", //
    "37f1d57b121219236acd2051003c3f52305ee906e07c34a3116cc48b2ace243b", //
    "5b1cc0c8259979c0cf2f881eb12160c25da18cb40df760febe13ecf596640dce", //
    "3fec75461a0ce6e4227fec33e791a4c4a1d73def1cf3bd01846484ea64183e6d", //
    "2ca5614f642231a9a220dbc5ec60bd3b80079a7af53f5766a8da99a82c67dc04", //
    "ca0ea1a9bbe95f9bf714e932d6a7449e544087501157625f928316dbeaa5db5c", //
    "bc2b4c7349bf1ed9a046738d506e53e274f98a9ebda6391f953511074299459c", //
    "336beffb4865da27dd8da58e048108c670a0620e938f4e8f6352b406b1ec7549", //
    "f43f6ed3bec8edde7b9f26140e43c7d99ea2b9fc762a90b59c4bed2d7ec5ab23", //
    "3fa3d8c66da45bafd039beb57fcf4ea87f946a47e6968ce26687ab93e46f94f7", //
    "0d548b57ca20674de8ff2326ea7aef83bd41a6df9c94333c511664b04d7c34eb", //
    "cfc800c76e8e72691f508b92e32de137414c4036f7bfc7a3da763e2128e7affb", //
    "4a75e6239c6db8a52b677d39438b6901ecb12069ba7331eee21f8d54725f7070", //
];

pub const POSEIDON_CONTROL_ID: [&'static str;
    risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "d38eab0ec1ca2d4159e0a95942d8480ec956016cc93cf24640f04d5d72f0a43a", //
    "379fc406899ab567e687f5215400e56e545ab5253e0c380736b7af65f68ef468", //
    "55fe5631d0f74610caf8c84b0c5e6073ff19e2115e334b623bcf546c41d49001", //
    "eeefaf51d421751b085ab61615c3f21ee492290d10c31a037faef55c9dc0d74e", //
    "1c5f926f8028925559884841783f654dbf0e794099b014634e69f551ac5f1414", //
    "6a6ae34e22e0c26b7feac171fab801772d48bc0c6d219868bb328d462672df70", //
    "f754886c0affe73bf9fff34d9cf74d1d6989b01a049b8f656a3ef5416979bb4b", //
    "dee99831bd4427755c17c2429ea35e4196df272f190a322a24a00c3d63e4d61b", //
    "1dcd8a40c3eb5e3e92772203f123e23001c3911d139efc04c1e20c7154fd2904", //
    "70407020c5596514b9619a6896541f711f6fd011b5134705bd1f3d40ede39470", //
    "fb52242a9f14a704d325184fd7ed6207b90308178826d7203f7f4563977c8449", //
    "eb0da3709e25a70d15c45a168ca8b1579c249e4e852ab0046bef7e19e40a2072", //
    "1814c948eda9943d3ca68414087601433b50ff5e29fccf67ed10506e4a78b027", //
];

pub const BLAKE2B_CONTROL_ID: [&'static str;
    risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2] = [
    "67eebdc307a901a343bd1fa3a1160a97cdab9ada32057ce26a3536ad145ab412", //
    "ca7448ef0f06a678826296ee1b5ca3c90a20ca6af2f66eaef96cc73bd8ec48b7", //
    "842c6463187287c7cad5564b72cff8ff775f9146aaf32a22395a5cd6f999b39a", //
    "a775a7bc7c3bc66d6656138ffca19d0388bcbd231f844ed32662a512c6cc7782", //
    "b1775dccd047a46966067c1553721b59dd2ddc6298ceb4f930ccc16a656d2748", //
    "2bac1670e7a46334828accc1ef8c3f25c137396538fd97281830af309ba444c9", //
    "33b7b772fccbb8f262c10b69423d7b8cec73fd51d3e39bf24fa64720234e1286", //
    "fc645c4efb09cd0d497b47351813a20a49ce5bda633871288ddd67e990cc2bef", //
    "ec77c79e090573822c76f7dd4b62db47d68dc5d0ab7b60bed89f2c4f3f42af71", //
    "7a80ea3c7835c9f17de4ea4e9f023feaaf4ee9c5919e03f9b0805aaf78cea746", //
    "2d3debbd171acc0c3df3d32465ee96876693185b5516662b7441ca3c7283e502", //
    "c860d3a11ce99a7290a3be6ca56e6febfb6647e60957d93e18f64ff3f8fb1d5d", //
    "ca6a68e9ab929fd2b4178e37712902efa9618b787af0eec487fe1faeeaf094ce", //
];
