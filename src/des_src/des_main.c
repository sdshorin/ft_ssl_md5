/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:34:18 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 00:40:08 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int	is_des_command(char *command)
{
	if (!ft_strcmp(command, "des"))
		return (1);
	if (!ft_strcmp(command, "des-ecb"))
		return (1);
	if (!ft_strcmp(command, "des-cbc"))
		return (1);
	return (0);
}

void	des_parse_flags(t_des_flags *flags, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("-a", *argv))
			flags->use_base64 = 1;
		else if (!ft_strcmp("-V", *argv))
			flags->verbpose = 1;
		else if (!ft_strcmp("-d", *argv))
			flags->decrypt = 1;
		else if (!ft_strcmp("-e", *argv))
			flags->decrypt = 0;
		else if (++i == argc)
			exit_error_unknown_flag(*argv);
		else if (!ft_strcmp("-i", *argv) || !ft_strcmp("-o", *argv))
			des_parse_files_flags(argv++, flags);
		else if (!ft_strcmp("-k", *argv) || !ft_strcmp("-p", *argv)
			|| !ft_strcmp("-s", *argv) || !ft_strcmp("-v", *argv))
			des_parse_security_flags(argv++, flags);
		else
			exit_error_unknown_flag(*argv);
		i++;
		argv++;
	}
}

void	exe_des_command(int argc, char **argv)
{
	t_des_flags		flags;

	ft_bzero((void *)&flags, sizeof(t_des_flags));
	flags.command = *argv;
	argv++;
	argc--;
	des_parse_flags(&flags, argc, argv);
	des_work(&flags);
}
