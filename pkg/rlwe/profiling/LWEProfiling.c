
#include <avr/io.h>
#include "measure_reduction.h"
#include "../device/clksys_driver.h"
#include "../device/usart_driver.h"
#include "../crypto/rng/avr_trng.h"

#include "profiling.h"

//include key files

#include "../keys/keypair_S_192_4093_8000.data"
#include "../keys/keypair_S_256_4093_8000.data"
#include "../keys/keypair_S_320_4093_8000.data"

#include "../keys/keypair_K_192_4096_8000.data"
#include "../keys/keypair_K_256_4096_8000.data"
#include "../keys/keypair_K_320_4096_8000.data"


int main(void)
{	
  // Set frequency to 32 MHz
  CLKSYS_Enable( OSC_RC32MEN_bm );
  do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );
  CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_RC32M_gc );
  CLKSYS_Disable( OSC_RC2MEN_bm | OSC_RC32KEN_bm );
	
  USARTinit();

 
  avr_trng_init();
	
  initMeasurement();
	
  printf("Attention! Max. precision depends on prescaler!\r\n\r\n");

  
  do_measurement_7681_256();
  
  do_measurement_12289_512();
  
  //do_measurement_4093(192, prvKeyR2_4093_192, pubKeyP_4093_192,pubKeyA_4093_192);
  
  //do_measurement_4093(256, prvKeyR2_4093_256, pubKeyP_4093_256,pubKeyA_4093_256);
  
  //do_measurement_4093(320, prvKeyR2_4093_320, pubKeyP_4093_320,pubKeyA_4093_320);
 	
  do_measurement_reduction_7681_c();

  do_measurement_reduction_7681_asm();

  do_measurement_karatsuba_4093(192, prvKeyR2_4093_192, pubKeyP_4093_192,pubKeyA_4093_192);
  
  do_measurement_karatsuba_4093(256, prvKeyR2_4093_256, pubKeyP_4093_256,pubKeyA_4093_256);
  
  do_measurement_karatsuba_4093(320, prvKeyR2_4093_320, pubKeyP_4093_320,pubKeyA_4093_320);

  do_measurement_karatsuba_4096(192, prvKeyR2_4096_192, pubKeyP_4096_192,pubKeyA_4096_192);
  
  do_measurement_karatsuba_4096(256, prvKeyR2_4096_256, pubKeyP_4096_256,pubKeyA_4096_256);
  
  do_measurement_karatsuba_4096(320, prvKeyR2_4096_320, pubKeyP_4096_320,pubKeyA_4096_320);

	             
  printf("\n\n");
  printf("\n\n");

  while(1)
    {
    }		
}
