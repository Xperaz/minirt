/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 03:35:29 by smia              #+#    #+#             */
/*   Updated: 2022/09/02 13:04:01 by aouhadou         ###   ########.fr       */
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

t_vec	init_vec( double x, double y, double z)
{
	t_vec vec;
	
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

int     hit_sphere(t_sphere *sp, t_CamRay *ray)
    {
        t_vec  oc; 
        double  a;
        double  b;
        double  c;
        double  discriminant;

        oc = sub_vec(ray->origin, sp->center);
        a = dot_product(ray->dir, ray->dir);
        b = 2.0 * dot_product(oc, ray->dir);
        c = dot_product(oc, oc) - sp->radius2;
        discriminant = b * b - 4 * a * c;
        return (discriminant > 0);
    }
	
t_sphere    sphere(t_vec center, double radius)
{
        t_sphere sp;

        sp.center = center;
        sp.radius = radius;
        sp.radius2 = radius * radius;
        return (sp);
    }

void    ft_render(t_scene *sc)
{
	void		*mlx;
	void		*mlx_win;
	img_data	img;
	
	double		v, u;
	//t_vec		dir;
	t_canvas	canv;
	t_camera	cam;
	//t_CamRay	ray;
	t_CamRay	ray_;
	//t_vec		_ray;
	t_sphere	sp;

	(void)sc;
	canv = canvas(WIDTH, HEIGHT);
	cam = camera(&canv, init_vec(0, 1, 0));

	sp = sphere(init_vec(0, 0, -5), 2);

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
			//ray_ = ray(make_vec(0.0, 0.0, 0.0), dir);
			ray_ = ray_primary(&cam, u, v);
			//_ray = ray_color(&ray_);
			printf("%f, %f, %f\n", ray_.dir.x, ray_.dir.y, ray_.dir.z);
			//color_p = ray_color(&ray);
			if (hit_sphere(&sp, &ray_))
				my_mlx_pixel_put(&img, j, i, 0x00FF0000);
			else
				my_mlx_pixel_put(&img, j, i, 0x00000000);
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