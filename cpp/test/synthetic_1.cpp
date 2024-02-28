// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2024 Cassio Neri <cassio.neri@gmail.com>

#include "cpp/test/impl.hpp"

// Other macros required by amaru/div10.h and amaru/mshift.h.
#define amaru_do_not_define_amaru_multiply
#define amaru_calculation_mshift amaru_synthetic_1
#define amaru_calculation_shift  32

#include "cpp/test/synthetic_1.hpp"

#include "amaru/div10.h"
#include "amaru/mshift.h"

using impl_t = amaru::test::synthetic_1_t;

int const impl_t::shift = amaru_calculation_shift;

amaru_u1_t
impl_t::div10(amaru_u1_t const m) {
  return amaru_div10(m);
}

amaru_u1_t
impl_t::mshift(amaru_u1_t const m, amaru_u1_t const u, amaru_u1_t const l) {
  return amaru_mshift(m, u, l);
}
