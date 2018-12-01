/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:36:26 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/04 21:22:40 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;
	size_t			i;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dest > source)
	{
		i = len;
		while (i > 0)
		{
			*(dest + i - 1) = *(source + i - 1);
			i--;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
