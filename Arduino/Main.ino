#include <Arduino.h>
#include "x9c.h"

void setup()
{
}

void loop()
{
  x9c x9c102(3, 4, 2);

  while(true)
  {
    // Sweep wiper up
    for (uint8_t i = 0; i < 100; i++) {
      x9c102.increment(true, 1);
      delay(50);
    }

    // Set wiper back to its lowest position
    x9c102.set(0);
    delay(50);    
  }
}