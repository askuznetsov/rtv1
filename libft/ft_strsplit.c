/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:28:51 by okuznets          #+#    #+#             */
/*   Updated: 2018/10/09 17:05:52 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_lenth(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (s[i] == c)
		i++;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static size_t	words(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	cw;
	char	**str;

	if (!s)
		return (NULL);
	cw = words(s, c);
	i = 0;
	j = 0;
	if (!(str = (char**)malloc(sizeof(char*) * (cw + 1))))
		return (NULL);
	while (cw--)
	{
		while (*s == c && *s)
			s++;
		j = get_lenth((char*)s, c);
		if (!(str[i] = ft_strsub((const char*)s, 0, j)))
			return (NULL);
		s += j;
		i++;
	}
	str[i] = NULL;
	return (str);
}
