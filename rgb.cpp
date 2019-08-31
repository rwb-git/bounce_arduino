
#include "globals.h"

uint8_t brightness;

int y_led;

#define fade_cnt 12       // this has to be at least 1. to disable fade, delete the call to get_fade(). or you could delete everything in this file that
                          // includes the word "fade" (and do the same to rgb.h). Also delete the call to clear_fade() in physics.cpp.

uint8_t fade[fade_cnt];

uint8_t fade_increment = 200 / fade_cnt;  // first value returned is 200, so for 4, we return 200 150 100 50 for fade_increment = 200/4 = 50

void save_fade(int i){

  // fade array saves last few indexes

  for (int i=fade_cnt -1; i>0; i--){  // shift indexes over by 1 so that the most recent will be in slot 0, and the oldest will be at the other end
                                      // of the array.

    fade[i] = fade[i-1];
  }

  fade[0] = i;

}

void clear_fade(void){

  for (int i=0;i<fade_cnt;i++){

    fade[i] = 255;
  }
}

void save_one(uint8_t val){

  pix_data[led_index] = val;

  led_index++;
}

void store_color(void){

  uint8_t other = brightness >> 3; // instead of pure red, green, blue, add some white

  switch (color){

    case 0:

      save_one(brightness);   // green
      save_one(other);        // red
      save_one(other);        // blue

      break;

    case 1:

      save_one(other);
      save_one(brightness);
      save_one(other);

      break;

    case 2:

      save_one(other);
      save_one(other);
      save_one(brightness);

      break;
  }
}

uint8_t get_fade(int j){  // we save the last few led indexes in fade[], and if this function finds the current index, it will return brightness. while
                          // searching, brightness is reduced for each slot in fade[], so that the first one found is the brightest, and each one found later
                          // has a lower value depending on which slot it is in. brightness has to be calculated for each search, rather than using a global,
                          // because the leds will not be found in order if we are down around the bottom, and the fading leds can be on both sides of the end,
                          // if that makes any sense.

  uint8_t intensity = 200;

  for (int i=0; i<fade_cnt;i++){

    if (fade[i] == j){

      return intensity;
    }

    if (intensity >= fade_increment){
      intensity -= fade_increment;
    } else {
      intensity = 0;
    }
  }

  return 0; 
}

void load_rgb(void){

  // take whatever y is and translate it to the led string

  y_led = (int)(y * led_cnt);

  color = 1;

  led_index = 0;

  for (int i=0; i<led_cnt; i++){

    if (i==y_led){

      brightness = 255;

    } else {

        brightness = get_fade(i);
    }

    store_color();
  }

  save_fade(y_led);
}

