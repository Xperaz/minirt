/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:28:21 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 14:07:29 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double  inter_cone(t_CamRay *ray, t_objs *co)
{
	double	k;
	double	a;
	double	b;
	double	c;
	double	delta;
	double	t = 0.0;
	double	t1;
	double	t2;
	double	y0;
	double	y1;
	t_vec	x;
	t_vec	v;
	
	k = (co->p.y / co->p.x) * (co->p.y / co->p.x);
	v = get_normalized(co->dir);
	x = sub_vec(ray->origin, co->cen);

	a = (pow(dot_product(ray->dir, v), 2.0)) - pow(cos(k), 2.0);
	b = 2 * ((dot_product(ray->dir, v) * dot_product(x, v)) - (dot_product(ray->dir, mult_vec(x, pow(cos(k), 2.0)))));
	c = (pow(dot_product(x, v), 2.0)) - (dot_product(x, mult_vec(x, pow(cos(k), 2.0))));
	
	delta = b * b - (4 * a * c);
	if (delta < EPS)
		return (-1.0);
	t1 = (-b + sqrt(delta)) / (2 * a);
	t2 = (-b - sqrt(delta)) / (2 * a);
	if (t1 < EPS)
		return (-1.0);
	if (t1 > t2)
		t = t2;
	else if (t1 < t2)
		t = t1;
	y0 = dot_product(ray->dir, v) * t2
		+ dot_product(x, v);
	y1 = dot_product(ray->dir, v) * t1
		+ dot_product(x, v);
	if (y0 >= EPS && y0 <= co->p.y)
		return (t2);
	if (y1 >= EPS && y1 <= co->p.y)
		return (t1);
	return (t);
}

t_inter	cone_normal(t_inter hold, t_objs *obj, t_CamRay *ray)
{
	t_inter	inter;
	double	k;
	double	m;
	t_vec	v;
	
	k = (obj->p.y / obj->p.x) * (obj->p.y / obj->p.x);
	inter.t = inter_cone(ray, obj);
	v = get_normalized(obj->dir);
	m = (dot_product(ray->dir, v) * inter.t) + dot_product(sub_vec(ray->origin, obj->cen), v);
	if (((hold.t > inter.t || hold.t == -1) && inter.t > EPS))
	{
		inter.col = obj->col;
        inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
		t_vec	d1 = sub_vec(inter.hit, obj->cen);
		t_vec	d2 = mult_vec(v, ((1 + k * k) * m));
		inter.norm = get_normalized(sub_vec(d1, d2));
		hold = inter;
	}
	return (hold);
}

t_inter	find_inter(t_CamRay *ray, t_scene *sc)
{
	t_inter	hold;
	t_objs	*obj;

	hold.t = -1.0;
	obj = sc->objs;
	while (obj)
	{
		if (obj->type == SP)
			hold = spher_normal(hold, obj, ray);
		if (obj->type == PL)
			hold = plane_normal(hold, obj, ray);
		if (obj->type == CY)
			hold = cylinder_normal(hold, obj, ray);
		if (obj->type == CO)
			hold = cone_normal(hold, obj, ray);
		obj = obj->next;
	}
	return (hold);
}
