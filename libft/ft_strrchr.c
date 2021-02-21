/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:16:23 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/11 21:04:05 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	to_find;
	char	*find;

	find = NULL;
	to_find = (char)c;
	while (*s)
	{
		if (*s == to_find)
			find = (char*)(void*)s;
		s++;
	}
	if (*s == to_find)
		return ((char*)(void*)s);
	else
		return (find);
}
