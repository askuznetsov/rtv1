/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:03:30 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:26:32 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

#define COL_RNG 255
#define MAX_UCHAR 256

static int			shine_producer(t_direct dir, t_gleam gl, t_shine *sh,
t_direct h)
{
	double	dir_l;
	int		col_r;
	int		col_g;
	int		col_b;
	double	w;

	dir_l = mul_scal(dir, gl.route);
	w = fmax(0, mul_scal(dir, h));
	w = pow(w, 12);
	col_b = fmin(0xFF, (sh->colour & COL_RNG)
	* fmax(0, dir_l) * sh->intencity
	+ (sh->colour & COL_RNG) * w * sh->intencity);
	col_g = fmin(0xFF, (sh->colour >> 8 & COL_RNG) * fmax(0, dir_l) *
	sh->intencity + (sh->colour >> 8 & COL_RNG) * w * sh->intencity);
	col_r = fmin(0xFF, (sh->colour >> 16 & COL_RNG) * fmax(0, dir_l) *
	sh->intencity + (sh->colour >> 16 & COL_RNG) * w * sh->intencity);
	return (col_b + (col_g * MAX_UCHAR) + (col_r * MAX_UCHAR * MAX_UCHAR));
}

static inline int	amb_shine(int shape_col, t_shine *shine)
{
	int		col_r;
	int		col_g;
	int		col_b;
	double	k;

	k = 0;
	while (shine && ((int)(k = fmax(shine->intencity / 2, k)) | 1))
		shine = shine->next;
	col_r = fmax(0, (shape_col >> 16 & COL_RNG) * k);
	col_g = fmax(0, (shape_col >> 8 & COL_RNG) * k);
	col_b = fmax(0, (shape_col & COL_RNG) * k);
	return (col_b + (col_g * MAX_UCHAR) + (col_r * MAX_UCHAR * MAX_UCHAR));
}

static inline int	colour_add(int fst, int sec)
{
	int sum;

	sum = fmin(0xFF, (fst & COL_RNG) + (sec & COL_RNG));
	sum += fmin(0xFF, (fst >> 8 & COL_RNG) + (sec >> 8 & COL_RNG))
	* MAX_UCHAR;
	sum += fmin(0xFF, (fst >> 16 & COL_RNG) + (sec >> 16 & COL_RNG))
	* MAX_UCHAR * MAX_UCHAR;
	return (sum);
}

static inline int	in_light_area(t_gleam gleam, t_form *sh, t_shine *shine)
{
	while (sh)
	{
		if ((sh->id != gleam.id) && (sh->inter(&gleam, sh->form, shine, NULL)))
			if ((!shine->is_route && gleam.arr < mod_dir(sub_dirs(gleam.birth,
			shine->route))) || shine->is_route)
				return (0);
		sh = sh->next;
	}
	return (1);
}

int					shine_calc(t_direct dir, t_gleam gl, t_shine *shine,
t_form *sh)
{
	t_direct	h;
	int			colour;

	colour = amb_shine(gl.prime_col, shine);
	while (shine)
	{
		gl.route = (shine->is_route) ? dirto_len(shine->route, -1, 0)
		: dirto_len(sub_dirs(shine->route, gl.birth), 1, 0);
		if (in_light_area(gl, sh, shine))
		{
			h = add_dirs(gl.rev_route, gl.route);
			colour = colour_add(colour, shine_producer(dir,
			gl, shine, dirto_len(h, 1, 0)));
		}
		shine = shine->next;
	}
	return (colour);
}
