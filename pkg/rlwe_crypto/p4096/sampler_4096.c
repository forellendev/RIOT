#include <inttypes.h>
#include <avr/pgmspace.h> 

#include "../sampler/cdf_sampler.h"
#include "../rng/aes_prng.h"

#include "cdf_table_4096_8000.data"

#define MAX_BUF 48

void get_gauss_poly_4096(uint16_t* retpoly, uint16_t add, const uint16_t paramN){
  //Generates or adds Gaussian noise to an array
  int8_t ret;
  uint16_t val=0;

  uint8_t rand_buf[MAX_BUF];
  uint8_t rand_consumed = 254;
  uint8_t rand_consumed_func= 0;

  for (uint16_t i = 0; i< paramN; i++){
    
    //General idea: First we sample some randomness into a buffer
    //Then we run the sampler and track how much random bytes have been used already
    //We refill the buffer in case we encounter that it does not contain enough randomness to sustain a worst case
    //run of the sampler. Thus the 13 as 13*8 = 104 and we have precision 100.

    if (rand_consumed > (MAX_BUF-13)){
      for(uint16_t j = 0; j < MAX_BUF/16; j++){
	//AES writes 128 bit = 16 byte into the buffer
	next_block_ptr(rand_buf+16*j);
      }
      
      /*
	for(uint8_t j=0; j<48; j++){
	  printf("%x",rand_buf[j]);
	}
      */

      rand_consumed = 0;
    }

    ret = sample_gauss(CDF_ROWS, CDF_COLUMNS, &cdf_table_4096_8000[0][0],  (uint8_t*) rand_buf+rand_consumed, (uint8_t*) &rand_consumed_func);
    rand_consumed += rand_consumed_func;
    
    //printf("Rand consumed %d\n",rand_consumed);

    if (ret <0){
      val = ret + 4096;
    } else{
      val = ret;
    }
    
    if(add == 1){
      retpoly[i] = (retpoly[i]+val) & 0xFFF;
      
    }else{
      retpoly[i] = val;
    }
  } 


}


void get_gauss_poly_4096_posneg(uint16_t* retpoly, uint16_t add, const uint16_t paramN){
  //Generates or adds Gaussian noise to an array
  int8_t ret;

  uint8_t rand_buf[MAX_BUF];
  uint8_t rand_consumed = 254;
  uint8_t rand_consumed_func= 0;

  for (uint16_t i = 0; i< paramN; i++){
    
    //General idea: First we sample some randomness into a buffer
    //Then we run the sampler and track how much random bytes have been used already
    //We refill the buffer in case we encounter that it does not contain enough randomness to sustain a worst case
    //run of the sampler. Thus the 13 as 13*8 = 104 and we have precision 100.

    if (rand_consumed > (MAX_BUF-13)){
      for(uint16_t j = 0; j < MAX_BUF/16; j++){
	//AES writes 128 bit = 16 byte into the buffer
	next_block_ptr(rand_buf+16*j);
      }
      
      /*
	for(uint8_t j=0; j<48; j++){
	  printf("%x",rand_buf[j]);
	}
      */

      rand_consumed = 0;
    }

    ret = sample_gauss(CDF_ROWS, CDF_COLUMNS, &cdf_table_4096_8000[0][0],  (uint8_t*) rand_buf+rand_consumed, (uint8_t*) &rand_consumed_func);
    rand_consumed += rand_consumed_func;
    
    //printf("Rand consumed %d\n",rand_consumed);
    
    if(add == 1){
      retpoly[i] = (4096-(retpoly[i]+ret)) & 0xFFF;
      
    }else{
      retpoly[i] = ret;
    }
  } 


}

