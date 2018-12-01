/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:04:15 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 18:00:22 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include <locale.h>

void	process_arg(t_printf *pf)
{
	if (pf->identifier == 'd' || pf->identifier == 'i')
		process_int(pf);
	else if (pf->identifier == 'D')
		process_large_int(pf);
	else if (pf->identifier == 'c' || pf->identifier == 'C'
			|| pf->identifier == '%')
		process_char(pf);
	else if (pf->identifier == 's')
		process_string(pf);
	else if (pf->identifier == 'S')
		process_large_string(pf);
	else if (pf->identifier == 'u' || pf->identifier == 'U')
		process_unsigned(pf);
	else if (pf->identifier == 'o' || pf->identifier == 'O')
		process_octal(pf);
	else if (pf->identifier == 'x' || pf->identifier == 'X')
		process_hexa(pf);
	else if (pf->identifier == 'p')
		process_pointer(pf);
	else if (pf->identifier == 'b')
		process_binary(pf);
}

int		ft_printf(const char *format, ...)
{
	t_printf	pf;
	int			count;

	ft_bzero(pf.buff, BUFF_SIZE);
	pf.buff_size = 0;
	pf.fd = 1;
	pf.total = 0;
	pf.err = 0;
	va_start(pf.args, format);
	count = parse_args(&pf, format);
	if (pf.buff_size != 0 && pf.err == 0)
	{
		pf.total += pf.buff_size;
		write(pf.fd, pf.buff, pf.buff_size);
	}
	if (pf.err == 1)
		return (-1);
	return (pf.total);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	pf;
	int			count;

	ft_bzero(pf.buff, BUFF_SIZE);
	pf.buff_size = 0;
	pf.fd = fd;
	pf.total = 0;
	pf.err = 0;
	va_start(pf.args, format);
	count = parse_args(&pf, format);
	if (pf.buff_size != 0 && pf.err == 0)
	{
		pf.total += pf.buff_size;
		write(pf.fd, pf.buff, pf.buff_size);
	}
	if (pf.err == 1)
		return (-1);
	return (pf.total);
}
