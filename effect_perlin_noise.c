#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "led_tasks.h"
#include "perlin.h"

int z=0;

hsv_c color_hsv;
rgb_c color_rgb;

void effect_perlinnoise_start() {
	color_hsv.s = 1.0f;
	color_hsv.v = 1.0f;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			color_hsv.h = pnoise3d(y * 0.2, x * 0.2, z * 0.1, 0.7, 5, 12124);
			color_rgb = hsv2rgb(color_hsv);
			led_set_pixel_rgb(x, y, color_rgb.r, color_rgb.g, color_rgb.b);
            	}
	}
}

void effect_perlinnoise_process() {
	usleep(1000);
	z += 1;
	for(int x = 0; x < LED_X; x++) {
		for(int y = 0; y < LED_Y; y++) {
			color_hsv.h = pnoise3d(y * 0.2, x * 0.2, z * 0.1, 0.7, 5, 12124)*72;
			color_rgb = hsv2rgb(color_hsv);
			led_set_pixel_rgb(x, y, color_rgb.r*255, color_rgb.g*255, color_rgb.b*255);
			//led_set_pixel_rgb(x, y, 0, pnoise3d(y * 0.2, x * 0.2, z * 0.1, 0.7, 5, 12124)*51, 0);
            	}
	}
	led_show();

}


void effect_perlinnoise_end() {
	usleep(10000);
	led_clear();
}
