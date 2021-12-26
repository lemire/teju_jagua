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

enum {
  ssize = CHAR_BIT * sizeof(suint_t),
  dsize = CHAR_BIT * sizeof(duint_t),
};

static inline
rep_t remove_trailing_zeros(rep_t decimal) {

  suint_t const m = (~((suint_t)0)) / 10 + 1;
  duint_t       p = ((duint_t) m) * decimal.mantissa;

  do {
    ++decimal.exponent;
    decimal.mantissa = (suint_t) (p >> ssize);
    p                = ((duint_t) m) * decimal.mantissa;
  } while ((suint_t) p < m);

  return decimal;
}

static inline
duint_t add(duint_t upper, duint_t lower) {
  return (upper << ssize) + lower;
}

static inline
suint_t scale(uint32_t const n_bits, duint_t const lower_prod, duint_t const upper_limbs) {
  if (n_bits >= ssize)
    return upper_limbs >> (n_bits - ssize);

  suint_t const lower_limb  = (suint_t) lower_prod;
  return (lower_limb >> n_bits) | (upper_limbs << (ssize - n_bits));
}

static inline
suint_t is_multiple_of_pow5(suint_t const upper, suint_t const lower,
  uint32_t const n_bits, duint_t const upper_prod,
  duint_t const lower_prod, duint_t const upper_limbs) {

  duint_t const multiplier = add(upper, lower);

  if (n_bits >= dsize) {

    if (AMARU_LOWER_BITS(upper_limbs, n_bits - ssize) >> ssize > 0)
      return false;

    duint_t const lower_limb = (suint_t) lower_prod;
    duint_t const prod       = add(upper_limbs, lower_limb);
    return prod < multiplier;
  }

  duint_t const prod = add(upper_prod, lower_prod);

  return AMARU_LOWER_BITS(prod, n_bits) < multiplier;
}

rep_t
TO_AMARU_DEC(bool const negative, int32_t const exponent,
  suint_t const mantissa) {

  rep_t decimal;
  decimal.negative = negative;

  if (exponent == exponent_min && mantissa == 0) {
    decimal.exponent = 0;
    decimal.mantissa = 0;
    return decimal;
  }

  decimal.exponent = log10_pow2(exponent);

  int32_t  const e             = exponent - decimal.exponent;

  uint32_t const index         = exponent - exponent_min;
  suint_t  const upper         = scalers[index].upper;
  suint_t  const lower         = scalers[index].lower;
  uint32_t const n_bits        = scalers[index].shift;

  suint_t  const m_a           = 2 * mantissa - 1;
  duint_t  const upper_prod_a  = ((duint_t) upper) * m_a;
  duint_t  const lower_prod_a  = ((duint_t) lower) * m_a;

  duint_t  const upper_prod_b  = upper_prod_a + 2 * ((duint_t) upper);
  duint_t  const lower_prod_b  = lower_prod_a + 2 * ((duint_t) lower);
  duint_t  const upper_limbs_b = upper_prod_b + (lower_prod_b >> ssize);

  suint_t  const b_hat         = scale(n_bits, lower_prod_b, upper_limbs_b);
  suint_t  const b             = b_hat / 2;

  bool shorten;

  if (mantissa != mantissa_min || exponent == exponent_min) {

    suint_t const s = 10 * (b / 10);

    if (s == b) {
      bool const is_exact = exponent > 0 &&
        decimal.exponent <= exponent_critical && b_hat % 2 == 0 &&
        is_multiple_of_pow5(upper, lower, n_bits + e, upper_prod_b,
          lower_prod_b, upper_limbs_b);
      shorten = !is_exact || mantissa % 2 == 0;
    }

    else {
      duint_t const upper_limbs_a = upper_prod_a + (lower_prod_a >> ssize);
      suint_t const a_hat         = scale(n_bits, lower_prod_a, upper_limbs_a);

      bool const is_exact = exponent > 0 &&
        decimal.exponent <= exponent_critical && a_hat % 2 == 0 &&
        is_multiple_of_pow5(upper, lower, n_bits + e, upper_prod_a,
          lower_prod_a, upper_limbs_a);
      suint_t const a = a_hat / 2 + !is_exact;
      shorten = s > a || (s == a && (!is_exact || mantissa % 2 == 0));
    }

    if (shorten) {
      decimal.mantissa = s;
      return remove_trailing_zeros(decimal);
    }

    else {
      suint_t const m           = m_a + 1; // = 2 * mantissa
      duint_t const upper_prod  = upper_prod_a + ((duint_t) upper) ;
      duint_t const lower_prod  = lower_prod_a + ((duint_t) lower);
      duint_t const upper_limbs = upper_prod + (lower_prod >> ssize);
      suint_t const c_hat       = scale(n_bits, lower_prod, upper_limbs);
      decimal.mantissa          = c_hat / 2;

      if (c_hat % 2 == 1)
        decimal.mantissa += decimal.mantissa % 2 == 1 ||
          !(0 > e && ((uint32_t) -e) < mantissa_size + 2 &&
          m % AMARU_POW2(suint_t, -e) == 0);
    }
  }
  else {
    // m = 4 * mantissa - 1 = 2 * m_a + 1
    duint_t const upper_prod  = 2 * upper_prod_a + ((duint_t) upper);
    duint_t const lower_prod  = 2 * lower_prod_a + ((duint_t) lower);
    duint_t const upper_limbs = upper_prod + (lower_prod >> ssize);

    suint_t const a_hat    = scale(n_bits, lower_prod, upper_limbs);
    bool    const is_exact = exponent > 1 &&
      decimal.exponent <= exponent_critical && a_hat % 4 == 0 &&
      is_multiple_of_pow5(upper, lower, n_bits + e, upper_prod, lower_prod,
        upper_limbs);
    suint_t const a        = a_hat / 4 + !is_exact;
    if (b >= a) {
      suint_t const s = 10 * (b / 10);
      if (s >= a) {
        decimal.mantissa = s;
        return remove_trailing_zeros(decimal);
      }

      else {
        // m = 2 * mantissa = m_a + 1
        duint_t const upper_prod  = upper_prod_a + ((duint_t) upper);
        duint_t const lower_prod  = lower_prod_a + ((duint_t) lower);
        duint_t const upper_limbs = upper_prod + (lower_prod >> ssize);

        suint_t const c_hat       = scale(n_bits, lower_prod, upper_limbs);
        decimal.mantissa          = c_hat / 2;

        if (decimal.mantissa < a)
          ++decimal.mantissa;
        else if (c_hat % 2 == 1)
          decimal.mantissa += decimal.mantissa % 2 == 1 ||
            !(((uint32_t) -e) <= mantissa_size + 1 && decimal.exponent <= 0);
      }
    }
    else {
      --decimal.exponent;
      suint_t const m           = 20 * mantissa;
      duint_t const upper_prod  = ((duint_t) upper) * m;
      duint_t const lower_prod  = ((duint_t) lower) * m;
      duint_t const upper_limbs = upper_prod + (lower_prod >> ssize);

      static_assert(CHAR_BIT * sizeof(duint_t) >= mantissa_size + 4,
        "duint is not large enough for calculations to not overflow.");

      suint_t const c_hat = scale(n_bits, lower_prod, upper_limbs);

      decimal.mantissa = c_hat / 2;
      if (c_hat % 2 == 1)
        decimal.mantissa += decimal.mantissa % 2 == 1 ||
          !(((uint32_t) -e) <= mantissa_size + 1 && decimal.exponent <= 0);
    }
  }
  return decimal;
}

#ifdef __cplusplus
}
#endif
