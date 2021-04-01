#include <inttypes.h>
#include <stdio.h>
#include <avr/pgmspace.h> 

#include "cdf_sampler.h"
#include "../rng/aes_prng.h"


int8_t sample_gauss(uint8_t row, uint8_t column, const uint8_t *table, uint8_t *rand_buf, uint8_t *rand_consumed){
  uint8_t i,j,val;
  uint8_t max_j = 0;
  *rand_consumed = 0;

  /*printf("%x ", table[1*r0]);
  printf("%x ", table[1*row+1]);
  printf("%x ", table[1*row+2]);
  printf("%x ", table[1*row+3]);
  */

  for (i=0; i<row; i++){
    max_j = 0;
    for (j=0; j<column; j++){
     
      //Select current table entry
      //val = table[i*column+j];
      val = pgm_read_byte(&table[i*column+j]);
      
      //Measure randomness consumption
      if (j > max_j){
	max_j = j;
      }
      
      //Start comparision
      if ( (uint8_t) rand_buf[j] < (uint8_t) val){
	*rand_consumed = max_j + 1;

	if (rand_buf[j+1]<=127){
	  return -((int8_t) i);
	} else
	return (int8_t) i;

      }else if ((uint8_t) rand_buf[j] == (uint8_t) val){
	continue;
	printf("Cont");
      }else if((uint8_t) rand_buf[j] > (uint8_t) val){
	break;
      }
    }
  }

  return 0; //Must not reach this
}
