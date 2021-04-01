#include <inttypes.h>
#include "des_prng.h"
#include "DES_driver.h"
#include "../../device/avr_compiler.h"

static uint8_t pool_key[8];
static uint8_t pool_plain[8];
static uint8_t pool_out[4];
//static uint32_t pool_out;
static uint8_t pool_cnt=0;

#define MAX_SIZE 32
static uint8_t ring_buf[MAX_SIZE];
static uint8_t buf_ptr=0;


void init_pool(uint8_t * ptr)
{
  for(uint8_t i = 0; i<8;i++)
    {
      pool_key[i] = ptr[i];
      pool_plain[i] = ptr[i+8];
    }
	
  pool_cnt = 0;
}

void get_pool(uint8_t * ptr){
  for(uint8_t i=0; i<8;i++){
    ptr[i] = pool_key[i];
  }
  for(uint8_t i=0; i<8;i++){
    ptr[i+8] = pool_plain[i];
  }
}

void update_pool(uint8_t * ptr, uint8_t sel)
{
  uint8_t result[8];
	
  DES_Encrypt(ptr, &ptr[8], result);
	
  for(uint8_t i = 0; i<8;i++)
    {
      if(sel == 0)
	pool_key[i] ^= result[i];
      else
	pool_plain[i] ^= result[i];
    }
	
  pool_cnt = 0;
}


void get_DES_block(uint8_t *buf)
{  	
  DES_Encrypt(pool_plain, buf, pool_key);
      
  //Use CBC construction
  for(uint8_t i=0; i<8; i++){
    pool_plain[i] ^= buf[i];
  }
}


static uint8_t * out_ptr;
static uint8_t buffer[8];

static void get_random_bits(void)
{  	
  //if(pool_cnt == 0)
    //{
      DES_Encrypt(pool_plain,buffer,pool_key);
      
      //Use CBC construction
      for(uint8_t i=0; i<8; i++){
	pool_plain[i] ^= buffer[i];
      }
      	
      //out_ptr = buffer;
	
      //pool_out = buffer[0] << 24 | buffer[1] << 16 | ((uint32_t)buffer[2] << 8) | buffer[3] << 16;

      pool_out[0] = buffer[4];
      pool_out[1] = buffer[5];
      pool_out[2] = buffer[6];
      pool_out[3] = buffer[7];
		
      //pool_cnt++;
      //}
      //else
      //{
      //out_ptr = pool_out;
      // pool_cnt = 0;
      //}			
}

uint32_t get_random_bits25(void){
  uint32_t result;
  get_random_bits();

  // compose 32 bit value in assembly
  asm (
       "mov %A0, %A1"	"\n\t"
       "mov %B0, %A2"	"\n\t"
       "mov %C0, %A3"	"\n\t"
       "mov %D0, %A4"	"\n\t"
       "andi %D0, 1"	
       : "=&r" (result)
       : "r"   (out_ptr[0]), "r" (out_ptr[1]), "r"   (out_ptr[2]), "r" (out_ptr[3])
       );

  return result;
}

uint32_t get_random_bits32(void){
  uint32_t result;

  get_random_bits();

  
  // compose 32 bit value in assembly
  asm (
       "mov %A0, %A1"	"\n\t"
       "mov %B0, %A2"	"\n\t"
       "mov %C0, %A3"	"\n\t"
       "mov %D0, %A4"	"\n\t"
       : "=&r" (result) : "r"   (out_ptr[0]), "r" (out_ptr[1]), "r"   (out_ptr[2]), "r" (out_ptr[3])
       );
  

  //return (uint32_t) *pool_out;
  return result;
}




