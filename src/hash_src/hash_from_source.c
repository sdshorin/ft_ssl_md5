/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_from_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:51:58 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 22:50:42 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int		is_hash_command(char *command)
{
	if (!ft_strcmp(command, "md5"))
		return (1);
	else if (!ft_strcmp(command, "sha256"))
		return (1);
	else if (!ft_strcmp(command, "sha224"))
		return (1);
	else if (!ft_strcmp(command, "sha512"))
		return (1);
	else if (!ft_strcmp(command, "sha384"))
		return (1);
	else if (!ft_strcmp(command, "sha512/256"))
		return (1);
	return (0);
}

void	print_hash_from_string(char *command, t_hash_flags *flags, char *str)
{
	t_hash	*hash;
	char	*hash_str;

	hash = factory_get_hash_obj(command);
	hash_str = get_hash_from_string(hash, str);
	print_hash(hash_str, str, flags, 0);
	free(hash);
	free(hash_str);
}

void	print_hash_from_file(char *command, t_hash_flags *flags,
													char *file_path)
{
	int		fd;
	t_hash	*hash;
	char	*hash_str;

	fd = open(file_path, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		ft_putstr("Cannot open file ");
		ft_putendl(file_path);
		return ;
	}
	hash = factory_get_hash_obj(command);
	hash_str = get_hash_from_file(hash, fd);
	print_hash(hash_str, file_path, flags, 1);
	free(hash);
	free(hash_str);
	close(fd);
}

char	*read_string_from_input(void)
{
	char *temp_str;
	char *input_str;
	char buffer[129];

	input_str = 0;
	ft_bzero(buffer, 129);
	while (read(0, buffer, 128) > 0 || !input_str)
	{
		temp_str = input_str;
		if (input_str)
			input_str = ft_strjoin(input_str, buffer);
		else
			input_str = ft_strdup(buffer);
		if (!input_str)
			exit(1);
		if (temp_str)
			free(temp_str);
		ft_bzero(buffer, 129);
	}
	return (input_str);
}

void	print_hash_from_input(char *command, t_hash_flags *flags)
{
	t_hash	*hash;
	char	*input_str;
	char	*hash_str;

	input_str = read_string_from_input();
	hash = factory_get_hash_obj(command);
	hash_str = get_hash_from_string(hash, input_str);
	if (flags->p_flag && input_str[ft_strlen(input_str) - 1] == '\n')
		ft_putstr(input_str);
	else if (flags->p_flag)
		ft_putendl(input_str);
	ft_putendl(hash_str);
	free(hash);
	free(hash_str);
	free(input_str);
}
