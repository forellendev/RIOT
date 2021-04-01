#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"

#include <inttypes.h>
#include "../crypto/p4093/school_4093.h"
#include "profiling.h"
#include <stdio.h>
#include <string.h>
#include "../device/measureRAM.h"

#define paramQ 4093

static int16_t start, end;

static void measurePolyGeneration_4093(uint16_t * a, int paramN)
{
  uint64_t mean = 0;
	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {					
      startMeasurement();		
			
      get_gauss_poly_4093(a,0,paramN);									       
					
      stopMeasurement(&mean);
    }
	
  printResult(&mean, "Gaussian Poly Generation: ");
	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      startMeasurement();		
										
      generateRandomPolyTable_4093(a,paramN);
					
      stopMeasurement(&mean);
    }
	
  printResult(&mean, "Random Poly Generation: ");	
}


static void measure_school_4093(uint16_t *a, const uint16_t *prvKeyR2_4093,  uint16_t *b, int paramN)
{
  uint64_t mean = 0;
	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {				          

      startMeasurement();		
		
      if (paramN==192){
	school_4093_192(a, prvKeyR2_4093, b);
      }
      if (paramN==256){
	school_4093_256(a, prvKeyR2_4093, b);
      }
      if (paramN==320){
	school_4093_320(a, prvKeyR2_4093, b);
      }
	       	
      end = endRAM(); 								
    }
	
  printResult(&mean, "Schoolbook multiplication: ");
}

static void measureLWEOperations_4093(uint16_t * a, uint16_t * b, int paramN, const uint16_t * prvKeyR2_4093, const uint16_t * pubKeyP_4093,const uint16_t * pubKeyA_4093)
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

      encrypt_4093((uint8_t *)msg,a,b, pubKeyA_4093, pubKeyP_4093,paramN);

      stopMeasurement(&mean);		
      end = endRAM();
    }
	
   printResultRAM(&mean, start-end, "Encryption: ");
	

	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      generateRandomPolyTable_4093(a, paramN);
      generateRandomPolyTable_4093(b, paramN);					
		
      start = startRAM(__malloc_heap_start); 
      startMeasurement();		
							
      decrypt_4093((uint8_t *)msg,a,b, prvKeyR2_4093,paramN);	

      stopMeasurement(&mean);	
      end = endRAM();
    }
	
   printResultRAM(&mean, start-end, "Decryption: ");
	

  /*	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      msg[0]= (char) i;
      msg[1]= (char) i+10;
      msg[2]= (char) i+55;
							
      startMeasurement();		
													
      add_encode_4093(msg,a,paramN);
					
      stopMeasurement(&mean);
    }
	
  printResult(&mean, "Encoding: ");
  */

  /*	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      generateRandomPolyTable_12289_512(a);
							
      startMeasurement();		
													
      decode_4093(a, msg, paramN);
					
      stopMeasurement(&mean);
    }
	
  printResult(&mean, "Decoding: ");
  */
}


static void measureCoding(uint16_t * a, int paramN){
	char msg[320/8+1] = "onetwothreefourfonetwothreefourf";
	uint64_t mean = 0;

	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		msg[0]= (char) i;
		msg[1]= (char) i+10;
		msg[2]= (char) i+55;
	
		
		startMeasurement();		

		add_encode_4093((uint8_t *)msg, a, paramN);
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Encoding: ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_7681_256(a);
							
		startMeasurement();		

	        decode_4093(a, (uint8_t *)msg, paramN);	
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Decoding: ");
}

void do_measurement_4093(int paramN, const uint16_t * r2, const uint16_t * p,const uint16_t * a)
{
  uint16_t buf1[320];
  uint16_t buf2[320];

  printf("Measure SchoolbookMul with n = %d and q = 4093:\n\r", paramN);

  measurePolyGeneration_4093(buf1,paramN);
  measureLWEOperations_4093(buf1,buf2,paramN, r2, p, a);		
  measure_school_4093(buf1, r2,  buf2, paramN);
  measureCoding(buf1, paramN);
	
  printf("\n\r");
}
