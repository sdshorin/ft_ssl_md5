/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:15:49 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:06:08 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ans;
	void	*data;

	ans = (t_list *)malloc(sizeof(t_list));
	data = malloc(content_size);
	if (!ans || !data)
		return (NULL);
	if (content)
	{
		data = ft_memcpy(data, content, content_size);
		ans->content = data;
		ans->content_size = content_size;
	}
	else
	{
		ans->content = NULL;
		ans->content_size = 0;
	}
	ans->next = NULL;
	return (ans);
}
