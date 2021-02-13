
# include "libft.h"

typedef unsigned int uint32_t;

# define ROTATE(x, n)	((x << n) | (x >> (32 - n)))
# define F(x, y, z) ((x & y) | (~x & z))
# define G(x, y, z) ((x & z) | (~z & y))
# define H(x, y, z) (x ^ z ^ y)
# define I(x, y, z) (y ^ (~z | x))



typedef struct md5_hash_struct {
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	long unsigned int data_sum_size;

} md5_hash;



md5_hash *md5_proceed_block(md5_hash *md5, void *data);
md5_hash *md5_proceed_last_block(md5_hash *md5, void *data, int block_size);
md5_hash *_md5_process_block(md5_hash *md5, void *data);
md5_hash *md5_proceed_last_block(md5_hash *md5, void *data, int block_size);
void md5_round(md5_hash *round, uint32_t data_c, int round_num);
uint32_t md5_get_T(int n);

