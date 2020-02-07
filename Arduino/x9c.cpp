#include "x9c.h"

x9c::x9c(uint8_t inc, uint8_t cs, uint8_t ud) : inc(inc), cs(cs), ud(ud)
{
    pinMode(inc, OUTPUT);
    pinMode(cs, OUTPUT);
    pinMode(ud, OUTPUT);
    
    // Since we cannot predict which tap point is used at initialization, 
    // we must assume the highest possible tap point (100) and move the
    //  wiper down by 100 positions!
    wiper_pos = 100;
    set(0);
}

void x9c::set(uint8_t pos)
{
    if (pos == wiper_pos)
    {
        return;
    }

    if (pos > 100)
    {
        pos = 100; // Pot only has 100 tap points!
    }

    digitalWrite(cs, LOW);
    digitalWrite(inc, HIGH);

    bool ud_state = (pos > wiper_pos); // Move wiper up if current wiper_pos < pos, otherwise move the wiper down!
    uint8_t n_pulses;

    if (ud_state)
    {
        n_pulses = pos - wiper_pos;
    }
    else
    {
        n_pulses = wiper_pos - pos;
    }

    digitalWrite(ud, ud_state);

    // Move wiper
    for (uint8_t i = 0; i < n_pulses; i++)
    {
        digitalWrite(inc, LOW);
        digitalWrite(inc, HIGH);
    }

    // Save/Apply wiper position to mem
    digitalWrite(cs, HIGH);
    delay(20);

    wiper_pos = pos;  
}

void x9c::increment(bool up, uint8_t n)
{
    if (n > 100)
    {
        n = 100;
    }

    if (up || (wiper_pos - n >= 0)) // Prevent underflow when incrementing wiper down
    {
        set(wiper_pos + (up ? n : -n));
    }
}

uint8_t x9c::get_wiper_pos()
{
    return wiper_pos;
}