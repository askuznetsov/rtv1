/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 19:08:38 by okuznets          #+#    #+#             */
/*   Updated: 2017/12/27 19:15:47 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	i;
	size_t	len;
	char	*c;

	i = 0;
	if (s == 0 || f == 0)
		return (0);
	len = ft_strlen(s);
	c = (char *)malloc(sizeof(char) * len + 1);
	if (c == 0)
		return (0);
	while (s[i])
	{
		c[i] = f(s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}
