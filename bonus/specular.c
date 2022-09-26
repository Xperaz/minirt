/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:22 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/26 14:01:34 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	specular(t_scene *sc, t_inter inter, t_light *light)
{
	t_vec	l;
	t_vec	v;
	t_vec	r;
	double	spec;
	t_vec	hit_light;

	hit_light = sub_vec(light->src, inter.hit);
	l = get_normalized(hit_light);
	v = get_normalized(sub_vec(inter.hit, sc->cam.cen));
	r = sub_vec(mult_vec(inter.norm, 2 * dot_product(inter.norm, l)), l);
	spec = pow(dot_product(r, v), 50) * light->ratio * 0.5;
	return (mult_vec(light->col, spec));
}
