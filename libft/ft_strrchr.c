/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okuznets <okuznets@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 19:45:46 by okuznets          #+#    #+#             */
/*   Updated: 2018/01/16 15:13:07 by okuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ss;
	char	cc;

	ss = (char *)s;
	cc = (char)c;
	len = ft_strlen(ss);
	if (ss[len] == cc)
		return (ss + len);
	while (len >= 0)
	{
		if (ss[len] == cc)
			return (ss + len);
		len--;
	}
	return (NULL);
}
