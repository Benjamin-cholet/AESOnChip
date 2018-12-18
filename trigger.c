/*
	AESOnChip
	20181218

	trigger.c

	Benjamin Cholet
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#include "trigger.h"

static volatile uint8_t *map;

void trigger_init() {

	int fd ;
	int i;

	//Obtain handle to physical memory
	if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) {

		perror("Unable to open /dev/mem:");
	}

	map = (uint8_t *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, TRIGGER_OFFSET);

	if ((int8_t *)map < 0) {

		perror("Error :");
	}
	return;
}

void trigger() {

	int i;
	for (i = 0; i < TRIGGER_MEM_SIZE; i++)

		map[i] = 0xFF;
	return;
}

void trigger_reset() {

	int i;
	for (i = 0; i < TRIGGER_MEM_SIZE; i++)

		map[i] = 0x00;
	return;
}
