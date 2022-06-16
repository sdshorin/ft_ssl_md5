/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:21:49 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:11:45 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*temph;
	const char	*tempn;

	if (!*haystack && *needle)
		return (NULL);
	if (!*needle)
		return ((char *)(void *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			temph = haystack;
			tempn = needle;
			while (*tempn && *temph && *temph == *tempn)
			{
				temph++;
				tempn++;
			}
			if (*tempn == '\0')
				return ((char *)(void *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
