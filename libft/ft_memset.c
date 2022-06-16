/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:04:14 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:16:35 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	byte;
	unsigned char	*a;

	a = (unsigned char *)b;
	byte = (unsigned char)c;
	while (len-- > 0)
		*a++ = byte;
	return (b);
}
