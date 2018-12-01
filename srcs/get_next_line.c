/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:53:07 by tgelu             #+#    #+#             */
/*   Updated: 2018/09/08 20:25:33 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list		*ft_get_file(int fd, t_list **file)
{
	t_list		*current;

	current = *file;
	while (current != NULL)
	{
		if ((int)current->content_size == fd)
			return (current);
		current = current->next;
	}
	if (!(current = ft_memalloc(sizeof(t_list))))
		return (NULL);
	current->content_size = fd;
	current->content = ft_strdup("");
	ft_lstadd(file, current);
	return (current);
}

int			ft_get_line(char **line, t_list *current)
{
	int			i;

	i = 0;
	while (((char *)current->content)[i] != '\n'
			&& ((char *)current->content)[i] != '\0')
		i++;
	if (((char*)current->content)[0])
		*line = ft_strsub(current->content, 0, i);
	return (i);
}

void		ft_trim_current(t_list **current, int i)
{
	char		*tmp;

	tmp = ft_strdup((char *)(*current)->content);
	ft_memdel(&(*current)->content);
	(*current)->content = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i);
	ft_strdel(&tmp);
}

int			get_next_line(const int fd, char **line)
{
	static t_list		*save;
	t_list				*current;
	char				buff[BUFF_SIZE + 1];
	char				*tmp;
	int					len;

	MALCHK((fd < 0 || line == NULL || read(fd, buff, 0) < 0
				|| !(current = ft_get_file(fd, &save))));
	if (ft_strchr(current->content, SEP) == NULL)
		while ((len = read(current->content_size, buff, BUFF_SIZE)))
		{
			buff[len] = '\0';
			if (!(tmp = ft_strjoin(current->content, buff)))
				return (-1);
			ft_memdel(&(current)->content);
			current->content = ft_strdup(tmp);
			ft_strdel(&tmp);
			if (ft_strchr(current->content, SEP))
				break ;
		}
	len = ft_get_line(line, current);
	if (!ft_strchr(current->content, '\n') && len == 0)
		return (0);
	ft_trim_current(&current, len);
	return (1);
}
