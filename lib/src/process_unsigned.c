/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:18:29 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/01 17:19:45 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int		int_len(uintmax_t c, t_printf *pf)
{
	int		len;

	len = 0;
	if (c == 0 && pf->prec != 0)
		return (1);
	while (c != 0)
	{
		len++;
		c /= 10;
	}
	return (len);
}

static void		print_left_unsigned(t_printf *pf, int len, uintmax_t value)
{
	int		i;

	i = -1;
	if (pf->attr & 16)
	{
		while (++i < pf->prec - len)
			buffer_add_char(pf, '0');
		ft_itoa_base_buff(value, "0123456789", pf);
		while (++i < pf->width - len)
			buffer_add_char(pf, ' ');
	}
	else
	{
		if (pf->attr & 8)
			buffer_add_char(pf, ' ');
		while (++i < pf->prec - len)
			buffer_add_char(pf, '0');
		ft_itoa_base_buff(value, "0123456789", pf);
		while (++i < pf->width - len + (!(pf->attr & 8) && !(pf->sign == '-')))
			buffer_add_char(pf, ' ');
	}
}

static void		print_right_unsigned(t_printf *pf, int len, uintmax_t value)
{
	int		tmpprec;
	int		i;

	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	i = 0;
	if (pf->attr & 8 && !(pf->attr & 16) && pf->width != 0 && !tmpprec)
		buffer_add_char(pf, ' ');
	while (i < pf->width - tmpprec && i < pf->width - len)
	{
		buffer_add_char(pf, ((pf->attr & 2 && pf->prec == -1) ? '0' : ' '));
		i++;
	}
	if (pf->attr & 8 && (!(pf->attr & 2)
		|| pf->prec != -1) && !(pf->identifier == 'u'))
		buffer_add_char(pf, ' ');
	i = 0;
	while (i < tmpprec - len)
	{
		buffer_add_char(pf, '0');
		i++;
	}
	ft_itoa_base_buff(value, "0123456789", pf);
}

void			print_unsigned(t_printf *pf, uintmax_t value)
{
	int		i;
	int		offset;
	int		len;
	int		tmpprec;

	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	len = int_len(value, pf);
	i = 0;
	if (pf->attr & 4)
		print_left_unsigned(pf, len, value);
	else
		print_right_unsigned(pf, len, value);
}

void			process_unsigned(t_printf *pf)
{
	pf->sign = '+';
	if (pf->identifier == 'U')
		pf->convmod |= 1 << 4;
	if (pf->convmod & 4)
		print_unsigned(pf, va_arg(pf->args, uintmax_t));
	else if (pf->convmod & 32)
		print_unsigned(pf, va_arg(pf->args, unsigned long long));
	else if (pf->convmod & 16)
		print_unsigned(pf, va_arg(pf->args, unsigned long));
	else if (pf->convmod & 8)
		print_unsigned(pf, va_arg(pf->args, size_t));
	else if (pf->convmod & 2)
		print_unsigned(pf, (unsigned char)va_arg(pf->args, unsigned int));
	else if (pf->convmod & 1)
		print_unsigned(pf, (unsigned short)va_arg(pf->args, unsigned int));
	else if (pf->convmod == 0)
		print_unsigned(pf, va_arg(pf->args, unsigned int));
}
