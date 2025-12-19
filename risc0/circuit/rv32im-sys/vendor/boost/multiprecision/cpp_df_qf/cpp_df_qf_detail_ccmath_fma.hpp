///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024 - 2025.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FMA_2024_12_17_HPP
#define BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FMA_2024_12_17_HPP

#include <cmath>
#include <type_traits>

namespace boost { namespace multiprecision { namespace backends { namespace cpp_df_qf_detail { namespace ccmath {

namespace unsafe {

namespace detail {

template <class T>
constexpr auto fma_impl(T x, T y, T z) noexcept -> T
{
   // Default to the written-out operations ...
   // ... and hope the compiler chooses FMA if available).

   return (x * y) + z;
}

#if defined(__GNUC__) && !defined(__clang__) && !defined(__INTEL_COMPILER) && !defined(__INTEL_LLVM_COMPILER)
template <>
constexpr auto fma_impl<float>(float x, float y, float z) noexcept -> float
{
  return __builtin_fmaf(x, y, z);
}

template <>
constexpr auto fma_impl<double>(double x, double y, double z) noexcept -> double
{
  return __builtin_fma(x, y, z);
}

template <>
constexpr auto fma_impl<long double>(long double x, long double y, long double z) noexcept -> long double
{
  return __builtin_fmal(x, y, z);
}
#endif

} // namespace detail

template <typename Real>
constexpr auto fma(Real x, Real y, Real z) noexcept -> Real
{
   return detail::fma_impl(x, y, z);
}

} // namespace unsafe

} } } } } // namespace boost::multiprecision::backends::cpp_df_qf_detail::ccmath

#endif // BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FMA_2024_12_17_HPP
