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

#include "rv32im/emu/paging.h"
#include "core/log.h"

namespace risc0::rv32im {

void PagedMemory::addCostPage() {
  size_t NUM_PARTS = PAGE_SIZE_WORDS / PAGE_PART_SIZE;
  counts[size_t(BlockType::P2Block)] += 2 * NUM_PARTS;
  counts[size_t(BlockType::P2ExtRound)] += 2 * 8 * NUM_PARTS;
  counts[size_t(BlockType::P2IntRounds)] += 2 * NUM_PARTS;
  counts[size_t(BlockType::PageInPart)] += NUM_PARTS;
  counts[size_t(BlockType::PageOutPart)] += NUM_PARTS;
  counts[size_t(BlockType::PageInPage)]++;
  counts[size_t(BlockType::PageOutPage)]++;
}

void PagedMemory::addCostNode() {
  counts[size_t(BlockType::P2Block)] += 2;
  counts[size_t(BlockType::P2ExtRound)] += 2 * 8;
  counts[size_t(BlockType::P2IntRounds)] += 2;
  counts[size_t(BlockType::PageInNode)]++;
  counts[size_t(BlockType::PageOutNode)]++;
  counts[size_t(BlockType::PageUncle)]++; // Technically we don't always need this
}

void PagedMemory::recomputeCost() {
  size_t tot = 0;
  for (size_t i = 0; i < size_t(BlockType::Empty); i++) {
    size_t countPer = getBlockCountPerRow(BlockType(i));
    tot += (counts[i] + countPer - 1) / countPer;
  }
  pagingCost = tot;
}

void PagedMemory::commit(const std::vector<PageDetails*>& pages) {
  // Set initial root
  toFpDigest(trace.getGlobals().rootIn, image.getDigest(1));
  // Page in all the pages that were read
  auto itNodeEnd = loaded.lower_bound(MEMORY_SIZE_PAGES);
  for (auto it = itNodeEnd; it != loaded.end(); ++it) {
    LOG(2, "Paging in: " << *it - MEMORY_SIZE_PAGES);
    pageInPage(*it - MEMORY_SIZE_PAGES);
  }
  // Page in all nodes that were read
  for (auto it = loaded.begin(); it != itNodeEnd; ++it) {
    pageInNode(*it);
  }
  // Page out all the new pages, update image
  for (auto it = loaded.lower_bound(MEMORY_SIZE_PAGES); it != loaded.end(); ++it) {
    size_t page = *it - MEMORY_SIZE_PAGES;
    LOG(2, "Paging out: " << page);
    pageOutPage(page, pages[page]);
  }
  // Page out all  nodes
  for (auto it = loaded.begin(); it != itNodeEnd; ++it) {
    uint32_t idx = *it;
    pageOutNode(idx);
    // If either child is not loaded, add uncle witness
    if (!loaded.count(idx * 2)) {
      pageUncle(idx * 2);
    }
    if (!loaded.count(idx * 2 + 1)) {
      pageUncle(idx * 2 + 1);
    }
  }
  // Set final root
  toFpDigest(trace.getGlobals().rootOut, image.getDigest(1));
}

void PagedMemory::pageInPage(uint32_t page) {
  PagePtr pagePtr = image.getPage(page);
  Digest cur = Digest::zero();
  size_t NUM_PARTS = PAGE_SIZE_WORDS / PAGE_PART_SIZE;
  for (size_t i = 0; i < NUM_PARTS; i++) {
    std::array<Fp, p2impl::CELLS_RATE> data;
    auto& pip = trace.makePageInPart();
    uint32_t addr = page * PAGE_SIZE_WORDS + i * PAGE_PART_SIZE;
    pip.addr = addr;
    toFpDigest(pip.in, cur);
    for (size_t j = 0; j < PAGE_PART_SIZE; j++) {
      uint32_t word = (*pagePtr)[i * PAGE_PART_SIZE + j];
      pip.data[j] = word;
      data[2 * j] = word & 0xffff;
      data[2 * j + 1] = word >> 16;
    }
    cur = p2.doBlock(cur, data, i == NUM_PARTS - 1);
    toFpDigest(pip.out, cur);
  }
  auto& pip = trace.makePageInPage();
  pip.addr = page * PAGE_SIZE_WORDS;
  toFpDigest(pip.node, cur);
}

void PagedMemory::pageInNode(uint32_t idx) {
  auto& wit = trace.makePageInNode();
  wit.index = idx;
  toFpDigest(wit.node, image.getDigest(idx));
  toFpDigest(wit.left, image.getDigest(idx * 2));
  toFpDigest(wit.right, image.getDigest(idx * 2 + 1));
  std::array<Fp, p2impl::CELLS_RATE> data;
  for (size_t i = 0; i < p2impl::CELLS_DIGEST; i++) {
    data[i] = wit.right[i];
    data[CELLS_DIGEST + i] = wit.left[i];
  }
  p2.doBlock(Digest::zero(), data, 1);
}

void PagedMemory::pageOutPage(uint32_t page, const PageDetails* pageData) {
  auto newPage = std::make_shared<Page>();
  Digest cur = Digest::zero();
  size_t NUM_PARTS = PAGE_SIZE_WORDS / PAGE_PART_SIZE;
  for (size_t i = 0; i < NUM_PARTS; i++) {
    std::array<Fp, p2impl::CELLS_RATE> data;
    auto& pop = trace.makePageOutPart();
    uint32_t addr = page * PAGE_SIZE_WORDS + i * PAGE_PART_SIZE;
    pop.addr = addr;
    toFpDigest(pop.in, cur);
    for (size_t j = 0; j < PAGE_PART_SIZE; j++) {
      uint32_t word = (*pageData)[i * PAGE_PART_SIZE + j].value;
      (*newPage)[i * PAGE_PART_SIZE + j] = word;
      pop.data[j] = word;
      pop.cycle[j] = (*pageData)[i * PAGE_PART_SIZE + j].cycle;
      data[2 * j] = word & 0xffff;
      data[2 * j + 1] = word >> 16;
    }
    cur = p2.doBlock(cur, data, i == NUM_PARTS - 1);
    toFpDigest(pop.out, cur);
  }
  auto& pop = trace.makePageOutPage();
  pop.addr = page * PAGE_SIZE_WORDS;
  toFpDigest(pop.node, cur);
  image.setPage(page, newPage);
}

void PagedMemory::pageOutNode(uint32_t idx) {
  auto& wit = trace.makePageOutNode();
  wit.index = idx;
  toFpDigest(wit.node, image.getDigest(idx));
  toFpDigest(wit.left, image.getDigest(idx * 2));
  toFpDigest(wit.right, image.getDigest(idx * 2 + 1));
  std::array<Fp, p2impl::CELLS_RATE> data;
  for (size_t i = 0; i < p2impl::CELLS_DIGEST; i++) {
    data[i] = wit.right[i];
    data[CELLS_DIGEST + i] = wit.left[i];
  }
  p2.doBlock(Digest::zero(), data, 1);
}

void PagedMemory::pageUncle(uint32_t idx) {
  auto& wit = trace.makePageUncle();
  wit.index = idx;
  toFpDigest(wit.node, image.getDigest(idx));
}

} // namespace risc0::rv32im
