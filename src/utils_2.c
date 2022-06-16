/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:58:24 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "hash.h"
#include "libft.h"
#include "stdio.h"

void	swipe_endian_bytes(unsigned char *all_data, int size)
{
	while (size)
	{
		reverse_byte(all_data + (size - 1));
		size--;
	}
}

void	reverse_byte_order_32(uint32_t *all_data)
{
	unsigned char	*data;

	data = (unsigned char *)all_data;
	ft_swipe(data, data + 3);
	ft_swipe(data + 1, data + 2);
}

ssize_t	write_lines(int fd, const void *buff, size_t len, size_t block_size)
{
	size_t	written_bytes;
	int		write_size;

	written_bytes = 0;
	while (len > 0)
	{
		write_size = ft_min(len, block_size);
		written_bytes += write(fd, buff, write_size);
		buff += write_size;
		len -= write_size;
		written_bytes += write(fd, "\n", 1);
	}
	return (written_bytes);
}

int	assert_false(int line)
{
	ft_putstr("Error in code, assert false on line");
	ft_putnbr(line);
	ft_putchar('\n');
	exit(1);
	return (0);
}

int	open_file(char *path, int mode)
{
	int	fd;

	fd = open(path, mode);
	if (fd < 0)
		exit_error_bad_file(path);
	if (mode & O_RDONLY && read(fd, NULL, 0) < 0)
		exit_error_bad_file(path);
	if (mode & O_WRONLY && write(fd, "", 0) < 0)
		exit_error_bad_file(path);
	return (fd);
}
