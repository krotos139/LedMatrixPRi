#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"

void effect_mainboxlight_start() {
	uint32_t led_color =0;
	
	led_clear();
	for (int l = 0 ; l < 256; l+=2) {
		led_color = rgb(l, l, l);
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, 0, led_color);
			led_set_pixel_color(x, 1, led_color);
			led_set_pixel_color(x, LED_Y-1, led_color);
			led_set_pixel_color(x, LED_Y-2, led_color);

		}
		for (int y = 0 ; y < LED_Y; y++) {
			led_set_pixel_color(0, y, led_color);
			led_set_pixel_color(1, y, led_color);
			led_set_pixel_color(LED_X-1, y, led_color);
			led_set_pixel_color(LED_X-2, y, led_color);
		}

		led_show();
		usleep(2000);
	}
}

void effect_mainboxlight_process() {
	usleep(10000);
}

void effect_mainboxlight_end() {
	uint32_t led_color = 0; 
	
	for (int l = 255 ; l >=0; l-=2) {
		led_color = rgb(l, l, l);
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, 0, led_color);
			led_set_pixel_color(x, 1, led_color);
			led_set_pixel_color(x, LED_Y-1, led_color);
			led_set_pixel_color(x, LED_Y-2, led_color);

		}
		for (int y = 0 ; y < LED_Y; y++) {
			led_set_pixel_color(0, y, led_color);
			led_set_pixel_color(1, y, led_color);
			led_set_pixel_color(LED_X-1, y, led_color);
			led_set_pixel_color(LED_X-2, y, led_color);
		}
		led_show();
		usleep(2000);
	}
	usleep(10000);
	led_clear();
}
