/*
 * seeed_led_matrix.cpp
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

#include "seeed_led_matrix.h"


SeeedLedMatrix::SeeedLedMatrix(uint8_t default_iic_addr = RGB_MATRIX_DEFAULT_IIC_ADDR)
{
    iic_addr_=default_iic_addr;
}

int SeeedLedMatrix::readVersion(uint8_t *version)
{
    return iicReadBytes(READ_VERSION,version,VERSION_LEN);
}


void SeeedLedMatrix::begin()
{
    Wire.begin();
}

/**Display custom picture.
 * @param  matrix   8X8 matrix，map to 8X8 LED matrix,one bit corresponding to one LED,0 is off,1 is on.   
 * @param  disp_time  Totol display time,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::dispCustomPicture(uint8_t *matrix,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	int ret=0;
	uint8_t send_buf[20]={0};
	send_buf[0]=disp_time;
	send_buf[1]=disp_time>>8;
	send_buf[2]=flag;
	send_buf[3]=disp_color;
	for(int i=0;i<8;i++)
	{
		send_buf[4+i]=matrix[i];
	}
	ret=i2cWriteBytes(DISPLAY_CUSTOM,&send_buf[0],8+4);
	Serial.println(ret);
}


/**Display color wave. 
 * @param  disp_time  Display time for one loop,unit ms.
 * @param  flag       Display forever or just display for once.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::displayColorWave(uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	uint8_t send_buf[10]={0};
	send_buf[0]=disp_time;
	send_buf[1]=disp_time>>8;
	send_buf[2]=flag;
	send_buf[3]=disp_color;
	i2cWriteBytes(DISPLAY_COLOR_WAVE,send_buf,4);
}

void SeeedLedMatrix::setDisplayOffset(uint8_t offset_x,uint8_t offset_y)
{
	uint8_t send_buf[10]={0};
	send_buf[0]=offset_x;
	send_buf[1]=offset_y;
	i2cWriteBytes(DISPLAY_SET_OFFSET,send_buf,2);

}

void SeeedLedMatrix::displayOff()
{
	i2cWriteReg(DISPLAY_CLEAN);
}


void SeeedLedMatrix::displayEmoji(uint8_t index,uint16_t disp_time,ForeverFlag flag)
{
	uint8_t send_buf[10]={0};
	send_buf[0]=index;
	send_buf[1]=disp_time;
	send_buf[2]=disp_time>>8;
	send_buf[3]=flag;
	i2cWriteBytes(DISPLAY_EMOJI,send_buf,4);
}

/**Display rainbow.
 * @param  disp_time  Totol display time,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 **/
void SeeedLedMatrix::display_rainbow(uint16_t disp_time,ForeverFlag flag)
{
	uint8_t send_buf[10]={0};
	send_buf[0]=disp_time;
	send_buf[1]=disp_time>>8;
	send_buf[2]=flag;
	i2cWriteBytes(DISPLAY_RAINBOW,send_buf,3);
}

/**Display color block.
 * @param  block_color   Display color for all LEDs.
 * @param  disp_time  Totol display time,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 **/
void SeeedLedMatrix::displayColorBlock(uint32_t block_color,uint16_t disp_time,ForeverFlag flag)
{
	uint8_t send_buf[10]={0};
	send_buf[0]=block_color>>16;
	send_buf[1]=block_color>>8;
	send_buf[2]=block_color;
	send_buf[3]=disp_time;
	send_buf[4]=disp_time>>8;
	send_buf[5]=flag;
	i2cWriteBytes(DISPLAY_COLOR_BLOCK,send_buf,6);
}

/**Display ascii.
 * @param  byte   The byte to be displayed.  
 * @param  disp_time  Totol display time,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::displayAscii(char byte,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	int ret;
	uint8_t send_buf[50]={0};
	send_buf[0]=byte;
	send_buf[1]=disp_time;
	send_buf[2]=disp_time>>8;
	send_buf[3]=flag;
	send_buf[4]=disp_color;
	ret=i2cWriteBytes(DISPLAY_ASCII,send_buf,5);
	Serial.println(ret);
}

/**Display ascii.
 * @param  index   Index of bars array,there are 32 pictures total. 
 * @param  disp_time  Totol display time,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::displayLedBars(uint8_t index,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	int ret;
	uint8_t send_buf[50]={0};
	send_buf[0]=index;
	send_buf[1]=disp_time;
	send_buf[2]=disp_time>>8;
	send_buf[3]=flag;
	send_buf[4]=disp_color;
	ret=i2cWriteBytes(DISPLAY_LED_BAR,send_buf,5);
	Serial.println(ret);
}

/**Display ascii.
 * @param  disp_number   The number to be displayed.range:0-65535.
 * @param  disp_time  Display time for one loop,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::displayNumber(uint16_t disp_number,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	int ret;
	uint8_t send_buf[10]={0};
	send_buf[0]=disp_number;
	send_buf[1]=disp_number>>8;
	send_buf[2]=disp_time;
	send_buf[3]=disp_time>>8;
	send_buf[4]=flag;
	send_buf[5]=disp_color;
	ret=i2cWriteBytes(DISPLAY_NUMBER,send_buf,6);
	Serial.println(ret);
}


/**Display string.
 * @param  disp_str   The string to be displayed.range:0-65535.
 * @param  disp_time  Display time for one loop,unit ms.
 * @param  flag       Display forever or just display for once,if once,displaying time depends on second param disp_time.
 * @param  disp_color  Display color,0-255 map to color rgb.
 **/
void SeeedLedMatrix::displayString(char *disp_str,uint16_t disp_time,ForeverFlag flag,uint8_t disp_color)
{
	uint8_t send_buf[10]={0};
	uint8_t len=strlen(disp_str);
	send_buf[0]=flag;
	send_buf[1]=disp_time;
	send_buf[2]=disp_time>>8;
	send_buf[3]=len;
	send_buf[4]=disp_color;
	for(int i=0;i<len;i++)
	{
		send_buf[5+i]=disp_str[i];
	}
	i2cWriteBytes(DISPALY_STRING,send_buf,len+5);
}



/***************************************************************************************************/
/************************************IIC communication oprations************************************/
/***************************************************************************************************/
/***************************************************************************************************/
int SeeedLedMatrix::iicReadByte(uint8_t reg,uint8_t &byte)
{
    
    u32 time_out_count=0;
    Wire.beginTransmission(iic_addr_);
	Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(iic_addr_,(u8)1);
    while(1!=Wire.available())
    {
        time_out_count++;
        if(time_out_count>10)  return -1;
        delay(1);
    }
    byte=Wire.read();
    return 0;
}

int SeeedLedMatrix::iicReadBytes(uint8_t reg,uint8_t *bytes,uint8_t len)
{
    u32 time_out_count=0;
    Wire.beginTransmission(iic_addr_);
	Wire.write(reg);
    Wire.endTransmission(false);

    Wire.requestFrom(iic_addr_,len);
    while(len!=Wire.available())
    {
        time_out_count++;
        if(time_out_count>10)  return -1;
        delay(1);
    }
    for(int i=0;i<len;i++)
    {
        bytes[i]=Wire.read();
    }
    return 0;
}

int SeeedLedMatrix::i2cWriteReg(uint8_t reg)
{
    Wire.beginTransmission(iic_addr_);
	Wire.write(reg);
    return Wire.endTransmission();
}


int SeeedLedMatrix::i2cWriteByte(uint8_t reg,uint8_t byte)
{
    Wire.beginTransmission(iic_addr_);
	Wire.write(reg);
	Wire.write(byte);
    return Wire.endTransmission();
}

int SeeedLedMatrix::i2cWriteBytes(uint8_t reg,uint8_t* data,uint32_t data_len)
{
    Wire.beginTransmission(iic_addr_);
	Wire.write(reg);
	for(int i=0;i<data_len;i++)
	{
		Wire.write(data[i]);
	}
	return Wire.endTransmission();
}
