// Copyright 2022 Risc0, Inc.
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

#include "risc0/r0vm/cpp/device/risc0.h"

using namespace risc0;

char* utoa(unsigned value, char* str, int base) {
  const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  int i, j;
  unsigned remainder;
  char c;

  /* Check base is supported. */
  if ((base < 2) || (base > 36)) {
    str[0] = '\0';
    return NULL;
  }

  /* Convert to string. Digits are in reverse order.  */
  i = 0;
  do {
    remainder = value % base;
    str[i++] = digits[remainder];
    value = value / base;
  } while (value != 0);
  str[i] = '\0';

  /* Reverse string.  */
  for (j = 0, i--; j < i; j++, i--) {
    c = str[j];
    str[j] = str[i];
    str[i] = c;
  }

  return str;
}

char* itoa(int value, char* str, int base) {
  unsigned uvalue;
  int i = 0;

  /* Check base is supported. */
  if ((base < 2) || (base > 36)) {
    str[0] = '\0';
    return nullptr;
  }

  /* Negative numbers are only supported for decimal.
   * Cast to unsigned to avoid overflow for maximum negative value.  */
  if ((base == 10) && (value < 0)) {
    str[i++] = '-';
    uvalue = (unsigned)-value;
  } else
    uvalue = (unsigned)value;

  utoa(uvalue, &str[i], base);
  return str;
}

extern "C" void risc0_main(Env* env) {
  uint8_t* src = static_cast<uint8_t*>(env->read(1024));
  uint8_t* dest = static_cast<uint8_t*>(env->read(1024));
  uint32_t srcOffset = env->read<uint32_t>();
  uint32_t destOffset = env->read<uint32_t>();
  uint32_t size = env->read<uint32_t>();
  if (srcOffset == 1024) {
    memset(dest + destOffset, 0xff, size);
  } else {
    memcpy(dest + destOffset, src + srcOffset, size);
  }
  env->write(dest, 1024);
}
