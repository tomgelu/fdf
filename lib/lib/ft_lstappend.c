/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 15:16:37 by tgelu             #+#    #+#             */
/*   Updated: 2018/08/15 20:58:46 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list *list, void *value, size_t content_size)
{
	t_list	*current;

	current = list;
	while (current->next != NULL)
		current = current->next;
	current->next = ft_lstnew(value, content_size);
}
