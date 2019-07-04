/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:14:23 by okuznets          #+#    #+#             */
/*   Updated: 2017/12/14 14:28:00 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *string1, const char *string2)
{
	size_t i;
	size_t j;

	i = 0;
	while (string1[i])
	{
		j = 0;
		while (string2[j] == string1[i + j])
		{
			if (string2[j + 1] == '\0')
			{
				return (char *)(string1 + i);
			}
			j++;
		}
		i++;
	}
	if (string2[0] == '\0' && string1[0] == '\0')
		return ((char *)(string2));
	else if (string2[0] == '\0' && string1[0] != '\0')
		return ((char *)(string1));
	return (0);
}
