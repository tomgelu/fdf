/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:29:04 by tgelu             #+#    #+#             */
/*   Updated: 2018/08/18 17:21:39 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../lib/lib/libft.h"
# include "../lib/inc/ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# define SEP '\n'

# define MALCHK(x) if(x) return (-1);

int			get_next_line(const int fd, char **line);
#endif
