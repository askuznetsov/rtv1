/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 15:49:47 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/17 21:06:43 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	size_t				i;
	int					minus;
	unsigned long int	number;

	i = 0;
	minus = 1;
	while (ft_is_delimeter(str[i]))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	number = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if ((number > 922337203685477580 || (number == 922337203685477580 &&
			(str[i] - '0') > 7)) && minus == 1)
			return (-1);
		else if ((number > 922337203685477580 ||
				(number == 922337203685477580 &&
				(str[i] - '0') > 8)) && minus == -1)
			return (0);
		number = (number * 10) + (str[i++] - '0');
	}
	return (number * minus);
}
