/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:18:45 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/01 17:29:22 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	print_left_spaces(t_printf *pf, char *str, int len)
{
	int		i;

	if (!(pf->attr & 4))
	{
		i = 0;
		while (i + len < pf->width || i + ft_strlen(str) < pf->width)
		{
			buffer_add_char(pf, (pf->attr & 2) ? '0' : ' ');
			i++;
		}
	}
}

void	print_right_spaces(t_printf *pf, char *str, int len)
{
	int		i;

	if (pf->attr & 4)
	{
		i = 0;
		while (i + len < pf->width || i + ft_strlen(str) < pf->width)
		{
			buffer_add_char(pf, (pf->attr & 2) ? '0' : ' ');
			i++;
		}
	}
}

void	print_string(t_printf *pf, char *str)
{
	int		i;
	int		len;

	if (str == NULL)
		str = "(null)";
	i = 0;
	len = ft_strlen(str);
	if (pf->prec != -1)
		len = pf->prec;
	pf->prec = -1;
	print_left_spaces(pf, str, len);
	while (str[i] && i < len)
	{
		buffer_add_char(pf, str[i]);
		i++;
	}
	print_right_spaces(pf, str, len);
}

void	process_string(t_printf *pf)
{
	if (pf->identifier == 's' && !(pf->convmod & 16))
		print_string(pf, va_arg(pf->args, char*));
	else if (pf->convmod & 16)
		process_large_string(pf);
}
