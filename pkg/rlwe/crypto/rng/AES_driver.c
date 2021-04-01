/* This file has been prepared for Doxygen automatic documentation generation.*/   
/*! \file *********************************************************************  
 *  
 * \brief  
 *      XMEGA AES driver source file.  
 *  
 *      This file contains the function implementations the XMEGA AES driver.  
 *  
 *      The driver is not intended for size and/or speed critical code, since  
 *      most functions are just a few lines of code, and the function call  
 *      overhead would decrease code performance. The driver is intended for  
 *      rapid prototyping and documentation purposes for getting started with  
 *      the XMEGA AES module.  
 *  
 *      For size and/or speed critical code, it is recommended to copy the  
 *      function contents directly into your application instead of making  
 *      a function call.  
 *  
 *      Several functions use the following construct:  
 *          "some_register = ... | (some_parameter ? SOME_BIT_bm : 0) | ..."  
 *      Although the use of the ternary operator ( if ? then : else ) is discouraged,  
 *      in some occasions the operator makes it possible to write pretty clean and  
 *      neat code. In this driver, the construct is used to set or not set a  
 *      configuration bit based on a boolean input parameter, such as  
 *      the "some_parameter" in the example above.  
 *  
 * \par Application note:  
 *      AVR1317 Using the XMEGA built in AES accelerator  
 *  
 * \par Documentation  
 *      For comprehensive code documentation, supported compilers, compiler  
 *      settings and supported devices see readme.html  
 *  
 * \author  
 *      Atmel Corporation: http://www.atmel.com \n  
 *      Support email: avr@atmel.com  
 *  
 * $Revision: 1569 $  
 * $Date: 2008-04-22 13:03:43 +0200 (ti, 22 apr 2008) $  \n  
 *  
 * Copyright (c) 2008, Atmel Corporation All rights reserved.  
 *  
 * Redistribution and use in source and binary forms, with or without  
 * modification, are permitted provided that the following conditions are met:  
 *  
 * 1. Redistributions of source code must retain the above copyright notice,  
 * this list of conditions and the following disclaimer.  
 *  
 * 2. Redistributions in binary form must reproduce the above copyright notice,  
 * this list of conditions and the following disclaimer in the documentation  
 * and/or other materials provided with the distribution.  
 *  
 * 3. The name of ATMEL may not be used to endorse or promote products derived  
 * from this software without specific prior written permission.  
 *  
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED  
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF  
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND  
key sch * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,  
 * INDIRECT, INkeyCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES  
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;  
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
 *****************************************************************************/   
#include "AES_driver.h"   
   

bool AES_encrypt(uint8_t * plaintext, uint8_t * ciphertext, uint8_t * key)   
{   
  bool encrypt_ok;   
   
  /* Load key into AES key memory. */   
  uint8_t * temp_key = key;   
  for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){   
    AES.KEY =  *(temp_key++);   
  }   
   
  /* Load data into AES state memory. */   
  uint8_t * temp_plaintext = plaintext;   
  for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){   
    AES.STATE =  *(temp_plaintext++);   
  }   
   
  /* Set AES in encryption mode and start AES. */   
  AES.CTRL = (AES.CTRL & (~AES_DECRYPT_bm)) | AES_START_bm;   
   
  do{   
    /* Wait until AES is finished or an error occurs. */   
  }while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);   
   
  /* If not error. */   
  if((AES.STATUS & AES_ERROR_bm) == 0){   
    /* Store the result. */   
    uint8_t * temp_ciphertext = ciphertext;   
    for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){   
      *(temp_ciphertext++) = AES.STATE;   
    }   
    encrypt_ok = true;   
  }else{   
    encrypt_ok = false;   
   
  }   
  return encrypt_ok;   
}   
   
   
   
/*! \brief  Polled function that does an AES decryption on one 128-bit data block.
 *
 *  \note This code is blocking and will dead lock if no interrupt flags are set.
 *
 *  \param  ciphertext  Pointer to the ciphertext that shall be decrypted
 *  \param  plaintext   Pointer to where in memory the plaintext (answer) shall be stored.
 *  \param  key         Pointer to the DES key
 *
 *  \retval true   If the AES decryption was successful.
 *  \retval false  If the AES decryption was not successful.
 */
bool AES_decrypt(uint8_t * ciphertext, uint8_t * plaintext,
                 uint8_t * key){

  bool decrypt_ok;

  /* Load key into AES key memory. */
  uint8_t * temp_key = key;
  for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){
    AES.KEY =  *(temp_key++);
  }

  /* Load data into AES state memory. */
  uint8_t * temp_ciphertext = ciphertext;
  for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){
    AES.STATE =  *(temp_ciphertext++);
  }

  /* Set AES in decryption mode and start the AES.*/
  AES.CTRL |= (AES_START_bm | AES_DECRYPT_bm);

  do{
    /* Wait until AES is finished or an error occurs. */
  }while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);

  /* If not error. */
  if((AES.STATUS & AES_ERROR_bm) == 0){
    /* Store the result. */
    uint8_t * temp_plaintext = plaintext;
    for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){
      *(temp_plaintext++) = AES.STATE;
    }
    decrypt_ok = true;
  }else{
    decrypt_ok = false;

  }
  return decrypt_ok;
}

   
   
/*! \brief  Polled function that does an AES encryption on one 128-bit data block.  
 *  
 *  Function equal to the AES_encrypt function but the key is not loaded  
 *  into the key memory. The function require that the key already is in the  
 *  key memory. Used when encryption and decryption with the same key is  
 *  done every other time.  
 *  
 *  \note This code is blocking and will dead lock if no interrupt flags are set.  
 *  
 *  \param  plaintext  Pointer to the plaintext that shall be encrypted  
 *  \param  ciphertext Pointer to where in memory the ciphertext (answer) shall be stored.  
 *  
 *  \retval true   If the AES encryption was successful.  
 *  \retval false  If the AES encryption was not successful.  
 */   
bool AES_encrypt_backtoback(uint8_t * plaintext, uint8_t * ciphertext)   
{   
  bool encrypt_ok;   
   
  /* Load data into AES state memory. */   
  uint8_t * temp_plaintext = plaintext;   
  for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){   
    AES.STATE =  *(temp_plaintext++);   
  }   
   
  /* Set AES in encryption mode and start AES. */   
  AES.CTRL = (AES.CTRL & (~AES_DECRYPT_bm)) | AES_START_bm;   
   
   
  do{   
    /* Wait until AES is finished or an error occurs. */   
  }while((AES.STATUS & (AES_SRIF_bm|AES_ERROR_bm) ) == 0);   
   
  /* If not error. */   
  if((AES.STATUS & AES_ERROR_bm) == 0){   
    /* Store the result. */   
    uint8_t * temp_ciphertext = ciphertext;   
    for(uint8_t i = 0; i < AES_BLOCK_LENGTH; i++){   
      *(temp_ciphertext++) = AES.STATE;   
    }   
    encrypt_ok = true;   
  }else{   
    encrypt_ok = false;   
   
  }   
  return encrypt_ok;   
}   
   
