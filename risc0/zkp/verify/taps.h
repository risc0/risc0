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

#pragma once

#include <cstdint>
#include <map>
#include <set>
#include <vector>

namespace risc0 {

// The tap set specifies for each register group and for each register, which
// timestaps back we 'tap'.  We group taps at two levels, first by register and
// then by register group.  Additionally, multiple registers (within or across
// groups) which have the same pattern of taps are part of the same 'combo'.
// These taps may be accumulated together in some places for later division by
// the same value.

enum class RegisterGroup : uint8_t {
  ACCUM = 0,
  CODE = 1,
  DATA = 2,
  INVALID = 3,
};

static constexpr size_t kNumRegisterGroups = 3;

namespace detail {

// This class is an implementation detail and carefully built to be efficient on
// RISC-V for use in recursion.
struct TapData {
  uint16_t offset;     // The offset in register group (reg #)
  uint16_t back;       // How many cycles back this tap is
  RegisterGroup group; // Which register group this tap is a part of
  // Precomputed helpers to speed up iteration
  uint8_t combo; // Which combo this register is part of
  uint8_t skip;  // How far to skip to next register
  bool operator<(const TapData& rhs) const {
    if (group != rhs.group) {
      return group < rhs.group;
    }
    if (offset != rhs.offset) {
      return offset < rhs.offset;
    }
    return back < rhs.back;
  }
  bool operator==(const TapData& rhs) const {
    return group == rhs.group && offset == rhs.offset && back == rhs.back;
  }
};

} // namespace detail

// Ref object to hide implementation details
class TapRef {
public:
  TapRef(const detail::TapData* data) : data_(data) {}
  RegisterGroup group() const { return data_->group; }
  size_t offset() const { return data_->offset; }
  size_t back() const { return data_->back; }
  size_t comboID() const { return data_->combo; }

private:
  const detail::TapData* data_;
};

// Not much of an interator, just enough to make range for happy
class TapIterator {
public:
  TapIterator(const detail::TapData* data) : data_(data) {}
  TapRef operator*() const { return TapRef(data_); }
  TapIterator& operator++() {
    ++data_;
    return *this;
  }
  bool operator==(const TapIterator& rhs) const { return data_ == rhs.data_; }
  bool operator!=(const TapIterator& rhs) const { return data_ != rhs.data_; }

private:
  const detail::TapData* data_;
};

// Ref object to view a group of taps as a single register
class RegRef {
public:
  RegRef(const detail::TapData* data) : data_(data) {}
  // Get tap elements which are fixed for a given register
  RegisterGroup group() const { return data_->group; }
  size_t offset() const { return data_->offset; }
  size_t comboID() const { return data_->combo; }
  // Number of taps in the register
  uint32_t size() const { return data_->skip; }
  // Allow registers to be used in range for to get taps
  TapIterator begin() const { return data_; }
  TapIterator end() const { return data_ + data_->skip; }
  // Get a specific 'back' value
  size_t operator[](size_t i) { return data_[i].back; }

private:
  // Points to the first tap for this register
  const detail::TapData* data_;
};

class RegIterator {
public:
  RegIterator(const detail::TapData* data) : data_(data) {}
  RegRef operator*() const { return RegRef(data_); }
  RegIterator& operator++() {
    data_ = data_ + data_->skip;
    return *this;
  }
  bool operator==(const RegIterator& rhs) const { return data_ == rhs.data_; }
  bool operator!=(const RegIterator& rhs) const { return data_ != rhs.data_; }

private:
  // Points to the first tap for this register
  const detail::TapData* data_;
};

namespace detail {

// Combo data holds the tap set for each 'combo'.  Basically, combo N consists
// of taps in the range [offsets[n], offsets[n+1]).  Again this is an
// implementation detail, and the format is designed to put the actual arrays
// into static data.
struct ComboData {
  uint16_t* taps;
  uint16_t* offsets;
  uint16_t count;
};

} // namespace detail

class ComboRef {
public:
  ComboRef(const detail::ComboData* data, size_t id) : data_(data), id_(id) {}
  size_t id() const { return id_; }
  size_t size() const { return data_->offsets[id_ + 1] - data_->offsets[id_]; }
  const uint16_t* begin() const { return data_->taps + data_->offsets[id_]; }
  const uint16_t* end() const { return data_->taps + data_->offsets[id_ + 1]; }

private:
  const detail::ComboData* data_;
  size_t id_;
};

class ComboIterator {
public:
  ComboIterator(const detail::ComboData* data, size_t id) : data_(data), id_(id) {}
  ComboRef operator*() const { return ComboRef(data_, id_); }
  ComboIterator& operator++() {
    id_++;
    return *this;
  }

private:
  const detail::ComboData* data_;
  size_t id_;
};

namespace detail {

struct TapSetData {
  const detail::TapData* taps;
  size_t groupBegin[kNumRegisterGroups + 1];
  ComboData combos;
};

} // namespace detail

template <typename It> class IteratorRange {
public:
  IteratorRange(It begin, It end) : begin_(begin), end_(end) {}
  It begin() const { return begin_; }
  It end() const { return end_; }

private:
  It begin_;
  It end_;
};

class TapSetRef {
private:
  const detail::TapSetData* data_;

public:
  TapSetRef(const detail::TapSetData* data) : data_(data) {}

  size_t tapsSize() { return data_->groupBegin[kNumRegisterGroups]; }

  IteratorRange<TapIterator> taps() {
    return IteratorRange<TapIterator>(data_->taps,
                                      data_->taps + data_->groupBegin[kNumRegisterGroups]);
  }

  IteratorRange<RegIterator> regs() {
    return IteratorRange<RegIterator>(data_->taps,
                                      data_->taps + data_->groupBegin[kNumRegisterGroups]);
  }

  IteratorRange<TapIterator> groupTaps(RegisterGroup group) {
    size_t groupID = static_cast<size_t>(group);
    return IteratorRange<TapIterator>(data_->taps + data_->groupBegin[groupID],
                                      data_->taps + data_->groupBegin[groupID + 1]);
  }

  IteratorRange<RegIterator> groupRegs(RegisterGroup group) {
    size_t groupID = static_cast<size_t>(group);
    return IteratorRange<RegIterator>(data_->taps + data_->groupBegin[groupID],
                                      data_->taps + data_->groupBegin[groupID + 1]);
  }

  size_t groupSize(RegisterGroup group) {
    size_t groupID = static_cast<size_t>(group);
    size_t last = (data_->taps + data_->groupBegin[groupID + 1] - 1)->offset;
    return last + 1;
  }

  size_t combosSize() const { return data_->combos.count; }

  IteratorRange<ComboIterator> combos() {
    return IteratorRange<ComboIterator>(ComboIterator(&data_->combos, 0),
                                        ComboIterator(&data_->combos, data_->combos.count));
  }

  ComboRef getCombo(size_t id) { return ComboRef(&data_->combos, id); }
};

class TapSet {
private:
  // Stuff used only while building
  bool finalized_;
  using Reg = std::set<size_t>;
  using Group = std::map<size_t, Reg>;
  using All = std::map<RegisterGroup, Group>;
  All all_;

  // Stuff that exists post finalization
  std::vector<detail::TapData> taps_;
  std::vector<uint16_t> comboTaps_;
  std::vector<uint16_t> comboBegin_;
  detail::TapSetData data_;

public:
  // Make an empty tap set
  TapSet();
  // Add a tap
  void addTap(RegisterGroup group, size_t offset, size_t back);
  // Called when all done
  void finalize();
  // Check if taps are finalized
  bool finalized() const { return finalized_; }

  // Convert to TapSetRef for use (must be finalized)
  TapSetRef getRef() const;
};

} // namespace risc0
