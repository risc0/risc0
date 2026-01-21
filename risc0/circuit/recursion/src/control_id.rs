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
pub const MIN_LIFT_PO2: usize = 14;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("0e5f5919b1664075b0eba11cbade2618466b192f1b8ae5590e31e270ec49e512"), // recursion lift_rv32im_m3_20.zkr
    digest!("dc766764f611de124ed94d5a8be9f32fe59f9a4e5b1ab656010c8624e1f4f20b"), // recursion lift_rv32im_m3_12.zkr
    digest!("e634303c76e86b6b0dfd7c18d1dba42c8e3fd15ff579ce0341c614777ae1d96d"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("82586f2087e98368d494044945974671c28bd66d9831031737eaf553c9ede667"), // recursion lift_rv32im_m3_17.zkr
    digest!("785b312e52ab1d3ad16838647ce16e5f9d96f4591b9dc95ba569236ed9fb4c08"), // recursion lift_rv32im_m3_21.zkr
    digest!("efb985727a3e2e5554be9439cc44474756ea833df1c81d437e2fec218221ae60"), // recursion lift_rv32im_m3_23.zkr
    digest!("0393c46672fd5f6c284e657083ad3c2504b0541be3e12406254dfe641a37870e"), // recursion lift_rv32im_m3_16.zkr
    digest!("956dd20900f7372f622be26aff79d960364ef8545e944b4f3a07626f6c270e09"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("f9aae3753b2e13231a6bea3171686c31f39c521be7910c1a7fb7e11ed007cc1c"), // recursion lift_rv32im_m3_22.zkr
    digest!("1bd2d25d1b62ad5020548506a800a525cc9c4700b01b106f923c5d6f92735641"), // recursion lift_rv32im_m3_14.zkr
    digest!("786f9568460f243f5596e5238a2b8011cd23a3158d2ddc1e0a27800bc6462b3f"), // recursion lift_rv32im_m3_13.zkr
    digest!("8b75e21f02f3d758d5b28c412c49da52b47b235c24fb7630f2902b2c50bd4177"), // recursion lift_rv32im_m3_24.zkr
    digest!("19c32545306c782d88b19c6339e8245d7bb8700d9a2ff85a898ed844831ded5f"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("2f2982688422010adfada26f86900f3b0fbe4460971a743081d1ff5c4b8e7376"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("b547ef2444e10563837fd5446bda490f0705c53c6f409b636656381ebd152841"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("dc54855c2713c16f071d88296729af6ada5a7720fbfbb935c458121134e12c76"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("691f8926b443671edd875d45eca44673be87191ac93ad438791db8637db0c256"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("deaef06085281961b21a695f7dfb1976b5aa8f4830fa855413923b3e7d9b7603"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("53d7fe47c144cb6cdeb6da1f76dd4b4653996b24f74aa3117f862914fa7d642b"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("4ec9a948421faa32a642a26fc25bfc734540ac6bb9493f31ac07c26b87ef0317"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("7ccdce333eb34e15c2146370a50f663c724dce11f4860f18612b6e25740fee4b"), // recursion lift_rv32im_m3_povw_24.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("1af45c65d3950d3b2f067b4995846812adc0b823082b384854ad334eb7865d3f"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("fb47dc098d6a1a490caf4a116723383e336dd75bf0f40b1686c48b474bdd981d"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("b9d1a34327e78e3eee37c14d8cb4cf5acc73de67c31b2649ff0f821dac87f212"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("dde2d70cf49f724d7e8f8b4d6ed9970072b73e0909d971170d84333109d35770"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("d45bfd3abd6564404d3bb83e16cc6f071bb4f1681c41304493aeab2a84baeb71"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("af0fd10e02bf3b279642a176f2728937ce9ae84ccd40bc3fe2da5f0963236c5f");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("0e5f5919b1664075b0eba11cbade2618466b192f1b8ae5590e31e270ec49e512"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("dc766764f611de124ed94d5a8be9f32fe59f9a4e5b1ab656010c8624e1f4f20b"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("e634303c76e86b6b0dfd7c18d1dba42c8e3fd15ff579ce0341c614777ae1d96d"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("82586f2087e98368d494044945974671c28bd66d9831031737eaf553c9ede667"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("785b312e52ab1d3ad16838647ce16e5f9d96f4591b9dc95ba569236ed9fb4c08"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("efb985727a3e2e5554be9439cc44474756ea833df1c81d437e2fec218221ae60"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("0393c46672fd5f6c284e657083ad3c2504b0541be3e12406254dfe641a37870e"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("956dd20900f7372f622be26aff79d960364ef8545e944b4f3a07626f6c270e09"),
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
        digest!("f9aae3753b2e13231a6bea3171686c31f39c521be7910c1a7fb7e11ed007cc1c"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("1bd2d25d1b62ad5020548506a800a525cc9c4700b01b106f923c5d6f92735641"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("786f9568460f243f5596e5238a2b8011cd23a3158d2ddc1e0a27800bc6462b3f"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("8b75e21f02f3d758d5b28c412c49da52b47b235c24fb7630f2902b2c50bd4177"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("19c32545306c782d88b19c6339e8245d7bb8700d9a2ff85a898ed844831ded5f"),
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
        digest!("2f2982688422010adfada26f86900f3b0fbe4460971a743081d1ff5c4b8e7376"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("b547ef2444e10563837fd5446bda490f0705c53c6f409b636656381ebd152841"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("dc54855c2713c16f071d88296729af6ada5a7720fbfbb935c458121134e12c76"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("691f8926b443671edd875d45eca44673be87191ac93ad438791db8637db0c256"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("deaef06085281961b21a695f7dfb1976b5aa8f4830fa855413923b3e7d9b7603"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("53d7fe47c144cb6cdeb6da1f76dd4b4653996b24f74aa3117f862914fa7d642b"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("4ec9a948421faa32a642a26fc25bfc734540ac6bb9493f31ac07c26b87ef0317"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("7ccdce333eb34e15c2146370a50f663c724dce11f4860f18612b6e25740fee4b"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("1af45c65d3950d3b2f067b4995846812adc0b823082b384854ad334eb7865d3f"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("fb47dc098d6a1a490caf4a116723383e336dd75bf0f40b1686c48b474bdd981d"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("b9d1a34327e78e3eee37c14d8cb4cf5acc73de67c31b2649ff0f821dac87f212"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("dde2d70cf49f724d7e8f8b4d6ed9970072b73e0909d971170d84333109d35770"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("d45bfd3abd6564404d3bb83e16cc6f071bb4f1681c41304493aeab2a84baeb71"),
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
        digest!("9fd3e8898a45e8bbfff6646762995bb0a240aba4b78fde3c834c662240ecae3a"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("fb1bc8ec398dea8bd022d31b382ebc99d71f91150596d01df3b6b650a67f13de"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("218261602766780aa40f3d413ea10649a402202bae215c1a21d5efdd01c75779"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("ba363e32fb11bf103edc8bed32b241dc865cc785de3eeb95fe6d294eb28d2e7d"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("b15975f027d392e7e0c9b341b342a99692a1adcdf5f8bd2ad62f6cba64f32885"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("7f42a53c90120a72bf66d159d001ee6c0c2b1e977fd331152a53885beaac6e0f"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("28810c101ed628f5131e0e7b343d7835f365b33d81f30fb2391e0cf252df7ad2"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("b29641f01335a9b24e38cdf5eb3fbdfa34ba10e5564826f0f02f4a66849250e8"),
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
        digest!("08b67029a8a214d942940518d9c84a20df8b6269f53bf8d985c38917c63d574d"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("b049bc0b3af7f842ab6ccb61ad7284721e5382578a7496dbebb9c48fe788a686"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("15f1a86ff6399450c0391dd9c3678b69593b2f063103d366bb5bed450558db1f"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("89cad8747cfb0e46a10dae2645e8ba9b9e1c558757daf01c3a723f2255c15dc7"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("018626d042337bed9131a941b7352ecbe898f263fdcb50827a42f118a9c2fb8c"),
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
        digest!("183cdb417430000335689305fb5691dc00ec8caf504cd0d17df78fcae4ec21a9"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("4b5c160808aecd215ee23250835722a165aedfc5fd832438e4cc3666c39c1c60"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("2433b56fed8ebe0139670280ac4b9adf8a95a27052fcb8a1fc7f39753031c54f"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("0c7c7e8853bb011318360f45224f8a40ed302a7645c02af6f3471bb2c94cc50b"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("6e842db492f5cf5d23d3515ed1c2cf6f7f74f66c4319332ec42d976070c7d9ce"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("d1ba9687a229244025f16f151f884a762860c2dd8f531ac6c43dca8dabcc2463"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("cf64712edf9e26478a57939bb979dd68664eb7057e21123b8368f7b404ab3578"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("1930a5284decff3b346e63e7ea24f6a0e86546b5c5c20077538ce94a663c4e7d"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("98669e197bb59fe9c5cc793d7e58a878d5e84ec43184d367111a89b5d7a7bafc"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("22319318f74bec37c94d9eeae9d8ed8fae68226ba5c73d3ddca15e5776d98561"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("283e609ef96dcf15b4460202f37001c160d45a93661ab8ad1af9c430223fb2db"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("f00f0d86dfe9098ba7f035b6b20860a598d5613a11e17927cbd53974f96b1f27"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("c8511fa45647a1ac683f1ebc18fba02b2ef08467073a223990be08a3b7dbe1ff"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
