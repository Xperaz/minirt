/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 13:01:02 by smia              #+#    #+#             */
/*   Updated: 2022/09/02 11:07:34 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 700
# define HEIGHT 500
# define CY 1
# define PL 2
# define SP 3
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
//# include "camera/camera.h"

/* img info struct */

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				img_data;

typedef struct  s_vec
{
	double  x;
	double  y;
	double  z;
}               t_vec;

typedef struct  t_cam
{
	t_vec   cen;
	t_vec   dir;
	double  fov;
	int     count;
}               t_cam;

typedef struct  s_light
{
	t_vec   src;
	double  ratio;
	int     count;
}               t_light;

typedef struct s_amb
{
	t_vec   col;
	double  ratio;
	int     count;
}   t_amb;

typedef struct  s_objs
{
	int             type;
	t_vec           cen;
	t_vec           dir;
	t_vec           p;
	t_vec           col;
	t_vec           norm;
	struct s_objs   *next;
}               t_objs;

typedef struct s_scene
{
	t_vec       col;
	t_cam       cam;
	t_light     light;
	t_amb       amb;
	t_objs      *objs;
}               t_scene;

typedef struct collector
{
	void				*adr;
	struct collector	*next;
}	t_collector;


/* camera */

typedef	struct Camera_Setup
{
	t_vec		orig;  // Camera origin (position)
    double		viewport_h; // viewport length
    double		viewport_w; // viewport width
    t_vec		horizontal; // horizontal length vector
    t_vec		vertical; // vertical length vector
    double		focal_len; // focal length
    t_vec		left_bottom; // lower left corner
	
}	t_camera;

typedef struct CamRay
{
	t_vec	origin;
	t_vec	dir;
	t_vec	m_ab;//vector from p1 to p2
}	t_CamRay;

typedef	struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio;
}	t_canvas;

/* sphere  */

typedef	struct  s_sphere
    {
        t_vec		center;
        double      radius;
        double      radius2;
    }	t_sphere;

/* sphere end */

/*mlx func */

void	my_mlx_pixel_put(img_data *data, int x, int y, int color);

/* mlx funct end */

t_CamRay	ray(t_vec orig, t_vec dir);
t_vec		ray_at(t_CamRay *ray, double t);
t_canvas	canvas(int  width, int height);
t_camera	camera(t_canvas *canvas, t_vec origin);
t_CamRay	ray_primary(t_camera *cam, double u, double v);
t_vec		color(double r, double g, double b);
t_vec		ray_color(t_CamRay *r);
t_vec		make_vec(double x, double y, double z);
/* camera end */

// parse
void	ft_err(char *err);
int     check_file(int ac, char **av);
void    parse(t_scene *sc, int fd);
void    parse_line(char *id, char **tockens, t_scene *sc);
void    parse_plane(t_scene *sc, char **tockens);
void    parse_cylinder(t_scene *sc, char **tockens);
void    parse_sphere(t_scene *sc, char **tockens);
void    parse_light(t_scene *sc, char **tockens);
void    parse_camera(t_scene *sc,char **tockens);
void    parse_ambient(t_scene *sc, char **tockens);

// allocation
t_scene         *alloc_scence(void);
t_objs          *alloc_obj(t_objs   **objs);
void	        ft_collect(t_collector **root, t_collector *node);
void	        *ft_malloc(t_collector **root, size_t size);
t_collector	    *root;

// tools
int	    ft_strlen(const char *str);
char	*gnl(int fd);
double	ft_atod(const char *str);
int	    ft_atoi(const char *str);
char	**ft_split(const char *str, char c);
void	free_split(char **s);

//vectors
void	    null_vec(t_vec *v);
t_vec       get_vec(char *s);
t_vec       get_color(char *s);
t_vec		get_normalized(t_vec v);
void		normalize(t_vec *v);
double		get_norm2(t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec		add_vec(t_vec u, t_vec v);
t_vec	    mult_vec(t_vec v, double a);
t_vec		vect_cross(t_vec u, t_vec v);
double	    dot_product(t_vec u, t_vec v);
t_vec		div_vect(t_vec v, double a);

// Intersection 

#endif