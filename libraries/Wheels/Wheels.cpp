/**
 * Wheels.cpp - Library for controlling car's wheels
 * Created by David Murillo, Sep 1, 2018
 * Released into the public domain.
 */

#include "Arduino.h"
#include "Wheels.h"

Wheels::Wheels() {
  pinMode(_IN1, OUTPUT);
  pinMode(_IN2, OUTPUT);
  pinMode(_IN3, OUTPUT);
  pinMode(_IN4, OUTPUT);
  pinMode(_ENA, OUTPUT);
  pinMode(_ENB, OUTPUT);
}

void Wheels::forward() { 
  digitalWrite(_ENA, HIGH); //enable L298n A channel
  digitalWrite(_ENB, HIGH); //enable L298n B channel
  digitalWrite(_IN1, HIGH); //set IN1 hight level
  digitalWrite(_IN2, LOW);  //set IN2 low level
  digitalWrite(_IN3, LOW);  //set IN3 low level
  digitalWrite(_IN4, HIGH); //set IN4 hight level
}

void Wheels::back() {
  digitalWrite(_ENA, HIGH);
  digitalWrite(_ENB, HIGH);
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
}

void Wheels::left() {
  digitalWrite(_ENA, HIGH);
  digitalWrite(_ENB, HIGH);
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
  digitalWrite(_IN3, LOW);
  digitalWrite(_IN4, HIGH); 
}

void Wheels::right() {
  digitalWrite(_ENA, HIGH);
  digitalWrite(_ENB, HIGH);
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  digitalWrite(_IN3, HIGH);
  digitalWrite(_IN4, LOW);
}
