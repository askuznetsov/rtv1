/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:46:23 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/16 15:19:17 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		itoa_is_negative(int *n, int *sign)
{
	if (*n < 0)
	{
		*n *= -1;
		*sign = 1;
	}
}

char			*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		temp;
	int		length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	temp = n;
	length = 2;
	sign = 0;
	itoa_is_negative(&n, &sign);
	while (temp /= 10)
		length++;
	length += sign;
	if ((str = (char *)malloc(sizeof(char) * length)) == NULL)
		return (NULL);
	str[--length] = '\0';
	while (length--)
	{
		str[length] = n % 10 + '0';
		n = n / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
