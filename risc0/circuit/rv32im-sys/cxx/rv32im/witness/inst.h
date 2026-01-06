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

#pragma once

#include "rv32im/witness/decode.h"

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstResumeWitness {
  PhysMemReadWitness v2Compat;
  PhysMemReadWitness pc;
  PhysMemReadWitness mode;
  PhysMemWriteWitness version;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstSuspendWitness {
  uint32_t cycle;
  uint32_t iCacheCycle;
  PhysMemWriteWitness pc;
  PhysMemWriteWitness mode;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstRegWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  RegMemReadWitness rs2;
  RegMemWriteWitness rd;
  uint32_t options;
  uint32_t out0;
  uint32_t out1;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstImmWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  uint32_t rs2;
  RegMemWriteWitness rd;
  uint32_t imm;
  uint32_t options;
  uint32_t out0;
  uint32_t out1;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstLoadWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  uint32_t rs2;
  VirtMemReadWitness mem;
  RegMemWriteWitness rd;
  uint32_t imm;
  uint32_t options;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstStoreWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  RegMemReadWitness rs2;
  VirtMemWriteWitness mem;
  uint32_t rd;
  uint32_t imm;
  uint32_t options;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstBranchWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  RegMemReadWitness rs2;
  uint32_t rd;
  uint32_t imm;
  uint32_t options;
  uint32_t out0;
  uint32_t out1;
  uint32_t didBranch;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstJalWitness {
  uint32_t cycle;
  FetchWitness fetch;
  uint32_t rs1;
  uint32_t rs2;
  RegMemWriteWitness rd;
  uint32_t imm;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstJalrWitness {
  uint32_t cycle;
  FetchWitness fetch;
  RegMemReadWitness rs1;
  uint32_t rs2;
  RegMemWriteWitness rd;
  uint32_t imm;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstLuiWitness {
  uint32_t cycle;
  FetchWitness fetch;
  uint32_t rs1;
  uint32_t rs2;
  RegMemWriteWitness rd;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstAuipcWitness {
  uint32_t cycle;
  FetchWitness fetch;
  uint32_t rs1;
  uint32_t rs2;
  RegMemWriteWitness rd;
  uint32_t imm;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstEcallWitness {
  uint32_t cycle;
  FetchWitness fetch;
  PhysMemWriteWitness savePc;
  PhysMemReadWitness dispatch;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstTrapWitness {
  uint32_t cycle;
  uint32_t iCacheCycle;
  PhysMemWriteWitness savePc;
  PhysMemReadWitness dispatch;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct InstMretWitness {
  uint32_t cycle;
  FetchWitness fetch;
  PhysMemReadWitness readPc;
};
