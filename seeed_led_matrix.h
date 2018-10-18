/*
 * seeed_led_matrix.h
 * Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
 *  
 * Copyright (c) 2018 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: sep. 2018
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#ifndef _SEEED_LED_MATRIX_H
#define _SEEED_LED_MATRIX_H

#include <Arduino.h>
#include <Wire.h>


/*#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif
*/

#define VERSION_LEN             5

#define DISPLAY_CUSTOM          0x00

#define DISPLAY_LED_BAR         0x01
#define DISPLAY_NUMBER          0x02
#define DISPALY_STRING          0x03
#define DISPLAY_COLOR_BLOCK     0x04
#define DISPLAY_ASCII           0X05
#define DISPLAY_RAINBOW         0x06
#define DISPLAY_EMOJI           0x07
#define DISPLAY_COLOR_WAVE      0x08
#define DISPLAY_SET_OFFSET      0x09
#define DISPLAY_CLEAN           0x0a

#define READ_VERSION            0xfe


#define RGB_MATRIX_DEFAULT_IIC_ADDR   0x65

typedef enum
{
	DISP_ONCE=0,
	DISP_FOREVER,
}ForeverFlag;



class SeeedLedMatrix
{
    public:
        SeeedLedMatrix(uint8_t default_iic_addr=RGB_MATRIX_DEFAULT_IIC_ADDR);
        ~SeeedLedMatrix(){};
        int readVersion(uint8_t *version);
        void begin();
        void dispCustomPicture(uint8_t *matrix,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
        void displayColorWave(uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
        void displayOff();
        void setDisplayOffset(uint8_t offset_x,uint8_t offset_y);
        void displayEmoji(uint8_t index,uint16_t disp_time,ForeverFlag flag);
        void display_rainbow(uint16_t disp_time,ForeverFlag flag);
        void displayColorBlock(uint32_t block_color,uint16_t disp_time,ForeverFlag flag);
        void displayAscii(char byte,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
        void displayLedBars(uint8_t index,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
        void displayNumber(uint16_t disp_number,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
        void displayString(char *disp_str,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color);
    private:
        uint8_t iic_addr_;
        int iicReadByte(uint8_t reg,uint8_t &byte);
        int i2cWriteReg(uint8_t reg);
        int i2cWriteByte(uint8_t reg,uint8_t byte);
        int i2cWriteBytes(uint8_t reg,uint8_t* data,uint32_t data_len);
        int iicReadBytes(uint8_t reg,uint8_t *bytes,uint8_t len);
};



#endif