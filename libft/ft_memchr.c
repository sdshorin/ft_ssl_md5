/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:18:19 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/11 20:56:00 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	cc;

	cc = (unsigned char)c;
	cs = (unsigned char*)s;
	while (n-- > 0)
	{
		if (*cs == cc)
			return ((void*)cs);
		cs++;
	}
	return (NULL);
}
