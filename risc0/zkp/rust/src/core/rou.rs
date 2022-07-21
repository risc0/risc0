// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! Tables containing the root of unity for the base field.
//!
//! There are two table, which are inverses of each other.

/// Maximum root of unity which is a power of 2, i.e. there is 2^27th root of
/// unity, but no 2^28th.
pub const MAX_ROU_PO2: usize = 27;

/// For each power of 2, what is the 'forward' root of unity for the po2.
/// That is, this list satisfies ROU_FWD\[i+1\] ^ 2 = ROU_FWD\[i\] in the prime
/// field F_2013265921, which implies ROU_FWD\[i\] ^ (2 ^ i) = 1.
pub const ROU_FWD: [u32; MAX_ROU_PO2 + 1] = [
    1, 2013265920, 284861408, 1801542727, 567209306, 740045640, 918899846, 1881002012, 1453957774,
    65325759, 1538055801, 515192888, 483885487, 157393079, 1695124103, 2005211659, 1540072241,
    88064245, 1542985445, 1269900459, 1461624142, 825701067, 682402162, 1311873874, 1164520853,
    352275361, 18769, 137,
];

/// For each power of 2, what is the 'reverse' root of unity for the po2.
/// This list satisfies ROU_FWD\[i\] * ROU_REV\[i\] = 1 in the prime field
/// F_2013265921.
pub const ROU_REV: [u32; MAX_ROU_PO2 + 1] = [
    1, 2013265920, 1728404513, 1592366214, 196396260, 1253260071, 72041623, 1091445674, 145223211,
    1446820157, 1030796471, 2010749425, 1827366325, 1239938613, 246299276, 596347512, 1893145354,
    246074437, 1525739923, 1194341128, 1463599021, 704606912, 95395244, 15672543, 647517488,
    584175179, 137728885, 749463956,
];
