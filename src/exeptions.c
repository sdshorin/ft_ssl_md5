/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exeptions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:13:47 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:52:26 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	exit_error_bad_file(char *file_name)
{
	ft_putstr("Cannot open file ");
	ft_putendl(file_name);
	exit(1);
}

void	exit_error_bad_input(void)
{
	ft_putstr("Bad input");
	exit(1);
}

void	exit_error(char *err)
{
	ft_putstr(err);
	exit(1);
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
