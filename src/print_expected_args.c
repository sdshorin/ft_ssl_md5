/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expected_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:53:07 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 02:00:53 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

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
