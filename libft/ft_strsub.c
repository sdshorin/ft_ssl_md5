/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:31:26 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:20:37 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ans;
	size_t	now;

	now = 0;
	ans = (char *)malloc(len + 1);
	if (!s || !ans || len + 1 < len)
		return (NULL);
	while (now < len)
	{
		ans[now] = s[start + now];
		now++;
	}
	ans[now] = '\0';
	return (ans);
}
