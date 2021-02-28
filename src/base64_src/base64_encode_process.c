/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:58:43 by bjesse            #+#    #+#             */
/*   Updated: 2021/03/01 00:37:47 by bjesse           ###   ########.fr       */
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

void	process_base64_last_chars(unsigned char *src, int len, char *dest)
{
	process_base64_3_char(src, dest);
	if(len == 1)
	{
		dest[2] = '=';
		dest[3] = '=';
	}
	else
		dest[3] = '=';
}

void	process_base64_block(unsigned char *source, int fd_output)
{
	char	out[BASE64_BLOCK_SIZE/3*4];
	int		source_pos;

	source_pos = 0;
	while (source_pos < BASE64_BLOCK_SIZE)
	{
		process_base64_3_char(source + source_pos, out + source_pos / 3 * 4);
		source_pos += 3;
	}
	write(fd_output, out, BASE64_BLOCK_SIZE/3*4);
}

void	process_base64_last_block(unsigned char *source, int len,int fd_output)
{
	char	out[BASE64_BLOCK_SIZE/3*4];
	int		source_pos;

	source_pos = 0;
	ft_bzero(out, BASE64_BLOCK_SIZE/3*4);
	while (source_pos <= len - 3)
	{
		process_base64_3_char(source + source_pos, out + source_pos / 3 * 4);
		source_pos += 3;
	}
	if (len % 3 > 0)
		process_base64_last_chars(source + source_pos, len % 3,
													out + source_pos / 3 * 4);
	ft_putendl_fd(out, fd_output);
}
