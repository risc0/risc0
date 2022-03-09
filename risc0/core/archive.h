#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace risc0 {

inline size_t align(size_t value, size_t alignment = sizeof(uint32_t)) {
  return ((value - 1) & ~(alignment - 1)) + alignment;
}

inline void* align(void* ptr, size_t alignment = sizeof(uint32_t)) {
  size_t value = reinterpret_cast<size_t>(ptr);
  return reinterpret_cast<void*>(align(value, alignment));
}

inline bool is_aligned(const void* ptr, size_t alignment = sizeof(uint32_t)) {
  return (reinterpret_cast<size_t>(ptr) & (alignment - 1)) == 0;
}

namespace detail {

template <typename T> struct Encoder {
  template <typename Archive> static void transfer(Archive& ar, const T& value) {
    const_cast<T&>(value).transfer(ar);
  }
};

template <typename T> struct Decoder {
  template <typename Archive> static void transfer(Archive& ar, T& value) { value.transfer(ar); }
};

template <typename Stream> class ArchiveWriter {
public:
  ArchiveWriter(Stream& stream) : stream(stream) {}

  template <typename T> void transfer(const T& value) {
    detail::Encoder<T>::transfer(*this, value);
  }

  void transfer(bool value) { stream.write_word(value); }

  void transfer(int8_t value) { stream.write_word(value); }
  void transfer(uint8_t value) { stream.write_word(value); }

  void transfer(int16_t value) { stream.write_word(value); }
  void transfer(uint16_t value) { stream.write_word(value); }

  void transfer(int32_t value) { stream.write_word(value); }
  void transfer(uint32_t value) { stream.write_word(value); }

  void transfer(int64_t value) { stream.write_dword(value); }
  void transfer(uint64_t value) { stream.write_dword(value); }

  void transfer(size_t value) { stream.write_word(value); }

  void transfer(const void* buf, size_t len) { stream.write_buffer(buf, len); }

private:
  Stream& stream;
};

template <typename Stream> class ArchiveReader {
public:
  ArchiveReader(Stream& stream) : stream(stream) {}

  template <typename T> void transfer(T& value) { Decoder<T>::transfer(*this, value); }

  void transfer(bool& value) { value = stream.read_word(); }

  void transfer(int8_t& value) { value = stream.read_word(); }
  void transfer(uint8_t& value) { value = stream.read_word(); }

  void transfer(int16_t& value) { value = stream.read_word(); }
  void transfer(uint16_t& value) { value = stream.read_word(); }

  void transfer(int32_t& value) { value = stream.read_word(); }
  void transfer(uint32_t& value) { value = stream.read_word(); }

  void transfer(int64_t& value) { value = stream.read_dword(); }
  void transfer(uint64_t& value) { value = stream.read_dword(); }

  void transfer(size_t& value) { value = stream.read_word(); }

  void transfer(void* buf, size_t len) { stream.read_buffer(buf, len); }

private:
  Stream& stream;
};

template <typename T> struct Encoder<std::vector<T>> {
  template <typename Archive> static void transfer(Archive& ar, const std::vector<T>& container) {
    ar.transfer(static_cast<uint32_t>(container.size()));
    for (const auto& item : container) {
      ar.transfer(item);
    }
  }
};

template <typename T> struct Decoder<std::vector<T>> {
  template <typename Archive> static void transfer(Archive& ar, std::vector<T>& container) {
    uint32_t size;
    ar.transfer(size);
    container.reserve(size);
    container.clear();
    for (size_t i = 0; i < size; i++) {
      T item;
      ar.transfer(item);
      container.push_back(item);
    }
  }
};

template <typename CharT> struct Encoder<std::basic_string<CharT>> {
  template <typename Archive>
  static void transfer(Archive& ar, const std::basic_string<CharT>& value) {
    ar.transfer(static_cast<uint32_t>(value.size()));
    ar.transfer(value.data(), value.size() * sizeof(CharT));
  }
};

template <typename CharT> struct Decoder<std::basic_string<CharT>> {
  template <typename Archive> static void transfer(Archive& ar, std::basic_string<CharT>& value) {
    uint32_t size;
    ar.transfer(size);
    value.resize(size);
    ar.transfer(value.data(), size * sizeof(CharT));
  }
};

class WordCounter {
public:
  void write_word(uint32_t word) { size++; }

  void write_dword(uint64_t dword) { size += 2; }

  void write_buffer(const void* buf, size_t len) { size += align(len) / sizeof(uint32_t); }

  size_t size = 0;
};

class BufferStreamWriter {
public:
  BufferStreamWriter(uint32_t* ptr) : ptr(ptr) {}

  void write_word(uint32_t word) { *ptr++ = word; }

  void write_dword(uint64_t dword) {
    *ptr++ = dword & 0xffffffff;
    *ptr++ = dword >> 32;
  }

  void write_buffer(const void* buf, size_t len) {
    uint8_t* ptr_u8 = reinterpret_cast<uint8_t*>(ptr);
    uint32_t* last = static_cast<uint32_t*>(align(ptr_u8 + len)) - 1;
    *last = 0;
    memcpy(ptr, buf, len);
    ptr = ++last;
  }

private:
  uint32_t* ptr;
};

class BufferStreamReader {
public:
  BufferStreamReader(uint32_t* ptr) : ptr(ptr) {}

  uint32_t read_word() { return *ptr++; }

  uint64_t read_dword() {
    uint32_t low = *ptr++;
    uint32_t high = *ptr++;
    return static_cast<uint64_t>(low) | static_cast<uint64_t>(high) << 32;
  }

  void read_buffer(void* buf, size_t len) {
    memcpy(buf, ptr, len);
    ptr += align(len) / sizeof(uint32_t);
  }

private:
  uint32_t* ptr;
};

} // namespace detail

struct Buffer {
  std::unique_ptr<uint32_t[]> buf;
  size_t size;
};

template <typename T> Buffer serialize(T& obj) {
  detail::WordCounter wc;
  detail::ArchiveWriter writer1(wc);
  obj.transfer(writer1);
  Buffer buf{std::unique_ptr<uint32_t[]>(new uint32_t[wc.size]), wc.size};
  detail::BufferStreamWriter stream(buf.buf.get());
  detail::ArchiveWriter writer2(stream);
  obj.transfer(writer2);
  return buf;
}

template <typename T> void deserialize(const Buffer& buf, T& obj) {
  detail::BufferStreamReader stream(buf.buf.get());
  detail::ArchiveReader reader(stream);
  obj.transfer(reader);
}

} // namespace risc0
