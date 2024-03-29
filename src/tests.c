/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 01:59:06 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 02:00:20 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	test_des_1(void)
{
	unsigned char	buff[9];
	t_des_env		env;
	uint64_t		result;

	ft_memcpy(env.key, (unsigned char *)"IEOFIT#1", 8);
	des_create_keys(&env);
	ft_strcpy((char *)buff, "IEOFIT#1");
	result = process_des_ecb_block(&env, *(uint64_t *)&buff);
	if (result == 18341058840126108615uLL)
		ft_putstr("test 1 des OK!\n");
	else
	{
		ft_putstr("test 1 des FAIL!\n");
		exit(1);
	}
}

void	tests(void)
{
	test_des_1();
}

int	is_test_command(char *command)
{
	if (!ft_strcmp(command, "test"))
		return (1);
	return (0);
}
