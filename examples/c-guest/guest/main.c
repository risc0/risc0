#include "platform.h"
#include <stdint.h>

int main() {
  // TODO introduce entropy into memory image (for zk)
  sha256_state* hasher = init_sha256();
  uint8_t output_bytes[4] = {0, 1, 2, 3};

  env_commit(hasher, output_bytes, sizeof(output_bytes));

  env_exit(hasher, 0);

  return 0;
}
