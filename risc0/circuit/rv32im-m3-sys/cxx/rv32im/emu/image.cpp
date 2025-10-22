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

#include "rv32im/emu/image.h"
#include "core/log.h"
#include "core/util.h"
#include "zkp/poseidon2.h"

#include <iostream>

namespace risc0::rv32im {

size_t MEMORY_SIZE_PAGES = (1 << MERKLE_TREE_DEPTH);

Digest hashPage(const uint32_t* data) {
  std::array<Fp, 24> cells;
  cells.fill(0);
  // Load data into felts as 16 bit values
  for (size_t i = 0; i < PAGE_SIZE_WORDS / 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      cells[2 * j] = Fp(data[i * 8 + j] & 0xffff);
      cells[2 * j + 1] = Fp(data[i * 8 + j] >> 16);
    }
    p2impl::poseidonSponge(cells);
  }
  Digest out;
  for (size_t i = 0; i < 8; i++) {
    out.words[i] = cells[i].asRaw();
  }
  return out;
}

Digest hashPair(const Digest& lhs, const Digest& rhs) {
  std::array<Fp, 24> cells;
  cells.fill(0);
  for (size_t i = 0; i < 8; i++) {
    cells[i] = Fp::fromRaw(rhs.words[i]);
    cells[8 + i] = Fp::fromRaw(lhs.words[i]);
  }
  p2impl::poseidonSponge(cells);
  Digest out;
  for (size_t i = 0; i < 8; i++) {
    out.words[i] = cells[i].asRaw();
  }
  return out;
}

MemoryImage::MemoryImage() {
  initZeros();
}

MemoryImage MemoryImage::zeros() {
  MemoryImage ret;
  ret.digests[1] = ret.zeroDigests[0];
  return ret;
}

MemoryImage MemoryImage::fromWords(const std::map<uint32_t, uint32_t>& words) {
  MemoryImage ret = MemoryImage::zeros();
  uint32_t curPageID = 0xffffffff;
  std::shared_ptr<Page> curPage;
  for (const auto& kvp : words) {
    uint32_t pageID = kvp.first / PAGE_SIZE_WORDS;
    if (pageID != curPageID) {
      if (curPage) {
        ret.setPage(curPageID, curPage);
      }
      curPage = std::make_shared<Page>();
      curPageID = pageID;
    }
    // printf("store(0x%08x, 0x%08x)\n", kvp.first, kvp.second);
    (*curPage)[kvp.first % PAGE_SIZE_WORDS] = kvp.second;
  }
  if (curPage) {
    ret.setPage(curPageID, curPage);
  }
  return ret;
}

MemoryImage MemoryImage::fromElfs(const std::string& kernel, const std::string& user) {
  std::map<uint32_t, uint32_t> words;
  loadWithKernel(words, kernel, user);
  return MemoryImage::fromWords(words);
}

MemoryImage MemoryImage::fromRawElf(const std::string& elf) {
  std::map<uint32_t, uint32_t> words;
  loadRaw(words, elf);
  return MemoryImage::fromWords(words);
}

MemoryImage MemoryImage::fromRawElfBytes(const ArrayRef<uint8_t>& elf) {
  std::map<uint32_t, uint32_t> words;
  loadRawBytes(words, elf);
  return MemoryImage::fromWords(words);
}

PagePtr MemoryImage::getPage(size_t page) {
  // LOG(1, "getPage: " << HexWord{static_cast<uint32_t>(page)});

  // If page exists, return it
  auto it = pages.find(page);
  if (it != pages.end()) {
    return it->second;
  }
  // Otherwise try an expand
  if (expandIfZero(MEMORY_SIZE_PAGES + page)) {
    pages[page] = zeroPage;
    return zeroPage;
  }
  // Otherwise fail
  LOG(0, "Unavailable page: " << HexWord{static_cast<uint32_t>(page)});
  throw std::runtime_error("Attempting to read unavailable page");
}

// Sets the data for a page
void MemoryImage::setPage(size_t page, PagePtr data) {
  // printf("setPage(0x%08zx)\n", page);
  // If page is zero, reify it so I have proper uncles
  expandIfZero(MEMORY_SIZE_PAGES + page);
  // Set page
  pages[page] = data;
  // Set the diest value
  digests[MEMORY_SIZE_PAGES + page] = hashPage(data->data());
  // Fixup digest values
  fixupDigests(MEMORY_SIZE_PAGES + page);
}

const Digest& MemoryImage::getDigest(size_t idx) const {
  // Expand if needed: make this appear const
  const_cast<MemoryImage*>(this)->expandIfZero(idx);
  // Return digest if available
  auto it = digests.find(idx);
  if (it != digests.end()) {
    return it->second;
  }
  // Otherwise fail
  throw std::runtime_error("Attempting to read unavailable digest");
}

void MemoryImage::setDigest(size_t idx, const Digest& digest) {
  // If digest is in a zero region, reify for proper uncles
  expandIfZero(idx);
  // Set the diest value
  digests[idx] = digest;
  // Fixup digest values
  fixupDigests(idx);
}

std::map<uint32_t, PagePtr> MemoryImage::getKnownPages() const {
  return std::map<uint32_t, PagePtr>(pages.begin(), pages.end());
}

std::map<uint32_t, Digest> MemoryImage::getKnownDigests() const {
  return std::map<uint32_t, Digest>(digests.begin(), digests.end());
}

void MemoryImage::initZeros() {
  auto writableZeroPage = std::make_shared<Page>();
  writableZeroPage->fill(0);
  zeroPage = writableZeroPage;
  Digest curDigest = hashPage(zeroPage->data());
  zeroDigests.resize(MERKLE_TREE_DEPTH + 1);
  for (size_t depth = MERKLE_TREE_DEPTH + 1; depth-- > 0;) {
    zeroDigests[depth] = curDigest;
    curDigest = hashPair(curDigest, curDigest);
  }
}

void MemoryImage::fixupDigests(size_t idx) {
  while (idx != 1) {
    size_t up = idx / 2;
    if (!digests.count(2 * up) || !digests.count(2 * up + 1)) {
      return;
    }
    Digest left = digests.at(2 * up);
    Digest right = digests.at(2 * up + 1);
    digests[up] = hashPair(left, right);
    idx = up;
  }
}

static size_t constexpr log2Floor(size_t in) {
  size_t po2 = 0;
  while ((size_t(1) << (po2 + 1)) <= in) {
    po2++;
  }
  return po2;
}

bool MemoryImage::isZero(size_t idx) {
  // Compute the depth in the tree of this node
  size_t depth = log2Floor(idx);
  // Go up until we hit a valid node or get past the root
  while (digests.count(idx) == 0 && idx > 0) {
    idx /= 2;
    depth--;
  }
  if (idx == 0) {
    return false;
  } // Failed to find a root at all
  return digests.at(idx) == zeroDigests[depth];
}

void MemoryImage::expandZero(size_t idx) {
  // Compute the depth in the tree of this node
  size_t depth = log2Floor(idx);
  // Go up until we hit the valid zero node
  while (digests.count(idx) == 0) {
    size_t newIdx = idx / 2;
    digests[2 * newIdx] = zeroDigests[depth];
    digests[2 * newIdx + 1] = zeroDigests[depth];
    idx = newIdx;
    depth--;
  }
}

bool MemoryImage::expandIfZero(size_t idx) {
  // printf("expandIfZero(0x%08zx)\n", idx);
  if (isZero(idx)) {
    expandZero(idx);
    return true;
  }
  return false;
}

void MemoryImage::setPageRaw(size_t pidx, PagePtr page) {
  pages[pidx] = page;
}

void MemoryImage::setDigestRaw(size_t didx, const Digest& digest) {
  digests[didx] = digest;
}

void MemoryImage::dumpZeros() {
  LOG(0, "Zero Digests");
  for (auto& digest : zeroDigests) {
    LOG(0, "digest: " << digest);
  }
}

void MemoryImage::dump() {
  LOG(0, "MemoryImage Digests");
  for (auto& digest : getKnownDigests()) {
    LOG(0, "digest: " << HexWord{digest.first} << ": " << digest.second);
  }
}

} // namespace risc0::rv32im
