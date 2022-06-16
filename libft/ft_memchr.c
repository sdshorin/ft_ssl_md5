/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:18:19 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:16:27 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cs;
	unsigned char	cc;

	cc = (unsigned char)c;
	cs = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*cs == cc)
			return ((void *)cs);
		cs++;
	}
	return (NULL);
}
