/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 12:28:21 by aouhadou          #+#    #+#             */
/*   Updated: 2022/09/25 14:06:18 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_inter	find_inter(t_CamRay *ray, t_scene *sc)
{
	t_inter	hold;
	t_objs	*obj;

	hold.t = -1.0;
	obj = sc->objs;
	while (obj)
	{
		if (obj->type == SP)
			hold = spher_normal(hold, obj, ray);
		if (obj->type == PL)
			hold = plane_normal(hold, obj, ray);
		if (obj->type == CY)
			hold = cylinder_normal(hold, obj, ray);
		obj = obj->next;
	}
	return (hold);
}
