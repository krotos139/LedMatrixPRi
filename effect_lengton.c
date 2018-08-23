#include <stdio.h>
#include <unistd.h>
//#include <ctime.h>
#include "led_tasks.h"


struct lengton {
	int x;
	int y;
	int black;
	int r;
	int g;
	int b;
	int ye;
	int dir;
};

struct lengton ant[6];

void effect_lengton_start() {
	srand ( time(NULL) );
/*	ant[0].x = 26;
	ant[0].y = 12;
	ant[0].black = 0;
	ant[0].r = 1;
	ant[0].g = 1;
	ant[0].b = 0;
	ant[0].ye = 1;
	ant[0].dir = 0;*/
	for (int i=0 ; i<6 ; i++) {
		ant[i].x = rand() % 56;
		ant[i].y = rand() % 24;
		ant[i].black = rand() % 2;
		ant[i].r = rand() % 2;
		ant[i].g = rand() % 2;
		ant[i].b = rand() % 2;
		ant[i].ye = rand() % 2;
		ant[i].dir = rand() % 4;
		//printf("ANT %d (%d, %d)\n", i, ant[i].x, ant[i].y);
	}

	led_clear();
	usleep(5000);
}

void effect_lengton_process() {
	for (int i=0 ; i<6 ; i++) {
		uint32_t color;
		uint32_t next;
		int dir = -1;
		led_get_pixel_color(ant[i].x, ant[i].y, &color);
		if (color == 0x000000) {
			dir = ant[i].black;
			next = 0x7F0000;
		} if (color == 0x7F0000) {
			dir = ant[i].r;
			next = 0x007F00;
		} if (color == 0x007F00) {
			dir = ant[i].g;
			next = 0x00007F;
		} if (color == 0x00007F) {
			dir = ant[i].b;
			next = 0x7F7F00;
		} if (color == 0x7F7F00) {
			dir = ant[i].ye;
			next = 0x000000;
		} 
		led_set_pixel_color(ant[i].x, ant[i].y, next);
		if (dir == 0) dir = -1;
		//printf("A %d (%d, %d) d:%d  ad:%d \n", i, ant[i].x, ant[i].y, dir, ant[i].dir);

		unsigned int sdir = (dir + ant[i].dir) % 4;
		ant[i].dir = sdir;
		if (sdir == 0) {
			ant[i].x = (ant[i].x+1)%56;
		}
		if (sdir == 1) {
			ant[i].y = (ant[i].y+1)%56;
		}
		if (sdir == 2) {
			ant[i].x = (ant[i].x-1)%24;
		}
		if (sdir == 3) {
			ant[i].y = (ant[i].y-1)%24;
		}

	}
	led_show();
	usleep(50000);
}

void effect_lengton_end() {
	led_clear();
}
