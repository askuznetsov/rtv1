/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:53 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:25:57 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline t_cam	*set_camera(t_cam *cam)
{
	cam->route = dirto_len(cam->route, 1, 0);
	if (cam->route.x == 0 && cam->route.z == 0)
	{
		cam->up = set_direct(1, 0, 0);
		cam->right = set_direct(0, 1, 0);
	}
	else
	{
		cam->up = set_direct(0, -1, 0);
		cam->right = mul_dir(cam->route, cam->up);
		cam->right = dirto_len(cam->right, 1, 0);
		cam->up = mul_dir(cam->right, cam->route);
	}
	return (cam);
}

static inline void	correct_flat_perpend(t_form *forms_list, t_cam camera)
{
	t_direct perp;

	while (forms_list)
	{
		if (forms_list->name == 'p')
		{
			perp = ((t_flat *)(forms_list->form))->perpend;
			if (mul_scal(perp, camera.route) <= 0)
				((t_flat *)(forms_list->form))->perpend =
			dirto_len(perp, -1, 0);
		}
		forms_list = forms_list->next;
	}
}

static void			exec_parsing(char **str, t_rtv *rtv, const t_parse pa[],
int fd)
{
	static int	id;
	int			i;

	i = -1;
	while (++i < NUM_FIG)
	{
		if (**str == 0 || **str == '#')
			break ;
		else if (!ft_strcmp(*str, pa[i].name))
		{
			if (!ft_strcmp(*str, "camera:"))
				parse_cam(fd, &(rtv->line_n), rtv->camera);
			else if (!ft_strcmp(*str, "light:"))
				pa[i].parse(fd, &(rtv->line_n), (void **)(rtv->shine), 0);
			else
				pa[i].parse(fd, &(rtv->line_n), (void **)(rtv->forms), id++);
			break ;
		}
		if (i == NUM_FIG && (free_func(rtv->shine, rtv->forms)))
			puterr(rtv->line_n, "No such object: ", *str);
	}
}

static inline void	read_line(t_rtv *rt, int fd, const t_parse pa[])
{
	int			k;
	char		*line;
	char		*n_line;

	rt->line_n = 0;
	while ((k = get_next_line(fd, &line)) > 0 && ((rt->line_n)++ | 1)
	&& ((int)(n_line = ft_strtrim(line)) | 1))
	{
		free(line);
		line = n_line;
		exec_parsing(&line, rt, pa, fd);
		ft_strdel(&line);
	}
	(k < 0 && free_func(rt->shine, rt->forms)) ? perror_exit("RTv1") : (void)1;
}

void				parse_file(int fd, t_rtv *rtv)
{
	const t_parse pa[] = {{"camera:", NULL}, {"sphere:", &parse_ball},
	{"light:", &shine_parse}, {"cylinder:", &parse_barrel},
	{"cone:", &parse_bell}, {"plane:", &parse_flat}};

	*(rtv->forms) = NULL;
	*(rtv->shine) = NULL;
	(rtv->camera)->is_est = 0;
	read_line(rtv, fd, pa);
	if (!(*(rtv->camera)).is_est && free_func(rtv->shine, rtv->forms)
	&& write(2, "No camera found\n", 16))
		exit(1);
	correct_flat_perpend(*(rtv->forms), *(rtv->camera));
	rtv->camera = set_camera(rtv->camera);
}
