Grove RGB LED Matrix 
==============


Introduction of LED matrix.
----------------------------  
This is the driver for Gvove 8X8 RGB LED matrix.
There are several examples for RGB LED matrix.  
Including build-in examples:

    rgb_display_emoji
    rgb_display_animation
    rgb_display_block
    rgb_display_clockwise
    rgb_display_color_bar
    rgb_display_color_wave
    rgb_display_ledbars
    rgb_display_num
    rgb_display_string
    rgb_user_custom
NOTICE:if you use rgb_user_custom example on avr board(seeeduino,arduino UNO,arduino 2560..),please modify the corresponding board's Wire library:
libraries\Wire.h:

    replace:
    #define BUFFER_LENGTH 32
    with:
    #define BUFFER_LENGTH 128
libraries\Wire\utility\twi.h:

    replace:
    #define TWI_BUFFER_LENGTH 32
    with:
    #define TWI_BUFFER_LENGTH 128
The official board(like UNO) Wire library located in $ARDUINO_INSTALL_DIR\Arduino\hardware\arduino\avr\libraries\Wire.  
Other third party board(like seeeduino) Wire library located in C:\Users\$USER_NAME\AppData\Local\Arduino15\packages\Seeeduino\hardware\Seeeduino_AVR\1.1.0\libraries\Wire.  

Please refer to APIs of **grove_two_rgb_led_matrix.h** to get more detail.

***
This software is written by downey  for seeed studio<br>
Email:dao.huang@seeed.cc
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>
