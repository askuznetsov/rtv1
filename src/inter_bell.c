/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_bell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:28:21 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 02:31:47 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static double			dest_to_bell(t_gleam gl, t_bell *bell)
{
	t_direct	v;
	double		text;
	double		abc[3];
	double		t[2];

	v = sub_dirs(gl.birth, bell->dot);
	t[0] = mul_scal(gl.route, bell->route);
	t[1] = mul_scal(v, bell->route);
	abc[2] = (1 + bell->ang * bell->ang);
	abc[0] = mul_scal(gl.route, gl.route) - abc[2] * (t[0] * t[0]);
	abc[1] = 2 * (mul_scal(gl.route, v) - abc[2] * t[0] * t[1]);
	abc[2] = mul_scal(v, v) - abc[2] * (t[1] * t[1]);
	text = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (text < 0)
		return (MAX_LENGTH);
	text = sqrt(text);
	t[0] = (-abc[1] - text) / (2 * abc[0]);
	t[1] = (-abc[1] + text) / (2 * abc[0]);
	gl.arr = (t[0] < t[1]) ? t[0] : t[1];
	return (gl.arr < 0) ? (MAX_LENGTH) : (gl.arr);
}

double					inter_bell(t_gleam *gl, void *con, t_shine *shine,
t_form *sh)
{
	t_direct	dir;
	double		a;
	t_bell		*bell;
	t_gleam		gleam;

	bell = (t_bell *)con;
	if (((*gl).arr = dest_to_bell(*gl, bell)) == MAX_LENGTH)
		return (0);
	if (sh && ((gleam.id = bell->id) | 1)
	&& ((gleam.prime_col = bell->colour) | 1))
	{
		gleam.birth = add_dirs((*gl).birth, dirto_len((*gl).route,
		(*gl).arr, 0));
		gleam.rev_route = dirto_len((*gl).route, -1, 1);
		dir = sub_dirs((*gl).birth, bell->dot);
		a = mul_scal((*gl).route, bell->route) * ((*gl).arr) +
		mul_scal(dir, bell->route);
		a = (1 + bell->ang * bell->ang) * a;
		dir = dirto_len(sub_dirs(sub_dirs(gleam.birth, bell->dot),
		dirto_len(bell->route, a, 0)), 1, 0);
		return (shine_calc(dir, gleam, shine, sh));
	}
	return (1);
}

static double			dest_to_cylin(t_gleam gl, t_barrel *bar)
{
	t_direct	v;
	double		descr;
	double		abc[3];
	double		t[2];

	v = sub_dirs(gl.birth, bar->dot);
	t[0] = mul_scal(gl.route, bar->route);
	t[1] = mul_scal(v, bar->route);
	abc[0] = mul_scal(gl.route, gl.route) - (t[0] * t[0]);
	abc[1] = 2 * (mul_scal(gl.route, v) - t[0] * t[1]);
	abc[2] = mul_scal(v, v) - (t[1] * t[1]) - bar->radius * bar->radius;
	descr = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (descr < 0)
		return (MAX_LENGTH);
	descr = sqrt(descr);
	t[0] = (-abc[1] - descr) / (2 * abc[0]);
	t[1] = (-abc[1] + descr) / (2 * abc[0]);
	gl.arr = (t[0] < t[1]) ? t[0] : t[1];
	return (gl.arr < 0) ? (MAX_LENGTH) : (gl.arr);
}

double					inter_barrel(t_gleam *gl, void *cy, t_shine *shine,
t_form *fr)
{
	t_gleam		s_gleam;
	t_direct	dir;
	double		a;
	t_barrel	*bar;

	bar = (t_barrel *)cy;
	if (((*gl).arr = dest_to_cylin(*gl, bar)) == MAX_LENGTH)
		return (0);
	if (fr && ((s_gleam.id = bar->id) | 1)
	&& ((s_gleam.prime_col = bar->colour) | 1))
	{
		s_gleam.birth = add_dirs((*gl).birth, dirto_len((*gl).route,
		(*gl).arr, 0));
		s_gleam.rev_route = dirto_len((*gl).route, -1, 1);
		dir = add_dirs((*gl).birth, dirto_len((*gl).route, (*gl).arr,
		0));
		a = mul_scal((*gl).route, bar->route) * ((*gl).arr) +
		mul_scal(dir, bar->route);
		dir = sub_dirs(dir, bar->dot);
		dir = dirto_len(sub_dirs(dir, dirto_len(bar->route, a, 0)), 1, 0);
		return (shine_calc(dir, s_gleam, shine, fr));
	}
	return (1);
}
