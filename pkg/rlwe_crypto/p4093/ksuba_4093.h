void encrypt_ksuba_4093(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p, const uint16_t paramN);
void decrypt_ksuba_4093(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2, const uint16_t paramN);

#define TEST 1
#if TEST == 1
void add_encode_ksuba_4093(const uint8_t* msg, uint16_t* encodedpoly, const uint16_t paramN);
void decode_ksuba_4093(uint16_t* cipherpoly, uint8_t* plaintext, const uint16_t paramN);
void set_max_recursion_stages(uint8_t val);
void karatsuba_4093_192(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands);
void karatsuba_4093_256(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands);
void karatsuba_4093_320(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands);
#endif
