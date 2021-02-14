
# include "ft_ssl_md5.h"

# include "md5.h"
# include "sha2.h"


# define TYPE_SHA_256 0

typedef struct hash32 hash32;
typedef struct virtual_table virtual_table;

struct hash32 {
    const virtual_table * const vtable;
	long unsigned int data_sum_size;
	uint32_t type;
	unsigned char last_block_size_big_endian;
	unsigned char invert_bytes_in_string;
	hash32 *backup;
};

struct virtual_table {
    void (*round)(hash32 *hash, uint32_t *memory, int round_num);
    void (*prepare_block)(uint32_t *block, void *data);
    void (*copy_hash)( hash32* copy, hash32* source);
    void (*add_hash)(hash32* base, hash32* to_add);
	// void (*init_buffer)(hash32* new_hash);
	char *(*hash_to_string)(hash32* hash);
	// void (*add_data_size)(hash32* hash, uint32_t added);
	

};

void round_32 (hash32 *h, uint32_t *memory, int round_num) { return h->vtable->round(h, memory, round_num); }
void prepare_block_32 (hash32 *h, uint32_t *block, void *data) { return h->vtable->prepare_block(block, data); }
void copy_hash_32 (hash32* copy, hash32* source) { return copy->vtable->copy_hash(copy, source); }
void add_hash_32 (hash32* base, hash32* to_add) { return base->vtable->add_hash(base, to_add); }
// void init_buffer_32 (hash32* h) { return h->vtable->init_buffer(h); }
char *hash_to_string_32 (hash32* h) { return h->vtable->hash_to_string(h); }
// inline void add_data_size_32 (hash32* h, uint32_t added) { return h->vtable->add_data_size(h, added); }


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

void sha256_round(hash32 *hash, uint32_t *memory, int round_num);
void sha256_prepare_block(uint32_t *block, void *data);
void sha256_copy_hash(hash32* copy, hash32* source);
void sha256_add_hash(hash32* base, hash32* to_add);
// void sha256_init_buffer(hash32* new_hash);
char *sha256_hash_to_string(hash32* hash);
// void sha256_add_data_size(hash32* hash, uint32_t added);





// typedef struct hash32 {
//     const virtual_table * const vtable;
// 	long unsigned int data_sum_size;
// 	uint32_t type;
// 	unsigned char last_block_size_big_endian;
// 	unsigned char invert_bytes_in_string;
// 	struct hash32 *backup;
// } hash32;


hash32 *sha256_create() {
    static const virtual_table vtable = {
        sha256_round, sha256_prepare_block, sha256_copy_hash,
        sha256_add_hash, sha256_hash_to_string
		// sha256_add_data_size, TYPE_SHA_256, 1, 1
    };
    static hash32 base = { &vtable, 0, TYPE_SHA_256, 1, 1 };

    sha256_hash *sha2 = (sha256_hash*)malloc(sizeof(sha256_hash));
    sha256_hash *backup = (sha256_hash*)malloc(sizeof(sha256_hash));
	if (!sha2 || !backup)
		exit(1);
    ft_memcpy(&sha2->base, &base, sizeof(base));
    ft_memcpy(&backup->base, &base, sizeof(base));
	sha2->h0 = 0x6a09e667;
	sha2->h1 = 0xbb67ae85;
	sha2->h2 = 0x3c6ef372;
	sha2->h3 = 0xa54ff53a;
	sha2->h4 = 0x510e527f;
	sha2->h5 = 0x9b05688c;
	sha2->h6 = 0x1f83d9ab;
	sha2->h7 = 0x5be0cd19;
	sha2->base.backup = (hash32*)backup;
    return &sha2->base;
}



