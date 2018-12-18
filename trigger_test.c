/*
	AESOnChip
	20181218

	trigger.c

	Benjamin Cholet
	JB Valladeau	
*/

#include <unistd.h>
#include "trigger.h"

int main(void) {

	trigger_init();

	while (1) {

		trigger();
		sleep(5);

		trigger_reset();
		sleep(5);
	}
}