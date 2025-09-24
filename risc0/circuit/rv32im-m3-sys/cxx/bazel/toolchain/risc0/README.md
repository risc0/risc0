# NOTES

## Building the toolchain

```
git clone https://github.com/riscv/riscv-gnu-toolchain -b 2022.02.25
cd riscv-gnu-toolchain
# needed for Apple Silicon support
sed -i .bak 's/.*=host-darwin.o$//' riscv-gcc/gcc/config.host
sed -i .bak 's/.* x-darwin.$//' riscv-gcc/gcc/config.host
./configure \
  --prefix=/tmp/riscv32im-darwin-arm64 \
  --with-arch=rv32im \
  --with-abi=ilp32 \
  --with-cmodel=medany
make -j8
cd /tmp
tar cJf riscv32im-darwin-arm64.tar.xz riscv32im-darwin-arm64
```

## Publishing a toolchain release

```
git clone git@github.com:risc0/toolchain.git
cd toolchain
git tag 2022.02.25
git push --tags
```

Create a new release based on the newly created tag.

```
github-release release -u risc0 -r toolchain -t 2022.02.25
github-release upload -u risc0 -r toolchain -t 2022.02.25 -f riscv32im-darwin-arm64.tar.xz -n riscv32im-darwin-arm64.tar.xz
```
