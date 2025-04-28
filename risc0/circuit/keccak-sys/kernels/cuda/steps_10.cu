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

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ void step_Top_9(ExecContext& ctx, MutableBuf arg0) {
  // Reg(<preamble>:5)
  // ControlState(zirgen/circuit/keccak/top.zir:403)
  // ComputeCurrentStep(zirgen/circuit/keccak/top.zir:459)
  // Top(zirgen/circuit/keccak/top.zir:483)
  set(ctx, arg0, 12, Val(7));
  // ControlState(zirgen/circuit/keccak/top.zir:404)
  set(ctx, arg0, 13, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:405)
  set(ctx, arg0, 14, Val(0));
  // ControlState(zirgen/circuit/keccak/top.zir:406)
  set(ctx, arg0, 15, get(ctx, arg0, 15, 1));
  return;
}
__device__ void step_Top_25(ExecContext& ctx, MutableBuf arg0, GlobalBuf arg1) {
  // TopState(zirgen/circuit/keccak/top.zir:43)
  // Top(zirgen/circuit/keccak/top.zir:492)
  Val x2 = get(ctx, arg0, 916, 1);
  Val x3 = get(ctx, arg0, 917, 1);
  Val x4 = get(ctx, arg0, 918, 1);
  Val x5 = get(ctx, arg0, 919, 1);
  Val x6 = get(ctx, arg0, 920, 1);
  Val x7 = get(ctx, arg0, 921, 1);
  Val x8 = get(ctx, arg0, 922, 1);
  Val x9 = get(ctx, arg0, 923, 1);
  Val x10 = get(ctx, arg0, 924, 1);
  Val x11 = get(ctx, arg0, 925, 1);
  Val x12 = get(ctx, arg0, 926, 1);
  Val x13 = get(ctx, arg0, 927, 1);
  Val x14 = get(ctx, arg0, 928, 1);
  Val x15 = get(ctx, arg0, 929, 1);
  Val x16 = get(ctx, arg0, 930, 1);
  Val x17 = get(ctx, arg0, 931, 1);
  // DigestReg(zirgen/circuit/keccak/top.zir:391)
  // ShutdownCycle(zirgen/circuit/keccak/top.zir:396)
  setGlobal(ctx, arg1, 0, x2);
  setGlobal(ctx, arg1, 1, x3);
  setGlobal(ctx, arg1, 2, x4);
  setGlobal(ctx, arg1, 3, x5);
  setGlobal(ctx, arg1, 4, x6);
  setGlobal(ctx, arg1, 5, x7);
  setGlobal(ctx, arg1, 6, x8);
  setGlobal(ctx, arg1, 7, x9);
  setGlobal(ctx, arg1, 8, x10);
  setGlobal(ctx, arg1, 9, x11);
  setGlobal(ctx, arg1, 10, x12);
  setGlobal(ctx, arg1, 11, x13);
  setGlobal(ctx, arg1, 12, x14);
  setGlobal(ctx, arg1, 13, x15);
  setGlobal(ctx, arg1, 14, x16);
  setGlobal(ctx, arg1, 15, x17);
  // TopState(zirgen/circuit/keccak/top.zir:36)
  // ShutdownCycle(zirgen/circuit/keccak/top.zir:399)
  set(ctx, arg0, 16, Val(0));
  set(ctx, arg0, 17, Val(0));
  set(ctx, arg0, 18, Val(0));
  set(ctx, arg0, 19, Val(0));
  set(ctx, arg0, 20, Val(0));
  set(ctx, arg0, 21, Val(0));
  set(ctx, arg0, 22, Val(0));
  set(ctx, arg0, 23, Val(0));
  set(ctx, arg0, 24, Val(0));
  set(ctx, arg0, 25, Val(0));
  set(ctx, arg0, 26, Val(0));
  set(ctx, arg0, 27, Val(0));
  set(ctx, arg0, 28, Val(0));
  set(ctx, arg0, 29, Val(0));
  set(ctx, arg0, 30, Val(0));
  set(ctx, arg0, 31, Val(0));
  set(ctx, arg0, 32, Val(0));
  set(ctx, arg0, 33, Val(0));
  set(ctx, arg0, 34, Val(0));
  set(ctx, arg0, 35, Val(0));
  set(ctx, arg0, 36, Val(0));
  set(ctx, arg0, 37, Val(0));
  set(ctx, arg0, 38, Val(0));
  set(ctx, arg0, 39, Val(0));
  set(ctx, arg0, 40, Val(0));
  set(ctx, arg0, 41, Val(0));
  set(ctx, arg0, 42, Val(0));
  set(ctx, arg0, 43, Val(0));
  set(ctx, arg0, 44, Val(0));
  set(ctx, arg0, 45, Val(0));
  set(ctx, arg0, 46, Val(0));
  set(ctx, arg0, 47, Val(0));
  set(ctx, arg0, 48, Val(0));
  set(ctx, arg0, 49, Val(0));
  set(ctx, arg0, 50, Val(0));
  set(ctx, arg0, 51, Val(0));
  set(ctx, arg0, 52, Val(0));
  set(ctx, arg0, 53, Val(0));
  set(ctx, arg0, 54, Val(0));
  set(ctx, arg0, 55, Val(0));
  set(ctx, arg0, 56, Val(0));
  set(ctx, arg0, 57, Val(0));
  set(ctx, arg0, 58, Val(0));
  set(ctx, arg0, 59, Val(0));
  set(ctx, arg0, 60, Val(0));
  set(ctx, arg0, 61, Val(0));
  set(ctx, arg0, 62, Val(0));
  set(ctx, arg0, 63, Val(0));
  set(ctx, arg0, 64, Val(0));
  set(ctx, arg0, 65, Val(0));
  set(ctx, arg0, 66, Val(0));
  set(ctx, arg0, 67, Val(0));
  set(ctx, arg0, 68, Val(0));
  set(ctx, arg0, 69, Val(0));
  set(ctx, arg0, 70, Val(0));
  set(ctx, arg0, 71, Val(0));
  set(ctx, arg0, 72, Val(0));
  set(ctx, arg0, 73, Val(0));
  set(ctx, arg0, 74, Val(0));
  set(ctx, arg0, 75, Val(0));
  set(ctx, arg0, 76, Val(0));
  set(ctx, arg0, 77, Val(0));
  set(ctx, arg0, 78, Val(0));
  set(ctx, arg0, 79, Val(0));
  set(ctx, arg0, 80, Val(0));
  set(ctx, arg0, 81, Val(0));
  set(ctx, arg0, 82, Val(0));
  set(ctx, arg0, 83, Val(0));
  set(ctx, arg0, 84, Val(0));
  set(ctx, arg0, 85, Val(0));
  set(ctx, arg0, 86, Val(0));
  set(ctx, arg0, 87, Val(0));
  set(ctx, arg0, 88, Val(0));
  set(ctx, arg0, 89, Val(0));
  set(ctx, arg0, 90, Val(0));
  set(ctx, arg0, 91, Val(0));
  set(ctx, arg0, 92, Val(0));
  set(ctx, arg0, 93, Val(0));
  set(ctx, arg0, 94, Val(0));
  set(ctx, arg0, 95, Val(0));
  set(ctx, arg0, 96, Val(0));
  set(ctx, arg0, 97, Val(0));
  set(ctx, arg0, 98, Val(0));
  set(ctx, arg0, 99, Val(0));
  set(ctx, arg0, 100, Val(0));
  set(ctx, arg0, 101, Val(0));
  set(ctx, arg0, 102, Val(0));
  set(ctx, arg0, 103, Val(0));
  set(ctx, arg0, 104, Val(0));
  set(ctx, arg0, 105, Val(0));
  set(ctx, arg0, 106, Val(0));
  set(ctx, arg0, 107, Val(0));
  set(ctx, arg0, 108, Val(0));
  set(ctx, arg0, 109, Val(0));
  set(ctx, arg0, 110, Val(0));
  set(ctx, arg0, 111, Val(0));
  set(ctx, arg0, 112, Val(0));
  set(ctx, arg0, 113, Val(0));
  set(ctx, arg0, 114, Val(0));
  set(ctx, arg0, 115, Val(0));
  set(ctx, arg0, 116, Val(0));
  set(ctx, arg0, 117, Val(0));
  set(ctx, arg0, 118, Val(0));
  set(ctx, arg0, 119, Val(0));
  set(ctx, arg0, 120, Val(0));
  set(ctx, arg0, 121, Val(0));
  set(ctx, arg0, 122, Val(0));
  set(ctx, arg0, 123, Val(0));
  set(ctx, arg0, 124, Val(0));
  set(ctx, arg0, 125, Val(0));
  set(ctx, arg0, 126, Val(0));
  set(ctx, arg0, 127, Val(0));
  set(ctx, arg0, 128, Val(0));
  set(ctx, arg0, 129, Val(0));
  set(ctx, arg0, 130, Val(0));
  set(ctx, arg0, 131, Val(0));
  set(ctx, arg0, 132, Val(0));
  set(ctx, arg0, 133, Val(0));
  set(ctx, arg0, 134, Val(0));
  set(ctx, arg0, 135, Val(0));
  set(ctx, arg0, 136, Val(0));
  set(ctx, arg0, 137, Val(0));
  set(ctx, arg0, 138, Val(0));
  set(ctx, arg0, 139, Val(0));
  set(ctx, arg0, 140, Val(0));
  set(ctx, arg0, 141, Val(0));
  set(ctx, arg0, 142, Val(0));
  set(ctx, arg0, 143, Val(0));
  set(ctx, arg0, 144, Val(0));
  set(ctx, arg0, 145, Val(0));
  set(ctx, arg0, 146, Val(0));
  set(ctx, arg0, 147, Val(0));
  set(ctx, arg0, 148, Val(0));
  set(ctx, arg0, 149, Val(0));
  set(ctx, arg0, 150, Val(0));
  set(ctx, arg0, 151, Val(0));
  set(ctx, arg0, 152, Val(0));
  set(ctx, arg0, 153, Val(0));
  set(ctx, arg0, 154, Val(0));
  set(ctx, arg0, 155, Val(0));
  set(ctx, arg0, 156, Val(0));
  set(ctx, arg0, 157, Val(0));
  set(ctx, arg0, 158, Val(0));
  set(ctx, arg0, 159, Val(0));
  set(ctx, arg0, 160, Val(0));
  set(ctx, arg0, 161, Val(0));
  set(ctx, arg0, 162, Val(0));
  set(ctx, arg0, 163, Val(0));
  set(ctx, arg0, 164, Val(0));
  set(ctx, arg0, 165, Val(0));
  set(ctx, arg0, 166, Val(0));
  set(ctx, arg0, 167, Val(0));
  set(ctx, arg0, 168, Val(0));
  set(ctx, arg0, 169, Val(0));
  set(ctx, arg0, 170, Val(0));
  set(ctx, arg0, 171, Val(0));
  set(ctx, arg0, 172, Val(0));
  set(ctx, arg0, 173, Val(0));
  set(ctx, arg0, 174, Val(0));
  set(ctx, arg0, 175, Val(0));
  set(ctx, arg0, 176, Val(0));
  set(ctx, arg0, 177, Val(0));
  set(ctx, arg0, 178, Val(0));
  set(ctx, arg0, 179, Val(0));
  set(ctx, arg0, 180, Val(0));
  set(ctx, arg0, 181, Val(0));
  set(ctx, arg0, 182, Val(0));
  set(ctx, arg0, 183, Val(0));
  set(ctx, arg0, 184, Val(0));
  set(ctx, arg0, 185, Val(0));
  set(ctx, arg0, 186, Val(0));
  set(ctx, arg0, 187, Val(0));
  set(ctx, arg0, 188, Val(0));
  set(ctx, arg0, 189, Val(0));
  set(ctx, arg0, 190, Val(0));
  set(ctx, arg0, 191, Val(0));
  set(ctx, arg0, 192, Val(0));
  set(ctx, arg0, 193, Val(0));
  set(ctx, arg0, 194, Val(0));
  set(ctx, arg0, 195, Val(0));
  set(ctx, arg0, 196, Val(0));
  set(ctx, arg0, 197, Val(0));
  set(ctx, arg0, 198, Val(0));
  set(ctx, arg0, 199, Val(0));
  set(ctx, arg0, 200, Val(0));
  set(ctx, arg0, 201, Val(0));
  set(ctx, arg0, 202, Val(0));
  set(ctx, arg0, 203, Val(0));
  set(ctx, arg0, 204, Val(0));
  set(ctx, arg0, 205, Val(0));
  set(ctx, arg0, 206, Val(0));
  set(ctx, arg0, 207, Val(0));
  set(ctx, arg0, 208, Val(0));
  set(ctx, arg0, 209, Val(0));
  set(ctx, arg0, 210, Val(0));
  set(ctx, arg0, 211, Val(0));
  set(ctx, arg0, 212, Val(0));
  set(ctx, arg0, 213, Val(0));
  set(ctx, arg0, 214, Val(0));
  set(ctx, arg0, 215, Val(0));
  set(ctx, arg0, 216, Val(0));
  set(ctx, arg0, 217, Val(0));
  set(ctx, arg0, 218, Val(0));
  set(ctx, arg0, 219, Val(0));
  set(ctx, arg0, 220, Val(0));
  set(ctx, arg0, 221, Val(0));
  set(ctx, arg0, 222, Val(0));
  set(ctx, arg0, 223, Val(0));
  set(ctx, arg0, 224, Val(0));
  set(ctx, arg0, 225, Val(0));
  set(ctx, arg0, 226, Val(0));
  set(ctx, arg0, 227, Val(0));
  set(ctx, arg0, 228, Val(0));
  set(ctx, arg0, 229, Val(0));
  set(ctx, arg0, 230, Val(0));
  set(ctx, arg0, 231, Val(0));
  set(ctx, arg0, 232, Val(0));
  set(ctx, arg0, 233, Val(0));
  set(ctx, arg0, 234, Val(0));
  set(ctx, arg0, 235, Val(0));
  set(ctx, arg0, 236, Val(0));
  set(ctx, arg0, 237, Val(0));
  set(ctx, arg0, 238, Val(0));
  set(ctx, arg0, 239, Val(0));
  set(ctx, arg0, 240, Val(0));
  set(ctx, arg0, 241, Val(0));
  set(ctx, arg0, 242, Val(0));
  set(ctx, arg0, 243, Val(0));
  set(ctx, arg0, 244, Val(0));
  set(ctx, arg0, 245, Val(0));
  set(ctx, arg0, 246, Val(0));
  set(ctx, arg0, 247, Val(0));
  set(ctx, arg0, 248, Val(0));
  set(ctx, arg0, 249, Val(0));
  set(ctx, arg0, 250, Val(0));
  set(ctx, arg0, 251, Val(0));
  set(ctx, arg0, 252, Val(0));
  set(ctx, arg0, 253, Val(0));
  set(ctx, arg0, 254, Val(0));
  set(ctx, arg0, 255, Val(0));
  set(ctx, arg0, 256, Val(0));
  set(ctx, arg0, 257, Val(0));
  set(ctx, arg0, 258, Val(0));
  set(ctx, arg0, 259, Val(0));
  set(ctx, arg0, 260, Val(0));
  set(ctx, arg0, 261, Val(0));
  set(ctx, arg0, 262, Val(0));
  set(ctx, arg0, 263, Val(0));
  set(ctx, arg0, 264, Val(0));
  set(ctx, arg0, 265, Val(0));
  set(ctx, arg0, 266, Val(0));
  set(ctx, arg0, 267, Val(0));
  set(ctx, arg0, 268, Val(0));
  set(ctx, arg0, 269, Val(0));
  set(ctx, arg0, 270, Val(0));
  set(ctx, arg0, 271, Val(0));
  set(ctx, arg0, 272, Val(0));
  set(ctx, arg0, 273, Val(0));
  set(ctx, arg0, 274, Val(0));
  set(ctx, arg0, 275, Val(0));
  set(ctx, arg0, 276, Val(0));
  set(ctx, arg0, 277, Val(0));
  set(ctx, arg0, 278, Val(0));
  set(ctx, arg0, 279, Val(0));
  set(ctx, arg0, 280, Val(0));
  set(ctx, arg0, 281, Val(0));
  set(ctx, arg0, 282, Val(0));
  set(ctx, arg0, 283, Val(0));
  set(ctx, arg0, 284, Val(0));
  set(ctx, arg0, 285, Val(0));
  set(ctx, arg0, 286, Val(0));
  set(ctx, arg0, 287, Val(0));
  set(ctx, arg0, 288, Val(0));
  set(ctx, arg0, 289, Val(0));
  set(ctx, arg0, 290, Val(0));
  set(ctx, arg0, 291, Val(0));
  set(ctx, arg0, 292, Val(0));
  set(ctx, arg0, 293, Val(0));
  set(ctx, arg0, 294, Val(0));
  set(ctx, arg0, 295, Val(0));
  set(ctx, arg0, 296, Val(0));
  set(ctx, arg0, 297, Val(0));
  set(ctx, arg0, 298, Val(0));
  set(ctx, arg0, 299, Val(0));
  set(ctx, arg0, 300, Val(0));
  set(ctx, arg0, 301, Val(0));
  set(ctx, arg0, 302, Val(0));
  set(ctx, arg0, 303, Val(0));
  set(ctx, arg0, 304, Val(0));
  set(ctx, arg0, 305, Val(0));
  set(ctx, arg0, 306, Val(0));
  set(ctx, arg0, 307, Val(0));
  set(ctx, arg0, 308, Val(0));
  set(ctx, arg0, 309, Val(0));
  set(ctx, arg0, 310, Val(0));
  set(ctx, arg0, 311, Val(0));
  set(ctx, arg0, 312, Val(0));
  set(ctx, arg0, 313, Val(0));
  set(ctx, arg0, 314, Val(0));
  set(ctx, arg0, 315, Val(0));
  set(ctx, arg0, 316, Val(0));
  set(ctx, arg0, 317, Val(0));
  set(ctx, arg0, 318, Val(0));
  set(ctx, arg0, 319, Val(0));
  set(ctx, arg0, 320, Val(0));
  set(ctx, arg0, 321, Val(0));
  set(ctx, arg0, 322, Val(0));
  set(ctx, arg0, 323, Val(0));
  set(ctx, arg0, 324, Val(0));
  set(ctx, arg0, 325, Val(0));
  set(ctx, arg0, 326, Val(0));
  set(ctx, arg0, 327, Val(0));
  set(ctx, arg0, 328, Val(0));
  set(ctx, arg0, 329, Val(0));
  set(ctx, arg0, 330, Val(0));
  set(ctx, arg0, 331, Val(0));
  set(ctx, arg0, 332, Val(0));
  set(ctx, arg0, 333, Val(0));
  set(ctx, arg0, 334, Val(0));
  set(ctx, arg0, 335, Val(0));
  set(ctx, arg0, 336, Val(0));
  set(ctx, arg0, 337, Val(0));
  set(ctx, arg0, 338, Val(0));
  set(ctx, arg0, 339, Val(0));
  set(ctx, arg0, 340, Val(0));
  set(ctx, arg0, 341, Val(0));
  set(ctx, arg0, 342, Val(0));
  set(ctx, arg0, 343, Val(0));
  set(ctx, arg0, 344, Val(0));
  set(ctx, arg0, 345, Val(0));
  set(ctx, arg0, 346, Val(0));
  set(ctx, arg0, 347, Val(0));
  set(ctx, arg0, 348, Val(0));
  set(ctx, arg0, 349, Val(0));
  set(ctx, arg0, 350, Val(0));
  set(ctx, arg0, 351, Val(0));
  set(ctx, arg0, 352, Val(0));
  set(ctx, arg0, 353, Val(0));
  set(ctx, arg0, 354, Val(0));
  set(ctx, arg0, 355, Val(0));
  set(ctx, arg0, 356, Val(0));
  set(ctx, arg0, 357, Val(0));
  set(ctx, arg0, 358, Val(0));
  set(ctx, arg0, 359, Val(0));
  set(ctx, arg0, 360, Val(0));
  set(ctx, arg0, 361, Val(0));
  set(ctx, arg0, 362, Val(0));
  set(ctx, arg0, 363, Val(0));
  set(ctx, arg0, 364, Val(0));
  set(ctx, arg0, 365, Val(0));
  set(ctx, arg0, 366, Val(0));
  set(ctx, arg0, 367, Val(0));
  set(ctx, arg0, 368, Val(0));
  set(ctx, arg0, 369, Val(0));
  set(ctx, arg0, 370, Val(0));
  set(ctx, arg0, 371, Val(0));
  set(ctx, arg0, 372, Val(0));
  set(ctx, arg0, 373, Val(0));
  set(ctx, arg0, 374, Val(0));
  set(ctx, arg0, 375, Val(0));
  set(ctx, arg0, 376, Val(0));
  set(ctx, arg0, 377, Val(0));
  set(ctx, arg0, 378, Val(0));
  set(ctx, arg0, 379, Val(0));
  set(ctx, arg0, 380, Val(0));
  set(ctx, arg0, 381, Val(0));
  set(ctx, arg0, 382, Val(0));
  set(ctx, arg0, 383, Val(0));
  set(ctx, arg0, 384, Val(0));
  set(ctx, arg0, 385, Val(0));
  set(ctx, arg0, 386, Val(0));
  set(ctx, arg0, 387, Val(0));
  set(ctx, arg0, 388, Val(0));
  set(ctx, arg0, 389, Val(0));
  set(ctx, arg0, 390, Val(0));
  set(ctx, arg0, 391, Val(0));
  set(ctx, arg0, 392, Val(0));
  set(ctx, arg0, 393, Val(0));
  set(ctx, arg0, 394, Val(0));
  set(ctx, arg0, 395, Val(0));
  set(ctx, arg0, 396, Val(0));
  set(ctx, arg0, 397, Val(0));
  set(ctx, arg0, 398, Val(0));
  set(ctx, arg0, 399, Val(0));
  set(ctx, arg0, 400, Val(0));
  set(ctx, arg0, 401, Val(0));
  set(ctx, arg0, 402, Val(0));
  set(ctx, arg0, 403, Val(0));
  set(ctx, arg0, 404, Val(0));
  set(ctx, arg0, 405, Val(0));
  set(ctx, arg0, 406, Val(0));
  set(ctx, arg0, 407, Val(0));
  set(ctx, arg0, 408, Val(0));
  set(ctx, arg0, 409, Val(0));
  set(ctx, arg0, 410, Val(0));
  set(ctx, arg0, 411, Val(0));
  set(ctx, arg0, 412, Val(0));
  set(ctx, arg0, 413, Val(0));
  set(ctx, arg0, 414, Val(0));
  set(ctx, arg0, 415, Val(0));
  set(ctx, arg0, 416, Val(0));
  set(ctx, arg0, 417, Val(0));
  set(ctx, arg0, 418, Val(0));
  set(ctx, arg0, 419, Val(0));
  set(ctx, arg0, 420, Val(0));
  set(ctx, arg0, 421, Val(0));
  set(ctx, arg0, 422, Val(0));
  set(ctx, arg0, 423, Val(0));
  set(ctx, arg0, 424, Val(0));
  set(ctx, arg0, 425, Val(0));
  set(ctx, arg0, 426, Val(0));
  set(ctx, arg0, 427, Val(0));
  set(ctx, arg0, 428, Val(0));
  set(ctx, arg0, 429, Val(0));
  set(ctx, arg0, 430, Val(0));
  set(ctx, arg0, 431, Val(0));
  set(ctx, arg0, 432, Val(0));
  set(ctx, arg0, 433, Val(0));
  set(ctx, arg0, 434, Val(0));
  set(ctx, arg0, 435, Val(0));
  set(ctx, arg0, 436, Val(0));
  set(ctx, arg0, 437, Val(0));
  set(ctx, arg0, 438, Val(0));
  set(ctx, arg0, 439, Val(0));
  set(ctx, arg0, 440, Val(0));
  set(ctx, arg0, 441, Val(0));
  set(ctx, arg0, 442, Val(0));
  set(ctx, arg0, 443, Val(0));
  set(ctx, arg0, 444, Val(0));
  set(ctx, arg0, 445, Val(0));
  set(ctx, arg0, 446, Val(0));
  set(ctx, arg0, 447, Val(0));
  set(ctx, arg0, 448, Val(0));
  set(ctx, arg0, 449, Val(0));
  set(ctx, arg0, 450, Val(0));
  set(ctx, arg0, 451, Val(0));
  set(ctx, arg0, 452, Val(0));
  set(ctx, arg0, 453, Val(0));
  set(ctx, arg0, 454, Val(0));
  set(ctx, arg0, 455, Val(0));
  set(ctx, arg0, 456, Val(0));
  set(ctx, arg0, 457, Val(0));
  set(ctx, arg0, 458, Val(0));
  set(ctx, arg0, 459, Val(0));
  set(ctx, arg0, 460, Val(0));
  set(ctx, arg0, 461, Val(0));
  set(ctx, arg0, 462, Val(0));
  set(ctx, arg0, 463, Val(0));
  set(ctx, arg0, 464, Val(0));
  set(ctx, arg0, 465, Val(0));
  set(ctx, arg0, 466, Val(0));
  set(ctx, arg0, 467, Val(0));
  set(ctx, arg0, 468, Val(0));
  set(ctx, arg0, 469, Val(0));
  set(ctx, arg0, 470, Val(0));
  set(ctx, arg0, 471, Val(0));
  set(ctx, arg0, 472, Val(0));
  set(ctx, arg0, 473, Val(0));
  set(ctx, arg0, 474, Val(0));
  set(ctx, arg0, 475, Val(0));
  set(ctx, arg0, 476, Val(0));
  set(ctx, arg0, 477, Val(0));
  set(ctx, arg0, 478, Val(0));
  set(ctx, arg0, 479, Val(0));
  set(ctx, arg0, 480, Val(0));
  set(ctx, arg0, 481, Val(0));
  set(ctx, arg0, 482, Val(0));
  set(ctx, arg0, 483, Val(0));
  set(ctx, arg0, 484, Val(0));
  set(ctx, arg0, 485, Val(0));
  set(ctx, arg0, 486, Val(0));
  set(ctx, arg0, 487, Val(0));
  set(ctx, arg0, 488, Val(0));
  set(ctx, arg0, 489, Val(0));
  set(ctx, arg0, 490, Val(0));
  set(ctx, arg0, 491, Val(0));
  set(ctx, arg0, 492, Val(0));
  set(ctx, arg0, 493, Val(0));
  set(ctx, arg0, 494, Val(0));
  set(ctx, arg0, 495, Val(0));
  set(ctx, arg0, 496, Val(0));
  set(ctx, arg0, 497, Val(0));
  set(ctx, arg0, 498, Val(0));
  set(ctx, arg0, 499, Val(0));
  set(ctx, arg0, 500, Val(0));
  set(ctx, arg0, 501, Val(0));
  set(ctx, arg0, 502, Val(0));
  set(ctx, arg0, 503, Val(0));
  set(ctx, arg0, 504, Val(0));
  set(ctx, arg0, 505, Val(0));
  set(ctx, arg0, 506, Val(0));
  set(ctx, arg0, 507, Val(0));
  set(ctx, arg0, 508, Val(0));
  set(ctx, arg0, 509, Val(0));
  set(ctx, arg0, 510, Val(0));
  set(ctx, arg0, 511, Val(0));
  set(ctx, arg0, 512, Val(0));
  set(ctx, arg0, 513, Val(0));
  set(ctx, arg0, 514, Val(0));
  set(ctx, arg0, 515, Val(0));
  set(ctx, arg0, 516, Val(0));
  set(ctx, arg0, 517, Val(0));
  set(ctx, arg0, 518, Val(0));
  set(ctx, arg0, 519, Val(0));
  set(ctx, arg0, 520, Val(0));
  set(ctx, arg0, 521, Val(0));
  set(ctx, arg0, 522, Val(0));
  set(ctx, arg0, 523, Val(0));
  set(ctx, arg0, 524, Val(0));
  set(ctx, arg0, 525, Val(0));
  set(ctx, arg0, 526, Val(0));
  set(ctx, arg0, 527, Val(0));
  set(ctx, arg0, 528, Val(0));
  set(ctx, arg0, 529, Val(0));
  set(ctx, arg0, 530, Val(0));
  set(ctx, arg0, 531, Val(0));
  set(ctx, arg0, 532, Val(0));
  set(ctx, arg0, 533, Val(0));
  set(ctx, arg0, 534, Val(0));
  set(ctx, arg0, 535, Val(0));
  set(ctx, arg0, 536, Val(0));
  set(ctx, arg0, 537, Val(0));
  set(ctx, arg0, 538, Val(0));
  set(ctx, arg0, 539, Val(0));
  set(ctx, arg0, 540, Val(0));
  set(ctx, arg0, 541, Val(0));
  set(ctx, arg0, 542, Val(0));
  set(ctx, arg0, 543, Val(0));
  set(ctx, arg0, 544, Val(0));
  set(ctx, arg0, 545, Val(0));
  set(ctx, arg0, 546, Val(0));
  set(ctx, arg0, 547, Val(0));
  set(ctx, arg0, 548, Val(0));
  set(ctx, arg0, 549, Val(0));
  set(ctx, arg0, 550, Val(0));
  set(ctx, arg0, 551, Val(0));
  set(ctx, arg0, 552, Val(0));
  set(ctx, arg0, 553, Val(0));
  set(ctx, arg0, 554, Val(0));
  set(ctx, arg0, 555, Val(0));
  set(ctx, arg0, 556, Val(0));
  set(ctx, arg0, 557, Val(0));
  set(ctx, arg0, 558, Val(0));
  set(ctx, arg0, 559, Val(0));
  set(ctx, arg0, 560, Val(0));
  set(ctx, arg0, 561, Val(0));
  set(ctx, arg0, 562, Val(0));
  set(ctx, arg0, 563, Val(0));
  set(ctx, arg0, 564, Val(0));
  set(ctx, arg0, 565, Val(0));
  set(ctx, arg0, 566, Val(0));
  set(ctx, arg0, 567, Val(0));
  set(ctx, arg0, 568, Val(0));
  set(ctx, arg0, 569, Val(0));
  set(ctx, arg0, 570, Val(0));
  set(ctx, arg0, 571, Val(0));
  set(ctx, arg0, 572, Val(0));
  set(ctx, arg0, 573, Val(0));
  set(ctx, arg0, 574, Val(0));
  set(ctx, arg0, 575, Val(0));
  set(ctx, arg0, 576, Val(0));
  set(ctx, arg0, 577, Val(0));
  set(ctx, arg0, 578, Val(0));
  set(ctx, arg0, 579, Val(0));
  set(ctx, arg0, 580, Val(0));
  set(ctx, arg0, 581, Val(0));
  set(ctx, arg0, 582, Val(0));
  set(ctx, arg0, 583, Val(0));
  set(ctx, arg0, 584, Val(0));
  set(ctx, arg0, 585, Val(0));
  set(ctx, arg0, 586, Val(0));
  set(ctx, arg0, 587, Val(0));
  set(ctx, arg0, 588, Val(0));
  set(ctx, arg0, 589, Val(0));
  set(ctx, arg0, 590, Val(0));
  set(ctx, arg0, 591, Val(0));
  set(ctx, arg0, 592, Val(0));
  set(ctx, arg0, 593, Val(0));
  set(ctx, arg0, 594, Val(0));
  set(ctx, arg0, 595, Val(0));
  set(ctx, arg0, 596, Val(0));
  set(ctx, arg0, 597, Val(0));
  set(ctx, arg0, 598, Val(0));
  set(ctx, arg0, 599, Val(0));
  set(ctx, arg0, 600, Val(0));
  set(ctx, arg0, 601, Val(0));
  set(ctx, arg0, 602, Val(0));
  set(ctx, arg0, 603, Val(0));
  set(ctx, arg0, 604, Val(0));
  set(ctx, arg0, 605, Val(0));
  set(ctx, arg0, 606, Val(0));
  set(ctx, arg0, 607, Val(0));
  set(ctx, arg0, 608, Val(0));
  set(ctx, arg0, 609, Val(0));
  set(ctx, arg0, 610, Val(0));
  set(ctx, arg0, 611, Val(0));
  set(ctx, arg0, 612, Val(0));
  set(ctx, arg0, 613, Val(0));
  set(ctx, arg0, 614, Val(0));
  set(ctx, arg0, 615, Val(0));
  set(ctx, arg0, 616, Val(0));
  set(ctx, arg0, 617, Val(0));
  set(ctx, arg0, 618, Val(0));
  set(ctx, arg0, 619, Val(0));
  set(ctx, arg0, 620, Val(0));
  set(ctx, arg0, 621, Val(0));
  set(ctx, arg0, 622, Val(0));
  set(ctx, arg0, 623, Val(0));
  set(ctx, arg0, 624, Val(0));
  set(ctx, arg0, 625, Val(0));
  set(ctx, arg0, 626, Val(0));
  set(ctx, arg0, 627, Val(0));
  set(ctx, arg0, 628, Val(0));
  set(ctx, arg0, 629, Val(0));
  set(ctx, arg0, 630, Val(0));
  set(ctx, arg0, 631, Val(0));
  set(ctx, arg0, 632, Val(0));
  set(ctx, arg0, 633, Val(0));
  set(ctx, arg0, 634, Val(0));
  set(ctx, arg0, 635, Val(0));
  set(ctx, arg0, 636, Val(0));
  set(ctx, arg0, 637, Val(0));
  set(ctx, arg0, 638, Val(0));
  set(ctx, arg0, 639, Val(0));
  set(ctx, arg0, 640, Val(0));
  set(ctx, arg0, 641, Val(0));
  set(ctx, arg0, 642, Val(0));
  set(ctx, arg0, 643, Val(0));
  set(ctx, arg0, 644, Val(0));
  set(ctx, arg0, 645, Val(0));
  set(ctx, arg0, 646, Val(0));
  set(ctx, arg0, 647, Val(0));
  set(ctx, arg0, 648, Val(0));
  set(ctx, arg0, 649, Val(0));
  set(ctx, arg0, 650, Val(0));
  set(ctx, arg0, 651, Val(0));
  set(ctx, arg0, 652, Val(0));
  set(ctx, arg0, 653, Val(0));
  set(ctx, arg0, 654, Val(0));
  set(ctx, arg0, 655, Val(0));
  set(ctx, arg0, 656, Val(0));
  set(ctx, arg0, 657, Val(0));
  set(ctx, arg0, 658, Val(0));
  set(ctx, arg0, 659, Val(0));
  set(ctx, arg0, 660, Val(0));
  set(ctx, arg0, 661, Val(0));
  set(ctx, arg0, 662, Val(0));
  set(ctx, arg0, 663, Val(0));
  set(ctx, arg0, 664, Val(0));
  set(ctx, arg0, 665, Val(0));
  set(ctx, arg0, 666, Val(0));
  set(ctx, arg0, 667, Val(0));
  set(ctx, arg0, 668, Val(0));
  set(ctx, arg0, 669, Val(0));
  set(ctx, arg0, 670, Val(0));
  set(ctx, arg0, 671, Val(0));
  set(ctx, arg0, 672, Val(0));
  set(ctx, arg0, 673, Val(0));
  set(ctx, arg0, 674, Val(0));
  set(ctx, arg0, 675, Val(0));
  set(ctx, arg0, 676, Val(0));
  set(ctx, arg0, 677, Val(0));
  set(ctx, arg0, 678, Val(0));
  set(ctx, arg0, 679, Val(0));
  set(ctx, arg0, 680, Val(0));
  set(ctx, arg0, 681, Val(0));
  set(ctx, arg0, 682, Val(0));
  set(ctx, arg0, 683, Val(0));
  set(ctx, arg0, 684, Val(0));
  set(ctx, arg0, 685, Val(0));
  set(ctx, arg0, 686, Val(0));
  set(ctx, arg0, 687, Val(0));
  set(ctx, arg0, 688, Val(0));
  set(ctx, arg0, 689, Val(0));
  set(ctx, arg0, 690, Val(0));
  set(ctx, arg0, 691, Val(0));
  set(ctx, arg0, 692, Val(0));
  set(ctx, arg0, 693, Val(0));
  set(ctx, arg0, 694, Val(0));
  set(ctx, arg0, 695, Val(0));
  set(ctx, arg0, 696, Val(0));
  set(ctx, arg0, 697, Val(0));
  set(ctx, arg0, 698, Val(0));
  set(ctx, arg0, 699, Val(0));
  set(ctx, arg0, 700, Val(0));
  set(ctx, arg0, 701, Val(0));
  set(ctx, arg0, 702, Val(0));
  set(ctx, arg0, 703, Val(0));
  set(ctx, arg0, 704, Val(0));
  set(ctx, arg0, 705, Val(0));
  set(ctx, arg0, 706, Val(0));
  set(ctx, arg0, 707, Val(0));
  set(ctx, arg0, 708, Val(0));
  set(ctx, arg0, 709, Val(0));
  set(ctx, arg0, 710, Val(0));
  set(ctx, arg0, 711, Val(0));
  set(ctx, arg0, 712, Val(0));
  set(ctx, arg0, 713, Val(0));
  set(ctx, arg0, 714, Val(0));
  set(ctx, arg0, 715, Val(0));
  set(ctx, arg0, 716, Val(0));
  set(ctx, arg0, 717, Val(0));
  set(ctx, arg0, 718, Val(0));
  set(ctx, arg0, 719, Val(0));
  set(ctx, arg0, 720, Val(0));
  set(ctx, arg0, 721, Val(0));
  set(ctx, arg0, 722, Val(0));
  set(ctx, arg0, 723, Val(0));
  set(ctx, arg0, 724, Val(0));
  set(ctx, arg0, 725, Val(0));
  set(ctx, arg0, 726, Val(0));
  set(ctx, arg0, 727, Val(0));
  set(ctx, arg0, 728, Val(0));
  set(ctx, arg0, 729, Val(0));
  set(ctx, arg0, 730, Val(0));
  set(ctx, arg0, 731, Val(0));
  set(ctx, arg0, 732, Val(0));
  set(ctx, arg0, 733, Val(0));
  set(ctx, arg0, 734, Val(0));
  set(ctx, arg0, 735, Val(0));
  set(ctx, arg0, 736, Val(0));
  set(ctx, arg0, 737, Val(0));
  set(ctx, arg0, 738, Val(0));
  set(ctx, arg0, 739, Val(0));
  set(ctx, arg0, 740, Val(0));
  set(ctx, arg0, 741, Val(0));
  set(ctx, arg0, 742, Val(0));
  set(ctx, arg0, 743, Val(0));
  set(ctx, arg0, 744, Val(0));
  set(ctx, arg0, 745, Val(0));
  set(ctx, arg0, 746, Val(0));
  set(ctx, arg0, 747, Val(0));
  set(ctx, arg0, 748, Val(0));
  set(ctx, arg0, 749, Val(0));
  set(ctx, arg0, 750, Val(0));
  set(ctx, arg0, 751, Val(0));
  set(ctx, arg0, 752, Val(0));
  set(ctx, arg0, 753, Val(0));
  set(ctx, arg0, 754, Val(0));
  set(ctx, arg0, 755, Val(0));
  set(ctx, arg0, 756, Val(0));
  set(ctx, arg0, 757, Val(0));
  set(ctx, arg0, 758, Val(0));
  set(ctx, arg0, 759, Val(0));
  set(ctx, arg0, 760, Val(0));
  set(ctx, arg0, 761, Val(0));
  set(ctx, arg0, 762, Val(0));
  set(ctx, arg0, 763, Val(0));
  set(ctx, arg0, 764, Val(0));
  set(ctx, arg0, 765, Val(0));
  set(ctx, arg0, 766, Val(0));
  set(ctx, arg0, 767, Val(0));
  set(ctx, arg0, 768, Val(0));
  set(ctx, arg0, 769, Val(0));
  set(ctx, arg0, 770, Val(0));
  set(ctx, arg0, 771, Val(0));
  set(ctx, arg0, 772, Val(0));
  set(ctx, arg0, 773, Val(0));
  set(ctx, arg0, 774, Val(0));
  set(ctx, arg0, 775, Val(0));
  set(ctx, arg0, 776, Val(0));
  set(ctx, arg0, 777, Val(0));
  set(ctx, arg0, 778, Val(0));
  set(ctx, arg0, 779, Val(0));
  set(ctx, arg0, 780, Val(0));
  set(ctx, arg0, 781, Val(0));
  set(ctx, arg0, 782, Val(0));
  set(ctx, arg0, 783, Val(0));
  set(ctx, arg0, 784, Val(0));
  set(ctx, arg0, 785, Val(0));
  set(ctx, arg0, 786, Val(0));
  set(ctx, arg0, 787, Val(0));
  set(ctx, arg0, 788, Val(0));
  set(ctx, arg0, 789, Val(0));
  set(ctx, arg0, 790, Val(0));
  set(ctx, arg0, 791, Val(0));
  set(ctx, arg0, 792, Val(0));
  set(ctx, arg0, 793, Val(0));
  set(ctx, arg0, 794, Val(0));
  set(ctx, arg0, 795, Val(0));
  set(ctx, arg0, 796, Val(0));
  set(ctx, arg0, 797, Val(0));
  set(ctx, arg0, 798, Val(0));
  set(ctx, arg0, 799, Val(0));
  set(ctx, arg0, 800, Val(0));
  set(ctx, arg0, 801, Val(0));
  set(ctx, arg0, 802, Val(0));
  set(ctx, arg0, 803, Val(0));
  set(ctx, arg0, 804, Val(0));
  set(ctx, arg0, 805, Val(0));
  set(ctx, arg0, 806, Val(0));
  set(ctx, arg0, 807, Val(0));
  set(ctx, arg0, 808, Val(0));
  set(ctx, arg0, 809, Val(0));
  set(ctx, arg0, 810, Val(0));
  set(ctx, arg0, 811, Val(0));
  set(ctx, arg0, 812, Val(0));
  set(ctx, arg0, 813, Val(0));
  set(ctx, arg0, 814, Val(0));
  set(ctx, arg0, 815, Val(0));
  // TopState(zirgen/circuit/keccak/top.zir:40)
  set(ctx, arg0, 816, Val(0));
  set(ctx, arg0, 817, Val(0));
  set(ctx, arg0, 818, Val(0));
  set(ctx, arg0, 819, Val(0));
  set(ctx, arg0, 820, Val(0));
  set(ctx, arg0, 821, Val(0));
  set(ctx, arg0, 822, Val(0));
  set(ctx, arg0, 823, Val(0));
  set(ctx, arg0, 824, Val(0));
  set(ctx, arg0, 825, Val(0));
  set(ctx, arg0, 826, Val(0));
  set(ctx, arg0, 827, Val(0));
  set(ctx, arg0, 828, Val(0));
  set(ctx, arg0, 829, Val(0));
  set(ctx, arg0, 830, Val(0));
  set(ctx, arg0, 831, Val(0));
  set(ctx, arg0, 832, Val(0));
  set(ctx, arg0, 833, Val(0));
  set(ctx, arg0, 834, Val(0));
  set(ctx, arg0, 835, Val(0));
  set(ctx, arg0, 836, Val(0));
  set(ctx, arg0, 837, Val(0));
  set(ctx, arg0, 838, Val(0));
  set(ctx, arg0, 839, Val(0));
  set(ctx, arg0, 840, Val(0));
  set(ctx, arg0, 841, Val(0));
  set(ctx, arg0, 842, Val(0));
  set(ctx, arg0, 843, Val(0));
  set(ctx, arg0, 844, Val(0));
  set(ctx, arg0, 845, Val(0));
  set(ctx, arg0, 846, Val(0));
  set(ctx, arg0, 847, Val(0));
  set(ctx, arg0, 848, Val(0));
  set(ctx, arg0, 849, Val(0));
  set(ctx, arg0, 850, Val(0));
  set(ctx, arg0, 851, Val(0));
  set(ctx, arg0, 852, Val(0));
  set(ctx, arg0, 853, Val(0));
  set(ctx, arg0, 854, Val(0));
  set(ctx, arg0, 855, Val(0));
  set(ctx, arg0, 856, Val(0));
  set(ctx, arg0, 857, Val(0));
  set(ctx, arg0, 858, Val(0));
  set(ctx, arg0, 859, Val(0));
  set(ctx, arg0, 860, Val(0));
  set(ctx, arg0, 861, Val(0));
  set(ctx, arg0, 862, Val(0));
  set(ctx, arg0, 863, Val(0));
  set(ctx, arg0, 864, Val(0));
  set(ctx, arg0, 865, Val(0));
  set(ctx, arg0, 866, Val(0));
  set(ctx, arg0, 867, Val(0));
  set(ctx, arg0, 868, Val(0));
  set(ctx, arg0, 869, Val(0));
  set(ctx, arg0, 870, Val(0));
  set(ctx, arg0, 871, Val(0));
  set(ctx, arg0, 872, Val(0));
  set(ctx, arg0, 873, Val(0));
  set(ctx, arg0, 874, Val(0));
  set(ctx, arg0, 875, Val(0));
  set(ctx, arg0, 876, Val(0));
  set(ctx, arg0, 877, Val(0));
  set(ctx, arg0, 878, Val(0));
  set(ctx, arg0, 879, Val(0));
  set(ctx, arg0, 880, Val(0));
  set(ctx, arg0, 881, Val(0));
  set(ctx, arg0, 882, Val(0));
  set(ctx, arg0, 883, Val(0));
  set(ctx, arg0, 884, Val(0));
  set(ctx, arg0, 885, Val(0));
  set(ctx, arg0, 886, Val(0));
  set(ctx, arg0, 887, Val(0));
  set(ctx, arg0, 888, Val(0));
  set(ctx, arg0, 889, Val(0));
  set(ctx, arg0, 890, Val(0));
  set(ctx, arg0, 891, Val(0));
  set(ctx, arg0, 892, Val(0));
  set(ctx, arg0, 893, Val(0));
  set(ctx, arg0, 894, Val(0));
  set(ctx, arg0, 895, Val(0));
  set(ctx, arg0, 896, Val(0));
  set(ctx, arg0, 897, Val(0));
  set(ctx, arg0, 898, Val(0));
  set(ctx, arg0, 899, Val(0));
  set(ctx, arg0, 900, Val(0));
  set(ctx, arg0, 901, Val(0));
  set(ctx, arg0, 902, Val(0));
  set(ctx, arg0, 903, Val(0));
  set(ctx, arg0, 904, Val(0));
  set(ctx, arg0, 905, Val(0));
  set(ctx, arg0, 906, Val(0));
  set(ctx, arg0, 907, Val(0));
  set(ctx, arg0, 908, Val(0));
  set(ctx, arg0, 909, Val(0));
  set(ctx, arg0, 910, Val(0));
  set(ctx, arg0, 911, Val(0));
  set(ctx, arg0, 912, Val(0));
  set(ctx, arg0, 913, Val(0));
  set(ctx, arg0, 914, Val(0));
  set(ctx, arg0, 915, Val(0));
  // TopState(zirgen/circuit/keccak/top.zir:43)
  set(ctx, arg0, 916, x2);
  set(ctx, arg0, 917, x3);
  set(ctx, arg0, 918, x4);
  set(ctx, arg0, 919, x5);
  set(ctx, arg0, 920, x6);
  set(ctx, arg0, 921, x7);
  set(ctx, arg0, 922, x8);
  set(ctx, arg0, 923, x9);
  set(ctx, arg0, 924, x10);
  set(ctx, arg0, 925, x11);
  set(ctx, arg0, 926, x12);
  set(ctx, arg0, 927, x13);
  set(ctx, arg0, 928, x14);
  set(ctx, arg0, 929, x15);
  set(ctx, arg0, 930, x16);
  set(ctx, arg0, 931, x17);
  return;
}
__device__ void step_Top_41(ExecContext& ctx, MutableBuf arg0) {
  // TopState(zirgen/circuit/keccak/top.zir:36)
  // Top(zirgen/circuit/keccak/top.zir:501)
  Val x1 = get(ctx, arg0, 663, 2);
  Val x2 = get(ctx, arg0, 674, 2);
  Val x3 = get(ctx, arg0, 659, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x4 = (x2 * Val(2));
  // builtin Sub
  Val x5 = ((x2 + x3) - (x4 * x3));
  // builtin Mul
  Val x6 = (x1 * Val(2));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x7 = get(ctx, arg0, 664, 2);
  Val x8 = get(ctx, arg0, 675, 2);
  Val x9 = get(ctx, arg0, 660, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x10 = (x8 * Val(2));
  // builtin Sub
  Val x11 = ((x8 + x9) - (x10 * x9));
  // builtin Mul
  Val x12 = (x7 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x13 = (((x7 + x11) - (x12 * x11)) * Val(2));
  // builtin Add
  Val x14 = (((x1 + x5) - (x6 * x5)) + x13);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x15 = get(ctx, arg0, 665, 2);
  Val x16 = get(ctx, arg0, 676, 2);
  Val x17 = get(ctx, arg0, 661, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x18 = (x16 * Val(2));
  // builtin Sub
  Val x19 = ((x16 + x17) - (x18 * x17));
  // builtin Mul
  Val x20 = (x15 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x21 = (((x15 + x19) - (x20 * x19)) * Val(4));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x22 = get(ctx, arg0, 666, 2);
  Val x23 = get(ctx, arg0, 677, 2);
  Val x24 = get(ctx, arg0, 662, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x25 = (x23 * Val(2));
  // builtin Sub
  Val x26 = ((x23 + x24) - (x25 * x24));
  // builtin Mul
  Val x27 = (x22 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x28 = (((x22 + x26) - (x27 * x26)) * Val(8));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x29 = get(ctx, arg0, 667, 2);
  Val x30 = get(ctx, arg0, 678, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x31 = (x30 * Val(2));
  // builtin Sub
  Val x32 = ((x30 + x1) - (x31 * x1));
  // builtin Mul
  Val x33 = (x29 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x34 = (((x29 + x32) - (x33 * x32)) * Val(16));
  // builtin Add
  Val x35 = (((x14 + x21) + x28) + x34);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x36 = get(ctx, arg0, 668, 2);
  Val x37 = get(ctx, arg0, 679, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x38 = (x37 * Val(2));
  // builtin Sub
  Val x39 = ((x37 + x7) - (x38 * x7));
  // builtin Mul
  Val x40 = (x36 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x41 = (((x36 + x39) - (x40 * x39)) * Val(32));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x42 = get(ctx, arg0, 669, 2);
  Val x43 = get(ctx, arg0, 680, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x44 = (x43 * Val(2));
  // builtin Sub
  Val x45 = ((x43 + x15) - (x44 * x15));
  // builtin Mul
  Val x46 = (x42 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x47 = (((x42 + x45) - (x46 * x45)) * Val(64));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x48 = get(ctx, arg0, 670, 2);
  Val x49 = get(ctx, arg0, 681, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x50 = (x49 * Val(2));
  // builtin Sub
  Val x51 = ((x49 + x22) - (x50 * x22));
  // builtin Mul
  Val x52 = (x48 * Val(2));
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x53 = (((x48 + x51) - (x52 * x51)) * Val(128));
  // builtin Add
  Val x54 = (((x35 + x41) + x47) + x53);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x55 = get(ctx, arg0, 671, 2);
  Val x56 = get(ctx, arg0, 682, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x57 = (x56 * Val(2));
  // builtin Sub
  Val x58 = ((x56 + x29) - (x57 * x29));
  Val x59 = ((x55 + x58) - ((x55 * Val(2)) * x58));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x60 = get(ctx, arg0, 672, 2);
  Val x61 = get(ctx, arg0, 683, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x62 = (x61 * Val(2));
  // builtin Sub
  Val x63 = ((x61 + x36) - (x62 * x36));
  Val x64 = ((x60 + x63) - ((x60 * Val(2)) * x63));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x65 = get(ctx, arg0, 673, 2);
  Val x66 = get(ctx, arg0, 684, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x67 = (x66 * Val(2));
  // builtin Sub
  Val x68 = ((x66 + x42) - (x67 * x42));
  Val x69 = ((x65 + x68) - ((x65 * Val(2)) * x68));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x70 = (((x54 + (x59 * Val(256))) + (x64 * Val(512))) + (x69 * Val(1024)));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x71 = get(ctx, arg0, 685, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x72 = (x71 * Val(2));
  // builtin Sub
  Val x73 = ((x71 + x48) - (x72 * x48));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x74 = (((x2 + x73) - (x4 * x73)) * Val(2048));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x75 = get(ctx, arg0, 686, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x76 = (x75 * Val(2));
  // builtin Sub
  Val x77 = ((x75 + x55) - (x76 * x55));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x78 = (((x8 + x77) - (x10 * x77)) * Val(4096));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x79 = get(ctx, arg0, 687, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x80 = (x79 * Val(2));
  // builtin Sub
  Val x81 = ((x79 + x60) - (x80 * x60));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x82 = (((x16 + x81) - (x18 * x81)) * Val(8192));
  // builtin Add
  Val x83 = (((x70 + x74) + x78) + x82);
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x84 = get(ctx, arg0, 656, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x85 = (x84 * Val(2));
  // builtin Sub
  Val x86 = ((x84 + x65) - (x85 * x65));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x87 = (((x23 + x86) - (x25 * x86)) * Val(16384));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x88 = get(ctx, arg0, 657, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x89 = (x88 * Val(2));
  // builtin Sub
  Val x90 = ((x88 + x2) - (x89 * x2));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x91 = (((x30 + x90) - (x31 * x90)) * Val(32768));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x92 = get(ctx, arg0, 577, 0);
  Val x93 = get(ctx, arg0, 579, 0);
  Val x94 = get(ctx, arg0, 570, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x95 = (x93 * Val(2));
  // builtin Sub
  Val x96 = ((x93 + x94) - (x95 * x94));
  Val x97 = ((x92 + x96) - ((x92 * Val(2)) * x96));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x98 = get(ctx, arg0, 578, 0);
  Val x99 = get(ctx, arg0, 580, 0);
  Val x100 = get(ctx, arg0, 571, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x101 = (x99 * Val(2));
  // builtin Sub
  Val x102 = ((x99 + x100) - (x101 * x100));
  Val x103 = ((x98 + x102) - ((x98 * Val(2)) * x102));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x104 = get(ctx, arg0, 581, 0);
  Val x105 = get(ctx, arg0, 572, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x106 = (x104 * Val(2));
  // builtin Sub
  Val x107 = ((x104 + x105) - (x106 * x105));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x108 = (((x93 + x107) - (x95 * x107)) * Val(4));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x109 = get(ctx, arg0, 582, 0);
  Val x110 = get(ctx, arg0, 573, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x111 = (x109 * Val(2));
  // builtin Sub
  Val x112 = ((x109 + x110) - (x111 * x110));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x113 = (((x99 + x112) - (x101 * x112)) * Val(8));
  // builtin Add
  Val x114 = (((x97 + (x103 * Val(2))) + x108) + x113);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x115 = get(ctx, arg0, 583, 0);
  Val x116 = get(ctx, arg0, 574, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x117 = (x115 * Val(2));
  // builtin Sub
  Val x118 = ((x115 + x116) - (x117 * x116));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x119 = (((x104 + x118) - (x106 * x118)) * Val(16));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x120 = get(ctx, arg0, 584, 0);
  Val x121 = get(ctx, arg0, 575, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x122 = (x120 * Val(2));
  // builtin Sub
  Val x123 = ((x120 + x121) - (x122 * x121));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x124 = (((x109 + x123) - (x111 * x123)) * Val(32));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x125 = get(ctx, arg0, 585, 0);
  Val x126 = get(ctx, arg0, 576, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x127 = (x125 * Val(2));
  // builtin Sub
  Val x128 = ((x125 + x126) - (x127 * x126));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x129 = (((x115 + x128) - (x117 * x128)) * Val(64));
  // builtin Add
  Val x130 = (((x114 + x119) + x124) + x129);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x131 = get(ctx, arg0, 586, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x132 = (x131 * Val(2));
  // builtin Sub
  Val x133 = ((x131 + x92) - (x132 * x92));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x134 = (((x120 + x133) - (x122 * x133)) * Val(128));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x135 = get(ctx, arg0, 587, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x136 = (x135 * Val(2));
  // builtin Sub
  Val x137 = ((x135 + x98) - (x136 * x98));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x138 = (((x125 + x137) - (x127 * x137)) * Val(256));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x139 = get(ctx, arg0, 588, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x140 = (x139 * Val(2));
  // builtin Sub
  Val x141 = ((x139 + x93) - (x140 * x93));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x142 = (((x131 + x141) - (x132 * x141)) * Val(512));
  // builtin Add
  Val x143 = (((x130 + x134) + x138) + x142);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x144 = get(ctx, arg0, 589, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x145 = (x144 * Val(2));
  // builtin Sub
  Val x146 = ((x144 + x99) - (x145 * x99));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x147 = (((x135 + x146) - (x136 * x146)) * Val(1024));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x148 = get(ctx, arg0, 590, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x149 = (x148 * Val(2));
  // builtin Sub
  Val x150 = ((x148 + x104) - (x149 * x104));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x151 = (((x139 + x150) - (x140 * x150)) * Val(2048));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x152 = get(ctx, arg0, 591, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x153 = (x152 * Val(2));
  // builtin Sub
  Val x154 = ((x152 + x109) - (x153 * x109));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x155 = (((x144 + x154) - (x145 * x154)) * Val(4096));
  // builtin Add
  Val x156 = (((x143 + x147) + x151) + x155);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x157 = get(ctx, arg0, 560, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x158 = (x157 * Val(2));
  // builtin Sub
  Val x159 = ((x157 + x115) - (x158 * x115));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x160 = (((x148 + x159) - (x149 * x159)) * Val(8192));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x161 = get(ctx, arg0, 561, 0);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeAE(zirgen/circuit/keccak/sha2.zir:93)
  // DoShaStep(zirgen/circuit/keccak/top.zir:139)
  Val x162 = (x161 * Val(2));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x163 = ((x161 + x120) - (x162 * x120));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x164 = (((x152 + x163) - (x153 * x163)) * Val(16384));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x165 = get(ctx, arg0, 562, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x166 = (x165 * Val(2));
  // builtin Sub
  Val x167 = ((x165 + x125) - (x166 * x125));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x168 = (((x157 + x167) - (x158 * x167)) * Val(32768));
  // builtin Add
  Val x169 = (((x156 + x160) + x164) + x168);
  Val x170 = (get(ctx, arg0, 624, 2) + (get(ctx, arg0, 625, 2) * Val(2)));
  Val x171 = ((x170 + (get(ctx, arg0, 626, 2) * Val(4))) + (get(ctx, arg0, 627, 2) * Val(8)));
  Val x172 = ((x171 + (get(ctx, arg0, 628, 2) * Val(16))) + (get(ctx, arg0, 629, 2) * Val(32)));
  Val x173 = ((x172 + (get(ctx, arg0, 630, 2) * Val(64))) + (get(ctx, arg0, 631, 2) * Val(128)));
  Val x174 = ((x173 + (get(ctx, arg0, 632, 2) * Val(256))) + (get(ctx, arg0, 633, 2) * Val(512)));
  Val x175 = ((x174 + (get(ctx, arg0, 634, 2) * Val(1024))) + (get(ctx, arg0, 635, 2) * Val(2048)));
  Val x176 = ((x175 + (get(ctx, arg0, 636, 2) * Val(4096))) + (get(ctx, arg0, 637, 2) * Val(8192)));
  Val x177 =
      ((x176 + (get(ctx, arg0, 638, 2) * Val(16384))) + (get(ctx, arg0, 639, 2) * Val(32768)));
  Val x178 = (get(ctx, arg0, 656, 1) + (get(ctx, arg0, 657, 1) * Val(2)));
  Val x179 = ((x178 + (get(ctx, arg0, 658, 1) * Val(4))) + (get(ctx, arg0, 659, 1) * Val(8)));
  Val x180 = ((x179 + (get(ctx, arg0, 660, 1) * Val(16))) + (get(ctx, arg0, 661, 1) * Val(32)));
  Val x181 = ((x180 + (get(ctx, arg0, 662, 1) * Val(64))) + (get(ctx, arg0, 663, 1) * Val(128)));
  Val x182 = ((x181 + (get(ctx, arg0, 664, 1) * Val(256))) + (get(ctx, arg0, 665, 1) * Val(512)));
  Val x183 = ((x182 + (get(ctx, arg0, 666, 1) * Val(1024))) + (get(ctx, arg0, 667, 1) * Val(2048)));
  Val x184 = ((x183 + (get(ctx, arg0, 668, 1) * Val(4096))) + (get(ctx, arg0, 669, 1) * Val(8192)));
  Val x185 =
      ((x184 + (get(ctx, arg0, 670, 1) * Val(16384))) + (get(ctx, arg0, 671, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x186 = (((x83 + x87) + x91) + (x169 + (x177 + x185)));
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:44)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  Val x187 = (bitAnd(x186, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 993, bitAnd(x187, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 994, (bitAnd(x187, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 995, (bitAnd(x187, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x188 = ((get(ctx, arg0, 995, 0) * Val(4)) + (get(ctx, arg0, 994, 0) * Val(2)));
  Val x189 = (x188 + get(ctx, arg0, 993, 0));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x190 = (x186 - (x189 * Val(65536)));
  // builtin NondetReg
  // Reg(<preamble>:5)
  // TopState(zirgen/circuit/keccak/top.zir:36)
  Val x191 = get(ctx, arg0, 658, 2);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x192 = (x191 * Val(2));
  // builtin Sub
  Val x193 = ((x191 + x8) - (x192 * x8));
  // builtin Mul
  Val x194 = (x3 * Val(2));
  // builtin Sub
  Val x195 = ((x3 + x16) - (x194 * x16));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x196 = (((x43 + x195) - (x44 * x195)) * Val(2));
  // builtin Add
  Val x197 = (((x37 + x193) - (x38 * x193)) + x196);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x198 = (x9 * Val(2));
  // builtin Sub
  Val x199 = ((x9 + x23) - (x198 * x23));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x200 = (((x49 + x199) - (x50 * x199)) * Val(4));
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x201 = (x17 * Val(2));
  // builtin Sub
  Val x202 = ((x17 + x30) - (x201 * x30));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x203 = (((x56 + x202) - (x57 * x202)) * Val(8));
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x204 = (x24 * Val(2));
  // builtin Sub
  Val x205 = ((x24 + x37) - (x204 * x37));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x206 = (((x61 + x205) - (x62 * x205)) * Val(16));
  // builtin Add
  Val x207 = (((x197 + x200) + x203) + x206);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x208 = ((x1 + x43) - (x6 * x43));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x209 = (((x66 + x208) - (x67 * x208)) * Val(32));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x210 = ((x7 + x49) - (x12 * x49));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x211 = (((x71 + x210) - (x72 * x210)) * Val(64));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x212 = ((x15 + x56) - (x20 * x56));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x213 = (((x75 + x212) - (x76 * x212)) * Val(128));
  // builtin Add
  Val x214 = (((x207 + x209) + x211) + x213);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x215 = ((x22 + x61) - (x27 * x61));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x216 = (((x79 + x215) - (x80 * x215)) * Val(256));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x217 = ((x29 + x66) - (x33 * x66));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x218 = (((x84 + x217) - (x85 * x217)) * Val(512));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x219 = ((x36 + x71) - (x40 * x71));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x220 = (((x88 + x219) - (x89 * x219)) * Val(1024));
  // builtin Add
  Val x221 = (((x214 + x216) + x218) + x220);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x222 = ((x42 + x75) - (x46 * x75));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x223 = (((x191 + x222) - (x192 * x222)) * Val(2048));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:78)
  Val x224 = ((x48 + x79) - (x52 * x79));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x225 = (((x3 + x224) - (x194 * x224)) * Val(4096));
  Val x226 = (((x9 + x55) - (x198 * x55)) * Val(8192));
  // builtin Add
  Val x227 = (((x221 + x223) + x225) + x226);
  // builtin Mul
  Val x228 = (((x17 + x60) - (x201 * x60)) * Val(16384));
  Val x229 = (((x24 + x65) - (x204 * x65)) * Val(32768));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x230 = get(ctx, arg0, 563, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x231 = (x230 * Val(2));
  // builtin Sub
  Val x232 = ((x230 + x131) - (x231 * x131));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x233 = get(ctx, arg0, 564, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x234 = (x233 * Val(2));
  // builtin Sub
  Val x235 = ((x233 + x135) - (x234 * x135));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x236 = (((x165 + x235) - (x166 * x235)) * Val(2));
  // builtin Add
  Val x237 = (((x161 + x232) - (x162 * x232)) + x236);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x238 = get(ctx, arg0, 565, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x239 = (x238 * Val(2));
  // builtin Sub
  Val x240 = ((x238 + x139) - (x239 * x139));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x241 = (((x230 + x240) - (x231 * x240)) * Val(4));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x242 = get(ctx, arg0, 566, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x243 = (x242 * Val(2));
  // builtin Sub
  Val x244 = ((x242 + x144) - (x243 * x144));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x245 = (((x233 + x244) - (x234 * x244)) * Val(8));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x246 = get(ctx, arg0, 567, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x247 = (x246 * Val(2));
  // builtin Sub
  Val x248 = ((x246 + x148) - (x247 * x148));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x249 = (((x238 + x248) - (x239 * x248)) * Val(16));
  // builtin Add
  Val x250 = (((x237 + x241) + x245) + x249);
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x251 = get(ctx, arg0, 568, 0);
  // builtin Mul
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x252 = (x251 * Val(2));
  // builtin Sub
  Val x253 = ((x251 + x152) - (x252 * x152));
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x254 = (((x242 + x253) - (x243 * x253)) * Val(32));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  // ShaCycle(zirgen/circuit/keccak/top.zir:194)
  Val x255 = get(ctx, arg0, 569, 0);
  // builtin Mul
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  // DoShaStep(zirgen/circuit/keccak/top.zir:137)
  // ShaCycle(zirgen/circuit/keccak/top.zir:196)
  Val x256 = (((x246 + x255) - (x247 * x255)) * Val(64));
  Val x257 = (((x251 + x94) - (x252 * x94)) * Val(128));
  // builtin Add
  Val x258 = (((x250 + x254) + x256) + x257);
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x259 = ((x255 + x100) - ((x255 * Val(2)) * x100));
  Val x260 = ((x94 + x105) - ((x94 * Val(2)) * x105));
  Val x261 = ((x100 + x110) - ((x100 * Val(2)) * x110));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x262 = (((x258 + (x259 * Val(256))) + (x260 * Val(512))) + (x261 * Val(1024)));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x263 = ((x105 + x116) - ((x105 * Val(2)) * x116));
  Val x264 = ((x110 + x121) - ((x110 * Val(2)) * x121));
  Val x265 = ((x116 + x126) - ((x116 * Val(2)) * x126));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x266 = (((x262 + (x263 * Val(2048))) + (x264 * Val(4096))) + (x265 * Val(8192)));
  // builtin Sub
  // BitXor(zirgen/circuit/keccak/bits.zir:34)
  // XorU32(zirgen/circuit/keccak/sha2.zir:10)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:79)
  Val x267 = ((x121 + x92) - ((x121 * Val(2)) * x92));
  Val x268 = ((x126 + x98) - ((x126 * Val(2)) * x98));
  // builtin Add
  // Pack(zirgen/circuit/keccak/pack.zir:35)
  // Pack32(zirgen/circuit/keccak/sha2.zir:74)
  // ComputeW(zirgen/circuit/keccak/sha2.zir:80)
  Val x269 = (get(ctx, arg0, 640, 2) + (get(ctx, arg0, 641, 2) * Val(2)));
  Val x270 = ((x269 + (get(ctx, arg0, 642, 2) * Val(4))) + (get(ctx, arg0, 643, 2) * Val(8)));
  Val x271 = ((x270 + (get(ctx, arg0, 644, 2) * Val(16))) + (get(ctx, arg0, 645, 2) * Val(32)));
  Val x272 = ((x271 + (get(ctx, arg0, 646, 2) * Val(64))) + (get(ctx, arg0, 647, 2) * Val(128)));
  Val x273 = ((x272 + (get(ctx, arg0, 648, 2) * Val(256))) + (get(ctx, arg0, 649, 2) * Val(512)));
  Val x274 = ((x273 + (get(ctx, arg0, 650, 2) * Val(1024))) + (get(ctx, arg0, 651, 2) * Val(2048)));
  Val x275 = ((x274 + (get(ctx, arg0, 652, 2) * Val(4096))) + (get(ctx, arg0, 653, 2) * Val(8192)));
  Val x276 =
      ((x275 + (get(ctx, arg0, 654, 2) * Val(16384))) + (get(ctx, arg0, 655, 2) * Val(32768)));
  Val x277 = (get(ctx, arg0, 672, 1) + (get(ctx, arg0, 673, 1) * Val(2)));
  Val x278 = ((x277 + (get(ctx, arg0, 674, 1) * Val(4))) + (get(ctx, arg0, 675, 1) * Val(8)));
  Val x279 = ((x278 + (get(ctx, arg0, 676, 1) * Val(16))) + (get(ctx, arg0, 677, 1) * Val(32)));
  Val x280 = ((x279 + (get(ctx, arg0, 678, 1) * Val(64))) + (get(ctx, arg0, 679, 1) * Val(128)));
  Val x281 = ((x280 + (get(ctx, arg0, 680, 1) * Val(256))) + (get(ctx, arg0, 681, 1) * Val(512)));
  Val x282 = ((x281 + (get(ctx, arg0, 682, 1) * Val(1024))) + (get(ctx, arg0, 683, 1) * Val(2048)));
  Val x283 = ((x282 + (get(ctx, arg0, 684, 1) * Val(4096))) + (get(ctx, arg0, 685, 1) * Val(8192)));
  Val x284 =
      ((x283 + (get(ctx, arg0, 686, 1) * Val(16384))) + (get(ctx, arg0, 687, 1) * Val(32768)));
  // Add2(zirgen/circuit/keccak/sha2.zir:30)
  Val x285 = (((x266 + (x267 * Val(16384))) + (x268 * Val(32768))) + (x276 + x284));
  Val x286 = (((x227 + x228) + x229) + x285);
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:45)
  // DoShaStep(zirgen/circuit/keccak/top.zir:138)
  Val x287 = (x286 + x189);
  // builtin Mul
  // Div(<preamble>:22)
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:35)
  Val x288 = (bitAnd(x287, Val(983040)) * Val(2013235201));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  set(ctx, arg0, 996, bitAnd(x288, Val(1)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:36)
  set(ctx, arg0, 997, (bitAnd(x288, Val(2)) * Val(1006632961)));
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:37)
  set(ctx, arg0, 998, (bitAnd(x288, Val(4)) * Val(1509949441)));
  // builtin Add
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:38)
  Val x289 = ((get(ctx, arg0, 998, 0) * Val(4)) + (get(ctx, arg0, 997, 0) * Val(2)));
  // builtin Sub
  // CarryExtract(zirgen/circuit/keccak/sha2.zir:39)
  Val x290 = (x287 - ((x289 + get(ctx, arg0, 996, 0)) * Val(65536)));
  // builtin NondetReg
  // NondetBitReg(zirgen/circuit/keccak/bits.zir:13)
  // UnpackReg(zirgen/circuit/keccak/pack.zir:52)
  // CarryAndExpand(zirgen/circuit/keccak/sha2.zir:46)
  set(ctx, arg0, 624, bitAnd(x190, Val(1)));
  set(ctx, arg0, 625, (bitAnd(x190, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 626, (bitAnd(x190, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 627, (bitAnd(x190, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 628, (bitAnd(x190, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 629, (bitAnd(x190, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 630, (bitAnd(x190, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 631, (bitAnd(x190, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 632, (bitAnd(x190, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 633, (bitAnd(x190, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 634, (bitAnd(x190, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 635, (bitAnd(x190, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 636, (bitAnd(x190, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 637, (bitAnd(x190, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 638, (bitAnd(x190, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 639, (bitAnd(x190, Val(32768)) * Val(2013204481)));
  set(ctx, arg0, 640, bitAnd(x290, Val(1)));
  set(ctx, arg0, 641, (bitAnd(x290, Val(2)) * Val(1006632961)));
  set(ctx, arg0, 642, (bitAnd(x290, Val(4)) * Val(1509949441)));
  set(ctx, arg0, 643, (bitAnd(x290, Val(8)) * Val(1761607681)));
  set(ctx, arg0, 644, (bitAnd(x290, Val(16)) * Val(1887436801)));
  set(ctx, arg0, 645, (bitAnd(x290, Val(32)) * Val(1950351361)));
  set(ctx, arg0, 646, (bitAnd(x290, Val(64)) * Val(1981808641)));
  set(ctx, arg0, 647, (bitAnd(x290, Val(128)) * Val(1997537281)));
  set(ctx, arg0, 648, (bitAnd(x290, Val(256)) * Val(2005401601)));
  set(ctx, arg0, 649, (bitAnd(x290, Val(512)) * Val(2009333761)));
  set(ctx, arg0, 650, (bitAnd(x290, Val(1024)) * Val(2011299841)));
  set(ctx, arg0, 651, (bitAnd(x290, Val(2048)) * Val(2012282881)));
  set(ctx, arg0, 652, (bitAnd(x290, Val(4096)) * Val(2012774401)));
  set(ctx, arg0, 653, (bitAnd(x290, Val(8192)) * Val(2013020161)));
  set(ctx, arg0, 654, (bitAnd(x290, Val(16384)) * Val(2013143041)));
  set(ctx, arg0, 655, (bitAnd(x290, Val(32768)) * Val(2013204481)));
  return;
}

} // namespace risc0::circuit::keccak::cuda
