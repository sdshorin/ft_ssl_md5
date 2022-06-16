/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 00:24:36 by sergey           ###   ########.fr       */
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

void	reverse_byte_order_64(uint64_t *all_data)
{
	unsigned char *data;

	data = (unsigned char*)all_data;
	ft_swipe(data, data + 7);
	ft_swipe(data + 1, data + 6);
	ft_swipe(data + 2, data + 5);
	ft_swipe(data + 3, data + 4);
}

void reverse_byte(unsigned char *byte)
{
	unsigned char result;
	int i;

	i = 0;
	result = 0;
	while (i < 8)
	{
		result |= ((*byte & (0x1 << i)) >> i) << (7 - i);
		i++;
	}
	*byte = result;

}
// swap_endian - reverse_bytes
void swipe_endian_bytes(unsigned char *all_data, int size)
{
	while (size)
	{
		reverse_byte(all_data + (size - 1));
		size--;
	}
}

void	reverse_byte_order_32(uint32_t *all_data)
{
	unsigned char *data;

	data = (unsigned char*)all_data;
	ft_swipe(data, data + 3);
	ft_swipe(data + 1, data + 2);
}


#include "stdio.h"
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

void print_binary(uint64_t num)
{

	// unsigned int a = 20;
	//unsigned char b = 1;
	//int c = *b;
	//int d = *(b + 3);
	for (int i=0; i < 64; i++){
		printf("%c", (num >> i & 0x01 ? '1' : '0'));
		if (!((i + 1) % 8))
			printf(".");
	}
	printf("\n");
}

void print_binary_32(uint32_t num)
{
	for (int i=0; i < 32; i++){
		printf("%c", (num >> i & 0x01 ? '1' : '0'));
		if (!((i + 1) % 8))
			printf(".");
	}
	printf("\n");
}


ssize_t write_lines(int fd, const void *buff, size_t len, size_t block_size) {
	size_t written_bytes;

	written_bytes = 0;
	while (len > 0) {
		int write_size = ft_min(len, block_size);
		written_bytes += write(fd, buff, write_size);
		buff += write_size;
		len -= write_size;
		written_bytes += write(fd, "\n", 1);
	}
	return written_bytes;
}


int assert_false(int line)
{
	ft_putstr("Error in code, assert false on line");
	ft_putnbr(line);
	ft_putchar('\n');
	exit(1);
	return 0;
}





int open_file(char *path, int mode)
{
	int fd;

	fd = open(path, mode);
	if (fd < 0)
		exit_error_bad_file(path);
	if (mode & O_RDONLY && read(fd, NULL, 0) < 0)
		exit_error_bad_file(path);
	if (mode & O_WRONLY && write(fd, "", 0) < 0)
		exit_error_bad_file(path);
	return (fd);
}

void	uint64_to_hex(uint64_t reg)
{
	int				i;
	char			*hex_char;
	unsigned char	*bytes;
	int				n;
	char dest[17];

	i = 0;
	hex_char = "0123456789abcdef";
	bytes = (unsigned char*)&reg;
	while (i < 8)
	{
		n = i;
		dest[i * 2] = hex_char[bytes[n] >> 4];
		dest[i * 2 + 1] = hex_char[bytes[n] & 0x0F];
		i++;
	}
	dest[16] = 0;
	printf("hex: %s\n", dest);
}



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



