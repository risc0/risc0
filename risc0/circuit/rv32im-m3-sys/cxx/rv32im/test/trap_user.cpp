#include <stdlib.h>
#include <cstdint>

volatile uint32_t* data = reinterpret_cast<volatile uint32_t*>(0xb0000000);

void check(bool x) {
  if (!x) { exit(1); }
}

int main() {
  // Make sure data is initially 0
  check(data[0] == 0);
  check(data[1] == 0);
  // Do something an unaligned read and make sure we hit a fault
  // Note: I tried to use volative memory accesses, but the compiler is very
  // clever and often notes alignment issues, etc, so asm is just more 
  // straightforward
  asm volatile(
      "li t3, 0xb0000002\n"
      "lw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 1);
  // Same but with a write
  asm volatile(
      "li t3, 0xb0000002\n"
      "sw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 2);
  // Try to read kernel memory
  asm volatile(
      "li t3, 0xc0000000\n"
      "lw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 3);
  // Try to write kernel memory
  asm volatile(
      "li t3, 0xc0000000\n"
      "sw t3, 0(t3)\n"
      : : : "t3");
  check(data[0] == 2);
  check(data[1] == 4);
  // Do an illegal instruction
  asm volatile("unimp\n" :::);
  check(data[0] == 2);
  check(data[1] == 5);
  // Do an mret instruction not in machine mode
  asm volatile("mret\n" :::);
  check(data[0] == 2);
  check(data[1] == 6);
  // Make sure ebreak is not processed as an ecall
  asm volatile("ebreak\n" :::);
  check(data[0] == 2);
  check(data[1] == 7);
  // DO nothing
}
