

// # include "sha2.h"
# include "hash_32.h"




void uint32_to_hash(char *dest, uint32_t num)
{
    int i;
    char *hex_char;
    unsigned char *bytes;

    i = 0;
    hex_char = "0123456789abcdef";
    bytes = (unsigned char*)&num;
    uint32_t  *yyy= (uint32_t  *)bytes;

    while (i < 4)
    {
        unsigned char ttt = bytes[i];
        char check = bytes[3 - i] >> 4;
        char check2 = bytes[3 - i] & 0x0F;
		//// Печать с другого конца!!
        dest[i * 2] = hex_char[bytes[3 - i] >> 4];
        dest[i * 2+ 1] = hex_char[bytes[3 - i] & 0x0F];
        i++;
    }
}


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
    uint32_to_hash(hash_str, hash->h0);
    uint32_to_hash(hash_str + 8, hash->h1);
    uint32_to_hash(hash_str + 16, hash->h2);
    uint32_to_hash(hash_str + 24, hash->h3);
    uint32_to_hash(hash_str + 32, hash->h4);
    uint32_to_hash(hash_str + 40, hash->h5);
    uint32_to_hash(hash_str + 48, hash->h6);
    uint32_to_hash(hash_str + 56, hash->h7);
    return hash_str;
}

// void print_hash(sha2_hash *sha2)
// {
// 	printf("%s\n", sha2_hash_to_string(sha2));
// }



void ft_swipe(unsigned char *a, unsigned char *b)
{
    if (*a == *b)
        return ;
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}


void swipe_endian_long(long unsigned int *all_data_size)
{
    unsigned char *data;
    data = (unsigned char*)all_data_size;

    ft_swipe(data, data + 7);
    ft_swipe(data + 1, data + 6);
    ft_swipe(data + 2, data + 5);
    ft_swipe(data + 3, data + 4);
}

void swipe_endian(uint32_t *all_data_size)
{
    unsigned char *data;
    data = (unsigned char*)all_data_size;

    ft_swipe(data, data + 3);
    ft_swipe(data + 1, data + 2);
}

int create_last_block_32(hash32 *hash, void **data, int block_size)
{
    void *filled_data;
    int zero_append_size;

    zero_append_size = (56 - (block_size + 1) % 64);
    if (zero_append_size < 0)
        zero_append_size += 64;
    filled_data = ft_memalloc(block_size + 1 + zero_append_size + 8);
    if (!filled_data)
        exit(1);
    ft_memmove(filled_data, *data, block_size);
    *(unsigned char*)(filled_data + block_size) = 0x80;
    if (hash->last_block_size_big_endian)
        swipe_endian_long(&hash->data_sum_size);
    ft_memmove(filled_data + block_size + zero_append_size + 1, (void*)&hash->data_sum_size, 8);
    *data = filled_data;
    return (block_size + 1 + zero_append_size + 8);
}


// sha2_hash *sha2_init_buffer (sha2_hash* sha2)
// {
// 	sha2->h0 = 0x6a09e667;
// 	sha2->h1 = 0xbb67ae85;
// 	sha2->h2 = 0x3c6ef372;
// 	sha2->h3 = 0xa54ff53a;
// 	sha2->h4 = 0x510e527f;
// 	sha2->h5 = 0x9b05688c;
// 	sha2->h6 = 0x1f83d9ab;
// 	sha2->h7 = 0x5be0cd19;
// 	sha2->data_sum_size = 0;
// 	return (sha2);
// }



uint32_t sha256_get_k(int n) {
	static uint32_t K[65] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	return K[n];
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


void _process_block_32_base(hash32 *hash, void *data) // 64 byte block
{
    uint32_t block[64];
    int i;
    // hash32 *hash_copy;

	// hash_copy = hash-
	prepare_block_32(hash, block, data);
	// hexDump(block, 64 * 4);
// round_32 (hash32 *h, uint32_t *memory, int round_num)
    i = 0;
    copy_hash_32(hash->backup, hash);
    while (i < 64) {
        round_32(hash, block, i); // + sha2_get_k(i));
        i++;
    }
    add_hash_32(hash, hash->backup);
	// print_hash(sha2);

    // return (sha2);
}






void proceed_block_32_base(hash32 *hash, void *data)
{
	hash->data_sum_size += 64;
	// add_data_size_32(hash, 64);
    _process_block_32_base(hash, data);
} 



void proceed_last_block_32_base(hash32 *hash, void *data, int block_size)
{
    int last_block_size;

    // sha2->data_sum_size += block_size;
	// add_data_size_32(hash, block_size)
	hash->data_sum_size += block_size;
    hash->data_sum_size *=8;
    last_block_size = create_last_block_32(hash, &data, block_size);
    if (last_block_size > 64)
    {
        _process_block_32_base(hash, data);
        _process_block_32_base(hash, data + 64);
    }
    else
        _process_block_32_base(hash, data);
    free(data);
    // return (sha2);
}












char *sha2_get_hash_from_string(char *str)
{
    int len;
    hash32 *hash;


	hash = sha256_create();

    // sha2_init_buffer(&sha2);
    len = ft_strlen(str);
	// print_hash(&sha2);
    while (len - 64 > 0)
    {
        proceed_block_32_base(hash, (void*)str);
        len -= 64;
        str += 64;
    }
    proceed_last_block_32_base(hash, (void*)str, len);
	// print_hash(&sha2);
    return (hash_to_string_32(hash));
}




int main(){
    char *result = sha2_get_hash_from_string("tty");
    printf("hash: %s\n", result);


}





