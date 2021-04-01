#include <inttypes.h>
#include "../../device/avr_compiler.h"


uint32_t get_trnd_adc(void)
{
	uint32_t result = 0;
	uint8_t res[4] = {0,0,0,0};
	
	for(int j = 0; j<4;j++)
	{
		for(int i = 0; i<8; i++)
		{
			ADCA.CH0.CTRL |= ADC_CH_START_bm; // start conversion on channel 0
		
			while(!ADCA.CH0.INTFLAGS); // wait for conversion to be finished
			
			ADCA.CH0.INTFLAGS=ADC_CH_CHIF_bm; // clear itnerrupt flag
		
			res[j] |= (ADCA.CH0RES & 1)<<i; // get LSB
		}	
	}
	
	// compose 32 bit value in assembly
	asm (
      "mov %A0, %A1"	"\n\t"
      "mov %B0, %A2"	"\n\t"
      "mov %C0, %A3"	"\n\t"
      "mov %D0, %A4"
         : "=&r" (result)
         : "r"   (res[0]), "r" (res[1]), "r"   (res[2]), "r" (res[3])
    );	
	
	return result;
}

// http://www.bostonandroid.com/manuals/xmega-precision-adc-howto.html
void avr_trng_init(void)
{
	PORTA.DIR = 0; 	// configure PORTA as input
	ADCA.CTRLA |= 0x1; 	// enable adc
	ADCA.CTRLB = ADC_RESOLUTION_12BIT_gc; 	// 12 bit conversion
	ADCA.REFCTRL = ADC_REFSEL_INT1V_gc | 0x02; 	// internal 1V bandgap reference
	ADCA.PRESCALER = ADC_PRESCALER_DIV8_gc; 	// peripheral clk/8 (2MHz/16=250kHz)
	ADCA.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc  | ADC_CH_GAIN_64X_gc; 	// single ended & 64x gain
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN4_gc; 	// PORTA:2 
}
