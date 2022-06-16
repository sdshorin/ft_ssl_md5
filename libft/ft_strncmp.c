/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:24:07 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:17:59 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)(void *)s1;
	cs2 = (unsigned char *)(void *)s2;
	if (n == 0)
		return (0);
	if (!*s2)
		return (*cs1 - *cs2);
	while (*cs1 && *cs1 == *cs2 && n)
	{
		n--;
		cs1++;
		cs2++;
	}
	if (n == 0)
		return (0);
	return (*cs1 - *cs2);
}
