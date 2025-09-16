# NOTE: This makefile is not necessary, and equivalent commands will be run in the build.rs script.
#       Only use this if you'd like to build manually

ROOT_DIR:=$(strip $(dir $(realpath $(lastword $(MAKEFILE_LIST)))))

ifeq ($(OS),Windows_NT)
$(error Windows not supported)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        MACHINE = linux
    endif
    ifeq ($(UNAME_S),Darwin)
        MACHINE = osx
    endif

    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        MACHINE := $(MACHINE)-x86_64
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        MACHINE := $(MACHINE)-arm64
    endif
endif

default: execute

.PHONY: platform
platform:
	CARGO_TARGET_DIR=${PWD}/guest/out/platform cargo +risc0 rustc -p zkvm-platform --target riscv32im-risc0-zkvm-elf --lib --crate-type staticlib --release  -vv

# Regenerate the header file. Assumes cbindgen installed locally.
.PHONY: headers
headers:
	cd ./platform && cbindgen --crate zkvm-platform -c ./cbindgen.toml -o ../guest/platform.h

.PHONY: gcc
gcc:
	@if ! [ -d "./riscv32im-${MACHINE}" ]; then \
        curl -L https://github.com/risc0/toolchain/releases/download/2024.01.05/riscv32im-${MACHINE}.tar.xz | tar xvJ -C ./; \
	else \
		echo "riscv32 toolchain already exists, skipping step"; \
    fi

.PHONY: guest
guest: gcc platform
	${ROOT_DIR}riscv32im-${MACHINE}/bin/riscv32-unknown-elf-gcc -nostartfiles ./guest/main.c -o ./guest/out/main -L${ROOT_DIR}guest/out/platform/riscv32im-risc0-zkvm-elf/release -lzkvm_platform -T ./guest/riscv32im-risc0-zkvm-elf.ld -D DEFINE_ZKVM

.PHONY: execute
execute: guest
	RISC0_DEV_MODE=true cargo run -p c-guest-host

.PHONY: prove
prove: guest
	cargo run -p c-guest-host
