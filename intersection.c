/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:00:32 by smia              #+#    #+#             */
/*   Updated: 2022/09/10 12:27:00 by aouhadou         ###   ########.fr       */
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
    b = 2 * dot_product(cam_sphere,ray->dir);
    c = dot_product(cam_sphere, cam_sphere) - (sp->p.x / 2) * (sp->p.x / 2);
    discr = b * b - (4 * a * c);
    if (discr < 0)
        return (-1);
    dist1 = (b * (-1) - sqrt(discr)) / (2 * a);
    dist2 = (b * (-1) + sqrt(discr)) / (2 * a);
    if (dist1 * dist2 >= 0)
    {
        if (dist1 >= 0)
            return take_min(dist1, dist2);
        return -1;
    }
    if (dist1 >= 0)
        return dist1;
    return dist2;
}

double inter_plane(t_CamRay *ray, t_objs *pl)
{
    t_vec   cam_plane;
    double  dist;
    
    if (fabs(dot_product(pl->dir,ray->dir)) <= 0.0001)
        return -1;
    cam_plane = sub_vec(pl->cen, ray->origin);
    dist = dot_product(pl->dir, cam_plane) / dot_product(pl->dir,ray->dir);
    if (dist >= 0)
        return dist;
    else
        return -1;
}

double inter_cylinder(t_CamRay *ray, t_objs *cy)
{
    t_vec		f;
	t_vec	    cam_cy;
	t_vec		abc;
	double		discr;
    double      dist1;
    double      dist2;

	cam_cy = sub_vec(ray->origin, cy->cen);
	f = sub_vec(ray->dir, mult_vec(cy->dir,dot_product(ray->dir, cy->dir)));
	cam_cy = sub_vec(cam_cy, mult_vec(cy->dir,dot_product(cam_cy, cy->dir)));
	abc.x = get_norm2(f);
	abc.y = 2 * dot_product(f, cam_cy);
	abc.z = get_norm2(cam_cy) - (cy->p.x * cy->p.x );
	discr = abc.y * abc.y - 4 * abc.x * abc.z;
    if (discr < 0)
        return -1;
    dist1 = (abc.y * (-1) - sqrt(discr)) / (2 * abc.x);
    dist2 = (abc.y * (-1) + sqrt(discr)) / (2 * abc.x);
    if (dist1 * dist2 >= 0)
    {
        if (dist1 >= 0)
            return take_min(dist1, dist2);
        return -1;
    }
    if (dist1 >= 0)
        return dist1;
    return dist2;  
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
            if ((hold.t > inter.t && inter.t > 0) || hold.t == -1)
                hold = inter;
        }
        if (obj->type == PL)
        {
            inter.t = inter_plane(ray, obj);
            inter.col = obj->col;
            if ((hold.t > inter.t && inter.t > 0) || hold.t == -1)
                hold = inter;
        }
        if (obj->type == CY)
        {
            inter.t = inter_cylinder(ray, obj);
            inter.col = obj->col;
            if ((hold.t > inter.t && inter.t > 0) || hold.t == -1)
                hold = inter;
        }
        obj = obj->next;
    }
    hold.hit = add_vec(ray->origin, mult_vec(ray->dir,hold.t));
    return (hold);
}
