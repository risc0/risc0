// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

const int S = 27;

#ifdef BABY_BEAR_CANONICAL

const fr_t group_gen = fr_t(0x1f);  // primitive_root(0x78000001)
const fr_t group_gen_inverse = fr_t(0x03def7be);

// Values in Montgomery form

const fr_t forward_roots_of_unity[S + 1] = {
    fr_t(0x0ffffffeu),
    fr_t(0x68000003u),
    fr_t(0x1c38d511u),
    fr_t(0x3d85298fu),
    fr_t(0x5f06e481u),
    fr_t(0x3f5c39ecu),
    fr_t(0x5516a97au),
    fr_t(0x3d6be592u),
    fr_t(0x5bb04149u),
    fr_t(0x4907f9abu),
    fr_t(0x548b8e90u),
    fr_t(0x1d8ca617u),
    fr_t(0x2ce7f0e6u),
    fr_t(0x621b371fu),
    fr_t(0x6d4d2d78u),
    fr_t(0x18716fcdu),
    fr_t(0x3b30a682u),
    fr_t(0x1c6f4728u),
    fr_t(0x59b01f7cu),
    fr_t(0x1a7f97acu),
    fr_t(0x0732561cu),
    fr_t(0x2b5a1cd4u),
    fr_t(0x6f7d26f9u),
    fr_t(0x16e2f919u),
    fr_t(0x285ab85bu),
    fr_t(0x0dd5a9ecu),
    fr_t(0x43f13568u),
    fr_t(0x57fab6eeu)
};

const fr_t inverse_roots_of_unity[S + 1] = {
    fr_t(0x0ffffffeu),
    fr_t(0x68000003u),
    fr_t(0x5bc72af0u),
    fr_t(0x02ec07f3u),
    fr_t(0x67e027cau),
    fr_t(0x5e1a0700u),
    fr_t(0x4bcc008cu),
    fr_t(0x0bed94d1u),
    fr_t(0x330b2e00u),
    fr_t(0x6b469805u),
    fr_t(0x0d83fad2u),
    fr_t(0x26e64394u),
    fr_t(0x0855523bu),
    fr_t(0x5c9f0045u),
    fr_t(0x5a7ba8c3u),
    fr_t(0x3c8b04e2u),
    fr_t(0x0c0f2066u),
    fr_t(0x1b51d34cu),
    fr_t(0x59f9bc12u),
    fr_t(0x3511f012u),
    fr_t(0x061ec85fu),
    fr_t(0x5fd09c6bu),
    fr_t(0x26bdc06cu),
    fr_t(0x1272832eu),
    fr_t(0x052ce2e8u),
    fr_t(0x02ff110du),
    fr_t(0x216ce204u),
    fr_t(0x5e12c8e9u)
};

#else

const fr_t group_gen = fr_t(3);
const fr_t group_gen_inverse = fr_t(0x50000001);

// Values in Montgomery form

const fr_t forward_roots_of_unity[S + 1] = {
    fr_t(0x0ffffffeu),
    fr_t(0x68000003u),
    fr_t(0x5bc72af0u),
    fr_t(0x02ec07f3u),
    fr_t(0x67e027cau),
    fr_t(0x19e5f901u),
    fr_t(0x3b27e54au),
    fr_t(0x20d1773eu),
    fr_t(0x771ea53au),
    fr_t(0x0fb182adu),
    fr_t(0x146d1455u),
    fr_t(0x3e7d65f0u),
    fr_t(0x327884f2u),
    fr_t(0x53fc8703u),
    fr_t(0x20742dd1u),
    fr_t(0x31062edau),
    fr_t(0x642b70abu),
    fr_t(0x1ccd534bu),
    fr_t(0x03cc9bf7u),
    fr_t(0x6686182fu),
    fr_t(0x2e2516d3u),
    fr_t(0x5701b5c8u),
    fr_t(0x193a6352u),
    fr_t(0x112fc5b9u),
    fr_t(0x63ec6b91u),
    fr_t(0x5b34b3ffu),
    fr_t(0x3fff6398u),
    fr_t(0x1ffffedcu)
};

const fr_t inverse_roots_of_unity[S + 1] = {
    fr_t(0x0ffffffeu),
    fr_t(0x68000003u),
    fr_t(0x1c38d511u),
    fr_t(0x3d85298fu),
    fr_t(0x5f06e481u),
    fr_t(0x38a3c615u),
    fr_t(0x4ed6e525u),
    fr_t(0x55372b64u),
    fr_t(0x4d88ae94u),
    fr_t(0x5806fd5eu),
    fr_t(0x2ced6d6au),
    fr_t(0x1851eacdu),
    fr_t(0x2fa36b4du),
    fr_t(0x0a556a3bu),
    fr_t(0x18ae7209u),
    fr_t(0x742ba568u),
    fr_t(0x3f462cbau),
    fr_t(0x50b5c3b2u),
    fr_t(0x0dfdfca6u),
    fr_t(0x3821b546u),
    fr_t(0x45e4cd80u),
    fr_t(0x3e6793bdu),
    fr_t(0x5bdeafa3u),
    fr_t(0x2e01d37au),
    fr_t(0x2da9f4f0u),
    fr_t(0x1db7e183u),
    fr_t(0x167ca34bu),
    fr_t(0x50b3630au)
};
#endif

const fr_t domain_size_inverse[S + 1] = {
    fr_t(0x0ffffffeu),
    fr_t(0x07ffffffu),
    fr_t(0x40000000u),
    fr_t(0x20000000u),
    fr_t(0x10000000u),
    fr_t(0x08000000u),
    fr_t(0x04000000u),
    fr_t(0x02000000u),
    fr_t(0x01000000u),
    fr_t(0x00800000u),
    fr_t(0x00400000u),
    fr_t(0x00200000u),
    fr_t(0x00100000u),
    fr_t(0x00080000u),
    fr_t(0x00040000u),
    fr_t(0x00020000u),
    fr_t(0x00010000u),
    fr_t(0x00008000u),
    fr_t(0x00004000u),
    fr_t(0x00002000u),
    fr_t(0x00001000u),
    fr_t(0x00000800u),
    fr_t(0x00000400u),
    fr_t(0x00000200u),
    fr_t(0x00000100u),
    fr_t(0x00000080u),
    fr_t(0x00000040u),
    fr_t(0x00000020u)
};
