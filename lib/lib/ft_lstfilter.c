/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 16:13:24 by tgelu             #+#    #+#             */
/*   Updated: 2018/08/15 21:01:26 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfilter(t_list *head, int (*f)(t_list *))
{
	t_list	*ret;
	t_list	*curr;

	curr = head;
	ret = ft_lstnew(NULL, 0);
	while (curr->next != NULL)
	{
		if (f(curr))
			ft_lstappend(ret, curr->content,
				ft_strlen(curr->content) * sizeof(curr->content));
		curr = curr->next;
	}
	ret = ft_lstshift(&ret);
	return (ret);
}
