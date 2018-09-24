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

int	check_3(int idx, t_all *all, int x_mouse)
{
	if (idx == CHECK_DIAG1)
	{
		if (all->points->end_diag1 == NULL)
			all->points->end_diag1 = all->points->diag1;
		else
			all->points->end_diag1 = NULL;
		return (1);
	}
	else if (idx == CHECK_DIAG2)
	{
		if (x_mouse > (all->points->x * all->zoom + all->half_step) && all->points->right \
			&& x_mouse <= all->points->right->x * all->zoom)
		{
			if (all->points->right->end_diag2 == NULL)
				all->points->right->end_diag2 = all->points->right->diag2;
			else
				all->points->right->end_diag2 = NULL;
			return (1);
		}
	}
	return (0);
}

int	check_2(int idx, t_all *all, int x_mouse, int y_mouse)
{
	if (idx == CHECK_RIGHT)
	{
		if (all->points->right && x_mouse >= all->points->x * all->zoom \
			&& x_mouse <= all->points->right->x * all->zoom)
		{
			if (all->points->end_right == NULL)
				all->points->end_right = all->points->right;
			else
				all->points->end_right = NULL;
			return (1);
		}
	}
	else if (idx == CHECK_LEFT)
	{
		if (all->points->down && y_mouse >= all->points->y * all->zoom \
			&& y_mouse <= all->points->down->y * all->zoom)
		{
			if (all->points->end_down == NULL)
				all->points->end_down = all->points->down;
			else
				all->points->end_down = NULL;
			return (1);
		}
	}
	return (0);
}

int	if_ret_one(t_all *all, int x_mouse, int y_mouse)
{
	if (y_mouse <= all->points->y * all->zoom + 4 && y_mouse >= all->points->y * all->zoom - 4)
	{
		if (check_2(CHECK_RIGHT, all, x_mouse, y_mouse))
			return (1);
	}
	else if (x_mouse <= all->points->x * all->zoom + 4 && x_mouse >= all->points->x * all->zoom - 4)
	{
		if (check_2(CHECK_LEFT, all, x_mouse, y_mouse))
			return (1);
	}
	else if ((y_mouse >= all->points->y * all->zoom && all->points->down && y_mouse <= \
		all->points->down->y * all->zoom) && (x_mouse >= all->points->x * all->zoom && \
		all->points->right && x_mouse < all->points->x * all->zoom + all->half_step))
	{
		if (check_3(CHECK_DIAG1, all, x_mouse))
			return (1);
	}
	else if ((y_mouse > all->points->y * all->zoom && all->points->down && \
		y_mouse < all->points->y * all->zoom + all->half_step))
	{
		if (check_3(CHECK_DIAG2, all, x_mouse))
			return (1);
	}
	return (0);
}

int	check(int x_mouse, int y_mouse, t_all *all)
{
	t_points *start;

	start = all->points;
	while (all->points)
	{
		if (if_ret_one(all, x_mouse, y_mouse))
		{
			all->points = start;
			return (1);
		}
		all->points = all->points->next;
	}
	all->points = start;
	return (0);
}
