// http://keccak.noekeon.org/sw_performance.html
// http://bench.cr.yp.to/primitives-sha3.html
// keccakc512	Keccak[r=1088,c=512,nr=24] with 256-bit output;

/*	Only Keccak-F1600 is supported	*/
#define	cKeccakB	1600

//#define	cKeccakR (HASHBYTES*8)
#define	cKeccakR 1088

// #define cKeccakFixedOutputLengthInBytes 64
// w=2^6=64

// capacity: c=25w−r = 512

// nr = 24?


