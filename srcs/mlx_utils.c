/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 20:41:02 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 02:30:09 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_fill_pixel(t_fdf *fdf, int x, int y)
{
	if (x < 0 || y < 0 || x > WIDTH - 1 || y > HEIGHT - 1)
		return ;
	*(int*)(fdf->img_data + (x + WIDTH * y) * fdf->bpp) = fdf->color;
}

void	ft_draw_1(t_fdf *fdf, t_pos pos, t_pos d, t_pos inc)
{
	int i;
	int	cumul;

	i = 0;
	cumul = d.x / 2;
	while (i < d.x)
	{
		pos.x += inc.x;
		cumul += d.y;
		if (cumul >= d.x)
		{
			cumul -= d.x;
			pos.y += inc.y;
		}
		ft_fill_pixel(fdf, pos.x, pos.y);
		i++;
	}
}

void	ft_draw_2(t_fdf *fdf, t_pos pos, t_pos d, t_pos inc)
{
	int i;
	int	cumul;

	i = 0;
	cumul = d.y / 2;
	while (i < d.y)
	{
		pos.y += inc.y;
		cumul += d.x;
		if (cumul >= d.y)
		{
			cumul -= d.y;
			pos.x += inc.x;
		}
		ft_fill_pixel(fdf, pos.x, pos.y);
		i++;
	}
}

void	ft_draw_line(t_fdf *fdf, t_pos p1, t_pos p2)
{
	t_pos	d;
	t_pos	inc;
	t_pos	pos;

	pos.x = p1.x;
	pos.y = p1.y;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	inc.x = (d.x > 0) ? 1 : -1;
	inc.y = (d.y > 0) ? 1 : -1;
	d.x *= inc.x;
	d.y *= inc.y;
	ft_fill_pixel(fdf, pos.x, pos.y);
	if (d.x > d.y)
		ft_draw_1(fdf, pos, d, inc);
	else
		ft_draw_2(fdf, pos, d, inc);
}

int		init_mlx(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, TITLE);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->img_data = mlx_get_data_addr(fdf->img_ptr,
		&fdf->bpp, &fdf->size_line, &fdf->endian);
	fdf->bpp /= 8;
	return (1);
}
