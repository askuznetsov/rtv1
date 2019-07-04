/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:54:13 by okuznets          #+#    #+#             */
/*   Updated: 2018/10/08 17:06:45 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->next = NULL;
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		if ((new->content = (void *)malloc(content_size)) == NULL)
		{
			free(new);
			return (NULL);
		}
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}

void	**ft_lst_expand(t_list *list)
{
	size_t	i;
	t_list	*temp;
	void	**res;

	if (list == 0)
		return (NULL);
	i = 0;
	temp = list;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	res = (void**)malloc(sizeof(*res) * (i + 1));
	res[i] = NULL;
	i = 0;
	while (list)
	{
		res[i] = malloc(list->content_size);
		ft_memcpy(res[i], list->content, list->content_size);
		list = list->next;
		i++;
	}
	return (res);
}
