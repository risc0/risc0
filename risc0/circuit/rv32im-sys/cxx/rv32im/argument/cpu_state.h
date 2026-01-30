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

template <typename C> struct CpuStateArgument {
  FDEV CpuStateArgument() = default;
  FDEV CpuStateArgument(Val<C> cycle, Val<C> pcLow, Val<C> pcHigh, Val<C> mm, Val<C> iCache)
      : cycle(cycle), pcLow(pcLow), pcHigh(pcHigh), mm(mm), iCache(iCache) {}
  FDEV CpuStateArgument(Val<C> cycle, ValU32<C> pc, Val<C> mm, Val<C> iCache)
      : cycle(cycle), pcLow(pc.low), pcHigh(pc.high), mm(mm), iCache(iCache) {}

  Val<C> cycle;
  Val<C> pcLow;
  Val<C> pcHigh;
  Val<C> mm;
  Val<C> iCache;
};

template <typename C> struct BigIntCpuStateArgument {
  FDEV BigIntCpuStateArgument() = default;
  FDEV BigIntCpuStateArgument(Val<C> cycle, Val<C> pcWord, Val<C> mm)
      : cycle(cycle), pcWord(pcWord), mm(mm) {}

  Val<C> cycle;
  Val<C> pcWord;
  Val<C> mm;
};

template <typename C> struct P2StepArgument {
  Val<C> cycle;
  Val<C> countBits;
  Val<C> inWordAddr;
  Val<C> outWordAddr;
  ValDigest<C> state;
};
