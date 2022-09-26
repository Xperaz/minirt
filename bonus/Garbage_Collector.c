/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Garbage_Collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhadou <aouhadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:13:09 by smia              #+#    #+#             */
/*   Updated: 2022/09/25 14:06:37 by aouhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_collector	*new_node(void *adr)
{
	t_collector	*node;

	node = malloc(sizeof(t_collector));
	if (!node)
		return (NULL);
	node->adr = adr;
	node->next = NULL;
	return (node);
}

t_collector	**append_adr(t_collector **g_root, void *adr)
{
	t_collector	*node;
	t_collector	*tmp;

	node = new_node(adr);
	if (!*g_root)
		return (*g_root = node, g_root);
	tmp = *g_root;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (g_root);
}

void	*ft_malloc(t_collector **g_root, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	else
		return (append_adr(g_root, ptr), ptr);
}

void	ft_collect(t_collector **g_root, t_collector *node)
{
	if (!node)
		return ;
	ft_collect(g_root, node->next);
	free(node->adr);
	free(node);
}
