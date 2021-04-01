#include <inttypes.h>
#include <avr/interrupt.h>

#include "../crypto/rng/aes_prng.h"
#include "../device/usart_driver.h"
#include "profiling.h"

uint16_t ovfs;


#define testmsg192 "!plaintexttest!!!plainte"
#define testmsg256 "!plaintexttest!!!plaintexttest!!"
#define testmsg320 "!plaintexttest!!!plaintexttest!!!plainte"
#define testmsg512 "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!" 

void generateRandomPolyTable_12289_512(uint16_t* retpoly){
  for(int i = 0; i<512; i++)
    {
      //retpoly[i] = get_random_bits25() % 12289;
      uint16_t x = 3;
      retpoly[i] = x;
      x = (x *193) % 12289;

       // TODO XXX get_random_bits25() % 4093;
    }  
}

void generateRandomPolyTable_7681_256(uint16_t* retpoly){
  for(int i = 0; i<256; i++)
    {
      uint16_t x = 3;
      retpoly[i] = x;
      x = (x *193) % 7681;

      //retpoly[i] = get_random_bits25() % 7681;
      //retpoly[i] = 0; // TODO XXX get_random_bits25() % 4093;
    }  
}


void generateRandomPolyTable_4093(uint16_t* retpoly, uint16_t n){
  for(int i = 0; i<n; i++)
    {
      //retpoly[i] = 0; // TODO XXX get_random_bits25() % 4093;

      uint16_t x = 3;
      retpoly[i] = x;
      x = (x *193) % 4093;
    }  
}

void generateRandomPolyTable_4096(uint16_t* retpoly, uint16_t n){
  for(int i = 0; i<n; i++)
    {
      //retpoly[i] = 0; // TODO XXX get_random_bits25() % 4093;

      uint16_t x = 3;
      retpoly[i] = x;
      x = (x *193) % 4096;
    }  
}


void startTimer(uint16_t prescaler)
{
  //if(prescaler == 1024)
  //		TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
  //	else if(prescaler == 256)
  //		TCC0.CTRLA = TC_CLKSEL_DIV256_gc;
  //	else
  //		TCC0.CTRLA = TC_CLKSEL_DIV1_gc;	
  
  TCC0.CTRLA = TC_CLKSEL_DIV1_gc;
  

}

void stopTimer(void)
{
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}

void initMeasurement(void)
{
  
  EVSYS.CH1MUX = EVSYS_CHMUX_TCC0_OVF_gc;
 
  PORTE.DIR = 0xFF;
  TCC0.INTCTRLA = TC_OVFINTLVL_MED_gc;
  TCC0.PER = 0xFFFF;
  
  TCC1.CTRLA = TC_CLKSEL_EVCH1_gc;
  TCC1.PER = 0xFFFF;
  
  PMIC.CTRL = PMIC_MEDLVLEN_bm;
}


void startMeasurement(void)
{
	ovfs = 0;
	TCC0.CNT = 0;
	TCC1.CNT = 0;

	//sei();
	startTimer(PRESCAL);
}

void stopMeasurement(uint64_t * mean)
{
	stopTimer();
	//cli();
	
	(*mean) += TCC0.CNT | (uint32_t)TCC1.CNT << 16;
}

void printResult(uint64_t * mean, const char * s)
{
	printf("%s", s);
	(*mean) /= MAX_MEASUREMENT;
	
	//USARTsendMeasurementResult((*mean), PRESCAL);
	printf("%ld ",(uint32_t) (*mean) * (uint32_t) PRESCAL );
	printf("Cycles\n");	
	(*mean) = 0;
}

void printResultRAM(uint64_t * mean, int16_t ram, const char * s)
{
	printf("%s", s);
	(*mean) /= MAX_MEASUREMENT;
	
	//USARTsendMeasurementResult((*mean), PRESCAL);
	printf("%ld ",(uint32_t) (*mean) * (uint32_t) PRESCAL );
	printf("Cycles %d bytes RAM\n", ram);

	(*mean) = 0;
}


ISR(TCC1_OVF_vect)
{
	printf("Warning: Overflow! Should not happen");
	ovfs++;
}








/*
void startTimer(uint16_t prescaler)
{
	if(prescaler == 1024)
		TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
	else if(prescaler == 256)
		TCC0.CTRLA = TC_CLKSEL_DIV256_gc;
	else
		TCC0.CTRLA = TC_CLKSEL_DIV1_gc;	
}

void stopTimer(void)
{
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}

void initMeasurement(void)
{
	PORTE.DIR = 0xFF;
	TCC0.INTCTRLA = TC_OVFINTLVL_MED_gc;
	TCC0.PER = 0xFFFF;
	
	PMIC.CTRL = PMIC_MEDLVLEN_bm;
}


void startMeasurement(void)
{
	ovfs = 0;
	TCC0.CNT = 0;
	sei();
	startTimer(PRESCAL);
}

void stopMeasurement(uint32_t * mean)
{
	stopTimer();
	cli();
	
	(*mean) += TCC0.CNT;
}
*void startTimer(uint16_t prescaler)
{
	if(prescaler == 1024)
		TCC0.CTRLA = TC_CLKSEL_DIV1024_gc;
	else if(prescaler == 256)
		TCC0.CTRLA = TC_CLKSEL_DIV256_gc;
	else
		TCC0.CTRLA = TC_CLKSEL_DIV1_gc;	
}

void stopTimer(void)
{
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}

void initMeasurement(void)
{
	PORTE.DIR = 0xFF;
	TCC0.INTCTRLA = TC_OVFINTLVL_MED_gc;
	TCC0.PER = 0xFFFF;
	
	PMIC.CTRL = PMIC_MEDLVLEN_bm;
}


void startMeasurement(void)
{
	ovfs = 0;
	TCC0.CNT = 0;
	sei();
	startTimer(PRESCAL);
}

void stopMeasurement(uint32_t * mean)
{
	stopTimer();
	cli();
	
	(*mean) += TCC0.CNT;

}
*/
