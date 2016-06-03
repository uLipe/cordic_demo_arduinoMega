/*
 * @brief helper for fractional values
 *
 */

#ifndef __FRAC_MATH_HELPER_H
#define __FRAC_MATH_HELPER_H


/** convert to frac16 macro */
#define TO_FRAC_16(x) (signed short)(x * 32768.0)
#define TO_FRAC_12(x) (signed short)(x * 4096.0)


/** convert to float from frac16 */
#define FRAC_16_TO_FLOAT(x) (float)((float)x / 32768.0)
#define FRAC_12_TO_FLOAT(x) (float)((float)x / 4096.0)


/** type of fractionals */
typedef signed short frac16;
typedef signed short frac12;



#endif /* __FRAC_MATH_HELPER_H */

