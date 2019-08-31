#include <Arduino.h>
#include "globals.h"
#include "adafruit_16_MHz.h"
#include "rgb.h"
#include "physics.h"


ISR(TIMER1_COMPA_vect){
    
  rgb_flag = 1;    
}



void init_timer_1_interrupt(void){

    TCCR1A = 0;
    TCCR1B = 0;     // Arduino or something is setting this register, because it is 0 on reset, but if this line is missing the timer does not work
                    // as intended

    TCCR1B = TCCR1B | ((1<<CS12) | (1<<CS10) | (1<< WGM12));    // cs12 and cs10 set prescaler to 1024. If this is changed, re-calculate dt in physics.cpp
                                                                // time for one interrupt is 42 * 1024 / 16e6 = 0.002688 seconds or about 372 hz
                                                                //
                                                                // each rgb led takes about 30 usec so, 36 would be about 1.08 msec or 926 hz max speed 

    OCR1A = 42;  // If this is changed, re-calculate dt in physics.cpp

    TIMSK1 = TIMSK1 | (1<<OCIE1A);

    TCNT1 = 0;
}



void setup(){

    noInterrupts();
  
    pinMode(adaRGBPin,OUTPUT);  

    init_timer_1_interrupt();

    interrupts(); 
}




void loop(){

    if (rgb_flag == 1){

        rgb_flag = 0;

        motion();

        load_rgb();

        adafruit();
    }
}
