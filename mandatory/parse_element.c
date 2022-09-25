/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:21:29 by smia              #+#    #+#             */
/*   Updated: 2022/09/25 14:05:38 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_light	*alloc_light(t_scene *sc)
{
	t_light	*new_light;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
		ft_err("allocation failed\n");
	new_light->next = sc->light;
	sc->light = new_light;
	return (new_light);
}

void	parse_ambient(t_scene *sc, char **tockens)
{
	if (!tockens || !tockens[1] || !tockens[2] || tockens[3])
		ft_err("invalid ambiant!");
	if (sc->amb.count != 0)
		ft_err("too many ambiant");
	sc->amb.count++;
	sc->amb.ratio = ft_atod(tockens[1]);
	if (sc->amb.ratio < 0 || sc->amb.ratio > 1)
		ft_err("enter ambient lighting ratio in range [0.0,1.0]");
	sc->amb.col = get_color(tockens[2]);
}

void	parse_camera(t_scene *sc, char **tockens)
{
	if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
		ft_err("invalid camera !");
	if (sc->cam.count != 0)
		ft_err("too many camera");
	sc->cam.count++;
	sc->cam.cen = get_vec(tockens[1]);
	sc->cam.dir = get_vec(tockens[2]);
	if (sc->cam.dir.x > 1 || sc->cam.dir.y > 1 || sc->cam.dir.z > 1)
		ft_err("invalid orientation camera");
	if (sc->cam.dir.x < -1 || sc->cam.dir.y < -1 || sc->cam.dir.z < -1)
		ft_err("invalid orientation camera");
	if (sc->cam.dir.x == 0 && sc->cam.dir.y == 0 && sc->cam.dir.z == 0)
		ft_err("invalid orientation camera");
	sc->cam.fov = ft_atod(tockens[3]);
	if (sc->cam.fov < 0 || sc->cam.fov > 180)
		ft_err("FOV  in range [0,180]");
}

void	parse_light(t_scene *sc, char **tockens)
{
	t_light	*new;

	if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
		ft_err("invalid light !");
	new = alloc_light(sc);
	new->src = get_vec(tockens[1]);
	new->ratio = ft_atod(tockens[2]);
	if (new->ratio < 0 || new->ratio > 1)
		ft_err("enter the light brightness ratio in range [0.0,1.0]");
	new->col = get_color(tockens[3]);
}
