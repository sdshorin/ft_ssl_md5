
#include "ft_ssl_md5.h"

uint64 sha512_k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

char *sha512_hash_to_string(hash *hash_base)
{
    char *hash_str;
    int i;
	sha512_hash *hash;

    i = 0;
	hash = (sha512_hash*) hash_base;
    hash_str = ft_memalloc(129);
	if (!hash_str)
		exit(1);
     uint64_to_hash(hash_base, hash_str, hash->h0);
     uint64_to_hash(hash_base, hash_str + 16, hash->h1);
     uint64_to_hash(hash_base, hash_str + 32, hash->h2);
     uint64_to_hash(hash_base, hash_str + 48, hash->h3);
     uint64_to_hash(hash_base, hash_str + 64, hash->h4);
     uint64_to_hash(hash_base, hash_str + 80, hash->h5);
     uint64_to_hash(hash_base, hash_str + 96, hash->h6);
     uint64_to_hash(hash_base, hash_str + 112, hash->h7);
    return hash_str;
}

void sha512_prepare_block(uint64 *block, void *data)
{
	int i;
	uint64 s0;
	uint64 s1;

	i = 0;
	ft_memmove((void*)block, data, 128);
	while (i < 16)
		swipe_endian_64(&block[i++]);
	while (i < 80)
	{
		s0 = ROTATER64(block[i - 15], 1) ^ ROTATER64(block[i - 15], 8) ^ (block[i - 15] >> 7);
		s1 = ROTATER64(block[i - 2], 19) ^ ROTATER64(block[i - 2], 61) ^ (block[i - 2] >> 6);
		block[i] = block[i - 16] + s0 + block[i - 7] + s1;
		i++;
	}
}

void sha512_round(hash *hash_base, uint64 *memory, int i)
{
	sha512_hash *hash;
	uint64 temp1;
	uint64 temp2;

	hash = (sha512_hash*)hash_base;
	temp1 = hash->h7 + S1_512(hash->h4) + CH(hash->h4, hash->h5, hash->h6) + memory[i] + sha512_k[i];
	temp2 = S0_512(hash->h0) + MAJ(hash->h0, hash->h1, hash->h2);
	hash->h7 = hash->h6;
	hash->h6 = hash->h5;
	hash->h5 = hash->h4;
	hash->h4 = hash->h3 + temp1;
	hash->h3 = hash->h2;
	hash->h2 = hash->h1;
	hash->h1 = hash->h0;
	hash->h0 = temp1 + temp2;
}

void sha512_copy_hash(hash* hash_base, hash *source_base)
{
	sha512_hash *hash_copy;
	sha512_hash *source;

	hash_copy = (sha512_hash*)hash_base;
	source = (sha512_hash*)source_base;
	hash_copy->h0 = source->h0;
	hash_copy->h1 = source->h1;
	hash_copy->h2 = source->h2;
	hash_copy->h3 = source->h3;
	hash_copy->h4 = source->h4;
	hash_copy->h5 = source->h5;
	hash_copy->h6 = source->h6;
	hash_copy->h7 = source->h7;
}

void sha512_add_hash(hash *hash_base, hash *hash_to_add)
{
	sha512_hash *hash;
	sha512_hash *to_add;

	hash = (sha512_hash*)hash_base;
	to_add = (sha512_hash*)hash_to_add;
	hash->h0 += to_add->h0;
	hash->h1 += to_add->h1;
	hash->h2 += to_add->h2;
	hash->h3 += to_add->h3;
	hash->h4 += to_add->h4;
	hash->h5 += to_add->h5;
	hash->h6 += to_add->h6;
	hash->h7 += to_add->h7;
}
