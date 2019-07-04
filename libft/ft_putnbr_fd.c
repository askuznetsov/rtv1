/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:32:55 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/11 20:01:34 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	i;
	int				ten;

	ten = 1;
	if (nb < 0)
		write(fd, "-", 1);
	i = nb < 0 ? -nb : nb;
	while (i >= 10)
	{
		i /= 10;
		ten *= 10;
	}
	i = nb < 0 ? -nb : nb;
	while (ten)
	{
		ft_putchar_fd(i / ten + '0', fd);
		i %= ten;
		ten /= 10;
	}
}
