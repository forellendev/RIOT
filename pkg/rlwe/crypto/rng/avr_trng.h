void avr_trng_init(void);
//Initialize

uint32_t get_trnd_adc(void);
// Returns 32 bits of randomness. Each bit is sampled by evaluating the
// ADC with maximum gain at the least significant bit. This results in more
// or less true random numbers.