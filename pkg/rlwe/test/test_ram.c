#include <avr/io.h> 
#include <avr/pgmspace.h>

#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"
#include "../device/measureRAM.h"
#include "../crypto/p4093/ksuba_4093.h"
#include "../crypto/p4093/school_4093.h"
#include "../crypto/p12289/ntt_12289_512.h"
#include "../crypto/p7681/ntt_7681_256.h"
#include "../crypto/rng/avr_trng.h"
#include "../crypto/rng/aes_prng.h"


//include key files
#include "../keys/keypair_N_256_7681_1132.data"
#include "../keys/keypair_N_512_12289_1218.data"

#include "../keys/keypair_S_192_4093_8000.data"
#include "../keys/keypair_S_256_4093_8000.data"
#include "../keys/keypair_S_320_4093_8000.data"

void test_ksuba_ram(void)
{  
	uint16_t c1[256];
	uint16_t c2[256];
	uint16_t res[256];
	uint16_t start, end;
	
       	//there is no Karatsuba for 7681 or 12289. Just for 4093
	//measure the RAM consumption depending on the various recursion stages
	generateRandomPolyTable_4093(c1, 256);
	generateRandomPolyTable_4093(c2, 256);

	for(uint8_t i=0; i<10;i++){
	  set_max_recursion_stages(i);
	  start = startRAM(__malloc_heap_start);

	  karatsuba_4093_256(c1, c2, res,0);
	  end = endRAM();
	  printf("KSUBA 4093 RAM consumption (stage %d): %d\n", i, start - end);       
	}

	/*
	//set_max_recursion_stages(0);
	//start = startRAM();
	//karatsuba_4093_256(c1, c2, res);
	//end = endRAM();
	//printf("\nKSUBA RAM consumption: %d\n", start - end);


	set_max_recursion_stages(2);
	start = startRAM();
	karatsuba_4093_256(c1, c2, res);
	end = endRAM();
	printf("\nKSUBA RAM consumption: %d\n", start - end);
	
	set_max_recursion_stages(3);
	start = startRAM();
	karatsuba_4093_256(c1, c2, res);
	end = endRAM();
	printf("\nKSUBA RAM consumption: %d\n", start - end);
	
	set_max_recursion_stages(10);
	start = startRAM();
	karatsuba_4093_256(c1, c2, res);
	end = endRAM();
	printf("\nKSUBA RAM consumption: %d\n", start - end);

	start = startRAM();
	karatsuba_4093_256(c1, c2, res);
	end = endRAM();
	printf("\nKSUBA RAM consumption: %d\n", start - end);
	*/
}


int main(void ){

  // Set frequency to 32 MHz
  CLKSYS_Enable( OSC_RC32MEN_bm );
  do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );
  CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_RC32M_gc );
  CLKSYS_Disable( OSC_RC2MEN_bm | OSC_RC32KEN_bm );
	
  USARTinit();
  avr_trng_init();

  printf("Ksuba RAM\n");
  test_ksuba_ram();
  
  for(uint16_t i=0; i<256; i++){
    printf("  ");
  }

  return 0;

}



