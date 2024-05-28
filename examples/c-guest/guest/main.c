#include <stdint.h>
#include "platform.h"

__asm__(
	".global _start\n\t"
	".type _start, @function\n\t"
	"_start:\n\t"
	"la sp,      _stack_top\n\t"

	// Load the globals pointer. The program will load pointers relative to this
	// register, so it must be set to the right value on startup.
	// See: https://gnu-mcu-eclipse.github.io/arch/riscv/programmer/#the-gp-global-pointer-register
	// Linker relaxations must be disabled to avoid the initialization beign
	// relaxed with an uninitialized global pointer: mv gp, gp
	".option push;\n\t"
	".option norelax\n\t"
	"la gp,      __global_pointer$\n\t"
	".option pop\n\t"

	// Jump to main function
	"call main\n\t");

int main()
{
	// TODO introduce entropy into memory image (for zk)
	sha256_state *hasher = init_sha256();
	uint8_t output_bytes[4] = {0, 1, 2, 3};

	env_commit(hasher, output_bytes, sizeof(output_bytes));

	env_exit(hasher, 0);

	return 0;
}
