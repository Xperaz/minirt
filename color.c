/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 19:12:11 by smia              #+#    #+#             */
/*   Updated: 2022/09/10 23:10:05 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	t_vec	hit_light;
	t_vec	normal_vec;
	double	d = 0;
	t_vec   px_col;
	inter = find_inter(ray, sc);
	if (inter.t > 0.000001)
	{
		// hit_point = ray_at(ray, t);
		normal_vec  = get_normalized(sub_vec(inter.hit,sc->objs->cen));
		hit_light = get_normalized(sub_vec(sc->light.src, inter.hit));
		d = dot_product(hit_light, normal_vec);
		if (d > 1.000001)
			d = 1;
		px_col = add_coef(inter.col, sc->amb.col, sc->amb.ratio); // this function try to merge 2 col with consideration of ratio
		t_CamRay sh_ray;
		sh_ray.origin = inter.hit;
		sh_ray.dir = get_normalized(sub_vec(sc->light.src,inter.hit));
		t_inter shadow = find_inter(&sh_ray,sc); // to know if our inter.hit is shading i send a ray from intersection to light.src and see if there is any intersection with any obejct 
		if (module_v(sub_vec(shadow.hit,sh_ray.origin)) > 0.000001 && module_v(sub_vec(sc->light.src,sh_ray.origin)) > module_v(sub_vec(shadow.hit,sh_ray.origin)))
			return (px_col);
		px_col = add_color(px_col,add_coef(px_col, sc->light.col, fabs(d) * sc->light.ratio));
		return (px_col);
	}
	return (mult_vec(sc->amb.col,sc->amb.ratio));
}