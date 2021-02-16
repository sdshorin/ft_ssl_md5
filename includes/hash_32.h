
// # include "ft_ssl_md5.h"

// # include "md5.h"
// # include "sha2.h"

# define TYPE_SHA_256 0
# define TYPE_MD5 1
typedef unsigned int uint32_t;
typedef struct hash32 hash32;
typedef struct virtual_table virtual_table;

struct hash32 {
    const virtual_table * const vtable;
	long unsigned int data_sum_size;
	uint32_t type;
	unsigned char last_block_size_big_endian;
	unsigned char invert_bytes_in_string;
	unsigned char prepare_block_before_round;
	hash32 *backup;
};

struct virtual_table {
    void (*round)(hash32 *hash, uint32_t *memory, int round_num);
    void (*prepare_block)(uint32_t *block, void *data);
    void (*copy_hash)( hash32* copy, hash32* source);
    void (*add_hash)(hash32* base, hash32* to_add);
	char *(*hash_to_string)(hash32* hash);	
};


// hash_32_interface.c
void round_32(hash32 *h, uint32_t *memory, int round_num);
void prepare_block_32(hash32 *h, uint32_t *block, void *data);
void copy_hash_32(hash32* copy, hash32* source);
void add_hash_32(hash32* base, hash32* to_add);
char *hash_to_string_32(hash32* h);


// hash_32_loop.c
int create_last_block_32(hash32 *hash, void **data, int block_size);
void _process_block_32(hash32 *hash, void *data);
void proceed_block_32(hash32 *hash, void *data);
void proceed_last_block_32(hash32 *hash, void *data, int block_size);





// sha256.c
typedef struct sha256_hash {
	hash32 base;
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
void sha256_round(hash32 *hash, uint32_t *memory, int round_num);
void sha256_prepare_block(uint32_t *block, void *data);
void sha256_copy_hash(hash32* copy, hash32* source);
void sha256_add_hash(hash32* base, hash32* to_add);
char *sha256_hash_to_string(hash32* hash);

// sha256_utils.c
uint32_t sha256_get_k(int n);

// sha256
# define ROTATER(x, n)	((x >> n) | (x << (32 - n)))
// S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
# define S1(e) (ROTATER(e, 6) ^ ROTATER(e, 11) ^ ROTATER(e, 25))
// ch = (e and f) xor ((not e) and g)
# define CH(e, f, g) ((e & f) ^ ((~e) &g))
// S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
# define S0(a) (ROTATER(a, 2) ^ ROTATER(a, 13) ^ ROTATER(a, 22))
// maj = (a and b) xor (a and c) xor (b and c)
# define MAJ(a, b, c) ((a & b) ^ (a & c) ^ (b & c))


//md5
# define ROTATEL(x, n)	((x << n) | (x >> (32 - n)))
# define F(x, y, z) ((x & y) | (~x & z))
# define G(x, y, z) ((x & z) | (~z & y))
# define H(x, y, z) (x ^ z ^ y)
# define I(x, y, z) (y ^ (~z | x))


// md5
typedef struct md5_hash_struct {
	hash32 base;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
} md5_hash;

// md5_base.c
void md5_round(hash32 *hash, uint32_t *memory, int round_num);
// void md5_prepare_block(uint32_t *block, void *data);
void md5_copy_hash(hash32* copy, hash32* source);
void md5_add_hash(hash32* base, hash32* to_add);
char *md5_hash_to_string(hash32* hash);

// md5_utils.c
uint32_t md5_get_T(int n);
int md5_get_byte_rotation(int round_num);
void md5_rotate_reg(md5_hash *self);
uint32_t md5_get_T(int n);




// factory.c 
hash32 *sha256_create();
hash32 *md5_create();



// utils.c
void uint32_to_hash(hash32 *hash, char *dest, uint32_t num);
void swipe_endian_long(long unsigned int *all_data_size);
void swipe_endian(uint32_t *all_data_size);



// main
char *get_hash_from_string_32(hash32 *hash, char *str);
char *get_hash_from_file_32(hash32 *hash, int fd);
