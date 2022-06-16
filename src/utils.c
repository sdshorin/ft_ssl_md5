/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:17:03 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/16 23:00:44 by bjesse           ###   ########.fr       */
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


