/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:41:35 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:08:47 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	long int	len;
	char		*ans;
	char		*temp;

	if (!s1 || !s2)
		return (NULL);
	len = 1 + ft_strlen(s1) + ft_strlen(s2);
	ans = (char *)malloc(len);
	if (!ans)
		return (NULL);
	temp = ans;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (ans);
}
