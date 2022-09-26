/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normale.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:18:51 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 18:36:13 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_inter	spher_normal(t_inter hold, t_objs *obj, t_CamRay *ray)
{
	t_inter	inter;

	inter.t = inter_sphere(ray, obj);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
		inter.hit = add_vec(ray->origin, mult_vec(ray->dir, inter.t));
		inter.norm = get_normalized(sub_vec(inter.hit, obj->cen));
		hold = inter;
	}
	return (hold);
}

t_inter	plane_normal(t_inter hold, t_objs *obj, t_CamRay *ray)
{
	t_inter	inter;

	inter.t = inter_plane(ray, obj);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
		inter.hit = add_vec(ray->origin, mult_vec(ray->dir, inter.t));
		inter.norm = obj->dir;
		if (dot_product(ray->dir, inter.norm) > __DBL_EPSILON__)
			inter.norm = get_normalized(mult_vec(obj->dir, -1));
		hold = inter;
	}
	return (hold);
}

t_inter	cylinder_normal(t_inter hold, t_objs *obj, t_CamRay *ray)
{
	t_inter	inter;
	double	m;
	t_vec	oc;

	inter.t = inter_cylinder(ray, obj);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
		inter.hit = add_vec(ray->origin, mult_vec(ray->dir, inter.t));
		oc = get_normalized(obj->dir);
		m = dot_product(ray->dir, mult_vec(oc, inter.t))
			+ dot_product(sub_vec(ray->origin, obj->cen), oc);
		inter.norm = get_normalized(sub_vec(sub_vec(inter.hit, obj->cen),
					mult_vec(oc, m)));
		hold = inter;
	}
	return (hold);
}
