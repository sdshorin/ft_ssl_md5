/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:13:12 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:07:33 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char			to_find;
	char			*ans;

	ans = (char *)(void *)s;
	to_find = (char)c;
	while (*ans && *ans != to_find)
		ans++;
	if (*ans == to_find)
		return (ans);
	else
		return (NULL);
}
