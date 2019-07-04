/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_delimeter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 21:00:12 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/17 21:06:45 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_delimeter(char temp)
{
	if (temp == ' ' || temp == '\n' || temp == '\t'
		|| temp == '\v' || temp == '\f' || temp == '\r')
		return (1);
	return (0);
}
