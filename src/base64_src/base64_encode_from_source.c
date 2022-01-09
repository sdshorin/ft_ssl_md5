/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode_from_source.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:39:15 by bjesse            #+#    #+#             */
/*   Updated: 2022/01/08 00:07:52 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_ssl_md5.h"

void	base64_encode_from_string(char *source, int fd_output)
{
	unsigned int	len;
	char	out_buff[BASE64_BLOCK_SIZE/3*4];

	len = ft_strlen(source);
	while (len > BASE64_BLOCK_SIZE)
	{
		process_base64_block((unsigned char*)source, out_buff);
		write(fd_output, out_buff, BASE64_BLOCK_SIZE/3*4);
		source += BASE64_BLOCK_SIZE;
		len -= BASE64_BLOCK_SIZE;
	}
	ft_bzero(out_buff, BASE64_BLOCK_SIZE/3*4);
	process_base64_last_block((unsigned char*)source, len, out_buff);
	ft_putendl_fd(out_buff, fd_output);
}


void	base64_encode_from_file(int fd_source, int fd_output)
{
	unsigned char	buff[BASE64_BLOCK_SIZE];
	char	out_buff[BASE64_BLOCK_SIZE/3*4];
	int		ch_read;
	int		i;

	while ((ch_read = read(fd_source, buff, BASE64_BLOCK_SIZE))
											== BASE64_BLOCK_SIZE)
		process_base64_block(buff, out_buff);
	i = ch_read;
	while(i < BASE64_BLOCK_SIZE)
		buff[i++] = '\0';
	ft_bzero(out_buff, BASE64_BLOCK_SIZE/3*4);
	process_base64_last_block(buff, ch_read, out_buff);
	ft_putendl_fd(out_buff, fd_output);
}
