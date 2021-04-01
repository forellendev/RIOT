#include <inttypes.h>
#include "../crypto/p4093/ksuba_4093.h"
#include "profiling.h"
#include <stdio.h>
#include <string.h>
#include "../device/measureRAM.h"
#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"


#define paramQ 4093

static int16_t start, end;

static void measureLWEOperations_ksuba_4093(uint16_t * a, uint16_t * b, int paramN, const uint16_t * prvKeyR2_4093, const uint16_t * pubKeyP_4093,const uint16_t * pubKeyA_4093)
{
  uint64_t mean = 0;
  char msg[paramN/8+1];
	
  if(paramN == 192)
    {
      strcpy(msg,"onetwothreefourfonetwoth");
    }
  else if(paramN == 256)
    {
      strcpy(msg,"onetwothreefourfonetwothreefourf");
    }
  //paramN == 320
  else
    {
      strcpy(msg,"onetwothreefourfonetwothreefourfivesixse");
    }
	
	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      generateRandomPolyTable_4093(a,paramN);
      generateRandomPolyTable_4093(b,paramN);
							
      msg[0]= (char) i;
      msg[1]= (char) i+10;
      msg[2]= (char) i+55;

      start = startRAM(__malloc_heap_start); 
      startMeasurement();		

      encrypt_ksuba_4093((uint8_t*)msg,a,b, pubKeyA_4093, pubKeyP_4093,paramN);
      stopMeasurement(&mean);					
      end = endRAM();

    }
	
  printResultRAM(&mean, start-end, "\nEncryption: ");
	

	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {

      generateRandomPolyTable_4093(a, paramN);
      generateRandomPolyTable_4093(b, paramN);					

      start = startRAM(__malloc_heap_start); 		
      startMeasurement();		
							
      decrypt_ksuba_4093((uint8_t*)msg,a,b, prvKeyR2_4093,paramN);	
      stopMeasurement(&mean);
      end = endRAM();
	
    }
	
  printResultRAM(&mean, start-end, "Decryption: ");
}

void do_measurement_karatsuba_4093(int paramN, const uint16_t * r2, const uint16_t * p,const uint16_t * a)
{
  uint16_t buf1[320];
  uint16_t buf2[320];

  printf("Measure KaratsubaMul with n = %d and q = 4093:\n\r", paramN);

  for(int i = 5; i< 6; i++)
    {
      set_max_recursion_stages(i);
			
      printf("Measuring with max_recursion_stage %d\n\r", i);
      measureLWEOperations_ksuba_4093(buf1,buf2,paramN, r2, p, a);
    }
		
	
  printf("\n\r");
}
