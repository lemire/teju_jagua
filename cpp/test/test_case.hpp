#ifndef AMARU_CPP_TEST_TEST_CASE_H_
#define AMARU_CPP_TEST_TEST_CASE_H_

#include "amaru/config.h"
#include "cpp/common/fields.hpp"
#include "cpp/common/traits.hpp"

#include <iosfwd>

namespace amaru {
namespace test {

template <typename T>
struct test_case_t {

  using fields_t = cpp_fields_t<T>;

  explicit test_case_t(T value, fields_t const& expected);

  explicit test_case_t(fields_t const& amaru_binary, fields_t const& expected);

  bool
  operator ==(fields_t const& actual) const;

  T const& value() const;

  fields_t const& expected() const;

private:

  T        value_;
  fields_t expected_;

}; // test_case_t

template <typename C, typename CT, typename T>
std::basic_ostream<C, CT>&
operator <<(std::basic_ostream<C, CT>& os, test_case_t<T> const& test_case) {

  using traits_t          = amaru::traits_t<T>;
  using fields_t          = typename test_case_t<T>::fields_t;
  using streamable_uint_t = typename fields_t::streamable_uint_t;

  auto const value        = test_case.value();
  auto const ieee         = traits_t::value_to_ieee(value);
  auto const amaru_binary = traits_t::ieee_to_amaru_binary(ieee);

  // Specially formatted for looking pretty in gtest messages.
  return os << test_case.expected() << "\n"
    "    [value = " << streamable_uint_t{amaru_binary.c.mantissa} <<
    " * 2^(" << amaru_binary.c.exponent << ")]";
}

} // namespace test
} // namespace amaru

#endif // AMARU_CPP_TEST_TEST_CASE_H_
