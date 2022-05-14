#!/bin/bash -x


# TODO(nils): Integrate this into cargo when it's easy to depend on
# riscv binaries.

set -e

rm -f simple_receipt simple_receipt.receipt simple_receipt.id

BAZEL_ROOT=../../../..

if ! bazel build --show_result=3 \
      //risc0/zkvm/prove/bench:bench_simple_loop \
      //risc0/zkvm/prove/bench:bench_simple_loop.id \
      //risc0/zkvm/r0vm > bazel.out 2>&1
then
    cat bazel.out
    exit 1
fi

cp ${BAZEL_ROOT}/$(egrep 'bench_simple_loop$' bazel.out | sed 's@ @@g') simple_receipt
cp ${BAZEL_ROOT}/$(egrep 'bench_simple_loop.id$' bazel.out | sed 's@ @@g') simple_receipt.id
R0VM=${BAZEL_ROOT}/$(egrep 'r0vm$' bazel.out | sed 's@ @@g')

${R0VM} simple_receipt < /dev/null 2> simple_receipt.receipt || cat -A simple_receipt.receipt
