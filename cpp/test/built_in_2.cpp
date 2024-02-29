// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Cassio Neri <cassio.neri@gmail.com>

#include "cpp/test/impl.hpp"

// Other macros required by teju/div10.h and teju/mshift.h.
#define teju_calculation_div10  teju_built_in_2
#define teju_calculation_mshift teju_built_in_2
#define teju_calculation_shift  32

#include "teju/div10.h"
#include "teju/mshift.h"

using impl_t = teju::test::built_in_2_t;

int const impl_t::shift = teju_calculation_shift;

teju_u1_t
impl_t::div10(teju_u1_t const m) {
  return teju_div10(m);
}

teju_u1_t
impl_t::mshift(teju_u1_t const m, teju_u1_t const u, teju_u1_t const l) {
  return teju_mshift(m, u, l);
}
