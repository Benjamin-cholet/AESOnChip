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



static volatile uint8_t *map;

void trigger_init() {
	printf("trigger init\n");
	int fd ;
	int i;

	//Obtain handle to physical memory
	if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) {

		perror("Unable to open /dev/mem:");
	}

	map = (uint8_t *)mmap(0, getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0x40010000);

	if ((int8_t *)map < 0) {

	perror("Error :");
}






	printf("%X \n", map[120]);

//	map[120] = 0x04;
//	imap[120] = 0x00;

	//printf("%X \n", map[120]);

	//if (munmap((void *)map,getpagesize()) < 0)
		//perror("munmap error");

	//close(fd);
	return;
}

void trigger_high() {

	map[120] = 0xFF;
}

void trigger_low() {

	map[120] = 0x00;

}


















