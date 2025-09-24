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

#include <map>
#include <set>
#include <vector>

#include "zkp/fpext.h"

namespace risc0 {

class TapManager;

class Tap {
public:
  Tap() = default;
  Tap(uint32_t group, uint32_t column, uint32_t back) : group(group), column(column), back(back) {}
  bool operator<(const Tap& rhs) const {
    if (group != rhs.group) { return group < rhs.group; }
    if (column != rhs.column) { return column < rhs.column; }
    return back < rhs.back;
  }
  bool operator==(const Tap& rhs) const {
    return group == rhs.group && column == rhs.column && back == rhs.back;
  }
  uint32_t group;  // Which group # this tap belongs to
  uint32_t column;  // Which column is it
  uint32_t back;  // How far back does it go
  uint32_t comboId;  // Which 'combo' is this part of
};

template<typename T>
class PtrRange {
public:
  PtrRange(const std::vector<T>& vec) : _begin(vec.data()), _end(vec.data() + vec.size()) {}
  PtrRange(const T* begin, const T* end) : _begin(begin), _end(end) {}
  size_t size() const{ return _end - _begin; }
  const T* begin() const { return _begin; }
  const T* end() const { return _end; }
  const T& operator[](size_t i) const { return *(_begin + i); }
private:
  const T* _begin;
  const T* _end;
};

class Column {
  friend class TapManager;
public:
  uint32_t group;
  uint32_t column;
  uint32_t comboId;
  PtrRange<Tap> getTaps() const { return PtrRange<Tap>(begin, end); }
private:
  const Tap* begin;
  const Tap* end;
};

class Group {
  friend class TapManager;
public:
  uint32_t group;
  PtrRange<Tap> getTaps() const { return PtrRange<Tap>(tapBegin, tapEnd); }
  PtrRange<Column> getColumns() const { return PtrRange<Column>(colBegin, colEnd); }
private:
  const Tap* tapBegin;
  const Tap* tapEnd;
  const Column* colBegin;
  const Column* colEnd;
};

class Combo {
  friend class TapManager;
public:
  uint32_t comboId;
  uint32_t offset;
  std::vector<uint32_t> backs;
};

class TapManager {
public:
  TapManager();
  void addTap(uint32_t group, uint32_t col, uint32_t back);
  void done(); // Automatically add check taps + check group

  // Prevent copying since internal pointers to tap array make this bad
  TapManager(const TapManager&) = delete;
  TapManager& operator=(const TapManager&) = delete;

  // Allow moving since this doesn't invalidate the internal pointers
  // TapManager(TapManager&&) = default;
  // TapManager& operator=(TapManager&&) = default;

  PtrRange<Tap> getTaps() const { return PtrRange<Tap>(taps); }
  PtrRange<Column> getColumns() const { return PtrRange<Column>(columns); }
  PtrRange<Group> getGroups() const { return PtrRange<Group>(groups); }
  PtrRange<Combo> getCombos() const { return PtrRange<Combo>(combos); }

  size_t comboSizeTot() const;

private:
  std::vector<Tap> taps;
  std::vector<Column> columns;
  std::vector<Group> groups;
  std::vector<Combo> combos;
};

}  // namespace risc0
