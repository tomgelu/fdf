/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:51:10 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 02:29:00 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pos	pos_sub(t_pos mat1, t_pos mat2)
{
	t_pos new;

	new.x = mat1.x - mat2.x;
	new.y = mat1.y - mat2.y;
	new.z = mat1.z - mat2.z;
	return (new);
}

int		ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int		ft_strisnum(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int		ft_tablen(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_tabfree(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_strdel(&(str[i]));
		i++;
	}
	ft_memdel((void **)str);
}
