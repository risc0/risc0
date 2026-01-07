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

struct PhysMemReadWitness {
  uint32_t wordAddr;
  uint32_t prevCycle;
  uint32_t value;
};

struct PhysMemWriteWitness {
  uint32_t wordAddr;
  uint32_t prevCycle;
  uint32_t prevValue;
  uint32_t value;
};

// Just in case we want to specialize later
using RegMemReadWitness = PhysMemReadWitness;
using RegMemWriteWitness = PhysMemWriteWitness;

// When we implment smode, we will actually neeed distinct witness data,
// but for now, they are just typedefs

using VirtMemReadWitness = PhysMemReadWitness;
using VirtMemWriteWitness = PhysMemWriteWitness;
