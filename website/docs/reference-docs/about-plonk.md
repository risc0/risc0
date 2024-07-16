# About PLONK and PLOOKUP

The [PLONK paper](https://eprint.iacr.org/2019/953) introduced an efficient technique for enforcing the validity of memory operations in arguments of computational integrity.
Building on top of PLONK, the [PLOOKUP paper](https://eprint.iacr.org/2020/315.pdf) introduced a method of enforcing the validity of lookup operations.

## Relevance in RISC Zero

RISC Zero's zkVM makes use of both PLONK and PLOOKUP in the process of generating a [receipt].
PLONK is used to generate constraints that authenticate [re-ordering of RISC-V memory data](https://www.youtube.com/watch?v=dYuEPvRLwLo\&list=PLcPzhUaCxlCiLk_VjLUNbmfb2mB1Y_N9N\&index=6).
PLOOKUP is used to generate constraints that enforce a bytes-based range-check.

_Note: RISC Zero uses an AIR-based arithmetization and not a PLONK-based arithmetization._

## Documentation

Implementation and documentation for RISC Zero's use of PLONK and PLOOKUP are in [plonk.rs](https://github.com/risc0/risc0/blob/3d00debce414f96353b8295720be21029ca63347/risc0/zkvm/src/prove/plonk.rs) and [accum.rs](https://github.com/risc0/risc0/blob/3d00debce414f96353b8295720be21029ca63347/risc0/zkp/src/prove/accum.rs).

## Basic Function

PLONK makes uses of [accumulators](https://hackmd.io/@relgabizon/ByFgSDA7D) in order to ensure that one list is a permutation of another.
PLOOKUP uses PLONK to ensure that one list is contained in another list.

## Suggested Reading and Videos

For more on how these ideas fit into RISC Zero's system, we recommend our talk from zk Summit 7: [Encoding Von-Neumann Architectures in Zero-Knowledge Proof Systems](https://www.youtube.com/watch?v=od033ugtlYQ\&list=PLcPzhUaCxlCgCvzkkaBWzVuHdBRsTNxj1\&index=7).
For general references, we recommend the following:

### Less Technical

- [ZK Podcast episode](https://www.youtube.com/watch?v=n6_nicI4ckM\&t=2629s) with the authors of the PLONK paper
- [Vitalik's PLONK intro](https://vitalik.eth.limo/general/2019/09/22/plonk.html)
- [@0xtaetaehoho's PLONK Skilltree](https://twitter.com/0xtaetaehoho/status/1618979438913527814)

### Moderately Technical

- [ZK Study Club on PLONK](https://www.youtube.com/watch?v=NqrVcDuQ8hM)
- ZK Whiteboard sessions on [PLONK](https://zkhack.dev/whiteboard/module-five/) and on [lookup arguments](https://zkhack.dev/whiteboard/module-six/)
- [PLOOKUP presentation at zkSummit](https://www.youtube.com/watch?v=Vdlc1CmRYRY)
- [Ariel Gabizon explains grand product arguments](https://hackmd.io/@relgabizon/ByFgSDA7D)

### Very Technical

- [PLONK paper](https://eprint.iacr.org/2019/953)
- [PLOOKUP paper](https://eprint.iacr.org/2020/315.pdf)

[receipt]: https://docs.rs/risc0-zkvm/*/risc0_zkvm/struct.Receipt.html
