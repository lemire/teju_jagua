#ifndef TO_AMARU_DEC
#error "Invalid inclusion of amaru.h."
#endif

#include "common.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static_assert(sizeof(duint_t) >= 2 * sizeof(suint_t),
  "duint_t must be at least twice the size of suint_t.");

enum {
  ssize = CHAR_BIT * sizeof(suint_t),
  dsize = CHAR_BIT * sizeof(duint_t),
};

static inline
rep_t remove_trailing_zeros(bool const negative, int32_t exponent,
  suint_t mantissa) {

  suint_t const m = (~((suint_t)0)) / 10 + 1;
  duint_t       p = ((duint_t) m) * mantissa;

  do {
    ++exponent;
    mantissa = (suint_t) (p >> ssize);
    p        = ((duint_t) m) * mantissa;
  } while ((suint_t) p < m);

  rep_t const decimal = { negative, exponent, mantissa };
  return decimal;
}

static inline
duint_t pack(duint_t upper_m, duint_t lower_m) {
  return (upper_m << ssize) + lower_m;
}

static inline
suint_t scale(suint_t const m, duint_t const upper, duint_t const lower,
  uint32_t const shift) {

  duint_t const upper_m = upper * m;
  duint_t const lower_m = lower * m;

  if (shift >= ssize)
    return (upper_m + (lower_m >> ssize)) >> (shift - ssize);

  return (lower_m >> shift) + (upper_m << (ssize - shift));
}

static inline
suint_t is_multiple_of_pow5(suint_t const m, duint_t const upper,
  duint_t const lower, uint32_t const n_bits) {

  duint_t const multiplier = pack(upper, lower);
  duint_t const upper_m    = upper * m;
  duint_t const lower_m    = lower * m;

  if (n_bits >= dsize) {

    duint_t const upper_limbs = upper_m + (lower_m >> ssize);

    if (AMARU_LSB(upper_limbs, n_bits - ssize) >= AMARU_POW2(duint_t, ssize))
      return false;

    duint_t const lower_limb = (suint_t) lower_m;
    duint_t const prod       = pack(upper_limbs, lower_limb);
    return prod < multiplier;
  }

  duint_t const prod = pack(upper_m, lower_m);
  return AMARU_LSB(prod, n_bits) < multiplier;
}

rep_t
TO_AMARU_DEC(bool const negative, int32_t const exponent,
  suint_t const mantissa) {

  if (exponent == bin_exponent_min && mantissa == 0) {
    rep_t decimal = { negative, 0, 0 };
    return decimal;
  }

  if (exponent == 0) {
    if (mantissa % 10 == 0)
      return remove_trailing_zeros(negative, 0, mantissa);
    rep_t decimal = { negative, 0, mantissa };
    return decimal;
  }

  int32_t  const f = log10_pow2(exponent);

  int32_t  const e = exponent - f;

#ifdef AMARU_USE_COMPACT_TBL
  int32_t  const e0    = log2_pow10(f) - f;
  uint32_t const extra = e - e0;
  int32_t  const i     = f - dec_exponent_min;
#else
  int32_t  const e0    = e;
  uint32_t const extra = 0;
  int32_t  const i     = exponent - bin_exponent_min;
#endif

#ifdef AMARU_UPPER_IS_ZERO
  duint_t  const upper  = 0;
#else
  duint_t  const upper  = scalers[i].upper;
#endif
  duint_t  const lower  = scalers[i].lower;
#ifdef AMARU_SHIFT
  uint32_t const shift  = AMARU_SHIFT;
#else
  uint32_t const shift  = scalers[i].shift;
#endif

  uint32_t const n_bits         = shift + e0;
  bool     const might_be_exact = e > 0 && f <= bin_exponent_critical;

  // The below doesn't overflow. (See generator's overflow check #1).
  suint_t const m_b   = 2 * mantissa + 1;
  suint_t const b_hat = scale(m_b << extra, upper, lower, shift);
  suint_t const b     = b_hat / 2;

  if (mantissa != normal_mantissa_min || exponent == bin_exponent_min) {

    suint_t const s = 10 * (b / 10);

    if (s == b) {
      bool const is_exact = might_be_exact && b_hat % 2 == 0 &&
        is_multiple_of_pow5(m_b, upper, lower, n_bits);
      if (!is_exact || mantissa % 2 == 0)
        return remove_trailing_zeros(negative, f, s);
    }

    else {
      suint_t const m_a      = 2 * mantissa - 1;
      suint_t const a_hat    = scale(m_a<< extra, upper, lower, shift);
      bool    const is_exact = might_be_exact && a_hat % 2 == 0 &&
        is_multiple_of_pow5(m_a, upper, lower, n_bits);
      suint_t const a = a_hat / 2 + !is_exact;
      if (s > a || (s == a && (!is_exact || mantissa % 2 == 0)))
        return remove_trailing_zeros(negative, f, s);
    }

    suint_t const m_c     = 2 * mantissa;
    suint_t const c_hat   = scale(m_c << extra, upper, lower, shift);
    rep_t         decimal = { negative, f, c_hat / 2 };

    decimal.mantissa += c_hat % 2 == 1 && (decimal.mantissa % 2 == 1 ||
      !(e < 0 && ((uint32_t) -e) < mantissa_size + 2 &&
      m_c % AMARU_POW2(suint_t, -e) == 0));

    return decimal;
  }

  // mantissa = mantissa_min

  // The below doesn't overflow. (See generator's overflow check #2).
  suint_t const m_a      = 4 * normal_mantissa_min - 1;
  suint_t const a_hat    = scale(m_a << extra, upper, lower, shift);
  bool    const is_exact = might_be_exact && a_hat % 4 == 0 &&
    is_multiple_of_pow5(m_a, upper, lower, n_bits);
  suint_t const a        = a_hat / 4 + !is_exact;

  if (b >= a) {

    suint_t const s = 10 * (b / 10);

    if (s >= a)
      return remove_trailing_zeros(negative, f, s);

    suint_t const m_c     = 2 * mantissa;
    suint_t const c_hat   = scale(m_c << extra, upper, lower, shift);
    rep_t         decimal = { negative, f, c_hat / 2 };
    if (decimal.mantissa < a)
      ++decimal.mantissa;

    else if (c_hat % 2 == 1)
      decimal.mantissa += decimal.mantissa % 2 == 1 ||
        !(((uint32_t) -e) <= mantissa_size + 1 && decimal.exponent <= 0);

    return decimal;
  }

  // The below doesn't overflow. (See generator's overflow check #2).
  suint_t const m_c     = 20 * normal_mantissa_min;
  suint_t const c_hat   = scale(m_c << extra, upper, lower, shift);
  rep_t         decimal = { negative, f - 1, c_hat / 2 };

  if (c_hat % 2 == 1)
    decimal.mantissa += decimal.mantissa % 2 == 1 ||
      !(((uint32_t) -e) <= mantissa_size + 1 && decimal.exponent <= 0);

  return decimal;
}

#ifdef __cplusplus
}
#endif
