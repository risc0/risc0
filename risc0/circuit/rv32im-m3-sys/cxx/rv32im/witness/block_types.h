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

// For each block type, define name of block and count per row
#define BLOCK_TYPES                                                                                \
  BLOCK_TYPE(Globals, 1)                                                                           \
  BLOCK_TYPE(Decode, 2)                                                                            \
  BLOCK_TYPE(InstResume, 1)                                                                        \
  BLOCK_TYPE(InstSuspend, 1)                                                                       \
  BLOCK_TYPE(InstReg, 5)                                                                           \
  BLOCK_TYPE(InstImm, 5)                                                                           \
  BLOCK_TYPE(InstLoad, 3)                                                                          \
  BLOCK_TYPE(InstStore, 3)                                                                         \
  BLOCK_TYPE(InstBranch, 4)                                                                        \
  BLOCK_TYPE(InstJal, 7)                                                                           \
  BLOCK_TYPE(InstJalr, 6)                                                                          \
  BLOCK_TYPE(InstLui, 9)                                                                           \
  BLOCK_TYPE(InstAuipc, 7)                                                                         \
  BLOCK_TYPE(InstEcall, 1)                                                                         \
  BLOCK_TYPE(InstMret, 1)                                                                          \
  BLOCK_TYPE(EcallTerminate, 1)                                                                    \
  BLOCK_TYPE(EcallRead, 1)                                                                         \
  BLOCK_TYPE(EcallWrite, 1)                                                                        \
  BLOCK_TYPE(EcallP2, 1)                                                                           \
  BLOCK_TYPE(EcallBigInt, 1)                                                                       \
  BLOCK_TYPE(P2Step, 1)                                                                            \
  BLOCK_TYPE(ReadByte, 1)                                                                          \
  BLOCK_TYPE(ReadWord, 4)                                                                          \
  BLOCK_TYPE(BigInt, 1)                                                                            \
  BLOCK_TYPE(UnitAddSub, 16)                                                                       \
  BLOCK_TYPE(UnitBit, 2)                                                                           \
  BLOCK_TYPE(UnitLt, 9)                                                                            \
  BLOCK_TYPE(UnitMul, 2)                                                                           \
  BLOCK_TYPE(UnitDiv, 3)                                                                           \
  BLOCK_TYPE(UnitShift, 5)                                                                         \
  BLOCK_TYPE(P2ExtRound, 2)                                                                        \
  BLOCK_TYPE(P2IntRounds, 2)                                                                       \
  BLOCK_TYPE(P2Block, 3)                                                                           \
  BLOCK_TYPE(PageInNode, 1)                                                                        \
  BLOCK_TYPE(PageInPart, 4)                                                                        \
  BLOCK_TYPE(PageInPage, 1)                                                                        \
  BLOCK_TYPE(PageOutNode, 1)                                                                       \
  BLOCK_TYPE(PageOutPart, 4)                                                                       \
  BLOCK_TYPE(PageOutPage, 1)                                                                       \
  BLOCK_TYPE(PageUncle, 1)                                                                         \
  BLOCK_TYPE(MakeTable, 3)
