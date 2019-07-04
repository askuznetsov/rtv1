/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:59:11 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:18:51 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double				mul_scal(t_direct d1, t_direct d2)
{
	return (d1.x * d2.x + d1.y * d2.y + d1.z * d2.z);
}

static double		dest_to_phere(t_gleam gl, t_ball *s)
{
	t_direct	d1;
	double		anal;
	double		t[2];
	double		abc[3];

	d1 = sub_dirs(gl.birth, s->heart);
	abc[0] = mul_scal(gl.route, gl.route);
	abc[1] = 2 * mul_scal(gl.route, d1);
	abc[2] = mul_scal(d1, d1) - s->radius * s->radius;
	anal = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (anal <= 0)
		return (MAX_LENGTH);
	anal = sqrt(anal);
	t[0] = (-abc[1] - anal) / (2 * abc[0]);
	t[1] = (-abc[1] + anal) / (2 * abc[0]);
	gl.arr = (t[0] < t[1]) ? t[0] : t[1];
	return (gl.arr < 0) ? (MAX_LENGTH) : (gl.arr);
}

static void			ball_comp(char **line, t_ball *s, int line_n, int *fl)
{
	char	*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (st_with(*line, "cen:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 1) | 1))
		s->heart = parse_direct(*line, line_n);
	else if (st_with(*line, "col:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 2) | 1))
		s->colour = colour_parse(*line, line_n);
	else if (st_with(*line, "rad:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 4) | 1))
		s->radius = fmax(1, str_to_dbl(*line, 0, line_n));
	else
		puterr(line_n, "Incorrect parameter ", *line);
}

double				inter_ball(t_gleam *gl, void *sf, t_shine *sh, t_form *frm)
{
	t_direct	dir;
	t_ball		*s;
	t_gleam		s_gleam;

	s = (t_ball *)sf;
	if (((*gl).arr = dest_to_phere(*gl, s)) == MAX_LENGTH)
		return (0);
	if (frm && ((s_gleam.id = s->id) | 1)
	&& ((s_gleam.prime_col = s->colour) | 1))
	{
		s_gleam.birth = add_dirs((*gl).birth, dirto_len((*gl).route,
		(*gl).arr, 0));
		s_gleam.rev_route = dirto_len((*gl).route, -1, 1);
		dir = dirto_len(sub_dirs(s_gleam.birth, s->heart), 1, 0);
		return (shine_calc(dir, s_gleam, sh, frm));
	}
	return (1);
}

int					parse_ball(int fd, int *line_n, void **list_form, int id)
{
	int			k;
	int			fl;
	char		*line;
	t_ball		*ball;

	ball = ft_memalloc(sizeof(t_ball));
	ball->id = id;
	fl = 0;
	while ((k = get_next_line(fd, &line)) > 0)
	{
		(*line_n)++;
		ball_comp(&line, ball, *line_n, &fl);
		ft_strdel(&line);
		if (fl == 7)
			break ;
	}
	(k < 0) ? perror_exit("RTv1") : (void)1;
	add_form((t_form **)list_form, ball, 's', id);
	return (0);
}
