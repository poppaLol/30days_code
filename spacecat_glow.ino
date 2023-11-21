#include "Arduino.h"

const byte PHOTORESISTOR_PIN = A0;
const byte RED_PIN = 11;
const byte GREEN_PIN = 10;
const byte BLUE_PIN = 9;

const auto ITERATIONS_MAX = 20000;

void displayColor(byte red, byte green, byte blue) {
  analogWrite(RED_PIN, red);      // write red LED intensity using PWM
  analogWrite(GREEN_PIN, green);  // write green LED intensity using PWM
  analogWrite(BLUE_PIN, blue);    // write blue LED intensity using PWM
}

//this is hacky but a simple way to limit a value between 0.0 and 1.0
//which we can then pass to the sinFunc to get a value between -1.0 and 1.0
//the offset value allows us to space the various colour signals relative to
//each other
float ratioWithOffset(int currentMillis, int offSet) {
  return float(currentMillis - offSet % ITERATIONS_MAX)/float(ITERATIONS_MAX);
}

//this returns a sin wave values for a given input
float sinFunc(float pos)
{
  return sin(pos*2*M_PI);
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  //get current time
  unsigned long currentMillis = millis();
  
  //get current light level
  unsigned int light_value = analogRead(PHOTORESISTOR_PIN);
  
  if (light_value > 60) { //if light level is high(ish) then turn off the LED channels
    displayColor(0, 0, 0);
  } else {
    //calculate percent through interval
    float redRatioTimeInterval = ratioWithOffset(currentMillis, 0);
    float greenRatioTimeInterval = ratioWithOffset(currentMillis, 7000);
    float blueRatioTimeInterval = ratioWithOffset(currentMillis, 14000);

    //calculate the colour from the interval, and ignore negative values (-1.0 to 0 in our case)
    //to allow some nice colour mixing as channels turn on and off
    byte redval = max(sinFunc(redRatioTimeInterval) * 255, 0);
    byte greenval = max(sinFunc(greenRatioTimeInterval) * 255, 0);
    byte blueval = max(sinFunc(blueRatioTimeInterval) * 255, 0);

    displayColor(redval, greenval, blueval);
    //Serial.print(redval); Serial.print(",");
    //Serial.print(greenval); Serial.print(",");
    //Serial.println(blueval);
  }
}
