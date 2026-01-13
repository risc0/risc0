///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2023 - 2025.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FREXP_2023_01_07_HPP
#define BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FREXP_2023_01_07_HPP

#include <cmath>
#include <type_traits>

namespace boost { namespace multiprecision { namespace backends { namespace cpp_df_qf_detail { namespace ccmath {

namespace detail
{

template <class T>
constexpr auto frexp_impl(T arg, int* expptr) -> T
{
   // Default to the regular frexp function.
   using std::frexp;

   return frexp(arg, expptr);
}

} // namespace detail

template <typename Real>
constexpr auto frexp(Real arg, int* expptr) -> Real
{
   return detail::frexp_impl(arg, expptr);
}

} } } } } // namespace boost::multiprecision::backends::cpp_df_qf_detail::ccmath

#endif // BOOST_MP_CPP_DF_QF_DETAIL_CCMATH_FREXP_2023_01_07_HPP
