/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:12:11 by smia              #+#    #+#             */
/*   Updated: 2022/09/26 13:56:27 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	calcul_color(t_scene *sc, t_inter inter, t_vec amb)
{
	t_light	*light;
	t_vec	ret;
	t_vec	black;

	black = make_vec(0, 0, 0);
	ret = black;
	light = sc->light;
	while (light)
	{
		if (dark(sc, light))
			ret = add_color(ret, black);
		else
		{
			if (shade(sc, inter, light))
				ret = add_color(ret, amb);
			else
			{
				ret = add_color(ret, amb);
				ret = add_color(ret, diffuse(inter, light));
				ret = add_color(ret, specular(sc, inter, light));
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
