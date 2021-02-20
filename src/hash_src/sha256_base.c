

#include "ft_ssl_md5.h"

char *sha256_hash_to_string(hash *hash_base)
{
    char *hash_str;
    int i;
	sha256_hash *hash;

    i = 0;
	hash = (sha256_hash*) hash_base;
    hash_str = ft_memalloc(65);
	if (!hash_str)
		exit(1);
    uint32_to_hash(hash_base, hash_str, hash->h0);
    uint32_to_hash(hash_base, hash_str + 8, hash->h1);
    uint32_to_hash(hash_base, hash_str + 16, hash->h2);
    uint32_to_hash(hash_base, hash_str + 24, hash->h3);
    uint32_to_hash(hash_base, hash_str + 32, hash->h4);
    uint32_to_hash(hash_base, hash_str + 40, hash->h5);
    uint32_to_hash(hash_base, hash_str + 48, hash->h6);
    uint32_to_hash(hash_base, hash_str + 56, hash->h7);
    return hash_str;
}

void sha256_prepare_block(uint32_t *block, void *data)
{
	int i;
	uint32_t s0;
	uint32_t s1;

	i = 0;
	ft_memmove((void*)block, data, 64);
	while (i < 16)
		swipe_endian_32(&block[i++]);
	while (i < 64)
	{
		s0 = ROTATER(block[i - 15], 7) ^ ROTATER(block[i - 15], 18) ^ (block[i - 15] >> 3);
		s1 = ROTATER(block[i - 2], 17) ^ ROTATER(block[i - 2], 19) ^ (block[i - 2] >> 10);
		block[i] = block[i - 16] + s0 + block[i - 7] + s1;
		i++;
	}
}

void sha256_round(hash *hash_base, uint32_t *memory, int i)
{
	sha256_hash *hash;
	uint32_t temp1;
	uint32_t temp2;

	hash = (sha256_hash*)hash_base;
	temp1 = hash->h7 + S1(hash->h4) + CH(hash->h4, hash->h5, hash->h6) + memory[i] + sha256_get_k(i);
	temp2 = S0(hash->h0) + MAJ(hash->h0, hash->h1, hash->h2);
	hash->h7 = hash->h6;
	hash->h6 = hash->h5;
	hash->h5 = hash->h4;
	hash->h4 = hash->h3 + temp1;
	hash->h3 = hash->h2;
	hash->h2 = hash->h1;
	hash->h1 = hash->h0;
	hash->h0 = temp1 + temp2;
}

void sha256_copy_hash(hash* hash_base, hash *source_base)
{
	sha256_hash *hash_copy;
	sha256_hash *source;
	hash_copy = (sha256_hash*)hash_base;
	source = (sha256_hash*)source_base;

	hash_copy->h0 = source->h0;
	hash_copy->h1 = source->h1;
	hash_copy->h2 = source->h2;
	hash_copy->h3 = source->h3;
	hash_copy->h4 = source->h4;
	hash_copy->h5 = source->h5;
	hash_copy->h6 = source->h6;
	hash_copy->h7 = source->h7;
}

void sha256_add_hash(hash *hash_base, hash *hash_to_add)
{
	sha256_hash *hash;
	sha256_hash *to_add;
	hash = (sha256_hash*)hash_base;
	to_add = (sha256_hash*)hash_to_add;

	hash->h0 += to_add->h0;
	hash->h1 += to_add->h1;
	hash->h2 += to_add->h2;
	hash->h3 += to_add->h3;
	hash->h4 += to_add->h4;
	hash->h5 += to_add->h5;
	hash->h6 += to_add->h6;
	hash->h7 += to_add->h7;
}
