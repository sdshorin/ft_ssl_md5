



#include "ft_ssl_md5.h"

#include <stdio.h>

int	g_block_start_p[64] = {
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17, 9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7,
};

int	g_block_end_p[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};


int	g_p_box_extend[48] = {
32, 1, 2, 3, 4, 5,
4, 5, 6, 7, 8, 9,
8, 9, 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1
};

int g_p_box[32] = {
16, 7, 20, 21,
29, 12, 28, 17,
1, 15, 23, 26,
5, 18, 31, 10,
2, 8, 24, 14,
32, 27, 3, 9,
19, 13, 30, 6,
22, 11, 4, 25,
};

int		g_s_boxes[8][4][16] = {
{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},

{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},

{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},

{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},

{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},

{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},

{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},

{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}
};

int		g_key_init_premutation[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

int		g_key_compress[56] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

int		g_des_key_rot[16] = {
1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

uint64_t permutation(uint64_t block, int *premut_table, int size)
{
	uint64_t data;
	int i;

	i = 0;
	data = 0;
	while (i < size)
	{
		data |= ((block >> (premut_table[i] - 1)) & 0x01) << i;
		i++;
	}
	return data;
}

uint64_t des_ecb_round_s_boxes(uint64_t data)
{
	int i;
	uint64_t result;
	unsigned char six_bit_block;
	unsigned char a;
	unsigned char b;

	i = 0;
	result = 0;
	while (i < 8)
	{
		six_bit_block = (data >> (6 * i)) & 0x3F;
		reverse_byte(&six_bit_block);
		six_bit_block = six_bit_block >> 2;
		print_binary_32((uint32_t)six_bit_block);
		a = (six_bit_block & 0x1) + (six_bit_block >> 5) * 2;
		b = (six_bit_block & 0x1e) >> 1;
		printf("six_bit_block: %d, a = %d, b = %d\n", six_bit_block, a, b);
		unsigned char s_result = g_s_boxes[i][a][b];
		reverse_byte(&s_result);
		s_result = s_result >> 4;
		printf("s_result for i=%d: %d\n", i, s_result);
		result |= ((uint64_t)s_result)<<(i*4);
		i++;
	}
	return (result);
}

uint32_t des_ecb_round(uint32_t L, uint32_t R, t_des_env *env, int n)
{
	uint64_t data;

	data = R;
	data = permutation(data, g_p_box_extend, 48);
	data ^= env->round_key[n];
	printf("after xor:");
	print_binary(data);
	data = des_ecb_round_s_boxes(data);
	printf("after s-box:");
	print_binary(data);
	data = permutation(data, g_p_box, 32);
	printf("after s-block premutation:");
	print_binary(data);
	return (((uint32_t)data)^L);
}

uint64_t 	process_des_ecb_block(t_des_env *env, uint64_t *block)
{
	int i;
	uint32_t L;
	uint32_t R;
	uint32_t temp;
	uint64_t result;


	i = 0;
	swipe_endian_bytes((unsigned char*)block, 8);
	*block = permutation(*block, g_block_start_p, 64);
	L = *(uint32_t*)(block);
	R = *((uint32_t*)(block) + 1);
	while (i < 16)
	{
		temp = des_ecb_round(L, R, env, i);
		L = R;
		R = temp;
		i += 1;
	}
	result = (uint64_t)R | (((uint64_t)L) << 32);
	result = permutation(result, g_block_end_p, 64);
	printf("Result: ");
	print_binary(result);
	swipe_endian_bytes((unsigned char*)&result, 8);
	return result;
}

void des_create_keys(t_des_env *env)
{
	uint32_t c;
	uint32_t d;
	uint64_t temp;
	int i;

	// des_check_key();
	i = 0;
	temp = *(uint64_t*)env->key;
	print_binary(temp);
	swipe_endian_bytes((unsigned char*)&temp, 8);
	print_binary(temp);
	temp = permutation(temp, g_key_init_premutation, 56);
	print_binary(temp);
	c = ((uint32_t)temp << 4) >> 4;
	print_binary_32(c);
	d = (uint32_t)(temp>>28);
	print_binary_32(d);
	while (i < 16)
	{
		c = (DES_ROT_KEY(c, g_des_key_rot[i]) << 4) >> 4;
		printf("c%d: ", i + 1);
		print_binary_32(c);
		d = (DES_ROT_KEY(d, g_des_key_rot[i]) << 4) >> 4;
		printf("d%d: ", i + 1);
		print_binary_32(d);
		temp = (uint64_t)c | (((uint64_t)d) << 28);
		temp = permutation(temp, g_key_compress, 56);
		env->round_key[i] = temp;
		printf("key %d: ", i + 1);
		print_binary(temp);
		i++;
	}
}


void	des_init_keys(t_des_env *env)
{
	env->key = (unsigned char *)"IEOFIT#1";
	// if (env->key)
	// {
	// 	des_decode_key();
	// 	des_create_subkeys(env);
	// 	return ;
	// }
	// des_get_salt(env);
	// des_get_pass(env);
	// des_comput_key(env);
	des_create_keys(env);
}


void des_ecb(t_des_env *env)
{
	unsigned char	buff[9];
	int		ch_read;
	int		i;
	uint64_t result;

	des_init_keys(env);
	ft_strcpy((char *)buff, "IEOFIT#1");
	result = process_des_ecb_block(env, (uint64_t*)&buff);
	des_print_block(result, env);
	// while ((ch_read = read(env->fd_in, buff, 8))
	// 										== 8)
	// 	process_des_ecb_block(env, (uint64_t*)buff);
	// if (ch_read > 0)
	// 	process_des_ecb_block(env, des_ecb_create_last_block(buff, ch_read));
}


void des_print_block(uint64_t encrypted_block, t_des_env *env)
{
	unsigned char *encrypted_bytes;
	int i;

	i = 0;
	encrypted_bytes = (unsigned char *)&encrypted_block;
	while (i<8){
		printf("%02X%s", encrypted_bytes[i], ( i + 1 ) % 16 == 0 ? "\r\n" : " " );
		i++;

	}
	printf("\n");
	printf("\n");
}

// struct s_des_env {
// 	unsigned char	a;
// 	unsigned char	d;
// 	unsigned char	*key;
// 	unsigned char	*pass;
// 	unsigned char	*salt;
// 	int				fd_in;
// 	int				fd_out;
// 	uint64_t		round_key[16];

// struct s_des_flag {
// 	unsigned char	a;
// 	unsigned char	d;
// 	char			*input_file;
// 	char			*output_file;
// 	char			*key;
// 	char			*pass;
// 	char			*salt;
// 	char			*i_vector;
// 	char			*command;

void des_init_env(t_des_env *env, t_des_flags *flags)
{

}

void des_work(t_des_flags *flags)
{
	t_des_env env;

	des_init_env(&env, flags);
	if (1)
		des_ecb(&env);
}