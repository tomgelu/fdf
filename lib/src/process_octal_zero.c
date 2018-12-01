/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_octal_zero.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 17:55:26 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:58:31 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void		print_octal_zero_left(t_printf *pf)
{
	int		offset;
	int		i;

	i = 0;
	offset = (pf->attr & 1);
	if (!offset && pf->width == 0 && pf->prec == 0)
		return ;
	while (pf->width != 0 && i < pf->width)
	{
		if (i < pf->prec)
			buffer_add_char(pf, '0');
		else
			buffer_add_char(pf, ' ');
		i++;
	}
}

void		print_octal_zero_right(t_printf *pf)
{
	int		offset;
	int		i;

	i = 0;
	offset = (pf->attr & 1);
	if (!offset && pf->width == 0 && pf->prec == 0)
		return ;
	while (i < pf->width - 1 || i < pf->prec - 1)
	{
		if ((pf->prec <= 0 || i < pf->prec) && pf->width != 0
				&& (pf->width > pf->prec) && (!(pf->attr & 2) || pf->prec > 0))
			buffer_add_char(pf, ' ');
		else
			buffer_add_char(pf, '0');
		i++;
	}
	buffer_add_char(pf, (pf->prec == 0 && pf->width > 0) ? ' ' : '0');
}

void		print_octal_zero(t_printf *pf)
{
	int		offset;
	int		i;

	i = 0;
	offset = (pf->attr & 1);
	if (!offset && pf->width == 0 && pf->prec == 0)
		return ;
	if (pf->attr & 4)
		print_octal_zero_left(pf);
	else
		print_octal_zero_right(pf);
}
