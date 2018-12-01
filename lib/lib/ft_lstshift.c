/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpophead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:01:27 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/18 17:11:23 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstshift(t_list **head)
{
	t_list	*next;

	next = (*head)->next;
	free((*head)->content);
	(*head)->next = NULL;
	free(*head);
	return (next);
}
