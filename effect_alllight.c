#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"


struct alllight_pixel {
	bool en;
	int x;
	int y;
	int r;
	int g;
	int b;
};

struct alllight_pixel pixels[32];

void effect_alllight_start() {
	uint32_t led_color =0;
	for (int i=0 ; i<32 ; i++) {
		pixels[i].en = false;
	}

	led_clear();
	for (int l = 0 ; l < 127; l+=1) {
		led_color = rgb(l, l, l);
		for (int y = 0 ; y < LED_Y; y++) {
			for (int x = 0 ; x < LED_X; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		led_show();
		usleep(5000);
	}
}

void effect_alllight_process() {
	uint32_t led_color = rgb(127, 127, 127);
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
			pixels[i].r -= (pixels[i].r - 127) *0.1;
			pixels[i].g -= (pixels[i].g - 127) *0.1;
			pixels[i].b -= (pixels[i].b - 127) *0.1;
			if ((pixels[i].r < 129) && (pixels[i].g < 129) && (pixels[i].b < 129) )
				pixels[i].en = false;

		} else {
		    if (rand() % 100 < 10) {
			pixels[i].en = true;
			pixels[i].x = rand() % LED_X;
			pixels[i].y = rand() % LED_Y;
			if (rand() % 2) {
				pixels[i].r = 255;
			} else {
				pixels[i].r = 127;
			}
			if (rand() % 2) {
				pixels[i].g = 255;
			} else {
				pixels[i].g = 127;
			}
			if (rand() % 2) {
				pixels[i].b = 255;
			} else {
				pixels[i].b = 127;
			}

		    }
		}
	}

	usleep(10000);
}

void effect_alllight_end() {
	uint32_t led_color;
	for (int l = 127 ; l >=0; l-=1) {
		led_color = rgb(l, l, l);
		for (int y = 0 ; y < LED_Y; y++) {
			for (int x = 0 ; x < LED_X; x++) {
				led_set_pixel_color(x, y, led_color);
			}
		}
		led_show();
		usleep(1000);
	}

	usleep(10000);
	led_clear();
}
