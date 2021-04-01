#include <avr/io.h> 
#include "../crypto/p4093/ksuba_4093.h"
#include "../crypto/p4096/ksuba_4096.h"
#include "../crypto/p4093/school_4093.h"
#include "../crypto/p12289/ntt_12289_512.h"
#include "../crypto/p7681/ntt_7681_256.h"




static void uart_init (void); 
static int uart_putchar(char c);

#define LEDPORT PORTE
volatile unsigned int counter; 


//Keys
#include "../keys/keypair_S_192_4093_8000.data"
#include "../keys/keypair_S_256_4093_8000.data"
#include "../keys/keypair_S_320_4093_8000.data"
#include "../keys/keypair_N_256_7681_1132.data"
#include "../keys/keypair_N_512_12289_1218.data"

int main (void)
{
  uart_init();  

 
  uint16_t c1[ALGOSELECT];
  uint16_t c2[ALGOSELECT];	
  uint8_t plaintext[ALGOSELECT/8];

  #if ALGOSELECT == 192 && ALGO == 0
    encrypt_4093(plaintext, c1, c2, pubKeyA_4093_192, pubKeyP_4093_192, 192);			
    decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_192, 192);
  #endif

  #if ALGOSELECT == 256 && ALGO == 0
    encrypt_4093(plaintext, c1, c2, pubKeyA_4093_256, pubKeyP_4093_256, 256);			
    decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_256, 256);
  #endif

  #if ALGOSELECT == 320 && ALGO == 0
    encrypt_4093(plaintext, c1, c2, pubKeyA_4093_320, pubKeyP_4093_320, 320);			
    decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_320, 320);
  #endif


  #if ALGOSELECT == 192 && ALGO == 1
    encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_192, pubKeyP_4093_192, 192);			
    decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_192, 192);
  #endif

  #if ALGOSELECT == 256 && ALGO == 1
    encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_256, pubKeyP_4093_256, 256);			
    decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_256, 256);
  #endif

  #if ALGOSELECT == 320 && ALGO == 1
    encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_320, pubKeyP_4093_320, 320);			
    decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_320, 320);
  #endif

  #if ALGOSELECT == 192 && ALGO == 5
    encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4093_192, pubKeyP_4093_192, 192);			
    decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4093_192, 192);
  #endif

  #if ALGOSELECT == 256 && ALGO == 5
    encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4093_256, pubKeyP_4093_256, 256);			
    decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4093_256, 256);
  #endif

  #if ALGOSELECT == 320 && ALGO == 5
    encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4093_320, pubKeyP_4093_320, 320);			
    decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4093_320, 320);
  #endif

  #if ALGOSELECT == 256 && ALGO == 2
    encrypt_7681_256(plaintext, c1, c2, pubKeyA_7681_256, pubKeyP_7681_256);
    decrypt_7681_256(plaintext, c1, c2, prvKeyR2_7681_256);
  #endif

  #if ALGOSELECT == 512 && ALGO == 2
    encrypt_12289_512(plaintext, c1, c2, pubKeyA_12289_512, pubKeyP_12289_512);
    decrypt_12289_512(plaintext, c1, c2, prvKeyR2_12289_512);
  #endif

  #if ALGOSELECT == 256 && ALGO == 3
    enc_p7681_96m(plaintext, c1, c2, pubKeyA_7681_256, pubKeyP_7681_256);
    dec_p7681_96m(plaintext, c1, c2, prvKeyR2_7681_256);
  #endif

  #if ALGOSELECT == 256 && ALGO == 4
    uint8_t redundancy[16];
    uint8_t key_enc[16];
    uint8_t key_dec[16];
    kem_encapsulate(c1, c2, pubKeyA_7681_256, pubKeyP_7681_256, key_enc, redundancy); 
    kem_decapsulate(key_dec, redundancy, c1, c2, prvKeyR2_7681_256);
  #endif


  for(uint16_t i=0; i<ALGOSELECT; i++){
    uart_putchar(plaintext[i]);
   }
         
}
 

static int uart_putchar (char c)
{
 
  // Wait for the transmit buffer to be empty
  while ( !( USARTC0.STATUS & USART_DREIF_bm) );
 
  // Put our character into the transmit buffer
  USARTC0.DATA = c; 
 
  return 0;
}
 
 
// Init USART.  Transmit only (we're not receiving anything)
// We use USARTC0, transmit pin on PC3.
// Want 9600 baud. Have a 2 MHz clock. BSCALE = 0
// BSEL = ( 2000000 / (2^0 * 16*9600)) -1 = 12
// Fbaud = 2000000 / (2^0 * 16 * (12+1))  = 9615 bits/sec
static void uart_init (void)
{
  // Set the TxD pin high - set PORTC DIR register bit 3 to 1
  PORTC.OUTSET = PIN3_bm;
 
  // Set the TxD pin as an output - set PORTC OUT register bit 3 to 1
  PORTC.DIRSET = PIN3_bm;
 
  // Set baud rate & frame format
  USARTC0.BAUDCTRLB = 0;// BSCALE = 0 as well
  USARTC0.BAUDCTRLA = 12;
 
  // Set mode of operation
  USARTC0.CTRLA = 0;// no interrupts please
  USARTC0.CTRLC = 0x03;// async, no parity, 8 bit data, 1 stop bit
 
  // Enable transmitter only
  USARTC0.CTRLB = USART_TXEN_bm;
}
