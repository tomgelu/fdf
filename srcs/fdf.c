/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:00:54 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 06:34:49 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pos			to_3d(t_fdf *fdf, t_pos c)
{
	t_pos	d;

	d.x = cos(fdf->camera_rot.y) * (sin(fdf->camera_rot.z) * c.y
			+ cos(fdf->camera_rot.z) * c.x) - sin(fdf->camera_rot.y) * c.z;
	d.z = sin(fdf->camera_rot.x) * (cos(fdf->camera_rot.y) * c.z
			+ sin(fdf->camera_rot.y)
			* (sin(fdf->camera_rot.z) * c.y + cos(fdf->camera_rot.z) * c.x))
		+ cos(fdf->camera_rot.x) * (cos(fdf->camera_rot.z) * c.y
				- sin(fdf->camera_rot.z) * c.x);
	d.y = cos(fdf->camera_rot.x) * (cos(fdf->camera_rot.y) * c.z
			+ sin(fdf->camera_rot.y) * (sin(fdf->camera_rot.z) * c.y
				+ cos(fdf->camera_rot.z) * c.x))
		- sin(fdf->camera_rot.x) * (cos(fdf->camera_rot.z) * c.y
				- sin(fdf->camera_rot.z) * c.x);
	return (d);
}

t_pos			to_2d(t_fdf *fdf, int x, int y)
{
	t_pos	ret;
	t_pos	tmp;
	t_pos	tmp2;

	tmp = pos_sub((t_pos) { x, y, fdf->map[y][x] * fdf->depth },
			fdf->camera_pos);
	tmp2 = to_3d(fdf, tmp);
	if (tmp2.z == 0)
		return ((t_pos) { 0, 0, 0 });
	ret.x = ((1 / tmp2.z) * tmp2.x) * WIDTH;
	ret.y = ((1 / tmp2.z) * tmp2.y) * HEIGHT;
	return (ret);
}

void			draw_lines(t_fdf *fdf, int x, int y)
{
	t_pos		a;
	t_pos		b;

	a = to_2d(fdf, x, y);
	if (y != fdf->height - 1)
	{
		b = to_2d(fdf, x, y + 1);
		if (b.x > 0 && b.x > 0 && a.y > 0 && a.y > 0)
			ft_draw_line(fdf, a, b);
	}
	if (x != fdf->widths[y] - 1)
	{
		b = to_2d(fdf, x + 1, y);
		if (b.x > 0 && b.x > 0 && a.y > 0 && a.y > 0)
			ft_draw_line(fdf, a, b);
	}
}

void			*draw_thread(void *fdf)
{
	int			y;
	int			x;
	t_thread	*t;
	int			max;

	t = (t_thread *)fdf;
	y = 0;
	max = (t->id != THREADS - 1) ? t->fdf->height / THREADS * (t->id + 1) : t->fdf->height;
	y = t->fdf->height / THREADS * t->id;
	while (y < max)
	{
		x = 0;
		while (x < t->fdf->widths[y])
		{
			draw_lines(t->fdf, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

void			draw(t_fdf *fdf)
{
	t_render	*r;
	int			i;

	ft_memset(fdf->img_data, 0, WIDTH * HEIGHT * fdf->bpp);
	i = 0;
	r = &fdf->render;
	while (i < THREADS)
	{
		r->args[i].id = i;
		r->args[i].fdf = fdf;
		pthread_create(r->threads + i, NULL, draw_thread, &(r->args[i]));
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(r->threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}
