/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode_from_source.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:53:30 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 23:15:13 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ssl_md5.h"

void	base64_decode_from_file(int fd_source, int fd_output)
{
	fd_source = 0;
	fd_output = 0;
	// char	buff[BASE64_BLOCK_SIZE];
	// int		ch_read;
	// int		i;

	// while ((ch_read = read(fd_source, buff, BASE64_BLOCK_SIZE))
	// 										== BASE64_BLOCK_SIZE)
	// 	process_base64_block(buff, fd_output);
	// i = ch_read;
	// while(i < BASE64_BLOCK_SIZE)
	// 	buff[i++] = '\0';
	// process_base64_last_block(buff, ch_read, fd_output);
}
