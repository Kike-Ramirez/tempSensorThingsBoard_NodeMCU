
/*
    MIT License
    Copyright (c) 2018, Enrique Ramírez
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "ssd1306.h"
#include <BounceEase.h>

uint32_t lastMillis;
uint8_t  hours = 10;
uint8_t  minutes = 35;
uint8_t  seconds = 0;

double yPos = 0;
double t = 0;
double xPos = 0;

BounceEase ease;

void printTemperature()
{
    char minutesStr[6] = "25 C";
    ssd1306_printFixedN(xPos,yPos, minutesStr, STYLE_NORMAL, FONT_SIZE_4X);
}

void setup() {
    /* Replace the line below with ssd1306_128x32_i2c_init() if you need to use 128x32 display */
    ssd1306_128x32_i2c_init();
    ssd1306_fillScreen(0x00);
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    lastMillis = millis();
    ease.setDuration(2);
    ease.setTotalChangeInPosition(32);
}

void loop()
{

    t = 0.001 * millis();
    // ssd1306_fillScreen(0x00);

    // yPos=ease.easeIn(t);
    printTemperature();

    if ((uint32_t)(millis() - lastMillis) >= 3000)
    {
        lastMillis = 0;
        
    }
    delay(100);
}




