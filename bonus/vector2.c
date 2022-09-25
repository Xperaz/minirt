/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:26:22 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 14:07:26 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec	sub_vec(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

double	module_v(t_vec	v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
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
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
