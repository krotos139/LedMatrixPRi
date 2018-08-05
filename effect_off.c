#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"

void effect_off_start() {
	usleep(200000);
	led_clear();
	led_show();
}

void effect_off_process() {
	usleep(200000);
}

void effect_off_end() {
	led_clear();
	led_show();
}

