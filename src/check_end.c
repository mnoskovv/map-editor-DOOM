/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziabkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:39:36 by aziabkin          #+#    #+#             */
/*   Updated: 2018/09/20 17:39:39 by aziabkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int check(int x_mouse,int y_mouse, t_all *all, int half_step)
{
	printf("click\n");
	printf("x click = %d y click = %d\n", x_mouse, y_mouse );
	t_points *start;

	start = all->points;
	while (all->points)
	{
		if (y_mouse <= all->points->y + 4 && y_mouse >= all->points->y - 4)
		{
			if (all->points->right && x_mouse >= all->points->x && x_mouse <= all->points->right->x)
			{
				if (all->points->end_right == NULL)
					all->points->end_right = all->points->right;
				else 
					all->points->end_right = NULL;
				all->points = start;
				return (1);
			}
		}
		else if (x_mouse <= all->points->x + 4 && x_mouse >= all->points->x - 4)
		{
			if (all->points->down && y_mouse >= all->points->y && y_mouse <= all->points->down->y)
			{
				if (all->points->end_down == NULL)
					all->points->end_down = all->points->down;
				else
					all->points->end_down = NULL;
				all->points = start;
				return (1);
			}
		}
		// просчитываем отрисовку дагоналей
		else if ((y_mouse >= all->points->y && all->points->down && y_mouse <= all->points->down->y) 
			&& (x_mouse >= all->points->x && all->points->right && x_mouse < all->points->x + half_step))
		{
				if (all->points->end_diag1 == NULL)
					all->points->end_diag1 = all->points->diag1;
				else
					all->points->end_diag1 = NULL;
				all->points = start;
				return (1);
		}
		all->points = all->points->next;
	}
	all->points = start;
	return  (0);
}