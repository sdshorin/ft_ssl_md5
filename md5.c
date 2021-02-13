
#include "md5.h"

void init_md5_buffer(md5_hash *md5)
{
	md5->a = 0x67452301;
    md5->b = 0xefcdab89;
    md5->c = 0x98badcfe;
    md5->d = 0x10325476;
	md5->data_sum_size = 0;
}


int get_data_num(round_num) {
    if (round_num < 16)
        return (round_num);
    if (round_num < 32)
        return (((round_num)*5 + 1) % 16);
    if (round_num < 48)
        return (((round_num)*3 + 5) % 16);
    return (((round_num)*7) % 16);
}


void proceed_block(md5_hash *md5, void *data)
{
	md5->data_sum_size += 64;
    _process_block(md5, data);
} 

void proceed_last_block(md5_hash *md5, void *data, int block_size)
{
    void *filled_data;
    md5->data_sum_size += block_size;
    filled_data + (char)0x80; block_size++;
    int zero_append_size = (56 - block_size % 64)
    if zero_append_size < 0:
        zero_append_size += 64
    
    filled_data = data + (char)0x00 * zero_append_size + (char*) md5->data_sum_size // 8 байт
} 

void _process_block(md5_hash *md5, void *data) // 64 byte block
{
    uint32_t *block;
    int i;

    i = 0;
    block = (uint32_t*)data;
    while (i < 64) {
        round_md5(md5, block[get_data_num(i)], i);
        i++;
    }
        a += aa, b += bb, c += cc, d += dd;

}



int get_byte_rotation(round_num) {
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

void rotate_reg(md5_hash *self) {
    uint32_t temp;

    temp = self->a;
    self->a = self->b;
    self->b = self->c;
    self->c = self->d;
    self->d = temp;
}


uint32_t get_T(int n) {
	static uint32_t T[65] = { 0,
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


void round_md5(md5_hash *round, uint32_t data_c, int round_num) {
    // uint32_t data_c;
    int s;

    rotate_reg(round);
    s = get_byte_rotation(round_num);
    // data_c = data[get_data_num(round_num)];

    if (round_num < 16)
        round->a += F(round->b, round->c, round->d);
    else if (round_num < 32)
        round->a += G(round->b, round->c, round->d);
    else if (round_num < 48)
        round->a += H(round->b, round->c, round->d);
    else
        round->a += I(round->b, round->c, round->d);
    round->a += data_c + get_T(round_num);

    round->a = ROTATE(round->a, s);
    round->a += round->b;
    
}







int main(){}