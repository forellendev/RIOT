#include <inttypes.h>
#include <avr/pgmspace.h> 

#include "param_12289_512.h"
#include "ntt_12289_512.h"
#include "../sampler/cdf_sampler.h"
#include "../rng/aes_prng.h"
#include "ntt_12289_512_const.data"
#include "mm12289.h"


#include "cdf_table_12289_1218.data"


#define paramQ 12289
#define paramN 512
#define paramS 11.32
#define paramL 64 // byte length of message

//---- Here starts the ntt/arithemtic part ------

//for debuggig purpose some functions are non-static
#define IS_STATIC 



#define MAX_BUF 48

void get_gauss_poly_12289_512(uint16_t* retpoly, uint16_t add) {
  //Generates or adds Gaussian noise to an array
  int8_t ret;
  uint16_t val=0;

  uint8_t rand_buf[MAX_BUF];
  uint8_t rand_consumed = 254;
  uint8_t rand_consumed_func= 0;

  for (uint16_t i = 0; i< 512; i++){

    //General idea: First we sample some randomness into a buffer
    //Then we run the sampler and track how much random bytes have been used already
    //We refill the buffer in case we encounter that it does not contain enough randomness to sustain a worst case
    //run of the sampler. Thus the 13 as 13*8 = 104 and we have precision 100.

    if (rand_consumed > (MAX_BUF-13)){
      for(uint16_t j = 0; j < MAX_BUF/16; j++){
	//AES writes 128 bit = 16 byte into the buffer
	next_block_ptr(rand_buf+16*j);
      }
      rand_consumed=0;
    }

    ret = sample_gauss(CDF_ROWS, CDF_COLUMNS, &cdf_table_12289_1218[0][0],  (uint8_t*) rand_buf+rand_consumed, (uint8_t*) &rand_consumed_func);
    rand_consumed += rand_consumed_func;
   
    val = ret;
    
    if(add == 1){
      if ( (retpoly[i]+val) >= paramQ){
	retpoly[i] = retpoly[i]+val - paramQ;
      }
      else if( (retpoly[i]+val) < 0)
      {
	retpoly[i] = retpoly[i]+val + paramQ;
      }
      else{
	retpoly[i] = retpoly[i]+val;
      }

    }else{
      retpoly[i] = val;
    }
  }


}

void first_stage_GS_12289_512(int16_t* a, const uint16_t* psi)
{
	uint16_t j = 0, jTwiddle = paramN/2;
	while(j < paramN - 1)
	{
		uint16_t W = pgm_read_word(&psi[jTwiddle]);

		int16_t temp = a[j];
		a[j] = temp + a[j + 1];
		if(a[j] >= paramQ)
			a[j] -= paramQ;

		temp = temp - a[j + 1];
		if(temp < 0)
			temp += paramQ;

		a[j + 1] = mm12289(W, temp);

		jTwiddle++;
		j = j + 2;
	}
}

void last_stage_GS_12289_512(int16_t* a, const uint16_t* psi)
{
	uint16_t distance = paramN/2;

	uint16_t jFirst;
	uint16_t W = pgm_read_word(&psi[1]);

	for(jFirst = 0; jFirst < paramN/2;jFirst++)
	{
		uint16_t j = jFirst;
		int16_t temp = a[j];
		a[j] = temp + a[j + distance];
		if(a[j] >= paramQ)
			a[j] -= paramQ;

		temp = temp - a[j + distance];
		if(temp < 0)
			temp += paramQ;

		a[j + distance] = mm12289(W, temp);
	}
}

void ntt_GS_bo_to_no_incl_invpsi_12289_512(int16_t* a, const uint16_t* psi)
{
	uint16_t numOfProblems = 1, problemSize = paramN/2, distance = 1;
	
	first_stage_GS_12289_512(a,psi);

	numOfProblems = numOfProblems * 2;
	problemSize = problemSize/2;
	distance = distance * 2;

	while(problemSize > 1)
	{
		uint16_t i;
		uint16_t offset = 0;

		for(i = 0; i < problemSize;i++)
		{
			uint16_t j;			
			uint16_t W = pgm_read_word(&psi[problemSize + i]);			

			for(j=offset;j<offset+numOfProblems;j++)
			{
				int16_t temp = a[j];
				a[j] = temp + a[j + distance];
				if(a[j] >= paramQ)
					a[j] -= paramQ;

				temp = temp - a[j + distance];
				if(temp < 0)
					temp += paramQ;

				a[j + distance] = mm12289(W, temp);
			}

			offset += 2*numOfProblems;			
		}

		numOfProblems = numOfProblems * 2;
		problemSize = problemSize/2;
		distance = distance * 2;
	}

	last_stage_GS_12289_512(a, psi);
}

void first_stage_CT_12289_512(int16_t * a)
{
	uint16_t distance=paramN/2;

	uint16_t j;
			
	for(j=0; j<paramN/2; j++)
	{
		int16_t temp;

		if(a[j + distance] < 0)
		{ 
			if(a[j + distance] < -15)
			{
				temp = mm12289(10810, (-1) * a[j + distance]);
			}
			else
			{
				temp = pgm_read_word(&omegamultiples_12289_512[(-1) * a[j + distance]]);
			}
			temp = ((-1) * temp) + paramQ;
		}
		else
		{
			if(a[j + distance] > 15)
			{
				temp = mm12289(10810, a[j + distance]);
			}
			else
			{
				temp = pgm_read_word(&omegamultiples_12289_512[a[j + distance]]);
			}
		}			

		a[j + distance] = a[j] - temp;
		if(a[j + distance] < 0)
			a[j+distance] += paramQ;
		if(a[j + distance] < 0)
			a[j+distance] += paramQ;

		a[j] = a[j] + temp;
		if(a[j] >= paramQ)
			a[j] -= paramQ;
		if(a[j] < 0)
			a[j] += paramQ;
	}
}

void last_stage_CT_12289_512(int16_t * a, const uint16_t* psi)
{
	uint16_t k, j;
	for(k=0;k<paramN/2;k++)
	{
		uint16_t W = pgm_read_word(&psi[paramN/2 + k]);

		j = 2 * k;		

		uint16_t temp;
		temp = mm12289(W, a[j + 1]);
		a[j + 1] = a[j] - temp;
		if(a[j + 1] < 0)
			a[j+1] += paramQ;

		a[j] = a[j] + temp;
		if(a[j] >= paramQ)
			a[j] -= paramQ;
	}
}

void ntt_CT_no_to_bo_incl_psi_12289_512_nolookup(int16_t* a, const uint16_t* psi)
{
	uint16_t pairsInGroup=paramN/2, numOfGroups=1, distance=paramN/2;

	while(numOfGroups < paramN/2)
	{
		uint16_t k, j;
		for(k=0;k<numOfGroups;k++)
		{
			uint16_t jFirst, jLast, W;
			jFirst = 2 * k * pairsInGroup;
			jLast = jFirst + pairsInGroup -1;

			W = pgm_read_word(&psi[numOfGroups + k]);
			
			for(j=jFirst; j<=jLast; j++)
			{
				int16_t temp;
				temp = mm12289(W, a[j + distance]);
				a[j + distance] = a[j] - temp;
				if(a[j + distance] < 0)
					a[j+distance] += paramQ;

				a[j] = (a[j] + temp);
				if(a[j] >= paramQ)
					a[j] -= paramQ;
			}
		}
		pairsInGroup /= 2;
		numOfGroups *= 2;
		distance /= 2;
	}

	last_stage_CT_12289_512(a, psi);
}

void ntt_CT_no_to_bo_incl_psi_12289_512(int16_t* a, const uint16_t* psi)
{
	uint16_t pairsInGroup=paramN/2, numOfGroups=1, distance=paramN/2;

	first_stage_CT_12289_512(a);

        pairsInGroup /= 2;
	numOfGroups *= 2;
	distance /= 2;

	while(numOfGroups < paramN/2)
	{
		uint16_t k, j;
		for(k=0;k<numOfGroups;k++)
		{
			uint16_t jFirst, jLast, W;
			jFirst = 2 * k * pairsInGroup;
			jLast = jFirst + pairsInGroup -1;

			W = pgm_read_word(&psi[numOfGroups + k]);
			
			for(j=jFirst; j<=jLast; j++)
			{
				int16_t temp;
				temp = mm12289(W, a[j + distance]);
				a[j + distance] = a[j] - temp;
				if(a[j + distance] < 0)
					a[j+distance] += paramQ;

				a[j] = (a[j] + temp);
				if(a[j] >= paramQ)
					a[j] -= paramQ;
			}
		}
		pairsInGroup /= 2;
		numOfGroups *= 2;
		distance /= 2;
	}

	last_stage_CT_12289_512(a, psi);
}


void pw_psi_12289(uint16_t* p1, uint16_t start_val, uint16_t psi){
  for(uint16_t i = 0; i<paramN; i++){
    p1[i] = mm12289(p1[i], start_val);
    start_val = mm12289(start_val, psi);
  }
}

IS_STATIC void pw_mul_flash_12289_512(uint16_t* polynomial, const uint16_t* addr){
  uint16_t temp;
  for(int i = 0; i<paramN; i++){
    temp = pgm_read_word(&addr[i]);    
    polynomial[i] = mm12289(temp, polynomial[i]);
  }
}

IS_STATIC void add_12289(uint16_t* p1, uint16_t* p2, uint16_t* res){
  for(int i = 0; i<paramN; i++){
    res[i] = (uint16_t) ((p1[i] + p2[i]));
    res[i] = mod12289(res[i]);
  }
}




void encrypt_12289_512(const uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* a, const uint16_t* p)
{	
  get_gauss_poly_12289_512(c1,0); //e1 stored in c1
  get_gauss_poly_12289_512(c2,0); //e2 stored in c2

  //Transform e1, e2
  ntt_CT_no_to_bo_incl_psi_12289_512((int16_t*)c1, psibitrev_12289_512);
  ntt_CT_no_to_bo_incl_psi_12289_512((int16_t*)c2, psibitrev_12289_512);

  //Pointwise multiplication with a and p, addition of e2
  for(uint16_t i = 0; i<paramN; i++){
    uint16_t temp = c1[i];

    c1[i] = mm12289(temp, pgm_read_word(&a[i]));

    if ( (c1[i]+c2[i]) >= paramQ){
	c1[i] = c1[i]+c2[i] - paramQ;
    }
    else{
	c1[i] = c1[i]+c2[i];
    }

    c2[i] = mm12289(temp, pgm_read_word(&p[i]));
  }

  //inverse transform
  ntt_GS_bo_to_no_incl_invpsi_12289_512((int16_t*)c2, omegainvbitrev_12289_512);

  get_gauss_poly_12289_512(c2,1); //add e3
  
  add_encode_12289_512(plaintext, c2);
}



void decrypt_12289_512(uint8_t* plaintext, uint16_t* c1, uint16_t* c2, const uint16_t* r2)
{	
  //Pointwise multiplication with r2
  pw_mul_flash_12289_512(c1, r2);
  
  //inverse transform c1
  ntt_GS_bo_to_no_incl_invpsi_12289_512((int16_t*)c1, omegainvbitrev_12289_512);
  
  //Add c2
  add_12289(c1,c2,c1);
  
  decode_12289_512(c1, plaintext);
}

IS_STATIC void add_encode_12289_512(const uint8_t* msg, uint16_t* encodedpoly)
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
	
      if(i == (8*paramL)-1)
	break;
			
      i++;
    } while (1);
}



// decoding
IS_STATIC void decode_12289_512(uint16_t* cipherpoly, uint8_t* plaintext)
{		
  uint16_t i = 0;
		
  do 
    {		
      // Decode(m) = 1 if m between q/4,-q/4, 0 else
      if((cipherpoly[i] < paramQ>>2) || (cipherpoly[i] >= 3*(paramQ>>2)))
	{
	  plaintext[i >> 3] = (plaintext[i >> 3] | (0 << (i%8)));
	}
      else
	{
	  plaintext[i >> 3] = (plaintext[i >> 3] | (1 << (i%8)));
	}
		
      if(i == (8*paramL)-1)
	break;
			
      i++;
    } while (1);
}
				
