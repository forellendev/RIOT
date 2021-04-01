#include <inttypes.h>
#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"

#include "../crypto/p7681/ntt_7681_256.h"
#include "../crypto/p7681/param_256_7681.h"
#include "../crypto/p7681/mm7681.h"

#include "profiling.h"
#include <stdio.h>
#include <string.h>

#include "../crypto/p7681/ntt_7681_256_const.data"

#include "../keys/keypair_N_256_7681_1132.data"                 
#include "../device/measureRAM.h"

static int16_t start, end;


static void measureNTT_7681_256(uint16_t * a, uint16_t * b)
{	
  uint64_t mean = 0;

  	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_7681_256(a);
					
      		startMeasurement();		
													
      		ntt_CT_no_to_bo_incl_psi_7681_256((int16_t*)a,psibitrev_7681_256);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (CT_no_to_bo_incl_psi): ");

	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_7681_256(a);
					
      		startMeasurement();		
													
      		ntt_CT_no_to_bo_incl_psi_7681_256_nolookup((int16_t*)a,psibitrev_7681_256);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (CT_no_to_bo_incl_psi_nolookup): ");

  	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_7681_256(a);
					
      		startMeasurement();		
													
      		ntt_GS_bo_to_no_incl_invpsi_7681_256((int16_t*)a,omegainvbitrev_7681_256);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (GS_bo_to_no_incl_invpsi): ");
	
  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      generateRandomPolyTable_7681_256(a);
      generateRandomPolyTable_7681_256(b);

      startMeasurement();		
										
      pw_mul_flash_7681_256(a,b);
					
      stopMeasurement(&mean);
    }

  printResult(&mean, "pw_mul_flash: ");



  for(int i = 0; i<MAX_MEASUREMENT;i++)
    {
      generateRandomPolyTable_7681_256(a);

      startMeasurement();		
										
      for(int j = 0; j<256; j++){		   
	a[j] = (uint32_t) a[j] * pgm_read_word(omegainvbitrev_7681_256) % 7681;     
      }
					
      stopMeasurement(&mean);
    }
	
  printResult(&mean, "pw_mul_flash (naive): ");

	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_7681_256(a);

		start = startRAM(__malloc_heap_start);  	
		startMeasurement();		
										
		pw_psi_7681(a, 1, PSI_VAL);

		stopMeasurement(&mean);
		end = endRAM();							
	}
	
	printResultRAM(&mean, start-end,  "pw_psi_mul: ");


  for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_7681_256(a);
		generateRandomPolyTable_7681_256(b);

		startMeasurement();		

	        add_7681(a, b, a);							
							
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Add: ");		
}
	
static void measurePolyGeneration_7681_256(uint16_t * a)
{
	uint64_t mean = 0;
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{					
		startMeasurement();		
			
		get_gauss_poly_7681_256(a,0);									       
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Gaussian Poly Generation: ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		startMeasurement();		
										
		generateRandomPolyTable_7681_256(a);
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Random Poly Generation: ");	
}

static void measureLWEOperations_7681_256(uint16_t * a, uint16_t * b)
{
	uint64_t mean = 0;
	char msg[paramN/8+1] = "onetwothreefourfonetwothreefourf";
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_7681_256(a);
		generateRandomPolyTable_7681_256(b);
							
		msg[0]= (char) i;
		msg[1]= (char) i+10;
		msg[2]= (char) i+55;
		
		start = startRAM(__malloc_heap_start);						
		startMeasurement();		

		encrypt_7681_256((uint8_t*)msg,a,b, pubKeyA_7681_256, pubKeyP_7681_256);

		stopMeasurement(&mean);
		end = endRAM(); 						

	}
	
	printResultRAM(&mean, start-end,  "Encryption: ");
	

	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{

		generateRandomPolyTable_7681_256(a);
		generateRandomPolyTable_7681_256(b);
							
		start = startRAM(__malloc_heap_start);	 
		startMeasurement();		

		decrypt_7681_256((uint8_t*)msg,a,b, prvKeyR2_7681_256);

		stopMeasurement(&mean);
		end = endRAM(); 						
	}
	
	printResultRAM(&mean, start-end,  "Decryption: ");
	

	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		msg[0]= (char) i;
		msg[1]= (char) i+10;
		msg[2]= (char) i+55;
							
		startMeasurement();		
													
		add_encode_7681_256((uint8_t*)msg,a);
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Encoding: ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_7681_256(a);
							
		startMeasurement();		
													
		decode_7681_256(a, (uint8_t*)msg);
					
		stopMeasurement(&mean);
	}
	
	printResult(&mean, "Decoding: ");
}

void do_measurement_7681_256(void)
{
	
	uint16_t a[paramN];
	uint16_t b[paramN];

	printf("Measure NTT with n = 256 and q = 7681:\n\r");
	
	measureNTT_7681_256(a,b);
	measurePolyGeneration_7681_256(a);
	measureLWEOperations_7681_256(a,b);	
	print_counter();
	
	printf("\n\r");
}
