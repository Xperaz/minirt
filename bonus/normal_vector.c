/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:24:24 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 14:06:56 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	get_norm2(t_vec v)
{
	double	result;

	result = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
	return (result);
}

void	normalize(t_vec *v)
{
	double	norm;

	norm = sqrt(get_norm2(*v));
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
}

t_vec	get_normalized(t_vec v)
{
	t_vec	v1;

	v1 = v;
	normalize(&v1);
	return (v1);
}
