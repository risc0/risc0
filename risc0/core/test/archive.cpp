// Copyright 2022 RISC Zero, Inc.
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

#include "risc0/core/archive.h"

#include <gtest/gtest.h>

#include "risc0/core/log.h"

namespace risc0 {

struct Primitives {
  bool flag;
  int8_t i8;
  uint8_t u8;
  int16_t i16;
  uint16_t u16;
  int32_t i32;
  uint32_t u32;
  int64_t i64;
  uint64_t u64;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(flag);
    ar.transfer(i8);
    ar.transfer(u8);
    ar.transfer(i16);
    ar.transfer(u16);
    ar.transfer(i32);
    ar.transfer(u32);
    ar.transfer(i64);
    ar.transfer(u64);
  }

  bool operator==(const Primitives& rhs) const {
    return flag == rhs.flag && i8 == rhs.i8 && u8 == rhs.u8 && i16 == rhs.i16 && u16 == rhs.u16 &&
           i32 == rhs.i32 && u32 == rhs.u32 && i64 == rhs.i64 && u64 == rhs.u64;
  }
};

struct StringPair {
  std::string first;
  std::string second;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(first);
    ar.transfer(second);
  }

  bool operator==(const StringPair& rhs) const {
    return first == rhs.first && second == rhs.second;
  }
};

struct ArchiveTestBuffer {
  std::unique_ptr<uint32_t[]> buf;
  size_t size;
};

class WordCounter {
public:
  void write_word(uint32_t word) { size++; }
  void write_dword(uint64_t dword) { size += 2; }
  void write_buffer(const void* buf, size_t len) { size += align(len) / sizeof(uint32_t); }

  size_t size = 0;
};

template <typename T> ArchiveTestBuffer serialize(T& obj) {
  WordCounter wc;
  ArchiveWriter writer1(wc);
  writer1.transfer(obj);
  ArchiveTestBuffer buf{std::unique_ptr<uint32_t[]>(new uint32_t[wc.size]), wc.size};
  BufferStreamWriter stream(buf.buf.get());
  ArchiveWriter writer2(stream);
  writer2.transfer(obj);
  return buf;
}

template <typename T> T deserialize(void* ptr) {
  T obj;
  BufferStreamReader stream(static_cast<uint32_t*>(ptr));
  ArchiveReader reader(stream);
  reader.transfer(obj);
  return obj;
}

template <typename T> T roundtrip(T pre) {
  ArchiveTestBuffer buf = serialize(pre);
  LOG(0, "buf: ");
  for (size_t i = 0; i < buf.size; i++) {
    LOG(0, "  [" << hex(i, 2) << "]: " << hex(buf.buf[i]));
  }
  T post = deserialize<T>(buf.buf.get());
  EXPECT_EQ(pre, post);
  return post;
}

TEST(Archive, Roundtrip) {
  Primitives x = roundtrip(Primitives{true, -4, 4, -5, 5, -6, 6, -7, 7});
  LOG(0,
      "flag: " << x.flag                     //
               << ", i8: " << int32_t(x.i8)  //
               << ", u8: " << uint32_t(x.u8) //
               << ", i16: " << x.i16         //
               << ", u16: " << x.u16         //
               << ", i32: " << x.i32         //
               << ", u32: " << x.u32         //
               << ", i64: " << x.i64         //
               << ", u64: " << x.u64);
  roundtrip(StringPair{"a", "a"});
  roundtrip(StringPair{"abcde", "a"});
}

} // namespace risc0
