#ifndef AMARU_AMAHU_INFIMUM_H_
#define AMARU_AMAHU_INFIMUM_H_

#ifdef __cplusplus
extern "C" {
#endif

#if (amaru_calculation_infimum % 2 == 0 &&                         \
    amaru_calculation_infimum >  2 * (amaru_multiply_type / 2)     \
  ) || (                                                           \
    amaru_calculation_infimum % 2 == 1 &&                          \
    amaru_calculation_infimum != 2 * (amaru_multiply_type / 2) + 1 \
  )
  #error "Value of 'amaru_calculation_infimum' isn't supported."
#endif

static inline
amaru_limb1_t
infimum(amaru_limb1_t const m, amaru_limb1_t const upper,
  amaru_limb1_t const lower) {

  #if amaru_calculation_infimum == amaru_built_in_4

    amaru_limb2_t const n = (((amaru_limb2_t) upper) << amaru_size) | lower;
    return (((amaru_limb4_t) n) * m) >> amaru_calculation_shift;

  #elif amaru_calculation_infimum == amaru_syntectic_2

    amaru_limb2_t const n = (((amaru_limb2_t) upper) << amaru_size) | lower;
    amaru_limb2_t u_prod;
    amaru_limb2_t const l_prod = amaru_multiply(n, m, &u_prod);

    #if amaru_calculation_shift >= 2 * amaru_size
      return u_prod >> (amaru_calculation_shift - 2 * amaru_size);
    #else
      return u_prod << (2 * amaru_size - amaru_calculation_shift) |
        l_prod >> (amaru_calculation_shift - amaru_size);
    #endif

  #elif amaru_calculation_infimum == amaru_built_in_2

    amaru_limb2_t const u_prod = ((amaru_limb2_t) upper) * m;
    amaru_limb2_t const l_prod = ((amaru_limb2_t) lower) * m;
    return (u_prod + (l_prod >> amaru_size)) >>
      (amaru_calculation_shift - amaru_size);

  #elif amaru_calculation_infimum == amaru_syntectic_1

    amaru_limb1_t ul_prod;
    (void) amaru_multiply(lower, m, &ul_prod);

    amaru_limb1_t uu_prod;
    amaru_limb1_t const lu_prod = amaru_multiply(upper, m, &uu_prod);
    amaru_limb1_t const l_prod  = ul_prod + lu_prod;

    amaru_limb1_t const carry  = l_prod < ul_prod;
    amaru_limb1_t const u_prod = uu_prod + carry;

    #if amaru_calculation_shift >= 2 * amaru_size
      return u_prod >> (amaru_calculation_shift - 2 * amaru_size);
    #else
      return u_prod << (2 * amaru_size - amaru_calculation_shift) |
        (l_prod >> amaru_calculation_shift);
    #endif

  #elif amaru_calculation_infimum == amaru_built_in_1

    amaru_limb1_t const p2 = ((amaru_limb1_t) 1) << (amaru_size / 2);

    amaru_limb1_t const a3 = upper / p2;
    amaru_limb1_t const a2 = upper % p2;
    amaru_limb1_t const a1 = lower / p2;
    amaru_limb1_t const a0 = lower % p2;

    amaru_limb1_t const b1 = m / p2; // b1 is relatively small.
    amaru_limb1_t const b0 = m % p2;

    // result, carry, temporary:
    amaru_limb1_t r, c, t;

    // order 0:
    t  = b0 * a0;
    r  = t / p2;

    // order 1:
    r += b1 * a0;
    t  = b0 * a1;
    r += t;
    c  = r < t;
    r /= p2;

    // order 2:
    r += b1 * a1 + (c << (amaru_size / 2));
    t  = b0 * a2;
    r += t;
    c  = r < t;
    r /= p2;

    // order 3:
    r += b1 * a2 + (c << (amaru_size / 2));
    t  = b0 * a3;
    r += t;
    c  = r < t;
    r /= p2;

    // order 4:
    r += b1 * a3 + (c << (amaru_size / 2));

    #if amaru_calculation_shift >= 2 * amaru_size
      return r >> (amaru_calculation_shift - 2 * amaru_size);
    #else
      #error "Unsupported combination of size, shift and calculation."
    #endif

  #endif
}

#ifdef __cplusplus
}
#endif

#endif // AMARU_AMAHU_INFIMUM_H_
