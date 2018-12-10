/**
 * RemoteControl.cpp - Library to read commands from remote control
 * Created by David Murillo, Sep 2, 2018
 * Released into the public domain.
 */
#include "Arduino.h"
#include "IRremote.h"
#include "RemoteControl.h"

RemoteControl::RemoteControl() {
  _irrecv.enableIRIn();
}

unsigned long RemoteControl::readButton() {
  if (_irrecv.decode(&_results)) {
  	unsigned long val = _results.value;
  	_irrecv.resume();
  	return val;
  } else {
  	return NOTHING;
  }

  
}