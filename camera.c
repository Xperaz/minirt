/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/14 18:18:12 by smia             ###   ########.fr       */
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
	cam.forward.x += 0.0000001;
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


t_vec	colorize(double r, double g, double b)
{
	t_vec color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}
t_vec	ray_at(t_CamRay *ray, double t)
{
	t_vec target;
	target.x = ray->origin.x + t * ray->dir.x;
	target.y = ray->origin.y + t * ray->dir.y;
	target.z = ray->origin.z + t * ray->dir.z;
	return (target);
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
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int j = HEIGHT - 1 ; j >= 0; j--)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			v = (double)i * 2 / WIDTH - 1;
			u = (double)j * 2 / HEIGHT - 1;
			ray_ = ray_primary(&cam, v, u);
			ray_col = ray_color(&ray_, sc);
			my_mlx_pixel_put(&img, i, HEIGHT - 1 - j, createRGB(ray_col.x, ray_col.y, ray_col.z));
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_loop(vars.mlx);
}