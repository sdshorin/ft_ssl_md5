/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:29:25 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:17:05 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void	*ans;

	if (size + 1 == 0)
		return (NULL);
	ans = malloc(size + 1);
	if (!ans)
		return (NULL);
	ft_memset(ans, 0, size + 1);
	return ((char *)ans);
}
