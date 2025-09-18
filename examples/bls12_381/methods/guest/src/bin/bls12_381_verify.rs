// Copyright 2025 RISC Zero, Inc.
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

#![no_main]
risc0_zkvm::guest::entry!(main);

// Test of the pairing operation with non-Montgomery constants.
fn test_pairing_result_against_relic() {
    let a = bls12_381::G1Affine::generator();
    let b = bls12_381::G2Affine::generator();

    let res = bls12_381::pairing(&a, &b);

    assert_eq!(
        // each const * R_INV (mod p)
        res.all_raw(),
        [
            [
                0xa843_05aa_ca17_89b6,
                0xb6d1_94f6_0839_c508,
                0x3dd8_e90c_e98d_b3e7,
                0x272d_441b_efa1_5c50,
                0xa7b2_d831_68d0_d727,
                0x1250_ebd8_71fc_0a92,
            ],
            [
                0x5988_2a98_eaa0_170f,
                0xf1a8_943e_5043_9f1d,
                0xaf5a_f689_452e_afab,
                0x68a8_4045_483c_92b7,
                0x8675_0ec6_a532_3488,
                0x089a_1c5b_46e5_110b,
            ],
            [
                0x881c_4c84_9ec2_3e87,
                0xddff_5730_9396_b38c,
                0x16da_0e22_a503_1b54,
                0x0378_a68e_72a6_b3b2,
                0x9703_f239_689c_e34c,
                0x1368_bb44_5c7c_2d20,
            ],
            [
                0x3150_21ec_3c19_934f,
                0xffe5_1d7a_5799_73b1,
                0x7c90_d8bd_6606_5b1f,
                0x37e0_794e_1e65_a761,
                0xc273_fa07_5a50_5129,
                0x1935_02b8_6edb_8857,
            ],
            [
                0x1dad_1c1f_b597_aaa5,
                0x19c3_4dff_bbaa_d843,
                0x1852_03fc_ca58_9ac7,
                0xfbf2_f8da_752f_7c74,
                0x9112_5ba8_4dc4_007c,
                0x01b2_f522_473d_1713,
            ],
            [
                0x8bea_e962_4045_b4b6,
                0x23f7_daca_a35c_8ca7,
                0x8061_e55c_ceba_478b,
                0x46da_634b_8f6b_e14a,
                0xbd3c_7993_7a45_b845,
                0x0181_0715_4f25_a764,
            ],
            [
                0x0f94_8226_e47e_e89d,
                0xbb12_d583_86a8_703e,
                0xdea5_4d43_b2b7_3f2c,
                0xc887_84fb_b3d0_b2db,
                0x9cd6_bd15_c3d5_a04d,
                0x19f2_6337_d205_fb46,
            ],
            [
                0x102a_e1c2_d5d5_ab1a,
                0x1bfd_1b68_ff02_f0b8,
                0xa7d2_809d_61bf_e02e,
                0xd585_7baa_f222_eb95,
                0x9f80_940c_a771_b6ff,
                0x06fb_a23e_b7c5_af0d,
            ],
            [
                0x1b93_b473_33e2_ba57,
                0x78ef_4888_1e32_fac9,
                0x7d0d_15ff_7b98_4e89,
                0xc81a_93b3_30ee_1a67,
                0xfcef_6808_3b0b_0ec5,
                0x11b8_b424_cd48_bf38,
            ],
            [
                0xbe22_91a0_c25a_99a2,
                0x7ba8_10c5_a09f_fdd9,
                0x20c8_06ad_3608_2910,
                0xc6a0_e978_6ab5_9733,
                0xc31b_4fcb_6ce5_771c,
                0x0335_0f55_a7ae_fcd3,
            ],
            [
                0x9108_f024_2d0f_e3ef,
                0xa4fa_fc05_0662_45cb,
                0x1c7c_dba7_b387_2629,
                0xa189_e879_35a9_5405,
                0x0224_9b64_728f_fd21,
                0x04c5_8123_4d08_6a99,
            ],
            [
                0xfde4_4938_3b67_6631,
                0xd48e_aa24_afe4_7e1e,
                0xdeff_686b_fd6d_f543,
                0x3bac_a4d7_2ca9_3544,
                0x0686_72cb_d01a_7ec7,
                0x0f41_e586_63bf_08cf,
            ]
        ]
    );
}

fn main() {
    test_pairing_result_against_relic();
}
