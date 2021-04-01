#include <avr/io.h> 
#include <avr/pgmspace.h>

#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"
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


int main(void ){

  // Set frequency to 32 MHz
  CLKSYS_Enable( OSC_RC32MEN_bm );
  do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );
  CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_RC32M_gc );
  CLKSYS_Disable( OSC_RC2MEN_bm | OSC_RC32KEN_bm );
	
  USARTinit();
  avr_trng_init();

  printf("\n");
  for(uint8_t i=0; i<200; i++){
    printf(" ");
  }
  printf("\n");

  uint16_t retpoly[512];
  get_gauss_poly_12289_512(retpoly, 0);

  for(uint16_t i=0; i<156;i++){
    int32_t val = retpoly[i];
    if (val >= 12289/2){
      val = val -12289;
    }
    printf("%d ", (int)val);
  }

  printf("\n");
  for(uint8_t i =0; i<200;i++){
    printf(" ");
  }
  printf("\n");
  
}
