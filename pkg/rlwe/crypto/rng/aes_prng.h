
#ifndef AES_PRNG_H

#define AES_PRNG_H
  void init_pool(uint32_t val,uint8_t word);
  void update_pool(uint32_t val,uint8_t word);
  uint8_t * get_pool(void);
  void next_block(void);
  void next_block_ptr(uint8_t* out_ptr);
  uint8_t * get_AES_output(void);
uint8_t * get_AES_pool(void);
#endif
