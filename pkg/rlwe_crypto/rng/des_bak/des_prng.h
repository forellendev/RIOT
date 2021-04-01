void get_DES_block(uint8_t *buf);

//void init_pool(uint8_t * ptr);
// Initializes the randomness pool. Is given 16 bytes of random input
// (pointed to by ptr) and stores these bits into the static variables
// uint8_t pool_key[8] and uint8_t pool_plain[8]. Sets pool_cnt=0.

//void update_pool(uint8_t * ptr, uint8_t sel);
// Initializes the randomness pool. Is given 16 bytes of random input.
// These 16 bytes are used as input (key and plaintext) for the DES and the
// result is xored into pool_key[] if sel==0 and xored into pool_plain[] if
// sel==1. Sets pool_cnt=0.

uint32_t get_random_bits25(void);
// Returns a uint32_t filled with 25 random bits. In order to generate
// the bits, the HW-DES engine of the ATXMega is called with pool_key and
// pool_plain as input. The 4 least significant bytes of the DES output are
// then returned and the remaining 4 bytes are stored in pool_out (tracked
// by pool_cnt). After a DES operation pool_plain[8] is regarded as a 64
// bit unsigned vector and increased by one. In case get_random_bits25 is
// called while the pool still contains 4 random bytes, these bytes are
// returned without a call to the DES engine.

uint32_t get_random_bits32(void);

//void get_pool(uint8_t * ptr);
