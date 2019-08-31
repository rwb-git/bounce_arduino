
#include "globals.h"

uint8_t   pix_data[led_cnt * 3];

uint8_t   *pixels = pix_data;    // pointer to the data that the adafruit code sends to the LEDs

uint8_t rgb_flag = 0;

uint8_t color = 0;

uint8_t led_index = 0;

float y = 1.0;
          