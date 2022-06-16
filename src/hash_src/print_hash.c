/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 03:22:37 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:22:25 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	print_hash_type(char *type)
{
	char	c;

	while (*type)
	{
		c = *type;
		if (c > 96 && c < 123)
			c -= 32;
		write(1, &c, 1);
		type++;
	}
}

void	print_source(char *source, int is_file)
{
	if (!is_file)
		write(1, "\"", 1);
	ft_putstr(source);
	if (!is_file)
		write(1, "\"", 1);
}

void	print_hash(char *hash, char *source, t_hash_flags *flags, int is_file)
{
	if (!flags->q_flag && !flags->r_flag)
	{
		print_hash_type(flags->command);
		write(1, " (", 2);
		print_source(source, is_file);
		write(1, ") = ", 4);
		ft_putendl(hash);
	}
	else if (!flags->q_flag)
	{
		ft_putstr(hash);
		write(1, " ", 1);
		print_source(source, is_file);
		write(1, "\n", 1);
	}
	else
		ft_putendl(hash);
}
