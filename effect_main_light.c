#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"

void effect_mainlight_start() {
	uint32_t led_color =0;
	
	led_clear();
	for (int l = 0 ; l < 256; l+=1) {
		led_color = rgb(l, l, l);
		for (int y = 0 ; y < 8; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		led_show();
		usleep(10000);
	}
}

void effect_mainlight_process() {
	usleep(10000);
}

void effect_mainlight_end() {
	uint32_t led_color = 0; 
	
	for (int l = 255 ; l >=0; l-=2) {
		led_color = rgb(l, l, l);
		for (int y = 0 ; y < 8; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 0 ; y < 8; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 0 ; x < 8; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 24 ; x < 32; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		for (int y = 16 ; y < 24; y++) {
			for (int x = 48 ; x < 56; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		led_show();
		usleep(10000);
	}
	usleep(10000);
	led_clear();
	led_show();
}
