#include <avr/io.h> 
#include <avr/pgmspace.h>

#include "../device/usart_driver.h"
#include "../device/clksys_driver.h"
#include "../device/measureRAM.h"
#include "../crypto/p4093/ksuba_4093.h"
#include "../crypto/p4096/ksuba_4096.h"
#include "../crypto/p4093/school_4093.h"
#include "../crypto/p12289/ntt_12289_512.h"
#include "../crypto/p7681/ntt_7681_256.h"
#include "../crypto/p12289/mm12289.h"
#include "../crypto/rng/avr_trng.h"
#include "../crypto/rng/aes_prng.h"
#include "../crypto/rng/des_bak/des_prng.h"


//include key files
#include "../keys/keypair_N_256_7681_1132.data"
#include "../keys/keypair_N_512_12289_1218.data"

#include "../keys/keypair_S_192_4093_8000.data"
#include "../keys/keypair_S_256_4093_8000.data"
#include "../keys/keypair_S_320_4093_8000.data"

#include "../keys/keypair_K_192_4096_8000.data"
#include "../keys/keypair_K_256_4096_8000.data"
#include "../keys/keypair_K_320_4096_8000.data"


void test_ksuba_school(uint16_t paramN);
void testEncryptionAndDecryption_Karatsuba_4093_192(void);
void testEncryptionAndDecryption_Karatsuba_4093_256(void);
void testEncryptionAndDecryption_Karatsuba_4093_320(void);
void testEncryptionAndDecryption_Karatsuba_4096_192(void);
void testEncryptionAndDecryption_Karatsuba_4096_256(void);
void testEncryptionAndDecryption_Karatsuba_4096_320(void);
void testEncryptionAndDecryption_School_4093_192(void);
void testEncryptionAndDecryption_School_4093_256(void);
void testEncryptionAndDecryption_School_4093_320(void);
void testEncryptionAndDecryption_NTT_7681_256(void);
void testEncryptionAndDecryption_NTT_12289_512(void);





void generateRandomPolyTable_12289_512(uint16_t* retpoly){
  for(int i = 0; i<512; i++)
    {
      retpoly[i] = get_random_bits25() % 12289;
    }  
}

void generateRandomPolyTable_4093(uint16_t* retpoly, uint16_t n){
  for(int i = 0; i<n; i++)
    {
      retpoly[i] = get_random_bits25() % 4093;
    }  
}


// void testbitrev(void);
// void testpwmul(void);
// void testEncodingAndDecoding(void);
// void testinterleavedntt(void);
// void check_bitrev(uint16_t* in);
// void check_pw_mul(uint16_t * first, uint16_t* second, uint16_t* res);
// void check_encode(uint8_t* msg, uint16_t* encodedpoly);
// void check_decode(uint16_t* cipherpoly, uint8_t* plaintext);
// void check_mul(int16_t* first, int16_t* second, int16_t* res);

static int mod_errors=0;
static int mod_tests=0;

void test_passed(void){
	printf("passed.\n\r");
}

void test_failed(void){
  printf("FAILED.\n\r");
  mod_errors++;
}

void test_start(char* str){
  printf("%s", str);
  mod_tests++;
}

void test_end(void){
  printf("Finished testing.\n\r");
  printf("Passed: %d/%d, FAILED: %d \n\r",mod_tests-mod_errors, mod_tests, mod_errors);
  printf("\n\r");
  printf("\n\r");
  printf("\n\r");
}


int main(void ){

  // Set frequency to 32 MHz
  CLKSYS_Enable( OSC_RC32MEN_bm );
  do {} while ( CLKSYS_IsReady( OSC_RC32MRDY_bm ) == 0 );
  CLKSYS_Main_ClockSource_Select( CLK_SCLKSEL_RC32M_gc );
  CLKSYS_Disable( OSC_RC2MEN_bm | OSC_RC32KEN_bm );
	
  USARTinit();
  avr_trng_init();

  printf("\n");
  
  //Currently not working - why?
  //printf("Ksuba RAM\n");
  //test_ksuba_ram();
  //test_ksuba_school(192);
  //test_ksuba_school(256);
  //test_ksuba_school(320);
  //printf("dadsadsadsad\n");

/*
	uint16_t a = 1234;
	uint16_t b = 6789;
	printf("Result of %d * %d: %u...expected: %u...\n\n", a, b, mm12289(a,b), (((uint32_t)a)*b)%12289);

	a = 1234;
	b = 9999;
	printf("Result of %d * %d: %u...expected: %u...\n\n", a, b, mm12289(a,b), (((uint32_t)a)*b)%12289);

	a = 12217;
	b = 5000;
	printf("Result of %d * %d: %u...expected: %u...\n\n", a, b, mm12289(a,b), (((uint32_t)a)*b)%12289);

	a = 2713;
	b = 1001;
	printf("Result of %d * %d: %u...expected: %u...\n\n", a, b, mm12289(a,b), (((uint32_t)a)*b)%12289);
*/
/*
	uint16_t a=6789;
	uint16_t b;

	for(b=1;b<12289;b++)
	{
		if(mm12289(a,b) != (((uint32_t)a)*b)%12289)
		{
			printf("Result of %d * %d: %u...expected: %u...\n\n", a, b, mm12289(a,b), (((uint32_t)a)*b)%12289);
			while(1);
		}
	}
	printf("Success!\n");

	while(1);
*/


  testEncryptionAndDecryption_NTT_7681_256();
  testEncryptionAndDecryption_NTT_12289_512();
  testEncryptionAndDecryption_School_4093_192();
  testEncryptionAndDecryption_School_4093_256();
  testEncryptionAndDecryption_School_4093_320();

  set_max_recursion_stages(5);
  set_max_recursion_stages4096(5);

  for(int i = 0; i<1;i++)
  {
  	testEncryptionAndDecryption_Karatsuba_4093_192();
  	testEncryptionAndDecryption_Karatsuba_4093_256();
  	testEncryptionAndDecryption_Karatsuba_4093_320();
  }

  for(int i = 0; i<1;i++)
  {
  	testEncryptionAndDecryption_Karatsuba_4096_192();
  	testEncryptionAndDecryption_Karatsuba_4096_256();
  	testEncryptionAndDecryption_Karatsuba_4096_320();
  }



/*
  // testing asm multiplier
  printf("%d * %d = %d (expected: %d)\n", -5, 1111, call_mulRed_asm_4093(-5, 1111), ((-5*1111)%4093) + 4093);
  printf("%d * %d = %d (expected: %d)\n", 5, 1111, call_mulRed_asm_4093(5, 1111), ((5*1111)%4093));
  printf("%d * %d = %d (expected: %d)\n", -10, 1234, call_mulRed_asm_4093(-10, 1234), ((-10*1234)%4093) + 4093);
  printf("%d * %d = %d (expected: %d)\n", 10, 1234, call_mulRed_asm_4093(10, 1234), ((10*1234)%4093));
  printf("%d * %d = %d (expected: %d)\n", -27, 3234, call_mulRed_asm_4093(-27, 3234), ((-27*3234L)%4093) + 4093);
  printf("%d * %d = %d (expected: %d)\n", 27, 3234, call_mulRed_asm_4093(27, 3234), ((27*3234L)%4093));
  printf("%d * %d = %d (expected: %d)\n", -33, 4001, call_mulRed_asm_4093(-33, 4001), ((-33*4001L)%4093) + 4093);
  printf("%d * %d = %d (expected: %d)\n", 33, 4001, call_mulRed_asm_4093(33, 4001), ((33*4001L)%4093));
*/	

  test_end();

  printf("\n");
  fflush(stdout);
  printf("\n");

  for(int i=0; i<500;i++){
    printf(" ");
  }

}


void test_ksuba_school(uint16_t paramN)
{
  uint16_t resksuba[paramN];
  uint16_t resschoolbook[paramN];

  uint16_t testpoly[paramN];
	
  set_max_recursion_stages(5);
	
  if(paramN == 192)
    {
      test_start("Testing Karatsuba and schoolbook multiplication with n = 192... ");
    }
  else if(paramN == 256)
    {
      test_start("Testing Karatsuba and schoolbook multiplication with n = 256... ");
    }
  else if(paramN == 320)
    {
      test_start("Testing Karatsuba and schoolbook multiplication with n = 320... ");
    }	
	
  for(int j = 0; j < 5; j++)
    {
      generateRandomPolyTable_4093(testpoly,paramN);

      // prvKeyR2_4093_320 -> flash adress is required, content doesnt matter
      if(paramN == 192)
	{
	  karatsuba_4093_192(testpoly, prvKeyR2_4093_320, resksuba,0);
	  school_4093_192(testpoly, prvKeyR2_4093_320, resschoolbook);
					
	  for(int i = 0; i<paramN;i++){
	    if(resksuba[i] != resschoolbook[i]){
	      test_failed();
	      return;
	    }
	  }
	}

      else if(paramN == 256)
	{
	  karatsuba_4093_256(testpoly, prvKeyR2_4093_320, resksuba,0);
	  school_4093_256(testpoly, prvKeyR2_4093_320, resschoolbook);
			
	  for(int i = 0; i<paramN;i++){
	    if(resksuba[i] != resschoolbook[i]){
	      test_failed();
	      return;
	    }
	  }
	}
		
      else if(paramN == 320)
	{
	  karatsuba_4093_320(testpoly, prvKeyR2_4093_320, resksuba,0);
	  school_4093_320(testpoly, prvKeyR2_4093_320, resschoolbook);
			
	  for(int i = 0; i<paramN;i++){
	    if(resksuba[i] != resschoolbook[i]){
	      test_failed();
	      return;
	    }
	  }
	}
    }
	
  test_passed();
}

// 
// void testpwmul(void)
// {
// 	struct polynomial testpoly;
// 	struct polynomial testpoly2;
// 	
// 	uint16_t res[nP];
// 	uint16_t res2[nP];
// 
// 	test_start("Testing pointwise multiplication... ");
// 	
// 	for(int j = 0; j<5; j++)
//     {
// 		generateRandomPolyTable(testpoly.coeffs);
// 		generateRandomPolyTable(testpoly2.coeffs);
// 
// 		pw_mul(testpoly.coeffs,testpoly2.coeffs,res);
// 		check_pw_mul(testpoly.coeffs,testpoly2.coeffs,res2);
// 	
// 		for(int i = 0; i<nP;i++)
// 		{
// 			if(res[i] != res2[i])
// 			{
// 				test_failed();
// 				return;
// 			}
// 		}
//     }
// 	
// 	test_passed();
// }
// 
// void testbitrev(void)
// {
// 	struct polynomial testpoly;
// 	struct polynomial testpoly2;
// 	
// 	
// 	test_start("Testing bitrev... ");
// 	
// 	for(int j = 0; j<5; j++)
//     {
// 		generateRandomPolyTable(testpoly.coeffs);
// 		
// 		for(int i = 0; i<nP;i++)
// 		{
// 		  testpoly2.coeffs[i] = testpoly.coeffs[i];
// 		}
// 		
// 		 bitrev(testpoly.coeffs);
// 		 check_bitrev(testpoly2.coeffs);
// 	
// 		for(int i = 0; i<nP;i++)
// 		{
// 			if(testpoly.coeffs[i] != testpoly2.coeffs[i])
// 			{
// 				test_failed();
// 				return;
// 			}
// 		}
//     }
// 	
//   test_passed();
// }

	

void testEncryptionAndDecryption_NTT_7681_256(void)
{	
  // Ciphertext
  uint16_t c1[256];
  uint16_t c2[256];
	
  uint8_t plaintext[256/8+1] = "!plaintexttest!!!plaintexttest!!";
  uint8_t check[256/8+1] = "!plaintexttest!!!plaintexttest!!";

	
  test_start("Testing Encryption and Decryption (NTT, n = 256, q = 7681)... ");
	
  encrypt_7681_256(plaintext, c1, c2, pubKeyA_7681_256, pubKeyP_7681_256);
				
  for(int i = 0; i<256/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_7681_256(plaintext, c1, c2, prvKeyR2_7681_256);
	
  for(int i = 0; i<256/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }


  // plaintext changed, test should fail now
  plaintext[0]++;

  encrypt_7681_256(plaintext, c1, c2, pubKeyA_7681_256, pubKeyP_7681_256);
				
  for(int i = 0; i<256/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_7681_256(plaintext, c1, c2, prvKeyR2_7681_256);
	
  for(int i = 0; i<256/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_passed();
	  plaintext[i] = check[i];
	  return;	
	}
    } 

  test_failed();
	
  //################################
}
	
void testEncryptionAndDecryption_NTT_12289_512(void)
{
  // Ciphertext
  uint16_t c1[512];
  uint16_t c2[512];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1]     = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (NTT, n = 512, q = 12289)... ");
	
  encrypt_12289_512(plaintext, c1, c2, pubKeyA_12289_512, pubKeyP_12289_512);
				
  for(int i = 0; i<512/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_12289_512(plaintext, c1, c2, prvKeyR2_12289_512);
	
  for(int i = 0; i<512/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_Karatsuba_4093_192(void)
{
  // Ciphertext
  uint16_t c1[192];
  uint16_t c2[192];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 192, q = 4093)... ");
	
  encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_192, pubKeyP_4093_192,192);
				
  for(int i = 0; i<192/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_192,192);
	
  for(int i = 0; i<192/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_Karatsuba_4093_256(void)
{	
  // Ciphertext
  uint16_t c1[256];
  uint16_t c2[256];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1] = "!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 256, q = 4093)... ");
	
  encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_256, pubKeyP_4093_256,256);
				
  for(int i = 0; i<256/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_256,256);
	
  for(int i = 0; i<256/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_Karatsuba_4093_320(void)
{	
  // Ciphertext
  uint16_t c1[320];
  uint16_t c2[320];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 320, q = 4093)... ");
	
  encrypt_ksuba_4093(plaintext, c1, c2, pubKeyA_4093_320, pubKeyP_4093_320,320);
				
  for(int i = 0; i<320/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4093(plaintext, c1, c2, prvKeyR2_4093_320,320);
	
  for(int i = 0; i<320/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}

void testEncryptionAndDecryption_Karatsuba_4096_192(void)
{
  // Ciphertext
  uint16_t c1[192];
  uint16_t c2[192];
	
  uint8_t plaintext[192/8+1] = "!plaintexttest!!!plainte";
  uint8_t check[192/8+1] = "!plaintexttest!!!plainte";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 192, q = 4096)... ");
	
  encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4096_192, pubKeyP_4096_192,192);
				
  for(int i = 0; i<192/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4096_192,192);

  for(int i = 0; i<192/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_Karatsuba_4096_256(void)
{	
  // Ciphertext
  uint16_t c1[256];
  uint16_t c2[256];
	
  uint8_t plaintext[256/8+1] = "!plaintexttest!!!plaintexttest!!";
  uint8_t check[256/8+1] = "!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 256, q = 4096)... ");
	
  encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4096_256, pubKeyP_4096_256,256);
				
  for(int i = 0; i<256/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4096_256,256);
	
  for(int i = 0; i<256/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_Karatsuba_4096_320(void)
{	
  // Ciphertext
  uint16_t c1[320];
  uint16_t c2[320];
	
  uint8_t plaintext[320/8+1] = "!plaintexttest!!!plaintexttest!!!plainte";
  uint8_t check[320/8+1] = "!plaintexttest!!!plaintexttest!!!plainte";
	
  test_start("Testing Encryption and Decryption (Karatsuba, n = 320, q = 4096)... ");
	
  encrypt_ksuba_4096(plaintext, c1, c2, pubKeyA_4096_320, pubKeyP_4096_320,320);
				
  for(int i = 0; i<320/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_ksuba_4096(plaintext, c1, c2, prvKeyR2_4096_320,320);
	
  for(int i = 0; i<320/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_School_4093_192(void)
{
  // Ciphertext
  uint16_t c1[192];
  uint16_t c2[192];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Schoolbook, n = 192, q = 4093)... ");
	
  encrypt_4093(plaintext, c1, c2, pubKeyA_4093_192, pubKeyP_4093_192,192);
				
  for(int i = 0; i<192/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_192,192);
	
  for(int i = 0; i<192/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_School_4093_256(void)
{
  // Ciphertext
  uint16_t c1[256];
  uint16_t c2[256];
	
  uint8_t plaintext[256/8+1] = "!plaintexttest!!!plaintexttest!!";
  uint8_t check[256/8+1] = "!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Schoolbook, n = 256, q = 4093)... ");
	
  encrypt_4093(plaintext, c1, c2, pubKeyA_4093_256, pubKeyP_4093_256,256);
				
  for(int i = 0; i<256/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_256,256);
	
  for(int i = 0; i<256/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}
	
void testEncryptionAndDecryption_School_4093_320(void)
{
  // Ciphertext
  uint16_t c1[320];
  uint16_t c2[320];
	
  uint8_t plaintext[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
  uint8_t check[512/8+1] = "!plaintexttest!!!plaintexttest!!!plaintexttest!!!plaintexttest!!";
	
  test_start("Testing Encryption and Decryption (Schoolbook, n = 320, q = 4093)... ");
	
  encrypt_4093(plaintext, c1, c2, pubKeyA_4093_320, pubKeyP_4093_320,320);
				
  for(int i = 0; i<320/8; i++)
    {
      plaintext[i] = 0;
    }

  decrypt_4093(plaintext, c1, c2, prvKeyR2_4093_320,320);
	
  for(int i = 0; i<320/8; i++)
    {
      if(plaintext[i] != check[i])
	{
	  test_failed();
	  plaintext[i] = check[i];
	  return;	
	}
    }
	
  test_passed();
	
  //################################
}

