/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:17 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:18:51 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	const char	*temp;
	char		*temp2;
	int			size;
	char		*ans;

	temp = s1;
	size = 0;
	while (*temp++)
		size++;
	if (size + 1 == 0)
		return (NULL);
	ans = (char *)malloc(size + 1);
	if (!ans)
		return (NULL);
	temp2 = ans;
	while (size-- > 0)
		*ans++ = *s1++;
	*ans = '\0';
	return (temp2);
}
