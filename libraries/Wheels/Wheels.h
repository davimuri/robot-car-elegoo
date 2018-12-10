/**
 * Car.h - Library for controlling car movement
 * Created by David Murillo, Sep 1, 2018
 * Released into the public domain.
 */
#ifndef Wheels_h
#define Wheels_h

#include "Arduino.h"

class Wheels {

  public:
    Wheels();
    void forward();
    void back();
    void left();
    void right();
    
  private:
    //define L298n module IO Pin
    const int _ENA = 5;
    const int _ENB = 6;
    const int _IN1 = 7;
    const int _IN2 = 8;
    const int _IN3 = 9;
    const int _IN4 = 11;
};

#endif
