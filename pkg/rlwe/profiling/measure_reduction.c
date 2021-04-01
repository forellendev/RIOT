#include <inttypes.h>

#include "profiling.h"
#include "../crypto/p7681/mm7681.h"
#include "../crypto/p12289/mm12289.h"
#include "mm24578.h"
#include <stdio.h>
#include <string.h>

#define paramQ 7681



int do_measurement_reduction_7681_c(void){
    volatile  uint16_t c;
    uint64_t mean = 0;
    uint16_t a=0,b=0;

  printf("Measure C based multiplication\n\r");
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	     

      a=3840;
      b=1337;
      c=7521;

	b =  mm7681(a,b);
	a =  mm7681(a,c);

        startMeasurement();			
	c = ((uint32_t)a*b) % 7681;
	stopMeasurement(&mean);		
    }

  printResult(&mean, "Modular Reduction: ");

  return c;



}

void  do_measurement_reduction_7681_asm(void){
  volatile  uint16_t c;
  uint64_t mean = 0;
  uint16_t a=0,b=0;
  uint64_t curr = 0;
  uint16_t max = 0;

  printf("Measure ASM based multiplication\n\r");
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=3840;
      b=1337;

      startMeasurement();		
	c =  mm7681(a,b);
      stopMeasurement(&mean);

	b = ((uint32_t)a*b) % 7681;
	a = ((uint32_t)a*c) % 7681;	
    }

  printResult(&mean, "Modular Reduction (7681): ");

    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=3840;
      b=11337;

      startMeasurement();		
	c =  mm12289(a,b);
      stopMeasurement(&mean);

	b = ((uint32_t)a*b) % 12289;
	a = ((uint32_t)a*c) % 12289;	
    }

  printResult(&mean, "Modular Reduction (12289): ");

    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=13840;
      b=11337;

      startMeasurement();		
	c =  mm24578(a,b);
      stopMeasurement(&mean);

	b = ((uint32_t)a*b) % 24578;
	a = ((uint32_t)a*c) % 24578;	
    }

  printResult(&mean, "Modular Reduction (24578): ");


    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=13840;
      b=11337;

      startMeasurement();		
      stopMeasurement(&mean);

	b = ((uint32_t)a*b) % 24578;
	a = ((uint32_t)a*c) % 24578;	
    }

  printResult(&mean, "Measurement overhead: ");

	// #############################################

    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=7680;
      b=7680;

      startMeasurement();		
	c =  mm7681(a,b);
      stopMeasurement(&curr);
	if(curr > max)
		max = curr;
	curr = 0;

	b = ((uint32_t)a*b) % 7681;
	a = ((uint32_t)a*c) % 7681;	
    }

    printf("Max. cycles mm7681: %d\n\r", max);
    max = 0;

    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=12288;
      b=12288;

      startMeasurement();		
	c =  mm12289(a,b);
      stopMeasurement(&curr);
	if(curr > max)
		max = curr;
	curr = 0;

	b = ((uint32_t)a*b) % 12289;
	a = ((uint32_t)a*c) % 12289;	
    }

  printf("Max. cycles mm12289: %d\n\r", max);
    max = 0;

    for(int i = 0; i<MAX_MEASUREMENT;i++)
    {	

      a=24577;
      b=24577;

      startMeasurement();		
	c =  mm24578(a,b);
      stopMeasurement(&curr);
	if(curr > max)
		max = curr;
	curr = 0;

	b = ((uint32_t)a*b) % 24578;
	a = ((uint32_t)a*c) % 24578;	
    }

  printf("Max. cycles mm24578: %d\n\r", max);
    max = 0;


}
