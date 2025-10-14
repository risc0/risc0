// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_FF_BLS12_381_FP2_HPP__
#define __SPPARK_FF_BLS12_381_FP2_HPP__

#include "bls12-381.hpp"

#ifdef __CUDA_ARCH__

# define inline __device__ __forceinline__
# ifdef __GNUC__
#  define asm __asm__ __volatile__
# else
#  define asm asm volatile
# endif

# ifndef WARP_SZ
#  define WARP_SZ 32
# endif

namespace bls12_381 {

class fp2_t : public fp_mont {
private:
    static inline uint32_t laneid()
    {   return threadIdx.x % WARP_SZ;   }

public:
    static const uint32_t degree = 2;

    class mem_t { friend fp2_t;
        fp_mont x[2];

    public:
        inline operator fp2_t() const           { return x[threadIdx.x&1]; }
        inline void zero()                      { x[threadIdx.x&1].zero(); }
        inline void to()                        { x[threadIdx.x&1].to();   }
        inline void from()                      { x[threadIdx.x&1].from(); }
        inline mem_t& operator=(const fp2_t& a)
        {   x[threadIdx.x&1] = a; return *this;   }
    };

    inline fp2_t()                              {}
    inline fp2_t(const fp_mont& a) : fp_mont(a) {}
    inline fp2_t(const mem_t* p)                { *this = p->x[threadIdx.x&1]; }
    inline void store(mem_t* p) const           { p->x[threadIdx.x&1] = *this; }

    friend inline fp2_t operator*(const fp2_t& a, const fp2_t& b)
    {
        auto id = laneid();
        auto mask = __activemask();
        auto t0 = b.shfl(id&~1, mask);
        auto t1 = a.shfl(id^1, mask);
        auto t2 = b.shfl(id|1, mask);
        t1.cneg((id&1) == 0);

        return dot_product(a, t0, t1, t2);  // a*t0 + t1*t2;
    }
    inline fp2_t& operator*=(const fp2_t& a)
    {   return *this = *this * a;   }

    inline fp2_t& sqr()
    {
        auto id = laneid();
        fp_mont t0 = shfl(id^1, __activemask());
        fp_mont t1 = *this;

        if ((id&1) == 0) {
            t1 = (fp_mont)*this + t0;
            t0 = (fp_mont)*this - t0;
        }
        t0 *= t1;
        t1 = t0 << 1;

        return *this = fp_mont::csel(t1, t0, id&1);
    }
    inline fp2_t& operator^=(int p)
    {   if (p != 2) asm("trap;"); return sqr();     }
    friend inline fp2_t operator^(fp2_t a, int p)
    {   if (p != 2) asm("trap;"); return a.sqr();   }

    friend inline fp2_t operator+(const fp2_t& a, const fp2_t& b)
    {   return (fp_mont)a + (fp_mont)b;   }
    inline fp2_t& operator+=(const fp2_t& b)
    {   return *this = *this + b;   }

    friend inline fp2_t operator-(const fp2_t& a, const fp2_t& b)
    {   return (fp_mont)a - (fp_mont)b;   }
    inline fp2_t& operator-=(const fp2_t& b)
    {   return *this = *this - b;   }

    friend inline fp2_t operator<<(const fp2_t& a, unsigned l)
    {   return (fp_mont)a << l;   }
    inline fp2_t& operator<<=(unsigned l)
    {   return *this = *this << l;   }

    inline fp2_t& cneg(bool flag)
    {   fp_mont::cneg(flag); return *this;  }
    friend inline fp2_t cneg(fp2_t a, bool flag)
    {   return a.cneg(flag);   }

    friend inline fp2_t czero(const fp2_t& a, int set_z)
    {   return czero((fp_mont)a, set_z);   }

    inline bool is_zero() const
    {
        auto ret = __ballot_sync(__activemask(), fp_mont::is_zero());
        return ((ret >> (laneid()&~1)) & 3) == 3;
    }

    inline bool is_zero(const fp2_t& a) const
    {
        auto ret = __ballot_sync(__activemask(), fp_mont::is_zero(a));
        return ((ret >> (laneid()&~1)) & 3) == 3;
    }

    static inline fp2_t one(int or_zero = 0)
    {   return fp_mont::one((laneid()&1) | or_zero);   }

    inline bool is_one() const
    {
        auto id = laneid();
        auto even = ~(0 - (id&1));
        uint32_t is_zero = ((fp_mont)*this)[0] ^ (fp_mont::one()[0] & even);

        for (size_t i = 1; i < n; i++)
            is_zero |= ((fp_mont)*this)[i] ^ (fp_mont::one()[i] & even);

        is_zero = __ballot_sync(__activemask(), is_zero == 0);
        return ((is_zero >> (id&~1)) & 3) == 3;
    }

    inline fp2_t reciprocal() const
    {
        auto a = (fp_mont)*this^2;
        auto b = shfl_xor(a);
        a += b;
        a = ct_inverse_mod_x(a);    // 1/(x[0]^2 + x[1]^2)
        a *= (fp_mont)*this;
        a.cneg(threadIdx.x&1);
        return a;
    }
    friend inline fp2_t operator/(int one, const fp2_t& a)
    {   if (one != 1) asm("trap;"); return a.reciprocal();   }
    friend inline fp2_t operator/(const fp2_t& a, const fp2_t& b)
    {   return a * b.reciprocal();   }
    inline fp2_t& operator/=(const fp2_t& a)
    {   return *this *= a.reciprocal();   }
};

} // namespace bls12_381

# undef inline
# undef asm

#else

namespace bls12_381 {

class fp2_t {
    vec384x val;

    static const size_t n = sizeof(vec384)/sizeof(limb_t);
    static const limb_t p0 = 0x89f3fffcfffcfffd;

public:
    static const unsigned int degree = 2;
    using mem_t = fp2_t;

    inline fp2_t() {}
    inline fp2_t(const vec384x p)
    {   vec_copy(val, p, sizeof(val));   }
    inline fp2_t(uint64_t re, uint64_t im = 0)
    {
        vec_zero(val, sizeof(val));
        val[0][0] = re;
        val[1][0] = im;
        to();
    }
    inline fp2_t(int re, int im = 0) : fp2_t((uint64_t)re, (uint64_t)im) {}

    static inline fp2_t one(bool or_zero = false)
    {
        fp2_t ret;
        limb_t mask = ~((limb_t)0 - or_zero);
        for (size_t i = 0; i < n; i++) {
            ret.val[0][i] = BLS12_381_ONE[i] & mask;
            ret.val[1][i] = 0;
        }
        return ret;
    }

    inline fp2_t& to()
    {
        mul_mont_384(val[0], BLS12_381_RR, val[0], BLS12_381_P, p0);
        mul_mont_384(val[1], BLS12_381_RR, val[1], BLS12_381_P, p0);
        return *this;
    }
    inline fp2_t& from()
    {
        from_mont_384(val[0], val[0], BLS12_381_P, p0);
        from_mont_384(val[1], val[1], BLS12_381_P, p0);
        return *this;
    }

    inline void store(limb_t *p) const
    {   vec_copy(p, val, sizeof(val));   }

    inline fp2_t& operator+=(const fp2_t& b)
    {   add_mod_384x(val, val, b.val, BLS12_381_P); return *this;   }
    friend inline fp2_t operator+(const fp2_t& a, const fp2_t& b)
    {
        fp2_t ret;
        add_mod_384x(ret.val, a.val, b.val, BLS12_381_P);
        return ret;
    }

    inline fp2_t& operator<<=(unsigned l)
    {
        lshift_mod_384(val[0], val[0], l, BLS12_381_P);
        lshift_mod_384(val[1], val[1], l, BLS12_381_P);
        return *this;
    }
    friend inline fp2_t operator<<(const fp2_t& a, unsigned l)
    {
        fp2_t ret;
        lshift_mod_384(ret.val[0], a.val[0], l, BLS12_381_P);
        lshift_mod_384(ret.val[1], a.val[1], l, BLS12_381_P);
        return ret;
    }

    inline fp2_t& operator>>=(unsigned r)
    {
        rshift_mod_384(val[0], val[0], r, BLS12_381_P);
        rshift_mod_384(val[1], val[1], r, BLS12_381_P);
        return *this;
    }
    friend inline fp2_t operator>>(const fp2_t& a, unsigned r)
    {
        fp2_t ret;
        rshift_mod_384(ret.val[0], a.val[0], r, BLS12_381_P);
        rshift_mod_384(ret.val[1], a.val[1], r, BLS12_381_P);
        return ret;
    }

    inline fp2_t& operator-=(const fp2_t& b)
    {   sub_mod_384x(val, val, b.val, BLS12_381_P); return *this;   }
    friend inline fp2_t operator-(const fp2_t& a, const fp2_t& b)
    {
        fp2_t ret;
        sub_mod_384x(ret.val, a.val, b.val, BLS12_381_P);
        return ret;
    }

    inline fp2_t& cneg(bool flag)
    {
        cneg_mod_384(val[0], val[0], flag, BLS12_381_P);
        cneg_mod_384(val[1], val[1], flag, BLS12_381_P);
        return *this;
    }
    friend inline fp2_t cneg(const fp2_t& a, bool flag)
    {
        fp2_t ret;
        cneg_mod_384(ret.val[0], a.val[0], flag, BLS12_381_P);
        cneg_mod_384(ret.val[1], a.val[1], flag, BLS12_381_P);
        return ret;
    }
    friend inline fp2_t operator-(const fp2_t& a)
    {
        fp2_t ret;
        cneg_mod_384(ret.val[0], a.val[0], true, BLS12_381_P);
        cneg_mod_384(ret.val[1], a.val[1], true, BLS12_381_P);
        return ret;
    }

    inline fp2_t& operator*=(const fp2_t& a)
    {
        if (this == &a) sqr_mont_384x(val, val, BLS12_381_P, p0);
        else            mul_mont_384x(val, val, a.val, BLS12_381_P, p0);
        return *this;
    }
    friend inline fp2_t operator*(const fp2_t& a, const fp2_t& b)
    {
        fp2_t ret;
        if (&a == &b)   sqr_mont_384x(ret.val, a.val, BLS12_381_P, p0);
        else            mul_mont_384x(ret.val, a.val, b.val, BLS12_381_P, p0);
        return ret;
    }

    // simplified exponentiation, but mind the ^ operator's precedence!
    friend inline fp2_t operator^(const fp2_t& a, unsigned p)
    {
        if (p < 2) {
            abort();
        } else if (p == 2) {
            fp2_t ret;
            sqr_mont_384x(ret.val, a.val, BLS12_381_P, p0);
            return ret;
        } else {
            fp2_t ret = a, sqr = a;
            if ((p&1) == 0) {
                do {
                    sqr_mont_384x(sqr.val, sqr.val, BLS12_381_P, p0);
                    p >>= 1;
                } while ((p&1) == 0);
                ret = sqr;
            }
            for (p >>= 1; p; p >>= 1) {
                sqr_mont_384x(sqr.val, sqr.val, BLS12_381_P, p0);
                if (p&1)
                    mul_mont_384x(ret.val, ret.val, sqr.val, BLS12_381_P, p0);
            }
            return ret;
        }
    }
    inline fp2_t& operator^=(unsigned p)
    {
        if (p < 2) {
            abort();
        } else if (p == 2) {
            sqr_mont_384x(val, val, BLS12_381_P, p0);
            return *this;
        }
        return *this = *this^p;
    }
    inline fp2_t operator()(unsigned p)
    {   return *this^p;   }
    friend inline fp2_t sqr(const fp2_t& a)
    {   return a^2;   }

    inline bool is_zero() const
    {   return vec_is_zero(val, sizeof(val));   }

    inline bool is_one() const
    {   return vec_is_equal(val[0], BLS12_381_ONE, sizeof(val[0]))
            && vec_is_zero(val[1], sizeof(val[1]));
    }

    inline void zero()
    {   vec_zero(val, sizeof(val));   }

    friend inline fp2_t czero(const fp2_t& a, int set_z)
    {   fp2_t ret;
        const vec384x zero = {{0}};
        vec_select(ret.val, zero, a.val, sizeof(ret), set_z);
        return ret;
    }

    fp2_t reciprocal() const
    {
        union { fp2_t fp2; fp_t fp[2]; } ret = { *this };
        fp_t t0 = ret.fp[0]^2;
        fp_t t1 = ret.fp[1]^2;
        t0 += t1;
        t1 = 1/t0;
        ret.fp[0] *= t1;
        ret.fp[1] *= t1;
        ret.fp[1].cneg(true);
        return ret.fp2;
    }
    friend inline fp2_t operator/(unsigned one, const fp2_t& a)
    {
        if (one == 1)
            return a.reciprocal();
        abort();
    }
    friend inline fp2_t operator/(const fp2_t& a, const fp2_t& b)
    {   return a * b.reciprocal();   }
    inline fp2_t& operator/=(const fp2_t& a)
    {   return *this *= a.reciprocal();   }

    friend inline bool operator==(const fp2_t& a, const fp2_t& b)
    {   return vec_is_equal(a.val, b.val, sizeof(vec384x));   }
    friend inline bool operator!=(const fp2_t& a, const fp2_t& b)
    {   return !vec_is_equal(a.val, b.val, sizeof(vec384x));   }

    template<class OStream, typename Traits = typename OStream::traits_type>
    friend OStream& operator<<(OStream& os, const fp2_t& obj)
    {
        unsigned char be[sizeof(obj)];
        char buf[10+2*sizeof(obj)+2], *str=buf;

        be_bytes_from_limbs(be, fp2_t{obj}.from().val[0], sizeof(obj));

        *str++ = 'r', *str++ = ':', *str++ = ' ', *str++ = '0', *str++ = 'x';
        for (size_t i = sizeof(obj)/2; i < sizeof(obj); i++)
            *str++ = hex_from_nibble(be[i]>>4), *str++ = hex_from_nibble(be[i]);
        *str++ = ' ';

        *str++ = 'i', *str++ = ':', *str++ = ' ', *str++ = '0', *str++ = 'x';
        for (size_t i = 0; i < sizeof(obj)/2; i++)
            *str++ = hex_from_nibble(be[i]>>4), *str++ = hex_from_nibble(be[i]);
        *str = '\0';

        return os << buf;
    }
};

} // namespace bls12_381

#endif
#endif
