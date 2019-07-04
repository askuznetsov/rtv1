/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:09:55 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/16 14:58:57 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*k;
	unsigned char	*l;
	size_t			i;

	i = 0;
	k = (unsigned char *)s1;
	l = (unsigned char *)s2;
	while (i < n)
	{
		if (k[i] == l[i] && k[i] && l[i])
			i++;
		else
			return (k[i] - l[i]);
	}
	return (0);
}
