/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:01:58 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 01:11:47 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int	base64_get_char_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (26 + c - 'a');
	if (c >= '0' && c <= '9')
		return (52 + c - '0');
	if (c == '+')
		return (62);
	if (c == '/')
		return (63);
	exit_error_bad_input();
	return (0);
}

int	base64_get_fd(char *file_name, int to_write, int def)
{
	int		fd;

	if (!file_name)
		return (def);
	if (!to_write)
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0 || read(fd, NULL, 0) < 0)
			exit_error_bad_file(file_name);
		return (fd);
	}
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd < 0 || write(fd, "", 0) < 0)
		exit_error_bad_file(file_name);
	return (fd);
}

void	exit_error_base64(char *command)
{
	if (!ft_strcmp("-i", command) || !ft_strcmp("-o", command)
		|| !ft_strcmp("-s", command))
		exit_error_no_string();
	else
		exit_error_unknown_flag(command);
}
