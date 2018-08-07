#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"

void effect_off_start() {
	usleep(2000);
	led_clear();
//	led_show();
}

void effect_off_process() {
	usleep(5000);
}

void effect_off_end() {
	usleep(2000);
	led_clear();
}

