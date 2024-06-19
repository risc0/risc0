// This is musl-libc commit 37e18b7bf307fa4a8c745feebfcba54a0ba74f30:
//
// src/string/memcpy.c
//
// This was compiled into assembly with:
//
// clang-14 -target riscv32 -march=rv32im -O3 -S memcpy.c -nostdlib -fno-builtin -funroll-loops
//
// and labels manually updated to not conflict.
//
// musl as a whole is licensed under the following standard MIT license:
//
// ----------------------------------------------------------------------
// Copyright © 2005-2020 Rich Felker, et al.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ----------------------------------------------------------------------
//
// Authors/contributors include:
//
// A. Wilcox
// Ada Worcester
// Alex Dowad
// Alex Suykov
// Alexander Monakov
// Andre McCurdy
// Andrew Kelley
// Anthony G. Basile
// Aric Belsito
// Arvid Picciani
// Bartosz Brachaczek
// Benjamin Peterson
// Bobby Bingham
// Boris Brezillon
// Brent Cook
// Chris Spiegel
// Clément Vasseur
// Daniel Micay
// Daniel Sabogal
// Daurnimator
// David Carlier
// David Edelsohn
// Denys Vlasenko
// Dmitry Ivanov
// Dmitry V. Levin
// Drew DeVault
// Emil Renner Berthing
// Fangrui Song
// Felix Fietkau
// Felix Janda
// Gianluca Anzolin
// Hauke Mehrtens
// He X
// Hiltjo Posthuma
// Isaac Dunham
// Jaydeep Patil
// Jens Gustedt
// Jeremy Huntwork
// Jo-Philipp Wich
// Joakim Sindholt
// John Spencer
// Julien Ramseier
// Justin Cormack
// Kaarle Ritvanen
// Khem Raj
// Kylie McClain
// Leah Neukirchen
// Luca Barbato
// Luka Perkov
// M Farkas-Dyck (Strake)
// Mahesh Bodapati
// Markus Wichmann
// Masanori Ogino
// Michael Clark
// Michael Forney
// Mikhail Kremnyov
// Natanael Copa
// Nicholas J. Kain
// orc
// Pascal Cuoq
// Patrick Oppenlander
// Petr Hosek
// Petr Skocik
// Pierre Carrier
// Reini Urban
// Rich Felker
// Richard Pennington
// Ryan Fairfax
// Samuel Holland
// Segev Finer
// Shiz
// sin
// Solar Designer
// Stefan Kristiansson
// Stefan O'Rear
// Szabolcs Nagy
// Timo Teräs
// Trutz Behn
// Valentin Ochs
// Will Dietz
// William Haddon
// William Pitcock
//
// Portions of this software are derived from third-party works licensed
// under terms compatible with the above MIT license:
//
// The TRE regular expression implementation (src/regex/reg* and
// src/regex/tre*) is Copyright © 2001-2008 Ville Laurikari and licensed
// under a 2-clause BSD license (license text in the source files). The
// included version has been heavily modified by Rich Felker in 2012, in
// the interests of size, simplicity, and namespace cleanliness.
//
// Much of the math library code (src/math/* and src/complex/*) is
// Copyright © 1993,2004 Sun Microsystems or
// Copyright © 2003-2011 David Schultz or
// Copyright © 2003-2009 Steven G. Kargl or
// Copyright © 2003-2009 Bruce D. Evans or
// Copyright © 2008 Stephen L. Moshier or
// Copyright © 2017-2018 Arm Limited
// and labelled as such in comments in the individual source files. All
// have been licensed under extremely permissive terms.
//
// The ARM memcpy code (src/string/arm/memcpy.S) is Copyright © 2008
// The Android Open Source Project and is licensed under a two-clause BSD
// license. It was taken from Bionic libc, used on Android.
//
// The AArch64 memcpy and memset code (src/string/aarch64/*) are
// Copyright © 1999-2019, Arm Limited.
//
// The implementation of DES for crypt (src/crypt/crypt_des.c) is
// Copyright © 1994 David Burren. It is licensed under a BSD license.
//
// The implementation of blowfish crypt (src/crypt/crypt_blowfish.c) was
// originally written by Solar Designer and placed into the public
// domain. The code also comes with a fallback permissive license for use
// in jurisdictions that may not recognize the public domain.
//
// The smoothsort implementation (src/stdlib/qsort.c) is Copyright © 2011
// Valentin Ochs and is licensed under an MIT-style license.
//
// The x86_64 port was written by Nicholas J. Kain and is licensed under
// the standard MIT terms.
//
// The mips and microblaze ports were originally written by Richard
// Pennington for use in the ellcc project. The original code was adapted
// by Rich Felker for build system and code conventions during upstream
// integration. It is licensed under the standard MIT terms.
//
// The mips64 port was contributed by Imagination Technologies and is
// licensed under the standard MIT terms.
//
// The powerpc port was also originally written by Richard Pennington,
// and later supplemented and integrated by John Spencer. It is licensed
// under the standard MIT terms.
//
// All other files which have no copyright comments are original works
// produced specifically for use as part of this library, written either
// by Rich Felker, the main author of the library, or by one or more
// contributors listed above. Details on authorship of individual files
// can be found in the git version control history of the project. The
// omission of copyright and license comments in each file is in the
// interest of source tree size.
//
// In addition, permission is hereby granted for all public header files
// (include/* and arch/* /bits/* ) and crt files intended to be linked into
// applications (crt/*, ldso/dlstart.c, and arch/* /crt_arch.h) to omit
// the copyright notice and permission notice otherwise required by the
// license, and to use these files without any requirement of
// attribution. These files include substantial contributions from:
//
// Bobby Bingham
// John Spencer
// Nicholas J. Kain
// Rich Felker
// Richard Pennington
// Stefan Kristiansson
// Szabolcs Nagy
//
// all of whom have explicitly granted such permission.
//
// This file previously contained text expressing a belief that most of
// the files covered by the above exception were sufficiently trivial not
// to be subject to copyright, resulting in confusion over whether it
// negated the permissions granted in the license. In the spirit of
// permissive licensing, and of not having licensing issues being an
// obstacle to adoption, that text has been removed.
	.text
	.attribute	4, 16
	.attribute	5, "rv32im"
	.file	"musl_memcpy.c"
	.globl	memcpy
	.p2align	2
	.type	memcpy,@function
memcpy:
	andi	a3, a1, 3
	seqz	a3, a3
	seqz	a4, a2
	or	a3, a3, a4
	bnez	a3, .LBBmemcpy0_11
	addi	a5, a1, 1
	mv	a6, a0
.LBBmemcpy0_2:
	lb	a7, 0(a1)
	addi	a4, a1, 1
	addi	a3, a6, 1
	sb	a7, 0(a6)
	addi	a2, a2, -1
	andi	a1, a5, 3
	snez	a1, a1
	snez	a6, a2
	and	a7, a1, a6
	addi	a5, a5, 1
	mv	a1, a4
	mv	a6, a3
	bnez	a7, .LBBmemcpy0_2
	andi	a1, a3, 3
	beqz	a1, .LBBmemcpy0_12
.LBBmemcpy0_4:
	li	a5, 32
	bltu	a2, a5, .LBBmemcpy0_26
	li	a5, 3
	beq	a1, a5, .LBBmemcpy0_19
	li	a5, 2
	beq	a1, a5, .LBBmemcpy0_22
	li	a5, 1
	bne	a1, a5, .LBBmemcpy0_26
	lw	a5, 0(a4)
	sb	a5, 0(a3)
	srli	a1, a5, 8
	sb	a1, 1(a3)
	srli	a6, a5, 16
	addi	a1, a3, 3
	sb	a6, 2(a3)
	addi	a2, a2, -3
	addi	a3, a4, 16
	li	a4, 16
.LBBmemcpy0_9:
	lw	a6, -12(a3)
	srli	a5, a5, 24
	slli	a7, a6, 8
	lw	t0, -8(a3)
	or	a5, a7, a5
	sw	a5, 0(a1)
	srli	a5, a6, 24
	slli	a6, t0, 8
	lw	a7, -4(a3)
	or	a5, a6, a5
	sw	a5, 4(a1)
	srli	a6, t0, 24
	slli	t0, a7, 8
	lw	a5, 0(a3)
	or	a6, t0, a6
	sw	a6, 8(a1)
	srli	a6, a7, 24
	slli	a7, a5, 8
	or	a6, a7, a6
	sw	a6, 12(a1)
	addi	a1, a1, 16
	addi	a2, a2, -16
	addi	a3, a3, 16
	bltu	a4, a2, .LBBmemcpy0_9
	addi	a4, a3, -13
	j	.LBBmemcpy0_25
.LBBmemcpy0_11:
	mv	a3, a0
	mv	a4, a1
	andi	a1, a3, 3
	bnez	a1, .LBBmemcpy0_4
.LBBmemcpy0_12:
	li	a1, 16
	bltu	a2, a1, .LBBmemcpy0_15
	li	a1, 15
.LBBmemcpy0_14:
	lw	a5, 0(a4)
	lw	a6, 4(a4)
	lw	a7, 8(a4)
	lw	t0, 12(a4)
	sw	a5, 0(a3)
	sw	a6, 4(a3)
	sw	a7, 8(a3)
	sw	t0, 12(a3)
	addi	a4, a4, 16
	addi	a2, a2, -16
	addi	a3, a3, 16
	bltu	a1, a2, .LBBmemcpy0_14
.LBBmemcpy0_15:
	andi	a1, a2, 8
	beqz	a1, .LBBmemcpy0_17
	lw	a1, 0(a4)
	lw	a5, 4(a4)
	sw	a1, 0(a3)
	sw	a5, 4(a3)
	addi	a3, a3, 8
	addi	a4, a4, 8
.LBBmemcpy0_17:
	andi	a1, a2, 4
	beqz	a1, .LBBmemcpy0_30
	lw	a1, 0(a4)
	sw	a1, 0(a3)
	addi	a3, a3, 4
	addi	a4, a4, 4
	j	.LBBmemcpy0_30
.LBBmemcpy0_19:
	lw	a5, 0(a4)
	addi	a1, a3, 1
	sb	a5, 0(a3)
	addi	a2, a2, -1
	addi	a3, a4, 16
	li	a4, 18
.LBBmemcpy0_20:
	lw	a6, -12(a3)
	srli	a5, a5, 8
	slli	a7, a6, 24
	lw	t0, -8(a3)
	or	a5, a7, a5
	sw	a5, 0(a1)
	srli	a5, a6, 8
	slli	a6, t0, 24
	lw	a7, -4(a3)
	or	a5, a6, a5
	sw	a5, 4(a1)
	srli	a6, t0, 8
	slli	t0, a7, 24
	lw	a5, 0(a3)
	or	a6, t0, a6
	sw	a6, 8(a1)
	srli	a6, a7, 8
	slli	a7, a5, 24
	or	a6, a7, a6
	sw	a6, 12(a1)
	addi	a1, a1, 16
	addi	a2, a2, -16
	addi	a3, a3, 16
	bltu	a4, a2, .LBBmemcpy0_20
	addi	a4, a3, -15
	j	.LBBmemcpy0_25
.LBBmemcpy0_22:
	lw	a5, 0(a4)
	sb	a5, 0(a3)
	srli	a6, a5, 8
	addi	a1, a3, 2
	sb	a6, 1(a3)
	addi	a2, a2, -2
	addi	a3, a4, 16
	li	a4, 17
.LBBmemcpy0_23:
	lw	a6, -12(a3)
	srli	a5, a5, 16
	slli	a7, a6, 16
	lw	t0, -8(a3)
	or	a5, a7, a5
	sw	a5, 0(a1)
	srli	a5, a6, 16
	slli	a6, t0, 16
	lw	a7, -4(a3)
	or	a5, a6, a5
	sw	a5, 4(a1)
	srli	a6, t0, 16
	slli	t0, a7, 16
	lw	a5, 0(a3)
	or	a6, t0, a6
	sw	a6, 8(a1)
	srli	a6, a7, 16
	slli	a7, a5, 16
	or	a6, a7, a6
	sw	a6, 12(a1)
	addi	a1, a1, 16
	addi	a2, a2, -16
	addi	a3, a3, 16
	bltu	a4, a2, .LBBmemcpy0_23
	addi	a4, a3, -14
.LBBmemcpy0_25:
	mv	a3, a1
.LBBmemcpy0_26:
	andi	a1, a2, 16
	bnez	a1, .LBBmemcpy0_35
	andi	a1, a2, 8
	bnez	a1, .LBBmemcpy0_36
.LBBmemcpy0_28:
	andi	a1, a2, 4
	beqz	a1, .LBBmemcpy0_30
.LBBmemcpy0_29:
	lb	a1, 0(a4)
	lb	a5, 1(a4)
	lb	a6, 2(a4)
	sb	a1, 0(a3)
	sb	a5, 1(a3)
	lb	a1, 3(a4)
	sb	a6, 2(a3)
	addi	a4, a4, 4
	addi	a5, a3, 4
	sb	a1, 3(a3)
	mv	a3, a5
.LBBmemcpy0_30:
	andi	a1, a2, 2
	bnez	a1, .LBBmemcpy0_33
	andi	a1, a2, 1
	bnez	a1, .LBBmemcpy0_34
.LBBmemcpy0_32:
	ret
.LBBmemcpy0_33:
	lb	a1, 0(a4)
	lb	a5, 1(a4)
	sb	a1, 0(a3)
	addi	a4, a4, 2
	addi	a1, a3, 2
	sb	a5, 1(a3)
	mv	a3, a1
	andi	a1, a2, 1
	beqz	a1, .LBBmemcpy0_32
.LBBmemcpy0_34:
	lb	a1, 0(a4)
	sb	a1, 0(a3)
	ret
.LBBmemcpy0_35:
	lb	a1, 0(a4)
	lb	a5, 1(a4)
	lb	a6, 2(a4)
	sb	a1, 0(a3)
	sb	a5, 1(a3)
	lb	a1, 3(a4)
	sb	a6, 2(a3)
	lb	a5, 4(a4)
	lb	a6, 5(a4)
	sb	a1, 3(a3)
	lb	a1, 6(a4)
	sb	a5, 4(a3)
	sb	a6, 5(a3)
	lb	a5, 7(a4)
	sb	a1, 6(a3)
	lb	a1, 8(a4)
	lb	a6, 9(a4)
	sb	a5, 7(a3)
	lb	a5, 10(a4)
	sb	a1, 8(a3)
	sb	a6, 9(a3)
	lb	a1, 11(a4)
	sb	a5, 10(a3)
	lb	a5, 12(a4)
	lb	a6, 13(a4)
	sb	a1, 11(a3)
	lb	a1, 14(a4)
	sb	a5, 12(a3)
	sb	a6, 13(a3)
	lb	a5, 15(a4)
	sb	a1, 14(a3)
	addi	a4, a4, 16
	addi	a1, a3, 16
	sb	a5, 15(a3)
	mv	a3, a1
	andi	a1, a2, 8
	beqz	a1, .LBBmemcpy0_28
.LBBmemcpy0_36:
	lb	a1, 0(a4)
	lb	a5, 1(a4)
	lb	a6, 2(a4)
	sb	a1, 0(a3)
	sb	a5, 1(a3)
	lb	a1, 3(a4)
	sb	a6, 2(a3)
	lb	a5, 4(a4)
	lb	a6, 5(a4)
	sb	a1, 3(a3)
	lb	a1, 6(a4)
	sb	a5, 4(a3)
	sb	a6, 5(a3)
	lb	a5, 7(a4)
	sb	a1, 6(a3)
	addi	a4, a4, 8
	addi	a1, a3, 8
	sb	a5, 7(a3)
	mv	a3, a1
	andi	a1, a2, 4
	bnez	a1, .LBBmemcpy0_29
	j	.LBBmemcpy0_30
.Lfuncmemcpy_end0:
	.size	memcpy, .Lfuncmemcpy_end0-memcpy

	.ident	"Ubuntu clang version 14.0.6-++20220622053131+f28c006a5895-1~exp1~20220622173215.157"
	.section	".note.GNU-stack","",@progbits
	.addrsig
