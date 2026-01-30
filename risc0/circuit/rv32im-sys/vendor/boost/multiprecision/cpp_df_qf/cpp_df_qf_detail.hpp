///////////////////////////////////////////////////////////////////////////////
//  Copyright 2021 Fahad Syed.
//  Copyright 2021 - 2025 Christopher Kormanyos.
//  Copyright 2021 Janek Kozicki.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_CPP_DF_QF_DETAIL_2023_01_02_HPP
#define BOOST_MP_CPP_DF_QF_DETAIL_2023_01_02_HPP

#include <boost/multiprecision/detail/standalone_config.hpp>

#if defined(BOOST_HAS_FLOAT128)
#if defined(__has_include)
#if __has_include(<quadmath.h>)

#include <quadmath.h>

#if !defined(BOOST_MP_CPP_DOUBLE_FP_HAS_FLOAT128)
#define BOOST_MP_CPP_DOUBLE_FP_HAS_FLOAT128
#endif

#endif // __has_include(<quadmath.h>)
#endif // defined(__has_include)
#endif // defined(BOOST_HAS_FLOAT128)

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/detail/float128_functions.hpp>
#include <boost/multiprecision/cpp_df_qf/cpp_df_qf_detail_ccmath.hpp>

namespace boost { namespace multiprecision { namespace backends { namespace cpp_df_qf_detail {

template <class FloatingPointTypeA, class FloatingPointTypeB>
struct pair
{
  static_assert(std::is_same<FloatingPointTypeA, FloatingPointTypeB>::value, "Error: floating point types A and B must be identical");

  using float_type = FloatingPointTypeA;

  float_type first;
  float_type second;

  constexpr pair() : first { }, second { } { };
  constexpr pair(float_type a, float_type b) : first { a }, second { b } { }
  constexpr pair(const pair& other) : first { other.first }, second { other.second } { }
  constexpr pair(pair&& other) noexcept : first { other.first }, second { other.second } { }

  constexpr auto operator=(const pair& other) -> pair&
  {
     if (this != &other)
     {
        first  = other.first;
        second = other.second;
     }

     return *this;
   }

  constexpr auto operator=(pair&& other) noexcept -> pair&
  {
     first  = other.first;
     second = other.second;

     return *this;
   }
};

template <class FloatingPointType>
struct is_floating_point
{
   static constexpr auto value =    ::std::is_same<FloatingPointType, float>::value
                                 || ::std::is_same<FloatingPointType, double>::value
                                 || ::std::is_same<FloatingPointType, long double>::value
#if defined(BOOST_MP_CPP_DOUBLE_FP_HAS_FLOAT128)
                                 || ::std::is_same<FloatingPointType, ::boost::float128_type>::value
#endif
                                 ;
};

template <typename FloatType>
struct split_maker
{
private:
   using float_type = FloatType;

public:
   static constexpr int
      n_shl
      {
         static_cast<int>((ccmath::numeric_limits<float_type>::digits + 1) / 2)
      };

      static_assert(n_shl < std::numeric_limits<std::uint64_t>::digits,
                    "Error: Left-shift amount for split does not fin in std::uint64_t");

   static constexpr float_type
      value
      {
         static_cast<float_type>
         (
            std::uint64_t
            {
                 UINT64_C(1)
               + std::uint64_t { UINT64_C(1) << static_cast<unsigned>(n_shl) }
            }
         )
      };
};

template <typename FloatingPointType>
struct exact_arithmetic
{
   // The exact_arithmetic<> struct implements a few extended
   // precision algorithms that are used in cpp_double_fp_backend.

   static_assert(is_floating_point<FloatingPointType>::value, "Error: exact_arithmetic<> invoked with unknown floating-point type");

   using float_type  = FloatingPointType;
   using float_pair  = pair<float_type, float_type>;

   static constexpr auto two_sum(const float_type a, const float_type b) -> float_pair
   {
     const float_type hi { a + b };
     const float_type a1 { hi - b };

     return { hi, float_type { (a - a1) + (b - float_type { hi - a1 }) } };
   }

   static constexpr auto two_diff(const float_type a, const float_type b) -> float_pair
   {
     const float_type hi { a - b };
     const float_type a1 { hi + b };

     return { hi, float_type { (a - a1) - (b + float_type { hi - a1 }) } };
   }

   static constexpr auto two_hilo_sum(const float_type a, const float_type b) -> float_pair
   {
      const float_type hi { a + b };

      return { hi, float_type { b - (hi - a) } };
   }

   static constexpr auto normalize(float_type a, float_type b) -> float_pair
   {
      const float_type u { a + b };

      return
      {
         u,
         float_type { a - u } + b
      };
   }
};

template<typename ArithmeticType>
struct pow2_maker
{
   static constexpr auto value(const int power_value) noexcept -> ArithmeticType
   {
     return ((power_value == 0) ? ArithmeticType { 1 } : ArithmeticType { 2 } * pow2_maker<ArithmeticType>::value(power_value - 1));
   }
};

} } } } // namespace boost::multiprecision::backends::cpp_df_qf_detail

#endif // BOOST_MP_CPP_DF_QF_DETAIL_2023_01_02_HPP
