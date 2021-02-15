

// # include "sha2.h"
# include "hash_32.h"





char *sha256_hash_to_string(hash32 *hash_base)
{
    char *hash_str;
    int i;
	sha256_hash *hash;

    i = 0;
	hash = (sha256_hash*) hash_base;
    hash_str = ft_memalloc(64); // защита!!!!
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
		swipe_endian(&block[i++]);
	while (i < 64)
	{
		s0 = ROTATER(block[i - 15], 7) ^ ROTATER(block[i - 15], 18) ^ (block[i - 15] >> 3);
		s1 = ROTATER(block[i - 2], 17) ^ ROTATER(block[i - 2], 19) ^ (block[i - 2] >> 10);
		block[i] = block[i - 16] + s0 + block[i - 7] + s1;
		i++;
	}
}


// a,  b,  c,  d,  e,  f,  g,  h
// h0, h1, h2, h3, h4, h5, h6, h7
void sha256_round(hash32 *hash_base, uint32_t *memory, int i) //uint32_t data)
{
	sha256_hash *hash;

	hash = (sha256_hash*)hash_base;
// S1 = (e rightrotate 6) xor (e rightrotate 11) xor (e rightrotate 25)
// ch = (e and f) xor ((not e) and g)
	uint32_t temp1;
	temp1 = hash->h7 + S1(hash->h4) + CH(hash->h4, hash->h5, hash->h6) + memory[i] + sha256_get_k(i);
// S0 = (a rightrotate 2) xor (a rightrotate 13) xor (a rightrotate 22)
// maj = (a and b) xor (a and c) xor (b and c)
// temp2 := S0 + maj
	uint32_t temp2;
	temp2 = S0(hash->h0) + MAJ(hash->h0, hash->h1, hash->h2);
// h = g
	hash->h7 = hash->h6;
// g = f
	hash->h6 = hash->h5;
// f = e
	hash->h5 = hash->h4;
// e = d + temp1
	hash->h4 = hash->h3 + temp1;
// d = c
	hash->h3 = hash->h2;
// c = b
	hash->h2 = hash->h1;
// b = a
	hash->h1 = hash->h0;
// a = temp1 + temp2
	hash->h0 = temp1 + temp2;
}



void sha256_copy_hash(hash32* hash_base, hash32 *source_base)
{
	sha256_hash *hash_copy;
	sha256_hash *source;
	hash_copy = (sha256_hash*)hash_base;
	source = (sha256_hash*)source_base;

	// ft_memmove((void*)hash_copy, (void*)sha2, sizeof(sha2_hash));
	hash_copy->h0 = source->h0;
	hash_copy->h1 = source->h1;
	hash_copy->h2 = source->h2;
	hash_copy->h3 = source->h3;
	hash_copy->h4 = source->h4;
	hash_copy->h5 = source->h5;
	hash_copy->h6 = source->h6;
	hash_copy->h7 = source->h7;
}

void sha256_add_hash(hash32 *hash_base, hash32 *hash_to_add)
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






