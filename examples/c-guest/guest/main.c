#include "platform.h"
#include <stdint.h>

union u32_cast {
  uint32_t value;
  uint8_t buffer[4];
};

int main() {
  // TODO introduce entropy into memory image (for zk)
  sha256_state* hasher = init_sha256();

  // Use buffer to read two u32 of bytes.
  union u32_cast a;
  union u32_cast b;
  env_read(a.buffer, 4);
  env_read(b.buffer, 4);

  a.value *= b.value;

  env_commit(hasher, a.buffer, sizeof(a.buffer));
  env_exit(hasher, 0);

  return 0;
}
