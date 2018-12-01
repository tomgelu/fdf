/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_large_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 19:51:04 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/01 15:26:25 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void		print_left_spaces(t_printf *pf, wchar_t *str)
{
	int		i;
	int		total;

	if (!(pf->attr & 4))
	{
		i = 0;
		total = 0;
		while (str[i] && (total + get_bytes_number(str[i]) <= pf->prec
			|| pf->prec == -1))
		{
			total += get_bytes_number(str[i]);
			i++;
		}
		i = 0;
		while (i < pf->width - total)
		{
			buffer_add_char(pf, ' ');
			i++;
		}
	}
}

static void		print_right_spaces(t_printf *pf, wchar_t *str, int bytes)
{
	int		i;

	if (pf->attr & 4)
	{
		i = bytes;
		while (i < pf->width)
		{
			buffer_add_char(pf, ' ');
			i++;
		}
	}
}

void			print_large_string(t_printf *pf, wchar_t *str)
{
	int		i;
	int		bytes;

	if (str == NULL)
	{
		print_string(pf, "(null)");
		return ;
	}
	bytes = 0;
	i = 0;
	print_left_spaces(pf, str);
	while (str[i] && (bytes + get_bytes_number(str[i]) <= pf->prec
		|| pf->prec == -1))
	{
		if (str[i] < 0 || (str[i] >= 0xD800 && str[i] <= 0xDBFF)
				|| (str[i] >= 0xDC00 && str[i] <= 0xDFFF))
		{
			pf->err = 1;
			return ;
		}
		process_large_char(pf, str[i]);
		bytes += get_bytes_number(str[i]);
		i++;
	}
	print_right_spaces(pf, str, bytes);
}

void			process_large_string(t_printf *pf)
{
	if (pf->identifier == 'S' || (pf->convmod & 16 && pf->identifier == 's'))
		print_large_string(pf, va_arg(pf->args, wchar_t *));
}
