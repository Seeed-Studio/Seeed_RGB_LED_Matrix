/*
    rgb_display_animation.ino
    Driver for RGB LED Matrix

    Copyright (c) 2018 Seeed Technology Co., Ltd.
    Website    : www.seeed.cc
    Author     : downey
    Create Time: sep. 2018
    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "grove_two_rgb_led_matrix.h"

#ifdef SEEED_XIAO_M0
    #define SERIAL Serial
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE)
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif


#define DISPLAY_COLOR    0X11


GroveTwoRGBLedMatrixClass matrix;
void setup() {
    Wire.begin();
    SERIAL.begin(115200);
    delay(1000);
    matrix.scanGroveTwoRGBLedMatrixI2CAddress();
    uint32_t version = 0;
    version = matrix.getTestVersion();
    SERIAL.print("version = ");
    SERIAL.println(version, HEX);
    SERIAL.println("Matrix init success!!!");

}

uint64_t pic[1] = {0x2345654354345676};

uint8_t pic8[] = {0x25, 0x35, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                  0x55, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
                  0x55, 0x55, 0x25, 0x55, 0x55, 0x55, 0x55, 0x55,
                  0x55, 0x55, 0x55, 0x25, 0x55, 0x55, 0x55, 0x55,
                  0x55, 0x55, 0x95, 0x55, 0x25, 0x55, 0x55, 0x55,
                  0x55, 0x55, 0x55, 0x55, 0x55, 0x25, 0x55, 0x55,
                  0x55, 0x55, 0x75, 0x55, 0x55, 0x55, 0x25, 0x55,
                  0x55, 0x55, 0x55, 0x55, 0x35, 0x55, 0x55, 0x55,
                 };
void loop() {
    matrix.displayFrames(pic8, 2000, true, 1);
    delay(5000);
}