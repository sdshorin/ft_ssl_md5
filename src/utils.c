/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:57:31 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "hash.h"
#include "libft.h"
#include "stdio.h"

void	uint32_to_hash(t_hash *hash, char *dest, uint32_t reg)
{
	int				i;
	char			*hex_char;
	unsigned char	*bytes;
	int				n;

	i = 0;
	hex_char = "0123456789abcdef";
	bytes = (unsigned char *)&reg;
	while (i < 4)
	{
		n = i;
		if (hash->invert_bytes_in_string)
			n = 3 - i;
		dest[i * 2] = hex_char[bytes[n] >> 4];
		dest[i * 2 + 1] = hex_char[bytes[n] & 0x0F];
		i++;
	}
}

void	uint64_to_hash(t_hash *hash, char *dest, uint64_t reg)
{
	int				i;
	char			*hex_char;
	unsigned char	*bytes;
	int				n;

	i = 0;
	hex_char = "0123456789abcdef";
	bytes = (unsigned char *)&reg;
	while (i < 8)
	{
		n = i;
		if (hash->invert_bytes_in_string)
			n = 7 - i;
		dest[i * 2] = hex_char[bytes[n] >> 4];
		dest[i * 2 + 1] = hex_char[bytes[n] & 0x0F];
		i++;
	}
}

void	ft_swipe(unsigned char *a, unsigned char *b)
{
	if (*a == *b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void	reverse_byte_order_64(uint64_t *all_data)
{
	unsigned char	*data;

	data = (unsigned char *)all_data;
	ft_swipe(data, data + 7);
	ft_swipe(data + 1, data + 6);
	ft_swipe(data + 2, data + 5);
	ft_swipe(data + 3, data + 4);
}

void	reverse_byte(unsigned char *byte)
{
	unsigned char	result;
	int				i;

	i = 0;
	result = 0;
	while (i < 8)
	{
		result |= ((*byte & (0x1 << i)) >> i) << (7 - i);
		i++;
	}
	*byte = result;
}
