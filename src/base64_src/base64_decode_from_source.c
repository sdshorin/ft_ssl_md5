/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode_from_source.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:53:30 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/28 23:58:36 by bjesse           ###   ########.fr       */
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

int		decode_base64_4char(char *str, int fd_output)
{
	int i;
	unsigned int data;

	i = 0;
	data = 0;
	while (i < 4)
	{
		if (*(str + i) == '=')
			break ;
		int a = base64_get_char_num(*(str + i)) & 0x3F;
		data |= (base64_get_char_num(*(str + i)) & 0x3F) << 6 * (3 - i);
		i++;
	}
	if (i == 0 || i == 1)
		return 1;
	ft_swipe((void*)&data, (void*)&data + 2);
	write(fd_output, (void*)&data, i - 1);
	return (i < 4);
}

int		decode_base64_block(char *buff, int fd_output)
{
	int i;

	i = 0;
	while (i < BASE64_BLOCK_SIZE * 2)
	{
		if (decode_base64_4char(buff + i, fd_output))
			break;
		i += 4;
	}
	return (i < BASE64_BLOCK_SIZE * 2);
}

int read_base64(int fd_source, char *buff)
{
	char	buff2[BASE64_BLOCK_SIZE * 2];
	int i;
	int j;
	int ch_read;

	i = 0;
	while (BASE64_BLOCK_SIZE * 2 - i > 0 && (ch_read = read(fd_source,
		buff2, BASE64_BLOCK_SIZE * 2 - i)))
	{
		if (ch_read == -1)
			return (ch_read);
		j = 0;
		while (j < ch_read)
		{
			if ((buff2[j] == '\n' || buff2[j] == ' ') && ++j)
				continue ;
			buff[i++] = buff2[j++];
		}
	}
	return (i);
}

void	base64_decode_from_file(int fd_source, int fd_output)
{
	char	buff[BASE64_BLOCK_SIZE * 2];
	int		ch_read;
	int		i;

	while ((ch_read = read_base64(fd_source, buff))
											== BASE64_BLOCK_SIZE * 2)
		if (decode_base64_block(buff, fd_output))
			return ;
	i = ch_read;
	while(i < BASE64_BLOCK_SIZE)
		buff[i++] = '=';
	decode_base64_block(buff, fd_output);
}
