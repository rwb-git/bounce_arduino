#include "globals.h"
#include "rgb.h"

float dt = 0.002688; //  the time for one timer interrupt which is 0.002688 seconds using compare 42 and 1024 prescale on 16 MHz clock

float time = 0.0;

float velocity = 0.0;

float v0 = 0.0;

float string_length = 1.667; // (feet)      led_cnt * feet_per_led; // 1.667;  // 24 leds * 0.833 / 12 (feet)

float feet_per_led = string_length /led_cnt;

float inches_per_led = feet_per_led / 12.0;

float y0 = string_length;

float a = 32.17; // (ft /sec&2)

float y_local; // y_local is in actual feet and will be normalized to 1.0 for load_rgb

int first_bounce = 0;

int fb_cnt = 0;

/*   
    a = gravitational acceleration = 32.17 ft/sec^2

    v = a * t + v0

    y = y0 + 1/2 (v + v0) * t

    these equations are ok continuously except for when we hit bottom and bounce, and at that point we reset time to 0 and
    reverse the velocity with some reduction so it does not bounce all the way back. once it has nearly stopped bouncing (low velocity)
    we restart the animation.
*/


void motion(void){  

        if (first_bounce == 1){  // we just bounced but we have to let it rise a little before we resume testing for bounces

            fb_cnt++;

            if (fb_cnt > 20){  // assume it has changed direction and so we can resume detecting bottom hit

                fb_cnt = 0;

                first_bounce = 0;
            }
        }

        if ((y_local< feet_per_led) && (first_bounce ==0)){  // if we are low and the timeout period is over, then bounce or start over if velocity is low

            v0 = -0.9* velocity;  // rebound with reduced velocity so we don't bounce all the way back

            first_bounce = 1;      // set flag to ignore position for a few cycles

            if (abs(v0) < 0.93){  // speed is low so start animation over with led at top

                y0 = string_length;

                v0 = 0;

                clear_fade();

            } else {  // normal bounce

                y0 = 0.0;                    
            }

            y_local = y0;

            time = 0.0;
        }

        time += dt; 

        velocity = -a * time + v0;

        y_local = y0 + 0.5 * (velocity + v0) * time; 
        
        y = y_local / string_length;
}
