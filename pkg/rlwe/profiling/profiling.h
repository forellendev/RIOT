#ifndef PROFILING_H

#define PROFILING_H

void stopMeasurement(uint64_t* mean);
void startMeasurement(void);
void initMeasurement(void);

void printResult(uint64_t * mean, const char * s);
void printResultRAM(uint64_t * mean, int16_t ram, const char * s);

void generateRandomPolyTable_12289_512(uint16_t* retpoly);
void generateRandomPolyTable_7681_256(uint16_t* retpoly);
void generateRandomPolyTable_4093(uint16_t* retpoly, uint16_t n);
void generateRandomPolyTable_4096(uint16_t* retpoly, uint16_t n);


void do_measurement_7681_256(void);
void do_measurement_12289_512(void);
void do_measurement_4093(int n, const uint16_t * r2, const uint16_t * p,const uint16_t * a);
void do_measurement_karatsuba_4093(int n, const uint16_t * r2, const uint16_t * p,const uint16_t * a);
void do_measurement_karatsuba_4096(int n, const uint16_t * r2, const uint16_t * p,const uint16_t * a);

void do_measurement_kem_correction(void);

#define MAX_MEASUREMENT 100
//#define PRESCAL 1024
//#define PRESCAL 256
#define PRESCAL 1

#endif
