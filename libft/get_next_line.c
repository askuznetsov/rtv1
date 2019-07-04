/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 12:48:57 by okuznets          #+#    #+#             */
/*   Updated: 2018/05/20 14:22:21 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strjoin_free_version(char *str, char *string)
{
	char *temp;

	temp = ft_strdup(str);
	if (str)
		free(str);
	str = ft_strjoin(temp, string);
	free(temp);
	return (str);
}

t_list			*check_file(size_t fd)
{
	static t_list	*file = NULL;
	t_list			*temp;

	temp = file;
	while (temp)
	{
		if (temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew("\0", fd);
	ft_lstadd(&file, temp);
	return (temp);
}

static char		*copy(char **dst_str, char *src_str)
{
	int count;
	int place_for_zero;

	count = 0;
	place_for_zero = 1;
	while (src_str[count] != '\n')
	{
		if (src_str[count] == '\0')
		{
			place_for_zero = 0;
			break ;
		}
		count++;
	}
	*dst_str = ft_strsub(src_str, 0, count);
	return (ft_strdup(&src_str[count + place_for_zero]));
}

int				get_next_line(const int fd, char **line)
{
	t_list	*file;
	char	*temp;
	char	buff[BUFF_SIZE + 1];
	int		is_read;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	file = check_file(fd);
	*line = NULL;
	while ((is_read = read(fd, buff, BUFF_SIZE)))
	{
		buff[is_read] = '\0';
		file->content = ft_strjoin_free_version(file->content, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (ft_strlen(file->content) == 0)
		return (0);
	*line = file->content;
	temp = file->content;
	file->content = copy(line, temp);
	free(temp);
	return (1);
}
