void encrypt_4093(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p, const uint16_t paramN);
void decrypt_4093(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2, const uint16_t paramN);

void generateKeys_4093(const uint16_t paramN);
void get_gauss_poly_4093(uint16_t* retpoly, uint16_t add, const uint16_t paramN);


#define TEST 1
#if TEST == 1
void add_encode_4093(const uint8_t* msg, uint16_t* encodedpoly, const uint16_t paramN);
void decode_4093(uint16_t* cipherpoly, uint8_t* plaintext, const uint16_t paramN);
void school_4093_192(const uint16_t* first, const uint16_t* second, uint16_t* result);
void school_4093_256(const uint16_t* first, const uint16_t* second, uint16_t* result);
void school_4093_320(const uint16_t* first, const uint16_t* second, uint16_t* result);
#endif
