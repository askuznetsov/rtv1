/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_till.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:01:24 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/17 18:08:41 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_till(char *str, int end, int flag)
{
	int i;

	i = 0;
	if (flag == 0)
	{
		if (str)
		{
			while (str[i])
				ft_putchar(str[i++]);
		}
	}
	if (flag == 1)
	{
		if (str)
		{
			while (i <= end)
				ft_putchar(str[i++]);
		}
	}
}
