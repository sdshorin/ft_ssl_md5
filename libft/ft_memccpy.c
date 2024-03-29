/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:50:54 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:14:33 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	unsigned char	cc;

	cc = (unsigned char)c;
	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	while (n-- > 0)
	{
		*cdst = *csrc;
		if (*cdst == cc)
			return (++cdst);
		cdst++;
		csrc++;
	}
	return (NULL);
}
