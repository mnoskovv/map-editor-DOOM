/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 18:56:30 by aziabkin          #+#    #+#             */
/*   Updated: 2018/09/20 18:56:31 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_points	*new_elem(void)
{
	t_points	*node;

	if (!(node = (t_points*)malloc(sizeof(t_points))))
		return (NULL);
	node->x = 0;
	node->y = 0;
	node->end_right = NULL;
	node->end_down = NULL;
	node->end_diag1 = NULL;
	node->right = NULL;
	node->down = NULL;
	node->diag1 = NULL;
	node->next = NULL;
	return (node);
}

void		put_coords(t_all *all, int x, int y)
{
	all->points->x = x;
	all->points->y = y;
}

void		create_list1(t_all *all)
{
	int			x;
	int			y;
	int			iterations;
	t_points	*start;

	start = all->points;
	iterations = 0;
	x = 0;
	while (x < all->w * all->scale)
	{
		iterations++;
		y = 0;
		while (y < all->h * all->scale)
		{
			(iterations)++;
			put_coords(all, x + 20, y + 20);
			if (iterations == all->w * (all->h + 1))
			{
				all->points->next = NULL;
				break ;
			}
			else
				all->points->next = new_elem();
			all->points = all->points->next;
			y += (all->scale);
		}
		x += (all->scale);
	}
	all->points = start;
}

void		create_list_points(t_all *all)
{
	t_points	*first;
	t_points	*begin;

	first = new_elem();
	begin = first;
	create_list1(all);
}
