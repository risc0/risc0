
#pragma once

#ifdef __CUDA_ARCH__
#define inline __device__ __forceinline__
#ifdef __GNUC__
#define asm __asm__ __volatile__
#else
#define asm asm volatile
#endif

class __align__(16) bb31_4_t {
  bb31_t c[4];

  static const uint32_t M = 0x77ffffff;
  static const uint32_t BETA = 0x37ffffe9;  // (11<<32)%MOD
  static const uint32_t NBETA = 0x40000018; // MOD-BETA

public:
  static const uint32_t MOD = 0x78000001;

  inline bb31_t& operator[](size_t i) {
    return c[i];
  }
  inline const bb31_t& operator[](size_t i) const {
    return c[i];
  }
  inline size_t len() const {
    return 4;
  }

  inline bb31_4_t() {}
  inline bb31_4_t(bb31_t a) {
    c[0] = a;
    *c[1] = *c[2] = *c[3] = 0;
  }
  inline bb31_4_t(int a) {
    c[0] = bb31_t{a};
    *c[1] = *c[2] = *c[3] = 0;
  }
  inline bb31_4_t(uint32_t a[4]) {
    *c[0] = a[0];
    *c[1] = a[1];
    *c[2] = a[2];
    *c[3] = a[3];
  }

  // Polynomial multiplication modulo x^4 - BETA
  friend __device__ __noinline__ bb31_4_t operator*(bb31_4_t a, bb31_4_t b) {
    uint32_t ret[4];

    // ret[0] = a[0]*b[0] + NBETA*(a[1]*b[3] + a[2]*b[2] + a[3]*b[1]);
    asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
        "mul.lo.u32    %lo, %4, %6;      mul.hi.u32  %hi, %4, %6;\n\t"
        "mad.lo.cc.u32 %lo, %3, %7, %lo; madc.hi.u32 %hi, %3, %7, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %2, %8, %lo; madc.hi.u32 %hi, %2, %8, %hi;\n\t"
        "setp.ge.u32 %p, %hi, %9;\n\t"
        "@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
        //"setp.ge.u32 %p, %hi, %9;\n\t"
        //"@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
        "mad.lo.cc.u32 %lo, %1, %5, %lo; madc.hi.u32 %hi, %1, %5, %hi;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
        "setp.ge.u32 %p, %0, %9;\n\t"
        "@%p sub.u32 %0, %0, %9;\n\t"
        "}"
        : "=r"(ret[0])
        : "r"(*a[0]),
          "r"(*a[1]),
          "r"(*a[2]),
          "r"(*a[3]),
          "r"(*b[0]),
          "r"(*b[1]),
          "r"(*b[2]),
          "r"(*b[3]),
          "r"(MOD),
          "r"(M),
          "r"(NBETA));

    // ret[1] = a[0]*b[1] + a[1]*b[0] + NBETA*(a[2]*b[3] + a[3]*b[2]);
    asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
        "mul.lo.u32    %lo, %4, %7;      mul.hi.u32  %hi, %4, %7;\n\t"
        "mad.lo.cc.u32 %lo, %3, %8, %lo; madc.hi.u32 %hi, %3, %8, %hi;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
        //"setp.ge.u32 %p, %hi, %9;\n\t"
        //"@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
        "mad.lo.cc.u32 %lo, %2, %5, %lo; madc.hi.u32 %hi, %2, %5, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %1, %6, %lo; madc.hi.u32 %hi, %1, %6, %hi;\n\t"
        "setp.ge.u32 %p, %hi, %9;\n\t"
        "@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
        "setp.ge.u32 %p, %0, %9;\n\t"
        "@%p sub.u32 %0, %0, %9;\n\t"
        "}"
        : "=r"(ret[1])
        : "r"(*a[0]),
          "r"(*a[1]),
          "r"(*a[2]),
          "r"(*a[3]),
          "r"(*b[0]),
          "r"(*b[1]),
          "r"(*b[2]),
          "r"(*b[3]),
          "r"(MOD),
          "r"(M),
          "r"(NBETA));

    // ret[2] = a[0]*b[2] + a[1]*b[1] + a[2]*b[0] + NBETA*(a[3]*b[3]);
    asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
        "mul.lo.u32    %lo, %4, %8;      mul.hi.u32  %hi, %4, %8;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %hi, %m, %9, %hi;\n\t"
        //"setp.ge.u32 %p, %hi, %9;\n\t"
        //"@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %lo, %hi, %11;    mul.hi.u32  %hi, %hi, %11;\n\t"
        "mad.lo.cc.u32 %lo, %3, %5, %lo; madc.hi.u32 %hi, %3, %5, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %2, %6, %lo; madc.hi.u32 %hi, %2, %6, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %1, %7, %lo; madc.hi.u32 %hi, %1, %7, %hi;\n\t"
        "setp.ge.u32 %p, %hi, %9;\n\t"
        "@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
        "setp.ge.u32 %p, %0, %9;\n\t"
        "@%p sub.u32 %0, %0, %9;\n\t"
        "}"
        : "=r"(ret[2])
        : "r"(*a[0]),
          "r"(*a[1]),
          "r"(*a[2]),
          "r"(*a[3]),
          "r"(*b[0]),
          "r"(*b[1]),
          "r"(*b[2]),
          "r"(*b[3]),
          "r"(MOD),
          "r"(M),
          "r"(NBETA));

    // ret[3] = a[0]*b[3] + a[1]*b[2] + a[2]*b[1] + a[3]*b[0];
    asm("{ .reg.b32 %lo, %hi, %m; .reg.pred %p;\n\t"
        "mul.lo.u32    %lo, %4, %5;      mul.hi.u32  %hi, %4, %5;\n\t"
        "mad.lo.cc.u32 %lo, %3, %6, %lo; madc.hi.u32 %hi, %3, %6, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %2, %7, %lo; madc.hi.u32 %hi, %2, %7, %hi;\n\t"
        "mad.lo.cc.u32 %lo, %1, %8, %lo; madc.hi.u32 %hi, %1, %8, %hi;\n\t"
        "setp.ge.u32 %p, %hi, %9;\n\t"
        "@%p sub.u32 %hi, %hi, %9;\n\t"

        "mul.lo.u32    %m, %lo, %10;\n\t"
        "mad.lo.cc.u32 %lo, %m, %9, %lo; madc.hi.u32 %0, %m, %9, %hi;\n\t"
        "setp.ge.u32 %p, %0, %9;\n\t"
        "@%p sub.u32 %0, %0, %9;\n\t"
        "}"
        : "=r"(ret[3])
        : "r"(*a[0]),
          "r"(*a[1]),
          "r"(*a[2]),
          "r"(*a[3]),
          "r"(*b[0]),
          "r"(*b[1]),
          "r"(*b[2]),
          "r"(*b[3]),
          "r"(MOD),
          "r"(M),
          "r"(NBETA));

    return bb31_4_t{ret};
  }
  inline bb31_4_t& operator*=(const bb31_4_t& b) {
    return *this = *this * b;
  }

  friend __device__ __noinline__ bb31_4_t operator*(bb31_4_t a, bb31_t b) {
    bb31_4_t ret;

    for (size_t i = 0; i < 4; i++)
      ret[i] = a[i] * b;

    return ret;
  }
  friend inline bb31_4_t operator*(bb31_t b, const bb31_4_t& a) {
    return a * b;
  }
  inline bb31_4_t& operator*=(bb31_t b) {
    return *this = *this * b;
  }

  friend inline bb31_4_t operator+(const bb31_4_t& a, const bb31_4_t& b) {
    bb31_4_t ret;

    for (size_t i = 0; i < 4; i++)
      ret[i] = a[i] + b[i];

    return ret;
  }
  inline bb31_4_t& operator+=(const bb31_4_t& b) {
    return *this = *this + b;
  }

  friend inline bb31_4_t operator+(const bb31_4_t& a, bb31_t b) {
    bb31_4_t ret;

    ret[0] = a[0] + b;
    ret[1] = a[1];
    ret[2] = a[2];
    ret[3] = a[3];

    return ret;
  }
  friend inline bb31_4_t operator+(bb31_t b, const bb31_4_t& a) {
    return a + b;
  }
  inline bb31_4_t& operator+=(bb31_t b) {
    c[0] += b;
    return *this;
  }

  friend inline bb31_4_t operator-(const bb31_4_t& a, const bb31_4_t& b) {
    bb31_4_t ret;

    for (size_t i = 0; i < 4; i++)
      ret[i] = a[i] - b[i];

    return ret;
  }
  inline bb31_4_t& operator-=(const bb31_4_t& b) {
    return *this = *this - b;
  }

  friend inline bb31_4_t operator-(const bb31_4_t& a, bb31_t b) {
    bb31_4_t ret;

    ret[0] = a[0] - b;
    ret[1] = a[1];
    ret[2] = a[2];
    ret[3] = a[3];

    return ret;
  }
  friend inline bb31_4_t operator-(bb31_t b, const bb31_4_t& a) {
    bb31_4_t ret;

    ret[0] = b - a[0];
    ret[1] = -a[1];
    ret[2] = -a[2];
    ret[3] = -a[3];

    return ret;
  }
  inline bb31_4_t& operator-=(bb31_t b) {
    c[0] -= b;
    return *this;
  }

  inline bb31_4_t reciprocal() const {
    const bb31_t beta{BETA};

    // don't bother with breaking this down, 1/x dominates.
    bb31_t b0 = c[0] * c[0] + beta * (c[1] * bb31_t{*c[3] << 1} - c[2] * c[2]);
    bb31_t b2 = c[0] * bb31_t{*c[2] << 1} - c[1] * c[1] + beta * (c[3] * c[3]);

    bb31_t inv = 1 / (b0 * b0 + beta * b2 * b2);

    b0 *= inv;
    b2 *= inv;

    bb31_4_t ret;
    bb31_t beta_b2 = beta * b2;
    ret[0] = c[2] * beta_b2 + c[0] * b0;
    ret[1] = -c[3] * beta_b2 - c[1] * b0;
    ret[2] = c[2] * b0 - c[0] * b2;
    ret[3] = c[1] * b2 - c[3] * b0;

    return ret;
  }
  friend inline bb31_4_t operator/(int one, const bb31_4_t& a) {
    if (one != 1)
      asm("trap;");
    return a.reciprocal();
  }
  friend inline bb31_4_t operator/(const bb31_4_t& a, const bb31_4_t& b) {
    return a * b.reciprocal();
  }
  friend inline bb31_4_t operator/(bb31_t a, const bb31_4_t& b) {
    return b.reciprocal() * a;
  }
  friend inline bb31_4_t operator/(const bb31_4_t& a, bb31_t b) {
    return a * b.reciprocal();
  }
  inline bb31_4_t& operator/=(const bb31_4_t& a) {
    return *this *= a.reciprocal();
  }
  inline bb31_4_t& operator/=(bb31_t a) {
    return *this *= a.reciprocal();
  }
};

#undef inline
#undef asm
#else
class bb31_4_t {
  bb31_t c[4];

public:
  inline bb31_t& operator[](size_t i) { return c[i]; }
  inline const bb31_t& operator[](size_t i) const { return c[i]; }

  inline bb31_4_t() {}
  inline bb31_4_t(bb31_t a) {
    c[0] = a;
    c[1] = c[2] = c[3] = 0;
  }
  inline bb31_4_t(int a) {
    c[0] = bb31_t{a};
    c[1] = c[2] = c[3] = 0;
  }
  inline bb31_4_t(uint32_t a[4]) {
    c[0] = a[0];
    c[1] = a[1];
    c[2] = a[2];
    c[3] = a[3];
  }

  friend bb31_4_t operator*(bb31_4_t a, bb31_4_t b) { return a; }
  friend bb31_4_t operator*(bb31_4_t a, bb31_t b) { return a; }
  friend bb31_4_t operator*(bb31_t a, bb31_4_t b) { return b; }
  friend bb31_4_t operator+(bb31_4_t a, bb31_4_t b) { return a; }
};
#endif

typedef bb31_4_t Fp4;
typedef bb31_4_t FpExt;
