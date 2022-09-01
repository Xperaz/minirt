/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:35:29 by smia              #+#    #+#             */
/*   Updated: 2022/09/01 19:06:50 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_file(int ac, char **av)
{
	int i;
	int fd;
	
	fd = 0;
	if (ac != 2 )
		return (1);
	if (!av[1])
		return (1);
	i = ft_strlen(av[1]);
	if (i < 4)
		return (1);
	if (av[1][i - 1] == 't' || av[1][i - 2] == 'r' || av[1][i - 3] == '.')
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else
		return (1);
	return (0);
}

void	my_mlx_pixel_put(img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vec	init_vec(t_vec vec, double x, double y, double z)
{
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void    ft_render(t_scene *sc)
{
	void		*mlx;
	void		*mlx_win;
	img_data	img;
	
	double		v, u;
	t_vec		origin;
	t_vec		dir;
	t_canvas	canv;
	t_camera	cam;
	t_CamRay	ray;
	// t_CamRay	ray_;
	// t_vec		_ray;

	(void)sc;
	origin.x = 0.0, origin.y = 0.0, origin.z = 0.0;
	dir.x = 0.0, dir.y = 0.0, dir.z = 1.0;
	canv = canvas(WIDTH, HEIGHT);
	cam = camera(&canv, origin);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	printf("%d %d\n", canv.width, canv.height);
	for (int i = canv.height - 1; i >= 0; i--)
	{
		for (int j = 0; j < canv.width; j++)
		{
			u = (double)i / (canv.width - 1);
			v = (double)j / (canv.height - 1);
			// ray_ = ray(origin, dir);
			// _ray = ray_at(&ray_, u);
			ray = ray_primary(&cam, u, v);
			printf("%f, %f, %f\n", ray.dir.x, ray.dir.y, ray.dir.z);
			//color_p = ray_color(&ray);
			my_mlx_pixel_put(&img, j, i, 0x00FF0000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

int main (int ac, char **av)
{
	t_scene *sc;
	int     fd;

	if (check_file(ac, av))
		ft_err("wrong args : Please try enter filename.rt");
	fd = open(av[1], O_RDONLY);
	sc = alloc_scence();
	if (!sc)
		ft_err("allocation");
	parse(sc,fd);
	ft_render(sc);
	while (sc->objs)
	{
		printf("%d \n" , sc->objs->type);
		sc->objs = sc->objs->next;
	}
	ft_collect(&root,root);
	return 0;
}