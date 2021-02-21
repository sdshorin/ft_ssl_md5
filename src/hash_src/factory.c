/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:34:14 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 21:34:59 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_virtual_table g_vtable_sha512 = {
	0, sha512_round, 0, sha512_prepare_block, sha512_copy_hash,
	sha512_add_hash, sha512_hash_to_string, 0, v_process_block_64,
	0, create_last_block_64
};
t_hash			g_base_sha512 = { &g_vtable_sha512,
	0, TYPE_SHA_512, 1, 1, 1, 128, 0 };

t_hash			*sha512_create(void)
{
	t_sha512_hash *sha2;
	t_sha512_hash *backup;

	sha2 = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	backup = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	if (!sha2 || !backup)
		exit(1);
	ft_memcpy(&sha2->base, &g_base_sha512, sizeof(g_base_sha512));
	ft_memcpy(&backup->base, &g_base_sha512, sizeof(g_base_sha512));
	sha2->h0 = 0x6a09e667f3bcc908ULL;
	sha2->h1 = 0xbb67ae8584caa73bULL;
	sha2->h2 = 0x3c6ef372fe94f82bULL;
	sha2->h3 = 0xa54ff53a5f1d36f1ULL;
	sha2->h4 = 0x510e527fade682d1ULL;
	sha2->h5 = 0x9b05688c2b3e6c1fULL;
	sha2->h6 = 0x1f83d9abfb41bd6bULL;
	sha2->h7 = 0x5be0cd19137e2179ULL;
	sha2->base.backup = (t_hash*)backup;
	return (&sha2->base);
}

t_virtual_table	g_vtable_sha256 = {
	sha256_round, 0, sha256_prepare_block, 0, sha256_copy_hash,
	sha256_add_hash, sha256_hash_to_string, v_process_block_32, 0,
	create_last_block_32, 0
};
t_hash			g_base_sha256 = { &g_vtable_sha256, 0,
	TYPE_SHA_256, 1, 1, 1, 64, 0 };

t_hash			*sha256_create(void)
{
	t_sha256_hash *sha2;
	t_sha256_hash *backup;

	sha2 = (t_sha256_hash*)malloc(sizeof(t_sha256_hash));
	backup = (t_sha256_hash*)malloc(sizeof(t_sha256_hash));
	if (!sha2 || !backup)
		exit(1);
	ft_memcpy(&sha2->base, &g_base_sha256, sizeof(g_base_sha256));
	ft_memcpy(&backup->base, &g_base_sha256, sizeof(g_base_sha256));
	sha2->h0 = 0x6a09e667;
	sha2->h1 = 0xbb67ae85;
	sha2->h2 = 0x3c6ef372;
	sha2->h3 = 0xa54ff53a;
	sha2->h4 = 0x510e527f;
	sha2->h5 = 0x9b05688c;
	sha2->h6 = 0x1f83d9ab;
	sha2->h7 = 0x5be0cd19;
	sha2->base.backup = (t_hash*)backup;
	return (&sha2->base);
}

t_virtual_table	g_vtable_sha224 = {
	sha256_round, 0, sha256_prepare_block, 0, sha256_copy_hash,
	sha256_add_hash, sha224_hash_to_string, v_process_block_32, 0,
	create_last_block_32, 0
};
t_hash			g_base_sha224 = { &g_vtable_sha224, 0,
	TYPE_SHA_224, 1, 1, 1, 64, 0 };

t_hash			*sha224_create(void)
{
	t_sha256_hash *sha2;
	t_sha256_hash *backup;

	sha2 = (t_sha256_hash*)malloc(sizeof(t_sha256_hash));
	backup = (t_sha256_hash*)malloc(sizeof(t_sha256_hash));
	if (!sha2 || !backup)
		exit(1);
	ft_memcpy(&sha2->base, &g_base_sha224, sizeof(g_base_sha224));
	ft_memcpy(&backup->base, &g_base_sha224, sizeof(g_base_sha224));
	sha2->h0 = 0xC1059ED8;
	sha2->h1 = 0x367CD507;
	sha2->h2 = 0x3070DD17;
	sha2->h3 = 0xF70E5939;
	sha2->h4 = 0xFFC00B31;
	sha2->h5 = 0x68581511;
	sha2->h6 = 0x64F98FA7;
	sha2->h7 = 0xBEFA4FA4;
	sha2->base.backup = (t_hash*)backup;
	return (&sha2->base);
}

t_virtual_table	g_vtable_md5 = {
	md5_round, 0, 0, 0, md5_copy_hash,
	md5_add_hash, md5_hash_to_string, v_process_block_32, 0,
	create_last_block_32, 0
};
t_hash			g_base_md5 = { &g_vtable_md5, 0,
	TYPE_MD5, 0, 0, 0, 64, 0 };

t_hash			*md5_create(void)
{
	t_md5_hash *md5;
	t_md5_hash *backup;

	md5 = (t_md5_hash*)malloc(sizeof(t_md5_hash));
	backup = (t_md5_hash*)malloc(sizeof(t_md5_hash));
	if (!md5 || !backup)
		exit(1);
	ft_memcpy(&md5->base, &g_base_md5, sizeof(g_base_md5));
	ft_memcpy(&backup->base, &g_base_md5, sizeof(g_base_md5));
	md5->a = 0x67452301;
	md5->b = 0xefcdab89;
	md5->c = 0x98badcfe;
	md5->d = 0x10325476;
	md5->base.backup = (t_hash*)backup;
	return (&md5->base);
}

t_hash			*factory_get_hash_obj(char *command)
{
	if (!ft_strcmp(command, "md5"))
		return (md5_create());
	else if (!ft_strcmp(command, "sha256"))
		return (sha256_create());
	else if (!ft_strcmp(command, "sha224"))
		return (sha224_create());
	else if (!ft_strcmp(command, "sha512"))
		return (sha512_create());
	else if (!ft_strcmp(command, "sha384"))
		return (sha384_create());
	else if (!ft_strcmp(command, "sha512/256"))
		return (sha512_256_create());
	return (md5_create());
}
