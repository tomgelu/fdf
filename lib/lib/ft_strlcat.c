/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:50:49 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/10 16:09:47 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dest;
	const char	*source;
	size_t		n;
	size_t		len;

	dest = dst;
	source = src;
	n = size;
	while (n-- != 0 && *dest != '\0')
		dest++;
	len = dest - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(source));
	while (*source != '\0')
	{
		if (n != 1)
		{
			*dest++ = *source;
			n--;
		}
		source++;
	}
	*dest = '\0';
	return (len + (source - src));
}
