// Copyright 2025 RISC Zero, Inc.
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

// This code is automatically generated

use risc0_zkp::adapter::{CircuitInfo, ProtocolInfo};

use super::CircuitImpl;

impl CircuitInfo for CircuitImpl {
    #[rustfmt::skip]
    const CIRCUIT_INFO: ProtocolInfo = ProtocolInfo(*b"RV32IM:v2_______");

    #[rustfmt::skip]
    const OUTPUT_SIZE: usize = 74;

    #[rustfmt::skip]
    const MIX_SIZE: usize = 36;
}

#[allow(dead_code)]
pub const NUM_POLY_MIX_POWERS: usize = 458;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
    136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154,
    155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173,
    174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 185, 187, 188, 190, 197, 198, 199, 200, 201,
    202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220,
    221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258,
    259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277,
    278, 279, 280, 283, 298, 304, 310, 317, 323, 326, 328, 329, 334, 335, 343, 349, 350, 355, 361,
    362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380,
    381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399,
    400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 417, 418,
    419, 420, 436, 456, 471, 487, 513, 521, 578, 586, 604, 635, 651, 658, 670, 681, 704, 705, 706,
    707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725,
    726, 727, 728, 729, 761, 808, 828, 853, 854, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864,
    865, 866, 867, 868, 869, 870, 871, 872, 1007, 1040, 1127, 1214, 1428, 1544, 1825, 2301, 2452,
    2620, 3487, 3907, 5914, 6323, 7027, 7743, 7744, 7745, 7746, 7747, 7748, 7749, 7750, 7751, 7752,
    7753, 7754, 7755, 7756, 7759, 7762, 7765, 7769, 7772, 7775, 7779, 7789, 7799, 7809, 7823, 7840,
    7850, 7861, 7881, 7891, 7910, 7912, 7919,
];
