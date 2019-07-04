/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 14:20:53 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/16 15:21:38 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(const char *string)
{
	size_t i;

	i = 0;
	while (string[i])
	{
		if (string[i] == ' ' || string[i] == '\t' || string[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}

static char		*fillone(char *str)
{
	if (!(str = (char *)malloc(sizeof(char))))
		return (NULL);
	str[0] = '\0';
	return (str);
}

char			*ft_strtrim(const char *s)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	count;

	if (!(count = 0) && !s)
		return (NULL);
	j = ft_strlen(s) - 1;
	i = 0;
	if (ft_strlen(s) && is_space(s))
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		while (s[j] == ' ' || s[j] == '\t' || s[j] == '\n')
			j--;
		if (!(str = (char *)malloc(sizeof(char) * (j - i) + 2)))
			return (NULL);
		while (i <= j)
			str[count++] = s[i++];
		str[count] = '\0';
	}
	else
		str = fillone(NULL);
	return (str);
}
