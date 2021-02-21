/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:57:25 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/07 19:06:48 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ans;

	ans = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (ans);
}
