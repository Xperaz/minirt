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

t_vec	diffuse(t_inter inter, t_light *light)
{
	t_vec		hit_light;
	double		d;
	t_vec		diff;

	hit_light = sub_vec(light->src, inter.hit);
	d = dot_product(get_normalized(hit_light), inter.norm);
	diff = add_coef(inter.col, light->col, fabs(d) * light->ratio);
	return (diff);
}

int	dark(t_scene *sc, t_light *light)
{
	t_inter		k;
	t_CamRay	ray;
	t_vec		cam_light;
	t_vec		obstacl;

	cam_light = sub_vec(light->src, sc->cam.cen);
	ray.origin = sc->cam.cen;
	ray.dir = get_normalized(cam_light);
	k = find_inter(&ray, sc);
	obstacl = sub_vec(sc->cam.cen, k.hit);
	if (k.t > EPS && (module_v(cam_light) > module_v(obstacl)))
		return (1);
	return (0);
}
