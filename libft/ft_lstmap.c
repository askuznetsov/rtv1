/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:17:35 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/16 16:37:36 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_lstdelcont(void *content, size_t content_size)
{
	if (content != NULL)
	{
		free(content);
		content_size = 0;
	}
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*buf;
	t_list	*new_list;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	buf = f(lst);
	if (!(new_list = ft_lstnew(buf->content, buf->content_size)))
		return (NULL);
	start = new_list;
	lst = lst->next;
	while (lst)
	{
		buf = f(lst);
		if (!(new_list->next = ft_lstnew(buf->content, buf->content_size)))
		{
			ft_lstdel(&start, &ft_lstdelcont);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	return (start);
}
