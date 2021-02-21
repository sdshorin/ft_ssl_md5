/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjesse <bjesse@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:14:01 by bjesse            #+#    #+#             */
/*   Updated: 2021/02/21 04:12:11 by bjesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	init_hash_flags(t_hash_flags *flags)
{
	flags->p_flag = 0;
	flags->q_flag = 0;
	flags->r_flag = 0;
	flags->s_flag = 0;
	flags->printed_hash_from_input = 0;
	flags->flags_parsed = 0;
}
