/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:58:31 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 02:59:45 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void	copy_hash(t_hash *copy, t_hash *source)
{
	return (copy->vtable->copy_hash(copy, source));
}

void	add_hash(t_hash *base, t_hash *to_add)
{
	return (base->vtable->add_hash(base, to_add));
}

char	*hash_to_string(t_hash *h)
{
	return (h->vtable->hash_to_string(h));
}
