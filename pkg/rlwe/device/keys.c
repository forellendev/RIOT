#include "keys.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define KEY_DEBOUNCE
#ifdef KEY_DEBOUNCE
#include <util/delay.h>
#endif

void KEYinit(void) {
  KEY_PORT.DIRCLR=KEYS;
  PORTCFG_MPCMASK=KEYS;
  //enable pull-up on group, pin number doesn't matter

  KEY_PORT.KEY_PINCCTRL = PORT_ISC_FALLING_gc|PORT_OPC_PULLUP_gc;
  KEY_PORT.INTCTRL  = PORT_INT0LVL_LO_gc;
  KEY_PORT.INT0MASK = KEYS;
}

uint8_t getKEYS(void) {
  return KEY_PORT.IN;
}
