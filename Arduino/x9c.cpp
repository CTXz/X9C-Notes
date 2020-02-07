/*
 * Copyright (c) 2020 Patrick Pedersen <ctx.xda@gmail.com>

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "x9c.h"

x9c::x9c(uint8_t inc, uint8_t cs, uint8_t ud) : inc(inc), cs(cs), ud(ud)
{
    pinMode(inc, OUTPUT);
    pinMode(cs, OUTPUT);
    pinMode(ud, OUTPUT);
    
    // Since we cannot predict which tap point is used at initialization, 
    // we must assume the highest possible tap point (99) and move the
    //  wiper down by 99 positions!
    wiper_pos = 99;
    set(0);
}

void x9c::set(uint8_t pos)
{
    if (pos == wiper_pos)
    {
        return;
    }

    if (pos > 99)
    {
        pos = 99; // Pot only has 100 tap points!
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

    // 2.9 us delay negligible

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
    if (n > 99)
    {
        n = 99;
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