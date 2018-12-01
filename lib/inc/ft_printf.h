/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:36:32 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:59:45 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include "../lib/libft.h"
# define BUFF_SIZE 32

typedef struct	s_printf
{
	va_list		args;
	char		buff[BUFF_SIZE];
	int			buff_size;
	int			width;
	int			prec;
	int			identifier;
	int			attr;
	int			convmod;
	char		sign;
	int			total;
	int			err;
	int			fd;
}				t_printf;

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				parse_args(t_printf *pf, const char *format);
void			process_arg(t_printf *pf);
void			process_int(t_printf *pf);
void			process_large_int(t_printf *pf);
void			process_char(t_printf *pf);
void			print_char(t_printf *pf, wchar_t value);
void			process_large_char(t_printf *pf, wchar_t value);
void			process_string(t_printf *pf);
void			process_large_string(t_printf *pf);
void			process_unsigned(t_printf *pf);
void			process_octal(t_printf *pf);
void			print_octal_zero(t_printf *pf);
void			print_octal_zero_right(t_printf *pf);
void			print_octal_zero_left(t_printf *pf);
void			process_hexa(t_printf *pf);
void			add_prefix(t_printf *pf, uintmax_t value);
void			process_pointer(t_printf *pf);
void			process_binary(t_printf *pf);
void			print_string(t_printf *pf, char *str);
void			print_int(t_printf *pf, intmax_t value);
void			buffer_add_string(t_printf *pf, char *str);
void			buffer_add_char(t_printf *pf, char c);
void			buffer_clean(t_printf *pf);
void			ft_itoa_base_buff(uintmax_t num, char *base, t_printf *pf);
char			*ft_convert_base(char *nbr, char *base_from, char *base_to);
int				get_bytes_number(wchar_t value);
int				is_identifier(char c);
int				is_attribute(char c);
int				is_valid_char(char c);
int				is_conv_modifier(const char *format);
void			set_conv_modifier(t_printf *pf, const char *format);
void			init_pf(t_printf *pf, int *len);
#endif
