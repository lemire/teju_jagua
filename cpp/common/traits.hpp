#ifndef AMARU_CPP_COMMON_TRAITS_HPP_
#define AMARU_CPP_COMMON_TRAITS_HPP_

#include "amaru/config.h"
#include "amaru/double.h"
#include "amaru/float.h"
#include "amaru/float128.h"
#include "amaru/ieee754.h"

#include "cpp/common/fields.hpp"
#include "cpp/common/other.hpp"

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace amaru {

/**
 * @brief Traits for floating point number types.
 *
 * Amaru (and possibly other third-party libraries with the same purpose) are
 * supposed to be called in C which doesn't support overloading and templates.
 * This class serves to wrap C functions (and data) referring to specific types
 * into a generic interface. For instance,
 * \c amaru_from_double_to_decimal_compact and
 * \c amaru_from_float_to_decimal_compact are two such functions that are
 * wrapped, respectively, by \c traits_t<double>::amaru_compact and
 * \c traits_t<float>::amaru_compact, make easier to call then in generic
 * tests. Specialisations of \c traits_t are provided for \c float and
 * \c double. They contain the following members.
 *
 * Types:
 *
 * \li u1_t               The 1-limb \c unsigned integer type.
 * \li fields_t           Fields type storing exponent and mantissa.
 * \li streamable_float_t A type constructible from the one of interest that is
 *                        streamable.
 * \li streamable_uint_t  A type constructible from \e u1_t that is streamable.
 *
 * Static data:
 *
 * \li exponent_size Exponent size in bits.
 * \li mantissa_size Mantissa size in bits.
 *
 * Static functions:
 *
 * \li fields_t to_ieee(T value)
 *   Returns IEEE-754's representation of \e value.
 * \li fields_t amaru_compact(T value)
 *   Returns Amaru decimal fields of \e value found by the compact table method.
 * \li fields_t amaru_full(T value)
 *   Returns Amaru decimal fields of \e value found by the full table method.
 * \li fields_t other(T value)
 *   Returns the third-party library binary fields of \e value.
 *
 * @warning Since platforms and third-party libraries lack support for larger
 * types (e.g., float128_t and uint128_t). Hence, some of the functions above or
 * even the whole corresponding \c traits_t specialisation might be
 * undefined.
 *
 * \tparam T                The type of interest.
 */
template <typename T>
struct traits_t;

namespace detail {

  /**
   * \brief Returns the IEEE-754 floating point value corresponding to the
   * given mantissa and exponent.
   *
   * \tparam T              The floating point number type.
   * \tparam mantissa_size  The number of bits in the mantissa.
   * \tparam U              An unsigned integer type of the same size as \c T.
   */
  template <typename T, std::uint32_t mantissa_size>
  T
  ieee_to_value(typename amaru::traits_t<T>::fields_t ieee) {

    using traits_t = amaru::traits_t<T>;
    using u1_t     = typename traits_t::u1_t;

    static_assert(sizeof(T) == sizeof(ieee.c.mantissa), "Incompatible types");

    auto const exponent = static_cast<u1_t>(ieee.c.exponent);
    auto const bits     = (exponent << mantissa_size) | ieee.c.mantissa;

    T value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
  }

} // namespace detail

// Specialisation of traits_t for float.
template <>
struct traits_t<float> {

  using u1_t     = amaru32_u1_t;
  using fields_t = cpp_fields_t<float>;

  static auto constexpr exponent_size =
    std::uint32_t{amaru_ieee754_binary32_exponent_size};
  static auto constexpr mantissa_size =
    std::uint32_t{amaru_ieee754_binary32_mantissa_size};

  static
  fields_t
  value_to_ieee(float const value) {
    return fields_t{amaru_float_to_ieee32(value)};
  }

  static
  float
  ieee_to_value(fields_t ieee) {
    return detail::ieee_to_value<float, mantissa_size>(ieee);
  }

  static
  fields_t
  ieee_to_amaru_binary(fields_t ieee32) {
    return fields_t{amaru_ieee32_to_amaru_binary(ieee32.c)};
  }

  static
  fields_t
  amaru_compact(float const value) {
    return fields_t{amaru_float_to_amaru_decimal_compact(value)};
  }

  static
  fields_t
  amaru_full(float const value) {
    return fields_t{amaru_float_to_amaru_decimal_full(value)};
  }

  static
  fields_t
  dragonbox_compact(float const value) {
    auto const fields = amaru::dragonbox_compact::to_decimal(value);
    return fields_t{std::int32_t{fields.exponent}, u1_t{fields.significand}};
  }

  static
  fields_t
  dragonbox_full(float const value) {
    auto const fields = amaru::dragonbox_full::to_decimal(value);
    return fields_t{std::int32_t{fields.exponent}, u1_t{fields.significand}};
  }

}; // traits_t<float>

// Specialisation of traits_t for float.
template <>
struct traits_t<double> {

  using u1_t     = amaru64_u1_t;
  using fields_t = cpp_fields_t<double>;

  static auto constexpr exponent_size =
    std::uint32_t{amaru_ieee754_binary64_exponent_size};
  static auto constexpr mantissa_size =
    std::uint32_t{amaru_ieee754_binary64_mantissa_size};

  static
  fields_t
  value_to_ieee(double const value) {
    return fields_t{amaru_double_to_ieee64(value)};
  }

  static
  double
  ieee_to_value(fields_t ieee) {
    return detail::ieee_to_value<double, mantissa_size>(ieee);
  }

  static
  fields_t
  ieee_to_amaru_binary(fields_t ieee64) {
    return fields_t{amaru_ieee64_to_amaru_binary(ieee64.c)};
  }

  static
  fields_t
  amaru_compact(double const value) {
    return fields_t{amaru_double_to_amaru_decimal_compact(value)};
  }

  static
  fields_t
  amaru_full(double const value) {
    return fields_t{amaru_double_to_amaru_decimal_full(value)};
  }

  static
  fields_t
  dragonbox_compact(double const value) {
    auto const fields = amaru::dragonbox_compact::to_decimal(value);
    return fields_t{std::int32_t{fields.exponent}, u1_t{fields.significand}};
  }

  static
  fields_t
  dragonbox_full(double const value) {
    auto const fields = amaru::dragonbox_full::to_decimal(value);
    return fields_t{std::int32_t{fields.exponent}, u1_t{fields.significand}};
  }

}; // traits_t<double>

#if defined(AMARU_HAS_FLOAT128)

// Specialisation of traits_t for float128.
template <>
struct traits_t<float128_t> {

  using u1_t     = amaru128_u1_t;
  using fields_t = cpp_fields_t<float128_t>;

  static auto constexpr exponent_size =
    std::uint32_t{amaru_ieee754_binary128_exponent_size};
  static auto constexpr mantissa_size =
    std::uint32_t{amaru_ieee754_binary128_mantissa_size};

  static
  fields_t
  value_to_ieee(float128_t const value) {
    return fields_t{amaru_float128_to_ieee128(value)};
  }

  static
  float128_t
  ieee_to_value(fields_t ieee) {
    return detail::ieee_to_value<float128_t, mantissa_size>(ieee);
  }

  static
  fields_t
  ieee_to_amaru_binary(fields_t ieee128) {
    return fields_t{amaru_ieee128_to_amaru_binary(ieee128.c)};
  }

  static
  fields_t
  amaru_compact(float128_t const value) {
    return {amaru_float128_to_amaru_decimal_compact(value)};
  }

  static
  fields_t
  amaru_full(float128_t const value) {
    return {amaru_float128_to_amaru_decimal_full(value)};
  }

  // TODO (CN): Perhaps we could use Ryu for float128_t but at the moment
  // testing and benchmarking against other libraries is not supported.

}; // traits_t<float128_t>

#endif // defined(AMARU_HAS_FLOAT128)

} // namespace amaru

#endif // AMARU_CPP_COMMON_TRAITS_HPP_
