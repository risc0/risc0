FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y build-essential wget curl file ncurses-base ncurses-bin libncurses5-dev dialog cpio rsync unzip bc
RUN curl -OL https://buildroot.org/downloads/buildroot-2025.05.1.tar.gz && tar xf buildroot-2025.05.1.tar.gz
COPY base.config buildroot-2025.05.1/.config
RUN cd buildroot-2025.05.1 && make -j $(nproc)
RUN mkdir -p buildroot-2025.05.1/output/host/riscv32-buildroot-linux-musl/sysroot/usr/lib/gcc/riscv32-buildroot-linux-musl/13.4.0/
RUN cp -r buildroot-2025.05.1/output/host/lib/gcc/riscv32-buildroot-linux-musl/13.4.0/* buildroot-2025.05.1/output/host/riscv32-buildroot-linux-musl/sysroot/usr/lib/gcc/riscv32-buildroot-linux-musl/13.4.0/ && \
	rm -rf buildroot-2025.05.1/output/host/riscv32-buildroot-linux-musl/sysroot/usr/lib/gcc/riscv32-buildroot-linux-musl/13.4.0/plugins 
RUN cd buildroot-2025.05.1/output/host/riscv32-buildroot-linux-musl && tar cf /sysroot.tar sysroot
RUN du -s -h /sysroot.tar
COPY clang-clang.mk buildroot-2025.05.1/package/llvm-project/clang/clang.mk
COPY clang-Config.in buildroot-2025.05.1/package/llvm-project/clang/Config.in
COPY clang-and-binutils.config buildroot-2025.05.1/.config
RUN cd buildroot-2025.05.1 && make -j $(nproc)
FROM ubuntu:24.04
COPY --from=build /buildroot-2025.05.1/output/images/rootfs.tar /rootfs.tar
COPY --from=build /sysroot.tar /sysroot.tar
RUN du -s -h /rootfs.tar
RUN du -s -h /sysroot.tar
RUN mkdir -p /merged && cd /merged && tar pvxf /rootfs.tar && tar --strip-components=1 -vpxf /sysroot.tar
RUN ls -lR /merged
RUN cd /merged && tar cf /sysroot-merged.tar . 