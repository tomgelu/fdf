/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:35:26 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:52:40 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	get_attribute(t_printf *pf, const char *format)
{
	while (is_attribute(*format))
	{
		if (*format == '#')
			pf->attr |= 1;
		if (*format == '0' && !ft_isdigit(*(format - 1)))
			pf->attr |= 1 << 1;
		if (*format == '-')
			pf->attr |= 1 << 2;
		if (*format == ' ')
			pf->attr |= 1 << 3;
		if (*format == '+')
			pf->attr |= 1 << 4;
		format++;
	}
}

void	set_width(t_printf *pf, const char *format, int *i)
{
	if (*(format + *i) != '*')
	{
		pf->width = ft_atoi(format + *i);
	}
	else if (*(format + *i) == '*')
	{
		pf->width = va_arg(pf->args, int);
		if (pf->width < 0)
		{
			pf->attr |= 1 << 2;
			pf->width *= -1;
		}
		(*i)++;
	}
	while (ft_isdigit(*(format + *i)))
		(*i)++;
	(*i)--;
}

void	set_prec(t_printf *pf, const char *format, int *i)
{
	(*i)++;
	if (*(format + *i) != '*')
		pf->prec = ft_atoi(format + *i);
	else if (*(format + *i) == '*')
	{
		pf->prec = va_arg(pf->args, int);
		if (pf->prec < 0)
		{
			pf->attr |= 1 << 2;
			pf->prec = -1;
		}
		(*i)++;
	}
	while (ft_isdigit(*(format + *i)))
		(*i)++;
}

int		parse_simple_arg(t_printf *pf, const char *format)
{
	int		len;
	int		i;

	i = -1;
	init_pf(pf, &len);
	while (format[++i])
	{
		if (is_attribute(format[i]))
			get_attribute(pf, format);
		if (((ft_isdigit(format[i]) && format[i] != '0')
			|| (format[i] == '*')) && format[i - 1] != '.')
			set_width(pf, format, &i);
		if (format[i] == '.')
			set_prec(pf, format, &i);
		if (is_conv_modifier(format + i))
			set_conv_modifier(pf, format + i);
		if (is_identifier(format[i]))
			pf->identifier = format[i];
		if (pf->identifier != '?')
			break ;
		len++;
	}
	if (pf->identifier != '?')
		process_arg(pf);
	return (len);
}

int		parse_args(t_printf *pf, const char *format)
{
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (pf->err == 0 && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] && is_valid_char(format[i]))
				len += parse_simple_arg(pf, format + i);
			while (is_valid_char(format[i]) && !is_identifier(format[i]))
				i++;
			if (format[i] && is_valid_char(format[i]))
				i++;
		}
		else
		{
			buffer_add_char(pf, format[i]);
			len++;
			i++;
		}
	}
	return (len);
}
