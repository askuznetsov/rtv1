/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bell_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:57:02 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:18:13 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline void		more_comp(char **ln, t_bell *bl, int ln_n, int *fl)
{
	if (st_with(*ln, "ang:") && (*ln = ft_strtrim_v1(*ln, 4))
	&& ((int)(bl->ang = fmin(1, fmax(0.05, tan(str_to_dbl(*ln, 0, ln_n) *
		M_PI / 180)))) | 1))
		*fl = *fl | (1 << 3);
	else
		puterr(ln_n, "Incorrect parameter ", *ln);
}

void					add_form(t_form **sh, void *form, char name, int id)
{
	t_form	*temp;
	t_form	*end;

	end = ft_memalloc(sizeof(t_form));
	end->name = name;
	end->id = id;
	end->form = form;
	if (name == 'p')
		end->inter = &inter_flat;
	else if (name == 's')
		end->inter = &inter_ball;
	else if (name == 'c')
		end->inter = &inter_bell;
	else
		end->inter = &inter_barrel;
	temp = *sh;
	end->next = NULL;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = end;
	}
	else
		*sh = end;
}

static void				bell_comp(char **line, t_bell *bl, int ln_n, int *fl)
{
	char		*new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (st_with(*line, "cen:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 1) | 1))
		bl->dot = parse_direct(*line, ln_n);
	else if (st_with(*line, "col:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 2) | 1))
		bl->colour = colour_parse(*line, ln_n);
	else if (st_with(*line, "dir:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | (1 << 2)) | 1))
		bl->route = dirto_len(parse_direct(*line, ln_n), 1, 0);
	else
		more_comp(line, bl, ln_n, fl);
}

int						st_with(char *line, char *st)
{
	int i;

	if (line && st && (i = -1))
		while (st[++i])
		{
			if (!line[i])
				return (0);
			if (line[i] != st[i])
				return (0);
		}
	else
		return (0);
	return (1);
}

int						parse_bell(int fd, int *ln_n, void **l_frm, int id)
{
	int			k;
	int			fl;
	char		*line;
	t_bell		*bell;

	fl = 0;
	bell = ft_memalloc(sizeof(t_bell));
	bell->id = id;
	while ((k = get_next_line(fd, &line)) > 0 && (++(*ln_n) | 1))
	{
		bell_comp(&line, bell, *ln_n, &fl);
		free(line);
		if (fl == 15)
			break ;
	}
	(k < 0) ? (perror_exit("RTv1")) : (void)1;
	add_form((t_form **)l_frm, bell, 'c', id);
	return (0);
}
