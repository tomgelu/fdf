/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:29:00 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:53:51 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	init_pf(t_printf *pf, int *len)
{
	pf->identifier = '?';
	pf->width = 0;
	pf->prec = -1;
	pf->attr = 0;
	pf->convmod = 0;
	*len = 0;
}

void	add_prefix(t_printf *pf, uintmax_t value)
{
	if (pf->attr & 1 && (value != 0 || pf->identifier == 'p'))
	{
		buffer_add_char(pf, '0');
		buffer_add_char(pf, (pf->identifier == 'x'
					|| pf->identifier == 'p') ? 'x' : 'X');
	}
}
