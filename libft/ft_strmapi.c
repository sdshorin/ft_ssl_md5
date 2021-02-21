/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 22:11:05 by bjesse            #+#    #+#             */
/*   Updated: 2019/04/25 22:44:07 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	char	*ans;
	char	*temp;
	int		now_index;

	now_index = 0;
	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	if (size + 1 == 0)
		return (NULL);
	ans = ft_memalloc(size + 1);
	if (!ans)
		return (NULL);
	temp = ans;
	while (size-- > 0)
		*temp++ = (*f)(now_index++, *s++);
	return (ans);
}
