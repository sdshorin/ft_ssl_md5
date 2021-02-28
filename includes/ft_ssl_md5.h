/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 04:11:13 by bjesse            #+#    #+#             */
/*   Updated: 2021/03/01 00:38:23 by bjesse           ###   ########.fr       */
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
void			exit_error_bad_input();

void			exit_error_unknown_flag(char *flag);
void			exit_error_bad_file(char *file_name);


void			init_hash_flags(t_hash_flags *flags);

void			exe_hash_command(int argc, char **argv);
void			ft_swipe(unsigned char *a, unsigned char *b);



typedef struct	s_base64_flags {
	unsigned char	d_flag;
	unsigned char	e_flag;
	unsigned char	s_flag_completed;
	char			*source;
	char			*output;
}				t_base64_flags;

# define BASE64_BLOCK_SIZE 126

int				is_base64_command(char *command);

void			process_base64_block(unsigned char *source, int fd_output);
void			process_base64_last_block(unsigned char *source, int len,int fd_output);
void			exe_base64_command(int argc, char **argv);
void			base64_decode_from_file(int fd_source, int fd_output);
void			base64_encode_from_file(int fd_source, int fd_output);
void			base64_encode_from_string(char *source, int fd_output);


#endif
