/**
 * Cordic on Arduino Demo, calculates the sine and cosine
 * and displays the waveform on Arduino plotter
 */

#include <cmath>
#include "cordic.h"

#define kMaxRange int16_t(M_PI_2 * 16384.0f)

int16_t angle = 0;
uint8_t quarter = 0;

void setup (void) {
  //Uses high baud rate to improve the data visualization
  Serial.begin(2000000);
}

void loop (void) {

  //Prints the calculated data on serial plottet (we can see the waveform)
  Serial.print(ArduinoCordic::GetCosine(angle));
  Serial.print(",");
  Serial.println(ArduinoCordic::GetSine(angle));

  //manage the next point using circle symmetry:
  switch(quarter) {
    //first quarter just increments until pi/2
    case 0:
      angle++;
      if(angle == kMaxRange) {
        quarter++;
      }
    break;

    //second quarter, decreases angle until zero and forms 1st half of circle
    case 1:
      angle--;
      if(angle == 0) {
        quarter++;
      }
    break;

    //third quarter, time for negative angles, go until -pi/2
    case 2:
      angle--;
      if(angle == -kMaxRange) {
        quarter++;
      }
    break;

    // fourth quarter, negative towards to zero and complete the waveform
    case 3:
      angle++;
      if(angle == 0) {
        quarter = 0;
      }
    break;
  }

  delay_ms(1);
}

