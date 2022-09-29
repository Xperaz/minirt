/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/28 23:56:01 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera	set_camera(t_scene *sc)
{
	t_camera	cam;

	cam.orig = sc->cam.cen;
	cam.aspect_r = (double) WIDTH / (double) HEIGHT;
	cam.theta = sc->cam.fov * M_PI / 180.0;
	cam.height = tan(cam.theta / 2);
	cam.width = cam.aspect_r * cam.height;
	cam.forward = sc->cam.dir;
	cam.forward.x += EPS;
	cam.up = get_normalized(vect_cross(cam.forward, make_vec(0.0, 1.0, 0.0)));
	cam.right = get_normalized(vect_cross(cam.forward, cam.up));
	return (cam);
}

t_CamRay	ray_primary(t_camera *cam, double v, double u)
{
	t_CamRay	ray;

	ray.origin = cam->orig;
	ray.dir = add_vec(add_vec(mult_vec(cam->up, v * cam->height),
				mult_vec(cam->right, u * cam->width)), cam->forward);
	ray.dir = get_normalized(ray.dir);
	return (ray);
}

t_vec	colorize(double r, double g, double b)
{
	t_vec	color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_vec	ray_at(t_CamRay *ray, double t)
{
	t_vec	target;

	target.x = ray->origin.x + t * ray->dir.x;
	target.y = ray->origin.y + t * ray->dir.y;
	target.z = ray->origin.z + t * ray->dir.z;
	return (target);
}
