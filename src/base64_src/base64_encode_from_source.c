/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode_from_source.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:39:15 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 23:09:32 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ssl_md5.h"

void	base64_encode_from_string(char *source, int fd_output)
{
	unsigned int	len;

	len = ft_strlen(source);
	while (len > BASE64_BLOCK_SIZE)
	{
		process_base64_block(source, fd_output);
		source += BASE64_BLOCK_SIZE;
		len -= BASE64_BLOCK_SIZE;
	}
	process_base64_last_block(source, len, fd_output);
}


void	base64_encode_from_file(int fd_source, int fd_output)
{
	char	buff[BASE64_BLOCK_SIZE];
	int		ch_read;
	int		i;

	while ((ch_read = read(fd_source, buff, BASE64_BLOCK_SIZE))
											== BASE64_BLOCK_SIZE)
		process_base64_block(buff, fd_output);
	i = ch_read;
	while(i < BASE64_BLOCK_SIZE)
		buff[i++] = '\0';
	process_base64_last_block(buff, ch_read, fd_output);
}
