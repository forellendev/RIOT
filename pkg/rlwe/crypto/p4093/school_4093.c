#include <inttypes.h>
#include <avr/pgmspace.h>

#include "school_4093.h"
#include "../sampler/cdf_sampler.h"
#include "math_asm_4093.h"


//for debuggig purpose some functions are non-static
#define IS_STATIC 

#define paramQ 4093







#ifndef CODESIZE
IS_STATIC void school_4093_without_flash(const uint16_t* first, const uint16_t* second, int16_t* res, const uint16_t paramN)
{
  uint32_t q,d;
    
  //init with 0
  for(int16_t i = 0; i<paramN; i++)
    {
      res[i] = 0;
    }
      
  for(int16_t i = 0;i < paramN; i++)
    {	
      for(int16_t j = 0; j<paramN; j++)
	{
	  q = i+j;
	  if(q>=paramN)
	    {
	      q -= paramN;
	    }
		  
	  //d =  (((uint32_t)first[i]) * second[j])%paramQ;
	  d = call_mulRed_asm_4093(first[i],second[j]);
		    
	  if((i+j) >= paramN)
	    {
	      res[q] -= d;
	      if(res[q] < 0)
		{
		  res[q] += paramQ;
		}
	    }
	  else
	    {
	      res[q] += d;
	      if(res[q] >= paramQ)
		{
		  res[q] -= paramQ;
		}
	    }
	}
    }
}
#endif






IS_STATIC void school_4093_192(const uint16_t* first, const uint16_t* second, uint16_t* result)
{
  //We reqire a RAM address as first coefficient and a Flash address as second
  const uint16_t paramN = 192;
	
  uint16_t res[paramN];

  //init with 0
  for(int16_t i = 0; i<paramN; i++)
    {
      res[i] = 0;
    }

  //polyMul_c_gauss_4093_192(first,second,res);

  polyMul_asm_4093_192(first,second,res);
	
    for(int16_t i = 0; i<paramN; i++)
  {
  result[i] = res[i];
    }
}


IS_STATIC void school_4093_256(const uint16_t* first, const uint16_t* second, uint16_t* result)
{	
  const uint16_t paramN = 256;
    
  uint16_t res[paramN];
      
  //init with 0
  for(int16_t i = 0; i<paramN; i++)
    {
      res[i] = 0;
    }
	
  polyMul_asm_4093_256(first,second,res);
	
  for(int16_t i = 0; i<paramN; i++)
    {
      result[i] = res[i];
    }
}


IS_STATIC void school_4093_320(const uint16_t* first, const uint16_t* second, uint16_t* result)
{
  // 	uint32_t q,d;
  // 	
  // 	const uint16_t paramN = 320;
  // 	
  // 	int16_t res[paramN];
  
  //init with 0
  // 	for(int16_t i = 0; i<paramN; i++)
  // 	{
  // 		res[i] = 0;
  // 	}
  // 
  // 	for(int16_t i = 0;i < paramN; i++)
  // 	{	
  // 		for(int16_t j = 0; j<paramN; j++)
  // 		{
  // 			q = i+j;
  // 			if(q>=paramN)
  // 			{
  // 				q -= paramN;
  // 			}
  // 
  // 			//d =  (((uint32_t)first[i]) * pgm_read_word(&second[j]))%paramQ;
  // 			d = call_mulRed_asm_4093(first[i],pgm_read_word(&second[j]));
  // 
  // 			if((i+j) >= paramN)
  // 			{
  // 				res[q] -= d;
  // 				if(res[q] < 0)
  // 				{
  // 					res[q] += paramQ;
  // 				}
  // 			}
  // 			else
  // 			{
  // 				res[q] += d;
  // 				if(res[q] >= paramQ)
  // 				{
  // 					res[q] -= paramQ;
  // 				}
  // 			}
  // 		}
  // 	
  // 	for(int16_t i = 0; i<paramN; i++)
  // 	{
  // 		result[i] = res[i];
  // }
  const uint16_t paramN = 320;
    
  uint16_t res[paramN];
      
  //init with 0
  for(int16_t i = 0; i<paramN; i++)
    {
      res[i] = 0;
    }
	
  polyMul_asm_4093_320(first,second,res);
	
  for(int16_t i = 0; i<paramN; i++)
    {
      result[i] = res[i];
    }
}



void encrypt_4093(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p, const uint16_t paramN)
{		
  get_gauss_poly_4093(c1,0, paramN);
    

  if(paramN == 192)
    {
      school_4093_192(c1, p, c2);
      school_4093_192(c1, a, c1);
    }

  

  if(paramN == 256)
    {
      school_4093_256(c1, p, c2);
      school_4093_256(c1, a, c1);
    }	



  if(paramN == 320)
    {
      school_4093_320(c1, p, c2);
      school_4093_320(c1, a, c1);
    }	

      
  get_gauss_poly_4093(c1,1, paramN);
  get_gauss_poly_4093(c2,1, paramN);
  
  add_encode_4093(plaintext, c2, paramN);
}


void decrypt_4093(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2, const uint16_t paramN)
{	

  if(paramN == 192)
    {
      school_4093_192(c1, r2, c1);
    }

  if(paramN == 256)
    {
      school_4093_256(c1, r2, c1);
    }	

  if(paramN == 320)
    {
      school_4093_320(c1, r2, c1);
    }

  
  //Add c2
  for(int i = 0; i<paramN; i++){
    c1[i] = (uint16_t) ((c1[i] + c2[i]));
    if (c1[i]>paramQ){
      c1[i]=c1[i]-paramQ;
    }
  }
  
  decode_4093(c1, plaintext, paramN);
}

IS_STATIC void add_encode_4093(const uint8_t* msg, uint16_t* encodedpoly, const uint16_t paramN)
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
IS_STATIC void decode_4093(uint16_t* cipherpoly, uint8_t* plaintext, const uint16_t paramN)
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

 /*
#ifndef CODESIZE
void generateKeys_4093(const uint16_t paramN)
{
  uint16_t a[paramN];
  int16_t p[paramN];
  uint16_t r2[paramN];
	
  //get_gauss_poly_4093(r1, 0, paramN);
  get_gauss_poly_4093(r2,0, paramN);
  generateRandomPolyTable_4093(a, paramN);
	    
  school_4093_without_flash(a, r2, p, paramN);
	      
  USARTsendStr(" \n############ R2: ", 18);
  for(int i = 0;i<paramN;i++)
    {
      //printf("%d, ", r2[i]);
    }
		  
  get_gauss_poly_4093(r2,0, paramN);
		    
  for(int i = 0; i<paramN; i++){
    p[i] = r2[i] - p[i];
    if(p[i] < 0)
      {
	p[i] += paramQ;
      }
  }
		
  USARTsendStr(" \n############ P: ", 17);
  for(int i = 0;i<paramN;i++)
    {
      //printf("%d, ", p[i]);
    }
  USARTsendStr(" \n############ A: ", 17);
  for(int i = 0;i<paramN;i++)
    {
      //printf("%d, ", a[i]);
   }
}
#endif
*/
