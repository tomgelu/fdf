/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:00:54 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 05:40:31 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				create_line(t_fdf *fdf, char **tab, int y)
{
	int x;

	x = -1;
	ft_bzero(fdf->map[y], ft_tablen(tab));
	while (tab[++x])
		if (ft_strisnum(tab[x]))
		{
			fdf->map[y][x] = (float)ft_atoi(tab[x]);
			if (fdf->map[y][x] > fdf->max_height)
				fdf->max_height = fdf->map[y][x];
		}
		else
			return (0);
	return (x);
}

int				create_map(t_fdf *fdf)
{
	int		y;
	int		x;
	char	**tab;
	t_list	*lst;
	t_list	*next;

	y = 0;
	fdf->max_height = 0;
	lst = fdf->data;
	while (lst && y < fdf->height)
	{
		next = lst->next;
		tab = ft_strsplit(lst->content, ' ');
		if (!(fdf->map[y] = (float *)ft_memalloc(sizeof(float)
			* ft_tablen(tab))))
			return (0);
		if (!(x = create_line(fdf, tab, y)))
			return (0);
		fdf->widths[y] = x;
		lst = next;
		y++;
		ft_tabfree(tab);
	}
	return (1);
}

int				parse_lines(t_fdf *fdf, char *filename)
{
	char	*tmp;

	if ((fdf->fd = open(filename, O_RDONLY)) < 0)
		return (0);
	if (get_next_line(fdf->fd, &tmp) < 0)
		return (0);
	fdf->height = 1;
	fdf->data = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	ft_strdel(&tmp);
	while (get_next_line(fdf->fd, &tmp) > 0)
	{
		fdf->height++;
		ft_lstappend(fdf->data, tmp, ft_strlen(tmp) + 1);
		ft_strdel(&tmp);
	}
	close(fdf->fd);
	if (!(fdf->map = (float **)ft_memalloc(sizeof(float *) * fdf->height)))
		return (0);
	if (!(fdf->widths = (int *)ft_memalloc(sizeof(int) * fdf->height)))
		return (0);
	if (!(create_map(fdf)))
		return (0);
	return (1);
}
