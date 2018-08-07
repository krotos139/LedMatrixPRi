#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "led_tasks.h"
#include "perlin.h"

int rgbz=0;

hsv_c color_hsv;
rgb_c color_rgb;

void effect_perlinnoisergb_start() {
	color_hsv.s = 1.0f;
	color_hsv.v = 1.0f;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			led_set_pixel_rgb(x, y, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 11857)*51, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 15673)*51, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 11234)*51);
            	}
	}
	led_show();

}

void effect_perlinnoisergb_process() {
	usleep(1000);
	rgbz += 1;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			led_set_pixel_rgb(x, y, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 11857)*51, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 15673)*51, 
					pnoise3d(y * 0.2, x * 0.2, rgbz * 0.1, 0.7, 5, 11234)*51);
            	}
	}
	led_show();

}


void effect_perlinnoisergb_end() {
	usleep(10000);
	led_clear();
}
