/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 03:33:28 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 05:34:52 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		free_data(t_fdf *fdf)
{
	t_list	*lst;
	t_list	*next;

	lst = fdf->data;
	while (lst)
	{
		next = lst->next;
		if (lst->content)
			ft_memdel(&lst->content);
		ft_memdel((void **)&lst);
		lst = next;
	}
}

void		free_map(t_fdf *fdf)
{
	int		y;

	y = 0;
	if (fdf->widths != NULL)
		ft_memdel((void **)&fdf->widths);
	while (y < fdf->height)
	{
		if (fdf->map[y] != NULL)
			ft_memdel((void **)&fdf->map[y]);
		y++;
	}
	if (fdf->map != NULL)
		ft_memdel((void **)&fdf->map);
}

void		free_mlx(t_fdf *fdf)
{
	if (fdf->img_ptr != NULL)
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
	if (fdf->win_ptr != NULL)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	if (fdf->mlx_ptr != NULL)
		ft_memdel((void **)&fdf->mlx_ptr);
}

void		free_fdf(t_fdf *fdf)
{
	free_map(fdf);
	free_data(fdf);
	free_mlx(fdf);
	if (fdf != NULL)
		ft_memdel((void **)&fdf);
}
