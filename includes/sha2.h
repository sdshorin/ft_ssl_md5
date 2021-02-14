
#include "ft_ssl_md5.h"


# define ROTATER(x, n)	((x >> n) | (x << (32 - n)))

// S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
# define S1(e) (ROTATER(e, 6) ^ ROTATER(e, 11) ^ ROTATER(e, 25))
// ch = (e and f) xor ((not e) and g)
# define CH(e, f, g) ((e & f) ^ ((~e) &g))

// S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
# define S0(a) (ROTATER(a, 2) ^ ROTATER(a, 13) ^ ROTATER(a, 22))

// maj = (a and b) xor (a and c) xor (b and c)
# define MAJ(a, b, c) ((a & b) ^ (a & c) ^ (b & c))
typedef struct sha2_hash_struct {
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;

	long unsigned int data_sum_size;
} sha2_hash;