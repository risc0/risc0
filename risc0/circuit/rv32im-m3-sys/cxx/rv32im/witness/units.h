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

#define UNIT_WITNESS(x) \
struct Unit ## x ## Witness { \
  uint32_t count; \
  uint32_t opts; \
  uint32_t a; \
  uint32_t b; \
  uint32_t out0; \
  uint32_t out1; \
};

// Not a real unit, used as a generic unit type in fast_emu
UNIT_WITNESS(Base)

UNIT_WITNESS(AddSub)
UNIT_WITNESS(Bit)
UNIT_WITNESS(Lt)
UNIT_WITNESS(Mul)
UNIT_WITNESS(Div)
UNIT_WITNESS(Shift)

