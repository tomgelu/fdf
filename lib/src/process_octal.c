/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_octal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:11:07 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:57:45 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	int_len(uintmax_t c, t_printf *pf)
{
	int		len;

	len = 0;
	if (c == 0 && pf->prec != 0)
		return (1);
	while (c != 0)
	{
		len++;
		c /= 8;
	}
	return (len);
}

static void	print_right_spaces(t_printf *pf, int len, int *i)
{
	if (pf->attr & 4)
	{
		while (*i < pf->width)
		{
			buffer_add_char(pf, ' ');
			(*i)++;
		}
	}
}

static void	print_left_spaces(t_printf *pf, int len, int *i)
{
	if (pf->attr & 4)
	{
		while (*i < pf->prec - len)
		{
			buffer_add_char(pf, '0');
			(*i)++;
		}
	}
	else
	{
		while (*i < pf->width - len - (pf->attr & 1)
				|| *i < pf->prec - len - (pf->attr & 1))
		{
			buffer_add_char(pf, ((pf->attr & 2 && pf->prec == -1)
				|| pf->width == 0 || *i >= pf->width - pf->prec) ? '0' : ' ');
			(*i)++;
		}
	}
}

void		print_octal(t_printf *pf, uintmax_t value)
{
	int		len;
	int		i;
	int		offset;

	if (value == 0)
	{
		print_octal_zero(pf);
		return ;
	}
	i = 0;
	len = int_len(value, pf);
	offset = pf->attr & 1;
	print_left_spaces(pf, len, &i);
	if (offset)
	{
		buffer_add_char(pf, '0');
		i++;
	}
	ft_itoa_base_buff(value, "01234567", pf);
	i += len;
	print_right_spaces(pf, len, &i);
}

void		process_octal(t_printf *pf)
{
	pf->sign = '+';
	if (pf->identifier == 'O')
		pf->convmod |= 1 << 4;
	if (pf->convmod & 4)
		print_octal(pf, va_arg(pf->args, uintmax_t));
	else if (pf->convmod & 32)
		print_octal(pf, va_arg(pf->args, unsigned long long));
	else if (pf->convmod & 16)
		print_octal(pf, va_arg(pf->args, unsigned long));
	else if (pf->convmod & 8)
		print_octal(pf, va_arg(pf->args, size_t));
	else if (pf->convmod & 2)
		print_octal(pf, (unsigned char)va_arg(pf->args, unsigned int));
	else if (pf->convmod & 1)
		print_octal(pf, (unsigned short)va_arg(pf->args, unsigned int));
	else if (pf->convmod == 0)
		print_octal(pf, va_arg(pf->args, unsigned int));
}
