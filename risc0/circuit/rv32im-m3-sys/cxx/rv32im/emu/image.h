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

#include "rv32im/base/constants.h"
#include "rv32im/emu/load_elf.h"
#include "zkp/digest.h"

#include <array>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace risc0::rv32im {

constexpr size_t MERKLE_TREE_DEPTH = 22;

using Page = std::array<uint32_t, PAGE_SIZE_WORDS>;
using PagePtr = std::shared_ptr<const Page>;

// A class to hold 'memory images'.  A memory image may not know all page data
// (for example partial transfer of image for proving).  Internally, the memory image
// is an actual tree of pages, with null pointer to 'unknown' pages.
class MemoryImage {
public:
  // Construct an 'all-unknown' memory image
  MemoryImage();
  // Construct an 'all-zero' memory image
  static MemoryImage zeros();
  // Construct an image for a 'word map'
  static MemoryImage fromWords(const std::map<uint32_t, uint32_t>& words);
  // Construct an image from elf files
  static MemoryImage fromElfs(const std::string& kernel, const std::string& user);
  // Construct an image from a single MM elf file
  static MemoryImage fromRawElf(const std::string& elf);
  // Construct an image from a single elf span.
  static MemoryImage fromRawElfBytes(const ArrayRef<uint8_t>& elf);

  // Returns a pointer to the page data, fails if unavailable
  PagePtr getPage(size_t page);
  // Sets the data for a page
  void setPage(size_t page, PagePtr data);
  // Gets a digest, fails if unavailable
  const Digest& getDigest(size_t idx) const;
  // Set a digest
  void setDigest(size_t idx, const Digest& digest);
  // Return a map of all 'known' pages
  std::map<uint32_t, PagePtr> getKnownPages() const;
  // Return a map of all 'known' digests
  std::map<uint32_t, Digest> getKnownDigests() const;

private:
  PagePtr zeroPage;
  std::vector<Digest> zeroDigests;

  // An nonexistant Page/Digest means the data is unavailable
  std::unordered_map<uint32_t, Digest> digests;
  std::unordered_map<uint32_t, PagePtr> pages;

  // Initialized the zeroPage + zeroDigests
  void initZeros();
  // Fixup digests after a change
  void fixupDigests(size_t idx);
  // Check is given MT node is a zero
  bool isZero(size_t idx);
  // Expand zero MT node (presume isZero(idx) returned true)
  void expandZero(size_t idx);
  // Do expansion if idx is a zero, return if expanded
  bool expandIfZero(size_t idx);
};

} // namespace risc0::rv32im
