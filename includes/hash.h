/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:38:42 by bjesse            #+#    #+#             */
/*   Updated: 2022/01/04 20:39:03 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "stdint.h"

# define TYPE_SHA_256 0
# define TYPE_MD5 1
# define TYPE_SHA_224 2
# define TYPE_SHA_512 3
# define TYPE_SHA_384 4
# define TYPE_SHA_512_256  5

struct s_hash;
struct s_virtual_table;

typedef struct	s_hash	{
	const struct s_virtual_table *const	vtable;
	uint64_t							data_sum_size;
	uint32_t							type;
	unsigned char						last_block_size_big_endian;
	unsigned char						invert_bytes_in_string;
	unsigned char						prepare_block_before_round;
	unsigned char						block_b;
	struct s_hash						*backup;
}				t_hash;

typedef struct	s_virtual_table {
	void	(*round_32)(t_hash *hash, uint32_t *memory, int round_num);
	void	(*round_64)(t_hash *hash, uint64_t *memory, int round_num);
	void	(*prepare_block_32)(uint32_t *block, void *data);
	void	(*prepare_block_64)(uint64_t *block, void *data);
	void	(*copy_hash)(t_hash *copy, t_hash *source);
	void	(*add_hash)(t_hash *base, t_hash *to_add);
	char	*(*hash_to_string)(t_hash *hash);
	void	(*v_process_block_32)(t_hash *hash, void *data);
	void	(*v_process_block_64)(t_hash *hash, void *data);
	int		(*create_last_block_32)(t_hash *hash, void **data, int block_size);
	int		(*create_last_block_64)(t_hash *hash, void **data, int block_size);
}				t_virtual_table;

void			v_process_block(t_hash *hash, void *data);
int				create_last_block(t_hash *hash, void **data, int block_size);

void			round_32(t_hash *h, uint32_t *memory, int round_num);
void			round_64 (t_hash *h, uint64_t *memory, int round_num);
void			prepare_block_32(t_hash *h, uint32_t *block, void *data);
void			copy_hash(t_hash *copy, t_hash *source);
void			add_hash(t_hash *base, t_hash *to_add);
char			*hash_to_string(t_hash *h);

int				create_last_block_32(t_hash *hash, void **data, int block_size);
void			v_process_block_32(t_hash *hash, void *data);
void			proceed_block_32(t_hash *hash, void *data);
void			proceed_last_block_32(t_hash *hash, void *data, int block_size);
void			prepare_block_64 (t_hash *h, uint64_t *block, void *data);

int				create_last_block_64(t_hash *hash, void **data, int block_size);
void			v_process_block_64(t_hash *hash, void *data);

# define ROTATEL(x, n)	((x << n) | (x >> (32 - n)))
# define F(x, y, z) ((x & y) | (~x & z))
# define G(x, y, z) ((x & z) | (~z & y))
# define H(x, y, z) (x ^ z ^ y)
# define I(x, y, z) (y ^ (~z | x))

typedef struct	s_md5_hash {
	t_hash		base;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_md5_hash;
void			md5_round(t_hash *hash, uint32_t *memory, int round_num);
void			md5_copy_hash(t_hash *copy, t_hash *source);
void			md5_add_hash(t_hash *base, t_hash *to_add);
char			*md5_hash_to_string(t_hash *hash);
uint32_t		md5_get_t(int n);
int				md5_get_byte_rotation(int round_num);
void			md5_rotate_reg(t_md5_hash *self);
uint32_t		md5_get_t(int n);

typedef struct	s_sha256_hash {
	t_hash		base;
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
	uint32_t	h4;
	uint32_t	h5;
	uint32_t	h6;
	uint32_t	h7;
}				t_sha256_hash;
void			sha256_round(t_hash *hash, uint32_t *memory, int round_num);
void			sha256_prepare_block(uint32_t *block, void *data);
void			sha256_copy_hash(t_hash *copy, t_hash *source);
void			sha256_add_hash(t_hash *base, t_hash *to_add);
char			*sha256_hash_to_string(t_hash *hash);
uint32_t		sha256_get_k(int n);

# define ROTATER(x, n)	((x >> n) | (x << (32 - n)))
# define S1(e) (ROTATER(e, 6) ^ ROTATER(e, 11) ^ ROTATER(e, 25))
# define CH(e, f, g) ((e & f) ^ ((~e) &g))
# define S0(a) (ROTATER(a, 2) ^ ROTATER(a, 13) ^ ROTATER(a, 22))
# define MAJ(a, b, c) ((a & b) ^ (a & c) ^ (b & c))

char			*sha224_hash_to_string(t_hash *hash);

# define ROTATER64(x, n)	((x >> n) | (x << (64 - n)))
# define S1_512(e) (ROTATER64(e, 14) ^ ROTATER64(e, 18) ^ ROTATER64(e, 41))
# define S0_512(a) (ROTATER64(a, 28) ^ ROTATER64(a, 34) ^ ROTATER64(a, 39))

typedef struct	s_sha512_hash {
	t_hash		base;
	uint64_t	h0;
	uint64_t	h1;
	uint64_t	h2;
	uint64_t	h3;
	uint64_t	h4;
	uint64_t	h5;
	uint64_t	h6;
	uint64_t	h7;
}				t_sha512_hash;

char			*sha512_hash_to_string(t_hash *hash_base);
void			sha512_prepare_block(uint64_t *block, void *data);
void			sha512_round(t_hash *hash_base, uint64_t *memory, int i);
void			sha512_copy_hash(t_hash *hash_base, t_hash *source_base);
void			sha512_add_hash(t_hash *hash_base, t_hash *hash_to_add);

char			*sha384_hash_to_string(t_hash *hash_base);
char			*sha512_256_hash_to_string(t_hash *hash_base);

t_hash			*sha512_256_create();
t_hash			*sha384_create();
t_hash			*sha512_create();
t_hash			*sha256_create();
t_hash			*sha224_create();
t_hash			*md5_create();

void			uint32_to_hash(t_hash *hash, char *dest, uint32_t num);
void			uint64_to_hash(t_hash *hash, char *dest, uint64_t reg);
void			reverse_byte_order_64(uint64_t *all_data_size);
void			reverse_byte_order_32(uint32_t *all_data_size);

char			*get_hash_from_string(t_hash *hash, char *str);
char			*get_hash_from_file(t_hash *hash, int fd);

#endif
