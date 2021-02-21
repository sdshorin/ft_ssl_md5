/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:13:12 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/10 22:33:23 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char			to_find;
	char			*ans;

	ans = (char*)(void*)s;
	to_find = (char)c;
	while (*ans && *ans != to_find)
		ans++;
	if (*ans == to_find)
		return (ans);
	else
		return (NULL);
}
