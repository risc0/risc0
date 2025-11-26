
#include <cstdint>
#include <cstddef>
#include <cassert>
#include <vector>

// Makes a hash map with capacity (2 << PO2)
// DO NOT FILL over about 1/4 to capacity...
template <size_t PO2>
class FastMap {
public:
  static_assert(PO2 > 0 && PO2 < 63, "PO2 must be reasonable");
  static constexpr uint32_t kCapacity = uint32_t(1) << PO2;
  static constexpr uint32_t kMask = kCapacity - 1;

  struct Entry {
    uint64_t key;    // 0 == empty
    uint64_t value;
  };

  FastMap() { entries.resize(kCapacity); }

  void clear() {
    for (uint32_t idx : touched) {
      entries[idx].key = 0;
    }
    touched.clear();
  }

  // Insert or overwrite.
  void set(uint64_t key, uint64_t value) noexcept {
    // key==0 is reserved as sentinel
    assert(key != 0);
    uint32_t idx = index_for(key);
    for (;;) {
      Entry& e = entries[idx];
      if (e.key == 0 || e.key == key) {
        if (!e.key) {
          touched.push_back(idx);
        }
        e.key = key;
        e.value = value;
        return;
      }
      idx = (idx + 1) & kMask;
    }
  }

  // Lookup; returns 0 if not found.
  uint64_t lookup(uint64_t key) const noexcept {
    // key==0 is reserved as sentinel
    assert(key != 0);
    uint32_t idx = index_for(key);
    for (;;) {
      const Entry& e = entries[idx];
      if (e.key == 0) {
        // Empty slot => key not present
        return 0;
      }
      if (e.key == key) {
        return e.value;
      }
      idx = (idx + 1) & kMask;
    }
  }

private:
  static constexpr uint64_t kHashConst = 0x9e3779b97f4a7c15ull;

  static constexpr uint32_t index_for(uint64_t key) noexcept {
    // Simple 64-bit multiplicative hash, using high bits.
    uint64_t h = key * kHashConst;
    return uint32_t(h >> (64 - PO2));
  }

  std::vector<Entry> entries;
  std::vector<uint32_t> touched;
};

