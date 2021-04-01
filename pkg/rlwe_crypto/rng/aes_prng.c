#include <inttypes.h>
#include "aes_prng.h"
#include "AES_driver.h"

//#include "../../device/avr_compiler.h"


//First 16 byte are plaintext, next 16 bytes are key

static uint32_t pool[8];
static uint8_t output[16];


void init_pool(uint32_t val,uint8_t word){
  //Initialize a word in the pool
  if(word<8){
    pool[word] = val;
  }
}

void update_pool(uint32_t val,uint8_t word){
  //Update the pool with data
  if(word<8){
    pool[word] ^= val;
  }
}

uint8_t * get_pool(){
  //Just return a pointer to the pool
  return (uint8_t *) pool;
}

void next_block()
{
  //AES_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key)   
  AES_encrypt((uint8_t *)&pool[0], output, &((uint8_t *)(pool))[16]);

  //Update the counter (plaintext)
  pool[0] = pool[0] + 1;
}

void next_block_ptr(uint8_t* out_ptr)
{
  //AES_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key)   
  AES_encrypt((uint8_t *)&pool[0], out_ptr, &((uint8_t *)(pool))[16]);

  //Update the counter (plaintext)
  pool[0] = pool[0] + 1;
}


uint8_t * get_AES_pool(){
  //Return address of the AES output
  return (uint8_t *)pool;
}






