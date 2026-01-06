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

#include "rv32im/base/base.h"

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct PhysMemReadWitness {
  uint32_t wordAddr;
  uint32_t prevCycle;
  uint32_t value;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct PhysMemWriteWitness {
  uint32_t wordAddr;
  uint32_t prevCycle;
  uint32_t prevValue;
  uint32_t value;
};

// Just in case we want to specialize later
using RegMemReadWitness = PhysMemReadWitness;
using RegMemWriteWitness = PhysMemWriteWitness;

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct VirtAddrWitness {
  uint32_t readCycle;
  uint32_t vpage;
  uint32_t ppage;
  uint32_t wordOffset;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct VirtMemReadWitness {
  VirtAddrWitness addr;
  uint32_t prevCycle;
  uint32_t value;
};

/// <div rustbindgen derive="::bytemuck::Pod"></div>
/// <div rustbindgen derive="::bytemuck::Zeroable"></div>
struct VirtMemWriteWitness {
  VirtAddrWitness addr;
  uint32_t prevCycle;
  uint32_t prevValue;
  uint32_t value;
};

struct VirtAddrResolve {
  uint32_t cacheCycle;
  VirtAddrWitness addr;
  PhysMemReadWitness satp;
  PhysMemReadWitness pte1;
  PhysMemReadWitness pte2;
};
