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

#include "rv32im/base/poseidon2.h"

template <typename C> struct P2CallArgument {
  Val<C> isFinal;
  ValDigest<C> in;
  ValData<C> data;
  ValDigest<C> out;
};

template <typename C> struct P2IdArgument {
  FDEV P2IdArgument() = default;
  FDEV P2IdArgument(Val<C> id) : id(id) {}

  Val<C> id;
};

template <typename C> struct P2StateArgument {
  Val<C> id;
  Val<C> round; // [0,3] ext 9 int [4, 7] ext 8 done
  ValCells<C> state;
};
