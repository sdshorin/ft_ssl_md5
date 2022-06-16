/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exeptions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:13:47 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/16 23:22:42 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	exit_error_bad_file(char *file_name)
{
	ft_putstr("Cannot open file ");
	ft_putendl(file_name);
	exit(1);
}

void	exit_error_bad_input()
{
	ft_putstr("Bad input");
	exit(1);
}

void exit_error(char *err)
{
	ft_putstr(err);
	exit(1);
}

void	print_unexpected_arg(char *arg)
{
	ft_putstr("ft_ssl: Error: ");
	ft_putstr(arg);
	ft_putstr(" is an invalid command.");
	ft_putendl("Standard commands:");
	ft_putendl("Message Digest commands:");
	ft_putendl("md5 sha256 sha224 sha512 sha384 sha512/256 ");
	ft_putendl("-p, -q, -r, -s");
	ft_putendl("Cipher commands:");
	ft_putendl("base64 des des-ecb des-cbc");
}

void	exit_error_no_string(void)
{
	ft_putendl("Error: no string after -s flag");
	exit(1);
}

void	exit_error_unknown_flag(char *flag)
{
	ft_putstr("Error: unknown flag ");
	ft_putendl(flag);
	exit(1);
}
