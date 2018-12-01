/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 03:14:25 by tgelu             #+#    #+#             */
/*   Updated: 2018/12/01 06:17:16 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include "../lib/inc/ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define WIDTH 1200
# define HEIGHT 1200
# define TITLE "WOW FDF!"
# define THREADS 8

typedef struct s_fdf	t_fdf;

typedef struct		s_pos
{
	float			x;
	float			y;
	float			z;
}					t_pos;

typedef struct		s_thread
{
	int				id;
	t_fdf			*fdf;
}					t_thread;

typedef struct		s_render
{
	pthread_t		threads[THREADS];
	t_thread		args[THREADS];
}					t_render;

struct				s_fdf
{
	int				fd;
	t_list			*data;
	float			**map;
	int				height;
	int				max_height;
	int				*widths;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bpp;
	int				size_line;
	int				endian;
	t_pos			camera_pos;
	t_pos			camera_rot;
	t_pos			camera_offset;
	t_render		render;
	int				mode;
	int				color;
	float			depth;
};

int					fdf(char *filename);
int					ft_tablen(char **tab);
void				ft_tabfree(char **tab);
int					ft_strisnum(char *str);
int					init_mlx(t_fdf *fdf);
int					ft_abs(int a);
void				ft_draw_line(t_fdf *fdf, t_pos p1, t_pos p2);
t_pos				pos_sub(t_pos mat1, t_pos mat2);
int					hook_keydown(int key, t_fdf *fdf);
int					parse_lines(t_fdf *fdf, char *filename);
void				draw(t_fdf *fdf);
void				free_data(t_fdf *fdf);
void				free_fdf(t_fdf *fdf);
void				free_mlx(t_fdf *fdf);

#endif
