/**
 *     @brief Cordic application demo
 */

#include <math.h>
#include "cordic.h"
#include "frac_math_helper.h"

/** Defines the resolution of our cordic engine */
#define DEMO_RESOLUTION 16

/** Define if angle increments or decrements */
#define DIRECTION       1

/** Variables used in this file */
cordic_engine cordic(DEMO_RESOLUTION);

/** Angle variable */
frac12 angle = TO_FRAC_12(0.0f);
frac16 cosine;
frac16 sine;

/**
 * @brief Arduino default setup routine
 */
void setup (void)
{
  /* Open serial port */
  Serial.begin(115200);

}

/**
 * @brief Arduino default main loop
 */
void loop (void)
{
  /* Prints a greeting message */
  Serial.println("Welcome to cordic Demo App \n\r");


  for (;;) {

    /* take sine and cosine of current angle and
     * prints on the console
     */
    sine = cordic.sine(angle);
    cosine = cordic.cosine(angle);


    Serial.print("Sine value of   ");

    /* converts angles to degrees */
    Serial.print((FRAC_12_TO_FLOAT(angle) * 180.0f) / 3.14159f);
    Serial.print("  is: ");
    Serial.print(FRAC_16_TO_FLOAT(sine));
    Serial.print("\n\r");

    /* converts angles to degrees  in cosine too*/
    Serial.print("Cosine value of   ");
    Serial.print((FRAC_12_TO_FLOAT(angle) * 180.0f) / 3.14159f);
    Serial.print("  is:  ");
    Serial.print(FRAC_16_TO_FLOAT(cosine));
    Serial.print("\n\r");

#if DIRECTION == 1
    /* We compute a quarter turn of canonical circle
     * which stills sufficient to demonstrate
     * basic cordic funcionality
     */
    angle += TO_FRAC_12(0.02f);
    if (angle > TO_FRAC_12(1.5708f)) {
    angle = TO_FRAC_12(0.0f);
    }
#else
    angle -= TO_FRAC_12(0.02f);
    if (angle < TO_FRAC_12(-1.5708f)) {
    angle = TO_FRAC_12(0.0f);
    }
#endif
    

     delay(500);
   
  }
}

