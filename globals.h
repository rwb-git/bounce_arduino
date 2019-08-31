
#include <Arduino.h>

#define adaRGBPin 2

#define led_cnt 24  // number of leds in your strip. max value 255

extern uint8_t rgb_flag, color, led_index;

extern uint8_t *pixels;

extern uint8_t pix_data[];

extern float y;