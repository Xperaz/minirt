/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:52:08 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 14:07:03 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_sphere(t_scene *sc, char **tockens)
{
	t_objs	*obj;

	if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
		ft_err("invalid sphere");
	obj = alloc_obj(sc);
	obj->type = SP;
	obj->cen = get_vec(tockens[1]);
	obj->p.x = ft_atod(tockens[2]);
	if (obj->p.x <= 0)
		ft_err("invalid diameter sphere");
	obj->col = get_color(tockens[3]);
}

void	parse_cylinder(t_scene *sc, char **tockens)
{
	t_objs	*obj;

	if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || !tockens[4]
		|| !tockens[5] || tockens[6])
		ft_err("invalid cylinder");
	obj = alloc_obj(sc);
	obj->type = CY;
	obj->cen = get_vec(tockens[1]);
	obj->dir = get_vec(tockens[2]);
	if (obj->dir.x > 1 || obj->dir.y > 1 || obj->dir.z > 1)
		ft_err("invalid orientation cylinder");
	if (obj->dir.x < -1 || obj->dir.y < -1 || obj->dir.z < -1)
		ft_err("invalid orientation cylinder");
	obj->p.x = ft_atod(tockens[3]);
	obj->p.y = ft_atod(tockens[4]);
	if (obj->p.x <= 0 || obj->p.y <= 0)
		ft_err("invalid diameter cy");
	obj->col = get_color(tockens[5]);
}

void	parse_plane(t_scene *sc, char **tockens)
{
	t_objs	*obj;

	if (!tockens || !tockens[1] || !tockens[2] || !tockens[3] || tockens[4])
		ft_err("invalid plane!");
	obj = alloc_obj(sc);
	obj->type = PL;
	obj->cen = get_vec(tockens[1]);
	obj->dir = get_vec(tockens[2]);
	if (obj->dir.x > 1 || obj->dir.y > 1 || obj->dir.z > 1)
		ft_err("invalid orientation plane");
	if (obj->dir.x < -1 || obj->dir.y < -1 || obj->dir.z < -1)
		ft_err("invalid orientation plane");
	obj->col = get_color(tockens[3]);
}
