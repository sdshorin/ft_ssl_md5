/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:23:25 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:19:52 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

char	*sha512_256_hash_to_string(t_hash *hash_base)
{
	char			*hash_str;
	int				i;
	t_sha512_hash	*hash;

	i = 0;
	hash = (t_sha512_hash *)hash_base;
	hash_str = ft_memalloc(65);
	if (!hash_str)
		exit(1);
	uint64_to_hash(hash_base, hash_str, hash->h0);
	uint64_to_hash(hash_base, hash_str + 16, hash->h1);
	uint64_to_hash(hash_base, hash_str + 32, hash->h2);
	uint64_to_hash(hash_base, hash_str + 48, hash->h3);
	return (hash_str);
}

char	*sha384_hash_to_string(t_hash *hash_base)
{
	char			*hash_str;
	int				i;
	t_sha512_hash	*hash;

	i = 0;
	hash = (t_sha512_hash *)hash_base;
	hash_str = ft_memalloc(97);
	if (!hash_str)
		exit(1);
	uint64_to_hash(hash_base, hash_str, hash->h0);
	uint64_to_hash(hash_base, hash_str + 16, hash->h1);
	uint64_to_hash(hash_base, hash_str + 32, hash->h2);
	uint64_to_hash(hash_base, hash_str + 48, hash->h3);
	uint64_to_hash(hash_base, hash_str + 64, hash->h4);
	uint64_to_hash(hash_base, hash_str + 80, hash->h5);
	return (hash_str);
}

char	*sha224_hash_to_string(t_hash *hash_base)
{
	char			*hash_str;
	int				i;
	t_sha256_hash	*hash;

	i = 0;
	hash = (t_sha256_hash *)hash_base;
	hash_str = ft_memalloc(57);
	if (!hash_str)
		exit(1);
	uint32_to_hash(hash_base, hash_str, hash->h0);
	uint32_to_hash(hash_base, hash_str + 8, hash->h1);
	uint32_to_hash(hash_base, hash_str + 16, hash->h2);
	uint32_to_hash(hash_base, hash_str + 24, hash->h3);
	uint32_to_hash(hash_base, hash_str + 32, hash->h4);
	uint32_to_hash(hash_base, hash_str + 40, hash->h5);
	uint32_to_hash(hash_base, hash_str + 48, hash->h6);
	return (hash_str);
}
