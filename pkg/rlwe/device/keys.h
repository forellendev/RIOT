#ifndef KEYS_H
#define KEYS_H
#include <inttypes.h>

#define KEY_PORT PORTF
#define KEY_PINCCTRL PIN4CTRL
#define KEY_PORT_INT0_vect PORTF_INT0_vect

volatile uint8_t key;

#define KEY0 0x01
#define KEY1 0x02
#define KEY2 0x04
#define KEY3 0x08
#define KEY4 0x10
#define KEY5 0x20
#define KEY6 0x40
#define KEY7 0x80
#define KEYS 0xFF


void KEYinit(void);
uint8_t getKEYS(void);
#endif
