/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 18:15:37 by okuznets          #+#    #+#             */
/*   Updated: 2017/12/22 18:33:18 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	temp[len];

	if (len < (128 * 1024 * 1024))
	{
		ft_memcpy(temp, src, len);
		ft_memcpy(dst, temp, len);
	}
	else
		return (0);
	return (dst);
}
