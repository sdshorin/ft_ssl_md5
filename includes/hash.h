
// # include "ft_ssl_md5.h"

// # include "md5.h"
// # include "sha2.h"

# define TYPE_SHA_256 0
# define TYPE_MD5 1
# define TYPE_SHA_224 2
# define TYPE_SHA_512 3
# define TYPE_SHA_384 4
typedef unsigned int uint32_t;
typedef unsigned long int uint64;
typedef struct hash hash;
typedef struct virtual_table virtual_table;

struct hash {
    const virtual_table * const vtable;
	long unsigned int data_sum_size;
	uint32_t type;
	unsigned char last_block_size_big_endian;
	unsigned char invert_bytes_in_string;
	unsigned char prepare_block_before_round;
	unsigned char block_b;
	hash *backup;
};

struct virtual_table {
    void (*round_32)(hash *hash, uint32_t *memory, int round_num);
    void (*round_64)(hash *hash, uint64 *memory, int round_num);
    void (*prepare_block_32)(uint32_t *block, void *data);
    void (*prepare_block_64)(uint64 *block, void *data);
    void (*copy_hash)( hash* copy, hash* source);
    void (*add_hash)(hash* base, hash* to_add);
	char *(*hash_to_string)(hash* hash);	
	void (*_process_block_32)(hash *hash, void *data);
	void (*_process_block_64)(hash *hash, void *data);
	int (*create_last_block_32)(hash *hash, void **data, int block_size);
	int (*create_last_block_64)(hash *hash, void **data, int block_size);
};


// hash_interface.c
void _process_block(hash *hash, void *data);
int create_last_block(hash *hash, void **data, int block_size);

void round_32(hash *h, uint32_t *memory, int round_num);
void round_64 (hash *h, uint64 *memory, int round_num) ;
void prepare_block_32(hash *h, uint32_t *block, void *data);
void copy_hash(hash* copy, hash* source);
void add_hash(hash* base, hash* to_add);
char *hash_to_string(hash* h);

// 32
int create_last_block_32(hash *hash, void **data, int block_size);
void _process_block_32(hash *hash, void *data);
void proceed_block_32(hash *hash, void *data);
void proceed_last_block_32(hash *hash, void *data, int block_size);
// 64
void prepare_block_64 (hash *h, uint64 *block, void *data);

int create_last_block_64(hash *hash, void **data, int block_size);
void _process_block_64(hash *hash, void *data);




//md5
# define ROTATEL(x, n)	((x << n) | (x >> (32 - n)))
# define F(x, y, z) ((x & y) | (~x & z))
# define G(x, y, z) ((x & z) | (~z & y))
# define H(x, y, z) (x ^ z ^ y)
# define I(x, y, z) (y ^ (~z | x))
typedef struct md5_hash_struct {
	hash base;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} md5_hash;
// md5_base.c
void md5_round(hash *hash, uint32_t *memory, int round_num);
void md5_copy_hash(hash* copy, hash* source);
void md5_add_hash(hash* base, hash* to_add);
char *md5_hash_to_string(hash* hash);
// md5_utils.c
uint32_t md5_get_T(int n);
int md5_get_byte_rotation(int round_num);
void md5_rotate_reg(md5_hash *self);
uint32_t md5_get_T(int n);



// sha256.c
typedef struct sha256_hash {
	hash base;
	uint32_t h0;
	uint32_t h1;
	uint32_t h2;
	uint32_t h3;
	uint32_t h4;
	uint32_t h5;
	uint32_t h6;
	uint32_t h7;
} sha256_hash;
// sha256_base.c
void sha256_round(hash *hash, uint32_t *memory, int round_num);
void sha256_prepare_block(uint32_t *block, void *data);
void sha256_copy_hash(hash* copy, hash* source);
void sha256_add_hash(hash* base, hash* to_add);
char *sha256_hash_to_string(hash* hash);
// sha256_utils.c
uint32_t sha256_get_k(int n);
// sha256
# define ROTATER(x, n)	((x >> n) | (x << (32 - n)))
# define S1(e) (ROTATER(e, 6) ^ ROTATER(e, 11) ^ ROTATER(e, 25))
# define CH(e, f, g) ((e & f) ^ ((~e) &g))
# define S0(a) (ROTATER(a, 2) ^ ROTATER(a, 13) ^ ROTATER(a, 22))
# define MAJ(a, b, c) ((a & b) ^ (a & c) ^ (b & c))
char *sha224_hash_to_string(hash* hash);

// sha512.c


# define ROTATER64(x, n)	((x >> n) | (x << (64 - n)))
# define S1_512(e) (ROTATER64(e, 14) ^ ROTATER64(e, 18) ^ ROTATER64(e, 41))
// # define CH_512(e, f, g) ((e & f) ^ ((~e) &g))
# define S0_512(a) (ROTATER64(a, 28) ^ ROTATER64(a, 34) ^ ROTATER64(a, 39))
// # define MAJ_512(a, b, c) ((a & b) ^ (a & c) ^ (b & c))

typedef struct sha512_hash {
	hash base;
	uint64 h0;
	uint64 h1;
	uint64 h2;
	uint64 h3;
	uint64 h4;
	uint64 h5;
	uint64 h6;
	uint64 h7;
} sha512_hash;

char *sha512_hash_to_string(hash *hash_base);
void sha512_prepare_block(uint64 *block, void *data);
void sha512_round(hash *hash_base, uint64 *memory, int i);
void sha512_copy_hash(hash* hash_base, hash *source_base);
void sha512_add_hash(hash *hash_base, hash *hash_to_add);


char *sha384_hash_to_string(hash *hash_base);



// factory.c 
hash *sha256_create();
hash *md5_create();



// utils.c
void uint32_to_hash(hash *hash, char *dest, uint32_t num);
void uint64_to_hash(hash *hash, char *dest, uint64 reg);
void swipe_endian_64(long unsigned int *all_data_size);
void swipe_endian_32(uint32_t *all_data_size);



// main
char *get_hash_from_string(hash *hash, char *str);
char *get_hash_from_file(hash *hash, int fd);
