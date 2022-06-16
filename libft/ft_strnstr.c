/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:20:54 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:05:11 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		string_len;

	string_len = ft_strlen(needle);
	if ((!*haystack && *needle) || ft_strlen(needle) > len)
		return (NULL);
	if (!*needle)
		return ((char *)(void *)haystack);
	len = len - ft_strlen(needle) + 1;
	while (*haystack && len > 0)
	{
		if (len > 0 && ft_strncmp(haystack, needle, string_len) == 0)
			return ((char *)(void *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
