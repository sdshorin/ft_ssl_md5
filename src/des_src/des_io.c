/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_io.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:16:11 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 00:30:55 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

ssize_t	nostop_read(int fd, void *out_buff, size_t buff_size)
{
	char	read_buff[BASE64_BLOCK_SIZE];
	int		i;
	int		j;
	int		ch_read;

	i = 0;
	while (buff_size - i > 0)
	{
		ch_read = read(fd, read_buff,
				ft_min(buff_size - i, BASE64_BLOCK_SIZE));
		if (!ch_read)
			break ;
		if (ch_read == -1)
			return (ch_read);
		j = 0;
		while (j < ch_read)
			((char *)out_buff)[i++] = read_buff[j++];
	}
	return (i);
}

ssize_t	read_wrapper_decode_base_64(int fd, void *out_buff, size_t size)
{
	static t_read_buff	static_buff;
	char				buff[BASE64_BLOCK_SIZE];
	char				decoded_buff[BASE_DES_BLOCK_SIZE];
	int					ch_read;
	int					i;

	if (size > BASE_DES_BLOCK_SIZE)
		return (assert_false(__LINE__));
	if (static_buff.size < (int)size)
	{
		ch_read = read_base64(fd, buff, BASE64_BLOCK_SIZE);
		if (ch_read < 0)
			exit_error_bad_input();
		i = ch_read;
		while (i < BASE64_BLOCK_SIZE)
			buff[i++] = '=';
		i = decode_base64_block(buff, decoded_buff, BASE64_BLOCK_SIZE);
		add_to_static_buff(&static_buff, decoded_buff, i);
	}
	return (read_from_static_buff(&static_buff, out_buff, size));
}

size_t	write_base64_block(const void *buff, char *out_buff, int fd, int flag)
{
	size_t	written_bytes;

	written_bytes = 0;
	process_base64_block((unsigned char *)buff, out_buff);
	if (flag & NEED_NEXT_LINE)
		written_bytes += write_lines(fd, out_buff,
				BASE64_BLOCK_SIZE / 3 * 4, 64);
	else
		written_bytes += write(fd, out_buff, BASE64_BLOCK_SIZE / 3 * 4);
	if (flag & NEED_NEXT_LINE)
		written_bytes += write(fd, "\n", 1);
	return (written_bytes);
}

ssize_t	write_base64(int fd, const void *buff, size_t len, int flag)
{
	char	out_buff[BASE64_BLOCK_SIZE / 3 * 4];
	size_t	last_block_size;
	size_t	written_bytes;

	written_bytes = 0;
	while (len > BASE64_BLOCK_SIZE)
	{
		written_bytes += write_base64_block(buff, out_buff, fd, flag);
		len -= BASE64_BLOCK_SIZE;
		buff += BASE64_BLOCK_SIZE;
	}
	if (len > 0)
	{
		last_block_size = process_base64_last_block(
				(unsigned char *)buff, len, out_buff);
		if (flag & NEED_NEXT_LINE)
			written_bytes += write_lines(fd, out_buff, last_block_size, 64);
		else
			written_bytes += write(fd, out_buff, last_block_size);
	}
	return (written_bytes);
}

ssize_t	write_wrapper(int fd, const void *buff, size_t len, int flag)
{
	flag = -flag;
	return (write(fd, buff, len));
}
