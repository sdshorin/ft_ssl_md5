/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 15:55:54 by bjesse            #+#    #+#             */
/*   Updated: 2019/09/14 15:56:03 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_c_vector(t_char_vector *c_vector)
{
	free(c_vector->data);
}

int		init_c_vector(t_char_vector *c_vector)
{
	c_vector->size = 0;
	c_vector->capacity = 16;
	c_vector->data = (char*)malloc(c_vector->capacity * sizeof(char));
	if (!c_vector->data)
		return (1);
	return (0);
}

int		c_vector_push_back(t_char_vector *c_vector, char c)
{
	char	*new_data;

	if (c_vector->size < c_vector->capacity)
	{
		c_vector->data[c_vector->size] = c;
		c_vector->size++;
		return (0);
	}
	c_vector->capacity *= 2;
	new_data = (char*)malloc(c_vector->capacity * sizeof(char));
	if (!new_data)
		return (1);
	ft_memcpy(new_data, c_vector->data,\
						(c_vector->capacity / 2) * sizeof(char));
	free(c_vector->data);
	c_vector->data = new_data;
	c_vector->data[c_vector->size] = c;
	c_vector->size++;
	return (0);
}

char	c_vector_pop_back(t_char_vector *c_vector)
{
	if (c_vector->size <= 0)
		return ('\0');
	c_vector->size--;
	return (c_vector->data[c_vector->size]);
}
