/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:21:47 by smia              #+#    #+#             */
/*   Updated: 2022/09/07 13:45:58 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
// #include "camera.h"

t_vec  *ft_vec3_multi_float(t_vec *target, float t, t_vec *v)
{
  target->x = v->x * t;
  target->y = v->y * t;
  target->z = v->z * t;
  return (target);
}

t_vec  *ft_vec3_set_xyz(t_vec *target, float x, float y, float z)
{
	target->x = x;
	target->y = y;
	target->z = z;
	return (target);
}

t_vec *ft_vec3_unit_vec(t_vec *target, t_vec *v)
{
	return (div_vect(*target, module_v(*v)), v);
}

t_CamRay    *ft_ray_set(t_CamRay *target, t_vec origin, t_vec direction)
{
  target->origin = origin;
  target->dir = direction;
  return (target);
}

t_vec   *ft_ray_at(t_vec *target, t_CamRay *ray, float t)
{
  target->x = ray->origin.x + t * ray->dir.x;
  target->y = ray->origin.y + t * ray->dir.y;
  target->z = ray->origin.z + t * ray->dir.z;
  return (target);
}

void  ft_camera_set(t_scene *sc, float aspect_ratio)
{
	sc->cam.viewport_h = 2.0;
  	sc->cam.viewport_w = aspect_ratio * sc->cam.viewport_h;
	sc->cam.focal_len = 1.0;
	ft_vec3_set_xyz(&sc->cam.cen, 0.0, 0.0, 0.0);
	ft_vec3_set_xyz(&sc->cam.horizontal, sc->cam.viewport_w, 0.0, 0.0);
	ft_vec3_set_xyz(&sc->cam.vertical, 0.0, sc->cam.viewport_h, 0.0);
	sc->cam.left_bottom.x = sc->cam.cen.x - (sc->cam.horizontal.x / 2) - (sc->cam.vertical.x / 2) - 0;
	sc->cam.left_bottom.y = sc->cam.cen.y - (sc->cam.horizontal.y / 2) - (sc->cam.vertical.y / 2) - 0;
	sc->cam.left_bottom.z = sc->cam.cen.z - (sc->cam.horizontal.z / 2) - (sc->cam.vertical.z / 2)				   - sc->cam.focal_len;
}

t_CamRay *ft_camera_cal_ray(t_CamRay *target, t_scene *sc, float u, float v)
{
	t_vec cal;

	cal.x = sc->cam.left_bottom.x + u * sc->cam.horizontal.x + v * sc->cam.vertical.x - sc->cam.cen.x;
	cal.y = sc->cam.left_bottom.y + u * sc->cam.horizontal.y + v * sc->cam.vertical.y - sc->cam.cen.y;
	cal.z = sc->cam.left_bottom.z + u * sc->cam.horizontal.z + v * sc->cam.vertical.z - sc->cam.cen.z;
	return (ft_ray_set(target, sc->cam.cen, cal));
}

t_vec	color(double r, double g, double b)
{
	t_vec color;

	color.x = r;
	color.y = g;
	color.z = b;
	return (color);
}

t_vec	ft_ray_color(t_scene *sc, t_CamRay *r, double hit)
{
	double	t;
	
	if (hit > 0)
            return (color(sc->objs->col.x, sc->objs->col.x, sc->objs->col.x));
    else
    {
        t = 0.5 * (r->dir.x+ 1.0);
        return (add_vec(mult_vec(color(sc->objs->col.x, sc->objs->col.x, sc->objs->col.x), 1.0 - hit), mult_vec(color(0.5, 0.7, 1.0), hit)));
   }
}


t_canvas    canvas(int width, int height)
{
	t_canvas    canv;

	canv.height = height;
	canv.width = width;
	canv.aspect_ratio = canv.width / canv.height;
	return (canv);
}

void    ft_render(t_scene *sc)
{
	void		*mlx;
	void		*mlx_win;
	img_data	img;
	double		    v, u;
	t_canvas	    canv;
	t_CamRay	    *ray_ = malloc(sizeof(t_CamRay));
	//t_vec           ray_col;
	unsigned long   color_p;
	
	canv = canvas(WIDTH, WIDTH);
	ft_camera_set(sc, canv.aspect_ratio);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, WIDTH, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, WIDTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	for (int i = canv.height - 1; i >= 0; i--)
	{
		for (int j = 0; j < canv.width; j++)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			ray_ = ft_camera_cal_ray(ray_ , sc, u, v);
			double hit = find_inter(ray_, &sc->objs);
			// ray_col = ft_ray_color(sc, ray_, hit);
			// printf("%f, %f, %f\n", ray_col.x, ray_col.y, ray_col.z);
			color_p = createRGB((int)sc->objs->col.x, (int)sc->objs->col.y, (int)sc->objs->col.z);
			if (hit > 0) //
				my_mlx_pixel_put(&img, j, i, color_p);
			else
				my_mlx_pixel_put(&img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}