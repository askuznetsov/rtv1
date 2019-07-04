/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:36:12 by okuznets          #+#    #+#             */
/*   Updated: 2018/10/25 14:39:19 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_back(t_list **tmp, void const *content, size_t content_size)
{
	t_list *lst;

	lst = *tmp;
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		lst->next = ft_lstnew(content, content_size);
	}
	else
		*tmp = ft_lstnew(content, content_size);
}
