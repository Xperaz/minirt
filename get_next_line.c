/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:05:50 by smia              #+#    #+#             */
/*   Updated: 2022/06/22 04:48:35 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*ft_strjoin(char *s, char c)
{
	char	*out;
	int		n;


	n = 2;
	if (s)
		while (*s && s++)
			n++;
	out = malloc(n * sizeof(char));
	out[--n] = '\0';
	out[--n] = c;
	if (s)
	{
		while (n--)
			out[n] = *--s;
		free(s);
	}
	return (out);
}

char	*gnl(int fd)
{
	char		c;
	static char	*line = NULL;

	if (line)
		free(line);
	line = NULL;
	while (read(fd, &c, 1) && (c != '\n' || line == NULL))
	{
		if (c == '\n')
			continue ;
		line = ft_strjoin(line, c);
	}
	return (line);
}