#include "risc0/core/log.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace risc0 {

int gLogLevel = 0;

void setLogLevel(int level) {
  gLogLevel = level;
}

int getLogLevel() {
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

std::string hex(uint32_t value, int digits) {
  std::stringstream ss;
  ss << "0x" << std::hex << std::setfill('0') << std::setw(digits) << value;
  return ss.str();
}

std::string hex(uint32_t value) {
  return hex(value, 8);
}

} // namespace risc0
