/* 
  AESOnChip

  20181218
  trigger.h

  Benjamin Cholet
  JB Valladeau


  downloaded from https://github.com/kokke/tiny-AES-c/blob/master/aes.h
*/

#ifndef _TRIGGER_H_
#define _TRIGGER_H_

void trigger_init();
void trigger();
void trigger_reset();

#define TRIGGER_OFFSET 0x40038000
#define TRIGGER_MEM_SIZE 0x1000

#endif //_TRIGGER_H_