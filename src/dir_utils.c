/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:03:23 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:15:56 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_direct	mul_dir(t_direct d1, t_direct d2)
{
	double		i;
	double		j;
	double		k;

	i = (d1.y * d2.z) - (d2.y * d1.z);
	j = -((d1.x * d2.z) - (d2.x * d1.z));
	k = (d1.x * d2.y) - (d2.x * d1.y);
	return (set_direct(i, j, k));
}

int			true_free(void *to_free)
{
	free(to_free);
	return (1);
}

t_direct	set_direct(double x, double y, double z)
{
	t_direct v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_direct	sub_dirs(t_direct d1, t_direct d2)
{
	t_direct sub;

	sub.x = d1.x - d2.x;
	sub.y = d1.y - d2.y;
	sub.z = d1.z - d2.z;
	return (sub);
}
