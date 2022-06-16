/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:47:29 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 00:48:17 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

size_t	des_add_padding(unsigned char *buff, size_t size)
{
	int				i;
	unsigned char	padding_byte;

	padding_byte = 8 - size % 8;
	i = (int)padding_byte;
	while (i > 0)
	{
		buff[size - 1 + i] = padding_byte;
		i--;
	}
	return (size + padding_byte);
}

size_t	des_remove_padding(unsigned char *buff, size_t size)
{
	int				i;
	unsigned char	padding_byte;

	if (size % 8 || size < 8)
		assert_false(__LINE__);
	padding_byte = buff[size - 1];
	if (padding_byte < 1 || padding_byte > 8)
		assert_false(__LINE__);
	i = (int)padding_byte;
	size -= padding_byte;
	while (i > 0)
	{
		buff[size - 1 + i] = 0;
		i--;
	}
	return (size);
}

void	print_salt_to_file(t_des_env *env, t_des_flags *flags)
{
	write(env->fd_out, "Salted__", 8);
	write(env->fd_out, flags->salt, 8);
}

uint64_t	permutation(uint64_t block, int *premut_table, int size)
{
	uint64_t	data;
	int			i;

	i = 0;
	data = 0;
	while (i < size)
	{
		data |= ((block >> (premut_table[i] - 1)) & 0x01) << i;
		i++;
	}
	return (data);
}
