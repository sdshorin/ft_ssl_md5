/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 17:09:41 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:18:19 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	int				des;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	des = 1;
	if (dst > src)
	{
		des = -1;
		cdst += len - 1;
		csrc += len - 1;
	}
	while (len-- > 0)
	{
		*cdst = *csrc;
		cdst = cdst + des;
		csrc = csrc + des;
	}
	return (dst);
}
