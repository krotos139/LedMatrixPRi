#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"


struct night_pixel {
	bool en;
	int x;
	int y;
	int r;
	int g;
	int b;
};

struct night_pixel pixels[32];

void effect_night_start() {
	uint32_t led_color =0;
	for (int i=0 ; i<32 ; i++) {
		pixels[i].en = false;
	}

	led_clear();
	led_color = rgb(0, 0, 1);
	for (int y = 0 ; y < LED_Y; y++) {
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, y, led_color);
		}
	}
	led_show();
	usleep(5000);
}

void effect_night_process() {
	uint32_t led_color = rgb(0, 0, 1);
	for (int y = 0 ; y < LED_Y; y++) {
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, y, led_color);
		}
	}
	for (int i=0 ; i<32 ; i++) {
		if (pixels[i].en) {
			led_set_pixel_rgb(pixels[i].x, pixels[i].y, pixels[i].r, pixels[i].g, pixels[i].b);
		}
	}
	led_show();
	for (int i=0 ; i<32 ; i++) {
		if (pixels[i].en) {
			pixels[i].r -= (pixels[i].r - 0) *0.1;
			pixels[i].g -= (pixels[i].g - 0) *0.1;
			pixels[i].b -= (pixels[i].b - 1) *0.1;
			if ((pixels[i].r < 1) && (pixels[i].g < 1) && (pixels[i].b < 3) ) {
				pixels[i].en = false;
				//printf("PIXEL REMOVE %d %d\n", pixels[i].x, pixels[i].y);
			}

		} else {
		    if (rand() % 100 < 10) {
			pixels[i].en = true;
			pixels[i].x = rand() % LED_X;
			pixels[i].y = rand() % LED_Y;
			if (rand() % 2) {
				pixels[i].r = 64;
			} else {
				pixels[i].r = 0;
			}
			if (rand() % 2) {
				pixels[i].g = 64;
			} else {
				pixels[i].g = 0;
			}
			if (rand() % 2) {
				pixels[i].b = 64;
			} else {
				pixels[i].b = 1;
			}
			//printf("PIXEL ADD %d %d (%d, %d, %d)\n", pixels[i].x, pixels[i].y, pixels[i].r, pixels[i].g, pixels[i].b );

		    }
		}
	}

	usleep(50000);
}

void effect_night_end() {
	led_clear();
}
