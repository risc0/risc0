FROM ubuntu:20.04
RUN echo 0
RUN apt-get update -y
RUN apt-get install wget -y
RUN apt-get install vim -y
RUN apt-get install apt-utils -y
RUN apt-get install libncurses5 -y
RUN apt-get install cmake -y
RUN apt-get install build-essential -y
RUN apt-get install git -y
RUN apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev  -y
RUN mkdir /src
WORKDIR /src
RUN git clone https://github.com/riscv/riscv-gnu-toolchain
WORKDIR /src/riscv-gnu-toolchain
RUN ./configure --prefix=/usr/local/riscv32 --with-arch=rv32im --with-abi=ilp32  --with-cmodel=medany
RUN make -j 4
ENV PATH="/usr/local/riscv32/bin:${PATH}"
WORKDIR /src
RUN git clone https://github.com/oneapi-src/oneTBB.git
RUN mkdir /src/oneTBB_build
WORKDIR /src/oneTBB_build
RUN cmake ../oneTBB
RUN make -j 4
RUN make install
WORKDIR /src
RUN git clone https://github.com/risc0/risc0.git
WORKDIR /src/risc0		#Remove this once merged
RUN git checkout cmakenative	#Remove this once merged
WORKDIR /src			#Remove this once merged
RUN mkdir buid
WORKDIR /src/build
RUN cmake ../risc0
RUN make -j 4
WORKDIR /src/build
CMD  ["make test"]
