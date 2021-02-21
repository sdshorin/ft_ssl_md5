/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_interface_32_64.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:56:58 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 03:45:33 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	round_32(t_hash *h, uint32_t *memory, int round_num)
{
	return (h->vtable->round_32(h, memory, round_num));
}

void	prepare_block_32(t_hash *h, uint32_t *block, void *data)
{
	return (h->vtable->prepare_block_32(block, data));
}

void	round_64(t_hash *h, uint64_t *memory, int round_num)
{
	return (h->vtable->round_64(h, memory, round_num));
}

void	prepare_block_64(t_hash *h, uint64_t *block, void *data)
{
	return (h->vtable->prepare_block_64(block, data));
}
