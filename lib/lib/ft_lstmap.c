/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:42:36 by tgelu             #+#    #+#             */
/*   Updated: 2018/04/17 19:01:11 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*list;

	if (lst == NULL)
		return (NULL);
	list = (*f)(lst);
	ret = list;
	while (lst->next)
	{
		lst = lst->next;
		list->next = (*f)(lst);
		list = list->next;
	}
	return (ret);
}
