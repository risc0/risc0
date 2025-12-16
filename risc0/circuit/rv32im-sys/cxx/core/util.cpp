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

#include "core/util.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

namespace risc0 {

std::vector<uint8_t> loadFile(const std::string& path) {
  std::ifstream is(path, std::ios::binary);
  is.exceptions(std::ios_base::failbit | std::ios_base::badbit);
  is.seekg(0, std::ios::end);
  size_t nbytes = is.tellg();
  is.seekg(0, std::ios::beg);
  std::vector<uint8_t> elfContents(nbytes, 0);
  is.read(reinterpret_cast<char*>(elfContents.data()), nbytes);
  is.close();
  return elfContents;
}

void parallel_map(size_t count, std::function<void(size_t)> body) {
  unsigned int num_logical_processors = std::thread::hardware_concurrency();
  std::vector<std::thread> threads;

  auto count_per_thread = count / num_logical_processors;
  for (size_t thread_id = 0; thread_id < num_logical_processors; thread_id++) {
    auto start = thread_id * count_per_thread;
    if (thread_id == num_logical_processors - 1) {
      count_per_thread += count % num_logical_processors;
    }
    threads.emplace_back([start, count_per_thread, body] {
      for (size_t i = 0; i < count_per_thread; i++) {
        body(start + i);
      }
    });
  }

  for (std::thread& t : threads) {
    t.join();
  }
}

} // namespace risc0
