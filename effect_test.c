#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "led_tasks.h"

void effect_test_start() {
	led_clear();
	led_show();
}

void effect_test_process() {
	uint32_t led_color = 0; 

	uint32_t* ledbuf;
	
	led_color = rgb(255, 0, 0);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(255, 255, 0);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(0, 255, 0);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(0, 255, 255);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(0, 0, 255);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(255, 0, 255);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(255, 255, 255);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(128, 128, 128);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(64, 64, 64);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(16, 16, 16);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(1, 1, 1);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(0, 0, 0);
	ledbuf = led_get_buf(0, 0);
	for (int i=0; i<LED_LENGTH*3; i++)
		ledbuf[i] = led_color;
	led_show();
	usleep(1000000);

	led_color = rgb(255, 0, 0);
	for (int y = 0 ; y < LED_Y; y++) {
		for (int x = 0 ; x < LED_X; x++) {
			led_set_pixel_color(x, y, led_color);
		}
		led_show();
		memset(ledbuf, 0, LED_LENGTH*3*4);
		usleep(50000);
	}
	
	led_color = rgb(0, 255, 0);
	for (int x = 0 ; x < LED_X; x++) {
		for (int y = 0 ; y < LED_Y; y++) {
			led_set_pixel_color(x, y, led_color);
		}
		led_show();
		memset(ledbuf, 0, LED_LENGTH*3*4);
		usleep(50000);
	}
	
	
}

void effect_test_end() {
	led_clear();
	led_show();
}

