#ifndef __FR_H
#define __FR_H

#include <cstdint>
#include <string>
#include <gmp.h>
#include <assert.h>

#ifdef __APPLE__
#include <sys/types.h> // typedef unsigned int uint;
#endif // __APPLE__

#include <cstdint>

#define Fr_N64 4
#define Fr_SHORT           0x00000000
#define Fr_MONTGOMERY      0x40000000
#define Fr_SHORTMONTGOMERY 0x40000000
#define Fr_LONG            0x80000000
#define Fr_LONGMONTGOMERY  0xC0000000

static_assert(sizeof(mp_limb_t) == sizeof(uint64_t), "expected 64-bit GMP");
typedef mp_limb_t FrRawElement[Fr_N64];

typedef struct __attribute__((__packed__)) {
    int32_t shortVal;
    uint32_t type;
    FrRawElement longVal;
} FrElement;

typedef FrElement *PFrElement;

extern FrElement Fr_q;

void Fr_copy(PFrElement r, PFrElement a);
void Fr_copyn(PFrElement r, PFrElement a, int n);
int Fr_toInt(PFrElement pE);
void Fr_str2element(PFrElement pE, char const*s, uint base);
char *Fr_element2str(PFrElement pE);
void Fr_add(PFrElement r, PFrElement a, PFrElement b);
void Fr_sub(PFrElement r, PFrElement a, PFrElement b);
void Fr_mul(PFrElement r, PFrElement a, PFrElement b);
void Fr_inv(PFrElement r, PFrElement a);
void Fr_div(PFrElement r, PFrElement a, PFrElement b);
void Fr_idiv(PFrElement r, PFrElement a, PFrElement b);
void Fr_mod(PFrElement r, PFrElement a, PFrElement b);
void Fr_pow(PFrElement r, PFrElement a, PFrElement b);

void Fr_shl(PFrElement r, PFrElement a, PFrElement b);
void Fr_shr(PFrElement r, PFrElement a, PFrElement b);
void Fr_band(PFrElement r, PFrElement a, PFrElement b);
void Fr_bor(PFrElement r, PFrElement a, PFrElement b);
void Fr_bxor(PFrElement r, PFrElement a, PFrElement b);
void Fr_bnot(PFrElement r, PFrElement a);

void Fr_eq(PFrElement r, PFrElement a, PFrElement b);
void Fr_neq(PFrElement r, PFrElement a, PFrElement b);
void Fr_gt(PFrElement r, PFrElement a, PFrElement b);
void Fr_leq(PFrElement r, PFrElement a, PFrElement b);
void Fr_geq(PFrElement r, PFrElement a, PFrElement b);

void Fr_lor(PFrElement r, PFrElement a, PFrElement b);
void Fr_lnot(PFrElement r, PFrElement a);
void Fr_land(PFrElement r, PFrElement a, PFrElement b);
void Fr_neg(PFrElement r, PFrElement a);
int Fr_isTrue(PFrElement pE);
void Fr_lt(PFrElement r, PFrElement a, PFrElement b);


void Fr_toNormal(PFrElement r, PFrElement a);
void Fr_toLongNormal(PFrElement r, PFrElement a);
void Fr_toMontgomery(PFrElement r, PFrElement a);


//void Fr_fail();
//void Fr_longErr();





#endif // __FR_H
