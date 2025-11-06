#!/bin/sh -e

HERE=`dirname $0`
cd "${HERE}"

if [ ! -d sppark ]; then
    trap '[ -h sppark ] && rm -f sppark' 0 2
    ln -s .. sppark
fi

# --allow-dirty because the temporary sppark symbolic link is not committed
cargo +stable publish --allow-dirty "$@"

while [ "x$1" != "x" ]; do
    [ "$1" = "--dry-run" ] && exit
    shift
done

git tag v`awk -F\" '/^version\s*=/ { print $2 }' Cargo.toml` && \
echo "Don't forget to 'git push --tags' to populate the new tag."
