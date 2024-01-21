/**
 * @file amaru/float128.h
 *
 * Amaru and helpers for \c float128_t values.
 */

#ifndef AMARU_AMARU_FLOAT128_H_
#define AMARU_AMARU_FLOAT128_H_

#include "amaru/config.h"

#if defined(AMARU_HAS_FLOAT128)

#include "amaru/generated/ieee128.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets IEEE-754's binary128 representation of a \c float128_t.
 *
 * See https://en.wikipedia.org/wiki/Quadruple-precision_floating-point_format
 *
 * @pre <tt>value > 0</tt>.
 *
 * @param value             The given \c float128_t.
 *
  * @returns IEEE-754's binary128 representation of \e value.
 */
amaru128_fields_t
amaru_float128_to_ieee128(float128_t value);

/**
 * @brief Gets Amaru's binary representation of a given IEEE-754 binary128 one.
 *
 * @pre <tt>value > 0</tt>.
 *
 * @param ieee128           The given IEEE-754 binary128 representation.
 *
 * @returns Amaru's binary representation \e value.
 */
amaru128_fields_t
amaru_ieee128_to_amaru_binary(amaru128_fields_t ieee128);

/**
 * @brief Gets Amaru's decimal representation of a \c float128_t.
 *
 * @pre <tt>value > 0</tt>.
 *
 * @param value             The given \c float128_t.
 *
 * @returns Amaru's decimal representation of \e value.
 */
amaru128_fields_t
amaru_float128_to_amaru_decimal(float128_t value);

#ifdef __cplusplus
}
#endif

#endif // defined(AMARU_HAS_FLOAT128)
#endif // AMARU_AMARU_FLOAT128_H_
