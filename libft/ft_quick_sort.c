/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 23:08:00 by bjesse            #+#    #+#             */
/*   Updated: 2019/11/02 23:08:10 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quick_step(int *num, int first, int last)
{
	int i;
	int j;
	int temp;

	i = first;
	j = last;
	while (i < j)
	{
		while (num[i] <= num[first] && i < last)
			i++;
		while (num[j] > num[first])
			j--;
		if (i < j)
		{
			temp = num[i];
			num[i] = num[j];
			num[j] = temp;
		}
	}
	return (j);
}

void		ft_quick_sort(int *number, int first, int last)
{
	int j;
	int temp;

	if (first < last)
	{
		j = quick_step(number, first, last);
		temp = number[first];
		number[first] = number[j];
		number[j] = temp;
		ft_quick_sort(number, first, j - 1);
		ft_quick_sort(number, j + 1, last);
	}
}
