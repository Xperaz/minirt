/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:00:53 by smia              #+#    #+#             */
/*   Updated: 2022/09/23 13:32:53 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			my_mlx_pixel_put(&img, i, HEIGHT - 1 - j, create_rgb(ray_col.x, ray_col.y, ray_col.z));
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, handle_key, &vars);
	mlx_loop(vars.mlx);
}