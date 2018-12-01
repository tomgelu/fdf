/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:44:20 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/01 16:55:05 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int		get_bytes_number(wchar_t value)
{
	if (value <= 0x7F)
		return (1);
	else if (value <= 0x7FF)
		return (2);
	else if (value <= 0xFFFF)
		return (3);
	else if (value <= 0x10FFFF)
		return (4);
	return (0);
}

void	print_char_left(t_printf *pf, wchar_t value)
{
	int		i;

	i = 0;
	if (value > 0x7F)
		process_large_char(pf, value);
	else
		buffer_add_char(pf, value);
	while (i < pf->width - get_bytes_number(value))
	{
		buffer_add_char(pf, (pf->attr & 2 ? '0' : ' '));
		i++;
	}
}

void	print_char_right(t_printf *pf, wchar_t value)
{
	int		i;

	i = 0;
	while (i < pf->width - get_bytes_number(value))
	{
		buffer_add_char(pf, (pf->attr & 2 ? '0' : ' '));
		i++;
	}
	if (value > 0x7F)
		process_large_char(pf, value);
	else
		buffer_add_char(pf, value);
}

void	print_char(t_printf *pf, wchar_t value)
{
	int		tmpprec;

	if (((pf->convmod & 16 || pf->identifier == 'C') && value < 0)
			|| (value >= 0xD800 && value <= 0xDBFF)
			|| (value >= 0xDC00 && value <= 0xDFFF))
	{
		pf->err = 1;
		return ;
	}
	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	if (pf->attr & 4)
		print_char_left(pf, value);
	else
		print_char_right(pf, value);
}

void	process_char(t_printf *pf)
{
	if (pf->identifier == '%')
		print_char(pf, '%');
	else if (pf->convmod & 16 || pf->identifier == 'C')
		print_char(pf, va_arg(pf->args, wchar_t));
	else
		print_char(pf, (char)va_arg(pf->args, wchar_t));
}
