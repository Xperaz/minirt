/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:30:08 by smia              #+#    #+#             */
/*   Updated: 2022/09/25 14:05:57 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((char *)src);
	if (!src)
		return (0);
	if (dstsize == 0)
		return (len);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

static int	count_words(const char *str, char sp)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str != sp)
			str++;
		while (sp && *str && *str == sp)
			str++;
		count++;
	}
	return (count);
}

static char	*malloc_word(const char *str, char sp)
{
	char	*word;
	int		count;

	count = 0;
	while (str[count] && str[count] != sp)
		count++;
	word = (char *)malloc(sizeof(char) * (count + 1));
	if (word == 0)
		return (0);
	ft_strlcpy(word, str, count + 1);
	return (word);
}

static char	**ft_free(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
	return (0);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		i;

	if (str == 0)
		return (0);
	while (*str && *str == c)
		str++;
	tab = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (tab == 0)
		return (0);
	i = 0;
	while (*str)
	{
		tab[i] = malloc_word(str, c);
		if (tab[i] == NULL)
			return (ft_free(tab));
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
