#include <inttypes.h>
#include <avr/pgmspace.h>
#include "ksuba_4096.h"
#include "sampler_4096.h"

//for debuggig purpose some functions are non-static
#define IS_STATIC 

#define paramQ 4096

uint8_t max_recursion_stages4096 = 255;

void set_max_recursion_stages4096(uint8_t val)
{
  max_recursion_stages4096 = val;
}

static uint16_t mulRed_4096(uint16_t a, uint16_t b)
{
	return call_mulRed_asm_4096(a, b);
}

IS_STATIC void reduce4096(int16_t  * input, int16_t * output, uint16_t paramN)
{
  for(int i = 0; i<paramN;i++)
    {
      output[i] = input[i] - input[i+paramN];

      if(output[i] < 0)
	{
	  output[i] += paramQ;
	}
    }
}

/*
 *	w = D2*x^2n + [D1-D2-D0]*x^n + D0.
 *	D0 = a0�b0
 *	D1 = (a0+a1) * (b0+b1)
 *	D2 = a1*b1
 *
 *	size of a - degree
 *	size of b - degree
 *	size of res - 2*degree
 */
IS_STATIC void karatsuba_recursive4096(const uint16_t* a, const uint16_t* b, int16_t* res, uint16_t degree, uint8_t recursion_stage)
{
  uint16_t halfdegree = degree>>1;
  int16_t temp[degree]; // used to store D2, D0, sums

  //schoolbook multiplication if !2|degree (paramN not always a power of 2)
  if(degree%2 == 1 || recursion_stage == max_recursion_stages4096)
    {
      for(uint16_t i = 0; i<degree*2;i++)
	{
	  res[i] = 0;
	}			
      for(uint16_t i = 0; i<degree;i++)
	{
	  for(uint16_t j = 0; j<degree;j++)
	    {
	      res[i+j] += mulRed_4096(a[i],b[j]);
	      res[i+j] &= 0xFFF;
	    }
	}
      return;
    }
	
  // compute D1 = (x0+x1) * (y0+y1)
  for(uint8_t i = 0; i<halfdegree;i++)
    {
      temp[i] = (a[i] + a[i+halfdegree]) & 0xFFF;
		
      temp[i+halfdegree] = (b[i] + b[i+halfdegree]) & 0xFFF;
    }		
  karatsuba_recursive4096((uint16_t*)temp,(uint16_t*)&temp[halfdegree],res,halfdegree,recursion_stage+1);
	
  // compute D2 = x1 * y1 and store it in result
  karatsuba_recursive4096(&a[halfdegree],&b[halfdegree],&res[degree],halfdegree,recursion_stage+1);	
	
  // compute D1 - D2
  for(uint16_t i = 0; i<degree;i++)
    {
      res[i] -= res[i+degree];
      if(res[i] < 0)
	{
	  res[i] += paramQ;
	}
    }
	
  // compute D0 = x0 * y0
  karatsuba_recursive4096(a,b,temp,halfdegree,recursion_stage+1);
	
  // compute (D1 - D2) - D0
  for(uint16_t i = 0; i<degree;i++)
    {
      res[i] -= temp[i];
      if(res[i] < 0)
	{
	  res[i] += paramQ;
	}
    }	
	
  // store D1 - D2 - D0 in result	
  for(uint16_t i = halfdegree; i<degree;i++)
    {	
      res[i+halfdegree] += res[i];
      res[i+halfdegree] &= 0xFFF;	
    }	
  for(uint16_t i = 0; i<halfdegree;i++)
    {	
      res[i+halfdegree] = res[i];
    }		

  // store D0 in result
  for(uint16_t i = 0; i<halfdegree;i++)
    {	
      res[i] = temp[i];
    }
	
  for(uint16_t i = halfdegree; i<degree;i++)
    {	
      res[i] += temp[i];
      res[i] &= 0xFFF;	
    }		
}


IS_STATIC void karatsuba_4096_192(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands)
{
  int16_t  tmp[2*192];
  uint16_t b[192];
	
  for(int i = 0; i<192;i++)
    {
      b[i] = pgm_read_word(&second[i]);	
    }

  if(!swap_operands)
  {
  	karatsuba_recursive4096((uint16_t*)first, (uint16_t*)b, tmp, 192,0);
  }
  else
  {
	karatsuba_recursive4096((uint16_t*)b, (uint16_t*)first, tmp, 192,0);
  }

  reduce4096(tmp, (int16_t*)result, 192);
}


IS_STATIC void karatsuba_4096_noflash(const uint16_t* first, const uint16_t* second, uint16_t * result, uint16_t paramN)
{
  int16_t  tmp[2*paramN];

  karatsuba_recursive4096(first, second, tmp, paramN,0);

  reduce4096(tmp, (int16_t*)result, paramN);
}


IS_STATIC void karatsuba_4096_256(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands)
{
  int16_t  tmp[2*256];
  uint16_t b[256];
	
  for(int i = 0; i<256;i++)
    {
      b[i] = pgm_read_word(&second[i]);		
    }

  if(!swap_operands)
  {
  	karatsuba_recursive4096((uint16_t*)first, (uint16_t*)b, tmp, 256,0);
  }
  else
  {
	karatsuba_recursive4096((uint16_t*)b, (uint16_t*)first, tmp, 256,0);
  }

  reduce4096(tmp, (int16_t*)result, 256);
}




IS_STATIC void karatsuba_4096_320(const uint16_t* first, const uint16_t* second, uint16_t * result, int swap_operands)
{
  int16_t  tmp[2*320];
	
  int16_t b[320];
	
  for(int i = 0; i<320;i++)
  {
      b[i] = pgm_read_word(&second[i]);		
  }

  if(!swap_operands)
  {
  	karatsuba_recursive4096((uint16_t*)first, (uint16_t*)b, tmp, 320,0);
  }
  else
  {
	karatsuba_recursive4096((uint16_t*)b, (uint16_t*)first, tmp, 320,0);
  }

  reduce4096(tmp, (int16_t*)result, 320);
}



void encrypt_ksuba_4096(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p, const uint16_t paramN)
{	
  //uint16_t temp[paramN];
	
  get_gauss_poly_4096_posneg(c1,0, paramN);


  if(paramN == 192)
    {
      karatsuba_4096_192(c1, p, c2,0);
      karatsuba_4096_192(c1, a, c1,0);
    }


  if(paramN == 256)
    {
      karatsuba_4096_256(c1, p, c2,0);
      karatsuba_4096_256(c1, a, c1,0);
    }	


  if(paramN == 320)
    {
      karatsuba_4096_320(c1, p, c2,0);
      karatsuba_4096_320(c1, a, c1,0);
    }	

  get_gauss_poly_4096(c1,1, paramN);
  get_gauss_poly_4096(c2,1, paramN);

  
  add_encode_ksuba_4096(plaintext, c2, paramN);
}


void decrypt_ksuba_4096(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2, const uint16_t paramN)
{	

  if(paramN == 192)
    {
      karatsuba_4096_192(c1, r2, c1,1);
    }

  if(paramN == 256)
    {
      karatsuba_4096_256(c1, r2, c1,1);
    }

  if(paramN == 320)
    {
      karatsuba_4096_320(c1, r2, c1,1);
    }

  //Add c2
  for(int i = 0; i<paramN; i++){
    if ((c1[i] + c2[i]) >  paramQ){
      c1[i] = (uint16_t) ((c1[i] + c2[i])) - paramQ ;//% paramQ;
    }else{
      c1[i] = (uint16_t) ((c1[i] + c2[i]));
    }
  }
  
  decode_ksuba_4096(c1, plaintext, paramN);
}

IS_STATIC void add_encode_ksuba_4096(const uint8_t* msg, uint16_t* encodedpoly, const uint16_t paramN)
{
  uint16_t i = 0;
			
  do 
    {		
      //encodedpoly[i] = (msg[(int)(i>>3)] & (1<<(i%8))? ((encodedpoly[i]+paramQ/2)%paramQ) : encodedpoly[i]);

      if (msg[(i>>3)] & (1<<(i%8))){
	encodedpoly[i] = encodedpoly[i]+paramQ/2;
	if (encodedpoly[i]>paramQ){
	  encodedpoly[i]=encodedpoly[i]-paramQ;
	}
      }
	
      if(i == (paramN)-1)
	break;
			
      i++;
    } while (1);
}



// decoding
IS_STATIC void decode_ksuba_4096(uint16_t* cipherpoly, uint8_t* plaintext, const uint16_t paramN)
{		
  uint16_t i = 0;
		
  do 
    {		
      // Decode(m) = 1 if m between q/4,-q/4, 0 else
      if((cipherpoly[i] < paramQ>>2) || (cipherpoly[i] >= 3*paramQ>>2))
	{
	  plaintext[i >> 3] = (plaintext[i >> 3] | (0 << (i%8)));
	}
      else
	{
	  plaintext[i >> 3] = (plaintext[i >> 3] | (1 << (i%8)));
	}
		
      if(i == (paramN)-1)
	break;
			
      i++;
    } while (1);
}
