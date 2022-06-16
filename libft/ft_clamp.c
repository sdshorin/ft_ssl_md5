/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:27:51 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:06:32 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_clamp(int value, int min, int max)
{
	if (value > min && value < max)
		return (value);
	else if (value < min)
		return (min);
	return (max);
}
