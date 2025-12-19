///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2025.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_SQRT_2023_01_07_HPP
#define BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_SQRT_2023_01_07_HPP

#include <cmath>
#include <type_traits>

namespace boost { namespace multiprecision { namespace backends { namespace cpp_df_qf_detail { namespace ccmath {

namespace detail {

template <class T>
constexpr auto sqrt_impl(T x) -> T
{
   // Default to the regular sqrt function.
   using std::sqrt;

   return sqrt(x);
}

} // namespace detail

template <typename Real>
constexpr auto sqrt(Real x) -> Real
{
   return cpp_df_qf_detail::ccmath::detail::sqrt_impl<Real>(x);
}

namespace unsafe {

namespace detail {

template <typename Real>
constexpr auto sqrt_impl_2(Real x, Real s, Real s2) noexcept -> Real
{
   return !(s < s2) ? s2 : sqrt_impl_2(x, (x / s + s) / 2, s);
}

template <typename Real>
constexpr auto sqrt_impl_1(Real x, Real s) noexcept -> Real
{
   return sqrt_impl_2(x, (x / s + s) / 2, s);
}

template <typename Real>
constexpr auto sqrt_impl(Real x) noexcept -> Real
{
   return sqrt_impl_1(x, x > 1 ? x : Real(1));
}

} // namespace detail

template <typename Real>
constexpr auto sqrt(Real x) noexcept -> Real
{
   return detail::sqrt_impl<Real>(x);
}

} // namespace unsafe

} } } } } // namespace boost::multiprecision::backends::cpp_df_qf_detail::ccmath

#endif // BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_SQRT_2023_01_07_HPP
