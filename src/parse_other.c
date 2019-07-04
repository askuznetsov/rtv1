/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:56:00 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:27:11 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int						colour_parse(char *line, int line_n)
{
	int			i;
	int			j;
	int			col;
	const char	hex[16] = "0123456789ABCDEF";

	if (st_with(line, "0x") && !(col = 0)
	&& (i = 1))
	{
		while (line[++i] && (j = -1))
		{
			while (hex[++j] && hex[j] != ft_toupper(line[i]))
				;
			(!hex[j]) ? puterr(line_n, "Wrong col scheme ", line) : (void)1;
			col = col * 16 + j;
		}
		return (col);
	}
	puterr(line_n, "Wrong colour representation ", line);
	return (0);
}

static inline double	search_float(char *line, int *i, int line_n)
{
	double a;

	a = str_to_dbl(line, *i, line_n);
	while (line[*i] && (line[*i] != ',' || ft_isdigit(line[*i]) ||
	line[*i] == '.'))
		(*i)++;
	while (line[++(*i)] && line[(*i)] < 33)
		;
	return (a);
}

t_direct				parse_direct(char *line, int line_n)
{
	double	a;
	int		i;
	double	b;
	int		fl;
	double	c;

	i = 1;
	fl = 0;
	if (st_with(line, "(") && ((int)(a = search_float(line, &i, line_n)) | 1)
	&& ((int)(b = search_float(line, &i, line_n)) | 1)
	&& ((int)(c = str_to_dbl(line, i, line_n)) | 1))
		while (line[i])
			if (line[i++] == ')')
				return (set_direct(a, b, c));
	puterr(line_n, "Wrong vector representation ", line);
	return (set_direct(0, 0, 0));
}

t_direct				add_dirs(t_direct d1, t_direct d2)
{
	t_direct sum;

	sum.x = d1.x + d2.x;
	sum.y = d1.y + d2.y;
	sum.z = d1.z + d2.z;
	return (sum);
}

int						free_func(t_shine **shine, t_form **sh)
{
	t_shine		*tmp;
	t_form		*stage_sh;

	while (*shine && ((int)(tmp = (*shine)->next) | 1) && (true_free(*shine)))
		*shine = tmp;
	while (*sh && ((int)(stage_sh = (*sh)->next)) && (true_free((*sh)->form))
	&& (true_free(*sh)))
		*sh = stage_sh;
	return (1);
}
