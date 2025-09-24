// Copyright 2025 RISC Zero, Inc.
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

#include "core/log.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace risc0 {

unsigned gLogLevel = 0;

void setLogLevel(unsigned level) {
  gLogLevel = level;
}

unsigned getLogLevel() {
  return gLogLevel;
}

void logTimestamp() {
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

} // namespace risc0
