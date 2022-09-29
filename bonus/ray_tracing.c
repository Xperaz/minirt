/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:00:53 by smia              #+#    #+#             */
/*   Updated: 2022/09/28 23:49:45 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_draw(t_render info, t_scene *sc)
{
	info.y = HEIGHT - 1;
	while (info.y >= 0)
	{
		info.x = 0;
		while (info.x < WIDTH)
		{
			info.v = (double)info.x * 2 / WIDTH - 1;
			info.u = (double)info.y * 2 / HEIGHT - 1;
			info.ray_ = ray_primary(&info.cam, info.v, info.u);
			info.ray_col = ray_color(&info.ray_, sc);
			my_mlx_pixel_put(&info.img, info.x, HEIGHT - 1 - info.y,
				create_rgb(info.ray_col.x, info.ray_col.y, info.ray_col.z));
			info.x++;
		}
		info.y--;
	}
}

void	image_init(t_render	*info)
{
	info->vars.mlx = mlx_init();
	info->vars.win = mlx_new_window(info->vars.mlx, WIDTH, HEIGHT, "MiniRT");
	info->img.img = mlx_new_image(info->vars.mlx, WIDTH, HEIGHT);
	info->img.addr = mlx_get_data_addr(info->img.img, &info->img.bits_per_pixel,
			&info->img.line_length, &info->img.endian);
}

void	ft_render(t_scene *sc)
{
	t_render	info;

	info.cam = set_camera(sc);
	image_init(&info);
	ft_draw(info, sc);
	mlx_put_image_to_window(info.vars.mlx, info.vars.win, info.img.img, 0, 0);
	mlx_key_hook(info.vars.win, handle_key, &info.vars);
	mlx_hook(info.vars.win, 17, 0, red_button, &info.vars);
	mlx_loop(info.vars.mlx);
}
