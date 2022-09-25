/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:12:11 by smia              #+#    #+#             */
/*   Updated: 2022/09/25 13:03:40 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return 1;
	return 0;
}

t_vec	specular(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec 	L;
	t_vec 	V;
	t_vec	R;
	double	spec;
	t_vec	hit_light;

	hit_light = sub_vec(light->src, inter.hit);
	L = get_normalized(hit_light);		
	V = get_normalized(sub_vec(inter.hit, sc->cam.cen));
	R = sub_vec(mult_vec(inter.norm, 2 * dot_product(inter.norm, L)), L);
	spec = pow(dot_product(R,V),50) * light->ratio * 0.5;
	return (mult_vec(light->col, spec));
}

t_vec	diffuse(t_inter inter, t_light * light)
{
	t_vec		hit_light;
	double		d;
	t_vec		diff;

	hit_light = sub_vec(light->src, inter.hit);
	d = dot_product(get_normalized(hit_light), inter.norm);
	diff = add_coef(inter.col, light->col ,  fabs(d) * light->ratio);
	return (diff);
}

int dark(t_scene *sc, t_light *light)
{
	t_inter 	k;
	t_CamRay	ray;
	t_vec		cam_light;
	t_vec		obstacl;

	cam_light = sub_vec(light->src, sc->cam.cen);
	ray.origin = sc->cam.cen;
	ray.dir = get_normalized(cam_light);
	k = find_inter(&ray, sc);
	obstacl = sub_vec(sc->cam.cen, k.hit);
	if (k.t > EPS && (module_v(cam_light) > module_v(obstacl)))
		return 1;
	return 0;
}

t_vec	calcul_color(t_scene *sc, t_inter inter, t_vec  amb)
{
	t_light	*light;
	t_vec	ret;
	t_vec	black;

	black = make_vec(0,0,0);
	ret = black;
	light = sc->light;
	while (light)
	{
		if (dark(sc, light)) // see if there is an obstacl between camera dir and light source
			ret = add_color(ret, black);
		else 
		{
			if (shade(sc, inter, light))
				ret = add_color(ret, amb);
			else
			{
				ret = add_color(ret, amb);
				ret = add_color(ret,diffuse(inter, light));
				ret = add_color(ret,specular(sc, inter, light));
			}
		}
		light = light->next;
	}
	return (ret);
}

t_vec	add_coef(t_vec col1, t_vec col2, double ratio)
{
	t_vec	ret;

	ret.x = col1.x * (col2.x / 255) * ratio;
	ret.y = col1.y * (col2.y / 255) * ratio;
	ret.z = col1.z * (col2.z / 255) * ratio;
	return (ret);
}

t_vec	add_color(t_vec col1, t_vec col2)
{
	t_vec	res;

	res = add_vec(col1, col2);
	if (res.x > 255)
		res.x = 255;
	if (res.y > 255)
		res.y = 255;
	if (res.z > 255)
		res.z = 255;
	return (res);
}

t_vec	ray_color(t_CamRay *ray, t_scene *sc)
{
	t_inter	inter;
	t_vec	px_col;
	t_vec	amb;

	inter = find_inter(ray, sc);
	if (inter.t > EPS)
	{
		amb = add_coef(inter.col, sc->amb.col, sc->amb.ratio);
		px_col = calcul_color(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb.col, sc->amb.ratio));
}
