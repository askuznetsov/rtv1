/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 01:47:27 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:24:22 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		cam_comp(char **line, t_cam *cam, int line_n, int *fl)
{
	char *new_line;

	new_line = ft_strtrim(*line);
	ft_strdel(line);
	*line = new_line;
	if (st_with(*line, "dir:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 1) | 1))
		(*cam).route = dirto_len(parse_direct(*line, line_n), 1, 0);
	else if (st_with(*line, "cen:") && (*line = ft_strtrim_v1(*line, 4))
	&& ((*fl = *fl | 2) | 1))
		(*cam).birth = parse_direct(*line, line_n);
	else
		puterr(line_n, "Incorrect parameter ", *line);
}

int				parse_cam(int fd, int *line_n, t_cam *cam)
{
	int			k;
	int			fl;
	char		*line;

	fl = 0;
	while ((k = get_next_line(fd, &line)) > 0 && (++(*line_n) | 1))
	{
		cam_comp(&line, cam, *line_n, &fl);
		free(line);
		if (fl == 3)
			break ;
	}
	(k < 0) ? perror_exit("RTv1") : (void)((*cam).is_est = 1);
	return (0);
}

void			rtv_init(t_rtv *rtv, t_form **list_form, t_shine **shine)
{
	if (!(rtv->mlx = mlx_init()) && (free_func(shine, list_form))
	&& (true_free(rtv)))
		perror_exit("RTv1");
	if (!(rtv->win = mlx_new_window(rtv->mlx, WH_SCREEN, WH_SCREEN, "RTv1"))
	&& (free_func(shine, list_form)) && (true_free(rtv)))
		perror_exit("RTv1");
	if (!(rtv->image = mlx_new_image(rtv->mlx, WH_SCREEN, WH_SCREEN))
	&& (free_func(shine, list_form)) && (true_free(rtv)))
		perror_exit("RTv1");
}

int				exit_func(int key, t_rtv *rtv)
{
	if (key == ESCAPE)
	{
		free_func(rtv->shine, rtv->forms);
		free(rtv);
		exit(0);
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_form		*list_form;
	t_cam		camera;
	t_shine		*shine;
	t_rtv		*rtv;
	int			fd;

	if (argc != 2 && write(2, "There must be one parameter\n", 28))
		exit(1);
	if (((fd = open(argv[1], O_RDONLY)) < 0) || (read(fd, NULL, 0) < 0))
		perror_exit("RTv1");
	rtv = ft_memalloc(sizeof(t_rtv));
	rtv->forms = &list_form;
	rtv->camera = &camera;
	rtv->shine = &shine;
	parse_file(fd, rtv);
	rtv_init(rtv, &list_form, &shine);
	cast_gleams(rtv, list_form, shine, camera);
	mlx_key_hook(rtv->win, exit_func, rtv);
	mlx_loop(rtv->mlx);
	return (0);
}
