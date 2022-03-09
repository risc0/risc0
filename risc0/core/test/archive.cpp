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
  size_t size;

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
    ar.transfer(size);
  }

  bool operator==(const Primitives& rhs) const {
    return flag == rhs.flag && i8 == rhs.i8 && u8 == rhs.u8 && i16 == rhs.i16 && u16 == rhs.u16 &&
           i32 == rhs.i32 && u32 == rhs.u32 && i64 == rhs.i64 && u64 == rhs.u64 && size == rhs.size;
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

template <typename T> T roundtrip(T pre) {
  Buffer buf = serialize(pre);
  LOG(0, "buf: ");
  for (size_t i = 0; i < buf.size; i++) {
    LOG(0, "  [" << hex(i, 2) << "]: " << hex(buf.buf[i]));
  }
  T post;
  deserialize(buf, post);
  EXPECT_EQ(pre, post);
  return post;
}

TEST(Archive, Roundtrip) {
  Primitives x = roundtrip(Primitives{true, -4, 4, -5, 5, -6, 6, -7, 7, 10});
  LOG(0,
      "flag: " << x.flag                 //
               << ", i8: " << int(x.i8)  //
               << ", u8: " << uint(x.u8) //
               << ", i16: " << x.i16     //
               << ", u16: " << x.u16     //
               << ", i32: " << x.i32     //
               << ", u32: " << x.u32     //
               << ", i64: " << x.i64     //
               << ", u64: " << x.u64     //
               << ", size: " << x.size);
  roundtrip(StringPair{"a", "a"});
  roundtrip(StringPair{"abcde", "a"});
}

} // namespace risc0
