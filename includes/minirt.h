/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:01:02 by smia              #+#    #+#             */
/*   Updated: 2022/09/26 14:16:17 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1200
# define HEIGHT 1200
# define EPS 0.000001
# define CY 1
# define PL 2
# define SP 3
# define CO 4 
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "structs.h"

// parse
void		ft_err(char *err);
int			check_file(int ac, char **av);
void		parse(t_scene *sc, int fd);
void		parse_line(char *id, char **tockens, t_scene *sc);
void		parse_plane(t_scene *sc, char **tockens);
void		parse_cylinder(t_scene *sc, char **tockens);
void		parse_sphere(t_scene *sc, char **tockens);
void		parse_light(t_scene *sc, char **tockens);
void		parse_camera(t_scene *sc, char **tockens);
void		parse_ambient(t_scene *sc, char **tockens);
void		parse_cone(t_scene *sc, char **tockens);
void		parse_triangle(t_scene *sc, char **tockens);

// allocation
t_scene		*alloc_scence(void);
t_objs		*alloc_obj(t_scene *sc);
void		ft_collect(t_collector **g_root, t_collector *node);
void		*ft_malloc(t_collector **g_root, size_t size);
t_collector	*g_root;

// tools
int			ft_strlen(const char *str);
char		*gnl(int fd);
double		ft_atod(const char *str);
int			ft_atoi(const char *str);
char		**ft_split(const char *str, char c);
void		free_split(char **s);

//vectors
void		null_vec(t_vec *v);
t_vec		get_vec(char *s);
t_vec		get_color(char *s);
t_vec		get_normalized(t_vec v);
void		normalize(t_vec *v);
double		get_norm2(t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec		add_vec(t_vec u, t_vec v);
t_vec		mult_vec(t_vec v, double a);
t_vec		vect_cross(t_vec u, t_vec v);
double		dot_product(t_vec u, t_vec v);
double		module_v(t_vec	v);
t_vec		div_vect(t_vec v, double a);
t_vec		make_vec(double x, double y, double z);

/*rendring */
void		ft_render(t_scene *sc);

/* camera */
t_camera	set_camera(t_scene *sc);
t_CamRay	ray_primary(t_camera *cam, double v, double u);
t_vec		ray_at(t_CamRay *ray, double t);
t_vec		ray_at(t_CamRay *ray, double t);

/* intersections*/
double		take_min(double x, double y);
t_inter		find_inter(t_CamRay *ray, t_scene *sc);
double		inter_sphere(t_CamRay *ray, t_objs *sp);
double		inter_plane(t_CamRay *ray, t_objs *pl);
double		inter_cylinder(t_CamRay *ray, t_objs *cy);

/* bonus */
double		pick_cone_inter(t_objs *co, t_CamRay *ray, t_cone_info inf);
double		inter_cone(t_CamRay *ray, t_objs *co);
t_inter		cone_normal(t_inter hold, t_objs *obj, t_CamRay *ray);
t_vec		specular(t_scene *sc, t_inter inter, t_light *light);

/* mlx funct */
int			red_button(t_vars *vars);
int			handle_key(int key, t_vars *vars);
void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

// color
t_vec		add_coef(t_vec col1, t_vec col2, double ratio);
int			create_rgb(int r, int g, int b);
t_vec		add_color(t_vec col1, t_vec col2);
t_vec		ray_color(t_CamRay *ray, t_scene *sc);
t_vec		colorize(double r, double g, double b);
t_vec		diffuse(t_inter inter, t_light *light, double d);
int			shade(t_scene *sc, t_inter inter, t_light *light);
int			dark(t_scene *sc, t_light *light);

//surface normal
int			is_inside(t_vec ray, t_vec norm);
t_inter		spher_normal(t_inter hold, t_objs *obj, t_CamRay *ray);
t_inter		plane_normal(t_inter hold, t_objs *obj, t_CamRay *ray);
t_inter		cylinder_normal(t_inter hold, t_objs *obj, t_CamRay *ray);

#endif