/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:42:52 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/26 13:57:51 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	pick_cone_inter(t_objs *co, t_CamRay *ray, t_cone_info inf)
{
	if (inf.delta < 0)
		return (-1.0);
	inf.t1 = (-inf.b + sqrt(inf.delta)) / (2 * inf.a);
	inf.t2 = (-inf.b - sqrt(inf.delta)) / (2 * inf.a);
	if (inf.t1 < EPS)
		return (-1.0);
	if (inf.t1 > inf.t2)
		inf.t = inf.t2;
	else if (inf.t1 < inf.t2)
		inf.t = inf.t1;
	inf.y0 = dot_product(ray->dir, inf.v) * inf.t2
		+ dot_product(inf.x, inf.v);
	inf.y1 = dot_product(ray->dir, inf.v) * inf.t1
		+ dot_product(inf.x, inf.v);
	if (inf.y0 >= EPS && inf.y0 <= co->p.y)
		return (inf.t2);
	if (inf.y1 >= EPS && inf.y1 <= co->p.y)
		return (inf.t1);
	return (-1.0);
}

double	inter_cone(t_CamRay *ray, t_objs *co)
{
	t_cone_info	inf;
	double		t;

	inf.k = tan((co->p.z / 2) * M_PI / 180.0);
	inf.v = get_normalized(co->dir);
	inf.x = sub_vec(ray->origin, co->cen);
	inf.a = dot_product(ray->dir, ray->dir) - (1 + pow(inf.k, 2.0))
		* dot_product(ray->dir, inf.v) * dot_product(ray->dir, inf.v);
	inf.b = 2.0 * (dot_product(ray->dir, inf.x) - (1 + pow(inf.k, 2.0))
			* dot_product(ray->dir, inf.v) * dot_product(inf.x, inf.v));
	inf.c = dot_product(inf.x, inf.x) - (1 + pow(inf.k, 2.0))
		* dot_product(inf.x, inf.v) * dot_product(inf.x, inf.v);
	inf.delta = inf.b * inf.b - (4 * inf.a * inf.c);
	t = pick_cone_inter(co, ray, inf);
	return (t);
}
