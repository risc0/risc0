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

template<typename C>
struct UnitArgument {
  FDEV UnitArgument() = default;
  FDEV UnitArgument(uint32_t opts, uint32_t a, uint32_t b, uint32_t out0, uint32_t out1)
    : opts(opts)
    , aLow(a & 0xffff)
    , aHigh(a >> 16)
    , bLow(b & 0xffff)
    , bHigh(b >> 16)
    , out0Low(out0 & 0xffff)
    , out0High(out0 >> 16)
    , out1Low(out1 & 0xffff)
    , out1High(out1 >> 16)
  {}

  Val<C> opts;
  Val<C> aLow;
  Val<C> aHigh;
  Val<C> bLow;
  Val<C> bHigh;
  Val<C> out0Low;
  Val<C> out0High;
  Val<C> out1Low;
  Val<C> out1High;
};

