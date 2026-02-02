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

#include "context.h"

inline void
extern_plonkWriteAccum_wom(device void* ctx, size_t cycle, const constant char* extra, thread Fp* args, thread Fp* outs) {
  device AccumContext* actx = static_cast<device AccumContext*>(ctx);
  actx->accum[cycle] = FpExt(args[0], args[1], args[2], args[3]);
}

inline void
extern_plonkReadAccum_wom(device void* ctx, size_t cycle, const constant char* extra, thread Fp* args, thread Fp* outs) {
  device AccumContext* actx = static_cast<device AccumContext*>(ctx);
  const device FpExt& value = actx->accum[cycle];
  outs[0] = value.elems[0];
  outs[1] = value.elems[1];
  outs[2] = value.elems[2];
  outs[3] = value.elems[3];
}
