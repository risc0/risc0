#include "fr.hpp"
#include <cstdint>
#include <cstring>

static_assert(sizeof(uint64_t) == sizeof(mp_limb_t), "expected 64-bit GMP");

FrElement Fr_q  = {0, Fr_LONG, { 0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029 } };
FrElement Fr_R2 = {0, Fr_LONG, { 0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5 } };
FrElement Fr_R3 = {0, Fr_LONG, { 0x5e94d8e1b4bf0040,0x2a489cbe1cfbb6b8,0x893cc664a19fcfed,0xcf8594b7fcc657c } };

static FrRawElement half = { 0xa1f0fac9f8000000,0x9419f4243cdcb848,0xdc2822db40c0ac2e,0x183227397098d014 };
static FrRawElement zero = {0};


static mp_limb_t     Fr_rawq[] = { 0x43e1f593f0000001,0x2833e84879b97091,0xb85045b68181585d,0x30644e72e131a029, 0 };
static FrRawElement Fr_rawR2  = { 0x1bb8e645ae216da7,0x53fe3ab1e35c59e3,0x8c49833d53bb8085,0x216d0b17f4e44a5 };
static mp_limb_t     Fr_np     = 0xc2e1f593efffffff;
static mp_limb_t     lboMask   = 0x3fffffffffffffff;


void Fr_rawAdd(FrRawElement pRawResult, const FrRawElement pRawA, const FrRawElement pRawB)
{
    uint64_t carry = mpn_add_n(pRawResult, pRawA, pRawB, Fr_N64);

    if(carry || mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawAddLS(FrRawElement pRawResult, FrRawElement pRawA, uint64_t rawB)
{
    uint64_t carry = mpn_add_1(pRawResult, pRawA, Fr_N64, rawB);

    if(carry || mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawSub(FrRawElement pRawResult, const FrRawElement pRawA, const FrRawElement pRawB)
{
    uint64_t carry = mpn_sub_n(pRawResult, pRawA, pRawB, Fr_N64);

    if(carry)
    {
        mpn_add_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawSubRegular(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mpn_sub_n(pRawResult, pRawA, pRawB, Fr_N64);
}

void Fr_rawSubSL(FrRawElement pRawResult, uint64_t rawA, FrRawElement pRawB)
{
    FrRawElement pRawA = {rawA};

    uint64_t carry = mpn_sub_n(pRawResult, pRawA, pRawB, Fr_N64);

    if(carry)
    {
        mpn_add_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawSubLS(FrRawElement pRawResult, FrRawElement pRawA, uint64_t rawB)
{
    uint64_t carry = mpn_sub_1(pRawResult, pRawA, Fr_N64, rawB);

    if(carry)
    {
        mpn_add_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawNeg(FrRawElement pRawResult, const FrRawElement pRawA)
{
    if (mpn_cmp(pRawA, zero, Fr_N64) != 0)
    {
        mpn_sub_n(pRawResult, Fr_rawq, pRawA, Fr_N64);
    }
    else
    {
        mpn_copyi(pRawResult, zero, Fr_N64);
    }
}

//  Substracts a long element and a short element form 0
void Fr_rawNegLS(FrRawElement pRawResult, FrRawElement pRawA, uint64_t rawB)
{
    uint64_t carry1 = mpn_sub_1(pRawResult, Fr_rawq, Fr_N64, rawB);
    uint64_t carry2 = mpn_sub_n(pRawResult, pRawResult, pRawA, Fr_N64);

    if (carry1 || carry2)
    {
        mpn_add_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawCopy(FrRawElement pRawResult, const FrRawElement pRawA)
{
    memcpy(pRawResult, pRawA, sizeof(FrRawElement));
}

int Fr_rawIsEq(const FrRawElement pRawA, const FrRawElement pRawB)
{
    return mpn_cmp(pRawA, pRawB, Fr_N64) == 0;
}

void Fr_rawMMul(FrRawElement pRawResult, const FrRawElement pRawA, const FrRawElement pRawB)
{
    const mp_size_t  N = Fr_N64+1;
    const mp_limb_t  *mq = Fr_rawq;

    uint64_t  np0;
    mp_limb_t  product0[N] = {0};
    mp_limb_t  product1[N] = {0};
    mp_limb_t  product2[N] = {0};
    mp_limb_t  product3[N] = {0};
    product0[N-1] = mpn_mul_1(product0, pRawB, Fr_N64, pRawA[0]);
    np0 = Fr_np * product0[0];
    //product1[1] = mpn_addmul_1(product0, mq, N, np0);
    product1[N-1] = mpn_addmul_1(product0, mq, N, np0);

    product1[N-1] = mpn_addmul_1(product1, pRawB, Fr_N64, pRawA[1]);
    mpn_add(product1, product1, N, product0+1, N-1);

    np0 = Fr_np * product1[0];
    //product2[1] = mpn_addmul_1(product1, mq, N, np0);
    product2[N-1] = mpn_addmul_1(product1, mq, N, np0);

    product2[N-1] = mpn_addmul_1(product2, pRawB, Fr_N64, pRawA[2]);
    mpn_add(product2, product2, N, product1+1, N-1);

    np0 = Fr_np * product2[0];
    //product3[1] = mpn_addmul_1(product2, mq, N, np0);
    product3[N-1] = mpn_addmul_1(product2, mq, N, np0);

    product3[N-1] = mpn_addmul_1(product3, pRawB, Fr_N64, pRawA[3]);
    mpn_add(product3, product3, N, product2+1, N-1);

    np0 = Fr_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fr_N64);

    if (mpn_cmp(pRawResult, mq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fr_N64);
    }
}
    
void Fr_rawMSquare(FrRawElement pRawResult, const FrRawElement pRawA)
{
    Fr_rawMMul(pRawResult, pRawA, pRawA);
}

void Fr_rawMMul1(FrRawElement pRawResult, const FrRawElement pRawA, uint64_t pRawB)
{
    const mp_size_t  N = Fr_N64+1;
    const mp_limb_t  *mq = Fr_rawq;
    uint64_t  np0;
    mp_limb_t  product0[N] = {0};
    mp_limb_t  product1[N] = {0};
    mp_limb_t  product2[N] = {0};
    mp_limb_t  product3[N] = {0};
    product0[N-1] = mpn_mul_1(product0, pRawA, Fr_N64, pRawB);
    np0 = Fr_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);
    np0 = Fr_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);
    np0 = Fr_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);
    np0 = Fr_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fr_N64);

    if (mpn_cmp(pRawResult, mq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fr_N64);
    }
}

void Fr_rawToMontgomery(FrRawElement pRawResult, const FrRawElement pRawA)
{
    Fr_rawMMul(pRawResult, pRawA, Fr_rawR2);
}

void Fr_rawFromMontgomery(FrRawElement pRawResult, const FrRawElement pRawA)
{
    const mp_size_t  N = Fr_N64+1;
    const mp_limb_t  *mq = Fr_rawq;
    uint64_t  np0;
    mp_limb_t  product0[N];
    mp_limb_t  product1[N] = {0};
    mp_limb_t  product2[N] = {0};
    mp_limb_t  product3[N] = {0};
    mpn_copyi(product0, pRawA, Fr_N64); product0[N-1] = 0;
    np0 = Fr_np * product0[0];
    product1[1] = mpn_addmul_1(product0, mq, N, np0);
    mpn_add(product1, product1, N, product0+1, N-1);
    np0 = Fr_np * product1[0];
    product2[1] = mpn_addmul_1(product1, mq, N, np0);
    mpn_add(product2, product2, N, product1+1, N-1);
    np0 = Fr_np * product2[0];
    product3[1] = mpn_addmul_1(product2, mq, N, np0);
    mpn_add(product3, product3, N, product2+1, N-1);
    np0 = Fr_np * product3[0];
    mpn_addmul_1(product3, mq, N, np0);

    mpn_copyi(pRawResult,  product3+1, Fr_N64);

    if (mpn_cmp(pRawResult, mq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, mq, Fr_N64);
    }
}


int Fr_rawIsZero(const FrRawElement rawA)
{
    return mpn_zero_p(rawA, Fr_N64) ? 1 : 0;
}

int Fr_rawCmp(FrRawElement pRawA, FrRawElement pRawB)
{
    return mpn_cmp(pRawA, pRawB, Fr_N64);
}

void Fr_rawSwap(FrRawElement pRawResult, FrRawElement pRawA)
{
    FrRawElement temp;

    Fr_rawCopy(temp, pRawResult);
    Fr_rawCopy(pRawResult, pRawA);
    Fr_rawCopy(pRawA, temp);
}

void Fr_rawCopyS2L(FrRawElement pRawResult, int64_t val)
{
    pRawResult[0] = val;
    pRawResult[1] = 0;
    pRawResult[2] = 0;
    pRawResult[3] = 0;

    if (val < 0) {
    pRawResult[1] = -1;
    pRawResult[2] = -1;
    pRawResult[3] = -1;

        mpn_add_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawAnd(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mpn_and_n(pRawResult, pRawA, pRawB, Fr_N64);

    pRawResult[3] &= lboMask;

    if (mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawOr(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mpn_ior_n(pRawResult, pRawA, pRawB, Fr_N64);

    pRawResult[3] &= lboMask;

    if (mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawXor(FrRawElement pRawResult, FrRawElement pRawA, FrRawElement pRawB)
{
    mpn_xor_n(pRawResult, pRawA, pRawB, Fr_N64);

    pRawResult[3] &= lboMask;

    if (mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}

void Fr_rawShl(FrRawElement r, FrRawElement a, uint64_t b)
{
    uint64_t bit_shift  = b % 64;
    uint64_t word_shift = b / 64;
    uint64_t word_count = Fr_N64 - word_shift;

    mpn_copyi(r + word_shift, a, word_count);
    std::memset(r, 0, word_shift * sizeof(uint64_t));

    if (bit_shift)
    {
        mpn_lshift(r, r, Fr_N64, bit_shift);
    }

    r[3] &= lboMask;

    if (mpn_cmp(r, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(r, r, Fr_rawq, Fr_N64);
    }
}

void Fr_rawShr(FrRawElement r, FrRawElement a, uint64_t b)
{
    const uint64_t bit_shift  = b % 64;
    const uint64_t word_shift = b / 64;
    const uint64_t word_count = Fr_N64 - word_shift;

    mpn_copyi(r, a + word_shift, word_count);
    std::memset(r + word_count, 0, word_shift * sizeof(uint64_t));

    if (bit_shift)
    {
        mpn_rshift(r, r, Fr_N64, bit_shift);
    }
}

void Fr_rawNot(FrRawElement pRawResult, FrRawElement pRawA)
{
    mpn_com(pRawResult, pRawA, Fr_N64);

    pRawResult[3] &= lboMask;

    if (mpn_cmp(pRawResult, Fr_rawq, Fr_N64) >= 0)
    {
        mpn_sub_n(pRawResult, pRawResult, Fr_rawq, Fr_N64);
    }
}


void Fr_copy(PFrElement r, const PFrElement a)
{
    *r = *a;
}

void Fr_toNormal(PFrElement r, PFrElement a)
{
    if (a->type == Fr_LONGMONTGOMERY)
    {
        r->type = Fr_LONG;
        Fr_rawFromMontgomery(r->longVal, a->longVal);
    }
    else
    {
        Fr_copy(r, a);
    }
}

static inline int has_mul32_overflow(int64_t val)
{
    int64_t sign = val >> 31;

    if (sign)
    {
        sign = ~sign;
    }

    return sign ? 1 : 0;
}

static inline int Fr_rawSMul(int64_t *r, int32_t a, int32_t b)
{
    *r = (int64_t)a * b;

    return has_mul32_overflow(*r);
}

static inline void mul_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    int64_t result;

    int overflow = Fr_rawSMul(&result, a->shortVal, b->shortVal);

    if (overflow)
    {
        Fr_rawCopyS2L(r->longVal, result);
        r->type = Fr_LONG;
        r->shortVal = 0;
    }
    else
    {
        // done the same way as in intel asm implementation
        r->shortVal = (int32_t)result;
        r->type = Fr_SHORT;
        //

        Fr_rawCopyS2L(r->longVal, result);
        r->type = Fr_LONG;
        r->shortVal = 0;
    }
}

static inline void mul_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
    Fr_rawMMul(r->longVal, r->longVal, Fr_R3.longVal);
}

static inline void mul_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ns2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    if (b->shortVal < 0)
    {
        int64_t b_shortVal = b->shortVal;
        Fr_rawMMul1(r->longVal, a->longVal, -b_shortVal);
        Fr_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fr_rawMMul1(r->longVal, a->longVal, b->shortVal);
    }

    Fr_rawMMul(r->longVal, r->longVal, Fr_R3.longVal);
}

static inline void mul_s1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    if (a->shortVal < 0)
    {
        int64_t a_shortVal = a->shortVal;
        Fr_rawMMul1(r->longVal, b->longVal, -a_shortVal);
        Fr_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fr_rawMMul1(r->longVal, b->longVal, a->shortVal);
    }

    Fr_rawMMul(r->longVal, r->longVal, Fr_R3.longVal);
}

static inline void mul_l1ms2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (b->shortVal < 0)
    {
        int64_t b_shortVal = b->shortVal;
        Fr_rawMMul1(r->longVal, a->longVal, -b_shortVal);
        Fr_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fr_rawMMul1(r->longVal, a->longVal, b->shortVal);
    }
}

static inline void mul_s1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (a->shortVal < 0)
    {
        int64_t a_shortVal = a->shortVal;
        Fr_rawMMul1(r->longVal, b->longVal, -a_shortVal);
        Fr_rawNeg(r->longVal, r->longVal);
    }
    else
    {
        Fr_rawMMul1(r->longVal, b->longVal, a->shortVal);
    }
}

static inline void mul_l1ns2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_l1ms2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_s1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

static inline void mul_s1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawMMul(r->longVal, a->longVal, b->longVal);
}

void Fr_mul(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    mul_l1ml2m(r, a, b);
                }
                else
                {
                    mul_l1ml2n(r, a, b);
                }
            }
            else
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    mul_l1nl2m(r, a, b);
                }
                else
                {
                    mul_l1nl2n(r, a, b);
                }
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            if (b->type & Fr_MONTGOMERY)
            {
                mul_l1ms2m(r, a, b);
            }
            else
            {
                mul_l1ms2n(r, a, b);
            }
        }
        else
        {
            if (b->type & Fr_MONTGOMERY)
            {
                mul_l1ns2m(r, a, b);
            }
            else
            {
                mul_l1ns2n(r, a, b);
            }
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (a->type & Fr_MONTGOMERY)
        {
            if (b->type & Fr_MONTGOMERY)
            {
                mul_s1ml2m(r, a, b);
            }
            else
            {
                mul_s1ml2n(r,a, b);
            }
        }
        else if (b->type & Fr_MONTGOMERY)
        {
            mul_s1nl2m(r, a, b);
        }
        else
        {
            mul_s1nl2n(r, a, b);
        }
    }
    else
    {
         mul_s1s2(r, a, b);
    }
}

void Fr_toLongNormal(PFrElement r, PFrElement a)
{
    if (a->type & Fr_LONG)
    {
        if (a->type & Fr_MONTGOMERY)
        {
            Fr_rawFromMontgomery(r->longVal, a->longVal);
            r->type = Fr_LONG;
        }
        else
        {
            Fr_copy(r, a);
        }
    }
    else
    {
        Fr_rawCopyS2L(r->longVal, a->shortVal);
        r->type = Fr_LONG;
        r->shortVal = 0;
    }
}

void Fr_toMontgomery(PFrElement r, PFrElement a)
{
    if (a->type & Fr_MONTGOMERY)
    {
        Fr_copy(r, a);
    }
    else if (a->type & Fr_LONG)
    {
        r->shortVal = a->shortVal;

        Fr_rawMMul(r->longVal, a->longVal, Fr_R2.longVal);

        r->type = Fr_LONGMONTGOMERY;
    }
    else if (a->shortVal < 0)
    {
        int64_t a_shortVal = a->shortVal;
       Fr_rawMMul1(r->longVal, Fr_R2.longVal, -a_shortVal);
       Fr_rawNeg(r->longVal, r->longVal);

       r->type = Fr_SHORTMONTGOMERY;
    }
    else
    {
        Fr_rawMMul1(r->longVal, Fr_R2.longVal, a->shortVal);

        r->type = Fr_SHORTMONTGOMERY;
    }
}

void Fr_copyn(PFrElement r, PFrElement a, int n)
{
    std::memcpy(r, a, n * sizeof(FrElement));
}

static inline int has_add32_overflow(int64_t val)
{
    int64_t signs = (val >> 31) & 0x3;

    return signs == 1 || signs == 2;
}

static inline int Fr_rawSSub(int64_t *r, int32_t a, int32_t b)
{
    *r = (int64_t)a - b;

    return has_add32_overflow(*r);
}

static inline void sub_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    int64_t diff;

    int overflow = Fr_rawSSub(&diff, a->shortVal, b->shortVal);

    if (overflow)
    {
        Fr_rawCopyS2L(r->longVal, diff);
        r->type = Fr_LONG;
        r->shortVal = 0;
    }
    else
    {
        r->type = Fr_SHORT;
        r->shortVal = (int32_t)diff;
    }
}

static inline void sub_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    Fr_rawSub(r->longVal, a->longVal, b->longVal);
}

static inline void sub_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement a_m;
    Fr_toMontgomery(&a_m, a);

    Fr_rawSub(r->longVal, a_m.longVal, b->longVal);
}

static inline void sub_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawSub(r->longVal, a->longVal, b->longVal);
}

static inline void sub_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement b_m;
    Fr_toMontgomery(&b_m, b);

    Fr_rawSub(r->longVal, a->longVal, b_m.longVal);
}

static inline void sub_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (a->shortVal >= 0)
    {
        Fr_rawSubSL(r->longVal, a->shortVal, b->longVal);
    }
    else
    {
        int64_t a_shortVal = a->shortVal;
        Fr_rawNegLS(r->longVal, b->longVal, -a_shortVal);
    }
}

static inline void sub_l1ms2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement b_m;
    Fr_toMontgomery(&b_m, b);

    Fr_rawSub(r->longVal, a->longVal, b_m.longVal);
}

static inline void sub_s1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement a_m;
    Fr_toMontgomery(&a_m, a);

    Fr_rawSub(r->longVal, a_m.longVal, b->longVal);
}

static inline void sub_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (b->shortVal < 0)
    {
        int64_t b_shortVal = b->shortVal;
        Fr_rawAddLS(r->longVal, a->longVal, -b_shortVal);
    }
    else
    {
        Fr_rawSubLS(r->longVal, a->longVal, b->shortVal);
    }
}

static inline void sub_l1ms2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawSub(r->longVal, a->longVal, b->longVal);
}

static inline void sub_s1ml2m(PFrElement r,PFrElement a,PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawSub(r->longVal, a->longVal, b->longVal);
}

void Fr_sub(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    sub_l1ml2m(r, a, b);
                }
                else
                {
                    sub_l1ml2n(r, a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                sub_l1nl2m(r, a, b);
            }
            else
            {
                sub_l1nl2n(r, a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            if (b->type & Fr_MONTGOMERY)
            {
                sub_l1ms2m(r, a, b);
            }
            else
            {
                sub_l1ms2n(r, a, b);
            }
        }
        else
        {
            sub_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            if (a->type & Fr_MONTGOMERY)
            {
               sub_s1ml2m(r,a,b);
            }
            else
            {
               sub_s1nl2m(r,a,b);
            }
        }
        else
        {
            sub_s1l2n(r,a,b);
        }
    }
    else
    {
         sub_s1s2(r, a, b);
    }
}

static inline int Fr_rawSAdd(int64_t *r, int32_t a, int32_t b)
{
    *r = (int64_t)a + b;

    return has_add32_overflow(*r);
}

static inline void add_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    int64_t sum;

    int overflow = Fr_rawSAdd(&sum, a->shortVal, b->shortVal);

    if (overflow)
    {
        Fr_rawCopyS2L(r->longVal, sum);
        r->type = Fr_LONG;
        r->shortVal = 0;
    }
    else
    {
        r->type = Fr_SHORT;
        r->shortVal = (int32_t)sum;
    }
}

static inline void add_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    Fr_rawAdd(r->longVal, a->longVal, b->longVal);
}

static inline void add_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement a_m;
    Fr_toMontgomery(&a_m, a);

    Fr_rawAdd(r->longVal, a_m.longVal, b->longVal);
}

static inline void add_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;
    Fr_rawAdd(r->longVal, a->longVal, b->longVal);
}

static inline void add_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement b_m;
    Fr_toMontgomery(&b_m, b);

    Fr_rawAdd(r->longVal, a->longVal, b_m.longVal);
}

static inline void add_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (a->shortVal >= 0)
    {
        Fr_rawAddLS(r->longVal, b->longVal, a->shortVal);
    }
    else
    {
        int64_t a_shortVal = a->shortVal;
        Fr_rawSubLS(r->longVal, b->longVal, -a_shortVal);
    }
}

static inline void add_l1ms2n(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement b_m;

    r->type = Fr_LONGMONTGOMERY;

    Fr_toMontgomery(&b_m, b);

    Fr_rawAdd(r->longVal, a->longVal, b_m.longVal);
}

static inline void add_s1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    FrElement m_a;
    Fr_toMontgomery(&m_a, a);

    Fr_rawAdd(r->longVal, m_a.longVal, b->longVal);
}

static inline void add_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    if (b->shortVal >= 0)
    {
        Fr_rawAddLS(r->longVal, a->longVal, b->shortVal);
    }
    else
    {
        int64_t b_shortVal = b->shortVal;
        Fr_rawSubLS(r->longVal, a->longVal, -b_shortVal);
    }
}

static inline void add_l1ms2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawAdd(r->longVal, a->longVal, b->longVal);
}

static inline void add_s1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONGMONTGOMERY;

    Fr_rawAdd(r->longVal, a->longVal, b->longVal);
}

void Fr_add(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    add_l1ml2m(r, a, b);
                }
                else
                {
                    add_l1ml2n(r, a, b);
                }
            }
            else
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    add_l1nl2m(r, a, b);
                }
                else
                {
                    add_l1nl2n(r, a, b);
                }
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            if (b->type & Fr_MONTGOMERY)
            {
                add_l1ms2m(r, a, b);
            }
            else
            {
                add_l1ms2n(r, a, b);
            }
        }
        else
        {
            add_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            if (a->type & Fr_MONTGOMERY)
            {
               add_s1ml2m(r, a, b);
            }
            else
            {
               add_s1nl2m(r, a, b);
            }
        }
        else
        {
            add_s1l2n(r, a, b);
        }
    }
    else
    {
        add_s1s2(r, a, b);
    }
}

int Fr_isTrue(PFrElement pE)
{
    int result;

    if (pE->type & Fr_LONG)
    {
        result = !Fr_rawIsZero(pE->longVal);
    }
    else
    {
        result = pE->shortVal != 0;
    }

    return result;
}

int Fr_longNeg(PFrElement pE)
{
    if(Fr_rawCmp(pE->longVal, Fr_q.longVal) >= 0)
    {
      assert(false);
       return 0;
    }

    int64_t result = pE->longVal[0] - Fr_q.longVal[0];

    int64_t is_long = (result >> 31) + 1;

    if(is_long)
    {
      assert(false);
       return 0;
    }

    return result;
}

int Fr_longNormal(PFrElement pE)
{
    uint64_t is_long = 0;
    uint64_t result;

    result = pE->longVal[0];

    is_long = result >> 31;

    if (is_long)
    {
         return Fr_longNeg(pE);
    }

    if (memcmp(&pE->longVal[1], zero, (sizeof(pE->longVal) - sizeof(pE->longVal[0]))))
    {
        return Fr_longNeg(pE);
    }

    return result;
}

// Convert a 64 bit integer to a long format field element
int Fr_toInt(PFrElement pE)
{
    int result;

    if (pE->type & Fr_LONG)
    {
       if (pE->type & Fr_MONTGOMERY)
       {
           FrElement e_n;
           Fr_toNormal(&e_n, pE);

           result = Fr_longNormal(&e_n);
       }
       else
       {
           result = Fr_longNormal(pE);
       }
    }
    else
    {
        result = pE->shortVal;
    }

    return result;
}

static inline int rlt_s1s2(PFrElement a, PFrElement b)
{
    return (a->shortVal < b->shortVal) ? 1 : 0;
}

static inline int rltRawL1L2(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(pRawB, pRawA);

    return result > 0 ? 1 : 0;
}

static inline int rltl1l2_n1(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawB);

    if (result < 0)
    {
        return rltRawL1L2(pRawA, pRawB);
    }

     return 1;
}

static inline int rltl1l2_p1(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawB);

    if (result < 0)
    {
        return 0;
    }

    return rltRawL1L2(pRawA, pRawB);
}

static inline int rltL1L2(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawA);

    if (result < 0)
    {
        return rltl1l2_n1(pRawA, pRawB);
    }

    return rltl1l2_p1(pRawA, pRawB);
}

static inline int rlt_l1nl2n(PFrElement a, PFrElement b)
{
    return rltL1L2(a->longVal, b->longVal);
}

static inline int rlt_l1nl2m(PFrElement a, PFrElement b)
{
    FrElement b_n;

    Fr_toNormal(&b_n, b);

    return rltL1L2(a->longVal, b_n.longVal);
}

static inline int rlt_l1ml2m(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    return rltL1L2(a_n.longVal, b_n.longVal);
}

static inline int rlt_l1ml2n(PFrElement a, PFrElement b)
{
    FrElement a_n;

    Fr_toNormal(&a_n, a);

    return rltL1L2(a_n.longVal, b->longVal);
}

static inline int rlt_s1l2n(PFrElement a,PFrElement b)
{
    FrElement a_n;

    Fr_toLongNormal(&a_n,a);

    return rltL1L2(a_n.longVal, b->longVal);
}

static inline int rlt_l1ms2(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_ln;

    Fr_toLongNormal(&b_ln ,b);
    Fr_toNormal(&a_n, a);

    return rltL1L2(a_n.longVal, b_ln.longVal);
}

static inline int rlt_s1l2m(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_n;

    Fr_toLongNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    return rltL1L2(a_n.longVal, b_n.longVal);
}

static inline int rlt_l1ns2(PFrElement a, PFrElement b)
{
    FrElement b_n;

    Fr_toLongNormal(&b_n, b);

    return rltL1L2(a->longVal, b_n.longVal);
}

int32_t Fr_rlt(PFrElement a, PFrElement b)
{
    int32_t result;

    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    result = rlt_l1ml2m(a, b);
                }
                else
                {
                    result = rlt_l1ml2n(a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                result = rlt_l1nl2m(a, b);
            }
            else
            {
                result = rlt_l1nl2n(a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            result = rlt_l1ms2(a, b);
        }
        else
        {
            result = rlt_l1ns2(a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            result = rlt_s1l2m(a,b);
        }
        else
        {
            result = rlt_s1l2n(a,b);
        }
    }
    else
    {
         result = rlt_s1s2(a, b);
    }

    return result;
}

void Fr_lt(PFrElement r, PFrElement a, PFrElement b)
{
    r->shortVal = Fr_rlt(a, b);
    r->type = Fr_SHORT;
}

void Fr_geq(PFrElement r, PFrElement a, PFrElement b)
{
   int32_t result = Fr_rlt(a, b);
   result ^= 0x1;

   r->shortVal = result;
   r->type = Fr_SHORT;
}

static inline int Fr_rawSNeg(int64_t *r, int32_t a)
{
    *r = -(int64_t)a;

    return has_add32_overflow(*r);
}

void Fr_neg(PFrElement r, PFrElement a)
{
    if (a->type & Fr_LONG)
    {
        r->type = a->type;
        r->shortVal = a->shortVal;
        Fr_rawNeg(r->longVal, a->longVal);
    }
    else
    {
        int64_t a_shortVal;

        int overflow = Fr_rawSNeg(&a_shortVal, a->shortVal);

        if (overflow)
        {
            Fr_rawCopyS2L(r->longVal, a_shortVal);
            r->type = Fr_LONG;
            r->shortVal = 0;
        }
        else
        {
            r->type = Fr_SHORT;
            r->shortVal = (int32_t)a_shortVal;
        }
    }
}

static inline int reqL1L2(FrRawElement pRawA, FrRawElement pRawB)
{
    return Fr_rawCmp(pRawB, pRawA) == 0;
}

static inline int req_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    return (a->shortVal == b->shortVal) ? 1 : 0;
}

static inline int req_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    return reqL1L2(a->longVal, b->longVal);
}

static inline int req_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement a_m;
    Fr_toMontgomery(&a_m, a);

    return reqL1L2(a_m.longVal, b->longVal);
}

static inline int req_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    return reqL1L2(a->longVal, b->longVal);
}

static inline int req_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement b_m;
    Fr_toMontgomery(&b_m, b);

    return reqL1L2(a->longVal, b_m.longVal);
}

static inline int req_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement a_n;
    Fr_toLongNormal(&a_n, a);

    return reqL1L2(a_n.longVal, b->longVal);
}

static inline int req_l1ms2(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement b_m;
    Fr_toMontgomery(&b_m, b);

    return reqL1L2(a->longVal, b_m.longVal);
}

static inline int req_s1l2m(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement a_m;
    Fr_toMontgomery(&a_m, a);

    return reqL1L2(a_m.longVal, b->longVal);
}

static inline int req_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    FrElement b_n;
    Fr_toLongNormal(&b_n, b);

    return reqL1L2(a->longVal, b_n.longVal);
}

// Compares two elements of any kind
int Fr_req(PFrElement r, PFrElement a, PFrElement b)
{
    int result;

    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    result = req_l1ml2m(r, a, b);
                }
                else
                {
                    result = req_l1ml2n(r, a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                result = req_l1nl2m(r, a, b);
            }
            else
            {
                result = req_l1nl2n(r, a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            result = req_l1ms2(r, a, b);
        }
        else
        {
            result = req_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            result = req_s1l2m(r, a, b);
        }
        else
        {
            result = req_s1l2n(r, a, b);
        }
    }
    else
    {
         result = req_s1s2(r, a, b);
    }

    return result;
}

void Fr_eq(PFrElement r, PFrElement a, PFrElement b)
{
    r->shortVal = Fr_req(r, a, b);
    r->type = Fr_SHORT;
}

void Fr_neq(PFrElement r, PFrElement a, PFrElement b)
{
    int result = Fr_req(r, a, b);

    r->shortVal = result ^ 0x1;
    r->type = Fr_SHORT;
}

// Logical or between two elements
void Fr_lor(PFrElement r, PFrElement a, PFrElement b)
{
    int32_t is_true_a;

    if (a->type & Fr_LONG)
    {
        is_true_a = !Fr_rawIsZero(a->longVal);
    }
    else
    {
        is_true_a = a->shortVal ? 1 : 0;
    }

    int32_t is_true_b;

    if (b->type & Fr_LONG)
    {
        is_true_b = !Fr_rawIsZero(b->longVal);
    }
    else
    {
        is_true_b = b->shortVal ? 1 : 0;
    }

    r->shortVal = is_true_a | is_true_b;
    r->type = Fr_SHORT;
}

void Fr_lnot(PFrElement r, PFrElement a)
{
    if (a->type & Fr_LONG)
    {
        r->shortVal = Fr_rawIsZero(a->longVal);
    }
    else
    {
        r->shortVal = a->shortVal ? 0 : 1;
    }

    r->type = Fr_SHORT;
}


static inline int rgt_s1s2(PFrElement a, PFrElement b)
{
    return (a->shortVal > b->shortVal) ? 1 : 0;
}

static inline int rgtRawL1L2(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(pRawB, pRawA);

    return (result < 0) ? 1 : 0;
}

static inline int rgtl1l2_n1(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawB);

    if (result < 0)
    {
        return rgtRawL1L2(pRawA, pRawB);
    }
    return 0;
}

static inline int rgtl1l2_p1(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawB);

    if (result < 0)
    {
        return 1;
    }
    return rgtRawL1L2(pRawA, pRawB);
}

static inline int rgtL1L2(FrRawElement pRawA, FrRawElement pRawB)
{
    int result = Fr_rawCmp(half, pRawA);

    if (result < 0)
    {
        return rgtl1l2_n1(pRawA, pRawB);
    }

    return rgtl1l2_p1(pRawA, pRawB);
}

static inline int rgt_l1nl2n(PFrElement a, PFrElement b)
{
    return rgtL1L2(a->longVal, b->longVal);
}

static inline int rgt_l1nl2m(PFrElement a, PFrElement b)
{
    FrElement b_n;
    Fr_toNormal(&b_n, b);

    return rgtL1L2(a->longVal, b_n.longVal);
}

static inline int rgt_l1ml2m(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    return rgtL1L2(a_n.longVal, b_n.longVal);
}

static inline int rgt_l1ml2n(PFrElement a, PFrElement b)
{
    FrElement a_n;
    Fr_toNormal(&a_n, a);

    return rgtL1L2(a_n.longVal, b->longVal);
}

static inline int rgt_s1l2n(PFrElement a, PFrElement b)
{
    FrElement a_n;
    Fr_toLongNormal(&a_n, a);

    return rgtL1L2(a_n.longVal, b->longVal);
}

static inline int rgt_l1ms2(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toLongNormal(&b_n, b);

    return rgtL1L2(a_n.longVal, b_n.longVal);
}

static inline int rgt_s1l2m(PFrElement a, PFrElement b)
{
    FrElement a_n;
    FrElement b_n;

    Fr_toLongNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    return rgtL1L2(a_n.longVal, b_n.longVal);
}

static inline int rgt_l1ns2(PFrElement a, PFrElement b)
{
    FrElement b_n;
    Fr_toLongNormal(&b_n, b);

    return rgtL1L2(a->longVal, b_n.longVal);
}

int Fr_rgt(PFrElement r, PFrElement a, PFrElement b)
{
    int result = 0;

    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    result = rgt_l1ml2m(a, b);
                }
                else
                {
                    result = rgt_l1ml2n(a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                result = rgt_l1nl2m(a, b);
            }
            else
            {
                result = rgt_l1nl2n(a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            result = rgt_l1ms2(a, b);
        }
        else
        {
            result = rgt_l1ns2(a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            result = rgt_s1l2m(a, b);
        }
        else
        {
            result = rgt_s1l2n(a,b);
        }
    }
    else
    {
         result = rgt_s1s2(a, b);
    }

    return result;
}

void Fr_gt(PFrElement r, PFrElement a, PFrElement b)
{
    r->shortVal = Fr_rgt(r, a, b);
    r->type = Fr_SHORT;
}

void Fr_leq(PFrElement r, PFrElement a, PFrElement b)
{
   int32_t result = Fr_rgt(r, a, b);
   result ^= 0x1;

   r->shortVal = result;
   r->type = Fr_SHORT;
}

// Logical and between two elements
void Fr_land(PFrElement r, PFrElement a, PFrElement b)
{
    int32_t is_true_a;

    if (a->type & Fr_LONG)
    {
        is_true_a = !Fr_rawIsZero(a->longVal);
    }
    else
    {
        is_true_a = a->shortVal ? 1 : 0;
    }

    int32_t is_true_b;

    if (b->type & Fr_LONG)
    {
        is_true_b = !Fr_rawIsZero(b->longVal);
    }
    else
    {
        is_true_b = b->shortVal ? 1 : 0;
    }

    r->shortVal = is_true_a & is_true_b;
    r->type = Fr_SHORT;
}

static inline void and_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal >= 0 && b->shortVal >= 0)
    {
        int32_t result = a->shortVal & b->shortVal;
        r->shortVal = result;
        r->type = Fr_SHORT;
        return;
    }

    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toLongNormal(&a_n, a);
    Fr_toLongNormal(&b_n, b);

    Fr_rawAnd(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void and_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawAnd(r->longVal, a->longVal, b->longVal);
}

static inline void and_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;
    Fr_toNormal(&b_n, b);

    Fr_rawAnd(r->longVal, a->longVal, b_n.longVal);
}

static inline void and_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    Fr_rawAnd(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void and_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    Fr_toNormal(&a_n, a);

    Fr_rawAnd(r->longVal, a_n.longVal, b->longVal);
}

static inline void and_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawAnd(r->longVal, a_n.longVal, b->longVal);
}

static inline void and_l1ms2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawAnd(r->longVal, b_n.longVal, a_n.longVal);
}

static inline void and_s1l2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&b_n, b);

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawAnd(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void and_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawAnd(r->longVal, a->longVal, b_n.longVal);
}

// Ands two elements of any kind
void Fr_band(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    and_l1ml2m(r, a, b);
                }
                else
                {
                    and_l1ml2n(r, a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                and_l1nl2m(r, a, b);
            }
            else
            {
                and_l1nl2n(r, a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            and_l1ms2(r, a, b);
        }
        else
        {
           and_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            and_s1l2m(r, a, b);
        }
        else
        {
            and_s1l2n(r, a, b);
        }
    }
    else
    {
         and_s1s2(r, a, b);
    }
}

void Fr_rawZero(FrRawElement pRawResult)
{
    std::memset(pRawResult, 0, sizeof(FrRawElement));
}

static inline void rawShl(FrRawElement r, FrRawElement a, uint64_t b)
{
    if (b == 0)
    {
        Fr_rawCopy(r, a);
        return;
    }

    if (b >= 254)
    {
        Fr_rawZero(r);
        return;
    }

    Fr_rawShl(r, a, b);
}

static inline void rawShr(FrRawElement r, FrRawElement a, uint64_t b)
{
    if (b == 0)
    {
        Fr_rawCopy(r, a);
        return;
    }

    if (b >= 254)
    {
        Fr_rawZero(r);
        return;
    }

    Fr_rawShr(r,a, b);
}

static inline void Fr_setzero(PFrElement r)
{
    r->type = 0;
    r->shortVal = 0;
}

static inline void do_shlcl(PFrElement r, PFrElement a, uint64_t b)
{
    FrElement a_long;
    Fr_toLongNormal(&a_long, a);

    r->type = Fr_LONG;
    rawShl(r->longVal, a_long.longVal, b);
}

static inline void do_shlln(PFrElement r, PFrElement a, uint64_t b)
{
    r->type = Fr_LONG;
    rawShl(r->longVal, a->longVal, b);
}

static inline void do_shl(PFrElement r, PFrElement a, uint64_t b)
{
    if (a->type & Fr_LONG)
    {
        if (a->type == Fr_LONGMONTGOMERY)
        {
            FrElement a_long;
            Fr_toNormal(&a_long, a);

            do_shlln(r, &a_long, b);
        }
        else
        {
            do_shlln(r, a, b);
        }
    }
    else
    {
        int64_t a_shortVal = a->shortVal;

        if (a_shortVal == 0)
        {
            Fr_setzero(r);
        }
        else if (a_shortVal < 0)
        {
            do_shlcl(r, a, b);
        }
        else if(b >= 31)
        {
            do_shlcl(r, a, b);
        }
        else
        {
            a_shortVal <<= b;

            const uint64_t a_is_over_short = a_shortVal >> 31;

            if (a_is_over_short)
            {
                do_shlcl(r, a, b);
            }
            else
            {
                r->type = Fr_SHORT;
                r->shortVal = a_shortVal;
            }
        }
    }
}

static inline void do_shrln(PFrElement r, PFrElement a, uint64_t b)
{
    r->type = Fr_LONG;
    rawShr(r->longVal, a->longVal, b);
}

static inline void do_shrl(PFrElement r, PFrElement a, uint64_t b)
{
    if (a->type == Fr_LONGMONTGOMERY)
    {
        FrElement a_long;
        Fr_toNormal(&a_long, a);

        do_shrln(r, &a_long, b);
    }
    else
    {
        do_shrln(r, a, b);
    }
}

static inline void do_shr(PFrElement r, PFrElement a, uint64_t b)
{
    if (a->type & Fr_LONG)
    {
        do_shrl(r, a, b);
    }
    else
    {
        int64_t a_shortVal = a->shortVal;

        if (a_shortVal == 0)
        {
            Fr_setzero(r);
        }
        else if (a_shortVal < 0)
        {
            FrElement a_long;
            Fr_toLongNormal(&a_long, a);

            do_shrl(r, &a_long, b);
        }
        else if(b >= 31)
        {
            Fr_setzero(r);
        }
        else
        {
            a_shortVal >>= b;

            r->shortVal = a_shortVal;
            r->type = Fr_SHORT;
        }
    }
}

static inline void Fr_shr_big_shift(PFrElement r, PFrElement a, PFrElement b)
{
    static FrRawElement max_shift = { 254 };

    FrRawElement shift;

    Fr_rawSubRegular(shift, Fr_q.longVal, b->longVal);

    if (Fr_rawCmp(shift, max_shift) >= 0)
    {
        Fr_setzero(r);
    }
    else
    {
        do_shl(r, a, shift[0]);
    }
}

static inline void Fr_shr_long(PFrElement r, PFrElement a, PFrElement b)
{
    static FrRawElement max_shift = { 254 };

    if (Fr_rawCmp(b->longVal, max_shift) >= 0)
    {
        Fr_shr_big_shift(r, a, b);
    }
    else
    {
        do_shr(r, a, b->longVal[0]);
    }
}

void Fr_shr(PFrElement r, PFrElement a, PFrElement b)
{
    if (b->type & Fr_LONG)
    {
        if (b->type == Fr_LONGMONTGOMERY)
        {
            FrElement b_long;
            Fr_toNormal(&b_long, b);

            Fr_shr_long(r, a, &b_long);
        }
        else
        {
            Fr_shr_long(r, a, b);
        }
    }
    else
    {
        int64_t b_shortVal = b->shortVal;

        if (b_shortVal < 0)
        {
            b_shortVal = -b_shortVal;

            if (b_shortVal >= 254)
            {
                Fr_setzero(r);
            }
            else
            {
                do_shl(r, a, b_shortVal);
            }
        }
        else if (b_shortVal >= 254)
        {
            Fr_setzero(r);
        }
        else
        {
            do_shr(r, a, b_shortVal);
        }
    }
}

static inline void Fr_shl_big_shift(PFrElement r, PFrElement a, PFrElement b)
{
    static FrRawElement max_shift = { 254 };

    FrRawElement shift;

    Fr_rawSubRegular(shift, Fr_q.longVal, b->longVal);

    if (Fr_rawCmp(shift, max_shift) >= 0)
    {
        Fr_setzero(r);
    }
    else
    {
        do_shr(r, a, shift[0]);
    }
}

static inline void Fr_shl_long(PFrElement r, PFrElement a, PFrElement b)
{
    static FrRawElement max_shift = { 254 };

    if (Fr_rawCmp(b->longVal, max_shift) >= 0)
    {
        Fr_shl_big_shift(r, a, b);
    }
    else
    {
        do_shl(r, a, b->longVal[0]);
    }
}

void Fr_shl(PFrElement r, PFrElement a, PFrElement b)
{
    if (b->type & Fr_LONG)
    {
        if (b->type == Fr_LONGMONTGOMERY)
        {
            FrElement b_long;
            Fr_toNormal(&b_long, b);

            Fr_shl_long(r, a, &b_long);
        }
        else
        {
            Fr_shl_long(r, a, b);
        }
    }
    else
    {
        int64_t b_shortVal = b->shortVal;

        if (b_shortVal < 0)
        {
            b_shortVal = -b_shortVal;

            if (b_shortVal >= 254)
            {
                Fr_setzero(r);
            }
            else
            {
                do_shr(r, a, b_shortVal);
            }
        }
        else if (b_shortVal >= 254)
        {
            Fr_setzero(r);
        }
        else
        {
            do_shl(r, a, b_shortVal);
        }
    }
}

void Fr_square(PFrElement r, PFrElement a)
{
    if (a->type & Fr_LONG)
    {
        if (a->type == Fr_LONGMONTGOMERY)
        {
            r->type = Fr_LONGMONTGOMERY;
            Fr_rawMSquare(r->longVal, a->longVal);
        }
        else
        {
            r->type = Fr_LONGMONTGOMERY;
            Fr_rawMSquare(r->longVal, a->longVal);
            Fr_rawMMul(r->longVal, r->longVal, Fr_R3.longVal);
        }
    }
    else
    {
        int64_t result;

        int overflow = Fr_rawSMul(&result, a->shortVal, a->shortVal);

        if (overflow)
        {
            Fr_rawCopyS2L(r->longVal, result);
            r->type = Fr_LONG;
            r->shortVal = 0;
        }
        else
        {
            // done the same way as in intel asm implementation
            r->shortVal = (int32_t)result;
            r->type = Fr_SHORT;
            //

            Fr_rawCopyS2L(r->longVal, result);
            r->type = Fr_LONG;
            r->shortVal = 0;
        }
    }
}

static inline void or_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal >= 0 && b->shortVal >= 0)
    {
        r->shortVal = a->shortVal | b->shortVal;
        r->type = Fr_SHORT;
        return;
    }

    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toLongNormal(&a_n, a);
    Fr_toLongNormal(&b_n, b);

    Fr_rawOr(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void or_s1l2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&b_n, b);

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawOr(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void or_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawOr(r->longVal, a_n.longVal, b->longVal);
}

static inline void or_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawOr(r->longVal, a->longVal, b_n.longVal);
}

static inline void or_l1ms2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawOr(r->longVal, b_n.longVal, a_n.longVal);
}

static inline void or_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawOr(r->longVal, a->longVal, b->longVal);
}

static inline void or_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;
    Fr_toNormal(&b_n, b);

    Fr_rawOr(r->longVal, a->longVal, b_n.longVal);
}

static inline void or_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    Fr_toNormal(&a_n, a);

    Fr_rawOr(r->longVal, a_n.longVal, b->longVal);
}

static inline void or_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    Fr_rawOr(r->longVal, a_n.longVal, b_n.longVal);
}


void Fr_bor(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    or_l1ml2m(r, a, b);
                }
                else
                {
                    or_l1ml2n(r, a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                or_l1nl2m(r, a, b);
            }
            else
            {
                or_l1nl2n(r, a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            or_l1ms2(r, a, b);
        }
        else
        {
           or_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            or_s1l2m(r, a, b);
        }
        else
        {
            or_s1l2n(r, a, b);
        }
    }
    else
    {
         or_s1s2(r, a, b);
    }
}

static inline void xor_s1s2(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->shortVal >= 0 && b->shortVal >= 0)
    {
        r->shortVal = a->shortVal ^ b->shortVal;
        r->type = Fr_SHORT;
        return;
    }

    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toLongNormal(&a_n, a);
    Fr_toLongNormal(&b_n, b);

    Fr_rawXor(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void xor_s1l2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawXor(r->longVal, a_n.longVal, b->longVal);
}

static inline void xor_s1l2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&b_n, b);

    if (a->shortVal >= 0)
    {
        a_n = {0, 0, {(uint64_t)a->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&a_n, a);
    }

    Fr_rawXor(r->longVal, a_n.longVal, b_n.longVal);
}

static inline void xor_l1ns2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawXor(r->longVal, a->longVal, b_n.longVal);
}

static inline void xor_l1ms2(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);

    if (b->shortVal >= 0)
    {
        b_n = {0, 0, {(uint64_t)b->shortVal}};
    }
    else
    {
        Fr_toLongNormal(&b_n, b);
    }

    Fr_rawXor(r->longVal, b_n.longVal, a_n.longVal);
}

static inline void xor_l1nl2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;
    Fr_rawXor(r->longVal, a->longVal, b->longVal);
}

static inline void xor_l1nl2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement b_n;
    Fr_toNormal(&b_n, b);

    Fr_rawXor(r->longVal, a->longVal, b_n.longVal);
}

static inline void xor_l1ml2n(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    Fr_toNormal(&a_n, a);

    Fr_rawXor(r->longVal, a_n.longVal, b->longVal);
}

static inline void xor_l1ml2m(PFrElement r, PFrElement a, PFrElement b)
{
    r->type = Fr_LONG;

    FrElement a_n;
    FrElement b_n;

    Fr_toNormal(&a_n, a);
    Fr_toNormal(&b_n, b);

    Fr_rawXor(r->longVal, a_n.longVal, b_n.longVal);
}

void Fr_bxor(PFrElement r, PFrElement a, PFrElement b)
{
    if (a->type & Fr_LONG)
    {
        if (b->type & Fr_LONG)
        {
            if (a->type & Fr_MONTGOMERY)
            {
                if (b->type & Fr_MONTGOMERY)
                {
                    xor_l1ml2m(r, a, b);
                }
                else
                {
                    xor_l1ml2n(r, a, b);
                }
            }
            else if (b->type & Fr_MONTGOMERY)
            {
                xor_l1nl2m(r, a, b);
            }
            else
            {
                xor_l1nl2n(r, a, b);
            }
        }
        else if (a->type & Fr_MONTGOMERY)
        {
            xor_l1ms2(r, a, b);
        }
        else
        {
           xor_l1ns2(r, a, b);
        }
    }
    else if (b->type & Fr_LONG)
    {
        if (b->type & Fr_MONTGOMERY)
        {
            xor_s1l2m(r, a, b);
        }
        else
        {
            xor_s1l2n(r, a, b);
        }
    }
    else
    {
         xor_s1s2(r, a, b);
    }
}

void Fr_bnot(PFrElement r, PFrElement a)
{
    r->type = Fr_LONG;

    if (a->type == Fr_LONG)
    {
        if (a->type & Fr_MONTGOMERY)
        {
            FrElement a_n;
            Fr_toNormal(&a_n, a);

            Fr_rawNot(r->longVal, a_n.longVal);
        }
        else
        {
            Fr_rawNot(r->longVal, a->longVal);
        }
    }
    else
    {
        FrElement a_n;
        Fr_toLongNormal(&a_n, a);

        Fr_rawNot(r->longVal, a_n.longVal);
    }
}


static mpz_t mpz_q;
static mpz_t mpz_zero;
static mpz_t mpz_one;
static mpz_t mpz_mask;
static size_t nBits;
static bool initialized = false;


void Fr_toMpz(mpz_t r, PFrElement pE) {
    FrElement tmp;
    Fr_toNormal(&tmp, pE);
    if (!(tmp.type & Fr_LONG)) {
        mpz_set_si(r, tmp.shortVal);
        if (tmp.shortVal<0) {
            mpz_add(r, r, mpz_q);
        }
    } else {
        mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
}

void Fr_fromMpz(PFrElement pE, mpz_t v) {
    if (mpz_fits_sint_p(v)) {
        pE->type = Fr_SHORT;
        pE->shortVal = mpz_get_si(v);
    } else {
        pE->type = Fr_LONG;
        for (int i=0; i<Fr_N64; i++) pE->longVal[i] = 0;
        mpz_export((void *)(pE->longVal), NULL, -1, 8, -1, 0, v);
    }
}


bool Fr_init() {
    if (initialized) return false;
    initialized = true;
    mpz_init(mpz_q);
    mpz_import(mpz_q, Fr_N64, -1, 8, -1, 0, (const void *)Fr_q.longVal);
    mpz_init_set_ui(mpz_zero, 0);
    mpz_init_set_ui(mpz_one, 1);
    nBits = mpz_sizeinbase (mpz_q, 2);
    mpz_init(mpz_mask);
    mpz_mul_2exp(mpz_mask, mpz_one, nBits);
    mpz_sub(mpz_mask, mpz_mask, mpz_one);
    return true;
}

void Fr_str2element(PFrElement pE, char const *s, uint base) {
    mpz_t mr;
    mpz_init_set_str(mr, s, base);
    mpz_fdiv_r(mr, mr, mpz_q);
    Fr_fromMpz(pE, mr);
    mpz_clear(mr);
}

char *Fr_element2str(PFrElement pE) {
    FrElement tmp;
    mpz_t r;
    if (!(pE->type & Fr_LONG)) {
        if (pE->shortVal>=0) {
            char *r = new char[32];
            sprintf(r, "%d", pE->shortVal);
            return r;
        } else {
            mpz_init_set_si(r, pE->shortVal);
            mpz_add(r, r, mpz_q);
        }
    } else {
        Fr_toNormal(&tmp, pE);
        mpz_init(r);
        mpz_import(r, Fr_N64, -1, 8, -1, 0, (const void *)tmp.longVal);
    }
    char *res = mpz_get_str (0, 10, r);
    mpz_clear(r);
    return res;
}

void Fr_idiv(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    // char *s1 = mpz_get_str (0, 10, ma);
    // printf("s1 %s\n", s1);
    Fr_toMpz(mb, b);
    // char *s2 = mpz_get_str (0, 10, mb);
    // printf("s2 %s\n", s2);
    mpz_fdiv_q(mr, ma, mb);
    // char *sr = mpz_get_str (0, 10, mr);
    // printf("r %s\n", sr);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_mod(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    Fr_toMpz(mb, b);
    mpz_fdiv_r(mr, ma, mb);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_pow(PFrElement r, PFrElement a, PFrElement b) {
    mpz_t ma;
    mpz_t mb;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mb);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    Fr_toMpz(mb, b);
    mpz_powm(mr, ma, mb, mpz_q);
    Fr_fromMpz(r, mr);

    mpz_clear(ma);
    mpz_clear(mb);
    mpz_clear(mr);
}

void Fr_inv(PFrElement r, PFrElement a) {
    mpz_t ma;
    mpz_t mr;
    mpz_init(ma);
    mpz_init(mr);

    Fr_toMpz(ma, a);
    mpz_invert(mr, ma, mpz_q);
    Fr_fromMpz(r, mr);
    mpz_clear(ma);
    mpz_clear(mr);
}

void Fr_div(PFrElement r, PFrElement a, PFrElement b) {
    FrElement tmp;
    Fr_inv(&tmp, b);
    Fr_mul(r, a, &tmp);
}


static bool init = Fr_init();
