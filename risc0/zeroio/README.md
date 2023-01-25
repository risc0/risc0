Zeroio provides utilities to communicate efficiently with the guest.

This is similar to serde's "Serialize" and "Deserialize", but has
different design targets:

* Guest runtime performance is paramount.
* It's a significant performance degradation for the guest to have to read a
  value that's not aligned on a 32-bit boundary.
* Space efficiency is nice, but less important than guest runtime
   performance.
* We want to conveniently be able to take cryptographic hashes of a
  structure.

In response, zeroio does these things differently than serde:

* There is only one on-wire format; zeroio does not try to be as featureful
  as serde.
* Datatypes available are much more limited
* We don't want to spend any cycles deserializing or copying, so we store
  the data in a format that's easy to access without copying, similarly to
  the `rkyv' crate.
* In contrast to rkyv, we use slices instead of pointers to refer to
  available serialized data.  This allows us to avoid unsafe code.
* We store all data buffers as [u32] (as opposed to the more common [u8]).
* There is one canonical format; any serialization of the same data will
  construct the same structure.  To take a cryptographic hash, we simply
  hash the [u32] slice.
* We null-pad all data buffers up to the size of the hash block (with one
  word remaining) to avoid copying when computing a hash.

Note that for deserializing, while we guarantee sha(a) == sha(b)
implies deserialize_from(a) == deserialize_from(b), we do not
guarantee the converse, that deserialize_from(a) ==
deserialize_from(b) implies a == b.
