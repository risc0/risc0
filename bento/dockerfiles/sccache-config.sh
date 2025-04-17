#!/bin/bash
set -e -u -o pipefail

export CC="sccache clang"
export CXX="sccache clang++"
export SCCACHE_IDLE_TIMEOUT=0
export CARGO_INCREMENTAL=0
export CARGO_PROFILE_DEV_DEBUG=0
export CMAKE_C_COMPILER_LAUNCHER=sccache
export CMAKE_CXX_COMPILER_LAUNCHER=sccache
export RUSTC_WRAPPER=sccache
S3_CACHE_PREFIX=$1

if [ -f /root/.aws/credentials ]; then
    CREDS_FILE_SIZE=$(stat -c%s /root/.aws/credentials)
    if [ $CREDS_FILE_SIZE -gt 0 ]; then
        export SCCACHE_BUCKET="risc0-ci-cache"
        export SCCACHE_REGION="us-west-2"
        export SCCACHE_S3_KEY_PREFIX=$S3_CACHE_PREFIX

        echo "Using s3 [$SCCACHE_BUCKET/$SCCACHE_S3_KEY_PREFIX] caching and sccache..."
    else
        echo "Using local sccache"
        export SCCACHE_DIR=/root/.cache/sccache/
    fi
else
    echo "Using local sccache"
    export SCCACHE_DIR=/root/.cache/sccache/
fi