/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 22:36:27 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:19:59 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	unsigned long long		ans;
	int						sig;

	sig = 0;
	ans = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sig = -1;
	while (*str >= '0' && *str <= '9')
	{
		if ((ans > 922337203685477580 || (ans == 922337203685477580
					&& *str > '7')) && sig == 0)
			return (-1);
		else if ((ans > 922337203685477580 || (ans == 922337203685477580
					&& *str > '8')) && sig == -1)
			return (0);
		ans = ans * 10 + (*str++ - '0');
	}
	if (sig == -1)
		return (-(int)ans);
	return ((int)ans);
}
