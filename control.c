#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"


int scene = -1;
int new_scene = 4;
	
void switchScene(int scene) {
	new_scene = scene;
}

int getScene() {
	return new_scene;
}

void control_task() {
	
	/* scenes:
	0: test
	1: artnet
	2: light
	3: off
	*/
	

		if (scene != new_scene) {
			printf("CONTROL: Switch to scene %d\n", new_scene);
			printf("CONTROL: stop scene %d\n", scene);
			switch (scene) {
				case 0: effect_test_end();
					break;
				case 1: artnet_end();
					break;
				case 2: effect_mainlight_end();
					break;
				case 3: effect_off_end();
					break;
				case 4: effect_perlinnoise_end(); 
					break;
				case 5: effect_perlinnoisergb_end(); 
					break;
				case 6: effect_perlinnoiseg_end(); 
					break;
				case 7: effect_perlinnoiseb_end(); 
					break;

			}
			scene = new_scene;
			printf("CONTROL: start scene %d\n", scene);
			switch (scene) {
				case 0: effect_test_start();
					break;
				case 1: artnet_start();
					break;
				case 2: effect_mainlight_start();
					break;
				case 3: effect_off_start();
					break;
				case 4: effect_perlinnoise_start(); 
					break;
				case 5: effect_perlinnoisergb_start(); 
					break;
				case 6: effect_perlinnoiseg_start(); 
					break;
				case 7: effect_perlinnoiseb_start(); 
					break;

			}
			printf("CONTROL: done swiching\n");

		}
		switch (scene) {
			case 0: effect_test_process();
				break;
			case 1: artnet_process();
				break;
			case 2: effect_mainlight_process();
				break;
			case 3: effect_off_process();
				break;
			case 4: effect_perlinnoise_process(); 
				break;
			case 5: effect_perlinnoisergb_process(); 
				break;
			case 6: effect_perlinnoiseg_process(); 
				break;
			case 7: effect_perlinnoiseb_process(); 
				break;

		}
}
