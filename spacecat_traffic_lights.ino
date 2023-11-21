#include "Arduino.h"  // include information about our HERO

const byte RED_LIGHTS_PIN = 10;    // pin controlling the red led
const byte YELLOW_LIGHTS_PIN = 11;  // pin controlling the yellow led
const byte GREEN_LIGHTS_PIN = 12;  // pin controlling the green led

const byte RED_LIGHTS_SWITCH_PIN = 2;    // red lights controlled by switch 1
const byte YELLOW_LIGHTS_SWITCH_PIN = 3;  // yellow lights controlled by switch 2
const byte GREEN_LIGHTS_SWITCH_PIN = 4;  // green lights controlled by switch 3

enum LedState { red, redamber, green, amber };
LedState next_state;

void setup() {
  pinMode(RED_LIGHTS_PIN, OUTPUT);    // pin controlling the cabin lights
  pinMode(YELLOW_LIGHTS_PIN, OUTPUT);  // pin controlling the storage lights
  pinMode(GREEN_LIGHTS_PIN, OUTPUT);  // pin controlling the exterior lights

  pinMode(RED_LIGHTS_SWITCH_PIN, INPUT);    // pin connected to switch 1 (cabin lights)
  pinMode(YELLOW_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 2 (storage lights)
  pinMode(GREEN_LIGHTS_SWITCH_PIN, INPUT);  // pin connected to switch 3 (exterior lights)

  next_state = red;
}

//turns on the red led if the dip switch is enabled
void go_red() {
  if (digitalRead(RED_LIGHTS_SWITCH_PIN) == HIGH) {
      digitalWrite(RED_LIGHTS_PIN, HIGH);
    } else {
      digitalWrite(RED_LIGHTS_PIN, LOW);
    }
    digitalWrite(YELLOW_LIGHTS_PIN, LOW);
    digitalWrite(GREEN_LIGHTS_PIN, LOW);
}

//turns on the red and yellow led if the respective dip switch is enabled
void go_redamber() {
  if (digitalRead(RED_LIGHTS_SWITCH_PIN) == HIGH) {
      digitalWrite(RED_LIGHTS_PIN, HIGH);
    } else {
      digitalWrite(RED_LIGHTS_PIN, LOW);
    }
    if (digitalRead(YELLOW_LIGHTS_SWITCH_PIN) == HIGH) {
      digitalWrite(YELLOW_LIGHTS_PIN, HIGH);
    } else {
      digitalWrite(YELLOW_LIGHTS_PIN, LOW);
    }
    digitalWrite(GREEN_LIGHTS_PIN, LOW);
}

//turns on the green led if the dip switch is enabled
void go_green() {
      if (digitalRead(GREEN_LIGHTS_SWITCH_PIN) == HIGH) {
      digitalWrite(GREEN_LIGHTS_PIN, HIGH);
    } else {
      digitalWrite(GREEN_LIGHTS_PIN, LOW);
    }
    digitalWrite(RED_LIGHTS_PIN, LOW);
    digitalWrite(YELLOW_LIGHTS_PIN, LOW);
}

//turns on the yellow led if the dip switch is enabled
void go_amber() {
    if (digitalRead(YELLOW_LIGHTS_SWITCH_PIN) == HIGH) {
      digitalWrite(YELLOW_LIGHTS_PIN, HIGH);
    } else {
      digitalWrite(YELLOW_LIGHTS_PIN, LOW);
    }
    digitalWrite(RED_LIGHTS_PIN, LOW);
    digitalWrite(GREEN_LIGHTS_PIN, LOW);
}

// Cycles through the given states, and applies next state in the sequence
void loop() {
  switch(next_state) {
    case red:       go_red();       delay(5000);  next_state = redamber;
    case redamber:  go_redamber();  delay(1500);  next_state = green;
    case green:     go_green();     delay(4000);  next_state = amber;
    case amber:     go_amber();     delay(1000);  next_state = red;
  }
}