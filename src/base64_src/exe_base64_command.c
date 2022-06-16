/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_base64_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 21:36:33 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:11:40 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int	is_base64_command(char *command)
{
	if (!ft_strcmp(command, "base64"))
		return (1);
	return (0);
}

void	init_base64_flags(t_base64_flags *flags)
{
	flags->d_flag = 0;
	flags->e_flag = 1;
	flags->source = 0;
	flags->output = 0;
	flags->s_flag_completed = 0;
}

void	print_base64_from_string(char *string, t_base64_flags *flags)
{
	base64_encode_from_string(string, 0);
	flags->s_flag_completed = 1;
}

int	work_with_flags_base64(t_base64_flags *flags, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("-e", *argv))
			flags->e_flag = 1;
		else if (!ft_strcmp("-d", *argv))
			flags->d_flag = 1;
		else if (++i == argc)
			exit_error_base64(*argv);
		else if (!ft_strcmp("-i", *argv))
			flags->source = *(++argv);
		else if (!ft_strcmp("-o", *argv))
			flags->output = *(++argv);
		else if (!ft_strcmp("-s", *argv))
			print_base64_from_string(*(++argv), flags);
		else
			exit_error_unknown_flag(*argv);
		i++;
		argv++;
	}
	return (i);
}

void	exe_base64_command(int argc, char **argv)
{
	t_base64_flags	flags;
	int				source_fd;
	int				output_fd;

	init_base64_flags(&flags);
	argv++;
	argc--;
	work_with_flags_base64(&flags, argc, argv);
	if (flags.s_flag_completed)
		return ;
	source_fd = base64_get_fd(flags.source, 0, 0);
	output_fd = base64_get_fd(flags.output, 1, 1);
	if (flags.e_flag && !flags.d_flag)
		base64_encode_from_file(source_fd, output_fd);
	else
		base64_decode_from_file(source_fd, output_fd);
	if (output_fd != 1)
		close(output_fd);
	if (source_fd != 0)
		close(source_fd);
}
