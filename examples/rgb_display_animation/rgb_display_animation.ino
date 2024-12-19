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
    uint16_t VID = 0;
    VID = matrix.getDeviceVID();
    if (VID != 0x2886) {
        SERIAL.println("Can not detect led matrix!!!");
        while (1);
    }
    SERIAL.println("Matrix init success!!!");

}

void loop() {
    matrix.displayColorAnimation(0, 5000, true);
    delay(5000);
    matrix.displayColorAnimation(1, 5000, true);
    delay(5000);
    matrix.displayColorAnimation(2, 5000, true);
    delay(5000);
    matrix.displayColorAnimation(3, 5000, true);
    delay(5000);
}