/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:27:09 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 03:53:29 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_virtual_table	g_vtable_sha384 = {
	0, sha512_round, 0, sha512_prepare_block, sha512_copy_hash,
	sha512_add_hash, sha384_hash_to_string, 0, v_process_block_64,
	0, create_last_block_64};
t_hash			g_base_sha384 = {&g_vtable_sha384, 0,
	TYPE_SHA_384, 1, 1, 1, 128, 0 };

t_hash			*sha384_create(void)
{
	t_sha512_hash						*sha2;
	t_sha512_hash						*backup;

	sha2 = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	backup = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	if (!sha2 || !backup)
		exit(1);
	ft_memcpy(&sha2->base, &g_base_sha384, sizeof(g_base_sha384));
	ft_memcpy(&backup->base, &g_base_sha384, sizeof(g_base_sha384));
	sha2->h0 = 0xCBBB9D5DC1059ED8;
	sha2->h1 = 0x629A292A367CD507;
	sha2->h2 = 0x9159015A3070DD17;
	sha2->h3 = 0x152FECD8F70E5939;
	sha2->h4 = 0x67332667FFC00B31;
	sha2->h5 = 0x8EB44A8768581511;
	sha2->h6 = 0xDB0C2E0D64F98FA7;
	sha2->h7 = 0x47B5481DBEFA4FA4;
	sha2->base.backup = (t_hash*)backup;
	return (&sha2->base);
}

t_virtual_table	g_vtable = {
	0, sha512_round, 0, sha512_prepare_block, sha512_copy_hash,
	sha512_add_hash, sha512_256_hash_to_string, 0, v_process_block_64,
	0, create_last_block_64
};
t_hash			g_base = { &g_vtable, 0, TYPE_SHA_512_256, 1, 1, 1, 128, 0 };

t_hash			*sha512_256_create(void)
{
	t_sha512_hash						*sha2;
	t_sha512_hash						*backup;

	sha2 = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	backup = (t_sha512_hash*)malloc(sizeof(t_sha512_hash));
	if (!sha2 || !backup)
		exit(1);
	ft_memcpy(&sha2->base, &g_base, sizeof(g_base));
	ft_memcpy(&backup->base, &g_base, sizeof(g_base));
	sha2->h0 = 0x22312194FC2BF72C;
	sha2->h1 = 0x9F555FA3C84C64C2;
	sha2->h2 = 0x2393B86B6F53B151;
	sha2->h3 = 0x963877195940EABD;
	sha2->h4 = 0x96283EE2A88EFFE3;
	sha2->h5 = 0xBE5E1E2553863992;
	sha2->h6 = 0x2B0199FC2C85B8AA;
	sha2->h7 = 0x0EB72DDC81C52CA2;
	sha2->base.backup = (t_hash*)backup;
	return (&sha2->base);
}
