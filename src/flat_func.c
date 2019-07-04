/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:58:38 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 02:31:47 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static double	arr_to_flat(t_gleam gl, t_flat *p)
{
	t_direct	v;
	double		num;

	num = mul_scal(gl.route, p->perpend);
	if (!num)
		return (MAX_LENGTH);
	v = sub_dirs(gl.birth, p->dot);
	gl.arr = (-1) * mul_scal(v, p->perpend) / num;
	return (gl.arr < 0) ? (MAX_LENGTH) : (gl.arr);
}

double			inter_flat(t_gleam *gl, void *pl, t_shine *shine,
t_form *sh)
{
	t_direct	dir;
	t_gleam		s_gleam;
	t_flat		*p;

	p = (t_flat *)pl;
	if (((*gl).arr = arr_to_flat(*gl, p)) == MAX_LENGTH)
		return (0);
	if (sh && ((s_gleam.id = p->id) | 1)
	&& ((s_gleam.prime_col = p->colour) | 1))
	{
		dir = dirto_len(p->perpend, -1, 0);
		s_gleam.rev_route = dirto_len((*gl).route, -1, 1);
		s_gleam.birth = add_dirs((*gl).birth, dirto_len((*gl).route,
		(*gl).arr, 0));
		return (shine_calc(dir, s_gleam, shine, sh));
	}
	return (1);
}

static void		flat_comp(char **line, t_flat *flat, int line_n, int *fl)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (st_with(*line, "cen:") && (*line = ft_strtrim_v1(*line, 4))
	&& (*fl = *fl | 1))
		flat->dot = parse_direct(*line, line_n);
	else if (st_with(*line, "col:") && (*line = ft_strtrim_v1(*line, 4))
	&& (*fl = *fl | 2))
		flat->colour = colour_parse(*line, line_n);
	else if (st_with(*line, "nor:") && (*line = ft_strtrim_v1(*line, 4))
	&& (*fl = *fl | 4))
		flat->perpend = dirto_len(parse_direct(*line, line_n), 1, 0);
	else
		puterr(line_n, "Incorrect parameter ", *line);
}

int				parse_flat(int fd, int *line_n, void **list_form, int id)
{
	int			k;
	int			fl;
	char		*line;
	t_flat		*flat;

	fl = 0;
	flat = ft_memalloc(sizeof(t_flat));
	flat->id = id;
	while ((k = get_next_line(fd, &line)) > 0 && (((*line_n)++) | 1))
	{
		flat_comp(&line, flat, *line_n, &fl);
		free(line);
		if (fl == 7)
			break ;
	}
	(k < 0) ? perror_exit("RTv1") : (void)1;
	add_form((t_form **)list_form, flat, 'p', id);
	return (0);
}
