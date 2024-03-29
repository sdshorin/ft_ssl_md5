/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:42:59 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:08:08 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	now_index;

	now_index = 0;
	if (!s || !f)
		return ;
	while (*s)
		(*f)(now_index++, s++);
}
