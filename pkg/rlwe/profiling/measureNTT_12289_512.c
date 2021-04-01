#include <avr/io.h> 
#include <avr/pgmspace.h>
#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"


#include <inttypes.h>

#include "../crypto/p12289/param_12289_512.h"
#include "../crypto/p12289/ntt_12289_512.h"

#include "../crypto/p12289/ntt_12289_512_const.data"

#include "../keys/keypair_N_512_12289_1218.data"                 


#include "../device/measureRAM.h"
#include "profiling.h"
#include <stdio.h>
#include <string.h>

static int16_t start, end;

static void measureNTT_12289_512(uint16_t * a, uint16_t * b)
{	
	uint64_t mean = 0;

	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_12289_512(a);
					
      		startMeasurement();		
													
      		ntt_CT_no_to_bo_incl_psi_12289_512((int16_t*)a,psibitrev_12289_512);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (CT_no_to_bo_incl_psi): ");

  	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_12289_512(a);
					
      		startMeasurement();		
													
      		ntt_GS_bo_to_no_incl_invpsi_12289_512((int16_t*)a,omegainvbitrev_12289_512);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (GS_bo_to_no_incl_invpsi): ");

	for(int i = 0; i<MAX_MEASUREMENT;i++)
    	{
      		generateRandomPolyTable_12289_512(a);
					
      		startMeasurement();		
													
      		ntt_CT_no_to_bo_incl_psi_12289_512_nolookup((int16_t*)a,psibitrev_12289_512);
					
      		stopMeasurement(&mean);
    	}
	
  	printResult(&mean, "NTT Transformation (CT_no_to_bo_incl_psi_nolookup): ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_12289_512(a);

		start = startRAM(__malloc_heap_start);  	
		startMeasurement();		
										
		pw_mul_flash_12289_512(a,omegainvbitrev_12289_512);

		stopMeasurement(&mean);
		end = endRAM();										
	}
	
	printResultRAM(&mean, start-end,  "pw_mul_flash: ");


	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_12289_512(a);

		start = startRAM(__malloc_heap_start);  	
		startMeasurement();		
										
		pw_psi_12289(a, 1, PSI_VAL);

		stopMeasurement(&mean);
		end = endRAM();							
	}
	
	printResultRAM(&mean, start-end,  "pw_psi_mul: ");


	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_12289_512(a);
		generateRandomPolyTable_12289_512(b);

		start = startRAM(__malloc_heap_start);								
		startMeasurement();		
		
	        add_12289(a, b, a);										

		stopMeasurement(&mean);
		end = endRAM(); 
	}
	
	printResultRAM(&mean, start-end,  "Add: ");	

}
	
static void measurePolyGeneration_12289_512(uint16_t * a)
{
	uint64_t mean = 0;
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{					

	  start = startRAM(__malloc_heap_start);										startMeasurement();		
	  
	  get_gauss_poly_12289_512(a,0);									       	
	  stopMeasurement(&mean);
	  end = endRAM(); 					
	}
	
	printResultRAM(&mean, start-end, "Gaussian Poly Generation: ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		start = startRAM(__malloc_heap_start);								
		startMeasurement();		
										
		generateRandomPolyTable_12289_512(a);
				
		stopMeasurement(&mean);
		end = endRAM(); 	
	}
	
	printResultRAM(&mean, start-end,  "Random Poly Generation: ");	
}

static void measureLWEOperations_12289_512(uint16_t * a, uint16_t * b)
{
	uint64_t mean = 0;
	char msg[paramN/8+1] = "onetwothreefourfonetwothreefourfonetwothreefourfonetwothreefourf";
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		generateRandomPolyTable_12289_512(a);
		generateRandomPolyTable_12289_512(b);
							
		msg[0]= (char) i;
		msg[1]= (char) i+10;
		msg[2]= (char) i+55;
		
		
		start = startRAM(__malloc_heap_start);	
		startMeasurement();		
		
		encrypt_12289_512((uint8_t*)msg,a,b, pubKeyA_12289_512, pubKeyP_12289_512);
					       
		stopMeasurement(&mean);
		end = endRAM(); 	
	}
	
	printResultRAM(&mean, start-end, "Encryption: ");
	

	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{

		generateRandomPolyTable_7681_256(a);
		generateRandomPolyTable_7681_256(b);
							

		start = startRAM(__malloc_heap_start);										startMeasurement();		
													
		decrypt_12289_512((uint8_t*)msg,a,b, prvKeyR2_12289_512);
				

		stopMeasurement(&mean);
		end = endRAM(); 	
	}
	
	printResultRAM(&mean, start-end,   "Decryption: ");
	

	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
		msg[0]= (char) i;
		msg[1]= (char) i+10;
		msg[2]= (char) i+55;

		start = startRAM(__malloc_heap_start);      						
		startMeasurement();		
					       									
		add_encode_12289_512((uint8_t*)msg,a);
		

		stopMeasurement(&mean);
		end = endRAM(); 			
	}
	
	printResultRAM(&mean, start-end,  "Encoding: ");
	
	for(int i = 0; i<MAX_MEASUREMENT;i++)
	{
	  generateRandomPolyTable_12289_512(a);
							
		start = startRAM(__malloc_heap_start);								
		startMeasurement();		
														
		decode_12289_512(a, (uint8_t*)msg);
		

		stopMeasurement(&mean);
		end = endRAM(); 			
	}
	
	printResultRAM(&mean, start-end, "Decoding: ");
}

void do_measurement_12289_512(void)
{
	uint16_t a[paramN];
	uint16_t b[paramN];

	printf("Measure NTT with n = 512 and q = 12289:\n\r");
	
	measureNTT_12289_512(a,b);
	measurePolyGeneration_12289_512(a);
	measureLWEOperations_12289_512(a,b);	
	
	printf("\n");
}
