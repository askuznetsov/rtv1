/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:24:36 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 03:06:53 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include "../libft/libft.h"
# define NUM_FIG 6
# define MAX_LENGTH 100500
# define WH_SCREEN 1000
# define ESCAPE 53

/*
** Vector struct
*/

typedef struct	s_direct
{
	double x;
	double y;
	double z;
}				t_direct;

/*
** Light struct
*/

typedef struct	s_shine
{
	char			is_route;
	t_direct		route;
	int				colour;
	double			intencity;
	struct s_shine	*next;
}				t_shine;

/*
** Camera struct
*/

typedef struct	s_cam
{
	t_direct	birth;
	t_direct	route;
	t_direct	up;
	t_direct	right;
	int			is_est;
	double		arr;
}				t_cam;

/*
** Ray struct
*/

typedef struct	s_gleam
{
	t_direct	birth;
	t_direct	route;
	t_direct	rev_route;
	double		arr;
	int			id;
	int			prime_col;
}				t_gleam;

/*
** Struct for generic figure
*/

typedef struct	s_form
{
	char			name;
	int				id;
	void			*form;
	double			(*inter)(t_gleam *, void *, t_shine *, struct s_form *);
	struct s_form	*next;
}				t_form;

/*
** Cone struct
*/

typedef struct	s_bell
{
	t_direct	route;
	t_direct	dot;
	double		ang;
	int			id;
	int			colour;
}				t_bell;

/*
** Sphere struct
*/

typedef struct	s_ball
{
	int			colour;
	t_direct	heart;
	int			id;
	double		radius;
}				t_ball;

/*
** Cylinder struct
*/

typedef struct	s_barrel
{
	t_direct	route;
	t_direct	dot;
	double		radius;
	int			id;
	int			colour;
}				t_barrel;

/*
** Plane struct
*/

typedef struct	s_flat
{
	t_direct	perpend;
	t_direct	dot;
	int			id;
	int			colour;
}				t_flat;

/*
** Struct for parsing
*/

typedef struct	s_parse
{
	char		*name;
	int			(*parse)(int, int*, void**, int);
}				t_parse;

/*
** Main struct with mlx data, array of figures' pointers, etc
*/

typedef struct	s_rtv
{
	void		*mlx;
	void		*win;
	void		*image;
	t_form		**forms;
	t_shine		**shine;
	t_cam		*camera;
	double		x;
	double		y;
	int			line_n;
}				t_rtv;

/*
** Parsing functions
*/

void			parse_file(int fd, t_rtv *rtv);
int				parse_flat(int fd, int *line_n, void **list_form, int id);
int				parse_cam(int fd, int *line_n, t_cam *camera);
t_direct		parse_direct(char *line, int line_n);
int				parse_barrel(int fd, int *line_n, void **list_form, int id);
int				colour_parse(char *line, int line_n);
int				parse_ball(int fd, int *line_n, void **list_form, int id);
int				parse_bell(int fd, int *line_n, void **list_form, int id);

/*
** Functions for intersecting figures
*/

double			inter_bell(t_gleam *r, void *c, t_shine *sh, t_form *f);
double			inter_flat(t_gleam *r, void *pl, t_shine *sh, t_form *f);
double			inter_barrel(t_gleam *r, void *c, t_shine *sh, t_form *f);
double			inter_ball(t_gleam *r, void *sf, t_shine *sh, t_form *f);
void			cast_gleams(t_rtv *r, t_form *f, t_shine *sh, t_cam cam);

/*
** Utils and other functions
*/

int				free_func(t_shine **shine, t_form **sh);
int				true_free(void *to_free);
void			puterr(int line_number, char *s1, char *s2);
void			perror_exit(const char *s);
void			add_form(t_form **sh, void *shape, char name, int id);
double			mod_dir(t_direct v);
double			mul_scal(t_direct d1, t_direct d2);
double			str_to_dbl(char *line, int i, int line_n);
int				shine_calc(t_direct d, t_gleam g, t_shine *s, t_form *f);
int				st_with(char *line, char *begin);
int				shine_calc(t_direct d, t_gleam gl, t_shine *sh, t_form *f);
int				shine_parse(int fd, int *line_n, void **shine_list, int n);
char			*ft_strtrim_v1(char *line, int i);
t_direct		sub_dirs(t_direct d1, t_direct d2);
t_direct		mul_dir(t_direct d1, t_direct d2);
t_direct		dirto_len(t_direct v, double len, int norm);
t_direct		set_direct(double x, double y, double z);
t_direct		add_dirs(t_direct d1, t_direct d2);

#endif
