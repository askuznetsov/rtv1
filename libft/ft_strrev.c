/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 19:38:12 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/17 20:58:59 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	i;
	size_t	length;
	char	*temp;

	i = 0;
	length = ft_strlen(str);
	temp = (char *)malloc(length + 1);
	temp[length] = '\0';
	while (length >= 1)
	{
		temp[length - 1] = str[i];
		i++;
		length--;
	}
	return (temp);
}
