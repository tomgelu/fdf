/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 17:46:03 by tgelu             #+#    #+#             */
/*   Updated: 2018/06/02 17:51:42 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int		is_identifier(char c)
{
	if (c == 'd' || c == 'D' || c == 's' || c == 'S'
			|| c == 'p' || c == 'i' || c == 'o' || c == 'O'
			|| c == 'u' || c == 'U' || c == 'x' || c == 'X'
			|| c == 'c' || c == 'C' || c == 'b' || c == '%')
		return (1);
	return (0);
}

int		is_attribute(char c)
{
	if (c == '#' || c == '0' || c == '-' ||
			c == ' ' || c == '+')
		return (1);
	return (0);
}

int		is_valid_char(char c)
{
	if (is_identifier(c) || is_attribute(c) || c == 'h' || c == 'l'
			|| c == 'j' || c == 'z' || c == '.' || ft_isdigit(c) || c == '*')
		return (1);
	return (0);
}

int		is_conv_modifier(const char *format)
{
	if (*format == 'h')
	{
		if (*(format - 1) == 'h')
			return (0);
		return (1);
	}
	if (*format == 'l')
	{
		if (*(format - 1) == 'l')
			return (0);
		return (1);
	}
	if (*format == 'j' || *format == 'z')
		return (1);
	return (0);
}

void	set_conv_modifier(t_printf *pf, const char *format)
{
	if (*format == 'h')
	{
		if (*(format + 1) == 'h')
			pf->convmod |= 1 << 1;
		else if (!(*(format + 1) == 'h'))
			pf->convmod |= 1;
	}
	if (*format == 'l')
	{
		if (*(format + 1) == 'l')
			pf->convmod |= 1 << 5;
		else if (!(*(format + 1) == 'h'))
			pf->convmod |= 1 << 4;
	}
	if (*format == 'j')
		pf->convmod |= 1 << 2;
	if (*format == 'z')
		pf->convmod |= 1 << 3;
}
