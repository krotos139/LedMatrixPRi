
static char VERSION[] = "XX.YY.ZZ";

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>
#include <stdarg.h>
#include <getopt.h>


#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
#include "version.h"
#include <pthread.h>

#include "led_tasks.h"

uint8_t running = 1;

static void ctrl_c_handler(int signum)
{
	(void)(signum);
    running = 0;
}

static void setup_handlers(void)
{
    struct sigaction sa =
    {
        .sa_handler = ctrl_c_handler,
    };

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
}

int main(/*int argc, char *argv[]*/)
{
    pthread_t thread;
    sprintf(VERSION, "%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);

    printf("START LED CONTROL SYSTEM. VERSION: %s\n", VERSION);

    sem_init(&semaphore, 0, 1);
    setup_handlers();

    init_led(); 

    if ( pthread_create( &thread, NULL, thread_led, NULL ) ) {
	printf("ERROR: Can not create thread\n");
	return -1;
    }

    printf("READY\n");

    while (running) {
    	control_task();
    }

    pthread_join(thread, NULL);

    sem_destroy(&semaphore);

    printf("QUIT\n");

    deinit_led();

    printf ("\n");
    return 0;
}
