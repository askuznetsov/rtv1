/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:01:13 by okuznets          #+#    #+#             */
/*   Updated: 2017/12/14 19:04:43 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (s2[j])
		j++;
	while (s1[i])
	{
		while (s1[i] == s2[k])
		{
			i++;
			k++;
			if (i > (int)(len))
				break ;
			if (s2[k] == '\0')
				return ((char *)&(s1[i - j]));
		}
		i++;
	}
	if (s2[0] == '\0')
		return ((char *)(s1));
	return (NULL);
}
