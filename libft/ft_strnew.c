/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 18:59:56 by okuznets          #+#    #+#             */
/*   Updated: 2017/12/27 16:55:56 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *)malloc(sizeof(char) * size + 1);
	if (string == NULL)
		return (NULL);
	while (i < size)
	{
		string[i] = '\0';
		i++;
	}
	string[i] = '\0';
	return (string);
}
