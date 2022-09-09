/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smia <smia@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 10:38:51 by smia              #+#    #+#             */
/*   Updated: 2022/09/08 19:24:47 by smia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	null_vec(t_vec *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

double	dot_product(t_vec u, t_vec v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec		vect_cross(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = (u.y * v.z) - (u.z * v.y);
	w.y = (u.x * v.z) - (u.z * v.x);
	w.z = (u.x * v.y) - (u.y * v.x);
	return (w);
}

t_vec	mult_vec(t_vec v, double a)
{
	v.x = v.x * a;
	v.y = v.y * a;
	v.z = v.z * a;
	return (v);
}

t_vec		add_vec(t_vec u, t_vec v)
{
	t_vec w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

t_vec		sub_vec(t_vec u, t_vec v)
{
	t_vec w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

double		module_v(t_vec	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

double		get_norm2(t_vec v)
{
	double result;

	result = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return (result);
}


void		normalize(t_vec *v)
{
	double	norm;

	norm = sqrt(get_norm2(*v));
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
}

t_vec		get_normalized(t_vec v)
{
	t_vec	v1;

	v1 = v;
	normalize(&v1);
	return (v1);
}

t_vec	div_vect(t_vec v, double a)
{
	v.x /= a;
	v.x /= a;
	v.z /= a;

	return (v);
}

t_vec	make_vec(double x, double y, double z)
{
	t_vec vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
