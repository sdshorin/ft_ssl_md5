/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:16:23 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:16:14 by sergey           ###   ########.fr       */
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
			find = (char *)(void *)s;
		s++;
	}
	if (*s == to_find)
		return ((char *)(void *)s);
	else
		return (find);
}
