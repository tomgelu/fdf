/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 16:51:10 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/21 17:01:06 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (s[len] && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
		len--;
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if ((int)(len - i) < 0)
		return (ft_strdup(""));
	return (ft_strsub(s, i, (len - i + 1)));
}
