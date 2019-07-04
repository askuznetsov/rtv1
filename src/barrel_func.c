/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrel_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:56:37 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:14:14 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void					perror_exit(const char *s)
{
	perror(s);
	exit(1);
}

static	inline void		comp1(char **line, t_barrel *bar, int line_n, int *fl)
{
	if (st_with(*line, "rad:") && ((int)(*line = ft_strtrim_v1(*line, 4)))
	&& ((*fl = *fl | (1 << 3)) | 1))
		bar->radius = fmax(1, str_to_dbl(*line, 0, line_n));
	else
		puterr(line_n, "Incorrect parameter ", *line);
}

double					mod_dir(t_direct v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

static void				bar_comp(char **ln, t_barrel *bar, int ln_n, int *fl)
{
	char		*new_ln;

	new_ln = ft_strtrim(*ln);
	ft_strdel(ln);
	*ln = new_ln;
	if (st_with(*ln, "cen:") && (*ln = ft_strtrim_v1(*ln, 4))
	&& ((*fl = *fl | 1) | 1))
		bar->dot = parse_direct(*ln, ln_n);
	else if (st_with(*ln, "col:") && (*ln = ft_strtrim_v1(*ln, 4))
	&& ((*fl = *fl | 2) | 1))
		bar->colour = colour_parse(*ln, ln_n);
	else if (st_with(*ln, "dir:") && (*ln = ft_strtrim_v1(*ln, 4))
	&& (*fl = *fl | (1 << 2) | 1))
		bar->route = dirto_len(parse_direct(*ln, ln_n), 1, 0);
	else
		comp1(ln, bar, ln_n, fl);
}

int						parse_barrel(int fd, int *line_n, void **l_frm, int id)
{
	int			k;
	int			fl;
	char		*line;
	t_barrel	*bar;

	fl = 0;
	bar = ft_memalloc(sizeof(t_barrel));
	bar->id = id;
	while ((k = get_next_line(fd, &line)) > 0 && (++(*line_n) | 1))
	{
		bar_comp(&line, bar, *line_n, &fl);
		free(line);
		if (fl == 15)
			break ;
	}
	(k < 0) ? perror_exit("RTv1") : (void)1;
	add_form((t_form **)l_frm, bar, 0, id);
	return (0);
}
