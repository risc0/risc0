#!/bin/bash
set -e -u -o pipefail

SCCACHE_ARCH=$1
SCCACHE_VERSION=$2
SCCACHE_FILE=sccache-$SCCACHE_VERSION-$SCCACHE_ARCH
SCCACHE_URL=https://github.com/mozilla/sccache/releases/download
curl -L "$SCCACHE_URL/$SCCACHE_VERSION/$SCCACHE_FILE.tar.gz" | tar xz
mv -f $SCCACHE_FILE/sccache /usr/local/bin
