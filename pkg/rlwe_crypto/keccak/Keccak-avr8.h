/*
The Keccak sponge function, designed by Guido Bertoni, Joan Daemen,
Michaël Peeters and Gilles Van Assche. For more information, feedback or
questions, please refer to our website: http://keccak.noekeon.org/

Implementation by Ronny Van Keer, hereby denoted as "the implementer".

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/
*/

#ifndef _Keccak_AVR_h_
#define _Keccak_AVR_h_

#include "Keccak-avr8-settings.h"

#ifndef cKeccakB
/*	Only Keccak-F1600 is supported	*/
#define	cKeccakB	1600
#endif


typedef unsigned char BitSequence;
typedef unsigned long long DataLength;
typedef enum { SUCCESS = 0, FAIL = 1, BAD_HASHLEN = 2 } HashReturn;

typedef struct hashStateStruct
{
	unsigned char	state[cKeccakB / 8];
	unsigned char bytesInQueue;
	unsigned char	trailingBitsInQueue;
} hashState;


int crypto_hash( unsigned char *out, const unsigned char *in, unsigned long long inlen );

#endif
