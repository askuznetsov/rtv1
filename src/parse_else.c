/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_else.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:47 by okuznets          #+#    #+#             */
/*   Updated: 2019/06/19 02:31:47 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

char			*ft_strtrim_v1(char *line, int i)
{
	char *line_n;

	if (!line)
		exit(1);
	if ((int)ft_strlen(line) >= i)
		while (line[i] && line[i] < 33)
			i++;
	else if (!(i = 0))
		;
	line_n = ft_strdup(line + i);
	free(line);
	return (line_n);
}

static double	find_partition(char *line, int i, int line_n)
{
	double	part_num;
	int		len;

	len = 0;
	(!ft_isdigit(line[i])) ? puterr(line_n, "Wrong float num", line) : (void)1;
	part_num = (double)ft_atoi(line + i);
	while (ft_isdigit(line[i++]))
		len++;
	part_num = part_num / pow(10, len);
	return (part_num);
}

void			puterr(int line_number, char *s1, char *s2)
{
	ft_putstr("Error in line #");
	ft_putnbr(line_number);
	if (write(1, "\n", 1) && (write(1, s1, ft_strlen(s1)))
	&& write(1, "\"", 1) && (write(1, s2, ft_strlen(s1)))
	&& write(1, "\"\n", 2))
		;
	exit(1);
}

double			str_to_dbl(char *line, int i, int line_n)
{
	double	num_wh;
	double	neg;

	neg = 1;
	if (!line)
		return (0);
	if (line[i] == '-' && (neg = -1))
		i++;
	(!ft_isdigit(line[i])) ? puterr(line_n, "Wrong float num", line) : (void)1;
	num_wh = (double)ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	num_wh += (line[i++] == '.') ? find_partition(line, i, line_n) : 0;
	return (neg * num_wh);
}
