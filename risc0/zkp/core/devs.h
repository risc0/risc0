#ifndef RISCV
#define CPU
#endif // #ifndef RISCV

#ifdef RISCV
#include <cstddef>
#include <cstdint>
#define DEVSPEC  /**/
#define DEVADDR  /**/
#define DEVLOCAL /**/
#define CONSTSCALAR constexpr
#endif // #ifdef RISCV

#ifdef CPU
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#define DEVSPEC  /**/
#define DEVADDR  /**/
#define DEVLOCAL /**/
#define CONSTSCALAR constexpr
#endif // #ifdef CPU
