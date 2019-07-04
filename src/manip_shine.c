/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_shine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:42 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:30:44 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline void		add_shine(t_shine **shine_list, t_shine *shine)
{
	t_shine *step;

	shine->next = NULL;
	step = *shine_list;
	if (step)
	{
		while (step->next)
			step = step->next;
		step->next = shine;
	}
	else
		*shine_list = shine;
}

static void				better_intensity(char **line, t_shine *shine,
int line_n, int *fl)
{
	double		intenc;

	if (st_with(*line, "col:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | (1 << 1)) | 1))
		shine->colour = colour_parse(*line, line_n);
	else if (st_with(*line, "int:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 1) | 1)
	&& ((int)(intenc = str_to_dbl(*line, 0, line_n)) | 1))
	{
		(intenc > 1 || intenc < 0)
		? puterr(line_n, "No such intenc as ", *line) : (void)1;
		shine->intencity = intenc;
	}
	else
		puterr(line_n, "Incorrect parameter ", *line);
}

static void				get_shine_params(char **line, t_shine *shine,
int line_n, int *fl)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (!ft_strcmp(*line, "point") && !(shine->is_route = 0))
		*fl = (*fl & ~(1 << 3)) | (1 << 4);
	else if (!ft_strcmp(*line, "direct") && (shine->is_route = 1))
		*fl = (*fl & ~(1 << 4)) | (1 << 3);
	else if (((st_with(*line, "dir:") && (*fl & (1 << 3))) ||
	(st_with(*line, "cen:") && (*fl & (1 << 4))))
	&& (*line = ft_strtrim_v1(*line, 4))
	&& (*fl = *fl | (1 << 2)))
		shine->route = parse_direct(*line, line_n);
	else
		better_intensity(line, shine, line_n, fl);
}

int						shine_parse(int fd, int *line_n, void **sh_lst, int n)
{
	int			fl;
	char		*line;
	int			k;
	t_shine		*shine;

	fl = 0 && (++n | 1);
	shine = ft_memalloc(sizeof(t_shine));
	while ((k = get_next_line(fd, &line)) > 0 && (++(*line_n) | 1))
	{
		get_shine_params(&line, shine, *line_n, &fl);
		free(line);
		if (fl == 15 || fl == 23)
			break ;
	}
	if (k < 0 && (true_free(shine)))
		perror_exit("RTv1");
	add_shine((t_shine **)sh_lst, shine);
	return (0);
}
