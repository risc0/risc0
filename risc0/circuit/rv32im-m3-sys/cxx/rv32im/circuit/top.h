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

#include "rv32im/witness/witness.h"
#include "rv32im/circuit/regext.h"

template<typename C>
struct Top {
  TwoHot<C, MAJOR_SPLIT_SIZE, MINOR_SPLIT_SIZE> select;
  union {
#define BLOCK_TYPE(name, count) struct { \
      BitReg<C> isValid[count]; \
      name ## Block<C> data[count]; \
    } name;
    BLOCK_TYPES
#undef BLOCK_TYPE
  } mux;
};

template<typename C>
struct AccumTop {
  OneHot<C, POLY_OP_SIZE> polyOp;
  RegExt<C> local;
  RegExt<C> poly;
  RegExt<C> term;
  RegExt<C> total;
  
  template<typename T>
  FDEV void applyInner(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z) DEV {
    T::apply(ctx, polyOp);
    T::apply(ctx, local);
    T::apply(ctx, poly);
    T::apply(ctx, term);
    T::apply(ctx, total);
  }

  // Sets polyOp + local
  FDEV void setPhase1(CTX, MDEV Top<C>* top, ValExt<C> z) DEV;
  FDEV bool isSimple() DEV;
  // Sets poly/term/total based on prev state
  FDEV void setPhase2(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z16, ValExt<C> neg) DEV;
  // Verifies everything
  FDEV void verify(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z) DEV;
  FDEV void addArguments(CTX, MDEV Top<C>* top, MDEV AccumTop<C>* prev, ValExt<C> z) DEV {}
};
