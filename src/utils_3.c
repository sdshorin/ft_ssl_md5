/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:03:27 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "hash.h"
#include "libft.h"
#include "stdio.h"

void	add_to_static_buff(t_read_buff *static_buff, char *decoded_buff,
		ssize_t size)
{
	static_buff->size += size;
	ft_memmove(static_buff->data, decoded_buff, size);
}

ssize_t	read_from_static_buff(t_read_buff *static_buff, char *des_buff,
		ssize_t size)
{
	size = ft_min(size, static_buff->size);
	ft_memmove(des_buff, static_buff->data, size);
	ft_memmove(static_buff->data, static_buff->data + size, size);
	static_buff->size -= size;
	return (size);
}

void	uint64_to_hex(uint64_t reg)
{
	int				i;
	char			*hex_char;
	unsigned char	*bytes;
	int				n;
	char			dest[17];

	i = 0;
	hex_char = "0123456789abcdef";
	bytes = (unsigned char *)&reg;
	while (i < 8)
	{
		n = i;
		dest[i * 2] = hex_char[bytes[n] >> 4];
		dest[i * 2 + 1] = hex_char[bytes[n] & 0x0F];
		i++;
	}
	dest[16] = 0;
}
