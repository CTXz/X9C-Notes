#pragma once

#include <Arduino.h>

class x9c
{
private:
    uint8_t inc;
    uint8_t cs;
    uint8_t ud;

    uint8_t wiper_pos;

public:
    x9c(uint8_t inc, uint8_t cs, uint8_t ud);
    void set(uint8_t pos);              // Sets wiper to any desired tap point between 0 and 100
    void increment(bool up, uint8_t n); // Increments/Moves wiper up or down by n positions
    uint8_t get_wiper_pos();            // Returns current tap point
};