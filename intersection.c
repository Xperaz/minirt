/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/14 21:03:45 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	double	t;
    //double  m;
	double	delta;
	t_CamRay new_ray;
	
	new_ray.origin = ray->origin;
	cy->dir = get_normalized(cy->dir);
	new_ray.dir = vect_cross(ray->dir, cy->dir);
	t_vec	p = sub_vec(ray->origin, cy->cen);
	a = dot_product(new_ray.dir, new_ray.dir);
    b = 2 * dot_product(new_ray.dir, vect_cross(p, cy->dir));
    c = dot_product(vect_cross(p, cy->dir), vect_cross(p, cy->dir)) - pow(cy->p.x / 2, 2);
    delta = pow(b, 2) - 4 * c * a;
	if (delta < 0.0 )
		return (-1.0);
    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
	if (t2 < 0 && t1 < 0)
		return -1.0;
    
    // double m0 = dot_product(ray->dir, cy->dir) * t1 + dot_product(pp, cy->dir);
    // double m1 = dot_product(ray->dir, cy->dir) * t2 + dot_product(pp, cy->dir);

    // if (t1 < t2 && m0 >= 0 && m0 <= cy->p.y)
    //     {
    //         m = m0;
    //         t = t1;
    //     }
    // else 
    //     if (m1 >= 0 && m1 <= cy->p.x)
    //         {
    //              m = m1;
    //              t = t2;
    //         }
    //     else 
    //         return(-1.0);
t = take_min(t1, t2);

double max = sqrt(pow(cy->p.y / 2, 2) + pow(cy->p.x, 2)); //pythagoras theorem
t_vec point = add_vec(ray->origin, mult_vec(ray->dir, t));//ray->origin + ray->dir* t;
t_vec len = sub_vec(point, cy->cen);//point - cylinder.center;
if (get_norm2(len) > max) // if t1 is too high we try with t2
	t = t2;
point = add_vec(ray->origin, mult_vec(ray->dir, t));//ray->origin + ray->dir* t;
len = sub_vec(point, cy->cen);//point - cylinder.center;
if (get_norm2(len) > max) // if t2 is too high too then there is no intersection, else t2 is the intersection. And t2 is in the second half of the cylinder
	return -1.0;
return (t);
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
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
                inter.norm = get_normalized(sub_vec(inter.hit, obj->cen));
                hold = inter;
            }
        }
        if (obj->type == PL)
        {
            inter.t = inter_plane(ray, obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
                inter.norm = get_normalized(sub_vec(inter.hit, obj->cen));
                hold = inter;
            }
        }
        if (obj->type == CY)
        {
            inter.t = inter_cylinder(ray, obj);
            if (((hold.t > inter.t || hold.t == -1)  && inter.t > 0.0000001))
            {
                inter.col = obj->col;
                inter.hit = add_vec(ray->origin, mult_vec(ray->dir,inter.t));
                inter.norm = get_normalized(sub_vec(inter.hit, obj->cen));
                hold = inter;
            }
        }
        obj = obj->next;
    }
    return (hold);
}
