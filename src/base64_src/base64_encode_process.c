/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:58:43 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/15 14:31:47 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

char	*g_base64_chars =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void	process_base64_3_char(unsigned char *src, char *dest)
{
	dest[0] = g_base64_chars[(*src) >> 2];
	dest[1] = g_base64_chars[((*src & 0x3) << 4) + (*(src + 1) >> 4)];
	dest[2] = g_base64_chars[(((*(src + 1)) & 0xF) << 2) + (*(src + 2) >> 6)];
	dest[3] = g_base64_chars[*(src + 2) & 0x3F];
}

size_t	process_base64_last_chars(unsigned char *src, int len, char *dest)
{
	process_base64_3_char(src, dest);
	if(len == 1)
	{
		dest[2] = '=';
		dest[3] = '=';
	}
	else
		dest[3] = '=';
	return 4;
}

void	process_base64_block(unsigned char *source, char *out_buff)
{
	int		source_pos;

	source_pos = 0;
	while (source_pos < BASE64_BLOCK_SIZE)
	{
		process_base64_3_char(source + source_pos, out_buff + source_pos / 3 * 4);
		source_pos += 3;
	}
}

size_t	process_base64_last_block(unsigned char *source, int len, char *out_buff)
{
	int		source_pos;
	size_t out_pos;

	source_pos = 0;
	out_pos = 0;
	// ft_bzero(out_buff, BASE64_BLOCK_SIZE/3*4);
	while (source_pos <= len - 3)
	{
		process_base64_3_char(source + source_pos, out_buff + out_pos);
		source_pos += 3;
		out_pos += 4;
	}
	if (len % 3 > 0)
		out_pos += process_base64_last_chars(source + source_pos, len % 3,
													out_buff + out_pos);
	return out_pos;

}
