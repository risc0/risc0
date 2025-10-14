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

#include <array>

#include "zkp/rou.h"

namespace risc0 {

// Maximum power of 2 for which we have a root of unity
size_t constexpr MAX_ROU_PO2 = 27;

// Array of 'forward' roots of unity.  These are critical for computing the NTT
// (see ntt.h). Basically, we want `fwdRou[i] ^ (2^i) == 1 (mod P)`, but
// `fwdRou[i] ^ (2^(i-1)) != 1 (mod P)`. Also, `fwdRou[i] = fwdRou[i+1] *
// fwdRou[i+1] (mod P)`.  To compute these values, we begin by finding the
// smallest number, x, such that `x^(2^(maxRouPo2 - 1)) == -1 (mod P)`.  In
// mathematicata, we find out x = 137 via:
// `SelectFirst[Table[{i, PowerMod[i, 2^26, P]}, {i, 2, 500}], (#[[2]] == P - 1)
// &][[1]]`. Then we compute `Table[PowerMod[137, (2^(27 - i)), P], {i, 0, 27}]`
constexpr std::array<Fp, MAX_ROU_PO2 + 1> ROU_FWD = {
    1,          2013265920, 284861408,  1801542727, 567209306,  740045640,  918899846,
    1881002012, 1453957774, 65325759,   1538055801, 515192888,  483885487,  157393079,
    1695124103, 2005211659, 1540072241, 88064245,   1542985445, 1269900459, 1461624142,
    825701067,  682402162,  1311873874, 1164520853, 352275361,  18769,      137};

// Multiplicative inverse of the above
constexpr std::array<Fp, MAX_ROU_PO2 + 1> ROU_REV = {
    1,          2013265920, 1728404513, 1592366214, 196396260,  1253260071, 72041623,
    1091445674, 145223211,  1446820157, 1030796471, 2010749425, 1827366325, 1239938613,
    246299276,  596347512,  1893145354, 246074437,  1525739923, 1194341128, 1463599021,
    704606912,  95395244,   15672543,   647517488,  584175179,  137728885,  749463956};

} // namespace risc0
