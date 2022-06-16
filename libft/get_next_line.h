/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 15:20:01 by bjesse            #+#    #+#             */
/*   Updated: 2022/06/17 02:20:50 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 1024

int				get_next_line(const int fd, char **line);

typedef struct s_fd_list_struct
{
	char					*str;
	int						fd;
	int						end;
	struct s_fd_list_struct	*next;
	struct s_fd_list_struct	*prev;
}				t_fd_list;

#endif
