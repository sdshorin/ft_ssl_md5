/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 04:00:16 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "hash.h"
#include "libft.h"

void	uint32_to_hash(t_hash *hash, char *dest, uint32_t reg)
{
	int				i;
	char			*hex_char;
	unsigned char	*bytes;
	int				n;

	i = 0;
	hex_char = "0123456789abcdef";
	bytes = (unsigned char*)&reg;
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
	bytes = (unsigned char*)&reg;
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

void	swipe_endian_64(uint64_t *all_data_size)
{
	unsigned char *data;

	data = (unsigned char*)all_data_size;
	ft_swipe(data, data + 7);
	ft_swipe(data + 1, data + 6);
	ft_swipe(data + 2, data + 5);
	ft_swipe(data + 3, data + 4);
}

void	swipe_endian_32(uint32_t *all_data_size)
{
	unsigned char *data;

	data = (unsigned char*)all_data_size;
	ft_swipe(data, data + 3);
	ft_swipe(data + 1, data + 2);
}
