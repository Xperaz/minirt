/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:22:01 by smia              #+#    #+#             */
/*   Updated: 2022/09/25 14:05:46 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	get_color(char *s)
{
	char	**params;
	t_vec	cord;

	params = ft_split(s, ',');
	if (!params || !params[1] || !params[2] || params[3])
		ft_err("invalid color!");
	cord = (t_vec){ft_atoi(params[0]), ft_atoi(params[1]), ft_atoi(params[2])};
	if (cord.x > 255 || cord.y > 255 || cord.z > 255)
		ft_err("invalid color");
	if (cord.x < 0 || cord.y < 0 || cord.z < 0)
		ft_err("invalid color");
	free_split(params);
	return (cord);
}

t_vec	get_vec(char *s)
{
	char	**params;
	t_vec	cord;

	params = ft_split(s, ',');
	if (!params || !params[1] || !params[2] || params[3])
		ft_err("invalid coordinates");
	cord = make_vec(ft_atod(params[0]), ft_atod(params[1]), ft_atod(params[2]));
	free_split(params);
	return (cord);
}

void	parse_line(char *id, char **tockens, t_scene *sc)
{
	if (id[0] == 'A' && id[1] == '\0')
		parse_ambient(sc, tockens);
	else if (id[0] == 'C' && id[1] == '\0')
		parse_camera(sc, tockens);
	else if (id[0] == 'L' && id[1] == '\0')
		parse_light(sc, tockens);
	else if (id[0] == 's' && id[1] == 'p' && id[2] == '\0')
		parse_sphere(sc, tockens);
	else if (id[0] == 'p' && id[1] == 'l' && id[2] == '\0')
		parse_plane(sc, tockens);
	else if (id[0] == 'c' && id[1] == 'y' && id[2] == '\0')
		parse_cylinder(sc, tockens);
	else
		ft_err("invalid object type");
}

void	parse(t_scene *sc, int fd)
{
	char	**tockens;

	while (1337)
	{
		tockens = ft_split(gnl(fd), ' ');
		if (tockens == NULL)
			break ;
		if (*tockens)
			parse_line(*tockens, tockens, sc);
		free_split(tockens);
	}
	close(fd);
}
