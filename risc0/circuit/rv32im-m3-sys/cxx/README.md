# rv32im-m3

To bootstrap, use:

```
bazelisk run //compiler/bootstrap -- $PWD/../../rv32im-m3/src/zirgen
cargo xfast bazel
cargo run -p xtask -- bootstrap
```
