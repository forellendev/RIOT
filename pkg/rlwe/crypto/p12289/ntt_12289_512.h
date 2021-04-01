void encrypt_12289_512(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p);
void decrypt_12289_512(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2);

void get_gauss_poly_12289_512(uint16_t* retpoly, uint16_t add);

#define TEST 1
#if TEST==1
void ntt_CT_no_to_bo_incl_psi_12289_512(int16_t* a, const uint16_t* psi);
void ntt_CT_no_to_bo_incl_psi_12289_512_nolookup(int16_t* a, const uint16_t* psi);
void ntt_GS_bo_to_no_incl_invpsi_12289_512(int16_t* a, const uint16_t* psi);
void pw_psi_12289(uint16_t* p1, uint16_t start_val, uint16_t psi);
void pw_mul_flash_12289_512(uint16_t* polynomial, const uint16_t* addr);
void add_encode_12289_512(const uint8_t* msg, uint16_t* encodedpoly);
void decode_12289_512(uint16_t* cipherpoly, uint8_t* plaintext);
void ntt_GS_bo_to_no_7681_256(int16_t* a, const uint16_t* omega);
void ntt_CT_no_to_bo_7681_256(int16_t* a, const uint16_t* omega);
void ntt_CT_no_to_bo_incl_psi_12289_512_nolookup(int16_t* a, const uint16_t* psi);
void add_12289(uint16_t* p1, uint16_t* p2, uint16_t* res);
#endif
