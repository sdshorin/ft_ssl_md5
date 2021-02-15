

#include "hash_32.h"


hash32 *sha256_create() {
    static const virtual_table vtable = {
        sha256_round, sha256_prepare_block, sha256_copy_hash,
        sha256_add_hash, sha256_hash_to_string
		// sha256_add_data_size, TYPE_SHA_256, 1, 1
    };
    static hash32 base = { &vtable, 0, TYPE_SHA_256, 1, 1, 1, 0 };

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



