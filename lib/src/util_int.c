/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:56:16 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/01 19:05:05 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_init_itoa_base(int *i, intmax_t *cpt)
{
	*cpt = 0;
	*i = -1;
}

void		ft_itoa_base_buff(uintmax_t num, char *base, t_printf *pf)
{
	intmax_t		cpt;
	uintmax_t		numcp;
	char			tmp[50];
	int				i;

	ft_bzero(tmp, 50);
	ft_init_itoa_base(&i, &cpt);
	numcp = num;
	if (num == 0 && pf->prec != 0)
		buffer_add_char(pf, '0');
	if (num == 0 && pf->prec != 0)
		return ;
	while (numcp > 0)
	{
		numcp /= ft_strlen(base);
		cpt++;
	}
	while (cpt > 0)
	{
		tmp[cpt - 1] = base[(num % ft_strlen(base))];
		cpt--;
		num /= ft_strlen(base);
	}
	while (tmp[++i])
		buffer_add_char(pf, tmp[i]);
}
