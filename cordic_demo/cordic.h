#pragma once 

#include <cstdint>
#include <cmath>

namespace ArduinoCordic {

/**
 * @fn GetSine
 * @brief Calculates the sine of given angle using cordic
 * @param angle - scaled angle in radians
 * @return  scaled sine of this angle 
 * @note angle MUST be between -pi/2 to pi/2 scaled by 16384
 * @note angles outside of specified range will return 0 
 * @note return is in -1 to 1 scaled by 32768
 */
int16_t GetSine(int16_t angle);

/**
 * @fn GetCosine
 * @brief Calculates the cosine of given angle using cordic
 * @param angle - scaled angle in radians
 * @return  scaled sine of this angle 
 * @note angle MUST be between -pi/2 to pi/2 scaled by 16384
 * @note angles outside of specified range will return 0 
 * @note return is in -1 to 1 scaled by 32768
 */
int16_t GetCosine(int16_t angle);

}

