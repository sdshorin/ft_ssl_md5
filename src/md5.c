
#include "md5.h"










void md5_init_buffer(md5_hash *md5)
{
	md5->a = 0x67452301;
    md5->b = 0xefcdab89;
    md5->c = 0x98badcfe;
    md5->d = 0x10325476;
	md5->data_sum_size = 0;
}


int md5_get_data_num(round_num) {
    if (round_num < 16)
        return (round_num);
    if (round_num < 32)
        return (((round_num)*5 + 1) % 16);
    if (round_num < 48)
        return (((round_num)*3 + 5) % 16);
    return (((round_num)*7) % 16);
}


void uint_to_hash(char *dest, uint32_t num)
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
        dest[i * 2] = hex_char[bytes[i] >> 4];
        dest[i * 2+ 1] = hex_char[bytes[i] & 0x0F];
        i++;
    }
}


char *md5_hash_to_string(md5_hash *md5)
{
    char *hash_str;
    int i;
    unsigned char *md5_pointer;

    int *test = (int*)md5;


    i = 0;
    md5_pointer = (unsigned char*)md5;
    hash_str = ft_memalloc(33); // защита!!!!
    uint_to_hash(hash_str, md5->a);
    uint_to_hash(hash_str + 8, md5->b);
    uint_to_hash(hash_str + 16, md5->c);
    uint_to_hash(hash_str + 24, md5->d);
    return hash_str;
}



char *md5_get_hash_from_string(char *str)
{
    int len;
    md5_hash md5;

    md5_init_buffer(&md5);
    len = ft_strlen(str);
    while (len - 64 > 0)
    {
        md5_proceed_block(&md5, (void*)str);
        len -= 64;
        str += 64;
    }
    md5_proceed_last_block(&md5, (void*)str, len);
    return (md5_hash_to_string(&md5));
}




md5_hash *md5_proceed_block(md5_hash *md5, void *data)
{
	md5->data_sum_size += 64;
    _md5_process_block(md5, data);
    return (md5);
} 

md5_hash *md5_proceed_last_block(md5_hash *md5, void *data, int block_size)
{
    void *filled_data;
    int zero_append_size;

    md5->data_sum_size += block_size;
    md5->data_sum_size *=8;
    zero_append_size = (56 - (block_size + 1) % 64);
    if (zero_append_size < 0)
        zero_append_size += 64;
    filled_data = ft_memalloc(block_size + 1 + zero_append_size + 8);
    if (!filled_data)
        exit(1);
    ft_memmove(filled_data, data, block_size);
    *(unsigned char*)(filled_data + block_size) = 0x80;
    ft_memmove(filled_data + block_size + zero_append_size + 1, (void*)&md5->data_sum_size, 8);
    if (block_size + zero_append_size + 8 > 64)
    {
        _md5_process_block(md5, filled_data);
        _md5_process_block(md5, filled_data + 64);
    }
    else
        _md5_process_block(md5, filled_data);
    free(filled_data);
    return (md5);
} 


void md5_add_hash(md5_hash *base, md5_hash * additional)
{
    base->a += additional->a;
    base->b += additional->b;
    base->c += additional->c;
    base->d += additional->d;
}

void md5_copy_hash(md5_hash *hash_copy, const md5_hash * md5)
{
    hash_copy->a = md5->a;
    hash_copy->b = md5->b;
    hash_copy->c = md5->c;
    hash_copy->d = md5->d;
}

md5_hash *_md5_process_block(md5_hash *md5, void *data) // 64 byte block
{
    uint32_t *block;
    int i;
    md5_hash hash_copy;

    i = 0;
    md5_copy_hash(&hash_copy, md5);
    block = (uint32_t*)data;
    while (i < 64) {
        md5_round(md5, block[md5_get_data_num(i)], i);
        i++;
    }
    md5_add_hash(md5, &hash_copy);
    return (md5);
}



int md5_get_byte_rotation(round_num) {
    static int s[16] = {
        7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21
    };
    if (round_num < 16)
        return (s[round_num % 4]);
    if (round_num < 32)
        return (s[round_num % 4 + 4]);
    if (round_num < 48)
        return (s[round_num % 4 + 8]);
    return (s[round_num % 4 + 12]);
}

void md5_rotate_reg(md5_hash *self) {
    uint32_t temp;

    temp = self->d;
    self->d = self->c;
    self->c = self->b;
    self->b = self->a;
    self->a = temp;
}


uint32_t md5_get_T(int n) {
	static uint32_t T[65] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};
	return T[n];
}


void md5_round(md5_hash *round, uint32_t data_c, int round_num) {
    int s;

    s = md5_get_byte_rotation(round_num);
    if (round_num < 16)
        round->a += F(round->b, round->c, round->d);
    else if (round_num < 32)
        round->a += G(round->b, round->c, round->d);
    else if (round_num < 48)
        round->a += H(round->b, round->c, round->d);
    else
        round->a += I(round->b, round->c, round->d);
    round->a += data_c + md5_get_T(round_num);

    round->a = ROTATE(round->a, s);
    round->a += round->b;
    md5_rotate_reg(round);
}







int main(){
    char *result = md5_get_hash_from_string("test");
    printf("hash: %s", result);


}