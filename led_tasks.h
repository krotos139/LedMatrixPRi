#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <semaphore.h>

#include "ws2811.h"


#define LED_LENGTH 448
#define LED_X 56
#define LED_Y 24


ws2811_led_t rgb(uint8_t r, uint8_t g, uint8_t b);
void led_set_pixel_color(uint8_t x, uint8_t y,  ws2811_led_t color);
void led_set_pixel_rgb(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);
void led_get_pixel_color(uint8_t x, uint8_t y, ws2811_led_t *color);
void led_show();
void led_clear();
ws2811_led_t* led_get_buf(uint8_t x, uint8_t y);

short ledMatrixMap(int px, int py);

void switchScene(int scene);
int getScene();

void effect_test_start();
void effect_test_process();
void effect_test_end();

void effect_mainlight_start();
void effect_mainlight_process();
void effect_mainlight_end();

void effect_off_start();
void effect_off_process();
void effect_off_end();

void effect_perlinnoise_start();
void effect_perlinnoise_process();
void effect_perlinnoise_end();

void effect_perlinnoisergb_start();
void effect_perlinnoisergb_process();
void effect_perlinnoisergb_end();

void effect_perlinnoiseg_start();
void effect_perlinnoiseg_process();
void effect_perlinnoiseg_end();

void effect_perlinnoiseb_start();
void effect_perlinnoiseb_process();
void effect_perlinnoiseb_end();

void effect_alllight_start();
void effect_alllight_process();
void effect_alllight_end();

void effect_night_start();
void effect_night_process();
void effect_night_end();

void effect_colorbox_start();
void effect_colorbox_process();
void effect_colorbox_end();

void effect_mainboxlight_start();
void effect_mainboxlight_process();
void effect_mainboxlight_end();


void artnet_start();
void artnet_process();
void artnet_end();

int init_led();
int deinit_led(); 
uint8_t init_artnet();

//void artnet_task();
uint8_t artnet_init();
void control_task();

void* thread_http_server( void* vptr_args );
void* thread_led( void* vptr_args );
sem_t semaphore;
uint8_t running;

void http_server_stop();

typedef struct {
	double r;       // a fraction between 0 and 1
	double g;       // a fraction between 0 and 1
	double b;       // a fraction between 0 and 1
} rgb_c;

typedef struct {
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
} hsv_c;

hsv_c   rgb2hsv(rgb_c in);
rgb_c   hsv2rgb(hsv_c in);
