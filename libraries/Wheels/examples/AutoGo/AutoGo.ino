#include <Wheels.h>

Wheels wheels;

void setup() {
}

void loop() {
  wheels.forward();
  delay(1000); // delay 1000 ms
  wheels.back();
  delay(1000);
  wheels.left();    
  delay(1000);
  wheels.right();
  delay(1000);
}
