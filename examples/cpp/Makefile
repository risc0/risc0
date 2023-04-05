CXX=riscv32-unknown-elf-c++
LDLIBS=$(shell cd ../.. && cargo risczero staticlib)

all: hello

test: hello hello.expected
	cargo run --manifest-path ../../risc0/r0vm/Cargo.toml --bin r0vm -- --elf hello > hello.actual
	cmp hello.expected hello.actual

.PHONY: test
