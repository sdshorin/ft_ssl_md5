/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:07:49 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/11 21:03:24 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*ans;

	ans = dst;
	while (*src && len != 0)
	{
		len--;
		*dst++ = *src++;
	}
	if (len == 0)
		return (ans);
	else
		while (len--)
			*dst++ = '\0';
	return (ans);
}
