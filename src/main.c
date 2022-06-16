/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 02:13:23 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 01:58:54 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void	print_usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		print_usage();
	else if (is_hash_command(argv[1]))
		exe_hash_command(argc - 1, argv + 1);
	else if (is_base64_command(argv[1]))
		exe_base64_command(argc - 1, argv + 1);
	else if (is_des_command(argv[1]))
		exe_des_command(argc - 1, argv + 1);
	else if (is_test_command(argv[1]))
		tests();
	else
		print_unexpected_arg(argv[1]);
}
