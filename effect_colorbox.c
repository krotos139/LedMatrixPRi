#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"


struct color_box {
	int r;
	int g;
	int b;
};

struct color_box box[14][6];

void effect_colorbox_start() {
	uint32_t led_color =0;
	for (int x=0 ; x<14 ; x++) {
		for (int y=0 ; y<6 ; y++) {
			box[x][y].r = 0;
			box[x][y].g = 0;
			box[x][y].b = 0;
		}
	}

	led_clear();
	usleep(5000);
}

void effect_colorbox_process() {
	uint32_t led_color = rgb(0, 0, 0);
	for (int y = 0 ; y < LED_Y; y++) {
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, y, led_color);
		}
	}
	for (int x=0 ; x<14 ; x++) {
		for (int y=0 ; y<6 ; y++) {
			for (int xi = 0 ; xi<4 ; xi++) {
				for (int yi = 0 ; yi<4 ; yi++) {
					led_set_pixel_rgb(x*4+xi, y*4+yi, box[x][y].r, box[x][y].g, box[x][y].b);
				}
			}
		}
	}	
	led_show();
	for (int x=0 ; x<14 ; x++) {
		for (int y=0 ; y<6 ; y++) {
			box[x][y].r -= (box[x][y].r - 0) *0.1;
			box[x][y].g -= (box[x][y].g - 0) *0.1;
			box[x][y].b -= (box[x][y].b - 0) *0.1;
			if ((box[x][y].r<2) && (box[x][y].g<2) && (box[x][y].b<2) ) {
				if (rand() % 100 < 10) {
					if (rand() % 2) {
						box[x][y].r = 255;
					} else {
						box[x][y].r = 0;
					}
					if (rand() % 2) {
						box[x][y].g = 255;
					} else {
						box[x][y].g = 0;
					}
					if (rand() % 2) {
						box[x][y].b = 255;
					} else {
						box[x][y].b = 0;
					}
		    		}
			}
		}
	}
	usleep(50000);
}

void effect_colorbox_end() {
	led_clear();
}
