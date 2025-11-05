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
#include <memory>
#include <set>
#include <vector>

#include <ankerl/unordered_dense.h>

#include "rv32im/emu/image.h"
#include "rv32im/emu/poseidon2.h"
#include "rv32im/emu/trace.h"

namespace risc0::rv32im {

struct MemoryInfo {
  uint32_t cycle;
  uint32_t value;
};

using PageDetails = std::array<MemoryInfo, MPAGE_SIZE_WORDS>;

class PagedMemory {
public:
  // Make a paging structure based a memory image
  inline PagedMemory(Trace& trace, MemoryImage& image)
      : trace(trace), p2(trace), image(image), pagingCost(0) {
    counts.fill(0);
  }

  PageDetails* pageIn(uint32_t pageId) {
    auto pageSrc = image.getPage(pageId);
    PageDetails* page = new PageDetails;
    for (size_t i = 0; i < MPAGE_SIZE_WORDS; i++) {
      (*page)[i].cycle = 0;
      (*page)[i].value = (*pageSrc)[i];
    }
    addCostPage();
    uint32_t idx = (pageId + MEMORY_SIZE_MPAGES);
    loaded.insert(idx);
    idx /= 2;
    while (idx != 0) {
      if (loaded.count(idx)) {
        break;
      }
      addCostNode();
      loaded.insert(idx);
      idx /= 2;
    }
    recomputeCost();
    return page;
  }

  // Return the cost paging everything out
  size_t getPagingCost() { return pagingCost; }

  void commit(const std::vector<PageDetails*>& pages);
  Poseidon2Witgen& getP2() { return p2; }

private:
  void addCostPage();
  void addCostNode();
  void recomputeCost();

  void pageInPage(uint32_t page);
  void pageInNode(uint32_t idx);
  void pageOutPage(uint32_t page, const PageDetails* pageData);
  void pageOutNode(uint32_t idx);
  void pageUncle(uint32_t idx);

  Trace& trace;
  Poseidon2Witgen p2;
  MemoryImage& image;
  // Tracking for # of rows
  size_t pagingCost;
  std::array<size_t, size_t(BlockType::Empty)> counts;
  // List of paged in page + merkle nodes
  std::set<uint32_t> loaded;
};

} // namespace risc0::rv32im
