#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "led_tasks.h"

#include "ws2811.h"

#define LED_STRIP_LENGTH 448
#define LED_STRIP_RMT_INTR_NUM 19U

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define DMA                     10
#define STRIP_TYPE            WS2811_STRIP_GRB 

ws2811_t ledstring1 =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = 10,
            .count = LED_STRIP_LENGTH,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
        [1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

ws2811_t ledstring2 =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA+1,
    .channel =
    {
        [0] =
        {
            .gpionum = 18,
            .count = LED_STRIP_LENGTH,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
	[1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

ws2811_t ledstring3 =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA+2,
    .channel =
    {
        [0] =
        {
            .gpionum = 21,
            .count = LED_STRIP_LENGTH,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
	[1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

static ws2811_led_t *matrix;

short ledmapalgo(int x, int y) {
	short led = 0;
	led += x*8;
	if ((x & 1) == 0) {
		led += y;
	} else {
		led += 7-y;
	}
	if (led>447) led = 447; //DEBUG
	return led;
}

short ledMatrixMap(int px, int py) {
	short mat = py*7;
	if (py!=1) {
		mat += px;
	} else {
		mat += 6-px;
		
	}
	return mat;
}

inline ws2811_led_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return  (r<<16) + (g<<8) + (b);
}

void led_set_pixel_color(uint8_t x, uint8_t y, ws2811_led_t color) {
	if (x>=LED_X || y >=LED_Y) return;
	matrix[y*LED_X+x] = color;
}

void led_set_pixel_rgb(uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue) {
	if (x>=LED_X || y >=LED_Y) return;
	matrix[y*LED_X+x] = rgb(red, green, blue);
}

void led_get_pixel_color(uint8_t x, uint8_t y, uint32_t *color) {
	if (x>=LED_X || y >=LED_Y) return;
	*color = matrix[y*LED_X+x]; 
}

ws2811_led_t* led_get_buf(uint8_t x, uint8_t y) {
	return &matrix[y*LED_X+x];
}

void led_show() {
	int i = 0;
	for (int x = 0 ; x<LED_X ; x++) {
		if (x % 2 == 0) {
			for (int y = 0 ; y<8 ; y++) {
				ledstring1.channel[0].leds[i++] = matrix[y*LED_X+x];
			}
		} else {
			for (int y = 7 ; y>=0 ; y--) {
				ledstring1.channel[0].leds[i++] = matrix[y*LED_X+x];
			}

		}
	}
	i=0;
	for (int x = 0 ; x<LED_X ; x++) {
		if (x % 2 == 0) {
			for (int y = 0 ; y<8 ; y++) {
				ledstring2.channel[0].leds[i++] = matrix[(y+8)*LED_X+x];
			}
		} else {
			for (int y = 7 ; y>=0 ; y--) {
				ledstring2.channel[0].leds[i++] = matrix[(y+8)*LED_X+x];
			}

		}
	}
	i=0;
	for (int x = 0 ; x<LED_X ; x++) {
		if (x % 2 == 0) {
			for (int y = 0 ; y<8 ; y++) {
				ledstring3.channel[0].leds[i++] = matrix[(y+16)*LED_X+x];
			}
		} else {
			for (int y = 7 ; y>=0 ; y--) {
				ledstring3.channel[0].leds[i++] = matrix[(y+16)*LED_X+x];
			}

		}
	}
	if (0) {
		printf("DEBUG LED:\n");
		for (int f = 0 ; f<16 ; f++) {
			printf("%X ", ledstring1.channel[0].leds[f]);
		}
		printf("\n");
		for (int f = 0 ; f<16 ; f++) {
			printf("%X ", ledstring2.channel[0].leds[f]);
		}
		printf("\n");
		for (int f = 0 ; f<16 ; f++) {
			printf("%X ", ledstring3.channel[0].leds[f]);
		}
		printf("\n");

	}

}

void led_clear() {
        for (int x = 0; x<LED_X ; x++ ) {
		for (int y = 0; y<LED_Y ; y++) {
			led_set_pixel_rgb(x, y, 0, 0, 0);
		}
    	}
	for (int i = 0 ; i < LED_STRIP_LENGTH ; i++) {
		ledstring1.channel[0].leds[i] = 0;
		ledstring2.channel[0].leds[i] = 0;
		ledstring3.channel[0].leds[i] = 0;
	}

}

void* thread_led( void* vptr_args ) {
   ws2811_return_t	ret;
   if (vptr_args == NULL)
	   ret = 0;
    while (running) {
	if ((ret = ws2811_render(&ledstring1)) != WS2811_SUCCESS) {
		fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
	}
	if ((ret = ws2811_render(&ledstring2)) != WS2811_SUCCESS) {
		fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
	}
	if ((ret = ws2811_render(&ledstring3)) != WS2811_SUCCESS) {
		fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
	}
    	usleep(10000);
    }
    printf("LED: quit\n");
    led_clear();
    if ((ret = ws2811_render(&ledstring1)) != WS2811_SUCCESS) {
	fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
    }
    if ((ret = ws2811_render(&ledstring2)) != WS2811_SUCCESS) {
	fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
    }
    if ((ret = ws2811_render(&ledstring3)) != WS2811_SUCCESS) {
	fprintf(stderr, "ws2811_render 1 failed: %s\n", ws2811_get_return_t_str(ret));
    }

    return NULL;
}

int init_led() {
    ws2811_return_t ret;

    matrix = malloc(sizeof(ws2811_led_t) * LED_X * LED_Y);

    if (matrix == NULL) {
	printf("LED: ERROR MALLOC\n");
	return -1;
    }

    printf("LED: init strip 1\n"); 
    if ((ret = ws2811_init(&ledstring1)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init 1 failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    printf("LED: init strip 2\n"); 
    if ((ret = ws2811_init(&ledstring2)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init 2 failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

    printf("LED: init strip 3\n"); 
    if ((ret = ws2811_init(&ledstring3)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init 3 failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }
/*
    for (int x = 0; x<LED_X ; x++ ) {
	for (int y = 0; y<LED_Y ; y++) {
		led_set_pixel_rgb(x, y, 0, x, y);
	}
    }
    led_show();
    for (int i = 0 ; i<64 ; i++) {
	printf("%X ", ledstring1.channel[0].leds[i]);
    }
    printf("\n");
*/
    printf("TEST...");

    ledstring1.channel[0].leds[0] = 0x00FFFFFF;
    ledstring2.channel[0].leds[0] = 0x00FFFFFF;
    ledstring3.channel[0].leds[0] = 0x00FFFFFF;
    ws2811_render(&ledstring1);
    ws2811_render(&ledstring2);
    ws2811_render(&ledstring3);
    usleep(1000000);
    ledstring1.channel[0].leds[0] = 0x000000FF;
    ledstring2.channel[0].leds[0] = 0x0000FF00;
    ledstring3.channel[0].leds[0] = 0x00FF0000;
    ws2811_render(&ledstring1);
    ws2811_render(&ledstring2);
    ws2811_render(&ledstring3);
    usleep(1000000);
    ledstring1.channel[0].leds[0] = 0x0000FFFF;
    ledstring2.channel[0].leds[0] = 0x00FFFF00;
    ledstring3.channel[0].leds[0] = 0x00FF00FF;
    ws2811_render(&ledstring1);
    ws2811_render(&ledstring2);
    ws2811_render(&ledstring3);
    usleep(1000000);

     return 0;
}

int deinit_led() {
    ws2811_fini(&ledstring1);
    ws2811_fini(&ledstring2);
    ws2811_fini(&ledstring3);
    return 0;
}
