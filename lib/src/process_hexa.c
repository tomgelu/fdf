/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 21:14:58 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:55:04 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int	int_len(uintmax_t c, t_printf *pf)
{
	int		len;

	len = 0;
	if (c == 0 && pf->prec != 0)
		len = 1;
	if (pf->attr & 1 && c != 0)
		len += 2;
	while (c != 0)
	{
		len++;
		c /= 16;
	}
	return (len);
}

static void	print_left_hexa(t_printf *pf, int len, uintmax_t value, char *base)
{
	int		i;
	int		tmpprec;

	i = 0;
	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	add_prefix(pf, value);
	while (i < tmpprec - len + (2 * ((pf->attr & 1) && value != 0)))
	{
		buffer_add_char(pf, '0');
		i++;
	}
	ft_itoa_base_buff(value, base, pf);
	i += (pf->identifier == 'p' && value == 0) ? 2 : 0;
	while (i < pf->width - len)
	{
		buffer_add_char(pf, ' ');
		i++;
	}
}

static void	print_right_hexa(t_printf *pf, int len, uintmax_t value, char *base)
{
	int		i;
	int		tmpprec;

	i = 0;
	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	if (pf->attr & 2 && pf->attr & 1 && pf->prec != 0)
		add_prefix(pf, value);
	i += (pf->attr & 1 && tmpprec != 0) ? 2 : 0;
	i += (pf->identifier == 'p' && value == 0) ? 2 : 0;
	i -= (pf->identifier == 'p' && pf->prec != -1) ? 2 : 0;
	while (i < pf->width - len && i < pf->width - tmpprec)
	{
		buffer_add_char(pf, (pf->attr & 2 && pf->prec == -1) ? '0' : ' ');
		i++;
	}
	if (!(pf->attr & 2) || pf->prec == 0)
		add_prefix(pf, value);
	i = 0;
	while (i < tmpprec - len + (2 * ((pf->attr & 1) && value != 0)))
	{
		buffer_add_char(pf, '0');
		i++;
	}
	ft_itoa_base_buff(value, base, pf);
}

void		print_hexa(t_printf *pf, uintmax_t value)
{
	int		i;
	int		offset;
	int		len;
	int		tmpprec;
	char	base[16];

	if (pf->identifier == 'x' || pf->identifier == 'p')
		ft_strcpy(base, "0123456789abcdef");
	else if (pf->identifier == 'X')
		ft_strcpy(base, "0123456789ABCDEF");
	else if (pf->identifier == 'b')
		ft_strcpy(base, "01");
	len = int_len(value, pf);
	i = 0;
	if (pf->attr & 4)
		print_left_hexa(pf, len, value, base);
	else
		print_right_hexa(pf, len, value, base);
}

void		process_hexa(t_printf *pf)
{
	void	*ret;

	pf->sign = '+';
	if (pf->convmod & 4)
		print_hexa(pf, va_arg(pf->args, uintmax_t));
	else if (pf->convmod & 32)
		print_hexa(pf, va_arg(pf->args, unsigned long long));
	else if (pf->convmod & 16)
		print_hexa(pf, va_arg(pf->args, unsigned long));
	else if (pf->convmod & 8)
		print_hexa(pf, va_arg(pf->args, size_t));
	else if (pf->convmod & 2)
		print_hexa(pf, (unsigned char)va_arg(pf->args, unsigned int));
	else if (pf->convmod & 1)
		print_hexa(pf, (unsigned short)va_arg(pf->args, unsigned int));
	else if (pf->convmod == 0)
		print_hexa(pf, va_arg(pf->args, unsigned int));
}
