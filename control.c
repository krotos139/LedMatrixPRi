#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"


int scene = -1;
int new_scene = 0;
	
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
			switch (scene) {
				case 0: effect_test_end();
					break;
			//	case 1: artnet_end();
			//		break;
				case 2: effect_mainlight_end();
					break;
				case 3: effect_off_end();
					break;
			}
			scene = new_scene;
			switch (scene) {
				case 0: effect_test_start();
					break;
			//	case 1: artnet_start();
			//		break;
				case 2: effect_mainlight_start();
					break;
				case 3: effect_off_start();
					break;
			}
		}
		switch (scene) {
			case 0: effect_test_process();
				break;
			//case 1: artnet_process();
			//	break;
			case 2: effect_mainlight_process();
				break;
			case 3: effect_off_process();
				break;
		}
}
