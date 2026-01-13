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

#include "rv32im/witness/block_types.h"

// clang-format off

#define HASH #
#define ATTR(key, ...) HASH [key(__VA_ARGS__)]

ATTR(derive, Debug, Copy, Clone, Hash, PartialEq, Eq, enum_map::Enum, strum::EnumIter, serde::Serialize, serde::Deserialize)
pub enum BlockType {
#define BLOCK_TYPE(name, count) name,
  BLOCK_TYPES
#undef BLOCK_TYPE
}


impl BlockType {
    ATTR(allow, clippy::identity_op)
    pub const COUNT: usize = 0
#define BLOCK_TYPE(name, count) + 1
      BLOCK_TYPES
#undef BLOCK_TYPE
    ;

    pub const fn count_per_row(&self) -> u8 {
        match self {
#define BLOCK_TYPE(name, count) Self::name => count,
  BLOCK_TYPES
#undef BLOCK_TYPE
        }
    }

    pub fn iter() -> impl Iterator<Item = Self> {
        <Self as strum::IntoEnumIterator>::iter()
    }
}

// clang-format on
