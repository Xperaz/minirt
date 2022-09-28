/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:51:35 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/26 14:00:01 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_inside(t_vec ray, t_vec norm)
{
	if (dot_product(ray, norm) > 0)
		return (1);
	return (0);
}

int	shade(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec		hit_light;
	t_CamRay	sh_ray;
	t_inter		shadow;
	t_vec		hit_sh;

	hit_light = sub_vec(light->src, inter.hit);
	sh_ray.origin = inter.hit;
	sh_ray.dir = get_normalized(hit_light);
	shadow = find_inter(&sh_ray, sc);
	hit_sh = sub_vec(shadow.hit, sh_ray.origin);
	if (shadow.t > EPS && (module_v(hit_light) > module_v(hit_sh)))
		return (1);
	return (0);
}

t_vec	diffuse(t_inter inter, t_light *light, double d)
{
	t_vec	diff;

	diff = add_coef(inter.col, light->col, d * light->ratio);
	return (diff);
}
