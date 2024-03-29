/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_interface_32_64_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:53:50 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:22:11 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	v_process_block(t_hash *hash, void *data)
{
	if (hash->vtable->v_process_block_32)
		return (hash->vtable->v_process_block_32(hash, data));
	return (hash->vtable->v_process_block_64(hash, data));
}

int	create_last_block(t_hash *hash, void **data, int block_size)
{
	if (hash->vtable->create_last_block_32)
		return (hash->vtable->create_last_block_32(hash, data, block_size));
	return (hash->vtable->create_last_block_64(hash, data, block_size));
}
