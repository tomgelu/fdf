/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:54:59 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 06:36:29 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_camera(t_fdf *fdf)
{
	fdf->mode = 1;
	fdf->depth = 1;
	fdf->color = 0x00FFFFFF;
	fdf->camera_pos.x = -(fdf->height + fdf->widths[0])/2;
	fdf->camera_pos.y = -(fdf->height + fdf->widths[0])/2;
	fdf->camera_pos.z = -10;
	fdf->camera_rot.x = 0;
	fdf->camera_rot.y = 0;
	fdf->camera_rot.z = -M_PI / 8;
	fdf->camera_offset.x = 0;
	fdf->camera_offset.y = 0;
}

int		on_exit(t_fdf *fdf)
{
	ft_printf("RED CROSS EXIT\n");
	free_fdf(fdf);
	return (0);
}

int		fdf(char *filename)
{
	t_fdf		*fdf;

	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		return (0);
	if (!(parse_lines(fdf, filename)))
	{
		free_fdf(fdf);
		return (0);
	}
	init_camera(fdf);
	init_mlx(fdf);
	draw(fdf);
	mlx_hook(fdf->win_ptr, 17, (1L << 17), on_exit, fdf);
	mlx_hook(fdf->win_ptr, 2, (1L << 0), hook_keydown, fdf);
	mlx_loop(fdf->mlx_ptr);
	free_fdf(fdf);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		ft_printf("usage : ./fdf filename");
	else
	{
		if (!fdf(av[1]))
			ft_printf("Map error\n");
	}
	return (0);
}
