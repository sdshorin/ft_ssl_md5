/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode_from_source.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:53:30 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/16 01:53:31 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ssl_md5.h"

int base64_get_char_num(char c)
{
	if (c >= 'A' && c <='Z')
		return (c - 'A');
	if (c >= 'a' && c <='z')
		return (26 + c - 'a');
	if (c >= '0' && c <='9')
		return (52 + c - '0');
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	exit_error_bad_input();
	return (0);
}

int		decode_base64_4char(char *str, char *decoded_buff)
{
	int i;
	unsigned int data;

	i = 0;
	data = 0;
	while (i < 4)
	{
		if (*(str + i) == '=')
			break ;
		data |= (base64_get_char_num(*(str + i)) & 0x3F) << 6 * (3 - i);
		i++;
	}
	if (i == 0 || i == 1)
		return -1;
	ft_swipe((void*)&data, (void*)&data + 2);
	ft_memcpy(decoded_buff, (void*)&data, i - 1);
	// write(fd_output, (void*)&data, i - 1);
	return (i - 1);
}

int		_decode_base64_block(char *buff, char *decoded_buff, size_t buff_size)
{
	size_t i;
	int decoded_bytes;
	size_t decoded_len;

	i = 0;
	decoded_len = 0;
	if (!buff_size % 4)
		return 1;
	while (i * 4 < buff_size && *(buff + i * 4) != '=')
	{
		decoded_bytes = decode_base64_4char(buff + i * 4, decoded_buff + i * 3);
		if (decoded_bytes == -1)
			return -1;
		decoded_len += decoded_bytes;
		if (decoded_bytes < 3)
			break;
		i += 1;
	}
	return decoded_len;
}

int read_base64(int fd_source, char *buff, size_t buff_size)
{
	char	read_buff[BASE64_BLOCK_SIZE];
	int i;
	int j;
	int ch_read;

	i = 0;
	while (buff_size - i > 0 && (ch_read = read(fd_source,
		read_buff, ft_min(buff_size - i, BASE64_BLOCK_SIZE))))
	{
		if (ch_read == -1)
			return (ch_read);
		j = 0;
		while (j < ch_read)
		{
			if ((read_buff[j] == '\n' || read_buff[j] == ' ') && ++j)
				continue ;
			buff[i++] = read_buff[j++];
		}
	}
	return (i);
}


int decode_base64_block(char *buff, char *decoded_buff, size_t buff_size)
{
	int decodet_bytes;

	decodet_bytes = _decode_base64_block(buff, decoded_buff, buff_size);
	if (decodet_bytes == -1)
		exit_error_bad_input();
	return decodet_bytes;
}


void	base64_decode_from_file(int fd_source, int fd_output)
{
	char	buff[BASE64_BLOCK_SIZE];
	char	decoded_buff[BASE64_BLOCK_SIZE / 4 * 3];
	int		ch_read;
	int		i;

	while ((ch_read = read_base64(fd_source, buff, BASE64_BLOCK_SIZE))
											== BASE64_BLOCK_SIZE)
	{
		i = decode_base64_block(buff, decoded_buff, BASE64_BLOCK_SIZE);
		write(fd_output, decoded_buff, i);
	}
	i = ch_read;
	if (ch_read < 0)
		exit_error_bad_input();
	while(i < BASE64_BLOCK_SIZE)
		buff[i++] = '=';
	i = decode_base64_block(buff, decoded_buff, BASE64_BLOCK_SIZE);
	write(fd_output, decoded_buff, i);
}
