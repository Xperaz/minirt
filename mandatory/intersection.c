/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/26 14:11:51 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	inter_sphere(t_CamRay *ray, t_objs *sp)
{
	t_sphere	sph;

	sph.oc = sub_vec(ray->origin, sp->cen);
	sph.a = dot_product(ray->dir, ray->dir);
	sph.b = 2.0 * dot_product(sph.oc, ray->dir);
	sph.c = dot_product(sph.oc, sph.oc) - (sp->p.x / 2.0) * (sp->p.x / 2.0);
	sph.t = sph.b * sph.b - (4 * sph.a * sph.c);
	if (sph.t < EPS)
		return (-1);
	sph.t1 = (sph.b * (-1.0) - sqrt(sph.t)) / (2.0 * sph.a);
	sph.t2 = (sph.b * (-1.0) + sqrt(sph.t)) / (2.0 * sph.a);
	if (sph.t1 * sph.t2 > EPS)
	{
		if (sph.t1 > EPS)
			return (take_min(sph.t1, sph.t2));
		return (-1);
	}
	if (sph.t1 > EPS)
		return (sph.t1);
	return (sph.t2);
}

double	inter_plane(t_CamRay *ray, t_objs *pl)
{
	t_vec	x;
	t_vec	normal;
	double	t;
	double	b;
	double	a;

	normal = get_normalized(pl->dir);
	x = sub_vec(ray->origin, pl->cen);
	b = dot_product(ray->dir, normal);
	if (b != 0)
	{
		a = dot_product(x, normal);
		t = -a / b;
		if (t < EPS)
			return (-1.0);
		return (t);
	}
	return (-1.0);
}

double	pick_cy_inter(t_cylinder inf, t_CamRay *ray, t_objs *cy)
{
	inf.t1 = (-inf.b + sqrt(inf.delta)) / (2 * inf.a);
	inf.t2 = (-inf.b - sqrt(inf.delta)) / (2 * inf.a);
	if (inf.t1 < EPS)
		return (-1.0);
	if (inf.t1 > inf.t2)
		inf.t = inf.t2;
	else
		inf.t = inf.t1;
	inf.y0 = dot_product(ray->dir, inf.normal) * inf.t2
		+ dot_product(inf.oc, inf.normal);
	inf.y1 = dot_product(ray->dir, inf.normal) * inf.t1
		+ dot_product(inf.oc, inf.normal);
	if (inf.y0 >= EPS && inf.y0 <= cy->p.y)
		return (inf.t2);
	if (inf.y1 >= EPS && inf.y1 <= cy->p.y)
		return (inf.t1);
	return (-1.0);
}

double	inter_cylinder(t_CamRay *r, t_objs *cy)
{
	t_cylinder	inf;
	double		t;

	inf.normal = get_normalized(cy->dir);
	inf.oc = sub_vec(r->origin, cy->cen);
	inf.a = dot_product(r->dir, r->dir) - (dot_product(r->dir, inf.normal)
			* dot_product(r->dir, inf.normal));
	inf.b = 2 * (dot_product(r->dir, inf.oc) - (dot_product(r->dir, inf.normal)
				* dot_product(inf.oc, inf.normal)));
	inf.c = dot_product(inf.oc, inf.oc)
		- (dot_product(inf.oc, inf.normal) * dot_product(inf.oc, inf.normal))
		- (cy->p.x / 2) * (cy->p.x / 2);
	inf.delta = inf.b * inf.b - 4 * inf.a * inf.c;
	if (inf.delta < EPS)
		return (-1.0);
	t = pick_cy_inter(inf, r, cy);
	return (t);
}
