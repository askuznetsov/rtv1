/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ray_tracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:01:02 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:21:19 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

#define NUM 500

static inline void	pixel_add(t_rtv *rtv, int x, int y, unsigned int colour)
{
	int		end;
	int		bbpe;
	int		*arr;
	int		size_l;

	if (x >= 0 && x < WH_SCREEN && y >= 0 && y < WH_SCREEN
	&& (arr = (int *)mlx_get_data_addr(rtv->image, &bbpe, &size_l, &end)))
		arr[WH_SCREEN * y + x] = colour;
}

static int			obtain_colour(t_gleam gleam, t_form *form, t_shine *shine)
{
	int		colour;
	t_form	*st;
	double	min;
	int		show_col;

	min = MAX_LENGTH;
	st = form;
	show_col = 0;
	while (form && ((colour = form->inter(&gleam,
	form->form, shine, st)) | 1))
	{
		if (gleam.arr <= min && ((int)(min = gleam.arr) | 1))
			show_col = colour;
		form = form->next;
	}
	return (show_col);
}

t_direct			dirto_len(t_direct v, double len, int dir)
{
	double mod;

	if (!dir && ((int)(mod = mod_dir(v)) | 1)
	&& ((int)(v.x = v.x / mod * len) | 1)
	&& ((int)(v.y = v.y / mod * len) | 1))
		v.z = v.z / mod * len;
	else if (((int)(v.x = v.x * len) | 1)
	&& ((int)(v.y = v.y * len) | 1))
		v.z = v.z * len;
	return (v);
}

void				cast_gleams(t_rtv *rtv, t_form *list_form, t_shine *sh,
t_cam cam)
{
	double		i;
	double		j;
	t_gleam		gleam;
	t_direct	v[3];
	int			colour;

	j = (-1) * WH_SCREEN / 2 - 1;
	gleam.route = dirto_len(cam.route, 1, 0);
	while (++j < WH_SCREEN / 2)
	{
		i = (-1) * WH_SCREEN / 2 - 1;
		while (++i < WH_SCREEN / 2)
		{
			v[0] = dirto_len(cam.up, j, 1);
			v[1] = dirto_len(cam.right, i, 1);
			v[2].x = v[0].x + v[1].x;
			v[2].y = v[0].y + v[1].y;
			v[2].z = v[0].z + v[1].z;
			gleam.birth = add_dirs(v[2], cam.birth);
			colour = obtain_colour(gleam, list_form, sh);
			pixel_add(rtv, i + NUM, j + NUM, colour);
		}
	}
	mlx_put_image_to_window(rtv->mlx, rtv->win, rtv->image, 0, 0);
}
