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

#include "core/log.h"

#include <chrono>
#include <iomanip>
#include <sstream>

#if defined(FROM_BAZEL)
static void logTimestamp() {
  auto& cerr = std::cerr;
  using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;
  static time_point timeBase = std::chrono::high_resolution_clock::now();
  static time_point lastTime = std::chrono::high_resolution_clock::now();
  auto now = std::chrono::high_resolution_clock::now();
  auto local = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeBase).count();
  auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
  lastTime = now;
  auto origWidth = cerr.width();
  auto origFill = cerr.fill();
  cerr << std::setw(3) << local / 1000 << ".";
  cerr << std::setfill('0') << std::setw(3) << local % 1000 << std::setfill(' ');
  cerr << " (";
  cerr << std::setw(1) << diff / 1000 << ".";
  cerr << std::setfill('0') << std::setw(3) << diff % 1000 << std::setfill(' ');
  cerr << "): ";
  cerr.width(origWidth);
  cerr.fill(origFill);
}

extern "C" void risc0_log_callback(int level, const char* data) {
  logTimestamp();
  std::cerr << data << std::endl;
}
#endif

namespace risc0 {

static int getInitialLogLevel() {
  if (const char* level = std::getenv("RISC0_LOG")) {
    return std::atoi(level);
  } else {
    return 0;
  }
}

unsigned gR0LogLevel = getInitialLogLevel();

void setR0LogLevel(unsigned level) {
  gR0LogLevel = level;
}

unsigned getR0LogLevel() {
  return gR0LogLevel;
}

} // namespace risc0
