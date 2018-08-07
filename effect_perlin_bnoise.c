#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "led_tasks.h"
#include "perlin.h"

int bz=0;

hsv_c color_hsv;
rgb_c color_rgb;

void effect_perlinnoiseb_start() {
	color_hsv.s = 1.0f;
	color_hsv.v = 1.0f;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			led_set_pixel_rgb(x, y, 
					0, 
					0, 
					pnoise3d(y * 0.2, x * 0.2, bz * 0.1, 0.7, 5, 10234)*51);
            	}
	}
	led_show();

}

void effect_perlinnoiseb_process() {
	usleep(1000);
	bz += 1;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			led_set_pixel_rgb(x, y, 
					0, 
					0, 
					pnoise3d(y * 0.2, x * 0.2, bz * 0.1, 0.7, 5, 10234)*51);
            	}
	}
	led_show();

}


void effect_perlinnoiseb_end() {
	usleep(10000);
	led_clear();
}
