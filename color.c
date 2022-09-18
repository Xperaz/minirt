/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:12:11 by smia              #+#    #+#             */
/*   Updated: 2022/09/17 20:17:28 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec calcul_color(t_scene *sc, t_inter inter, t_vec  amb)
{
	t_light *l;
	t_vec 	col;
	col = make_vec(0,0,0);
	t_vec	ret = amb;
	t_vec	hit_light;
	double d;
	l = sc->light;
	while (l)
	{
		hit_light = sub_vec(l->src, inter.hit);
		
		t_CamRay sh_ray;
		sh_ray.origin = inter.hit;
		sh_ray.dir = get_normalized(hit_light);
		t_inter shadow = find_inter(&sh_ray,sc);
		t_vec hit_sh = sub_vec(shadow.hit,sh_ray.origin);
		if (shadow.t > 0.0000001 && (module_v(hit_light) > module_v(hit_sh)))
			ret = add_color(ret, col);
		else
		{
			d = dot_product(get_normalized(hit_light), inter.norm);
			ret = add_color(ret,add_coef(inter.col, l->col , fabs(d) * l->ratio));
			// R = (2*N.L)*N - L.
			t_vec L = get_normalized(hit_light);
			t_vec V = get_normalized(sub_vec(inter.hit, sc->cam.cen));
			t_vec R = sub_vec(mult_vec(inter.norm, 2 * dot_product(inter.norm, L)), L);
			double spec = pow(dot_product(R,V),50) * l->ratio * 0.5;
			ret = add_color(ret, mult_vec(l->col, spec));
		}
		l = l->next;
	}
	return ret;
}

t_vec    add_coef(t_vec col1, t_vec col2, double ratio)
{
    t_vec    ret;

    ret.x = col1.x * (col2.x / 255) * ratio;
    ret.y = col1.y * (col2.y / 255) * ratio;
    ret.z = col1.z * (col2.z / 255) * ratio;
    return (ret);
}

t_vec   add_color(t_vec col1, t_vec col2)
{
    t_vec res;

    res = add_vec(col1, col2);
    if (res.x > 255)
        res.x = 255;
    if (res.y > 255)
        res.y = 255;
    if (res.z > 255)
        res.z = 255;
    return res;
}

t_vec	ray_color(t_CamRay *ray, t_scene *sc)
{
	t_inter	inter;
	t_vec   px_col;

	inter = find_inter(ray, sc);
	if (inter.t > 0.0000001)
	{
		t_vec amb = add_coef(inter.col, sc->amb.col,sc->amb.ratio);
		px_col = calcul_color(sc, inter, amb);
		return (px_col);
	}
	return (mult_vec(sc->amb.col,sc->amb.ratio));
}