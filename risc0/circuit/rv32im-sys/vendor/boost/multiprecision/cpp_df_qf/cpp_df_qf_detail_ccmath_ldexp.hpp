///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2025.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_LDEXP_2023_01_07_HPP
#define BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_LDEXP_2023_01_07_HPP

#include <cmath>
#include <type_traits>

namespace boost { namespace multiprecision { namespace backends { namespace cpp_df_qf_detail { namespace ccmath {

namespace detail {

template <class T>
constexpr auto ldexp_impl(T arg, int expval) -> T
{
   // Default to the regular ldexp function.
   using std::ldexp;

   return ldexp(arg, expval);
}

} // Namespace detail

template <typename Real>
constexpr auto ldexp(Real arg, int expval) -> Real
{
   return detail::ldexp_impl(arg, expval);
}

namespace unsafe {

template <typename Real>
constexpr auto ldexp(Real arg, int exp) noexcept -> Real
{
   while(exp > 0)
   {
      arg *= 2;
      --exp;
   }
   while(exp < 0)
   {
      arg /= 2;
      ++exp;
   }

   return arg;
}

} // namespace unsafe

} } } } } // namespace boost::multiprecision::backends::cpp_df_qf_detail::ccmath

#endif // BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_LDEXP_2023_01_07_HPP
