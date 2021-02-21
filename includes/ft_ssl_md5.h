/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 04:11:13 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 04:14:17 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"
# include <fcntl.h>
# include "hash.h"

typedef struct	s_hash_flags {
	unsigned char	p_flag;
	unsigned char	q_flag;
	unsigned char	r_flag;
	unsigned char	s_flag;
	unsigned char	flags_parsed;
	unsigned char	printed_hash_from_input;
	char			*command;
}				t_hash_flags;

t_hash			*factory_get_hash_obj(char *command);
void			print_hash(char *hash, char *source, t_hash_flags *flags,
																int is_file);
int				is_hash_command(char *command);

void			print_hash_from_string(char *command, t_hash_flags *flags,
																	char *str);
void			print_hash_from_file(char *command, t_hash_flags *flags,
															char *file_path);
void			print_hash_from_input(char *command, t_hash_flags *flags);

void			print_unexpected_arg();
void			exit_error_no_string();
void			exit_error_unknown_flag(char *flag);

void			init_hash_flags(t_hash_flags *flags);

#endif
