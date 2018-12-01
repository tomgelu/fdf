/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 19:00:54 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 04:26:33 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_rotations(t_fdf *fdf, int key)
{
	if (key == 13)
	{
		fdf->camera_rot.x += 0.01;
	}
	if (key == 1)
	{
		fdf->camera_rot.x -= 0.01;
	}
	if (key == 12)
		fdf->camera_rot.z += 0.01;
	if (key == 14)
		fdf->camera_rot.z -= 0.01;
}

void	handle_transformations(t_fdf *fdf, int key)
{
	if (key == 49)
		fdf->camera_pos.z += 1;
	if (key == 48)
		fdf->camera_pos.z -= 1;
	if (key == 123)
		fdf->camera_pos.x -= 1;
	if (key == 124)
		fdf->camera_pos.x += 1;
	if (key == 126)
		fdf->camera_pos.y += 1;
	if (key == 125)
		fdf->camera_pos.y -= 1;
	if (key == 78 && fdf->depth < 5)
		fdf->depth += 0.2;
	if (key == 69 && fdf->depth > -5)
		fdf->depth -= 0.2;
}

int		hook_keydown(int key, t_fdf *fdf)
{
	handle_rotations(fdf, key);
	handle_transformations(fdf, key);
	if (key == 53)
		exit(EXIT_SUCCESS);
	draw(fdf);
	return (0);
}
