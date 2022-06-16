/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 02:40:06 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 02:42:02 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

void	reverse_byte_order_64(uint64_t *all_data_size);
void	swipe_endian_bytes(unsigned char *all_data, int size);
void	reverse_byte(unsigned char *byte);

int		is_test_command(char *command);
void	tests(void);

void	uint64_to_hex(uint64_t reg);
int		assert_false(int line);
int		open_file(char *path, int mode);

#endif
