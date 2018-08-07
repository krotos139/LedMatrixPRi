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


