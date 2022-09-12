/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/12 20:07:16 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int sign(double v)
{
	if (v < 0) 
		return -1;
	if (v > 0)
		return 1;
	return 0;
}
double inter_sphere(t_CamRay *ray, t_objs *sp)
{
	double   a;
    double   b;
    double   c;
    double   discr;
    double   dist1;
    double   dist2;
    t_vec   cam_sphere;

    dist1 = 0;
    dist2 = 0;
    cam_sphere = sub_vec(ray->origin,sp->cen);
    a = dot_product(ray->dir,ray->dir); 
    b = 2.0 * dot_product(cam_sphere,ray->dir);
    c = dot_product(cam_sphere, cam_sphere) - (sp->p.x / 2.0) * (sp->p.x / 2.0);
    discr = b * b - (4 * a * c);
    if (discr < 0.0000001)
        return (-1);
    dist1 = (b * (-1.0) - sqrt(discr)) / (2.0 * a);
    dist2 = (b * (-1.0) + sqrt(discr)) / (2.0 * a);
    if (dist1 * dist2 > 0.0000001)
    {
        if (dist1 > 0.0000001)
            return take_min(dist1, dist2);
        return -1;
    }
    if (dist1 > 0.0000001)
        return dist1;
    return dist2;
}

double inter_plane(t_CamRay *ray, t_objs *pl)
{
	t_vec   cam_plane;
	double  dist;
	
	if (fabs(dot_product(pl->dir,ray->dir)) <= 0.000001)
		return -1;
	cam_plane = sub_vec(pl->cen, ray->origin);
	dist = dot_product(pl->dir, cam_plane) / dot_product(pl->dir,ray->dir);
	if (sqrt(dist) >= 0.000001)
		return dist;
	else
		return -1;
}

double inter_cylinder(t_CamRay *ray, t_objs *cy)
{
	double	a;
	double	b;
	double	c;
	double	radius = 4;
	double	height = 8;
	double	t;
	double	delta;
	t_CamRay new_ray;
	
	new_ray.origin = ray->dir;
	cy->dir = get_normalized(cy->dir);
	new_ray.dir = vect_cross(ray->dir, cy->dir);
	t_vec	p = sub_vec(ray->origin, cy->cen);
	a = dot_product(new_ray.dir, new_ray.dir);
    b = 2 * dot_product(new_ray.dir, vect_cross(p, cy->dir));
    c = dot_product(vect_cross(p, cy->dir), vect_cross(p, cy->dir)) - pow(radius / 2, 2);
    delta = pow(b, 2) - 4 * c * a;
    if (fabs(delta) < 0.001)
        return (-1.0);
	if (delta < 0.0 )
		return (-1.0);
    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
	if (t1 > t2)
		t = t1;
	else
		t = t1;
	double r = ray->origin.y + t * ray->dir.y;
	if ((r >= cy->cen.y) && (r <= cy->cen.y + height))
		return (t);
	return (-1.0);
}

t_inter find_inter(t_CamRay *ray, t_scene *sc)
{
	t_inter hold;
	t_inter inter;
	hold.t = -1;
	t_objs  *obj;
	obj = sc->objs;

	while (obj)
	{
		if (obj->type == SP)
		{
			inter.t = inter_sphere(ray,obj);
			inter.col = obj->col;
			if ((hold.t > inter.t && inter.t > 0.000001) || hold.t == -1)
				hold = inter;
		}
		if (obj->type == PL)
		{
			inter.t = inter_plane(ray, obj);
			inter.col = obj->col;
			if ((hold.t > inter.t && inter.t > 0.000001) || hold.t == -1)
				hold = inter;
		}
		if (obj->type == CY)
		{
			inter.t = inter_cylinder(ray, obj);
			inter.col = obj->col;
			if ((hold.t > inter.t && inter.t > 0.000001) || hold.t == -1)
				hold = inter;
		}
		obj = obj->next;
	}
	hold.hit = add_vec(ray->origin, mult_vec(ray->dir,hold.t));
	return (hold);
}
