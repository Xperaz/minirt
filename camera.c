/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/10 11:49:02 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// #include "camera.h"

int	handle_key(int key, t_vars *vars)
{
	if (key == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

t_camera    set_camera(t_scene *sc)
{
    t_camera cam;

    cam.aspect_r = (double) WIDTH / (double) HEIGHT;
    
    cam.theta = sc->cam.fov * M_PI / 180.0;
    cam.height = tan(cam.theta / 2);
    cam.width = cam.aspect_r * cam.height;
    cam.forward = sc->cam.dir;
    cam.up = get_normalized(vect_cross(cam.forward, make_vec(0.0,1.0,0.0)));
    cam.right = get_normalized(vect_cross(cam.forward, cam.up));
    return (cam);
}

t_CamRay       ray_primary(t_camera *cam, double v, double u)
{
    t_CamRay   ray;
    
    ray.origin = cam->orig;

    ray.dir = add_vec(add_vec(mult_vec(cam->up, v * cam->height), mult_vec(cam->right, u * cam->width)),cam->forward);
    ray.dir = get_normalized(ray.dir);
    return (ray);
}

// double	hit_sphere(t_CamRay	*r, t_scene	*sc, double radius)
// {
// 	t_vec	oc;
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	disc;

// 	oc = sub_vec(r->origin, sc->objs->cen);
// 	a = dot_product(r->dir, r->dir);
// 	b = 2.0 * dot_product(oc, r->dir);
// 	c = dot_product(oc, oc) - radius;
// 	disc = (b * b) - (4 * a * c);
// 	if (disc < 0)
// 		return (-1.0);
// 	return ((-b - sqrt(disc)) / (2 * a));
// }

t_vec	colorize(double r, double g, double b)
{
	t_vec color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}
t_vec	ray_at(t_CamRay *ray, float t)
{
	t_vec target;
	target.x = ray->origin.x + t * ray->dir.x;
	target.y = ray->origin.y + t * ray->dir.y;
	target.z = ray->origin.z + t * ray->dir.z;
	return (target);
}

t_vec	ray_color(t_CamRay *ray, t_scene *sc)
{
	t_inter	inter;
	t_vec	hit_light;
	t_vec	normal_vec;
	t_vec	n;
	double	d;
	t_vec   px_col;
	t_vec	dark;
	dark = make_vec(0,0,0);
	inter = find_inter(ray, sc);
	if (inter.t > 0.0)
	{
		// hit_point = ray_at(ray, t);
		normal_vec  = sub_vec(inter.hit, sc->objs->cen);
		n = get_normalized(normal_vec);
		hit_light = sub_vec(sc->light.src, inter.hit);
		d = dot_product(hit_light, normal_vec);
		if (d < 0)
			d = 0;
		if (d > 1)
			d = 1;
		px_col = add_coef(inter.col, sc->amb.col, sc->amb.ratio); // this function try to merge 2 col with consideration of ratio
		t_CamRay sh_ray;
		sh_ray.origin = inter.hit;
		sh_ray.dir = sub_vec(sc->light.src,inter.hit);
		t_inter shadow = find_inter(&sh_ray,sc); // to know if our inter.hit is shading i send a ray from intersection to light.src and see if there is any intersection with any obejct 
		if (module_v(sub_vec(sc->light.src,inter.hit)) < module_v(sub_vec(shadow.hit,sh_ray.origin)))
			return (add_coef(dark, px_col, sc->amb.ratio));
		px_col = add_coef(px_col, sc->light.col, d * sc->light.ratio);
		return (px_col);
	}
	return (mult_vec(sc->amb.col, sc->amb.ratio));
}

void    ft_render(t_scene *sc)
{
	t_vars		vars;
	img_data	img;
	
	double		v, u;
	t_camera	cam;
	t_CamRay	ray_;
	t_vec		ray_col;

	cam = set_camera(sc);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = 0 ; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			v = (double)i * 2 / HEIGHT - 1;
			u = (double)j * 2 / WIDTH - 1;
			ray_ = ray_primary(&cam, v, u);
			ray_col = ray_color(&ray_, sc);
			my_mlx_pixel_put(&img, j, i, createRGB(ray_col.x, ray_col.y, ray_col.z));
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_loop(vars.mlx);
}