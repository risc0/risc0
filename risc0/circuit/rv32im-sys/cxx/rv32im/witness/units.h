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

#pragma once

#include "rv32im/base/base.h"

#define UNIT_WITNESS_BODY                                                                          \
  uint32_t count;                                                                                  \
  uint32_t opts;                                                                                   \
  uint32_t a;                                                                                      \
  uint32_t b;                                                                                      \
  uint32_t out0;                                                                                   \
  uint32_t out1

/// Not a real unit, used as a generic unit type in fast_emu
///
/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitBaseWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitAddSubWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitBitWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitLtWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitMulWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitDivWitness {
  UNIT_WITNESS_BODY;
};

/// <div rustbindgen derive="Debug, Copy, Clone, PartialEq, Pod, Zeroable"></div>
struct UnitShiftWitness {
  UNIT_WITNESS_BODY;
};
